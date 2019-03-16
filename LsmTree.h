//
// Created by Stathis on 3/12/2019.
//

#ifndef SIMPLE_EXAMPLE_LSMTREE_H
#define SIMPLE_EXAMPLE_LSMTREE_H

#include "Level.h"

class LsmTree {
private:
    Level * levels;
    int runsPerLevel;
    int bitsPerLevel;
    int entriesPerRun;
    int levelsCount;

public:
    LsmTree();
    LsmTree(int runsPerLevel, int bitsPerValue, int entriesPerRun);
    void insert(int key, int value);

    void remove(int key);
    void removeMany();


};


#endif //SIMPLE_EXAMPLE_LSMTREE_H
