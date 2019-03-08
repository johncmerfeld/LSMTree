//
// Created by Stathis on 3/8/2019.
//
#include "BloomFilter.h"
#include "FencePointer.h"

#ifndef LSMTREE_RUNMETADATA_H
#define LSMTREE_RUNMETADATA_H
Class RunMetadata{
private:
        BloomFilter bloomfilter *;
        FencePointer fencePointers **;
};

#endif //LSMTREE_RUNMETADATA_H
