#include "DataTrace.h"
#include "IBMFloatingPointParser.h"

#include <iostream>
#include <iomanip>

DataTrace::DataTrace(const int& numberOfSamples, const short& sampleInterval)
{
    m_numberOfSamples = numberOfSamples;
    m_sampleInterval = static_cast<float>(sampleInterval) / 1000.0f; // Microseconds to Milliseconds
}

void DataTrace::Unmarshal(DataStream &dataStream, size_t& readPosition)
{
    // Unmarshal bytes into TraceHeader object.
    m_traceHeader.Unmarshal(dataStream, readPosition);

    for (int i = 0; i < m_numberOfSamples; ++i)
    {
        unsigned int sample{};
        dataStream.ReadBytes(sample, readPosition);

        // Convert IBM Floating Point Number to IEEE Floating Point Number.
        m_samples.push_back(IBMFloatingPointParser::
            ParseAsIEEEFloatingPoint(sample));
    }
}

void DataTrace::WriteTraceHeader(std::ofstream& stream) const
{
    m_traceHeader.WriteHeader(stream);
}

void DataTrace::WriteDataSamples(std::ofstream &stream) const
{
    stream << "Index\t\tTime (ms)\t\tSample" << std::endl;

    int index{ 0 };
    float time{ 0.0f };

    for (const auto& sample : m_samples)
    {
        stream << 
            index << "\t\t\t" << 
            time << "\t\t\t\t" <<
            std::setprecision(8) << 
            sample << std::endl;

        ++index;
        time += m_sampleInterval;
    }
}

int DataTrace::GetTraceSequenceNumberLine() const
{
    return m_traceHeader.GetTraceSequenceNumberLine();
}
