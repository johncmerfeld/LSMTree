//
// Created by Stathis on 3/13/2019.
//

#include "Level.h"

Level::Level() {}

Level::Level(int runsPerLevel) {}

void Level::setRunsPerLevel(int runs) {}

bool Level::insert(Run run) {}

bool TieringLevel::mergeLevels(Level *level) {}

bool TieringLevel::insert(Run run) {}

bool LevelingLevel::mergeLevels(Level *level) {}

bool LevelingLevel::insert(Run run) {}