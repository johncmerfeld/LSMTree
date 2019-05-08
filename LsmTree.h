//
// Created by Stathis on 3/12/2019.
//

#ifndef SIMPLE_EXAMPLE_LSMTREE_H
#define SIMPLE_EXAMPLE_LSMTREE_H

#include <iostream>

#include "Level.h"
#include "MemoryRun.h"
#include "ResultSet.h"
#include <string>
#include <vector>

using namespace std;

class LsmTree {
protected:

    //---------- Levels ----------
    Level *diskLevels;
    MemoryRun *memRun;


    //---------- Tree metadata ----------
    int levelsCount;
    int entriesPerRun;
    short bitsPerValue;

    string filename;

    MemoryRun sortMerge(MemoryRun *older, MemoryRun *newer);

    string getNextFilename();

    RunMetadata *createMetadata(MemoryRun *memRunData, string suffix);

    Entry *getFromDisk(int key);

    string suffix(int level, int run);


public:
    LsmTree();

    LsmTree(int entriesPerRun, int maxRunsPerLevel, short bitsPerValue);

    void removeMany();

    Entry *get(int key);

    MemoryRun *getRange(int low, int high);

    void printMeta();

    ~LsmTree();
};

class TierLsmTree : public LsmTree {
public:
    TierLsmTree(int, int, short bitsPerValue);

    void flushToDisk();

    void insert(int key, int value, bool isRemove);

    void insert(int key, int value);

    void remove(int key);

    void insert(Entry *temp);


};

class LevelLsmTree : public LsmTree {
public:
    LevelLsmTree(int, int, short bitsPerValue);

    void flushToDisk();

    void insert(int key, int value);
};


#endif //SIMPLE_EXAMPLE_LSMTREE_H
