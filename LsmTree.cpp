//
// Created by Stathis on 3/12/2019.
//

#include "LsmTree.h"

#include "MemoryRun.h"

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
		/* sort it */
		//BloomFilter bloomftr = new BloomFilter(...);
		//FencePointer fenceptr = new FencePointer(lowest, highest);
		//disk pointer...
		//RunMetadata runmeta = new RunMetaData(bloomftr, fenceptr, disk pointer);

	}




}











