//
// Created by Stathis on 3/11/2019.
//

#include "RunMetadata.h"
#include "BloomFilter.h"
#include "LsmTree.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
	ResultSet *rs;
	TierLsmTree* tree = new TierLsmTree(4,5,1);

	for (int i = 1; i < 20; i++) {
		tree->insert(i, i);

	}

//    tree->insert(i,i);
	Entry * entries = (Entry * ) new Entry[2] {Entry(5,5,5), Entry(1,1,1)};
	cout << entries[0].getKey()<<"lala"<<endl;
	cout<< sizeof(Entry);
	TieringLevel *tieringLevel = new TieringLevel();
	tieringLevel->add(entries, 2);
//	rs = tree->getRange(10, 30);
//
//	rs->print();
}
