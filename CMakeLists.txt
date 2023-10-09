cmake_minimum_required(VERSION 3.20)
project(SEGY_PARSER)
add_executable(${PROJECT_NAME} 
    main.cpp
    Endian.cpp
    IBMFloatingPointParser.cpp
    DataStream.cpp
    BinaryHeader.cpp
    TraceHeader.cpp
    DataTrace.cpp
    CharacterSetHelper.cpp
    Segy.cpp)
