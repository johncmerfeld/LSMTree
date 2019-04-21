#include "LsmTree.h"
#include "ResultSet.h"
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

	ResultSet rs = tree->getRange(10, 30);

	rs.print();


}



