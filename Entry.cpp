//
// Created by Stathis on 3/12/2019.
//

#include "Entry.h"
#include<limits.h>

Entry::Entry(int key, int value, bool removeBit) :
		key(key), value(value), removeBit(removeBit) {}

int Entry::getKey() { return this->key ;}

int Entry::getValue() { return this->value ;}

bool Entry::isRemove() { return this->removeBit ;}

void Entry::updateValue(int newValue) {
    this->value = newValue;
}

void Entry::updateRemove(bool newRemoveBit) {
	this->removeBit = newRemoveBit;

	// if this is a remove, set to sentinal value
	if (newRemoveBit == true) {
		this->value = INT_MIN;
	}

}
