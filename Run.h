/*
 * Run.h
 *
 */

#ifndef RUN_H_
#define RUN_H_

#include "Entry.h"
#include "RunMetadata.h"


class MemoryRun {
private:
    Entry *entries;
    int maxEntries;
    int nextPos;


public:
    MemoryRun(int size)

    bool insert(Entry e);

    bool insert(Entry e, int pos);

    bool remove(Entry e);

    bool remove(int pos);

    int numElements();

    Entry get(int pos);

};

class DiskRun {
private:
    int fileDesc;
    BloomFilter *bloomfilter;
    FencePointer *fencePointers;
};


#endif /* RUN_H_ */
