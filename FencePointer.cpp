//
// Created by Stathis on 3/11/2019.
//
#include <cstdio>
#include "FencePointer.h"

FencePointer::FencePointer(int low, int high) :
        lowest(low), highest(high) {}

int FencePointer::getLowest() { return this->lowest; }

int FencePointer::getHighest() { return this->highest; }

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

bool FencePointer::isInRange(int query) {
//    printf("low is %d and high is %d\n", lowest, highest);
    return ((query >= lowest) && (query <= highest));
}

bool FencePointer::rangeOverlaps(int low, int high) {
    return ((low <= highest) && (high >= lowest));
}
