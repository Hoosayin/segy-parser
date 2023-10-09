#include "TraceHeader.h"

void TraceHeader::Unmarshal(DataStream &dataStream, size_t& readPosition)
{
    dataStream.ReadBytes(m_traceSequenceNumberLine, readPosition); 
    dataStream.ReadBytes(m_padding1, 12, readPosition);
    dataStream.ReadBytes(m_sp, readPosition);
    dataStream.ReadBytes(m_padding2, 50, readPosition);
    dataStream.ReadBytes(m_scalarCoordinates, readPosition);
    dataStream.ReadBytes(m_sourceX, readPosition);
    dataStream.ReadBytes(m_sourceY, readPosition);
    dataStream.ReadBytes(m_padding3, 160, readPosition);
}

void TraceHeader::WriteHeader(std::ofstream& stream) const
{
    stream << m_traceSequenceNumberLine << "\t\t\t" << 
        m_sp << "\t\t\t" << 
        m_scalarCoordinates << "\t\t\t" << 
        m_sourceX << "\t\t\t" << 
        m_sourceY << std::endl;
}

int TraceHeader::GetTraceSequenceNumberLine() const
{
    return m_traceSequenceNumberLine;
}
