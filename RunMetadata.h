//
// Created by Stathis on 3/8/2019.
//
#include "BloomFilter.h"
#include "FencePointer.h"
#include <string>

using namespace std;

#ifndef RUNMETADATA_H
#define RUNMETADATA_H

class RunMetadata {

private:
    BloomFilter *bloomfilter;

    /* TODO change this to an array of fence pointers */
    FencePointer *fencepointer;
    string filename;
    int size;

public:
    RunMetadata(BloomFilter *bloomftr, FencePointer *fenceptr, string filename, int size);

    RunMetadata(string filename);

    void setFilename(string levelNumber);

    string getFilename();

    BloomFilter* getBloomFilter();
    FencePointer* getFencePointer();

    bool isInRange(int query);
    bool rangeOverlaps(int low, int high);
    bool mightContain(int query);

    int getSize();

    ~RunMetadata();
};

#endif //RUNMETADATA_H
