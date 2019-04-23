//
// Created by Stathis on 3/12/2019.
//

#include "LsmTree.h"
#include "MemoryRun.h"
#include "RunMetadata.h"
#include "ResultSet.h"
#include "Level.h"
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

#define pageSize 4096

LsmTree::LsmTree(int entriesPerRun, int maxRunsInLevel, short bitsPerValue) {

    this->bitsPerValue = bitsPerValue;

    diskLevels = new TieringLevel[2];
    cout << "constructor" << endl;
    cout << diskLevels[0].hasSpace() << endl;
    cout << "perase" << endl;
    this->levelsCount = 2;
    this->currentLevel = 0;

    this->nextFileNumber = 1;


    /*this->levels = new TieringLevel[1];
    this->levelsCount = 1;*/
    Level::setRunsPerLevel(maxRunsInLevel);

    //----------  Setup memory run ----------
    this->entriesPerRun = entriesPerRun;
    this->memRun = new MemoryRun(entriesPerRun);
}

void LsmTree::insert(int value) {
    insert(value, value);
}

void LsmTree::insert(int key, int value) {

    /* make a new 'Insert' entry */
    Entry *e = new Entry(key, value, false);

    /* insert into memory run. If it's full: */
    if (!memRun->insert(e)) {
        this->createMetadata(memRun);
    }

}

void LsmTree::remove(int key) {

    /* delete from memory run. If that fills it: */
    if (!memRun->remove(key)) {
        this->createMetadata(memRun);
    }
}

/* returns NULL if not in tree */
int LsmTree::get(int key) {

    int result = memRun->get(key);

    /* if we can't find it in memory */
    if (result == 0) {
        result = getFromDisk(key);
    }
    return result;
}

ResultSet *LsmTree::getRange(int low, int high) {

    ResultSet *memoryResults = memRun->getRange(low, high);
    //ResultSet diskResults = diskLevels->getRange(low, high); /* need to implement this */
    //return memoryResults.combine(diskResults);

    return memoryResults;

}


void LsmTree::createMetadata(MemoryRun *memRunData) {
    int entriesPerRun = memRunData->getSize();

    BloomFilter *bloomftr = new BloomFilter(1024, 5); // args?
    for (int i = 0; i < entriesPerRun; i++) {
        bloomftr->add(memRunData->at(i).getKey());
    }

    FencePointer *fenceptr = new FencePointer(entries[0].getValue(), entries[entriesPerRun - 1].getValue());
    string filename = getNextFilename();
    RunMetadata *runmeta = new RunMetadata(bloomftr, fenceptr, filename);

    /* TODO write to the file and give the run metadata to disk tree */
}

int LsmTree::getFromDisk(int key) {
    return -1;
}

string LsmTree::getNextFilename() {
    return "file" + std::to_string(nextFileNumber++) + ".dat";
}


//---------- Tier Level methods ----------
TierLsmTree::TierLsmTree(int entriesPerRun, int maxRunsInLevel, short bitsPerValue)
        : LsmTree(entriesPerRun, maxRunsInLevel, bitsPerValue) {

}

void TierLsmTree::insert(int key, int value) {
//    LsmTree::insert(key, value);
    if (this->memRun->insert(new Entry(key, value))) {
        this->flushToDisk(this->memRun);
        TieringLevel *temp;

    }
}

void TierLsmTree::flushToDisk(MemoryRun *data) {
    MemoryRun *mergedData;
    TieringLevel *temp;
    int levelsCounter = 0;

    while (levelsCounter < this->levelsCount) {
        if (this->diskLevels[levelsCounter].hasSpace()) {
            createMetadata(data);
            diskLevels[levelsCounter].add(data->getEntries(), data->numElements());
            return;
        }
        data = diskLevels[levelsCounter].mergeLevel(data);
        levelsCounter++;
    }

    temp = new TieringLevel[levelsCount * 2];
    memcpy(temp, diskLevels, levelsCounter * sizeof(TieringLevel));
    delete diskLevels;
    diskLevels = temp;
    levelsCount *= 2;

    diskLevels[levelsCounter].add(data->getEntries(), data->numElements());
    //create metadata
    //diskLevels[levelsCounter].add()

}





