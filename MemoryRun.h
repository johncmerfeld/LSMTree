/*
 * Run.h
 *
 */

#ifndef MEMORYRUN_H_
#define MEMORYRUN_H_

#include "Entry.h"
#include "RunMetadata.h"
#include "ResultSet.h"


class MemoryRun {
private:
    Entry *entries;
    int maxEntries;
    int nextPos;

public:
    // implemented
    MemoryRun(int size);

    MemoryRun(Entry *entries, int size);

    int numElements();

    bool insert(Entry *e);

    int get(int key);

    ResultSet *getRange(int low, int high);

    bool remove(int key);

    Entry *getEntries();

    Entry *getEntriesSorted();

    void reset();

    int getSize();
};


#endif /* MEMORYRUN_H_ */
