/*
 * Run.cpp
 */

#include "MemoryRun.h"

MemoryRun::MemoryRun(int size) {
	entries = new Entry[size];
	nextPos = 0;
	maxEntries = size;
}

int MemoryRun::numElements() {
	return this->nextPos;
}

bool MemoryRun::insert(Entry* e) {

	/* insert and increment */
	entries[nextPos] = *e;
	nextPos++;

	/* if full: */
	if (nextPos == maxEntries) {
		/* reset counter, tell LSMTree to flush me */
		nextPos = 0;
		return false;
	}
	/* otherwise, just return */
	return true;
}

int MemoryRun::get(int key) {
	for (int i = nextPos; i >= 0; i--) {
		if (entries[i].getKey() == key) {
			/* if the entry is a delete entry, we will get the delete sentinal */
			return entries[i].getValue();
		}
	}
	return NULL; /* or some null sentinal */
}

int* MemoryRun::getRange(int low, int high) {

	/* create an array the size of memrun?
	 * fill it with everything that matches
	 *
	 * search each disk level. How to do this dynamically?
	 */
}

bool MemoryRun::remove(int key) {

	for (int i = nextPos; i >= 0; i--) {
		if (entries[i].getKey() == key) {
			if (entries[i].isRemove()) {
				return true;
			}
			entries[i].updateRemove(true);
			return true;
		}
	}

	/* we didn't find it */
	Entry* e = new Entry(key, NULL, true);
	return this->insert(e);

}

Entry* MemoryRun::getEntries() {
	return entries;
}

Entry* MemoryRun::getEntriesSorted() {

	Entry* resultSet[maxEntries];



	// FILL THIS IN
	return NULL;
}
