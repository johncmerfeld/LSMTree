//
// Created by Stathis on 3/8/2019.
//
#include "BloomFilter.h"
#include "FencePointer.h"

#ifndef RUNMETADATA_H
#define RUNMETADATA_H

class RunMetadata {

private:
	BloomFilter bloomfilter;
	FencePointer fencepointer;
	// disk location...

public:
	RunMetadata(BloomFilter bloomftr, FencePointer fenceptr);

};

#endif //RUNMETADATA_H
