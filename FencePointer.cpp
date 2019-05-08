//
// Created by Stathis on 3/11/2019.
//
#include <cstdio>
#include "FencePointer.h"
#include <iostream>

using namespace std;


//-------------------- Constructor --------------------
FencePointer::FencePointer(int low, int high) :
        lowest(low), highest(high) {}


//-------------------- Getters --------------------
int FencePointer::getLowest() { return this->lowest; }

int FencePointer::getHighest() { return this->highest; }


//-------------------- Setters --------------------
void FencePointer::setLowest(int newLow) {
    this->lowest = newLow;
}

void FencePointer::setHighest(int newHigh) {
    this->highest = newHigh;
}

void FencePointer::setPointers(int low, int high) {
    this->lowest = low;
    this->highest = high;
}

//-------------------- Range checks --------------------
int FencePointer::isInRange(int query) {
	if ((query >= lowest) && (query <= highest))
		return 0;
	else if (query > highest)
		return 1;
	else
		return -1;
}

int FencePointer::rangeOverlaps(int low, int high) {
    return ((low <= highest) && (high >= lowest));

}
