/*
 * ResultSet.cpp
 *
 * A dynamic array class to handle uncertain range query results
 */

#include "ResultSet.h"
#include<iostream>
#include<string>

using namespace std;

ResultSet::ResultSet(int size) {
	this->size = size;
	this->nextPos = 0;
	this->results = new int[size];
}

ResultSet::~ResultSet() {
	delete [] results;
}

int ResultSet::getSize() {
	return nextPos;
}

int* ResultSet::getResults() {

	int* nonEmptyResults = new int[nextPos];

	for (int i = 0; i < nextPos; i++) {
		nonEmptyResults[i] = results[i];
	}

	return nonEmptyResults;
}

void ResultSet::insert(int value) {
	results[nextPos++] = value;

	if (nextPos == size) {
		resize();
	}
}

/* for combining the in-memory and disk results */
int* ResultSet::combine(ResultSet rs) {

	int otherSize = rs.getSize();
	int* otherResults = rs.getResults();
	int* combinedSet = new int[size + otherSize];

	for (int i = 0; i < size; i++) {
		combinedSet[i] = results[i];
	}
	for (int i = 0; i < otherSize; i++) {
		combinedSet[i + size] = otherResults[i];
	}

	return combinedSet;

}

void ResultSet::resize() {

	nextPos = 0;
	int newSize = size * 2;
	int* newResults = new int[newSize];

	for (int i = 0; i < size; i++) {
		newResults[i] = results[i];
	}

	delete [] results;
	results = newResults;
}

void ResultSet::print() {

	string output = "[ ";

	for (int i = 0; i < nextPos; i++) {
		output += " " + to_string(results[i]);
	}

	output += "]";
	cout << output << endl;
}

