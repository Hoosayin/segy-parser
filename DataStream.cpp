#include "DataStream.h"
#include <iostream>

DataStream::~DataStream()
{
    Cleanup();
}

DataStream::DataStream(
    const std::string& filename,
    ENDIAN_TYPE streamEndian)
{
    // Set Stream Endian.
    m_streamEndian = streamEndian;

    // Open SEG-Y File.
    m_segyFile.open(filename, std::ios::binary);

    if (m_segyFile.fail())
    {
        std::cout << "Failed to open " << filename << std::endl;
    }
    else
    {
        // Get file stream size.
        m_segyFile.seekg(0, std::ios::end);
        m_streamSize = m_segyFile.tellg();
        m_segyFile.seekg(0, std::ios::beg);
    }
}

void DataStream::DoRead(
    char *bytes, const size_t& size, 
    size_t& readPosition)
{
    // Lock SEG-Y file before reading.
    std::lock_guard<std::mutex> guard(m_fileLock);

    // Update read position if it has changed.
    if (m_segyFile.tellg() != readPosition)
        m_segyFile.seekg(readPosition);

    m_segyFile.read(bytes, size);
    readPosition = m_segyFile.tellg();
}

void DataStream::ReadBytes(float &data, size_t& readPosition)
{
    ReadAlgorithm(data, readPosition);
}

void DataStream::ReadBytes(int &data, size_t& readPosition)
{
    ReadAlgorithm(data, readPosition);
}

void DataStream::ReadBytes(unsigned int &data, size_t& readPosition)
{
    ReadAlgorithm(data, readPosition);
}

void DataStream::ReadBytes(unsigned short &data, size_t& readPosition)
{
    ReadAlgorithm(data, readPosition);
}

void DataStream::ReadBytes(short &data, size_t& readPosition)
{
    ReadAlgorithm(data, readPosition);
}

void DataStream::ReadBytes(
    char *bytes, size_t size,
    size_t& readPosition)
{
    DoRead(bytes, size, readPosition);
}

ENDIAN_TYPE DataStream::GetStreamEndian() const
{
    return m_streamEndian;
}

void DataStream::Cleanup()
{
    // Close the file.
    if (m_segyFile.is_open())
        m_segyFile.close();
}

size_t DataStream::Size() const
{
    return m_streamSize;
}
