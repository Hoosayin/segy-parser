# SEGY Parser

**segy-parser** is a C++ console application designed to parse SEGY binary files and extract specific information for each record. The extracted data includes the Text Header, Binary Header, and Data Traces and their samples. This information is then written in a Text file in ASCII format.

## What is SEGY?

**SEGY** stands for "Standard for the Exchange of Geophysical Data." It is a common file format used in the geophysical industry, particularly for storing seismic data. SEGY files contain information about subsurface structures, such as those used in oil and gas exploration, and they store seismic measurements in a standardized binary format for processing and analysis.

## Features

- Parses UKOOA text files.
- Extracts First and Last SP, X coordinate, and Y coordinate for each record.
- Appends the extracted information to a specified JSON file.

## Building and Running

### Configure (Modify CMake Generator as Needed)

For Linux:

```bash
./configure.sh
```

For Windows:

```bash
configure.bat
```

### Build (Make Appropriate Generator Choice)

For Linux:

```bash
./build.sh
```

For Windows:

```bash
build.bat
```

### Run

For Linux:

```bash
./run.sh
```

For Windows:

```bash
run.bat
```

Feel free to configure, build, and run the project as needed for your environment.

**Note:** Please ensure that you have the necessary dependencies, including CMake, properly set up in your environment before building and running the project.
