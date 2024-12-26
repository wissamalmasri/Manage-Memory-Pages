//Name: Wissam Almasri
//Red ID: 130183310

#include <iostream>
#include "pageTableLevel.h"


PageTable::PageTable(unsigned int levelCount, unsigned int* bitMaskAry, unsigned int* shiftAry, unsigned int* entryCount) {
    this->levelCount = levelCount; // Set the number of levels
    // Allocate memory for bit masks, shift amounts, and entry counts
    this->bitMaskAry = new unsigned int[levelCount];
    this->shiftAry = new unsigned int[levelCount];
    this->entryCount = new unsigned int[levelCount];

    // Copy the arrays into the PageTable instance
    for (unsigned int i = 0; i < levelCount; i++) {
        this->bitMaskAry[i] = bitMaskAry[i];
        this->shiftAry[i] = shiftAry[i];
        this->entryCount[i] = entryCount[i];
    }

    // Initialize the root level of the page table
    rootNodePtr = new Level(0, this);
}

// Record a page access by delegating to the root level
unsigned int PageTable::recordPageAccess(unsigned int address) {
    return rootNodePtr->recordPageAccess(address);
}

// PageTable destructor
PageTable::~PageTable() {
    delete rootNodePtr; // Delete the root level
    delete[] bitMaskAry; // Deallocate memory for bit masks
    delete[] shiftAry; // Deallocate memory for shift amounts
    delete[] entryCount; // Deallocate memory for entry counts
}

// Level constructor
Level::Level(unsigned int depth, PageTable* pageTable) {
    this->depth = depth; // Set the level depth
    this->pageTablePtr = pageTable; // Set the pointer to the page table
    this->numOfAccesses = 0; // Initialize the number of accesses
    // Allocate memory for next level pointers
    this->nextLevelPtr = new Level*[pageTable->entryCount[depth]];

    // Initialize all next level pointers to nullptr
    for (unsigned int i = 0; i < pageTable->entryCount[depth]; i++) {
        nextLevelPtr[i] = nullptr;
    }
}
unsigned int PageTable::extractPageNumberFromAddress(unsigned int address, unsigned int mask, unsigned int shift) {
    return (address & mask) >> shift; // Apply mask and shift to get the page number
}

// Record a page access at this level
unsigned int Level::recordPageAccess(unsigned int address) {
    // Extract the page index for this level
    unsigned int pageIndex = pageTablePtr->extractPageNumberFromAddress(address, pageTablePtr->bitMaskAry[depth], pageTablePtr->shiftAry[depth]);

    // If this is the last level, return the number of accesses
    if (depth == pageTablePtr->levelCount) {
        numOfAccesses++;
        return numOfAccesses;
    }


    // If the next level for this page index doesn't exist, create it
    if (nextLevelPtr[pageIndex] == nullptr) {
        nextLevelPtr[pageIndex] = new Level(depth + 1, pageTablePtr);
    }

    numOfAccesses++; // Increment the access count
    // Delegate the page access record to the next level
    return nextLevelPtr[pageIndex]->recordPageAccess(address);
}

// Level destructor
Level::~Level() {
    // Recursively delete next levels if this is not the last level
    if (depth < pageTablePtr->levelCount - 1) {
        for (unsigned int i = 0; i < pageTablePtr->entryCount[depth]; i++) {
            delete nextLevelPtr[i]; // Delete the next level
        }
    }
    delete[] nextLevelPtr; // Deallocate memory for next level pointers
}


