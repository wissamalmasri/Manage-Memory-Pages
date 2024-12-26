//Name: Wissam Almasri
//Red ID: 130183310

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdio>
#include "pageTableLevel.h"
#include "log.h"
#include "tracereader.h"

using namespace std;


int main(int argc, char **argv) {
    // Check if the number of command-line arguments is correct
    if (argc != 3) {
        cerr << "Usage: ./pagetrace <tracefile> <levelbits>" << endl; // Print usage message
        return 1;
    }

    // Open the trace file in binary read mode
    FILE *traceFile = fopen(argv[1], "rb");
    // Check if the file was opened successfully
    if (!traceFile) {
        cerr << "Unable to open " << argv[1] << endl; // Print error message
        return 1; // Return error code
    }

    // Create a string stream from the second command-line argument (level bits)
    istringstream levelStream(argv[2]);
    vector<unsigned int> levelBits; // Vector to store level bits
    unsigned int bit; // Temporary variable to hold each bit size
    // Read bit sizes from the string stream and store them in the vector
    while (levelStream >> bit) {
        levelBits.push_back(bit); // Add bit size to vector
    }

    unsigned int levelCount = levelBits.size(); // Get the number of levels
    // Create unique pointers for bit masks, shift amounts, and entry counts
    unsigned int* bitMaskAry(new unsigned int[levelCount]);
    unsigned int* shiftAry(new unsigned int[levelCount]);
    unsigned int* entryCount(new unsigned int[levelCount]);

    unsigned int totalBits = 32; // Assuming a 32-bit address space
    unsigned int shift = totalBits; // Initialize shift amount

    // Calculate bit masks, shift amounts, and entry counts for each level
    for (unsigned int i = 0; i < levelCount; i++) {
        shift -= levelBits[i]; // Update shift amount
        bitMaskAry[i] = ((1U << levelBits[i]) - 1) << shift; // 1U << levelBits[i] shifts the number 1 to the left by levelBits[i] positions.
        // This creates a value with levelBits[i] number of ones in binary (for 3 bits: 111).
        // Subtracting 1 ensures we get all ones for that number of bits (2^3 - 1 = 111 in binary).
        // Then, the result is shifted left by shift, so the bit mask is placed correctly in the total address.
        // The bit mask will extract the corresponding bits from the virtual address for this level of the table.
        shiftAry[i] = shift; // Store shift amount
        entryCount[i] = 1U << levelBits[i]; // Calculate number of entries
        // 1U << levelBits[i] calculates the total number of entries or slots in the table at this level.
        // Since 'levelBits[i]' defines the number of bits used for indexing, the number of entries is 2^levelBits[i].
        // This determines how many possible entries or pointers exist for this level of the page table.
    }

    // Create a PageTable object with the calculated parameters
    PageTable pageTable(levelCount, bitMaskAry, shiftAry, entryCount);

    log_bitmasks(levelCount, bitMaskAry); // Log bitmasks for each level

    p2AddrTr traceAddr; // Struct to hold address from trace file
    // Read addresses from the trace file
    while (NextAddress(traceFile, &traceAddr)) {
        unsigned int address = traceAddr.addr; // Get the address from the struct
        // Create a unique pointer for page indices at each level
        unsigned int* pageIndices(new unsigned int[levelCount]);

        // Calculate page indices for each level
        for (unsigned int i = 0; i < levelCount; i++) {
            pageIndices[i] = pageTable.extractPageNumberFromAddress(address, bitMaskAry[i], shiftAry[i]);
        }

        // Record page access and get the number of accesses
        unsigned int numOfAccesses = pageTable.recordPageAccess(address);

        // Log page indices and the number of accesses
        log_pgindices_numofaccesses(address, levelCount, pageIndices, numOfAccesses);
    }

    fclose(traceFile);
    return 0;
}
