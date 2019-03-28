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

	/* insert and increment */
	entries[nextPos] = e;
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

int MemoryRun::search(int key) {
	for (int i = nextPos; i >= 0; i--) {
		if (entries[i].getKey() == key) {
			/* if the entry is a delete entry, we will get the delete sentinal */
			return entries[i].getValue();
		}
	}
	return NULL; /* or some null sentinal */
}

void MemoryRun::remove(int key) {

	for (int i = nextPos; i >= 0; i--) {
		if (entries[i].getKey() == key) {
			if (entries[i].isRemove()) {
				return;
			}
			entries[i].updateRemove(true);
			return;
		}
	}

	/* we didn't find it */
	Entry e = new Entry(key, NULL, true);
	this->insert(e);

}

Entry* MemoryRun::getEntries() {
	return entries;
}
