//
// Created by Stathis on 3/12/2019.
//

#include "Entry.h"
#include <limits.h>
#include <cstdio>
#include <cstdlib>

Entry::Entry(){}

Entry::Entry(int key, int value, bool removeBit) :
        key(key), value(value), removeBit(removeBit) {}


Entry::Entry(int key, int value) : Entry(key, value, 0) {}

int Entry::getKey() { return this->key; }

int Entry::getValue() { return this->value; }

bool Entry::isRemove() { return this->removeBit; }

void Entry::updateValue(int newValue) {
    this->value = newValue;
}


void Entry::updateRemove(bool newRemoveBit) {
    this->removeBit = newRemoveBit;

    // if this is a remove, set to sentinal value
    if (!newRemoveBit) return;
    this->value = INT_MIN;

}

void Entry::setEntry(Entry *e) {
    key = e->getKey();
    value = e->getValue();
    removeBit = e->isRemove();
}

void Entry::printer() {
    printf("Entry : [%d, %d, %d ]\n", key, value, removeBit);
}