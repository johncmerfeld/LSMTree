/*
 * Level.h
 */

#include "MemoryRun.h"
#include "DiskRun.h"

#ifndef LEVEL_H_
#define LEVEL_H_

class Level {

protected:
    DiskRun* diskRuns;
    int runsInLevel;
    static int maxRuns;

public:
    Level();

    Level(int runsInLevel = 0);

    static void setRunsPerLevel(int runs);

    virtual bool insert(DiskRun run) = 0;

    virtual bool mergeLevels(Level *level) = 0;


};

class TieringLevel : public Level {
public:
    bool insert(DiskRun run);

    bool mergeLevels(Level *level);
};

class LevelingLevel : public Level {
public:
    bool insert(DiskRun run);

    bool mergeLevels(Level *level);
};


#endif /* LEVEL_H_ */
