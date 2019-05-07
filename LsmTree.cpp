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

    int page = -1;

    for (int i = 0; i < levelsCount; i++) {
        /* get the array of metadata */
//        printf("gonna get meta from level %d\n", i);
//        getchar();
        RunMetadata **diskRunMetadata = diskLevels[i].getMetadata();
//        printf("i got the meta from level %d\n\n", i);
        /* for each run in the level: */
        MemoryRun *diskRun;
//        printf("runs in  level %d are %d\n", i, diskLevels[i].getRuns() - 1);
        for (int j = diskLevels[i].getRuns() - 1; j >= 0; j--) {
            /* if it might be there, read from disk */
//            printf("entered level %d\n", i);
//            getchar();
//            diskLevels[j].printMeta();
            if (diskRunMetadata[j]->mightContain(key)) {
//                printf("we ARE in the might contain\n");
                page = diskRunMetadata[j]->pageInRange(key);
//                printf("found it in page %d\n", page);
                /* if it's in the range of a page, read disk */
                if (page != -1) {
//                    printf("in here\n");
                    diskRun = diskLevels[i].readEntries(diskRunMetadata[j], 0, page);
//                    diskRun->printer();
//                    diskRun->printer();
                    Entry *result = diskRun->getBinarySearch(key);

                    if (result == nullptr) {
//                        printf("alalala");
                        continue;
                    }
                    else if (result->isRemove()) {
                        /* found a delete */
//                        printf("hohoho");
                        return nullptr;
                    }
                    else {
                        return result;
                    }
                }
            }
        }
    }
    /* we didn't find it */
    return nullptr;
}

/* gets a range from the LSM tree
 * First, gets the range from
 */
MemoryRun *LsmTree::getRange(int low, int high) {

    /* first get memory results */
    MemoryRun *results = memRun->getRange(low, high);
    results->sort();

    int page = -1;

    /* for each level: */
    for (int i = 0; i < levelsCount; i++) {
        /* get the array of metadata */
        RunMetadata **diskRunMetadata = diskLevels[i].getMetadata();
        /* for each run in the level: */
        for (int j = diskLevels[i].getRuns() - 1; j >= 0; j--) {

            MemoryRun *diskRun;

            page = diskRunMetadata[j]->pageRangeOverlaps(low, high);
            /* if it's in the range of a page, read disk */
            if (page != -1) {
                diskRun = diskLevels[i].readEntries(diskRunMetadata[j], 0, page);

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


    //---------- Initialize Bloomfilter ----------
    int bloomFilterSize = entriesInRun * bitsPerValue / 8 + 1;
    BloomFilter *bloomftr = new BloomFilter(bloomFilterSize, bitsPerValue);
    for (int i = 0; i < entriesInRun; i++)
        bloomftr->add(entries[i].getKey());

    //---------- Initialize Fence Pointers ----------
    memRun->sort();
    FencePointer *fenceptr = new FencePointer[1];
    int
            numOfFencePointers = memRunData->getSize() * sizeof(Entry) / getpagesize() +
                                 int(memRunData->getSize() * sizeof(Entry) % getpagesize() != 0);
//    printf("memrun has size %d entry has size %d and page size is %d and we re gonna have %d pages\n",
//           memRunData->getSize(),
//           sizeof(Entry), getpagesize(), numOfFencePointers);
    FencePointer *fencePointer = new FencePointer[numOfFencePointers];
    int step = memRunData->getSize() / numOfFencePointers + int((memRunData->getSize() % numOfFencePointers) != 0);
    int i;
//    printf("low is %d and high is %d\n", memRunData->at(0).getKey(),
//           memRunData->at(memRunData->getSize() - 1).getKey());
    for (i = 0; i < numOfFencePointers - 1; i++) {
        fencePointer[i].setPointers(memRunData->at(i * step).getKey(), memRunData->at((i + 1) * step - 1).getKey());

    }
//    printf("%d %d\n", memRunData->at((numOfFencePointers - 1) * step).getKey(),
//           memRunData->at(memRunData->getSize() - 1).getKey());
    fencePointer[numOfFencePointers - 1].setPointers(memRunData->at((numOfFencePointers - 1) * step).getKey(),
                                                     memRunData->at(memRunData->getSize() - 1).getKey());
//    for (i = 0; i < numOfFencePointers; i++)
//        printf("low is %d and high is %d\n", fencePointer[i].getLowest(), fencePointer[i].getHighest());

    //---------- Initialize filename ----------
    string filename = this->filename + suffix;

    //---------- Create the metadata  ----------
    RunMetadata *metadata = new RunMetadata(bloomftr, fencePointer, filename, entriesInRun, numOfFencePointers);

    return metadata;
}

void LsmTree::printMeta() {
    for (int i = 0; i < levelsCount; i++)
        diskLevels[i].printMeta();
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
    //---------- Check if we can insert in the first level ----------
    //---------- After that get and use the merged data of the 1st level ----------
    if (diskLevels[0].hasSpace()) {
        meta = createMetadata(this->memRun, suffix(0, diskLevels[0].getRuns()));
        diskLevels[0].add(this->memRun, meta);
        FencePointer *pointers = meta->getFencePointers();
//        for (int i = 0; i < 12; i++) {
//            printf("lalalala %d-%d\n", pointers[i].getLowest(), pointers[i].getHighest());
//        }
        return;
    }
    else
        merged = diskLevels[0].mergeLevel(this->memRun);

//    memRun->reset();
//    printf("size of merged is %d\n", merged->getSize());
    int levelsCounter = 1;
    while (levelsCounter < levelsCount && !flag) {
        flag = false;
        if (diskLevels[levelsCounter].hasSpace()) {
            meta = createMetadata(merged, suffix(levelsCounter, diskLevels[levelsCounter].getRuns()));
            diskLevels[levelsCounter].add(merged, meta);
            flag = true;
        }
        else {
            data = merged;
            merged = diskLevels[levelsCounter].mergeLevel(merged);
            delete data;
        }
        levelsCounter++;
    }

    //---------- If we did not manage to add the memory run to some existing level ----------
    if (!flag) {
        //---------- Add new level and insert the run in that level ----------
        temp = new TieringLevel[levelsCount + 1];
        memcpy(temp, diskLevels, levelsCount * sizeof(TieringLevel));
        delete[] diskLevels;
        diskLevels = temp;
        levelsCount += 1;

        //---------- Insert the new run in the disk ----------
        meta = createMetadata(merged, suffix(levelsCounter, diskLevels[levelsCounter].getRuns()));
        diskLevels[levelsCounter].add(merged, meta);
    }
//    delete merged;
}





