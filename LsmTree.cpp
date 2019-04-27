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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

#define pageSize 4096


//-------------------- Constructors --------------------

LsmTree::LsmTree(int entriesPerRun, int maxRunsInLevel, short bitsPerValue) {

    //---------- Setup levels information ----------
    this->levelsCount = 1;


    Level::setRunsPerLevel(maxRunsInLevel);

    //----------  Setup memory run ----------
    this->entriesPerRun = entriesPerRun;
    this->memRun = new MemoryRun(entriesPerRun);


    //---------- BloomFilter ----------
    this->bitsPerValue = bitsPerValue;

    //----------Filenames initiliazion ----------
    struct stat st = {0};
    if (stat("files", &st) == -1) {
        mkdir("files", 0700);
    }
    filename = "files/f";
}


//-------------------- Common methods --------------------
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


RunMetadata *LsmTree::createMetadata(MemoryRun *memRunData, string suffix) {
    int entriesPerRun = memRunData->getSize();
    Entry *entries = memRunData->getEntries();

    //---------- Initialize Bloomfilter ----------
    int bloomFilterSize = entriesPerRun * bitsPerValue / 8 + 1;
    BloomFilter *bloomftr = new BloomFilter(bloomFilterSize, bitsPerValue);
    for (int i = 0; i < entriesPerRun; i++)
        bloomftr->add(entries[i].getKey());

    //---------- Initialize Fence Pointers ----------
    memRun->sort();
    FencePointer *fenceptr = new FencePointer(memRun->at(0).getValue(),
                                              memRun->at(memRun->getSize() - 1).getValue());

    //---------- Initialize filename ----------
    string filename = this->filename + suffix;

    //---------- Create the metadata  ----------
    RunMetadata *metadata = new RunMetadata(bloomftr, fenceptr, filename, memRun->getSize());

    return metadata;
}

MemoryRun LsmTree::sortMerge(MemoryRun *left, MemoryRun *right) {

    int totalSize = left->getSize() + right->getSize();

    left->sort();
    right->sort();

    return *MemoryRun::merge(left, right);

}

int LsmTree::getFromDisk(int key) {
    return -1;
}

string LsmTree::suffix(int level, int run) {
    return (std::to_string(level) + "_" + std::to_string(run));

}

//-------------------- Tier Level methods --------------------

TierLsmTree::TierLsmTree(int entriesPerRun, int maxRunsInLevel, short bitsPerValue)
        : LsmTree(entriesPerRun, maxRunsInLevel, bitsPerValue) {
    //---------- Instantiate a disk level ----------
    this->diskLevels = new TieringLevel[1];
}

void TierLsmTree::insert(int key, int value) {
    this->insert(key, value, 0);
}

void TierLsmTree::insert(int key, int value, int type) {
    Entry *temp = new Entry(key, value, 0);

    //---------- Insert the entry in the Memory Run ----------
    if (!this->memRun->insert(temp)) {
        //---------- If Memory Run fills up, flush to disk and reset the memoryRun ----------
        this->flushToDisk(this->memRun);
        memRun->reset();
    }

    delete temp;
}


void TierLsmTree::flushToDisk(MemoryRun *data) {
    MemoryRun *mergedData;
    TieringLevel *temp;
    RunMetadata *meta;
    int levelsCounter = 0;
    bool flag = 0;

    do {
        flag = false;
        if (diskLevels[levelsCounter].hasSpace()) {
            meta = createMetadata(data, suffix(levelsCounter, diskLevels[levelsCounter].getRuns()));
            diskLevels[levelsCounter].add(data, meta);
            flag = true;
        } else {
            data = diskLevels[levelsCounter].mergeLevel(data);
        }
        levelsCounter++;
    } while (levelsCounter < levelsCount && !flag);

    //---------- If we managed to add the memory run to some level return ----------
    if (flag)
        return;


    //---------- Add new level and insert the run in that level ----------

    temp = new TieringLevel[levelsCount + 1];
    memcpy(temp, diskLevels, levelsCounter * sizeof(TieringLevel));
    delete diskLevels;
    diskLevels = temp;
    levelsCount += 1;

    meta = createMetadata(data, suffix(levelsCounter, diskLevels[levelsCounter].getRuns()));
    diskLevels[levelsCounter].add(data, meta);
}





