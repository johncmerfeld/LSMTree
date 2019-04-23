/*
 * Run.cpp
 */

#include "MemoryRun.h"
#include "ResultSet.h"
#include<limits.h>

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

bool MemoryRun::insert(Entry* e) {

    /* insert and increment */
    entries[nextPos++] = *e;

    /* if full: */
    if (nextPos == maxEntries) {
        /* reset counter, tell LSMTree to flush me */
        reset();
        return false;
    }
    /* otherwise, just return */
    return true;
}

void MemoryRun::insertAtPos(Entry* e, int pos) {
	entries[pos] = *e;
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
	// TODO throw error of out of range?
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
    return this->insert(e);

}

Entry *MemoryRun::getEntries() {
    return entries;
}

Entry *MemoryRun::getEntriesSorted() {

    return mergeSort(*this, 0, nextPos).getEntries();
}

/* creates a full memoryRun from two others */
MemoryRun MemoryRun::combine(MemoryRun runToCombine) {

	int mySize = this->getSize();
	int otherSize = runToCombine.getSize();

	MemoryRun combined = new MemoryRun(mySize + otherSize);

	for (int i = 0; i < mySize; i++) {
		combined.insert(&entries[i]);
	}

	for (int i = 0; i < otherSize; i++) {
		combined.insert(&runToCombine.at(i));
	}

	return combined;

}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
MemoryRun MemoryRun::merge(MemoryRun runToMerge, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* create temp arrays */
    MemoryRun L = new MemoryRun(n1);
    MemoryRun R = new MemoryRun(n2);

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = runToMerge.at(left + i);
    for (j = 0; j < n2; j++)
        R[j] = runToMerge(mid + 1 + j);

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L.at(i) <= R.at(j))
        {
        	runToMerge.insertAtPos(&L.at(i), k);
            i++;
        }
        else
        {
        	runToMerge.insertAtPos(&R.at(j), k);
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
    	runToMerge.insertAtPos(&L.at(i), k);
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
    	runToMerge.insertAtPos(&R.at(j), k);
        j++;
        k++;
    }

    return runToMerge;

}

// https://www.geeksforgeeks.org/merge-sort/
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
MemoryRun MemoryRun::mergeSort(MemoryRun runToSort, int left, int right)
{
    if (left < right)
    {
        int mid = right - left / 2;

        // Sort first and second halves
        runToSort = mergeSort(runToSort, left, mid);
        runToSort = mergeSort(runToSort, mid + 1, right);

        runToSort = merge(runToSort, left, mid, right);
    }
    return runToSort;
}

void MemoryRun::reset() {
    delete entries;
    entries = new Entry[maxEntries];
    nextPos = 0;

}

int MemoryRun::getSize() {
    return this->nextPos;
}
