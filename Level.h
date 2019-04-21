/*
 * Level.h
 */

#include "MemoryRun.h"
#include "DiskRun.h"

#ifndef LEVEL_H_
#define LEVEL_H_

class Level {

protected:
    DiskRun *diskRuns;
    int runsInLevel;
    static int maxRuns;

public:
    Level();

    static void setRunsPerLevel(int runs);

//    virtual bool insert(DiskRun run) = 0;

    virtual bool mergeLevels(Level *level) = 0;

    virtual bool hasSpace() = 0;

};

class TieringLevel : public Level {
public:

    TieringLevel();

//    bool insert(DiskRun run);

    bool mergeLevels(Level *level);

    bool hasSpace();
};

class LevelingLevel : public Level {
    int entriesPerLevel;
    int currentEntriesInLevel;
public:
    LevelingLevel();

//    bool insert(DiskRun run);

    bool mergeLevels(Level *level);

    bool hasSpace();
};


#endif /* LEVEL_H_ */
