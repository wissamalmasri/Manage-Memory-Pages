Author
Wissam Almasri (Red ID: 130183310)


Multi-Level Page Table Simulation
This project simulates a multi-level page table, allowing you to process memory trace files and analyze the

Features
- Implements a multi-level page table using customizable bit masks and shifts for each level.
- Reads trace files containing memory access patterns.
- Outputs detailed logs of page indices and access statistics.

Files
- main.cpp: The entry point for the program, which initializes the page table and processes the trace file.
- pageTableLevel.h and pageTableLevel.cpp: Defines the PageTable and Level classes for handling the m
- tracereader.h and tracereader.cpp: Handles reading and decoding memory trace files.
- log.h and log.cpp: Provides utility functions for logging the results.
- Makefile: Automates the build process.

Usage
Prerequisites
- A C++ compiler supporting C++11 or later.
- A trace file in the specified format.

Compilation
Run the following command to compile the program:
make
Running the Program

Execute the program using:
./pagetrace <tracefile> <levelbits>
<tracefile>: Path to the memory trace file (e.g., trace.bin).
<levelbits>: Space-separated bit sizes for each level of the page table (e.g., 10 10 12).

Example
./pagetrace trace.bin 10 10 12

Output
The program generates logs containing:
1. The bit masks for each level.
2. Page indices and access counts for each memory address.

Code Overview

Key Classes
- PageTable: Represents the multi-level page table, calculates page indices, and tracks access statistics.
- Level: Represents individual levels of the page table and manages the hierarchical structure.

Trace File Reader
The trace reader processes binary trace files and converts memory addresses into a structured format for a

Logging
Logs are output to the console, detailing bit masks, page indices, and the frequency of page accesses.

License
This project is licensed under the MIT License. See the LICENSE file for details.
