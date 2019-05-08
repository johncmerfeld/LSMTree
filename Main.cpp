//
// Created by Stathis on 3/11/2019.
//

#include "RunMetadata.h"
#include "BloomFilter.h"
#include "LsmTree.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    ResultSet *rs;
    TierLsmTree *tree = new TierLsmTree(4000, 2, 5);

    for (int i = 0; i < atoi(argv[1]); i++) {
        tree->insert(i, i);
    }

    tree->get(3999)->printer();
    tree->getRange(10, 50)->printer();
}
