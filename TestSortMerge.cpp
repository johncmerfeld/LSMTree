/*
 * TestSortMerge.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: johncmerfeld
 */

#include<iostream>
#include "MemoryRun.h"
#include "Entry.h"

using namespace std;

int main() {


	MemoryRun* memRun1 = new MemoryRun(10000);
	for (int i = 100; i > 0; i-= 7) {
		Entry* e = new Entry(i, i);
		memRun1->insert(*e);
	}

	MemoryRun* memRun2 = new MemoryRun(10000);
	for (int i = 0; i < 100; i += 5) {
		Entry* e = new Entry(i, i);
		memRun2->insert(*e);
	}

	memRun1->sort();
	memRun2->sort();

	MemoryRun memRun3 = MemoryRun::merge(memRun1, memRun2);

	memRun3.sort();

	memRun3.print();
	cout << endl;

	//memRun1->print();

	/*
	for (int i = 0; i < memRun4.getSize(); i++) {
		cout << memRun4.at(i).getKey() << " ";
	} */

	return 0;
}


