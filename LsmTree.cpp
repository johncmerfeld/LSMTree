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

LsmTree::~LsmTree() {
    delete memRun;
    delete[] diskLevels;
}

//-------------------- Common methods --------------------
Entry *LsmTree::get(int key) {

    Entry *result = memRun->get(key);

    /* if we can't find it in memory */
    if (result == nullptr) {
        result = getFromDisk(key);
    }

    if (result == nullptr)
        return NULL;
        /* if we found a delete in memory */
    else if (result->isRemove()) {
        /* say we didn't find it */
        return NULL;
    }

    return result;
}

Entry *LsmTree::getFromDisk(int key) {
    for (int i = 0; i < levelsCount; i++) {
        /* get the array of metadata */
        RunMetadata **diskRunMetadata = diskLevels[i].getMetadata();
        /* for each run in the level: */
        MemoryRun *diskRun;
        for (int j = diskLevels[i].getRuns() - 1; j >= 0; j--) {
            /* if it might be there, read from disk */
            if ((diskRunMetadata[j]->mightContain(key)) &&
                (diskRunMetadata[j]->isInRange(key))) {
                diskRun = diskLevels[i].readEntries(diskRunMetadata[j], 0);
                Entry *result = diskRun->get(key);
                if (result == NULL) {
                    /* found a delete */
                    continue;
                }
                else if (result->isRemove()) {
                    return nullptr;
                }
                else {
                    return result;
                }
            }
        }
    }
    /* we didn't find it */
    return NULL;
}

/* gets a range from the LSM tree
 * First, gets the range from
 */
MemoryRun *LsmTree::getRange(int low, int high) {

    /* first get memory results */
    MemoryRun *results = memRun->getRange(low, high);
    results->sort();

    /* for each level: */
    for (int i = 0; i < levelsCount; i++) {
        /* get the array of metadata */
        RunMetadata **diskRunMetadata = diskLevels[i].getMetadata();
        /* for each run in the level: */
        for (int j = diskLevels[i].getRuns() - 1; j >= 0; j--) {

            MemoryRun *diskRun;
            /* only checking fence pointer because I don't think it
             * makes sense to check bloom filters for a large range */
            /* if it might be there, read from disk */
            if (diskRunMetadata[j]->rangeOverlaps(low, high)) {
                diskRun = diskLevels[i].readEntries(diskRunMetadata[j], 0);

                MemoryRun *diskResults = diskRun->getRange(low, high);
                diskResults->sort();

                results = MemoryRun::merge(diskResults, results);

            }
        }
    }

    /* remove deletes from result set */
    results->removeDeletes();
    return results;

}

RunMetadata *LsmTree::createMetadata(MemoryRun *memRunData, string suffix) {
    int entriesInRun = memRunData->getSize();
    Entry *entries = memRunData->getEntries();

//    printf("i will create metadata with size %d for entries:\n", memRunData->getSize());
//    memRunData->printer();

    //---------- Initialize Bloomfilter ----------
    int bloomFilterSize = entriesInRun * bitsPerValue / 8 + 1;
    BloomFilter *bloomftr = new BloomFilter(bloomFilterSize, bitsPerValue);
    for (int i = 0; i < entriesInRun; i++)
        bloomftr->add(entries[i].getKey());

    //---------- Initialize Fence Pointers ----------
    memRun->sort();
    FencePointer *fenceptr = new FencePointer(memRun->at(0).getValue(),
                                              memRun->at(memRun->getSize() - 1).getValue());

    //---------- Initialize filename ----------
    string filename = this->filename + suffix;

    //---------- Create the metadata  ----------
    RunMetadata *metadata = new RunMetadata(bloomftr, fenceptr, filename, entriesInRun);

    return metadata;
}

MemoryRun LsmTree::sortMerge(MemoryRun *left, MemoryRun *right) {

    int totalSize = left->getSize() + right->getSize();

    left->sort();
    right->sort();

    return *MemoryRun::merge(left, right);

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
    this->insert(key, value, false);
}

void TierLsmTree::remove(int key) {
	this->insert(key, 0, true);
}

void TierLsmTree::insert(int key, int value, bool isRemove) {
    Entry *temp = new Entry(key, value, isRemove);

    //---------- Insert the entry in the Memory Run ----------
    if (!this->memRun->insert(temp)) {
        //---------- If Memory Run fills up, flush to disk and reset the memoryRun ----------
        memRun->removeDuplicates();
        this->flushToDisk();
        memRun->reset();
    }

    delete temp;
}


void TierLsmTree::flushToDisk() {
    MemoryRun *data, *merged;

    TieringLevel *temp;
    RunMetadata *meta = nullptr;

    bool flag = false;
//    cout << "----------------------" << endl;
//    for (int i = 0; i < levelsCount; i++) {
//        diskLevels[i].printMeta();
//    }
//    cout << endl;

    //---------- Check if we can insert in the first level ----------
    //---------- After that get and use the merged data of the 1st level ----------
    if (diskLevels[0].hasSpace()) {
        meta = createMetadata(this->memRun, suffix(0, diskLevels[0].getRuns()));
        diskLevels[0].add(this->memRun, meta);
//        cout << "----------------" << endl;
        return;
    }
    else
        merged = diskLevels[0].mergeLevel(this->memRun);

//    memRun->reset();

    int levelsCounter = 1;
//    printf("merged before has %d \n", merged->getSize());
//    merged->printer();
//    cout << endl;

    while (levelsCounter < levelsCount && !flag) {
        flag = false;
//        cout << "mpike" << endl;
        if (diskLevels[levelsCounter].hasSpace()) {
            meta = createMetadata(merged, suffix(levelsCounter, diskLevels[levelsCounter].getRuns()));
            diskLevels[levelsCounter].add(merged, meta);
            flag = true;
        }
        else {
            data = merged;
            merged = diskLevels[levelsCounter].mergeLevel(merged);
            delete data;
//            printf("merged has %d \n", merged->getSize());
        }
        levelsCounter++;
    }

    //---------- If we did not manage to add the memory run to some existing level ----------
    if (!flag) {
        //---------- Add new level and insert the run in that level ----------
//        cout << "time for a new level" << endl;
        temp = new TieringLevel[levelsCount + 1];
        memcpy(temp, diskLevels, levelsCount * sizeof(TieringLevel));
        delete[] diskLevels;
        diskLevels = temp;
        levelsCount += 1;

        //---------- Insert the new run in the disk ----------
//        cout << "before creating metadata for new level ";
//        cout << meta->getSize();
        meta = createMetadata(merged, suffix(levelsCounter, diskLevels[levelsCounter].getRuns()));
        cout << "after creating metadata for new level ";
        cout << meta->getSize();
        diskLevels[levelsCounter].add(merged, meta);

    }
//    cout << "----------------------" << endl;
//    delete merged;
}





