/*
 * Level.h
 */


#ifndef LEVEL_H_
#define LEVEL_H_


#include "MemoryRun.h"
#include "DiskRun.h"


class Level {

protected:
    RunMetadata **levelMetadata;
    int runsInLevel;
    static int maxRuns;

public:
    Level();

    static void setRunsPerLevel(int runs);

//    virtual bool insert(DiskRun run) = 0;

    virtual MemoryRun * mergeLevel(MemoryRun *memoRun) = 0;

    virtual bool hasSpace() = 0;

    virtual bool add(Entry *entries, int numOfEntries) = 0;

};

class TieringLevel : public Level {
public:

    TieringLevel();

//    bool insert(DiskRun run);

    MemoryRun  *mergeLevel(MemoryRun *memoRun);

    bool hasSpace();

    bool add(Entry *entries, int numOfEntries);
};

class LevelingLevel : public Level {
    int entriesPerLevel;
    int currentEntriesInLevel;
public:
    LevelingLevel();

//    bool insert(DiskRun run);

    MemoryRun  *mergeLevel(MemoryRun *memoRun);

    bool hasSpace();

    bool add(Entry *entries, int numOfEntries);
};


#endif /* LEVEL_H_ */
