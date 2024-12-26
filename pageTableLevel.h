//Name: Wissam Almasri
//Red ID: 130183310


#ifndef PAGETABLELEVEL_H // Include guard to prevent multiple inclusions
#define PAGETABLELEVEL_H

class PageTable {
public:
    unsigned int levelCount; // Number of levels in the page table
    unsigned int* bitMaskAry; // Array of bit masks for each level
    unsigned int* shiftAry; // Array of shift amounts for each level
    unsigned int* entryCount; // Array of entry counts for each level
    class Level* rootNodePtr; // Pointer to the root level

    // Constructor to initialize a PageTable
    PageTable(unsigned int levelCount, unsigned int* bitMaskAry, unsigned int* shiftAry, unsigned int* entryCount);
    // Destructor to clean up resources
    ~PageTable();
    unsigned int extractPageNumberFromAddress(unsigned int address, unsigned int mask, unsigned int shift);
    // Method to record a page access
    unsigned int recordPageAccess(unsigned int address);
};

class Level {
public:
    unsigned int depth; // Depth of this level in the page table
    PageTable* pageTablePtr; // Pointer to the associated PageTable
    unsigned int numOfAccesses; // Number of accesses to this level
    Level** nextLevelPtr; // Array of pointers to the next level

    // Constructor to initialize a Level
    Level(unsigned int depth, PageTable* pageTable);
    // Destructor to clean up resources
    ~Level();
    // Method to record a page access at this level
    unsigned int recordPageAccess(unsigned int address);
};

// Helper
#endif