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

int RunMetadata::pageInRange(int query) {
    printf("we have %d fencepointers\n", numFencePointers);
    for (int i = 0; i < numFencePointers; i++) {
        if (fencepointers[i].isInRange(query)) {
            return i;
        }
    }
    /* not in range */
    return -1;
}

int RunMetadata::pageRangeOverlaps(int low, int high) {

    for (int i = 0; i < numFencePointers; i++) {
        if (fencepointers[i].rangeOverlaps(low, high)) {
            return i;
        }
    }
    /* no overlap */
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
    delete fencepointers;
}
