/*
 * Run.h
 *
 */

#ifndef MEMORYRUNn_H_
#define MEMORYRUNn_H_

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

    bool insert(Entry *entry);



//rggr


    void insertAtPos(Entry e, int pos);

    int get(int key);

    Entry at(int pos);

    ResultSet *getRange(int low, int high);

    bool remove(int key);

    Entry *getEntries();

    static MemoryRun *merge(MemoryRun *left, MemoryRun *right);

    void sort();

    void print();

    void reset();

    int getSize();

    void printer();

    ~MemoryRun();
};


#endif /* MEMORYRUN_H_ */
