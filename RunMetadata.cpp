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

RunMetadata::RunMetadata(BloomFilter *bloomftr, FencePointer *fenceptrs, string filename, int size,
                         int numFencePtrs) {
    this->bloomfilter = bloomftr;
    this->fencepointers = fenceptrs;
    this->filename = filename;
    this->size = size;
    this->numFencePointers = numFencePtrs;
}

RunMetadata::RunMetadata(BloomFilter *bloomftr, FencePointer *fenceptrs,
                         string filename, int size) : RunMetadata(bloomftr, fenceptrs, filename, size, 1) {
}

RunMetadata::RunMetadata(string filename) : RunMetadata(nullptr, nullptr, filename, 1) {
}

void RunMetadata::setFilename(string levelNumber) {
    this->filename = levelNumber;
}

string RunMetadata::getFilename() {
    return this->filename;
}

BloomFilter *RunMetadata::getBloomFilter() {
    return this->bloomfilter;
}

FencePointer *RunMetadata::getFencePointers() {
    return this->fencepointers;
}

int RunMetadata::getNumFncPtrs() { return this->numFencePointers; }

/* binary search over fence pointers */
int RunMetadata::pageInRange(int query) {

	int left = 0;
	int right = numFencePointers - 1;
	int mid, outcome;

	while (left <= right) {
		mid = (right + left) / 2;
		outcome = fencepointers[mid].isInRange(query);
		if (outcome == 0) {
			return mid;
		}
		else if (outcome == -1) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	/* didn't find it */
	return -1;
}


int RunMetadata::pageRangeOverlaps(int low, int high) {

	int left = 0;
	int right = numFencePointers - 1;
	int mid, outcome;

	while (left <= right) {
		mid = (right + left) / 2;
		outcome = fencepointers[mid].rangeOverlaps(low, high);
		if (outcome == 0) {
			return mid;
		}
		else if (outcome == -1) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	/* didn't find it */
	return -1;
}

bool RunMetadata::mightContain(int query) {
    return bloomfilter->contains(query);
}

int RunMetadata::getSize() {
    return this->size;
}

RunMetadata::~RunMetadata() {
    delete bloomfilter;
    delete[] fencepointers;
}
