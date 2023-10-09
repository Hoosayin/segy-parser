#pragma once

#include "BinaryHeader.h"
#include "DataStream.h"
#include "DataTrace.h"

#include <map>
#include <fstream>
#include <thread>
#include <mutex>

// Constants
constexpr unsigned short TEXT_HEADER_SIZE{ 3200 };
constexpr unsigned short BINARY_HEADER_SIZE{ 400 };
constexpr unsigned short TRACE_HEADER_SIZE{ 240 };
constexpr unsigned short SAMPLE_SIZE{ 4 };
constexpr unsigned short NUMBER_OF_THREADS{ 4 };

struct DATA_TRACE_THREAD
{
    size_t m_readPosition{};
    std::thread m_thread{};

    DATA_TRACE_THREAD() = default;
    virtual ~DATA_TRACE_THREAD() = default;
};

class Segy
{
private:
    unsigned char m_textHeader[TEXT_HEADER_SIZE]{};
    BinaryHeader m_binaryHeader{};
    std::map<int, DataTrace> m_dataTraces{};
    std::mutex m_dataTracesLock{};
    
    void WriteTextHeader(std::ofstream& stream) const;

public:
    Segy() = default;
    virtual ~Segy() = default;

    void Unmarshal(DataStream& dataStream);
    void WriteToFile();
};