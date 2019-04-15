//
// Created by Stathis on 3/12/2019.
//

#include "LsmTree.h"
#include "MemoryRun.h"
#include "RunMetadata.h"
#include <string>

using namespace std;

#define pageSize 4096

LsmTree::LsmTree(short bitsPerValue) {
	this->bitsPerValue = bitsPerValue;
	this->levelsCount = 0;
	this->nextFileNumber = 0;
    /*this->levels = new TieringLevel[1];
    this->levelsCount = 1;
    Level::setRunsPerLevel(runsPerLevel); */

	/* fix how this is assigned */
	this->entriesPerRun = 1000;
    this->memRun = new MemoryRun(entriesPerRun);
}

void LsmTree::insert(int value) {
	insert(value, value);
}

void LsmTree::insert(int key, int value) {

	/* make a new 'Insert' entry */
	Entry* e = new Entry(key, value, false);

	/* insert into memory run. If it's full: */
	if (! memRun->insert(e)) {
		this->flushToDisk(memRun->getEntriesSorted());
	}

}

void LsmTree::remove(int key) {

	/* delete from memory run. If that fills it: */
	if (! memRun->remove(key)) {
		this->flushToDisk(memRun->getEntriesSorted());
	}
}

/* returns NULL if not in tree */
int LsmTree::get(int key) {

	int result = memRun->get(key);

	/* if we can't find it in memory */
	if (result == NULL) {
		result = getFromDisk(key);
	}
	return result;
}

void LsmTree::flushToDisk(Entry* entries) {

	BloomFilter* bloomftr = new BloomFilter(1024, 5); // args?
	for (int i = 0; i < entriesPerRun; i++) {
		bloomftr->add(entries[i].getKey());
	}

	FencePointer* fenceptr = new FencePointer(entries[0].getValue(), entries[entriesPerRun - 1].getValue());
	string filename = getNextFilename();
	RunMetadata* runmeta = new RunMetadata(bloomftr, fenceptr, filename);

	/* TODO write to the file and give the run metadata to disk tree */
}

int LsmTree::getFromDisk(int key) {
	return -1;
}

string LsmTree::getNextFilename() {
	return "file" + std::to_string(nextFileNumber++) + ".dat";
}







