#include "Segy.h"
#include "CharacterSetHelper.h"

#include <iostream>
#include <array>

void Segy::Unmarshal(DataStream &dataStream)
{
    // Create read position of reading headers.
    size_t headersReadPosition{ 0 };

    std::cout << "Unmarshalling Text Header..." << std::endl;

    // Read Text Header.
    dataStream.ReadBytes(
        reinterpret_cast<char*>(m_textHeader), 
        TEXT_HEADER_SIZE, headersReadPosition);

    // Convert Text Header from EBCDIC to ASCII.
    CharacterSetHelper::ConvertEBCDICToASCII(m_textHeader);

    std::cout << "Unmarshalling Binary Header..." << std::endl;

    // Unmarshal bytes into BinaryHeader object.
    m_binaryHeader.Unmarshal(dataStream, headersReadPosition);

    std::cout << "Unmarshalling Data Traces and their samples..." << std::endl;

    // Calculate Number of Data Traces.
    int dataTraceBytes = dataStream.Size() - 
        (TEXT_HEADER_SIZE + BINARY_HEADER_SIZE);

    int numberOfSamplesPerTrace = 
        m_binaryHeader.GetNumberOfDataTracesForReel();

    int dataTraceSize = TRACE_HEADER_SIZE + 
        (SAMPLE_SIZE * numberOfSamplesPerTrace);

    int numberOfDataTraces = dataTraceBytes / dataTraceSize;

    // Calculate number of Data Traces per thread.
    int dataTracesPerThread = numberOfDataTraces / NUMBER_OF_THREADS;

    // Threads Array.
    std::array<DATA_TRACE_THREAD*, NUMBER_OF_THREADS> dataTraceThreads{};

    // Read Position for First Thread.
    size_t fromReadPosition = headersReadPosition;
    size_t toReadPosition = fromReadPosition + 
        (dataTraceSize * dataTracesPerThread);

    // Create threads for reading Data Traces.
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        DATA_TRACE_THREAD* dataTraceThread = new DATA_TRACE_THREAD();

        // Assign Read Position to the thread.
        dataTraceThread->m_readPosition = fromReadPosition;

        // Create thread.
        dataTraceThread->m_thread = std::thread(
        [this](
            int numberOfDataTraces, 
            DataStream* dataStream, 
            size_t* readPosition,
            std::mutex* dataTracesLock, 
            std::map<int, DataTrace>* dataTraces)
            {
                for (int i = 0; i < numberOfDataTraces; ++i)
                {
                    DataTrace dataTrace{ 
                        m_binaryHeader.GetNumberOfDataTracesForReel(), 
                        m_binaryHeader.GetSampleInterval() };

                    // Unmarshal bytes into DataTrace object.  
                    dataTrace.Unmarshal(*dataStream, *readPosition);
             
                    // Lock resource.
                    {
                        std::lock_guard<std::mutex> guard(*dataTracesLock);

                        // Empalce a new data trace.
                        dataTraces->emplace(
                            dataTrace.GetTraceSequenceNumberLine(), dataTrace );
                    }
                }

                return true;
        },
        dataTracesPerThread,
        &dataStream,
        &(dataTraceThread->m_readPosition),
        &m_dataTracesLock,
        &m_dataTraces);

        // Insert Data Trace Thread in array.
        dataTraceThreads[i] = dataTraceThread;

        // Compute Read Position for next thread.
        fromReadPosition = toReadPosition;

        /* If next thread is the last thread, 
           re-calculate number of data traces to read. */
        if (i == (NUMBER_OF_THREADS - 2))
        {
            toReadPosition = dataStream.Size();
            dataTracesPerThread = (toReadPosition - fromReadPosition) / dataTraceSize;
        }
        else
        {
            toReadPosition = fromReadPosition + (dataTraceSize * dataTracesPerThread);
        }
    }

    for (auto*& dataTraceThread : dataTraceThreads)
    {
        // Wait for thread to join Main Thread.
        dataTraceThread->m_thread.join();   

        // Delete Data Thread Thread.
        delete dataTraceThread;
        dataTraceThread = nullptr;
    }

    // Clean up DataStream.
    dataStream.Cleanup();
}

void Segy::WriteTextHeader(std::ofstream &stream) const
{
    stream << std::endl << std::endl
        << "TEXT HEADER" << std::endl;

    for (int i = 0; i < TEXT_HEADER_SIZE; ++i)
    {
        // Print a new line after every 80 characters.
        if (i % 80 == 0)
            stream << std::endl;
        
        stream << m_textHeader[i];
    }
}

void Segy::WriteToFile()
{
    std::ofstream outputFile{};
    outputFile.open("velocity.txt");

    std::cout << "Writing Text Header..." << std::endl;

    // Write Text Header.
    WriteTextHeader(outputFile);

    std::cout << "Writing Binary Header..." << std::endl;

    // Write Binary Header.
    m_binaryHeader.WriteHeader(outputFile);

    std::cout << "Writing Trace Headers..." << std::endl;

    // Write Trace Headers.
    outputFile << std::endl << std::endl
        << "TRACE HEADERS" << std::endl;

    outputFile << 
        "Trace #\t\tSP\t\tScalar\t\tSource X\t\tSource Y" 
        << std::endl;

    for (const auto& [index, dataTrace] : m_dataTraces)
        dataTrace.WriteTraceHeader(outputFile);

    std::cout << "Writing Data Samples..." << std::endl;

    // Write Data Samples.
    int traceNumber{ 0 };

    for (const auto& [index, dataTrace] : m_dataTraces)
    {
        std::cout << "Writing Data Samples for Trace # " << 
            std::to_string(++traceNumber) << "..." << std::endl;

        outputFile << std::endl << std::endl
            << "DATA SAMPLES - TRACE # " << traceNumber << std::endl;
        
        dataTrace.WriteDataSamples(outputFile);
    }

    outputFile.close();
}
