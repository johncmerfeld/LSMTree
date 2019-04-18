/*
 * Run.cpp
 */

#include "MemoryRun.h"
#include "ResultSet.h"

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
	entries[nextPos++] = *e;

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

	ResultSet results = new ResultSet(maxEntries);

	for (int i = 0; i < nextPos; i++) {
		if ((entries[i].getKey() >= low) &&
				(entries[i].getKey() <= high)) {
			results.insert(entries[i].getValue());
		}
	}

	return results.getResults();

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

	int mindex = 0;
	int minKey = entries[mindex];

	for (int i = 1; i < maxEntries; i++) {
		if (entries[i] < minKey) {
			minKey = entries[i];
			mindex = i;
		}
	}

	Entry* resultSet[maxEntries];
	/* hey, this is an insertion sort just to have a working thing.
	   We can obviously speed it up */
	for (int i = 0; i < maxEntries; i++) {
		resultSet[i] = entries[mindex];
		/* find the next mindex */
		for (int i = 0; i < maxEntries; i++) {
			/* if it's the next largest entry: */
			if ((entries[i] < minKey) && (entries[i] > resultSet[i])) {
				minKey = entries[i];
				mindex = i;
			}
		}

	}

	return resultSet;
}
