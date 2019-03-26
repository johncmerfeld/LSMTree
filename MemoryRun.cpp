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

bool MemoryRun::insert(Entry e) {

	// insert a thing
	//


	return false;
}

/* do we need a copy constructor etc.? */

int MemoryRun::search(int key) {
	for (int i = 0; i < nextPos; i++) {
		if (entries[i].getKey() == key) {
			return entries[i].getValue();
		}
	}

	return INT_MIN; /* or some null sentinal */
}
