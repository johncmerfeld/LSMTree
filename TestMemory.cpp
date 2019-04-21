#include "LsmTree.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {

	LsmTree* tree = new LsmTree(1);

	for (int i = 1; i < 100; i++) {
		tree->insert(i);
		if (i % 2 == 0) {
			tree->remove(i);
		}
	}

	for (int i = 1; i < 100; i++) {
		cout << tree->get(i) << endl;
	}



}



