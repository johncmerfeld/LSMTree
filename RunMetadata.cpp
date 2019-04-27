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

RunMetadata::RunMetadata(BloomFilter *bloomftr, FencePointer *fenceptr,
                         string filename, int size) {
    this->bloomfilter = bloomftr;
    this->fencepointer = fenceptr;
    this->filename = filename;
    this->size = size;

}

RunMetadata::RunMetadata(string filename) : RunMetadata(nullptr, nullptr, filename, 0) {

}

void RunMetadata::setFilename(string levelNumber) {
    this->filename = levelNumber;
}

string RunMetadata::getFilename() {
    return this->filename;
}

int RunMetadata::getSize() {
    return this->size;
}

RunMetadata::~RunMetadata() {
    delete bloomfilter;
    delete fencepointer;
}