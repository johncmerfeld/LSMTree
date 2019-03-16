/*
 * Run.cpp
 *
 */

#include "Run.h"

MemoryRun::MemoryRun(int size) {
	entries = new Entry[size];
	nextPos = 0;
	maxEntries = size;
	/* initialize metadata? */

}

int MemoryRun::numElements() {
	return this->nextPos;
}

bool MemoryRun::insert(Entry e) {
	/* so, we can either:
	 * 1. insert first and return false if our insertion makes the array full...
	 * 2. check the position first and return false if we CANNOT insert
	 *
	 * I like option 1 because main memory can just keep saying:
	 * 		if (! run.insert(entry) {
	 * 		    writeRunToDisk()
	 * 		}
	 * Thus main memory never has to check the contents of the run
	 * and insertions are always successful
	 */
	return false;
}

/* do we need a copy constructor etc.? */


int Run::maxEntries;

void Run::setMaxEntries(int max) {Run::maxEntries = max;}