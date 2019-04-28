//
// Created by Stathis on 3/11/2019.
//

#include "FencePointer.h"

FencePointer::FencePointer(int low, int high) :
						   lowest(low), highest(high) {}

int FencePointer::getLowest() {return this->lowest ;}

int FencePointer::getHighest() {return this->highest ;}

void FencePointer::setLowest(int newLow) {
	this->lowest = newLow;
}

void FencePointer::setHighest(int newHigh) {
	this->highest = newHigh;
}

bool FencePointer::isInRange(int query) {
	return ((query >= lowest) && (query <= highest));
}

bool FencePointer::rangeOverlaps(int low, int high) {
	return ((low <= highest) && (high >= lowest));
}
