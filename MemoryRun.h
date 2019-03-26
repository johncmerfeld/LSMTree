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
    Entry *entries;
    int maxEntries;
    int nextPos;


public:
    MemoryRun(int size);

    bool insert(Entry e);

    bool insert(Entry e, int pos);

    bool remove(Entry e);

    bool remove(int pos);

    int numElements();

    Entry get(int pos);

public:
    Entry *getEntries();
    int search(int key);

};


#endif /* MEMORYRUN_H_ */
