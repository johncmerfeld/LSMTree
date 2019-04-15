//
// Created by Stathis on 3/12/2019.
//

#ifndef SIMPLE_EXAMPLE_LSMTREE_H
#define SIMPLE_EXAMPLE_LSMTREE_H

#include "Level.h"
#include "MemoryRun.h"
#include "DiskRun.h"
#include <string>

using namespace std;

class LsmTree {
private:

    Level* diskLevels;
    MemoryRun* memRun;

    int levelsCount;
    int nextFileNumber;
    int entriesPerRun;
    short bitsPerValue;

    string getNextFilename();
    void flushToDisk(Entry* entries);

    int getFromDisk(int key);

public:
    LsmTree();
    LsmTree(short bitsPerValue);

    void insert(int value);
    void insert(int key, int value);

    void remove(int key);
    void removeMany();

    int get(int key);



};


#endif //SIMPLE_EXAMPLE_LSMTREE_H
