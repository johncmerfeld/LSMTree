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
	BloomFilter* bloomfilter;
	FencePointer* fencepointer;
	string filename;

public:
	RunMetadata(BloomFilter* bloomftr, FencePointer* fenceptr, string filename);
	void setFilename(string levelNumber);
};

#endif //RUNMETADATA_H
