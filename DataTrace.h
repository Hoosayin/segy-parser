#pragma once

#include "TraceHeader.h"
#include "DataStream.h"

#include <vector>
#include <fstream>

class DataTrace
{
private:
    TraceHeader m_traceHeader{};
    std::vector<float> m_samples{};
    int m_numberOfSamples{ 0 };
    float m_sampleInterval{ 0.0f };

public:
    DataTrace() = delete;
    DataTrace(const int& numberOfSamples, const short& sampleInterval);
    virtual ~DataTrace() = default;

    void Unmarshal(DataStream& dataStream, size_t& readPosition);
    void WriteTraceHeader(std::ofstream& stream) const;
    void WriteDataSamples(std::ofstream& stream) const;
    int GetTraceSequenceNumberLine() const;
};