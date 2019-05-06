/*
 * RunMetadata.cpp
 */

#include "RunMetadata.h"
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

RunMetadata::RunMetadata(BloomFilter *bloomftr, FencePointer **fenceptrs,
                         string filename, int size, int numFencePtrs) {
    this->bloomfilter = bloomftr;
    this->fencepointers = fenceptrs;
    this->filename = filename;
    this->size = size;
    this->numFencePointers = numFencePtrs;

}

RunMetadata::RunMetadata(string filename) : RunMetadata(nullptr, nullptr, filename, 0) {

}

void RunMetadata::setFilename(string levelNumber) {
    this->filename = levelNumber;
}

string RunMetadata::getFilename() {
    return this->filename;
}

BloomFilter* RunMetadata::getBloomFilter() {
	return this->bloomfilter;
}

FencePointer** RunMetadata::getFencePointers() {
	return this->fencepointers;
}

bool RunMetadata::isInRange(int query) {
	//TODO fix this
	// return fencepointer->isInRange(query);
	return false;
}

bool RunMetadata::rangeOverlaps(int low, int high) {
	// TODO fix this
	//return fencepointer->rangeOverlaps(low, high);
	return false;
}

bool RunMetadata::mightContain(int query) {
	return bloomfilter->contains(query);
}

int RunMetadata::getSize() {
    return this->size;
}

RunMetadata::~RunMetadata() {
    delete bloomfilter;
    delete fencepointer;
}
