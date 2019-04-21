//
// Created by Stathis on 3/13/2019.
//

#include "Level.h"

Level::Level() {
    this->runsInLevel = 0;
}

void Level::setRunsPerLevel(int runs) {}

//bool Level::insert(Run run) {}


//---------- Tier Level Methods ----------

TieringLevel::TieringLevel() : Level() {
}

bool TieringLevel::hasSpace() {
    return (this->runsInLevel == Level::maxRuns);
}

//bool TieringLevel::insert(Run run) {}


//---------- Level Level Methods ----------
LevelingLevel::LevelingLevel() : Level() {}


bool LevelingLevel::mergeLevels(Level *level) {}

//bool LevelingLevel::insert(Run run) {}

bool LevelingLevel::hasSpace() {
    return ((entriesPerLevel * Level::maxRuns) > currentEntriesInLevel);
}