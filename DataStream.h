#pragma once

#include "Endian.h"

#include <vector>
#include <cstring>
#include <fstream>
#include <mutex>

class DataStream
{
private:
    std::ifstream m_segyFile{};
    std::mutex m_fileLock{};
    size_t m_streamSize{ 0 };
    ENDIAN_TYPE m_streamEndian{ ENDIAN_TYPE::BIG };

    template <typename T>
    void ReadAlgorithm(T &data, size_t& readPosition)
    {
        // Cast typename T into bytes
        char* bytes = reinterpret_cast<char*>(&data);
        size_t size = sizeof(T);

        // Read bytes.
        DoRead(bytes, size, readPosition);

        // Convert to Machine Endian. (LITTLE)
        Endian::GetInstance()->FlipBytes(
            bytes, size, m_streamEndian);
    }

    void DoRead(
        char *bytes, const size_t& size, 
        size_t& readPosition);

public:
    DataStream() = delete;
    
    DataStream(
        const std::string& filename,
        ENDIAN_TYPE streamEndian);
    
    virtual ~DataStream();

    // Read Operations.
    void ReadBytes(float &data, size_t& readPosition);

    void ReadBytes(int &data, size_t& readPosition);
    void ReadBytes(unsigned int &data, size_t& readPosition);

    void ReadBytes(short &data, size_t& readPosition);
    void ReadBytes(unsigned short &data, size_t& readPosition);

    void ReadBytes(char* bytes, size_t size, 
        size_t& readPosition);
    
    // Utility Functions.
    size_t Size() const;
    ENDIAN_TYPE GetStreamEndian() const;

    void Cleanup();
};