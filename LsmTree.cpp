//
// Created by Stathis on 3/12/2019.
//

#include "LsmTree.h"

#include "MemoryRun.h"

#define pageSize 4096

LsmTree::LsmTree():LsmTree(2, 4, 4096/ sizeof(Entry)) {

}



LsmTree::LsmTree(int runsPerLevel, int bitsPerValue, int entriesPerRun) {
    this->levels = new TieringLevel[1];
    this->levelsCount = 1;
    Level::setRunsPerLevel(runsPerLevel);
    Run::setMaxEntries(entriesPerRun);
}













