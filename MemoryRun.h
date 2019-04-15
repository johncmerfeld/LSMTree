/*
 * Run.h
 *
 */

#ifndef MEMORYRUN_H_
#define MEMORYRUN_H_

#include "Entry.h"
#include "RunMetadata.h"


class MemoryRun {
private:
    Entry* entries;
    int maxEntries;
    int nextPos;

public:
    // implemented
    MemoryRun(int size);
    int numElements();
    bool insert(Entry* e);
    int get(int key);
    bool remove(int key);
    Entry* getEntries();
    Entry* getEntriesSorted();

    // not implemented
    int* getRange(int low, int high);

};


#endif /* MEMORYRUN_H_ */
