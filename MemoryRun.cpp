/*
 * Run.cpp
 */

#include "MemoryRun.h"
#include "ResultSet.h"
#include<limits.h>
#include<iostream>

using namespace std;

MemoryRun::MemoryRun(int size) {
    entries = new Entry[size];
    nextPos = 0;
    maxEntries = size;
}

MemoryRun::MemoryRun(Entry *entries, int size) {
    this->entries = entries;
    this->maxEntries = size;
    this->nextPos = size;

}

int MemoryRun::numElements() {
    return this->nextPos;
}

bool MemoryRun::insert(Entry e) {

    /* insert and increment */
    entries[nextPos++] = e;

    /* if full: */
    if (nextPos == maxEntries) {
        /* reset counter, tell LSMTree to flush me */
        //nextPos = 0;
        return false;
    }
    /* otherwise, just return */
    return true;
}

void MemoryRun::insertAtPos(Entry e, int pos) {
	cout << "INSERTATPOS(" << e.getKey() << ", "<< pos << ")" << endl;
	entries[pos] = e;
}

int MemoryRun::get(int key) {
    for (int i = nextPos; i >= 0; i--) {
        if (entries[i].getKey() == key) {
            /* if the entry is a delete entry, we will get the delete sentinal */
            return entries[i].getValue();
        }
    }
    return INT_MIN; /* or some null sentinal */
}

Entry MemoryRun::at(int pos) {
	// TODO throw error if out of range?
	return entries[pos];
}

ResultSet *MemoryRun::getRange(int low, int high) {

    ResultSet *results = new ResultSet(maxEntries);

    for (int i = 0; i < nextPos; i++) {
        if ((entries[i].getKey() >= low) &&
            (entries[i].getKey() <= high) &&
            (!entries[i].isRemove())) {
            results->insert(entries[i].getValue());
        }
    }

    return results;

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
    Entry *e = new Entry(key, INT_MIN, true);
    return this->insert(*e);

}

Entry *MemoryRun::getEntries() {
    return entries;
}

Entry *MemoryRun::getEntriesSorted() {

   //mergeSort(this, 0, nextPos);
    return entries;
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
MemoryRun MemoryRun::merge(MemoryRun* left, MemoryRun* right) {

	int leftSize = left->getSize();
	int rightSize = right->getSize();

	MemoryRun* merged = new MemoryRun(leftSize + rightSize);

    int i = 0;
    int j = 0;

    while (i < leftSize && j < rightSize) {
    	/* remove duplicates - if the keys are equal,
    	     just skip that entry of the 'right-side' run
    	 */
    	if (left->at(i).getKey() == right->at(j).getKey()) {
    		j++;
    	}
    	else if (left->at(i).getKey() < right->at(j).getKey()) {
        	merged->insert(left->at(i));
            i++;
        }
        else {
        	merged->insert(right->at(j));
        	j++;
        }
    }

    /* Copy the remaining elements, if any */
    while (i < leftSize) {
    	merged->insert(left->at(i));
        i++;
    }

    while (j < rightSize) {
    	merged->insert(right->at(j));
    	j++;
    }
    return *merged;

}

// https://www.geeksforgeeks.org/merge-sort/
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
MemoryRun MemoryRun::sort(MemoryRun* runToSort) {

}

void MemoryRun::reset() {
    delete entries;
    entries = new Entry[maxEntries];
    nextPos = 0;
}

void MemoryRun::print() {
	cout << "[";
	for (int i = 0; i < nextPos; i++) {
		cout << " " << entries[i].getValue();
	}
	cout << "]";
}

int MemoryRun::getSize() {
    return this->nextPos;
}
