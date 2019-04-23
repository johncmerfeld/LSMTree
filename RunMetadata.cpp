/*
 * RunMetadata.cpp
 */

#include "RunMetadata.h"

RunMetadata::RunMetadata(BloomFilter* bloomftr, FencePointer* fenceptr, string filename) {
	this->bloomfilter = bloomftr;
	this->fencepointer = fenceptr;
	this->filename = filename;
}

void RunMetadata::setFilename(string levelNumber) {
	this->filename = filename;
}


