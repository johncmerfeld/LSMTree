//
// Created by Stathis on 3/12/2019.
//

#include "LsmTree.h"
#include "MemoryRun.h"
#include <string>

using namespace std;

#define pageSize 4096

LsmTree::LsmTree():LsmTree(4) {

}



LsmTree::LsmTree(int bitsPerValue) {
	this->bitsPerValue = bitsPerValue;
	this->levelsCount = 0;
    /*this->levels = new TieringLevel[1];
    this->levelsCount = 1;
    Level::setRunsPerLevel(runsPerLevel);
    memRun = new MemoryRun(entriesPerRun); */
}

void LsmTree::insert(int value) {
	insert(value, value);
}

void LsmTree::insert(int key, int value) {

	/* make a new 'Insert' entry */
	Entry e = new Entry(key, value, false);

	/* insert into memory run. If it's full: */
	if (! memRun.insert(e)) {
		this->flushToDisk(memRun.entries);
	}

}

void LsmTree::remove(int key) {

	/* delete from memory run. If that fills it: */
	if (! memRun.remove(key)) {
		this->flushToDisk(memRun.entries);
	}
}

/* returns NULl if not in tree */
int LsmTree::get(int key) {

	int result = memRun.get(key);

	/* if we can't find it in memory */
	if (result == NULL) {
		// result = search disk levels()
	}

	return result;

}

void LsmTree::flushToDisk(Entry* entries) {
	/* sort it */
	//BloomFilter bloomftr = new BloomFilter(...);
	//FencePointer fenceptr = new FencePointer(lowest, highest);
	//
	//RunMetadata runmeta = new RunMetaData(bloomftr, fenceptr, disk pointer);
}

string LsmTree::getNextFilename() {
	// read next file number...
}







