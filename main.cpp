#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "DataStream.h"
#include "Segy.h"

int main ()
{
    // Create a DataStream object.
    DataStream dataStream{ "velocity.segy", ENDIAN_TYPE::BIG };
    
    Segy segy{};

    // Create Timepoint objects for benchmarking.
    std::chrono::time_point<std::chrono::system_clock> 
        start{}, end{};

    std::cout << "Unmarshalling velocity.segy. This may take some time..." << std::endl;
    
    // Note the time before unmarshalling.
    start = std::chrono::system_clock::now();

    // Unmarshal bytes into Segy object.
    segy.Unmarshal(dataStream);

    // Note the time after unmarshalling.
    end = std::chrono::system_clock::now();

    // Calculate Unmarshal Time.
    std::chrono::duration<double> unmarshalTime = end - start;

    std::cout << "Unmarshal Time: " << 
        unmarshalTime.count() << std::endl;

    std::cout << "Writing velocity.txt. This may take some time..." << std::endl;

    // Write unmarshalled data into file.
    segy.WriteToFile();

    std::cout << 
        "File has been written successfully." << std::endl;

    return EXIT_SUCCESS;
}