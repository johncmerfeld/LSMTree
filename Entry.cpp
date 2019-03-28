//
// Created by Stathis on 3/12/2019.
//

#include "Entry.h"

Entry::Entry(int key = 0, int value = 0, bool removeBit = false) :
		key(key), value(value), removeBit(removeBit) {}

int Entry::getKey() { return this->key ;}

int Entry::getValue() { return this->value ;}

bool Entry::isRemove() { return this->removeBit ;}

void Entry::updateValue(int newValue) {
    this->value = newValue;
}

void Entry::updateRemove(bool newRemoveBit) {
	this->removeBit = newRemoveBit;
}
