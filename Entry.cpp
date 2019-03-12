//
// Created by Stathis on 3/12/2019.
//

#include "Entry.h"

Entry::Entry(int key = 0, int value = 0) : key(key), value(value) {}

void Entry::update(int newValue) {
    this->value = newValue;
}

int Entry::getKey() { return this->key ;}

int Entry::getValue() { return this->value ;}