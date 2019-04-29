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

//int main(int argc, char *argv[]) {
//    ResultSet *rs;
//    TierLsmTree *tree = new TierLsmTree(20, 2, 5);
//
//    for (int i = 0; i < atoi(argv[1]); i++) {
//        tree->insert(i%4, i);
//    }
//
//    delete tree;
//
//    cout << "----------------";
//    MemoryRun *temp = new MemoryRun(20);
//
//    for (int i = 0; i < 9; i++)
//        temp->insert(new Entry(i, i, 0));
//
//
//    for (int i = 0; i < 9; i++)
//        temp->insert(new Entry(i % 2, 2 * i, 0));
//
//
//    temp->removeDuplicates();
//
//
//    temp->printer();
//
//    int news = temp->getSize() / 2;
////    MemoryRun *temp2 = new MemoryRun(entries2, j);
//
//}
