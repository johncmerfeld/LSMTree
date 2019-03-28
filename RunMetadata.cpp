/*
 * RunMetadata.cpp
 */

#include "RunMetadata.h"

RunMetadata::RunMetadata(BloomFilter bloomftr, FencePointer fenceptr) {
	this->bloomfilter = bloomftr;
	this->fencepointer = fenceptr;
}


