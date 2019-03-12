//
// Created by Stathis on 3/8/2019.
//
#include "BloomFilter.h"
#include "FencePointer.h"

#ifndef RUNMETADATA_H
#define RUNMETADATA_H


class RunMetadata {
private:
    BloomFilter *bloomfilter;
    FencePointer **fencePointers;
};

#endif //RUNMETADATA_H
