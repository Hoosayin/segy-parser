# SEGY Parser

**segy-parser** is a C++ console application designed to parse SEGY binary files and extract specific information for each record. The extracted data includes the Text Header, Binary Header, and Data Traces and their samples. This information is then written in a Text file in ASCII format.

## What is SEGY?

**SEGY** stands for "Standard for the Exchange of Geophysical Data." It is a common file format used in the geophysical industry, particularly for storing seismic data. SEGY files contain information about subsurface structures, such as those used in oil and gas exploration, and they store seismic measurements in a standardized binary format for processing and analysis.

## Technical Details

- **DataStream Class**: This class holds an input Stream file object of an input SEGY file. It also contains stream size and source Endian type information. The class provides utility methods to read different data types and increments the read position accordingly.

- **Endian Class**: The Endian class maintains the state of the machine Endian and stream Endian. It provides a method to convert stream Endian into machine Endian.

- **IBMFloatingPointParser Class**: This class parses the data samples represented in IBM Floating Point to IEEE Floating Point.

- **CharacterSetHelper Class**: The CharacterSetHelper class offers a utility method to convert EBCDIC Text Headers to ASCII characters.

- **TraceHeader Class**: Responsible for unmarshalling Trace Header from a given data stream position and writing parsed values to an output stream file.

- **DataTrace Class**: The DataTrace class holds a TraceHeader object and is responsible for unmarshalling data samples from a given data stream position and writing them to an output stream file.

- **BinaryHeader Class**: Responsible for unmarshalling Binary Headers from a given data stream position and writing parsed values to an output stream file.

- **Segy Class**: The Segy class is the main class that corresponds to the SEGY 2.0 format specification. It is responsible for unmarshalling the Text Header, then delegating unmarshalling commands to the BinaryHeader class object, and finally to the DataTraces class objects. It also handles the writing of the entire SEGY file to an output stream file. In practice, SEGY files can be very large, so the Segy class divides the number of data traces to be read into four. It creates four threads and assigns them a subset of data traces to be read with data stream positions accordingly. Since the DataStream object is a shared resource, a thread-safety mechanism is implemented using std::mutex and std::lock-guard objects. Once a thread finishes unmarshalling its data traces, it joins the main thread. Once all the SEGY data stream is unmarshalled, the main thread starts writing parsed information in ASCII to an output stream file.

- **main.cpp**: Contains the driver code for unmarshalling the "velocity.segy" file and performs benchmarking for the entire unmarshalling process.

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
