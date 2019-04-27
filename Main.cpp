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
    TierLsmTree *tree = new TierLsmTree(4000, 4, 5);

    for (int i = 1; i < 200000; i++) {
        tree->insert(i, i);
    }

    for (int i = 1; i < 20; i++) {
        tree->insert(i, i);

    }

}
