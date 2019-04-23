//
// Created by Stathis on 3/12/2019.
//

#ifndef SIMPLE_EXAMPLE_LSMTREE_H
#define SIMPLE_EXAMPLE_LSMTREE_H

#include <iostream>

#include "Level.h"
#include "MemoryRun.h"
#include "DiskRun.h"
#include "ResultSet.h"
#include <string>

using namespace std;

class LsmTree {
protected:

    //---------- Levels ----------
    Level *diskLevels;
    MemoryRun *memRun;


    //---------- Tree metadata ----------
    int levelsCount;
    int currentLevel;
    int nextFileNumber;
    int entriesPerRun;
    short bitsPerValue;


    string getNextFilename();

    void createMetadata(MemoryRun *memRunData);

    int getFromDisk(int key);

public:
    LsmTree();

    LsmTree(int, int, short bitsPerValue);

    void insert(int value);

    void insert(int key, int value);

    void remove(int key);

    void removeMany();

    int get(int key);

    ResultSet *getRange(int low, int high);


};

class TierLsmTree : LsmTree {
public:
    TierLsmTree(int, int, short bitsPerValue);

    void flushToDisk(MemoryRun *memRunData);

    void insert(int key, int value);
};

class LevelLsmTree : LsmTree {
public:
    LevelLsmTree(int, int, short bitsPerValue);

    void flushToDisk(MemoryRun *memRunData);

    void insert(int key, int value);
};


#endif //SIMPLE_EXAMPLE_LSMTREE_H
