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

    bool insert(Entry e);
    void insertAtPos(Entry e, int pos);

    int get(int key);

    Entry at(int pos);

    ResultSet *getRange(int low, int high);

    bool remove(int key);

    Entry *getEntries();

    Entry *getEntriesSorted();

    static MemoryRun merge(MemoryRun* left, MemoryRun* right);

    static MemoryRun sort(MemoryRun* runToSort);

    void print();

    void reset();

    int getSize();
};


#endif /* MEMORYRUN_H_ */
