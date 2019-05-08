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

    FencePointer *fencepointers;
    string filename;
    int size;
    int numFencePointers;

public:
    RunMetadata(BloomFilter *bloomftr, FencePointer *fenceptrs, string filename, int size, int numFencePtrs);

    RunMetadata(BloomFilter *bloomftr, FencePointer *fenceptrs, string filename, int size);

    RunMetadata(string filename);

    // --------------------------------------------------------------
    string getFilename();

    BloomFilter *getBloomFilter();

    FencePointer *getFencePointers();

    int getNumFncPtrs();

    int getSize();

    void setFilename(string levelNumber);

    // --------------------------------------------------------------
    int pageInRange(int query);

    int pageRangeOverlaps(int low, int high);

    bool mightContain(int query);

    // --------------------------------------------------------------
    ~RunMetadata();
};

#endif //RUNMETADATA_H
