//
// Created by Stathis on 3/11/2019.
//

#include "RunMetadata.h"
#include "BloomFilter.h"
#include "LsmTree.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    ResultSet *rs;
    TierLsmTree *tree = new TierLsmTree(20, 2, 5);

    for (int i = 0; i < atoi(argv[1]); i++) {
        tree->insert(i, i);
    }

    for (int i = 0; i < atoi(argv[1]); i++) {
        tree->insert(i, i);
    }


}
