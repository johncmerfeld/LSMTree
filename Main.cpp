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
    TierLsmTree *tree = new TierLsmTree(20, 2, 5);

    for (int i = 0; i < atoi(argv[1]); i++) {
        tree->insert(i, i);
    }

    delete tree;

    cout << "----------------";
    MemoryRun *temp = new MemoryRun(20);

    for (int i = 0; i < 9; i++)
        temp->insert(new Entry(i, i, 0));


    for (int i = 0; i < 9; i++)
        temp->insert(new Entry(i%2, 2 * i, 0));


    temp->sort();

    //------------------------Keep only latest version in memory run after sorting ---------------------
    Entry *entries = temp->getEntries();
    Entry *entries2 = new Entry[temp->getSize()];
    int j = 0;
    for (int i = 0; i < temp->getSize()-1; i++) {
        if (entries[i].getKey() != entries[i + 1].getKey()) {
            memcpy(&entries2[j], &entries[i], sizeof(Entry));
            j++;
        }
    }
    memcpy(&entries2[j], &entries[temp->getSize()-1], sizeof(Entry));
    j++;

    memcpy(temp->getEntries(), entries2, j * sizeof(Entry));
    temp->setSize(j);
    //------------------------------------------------------------

    temp->printer();

    int news = temp->getSize() / 2;
    MemoryRun *temp2 = new MemoryRun(entries2, j);
    
}
