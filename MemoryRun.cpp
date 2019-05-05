/*
 * MemoryRun.cpp
 */

#include "MemoryRun.h"
#include "ResultSet.h"
#include <limits.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstring>

using namespace std;

MemoryRun::MemoryRun(int size) {
    entries = new Entry[size];
//    memset(entries, size*sizeof(Entry), 0);
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
    entries[nextPos].setEntry(&e);

    nextPos += 1;
    /* if full: */
    return nextPos != maxEntries;

}

bool MemoryRun::insert(Entry *e) {
    memcpy(&entries[nextPos], e, sizeof(Entry));
    nextPos++;
    return nextPos != maxEntries;
}

void MemoryRun::insertAtPos(Entry e, int pos) {
    entries[pos].setEntry(&e);
}

Entry *MemoryRun::get(int key) {
    for (int i = nextPos; i >= 0; i--) {
        if (entries[i].getKey() == key) {
            /* if the entry is a delete entry, we will get the delete sentinal */
            return &entries[i];
        }
    }
    return NULL;
}

Entry *MemoryRun::getBinarySearch(int key) {
	/* TODO change this! */
    for (int i = nextPos; i >= 0; i--) {
        if (entries[i].getKey() == key) {
            /* if the entry is a delete entry, we will get the delete sentinal */
            return &entries[i];
        }
    }
    return NULL;
}

Entry MemoryRun::at(int pos) {
    // TODO throw error if out of range?
    return entries[pos];
}

MemoryRun *MemoryRun::getRange(int low, int high) {

    MemoryRun *results = new MemoryRun(maxEntries);

    for (int i = 0; i < nextPos; i++) {
        if ((entries[i].getKey() >= low) &&
            (entries[i].getKey() <= high)) {
            results->insert(entries[i]);
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
    Entry *e = new Entry(key, 0, true);
    return this->insert(*e);

}

Entry *MemoryRun::getEntries() {
    return entries;
}

bool MemoryRun::isEmpty() {
    return (nextPos == 0);
}

// Merges two memoryRuns
// This should always be run such that the older run is
// the first argument and the newer one is second
MemoryRun *MemoryRun::merge(MemoryRun *older, MemoryRun *newer) {

    int olderSize = older->getSize();
    int newerSize = newer->getSize();

    MemoryRun *merged = new MemoryRun(olderSize + newerSize);

    int i = 0;
    int j = 0;

    while (i < olderSize && j < newerSize) {
        /* REMOVING DUPLICATES
         *
         * The right-side run is newer. Therefore, if the keys are the same,
         * we always skip the left-side entry, because the newer instruction,
         * whether it be an insert or a delete, should be what propagates down
         * the tree.
         */
        if (older->at(i).getKey() == newer->at(j).getKey()) {
            //cout << "dupe!" << endl;
            i++;
        }
        else if (older->at(i).getKey() < newer->at(j).getKey()) {
            merged->insert(older->at(i));
            i++;
        }
        else {
            merged->insert(newer->at(j));
            j++;
        }
    }

    /* Copy the remaining elements, if any */
    while (i < olderSize) {
        merged->insert(older->at(i));
        i++;
    }

    while (j < newerSize) {
        merged->insert(newer->at(j));
        j++;
    }
    return merged;
}

void MemoryRun::removeDuplicates() {
    this->sort();
    //------------------------Keep only latest version in memory run after sorting ---------------------
    Entry *entries = this->getEntries();
    Entry *entries2 = new Entry[this->getSize()];
    int j = 0;
    for (int i = 0; i < this->getSize() - 1; i++) {
        if (entries[i].getKey() != entries[i + 1].getKey()) {
            memcpy(&entries2[j], &entries[i], sizeof(Entry));
            j++;
        }
    }
    memcpy(&entries2[j], &entries[this->getSize() - 1], sizeof(Entry));
    j++;

    memcpy(this->getEntries(), entries2, j * sizeof(Entry));
    this->setSize(j);
    //------------------------------------------------------------
}

// https://stackoverflow.com/questions/1557894/non-recursive-merge-sort
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void MemoryRun::sort() {

    MemoryRun *temp = new MemoryRun(nextPos);

    int size = nextPos;

    int rght, wid, rend;
    int i, j, m, t;

    for (int k = 1; k < size; k *= 2) {
        for (int left = 0; left + k < size; left += k * 2) {
            rght = left + k;
            rend = rght + k;
            if (rend > size) {
                rend = size;
            }
            m = left;
            i = left;
            j = rght;
            while (i < rght && j < rend) {
                if (entries[i].getKey() <= entries[j].getKey()) {
                    temp->insertAtPos(entries[i], m);
                    i++;
                }
                else {
                    temp->insertAtPos(entries[j], m);
                    j++;
                }
                m++;
            }
            while (i < rght) {
                temp->insertAtPos(entries[i], m);
                i++;
                m++;
            }
            while (j < rend) {
                temp->insertAtPos(entries[j], m);
                j++;
                m++;
            }

            for (m = left; m < rend; m++) {
                entries[m] = temp->at(m);
            }
        }
    }
    delete temp;
}

void MemoryRun::reset() {
//    delete entries;
//    entries = new Entry[maxEntries];
    nextPos = 0;
}

void MemoryRun::print() {
    cout << "[";
    for (int i = 0; i < nextPos; i++) {
        cout << " " << entries[i].getValue();
    }
    cout << "]";
}

void MemoryRun::removeDeletes() {
    Entry *cleaned = new Entry[maxEntries];

    int cleanedNext = 0;

    for (int i = 0; i < nextPos; i++) {
        if (!entries[i].isRemove()) {
            cleaned[cleanedNext] = entries[i];
            cleanedNext++;
        }
    }
    delete[] entries;
    entries = cleaned;
}

int MemoryRun::getSize() {
    return this->nextPos;
}


void MemoryRun::printer() {
    printf("Memrun contains %d entries : ", nextPos);
    for (int i = 0; i < nextPos; i++) {
        cout << entries[i].getKey();
        cout << ":";
        cout << entries[i].getValue();
        cout << "|";
    }
    cout << endl;
}

void MemoryRun::setSize(int size) {
    this->nextPos = size;
}

MemoryRun::~MemoryRun() {
//    delete[] this->entries;
}
