#pragma once

#include "DataStream.h"
#include <fstream>

class TraceHeader
{
private:
    int m_traceSequenceNumberLine{}; // 1 - 4
    char m_padding1[12]{}; // 5 - 16
    int m_sp{}; // 17 - 20
    char m_padding2[50]{}; // 21 - 70
    short m_scalarCoordinates{}; // 71 - 72
    int m_sourceX{}; // 73 - 76
    int m_sourceY{}; // 77 - 80
    char m_padding3[160]{}; // 81 - 240

public:
    TraceHeader() = default;
    virtual ~TraceHeader() = default;

    void Unmarshal(DataStream& dataStream, size_t& readPosition);
    void WriteHeader(std::ofstream& stream) const;

    int GetTraceSequenceNumberLine() const;
};