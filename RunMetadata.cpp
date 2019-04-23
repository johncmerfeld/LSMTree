/*
 * RunMetadata.cpp
 */

#include "RunMetadata.h"

RunMetadata::RunMetadata(BloomFilter* bloomftr, FencePointer* fenceptr,
		string filename, int size) {
	this->bloomfilter = bloomftr;
	this->fencepointer = fenceptr;
	this->filename = filename;
	this->size = size;
}

void RunMetadata::setFilename(string levelNumber) {
	this->filename = filename;
}


