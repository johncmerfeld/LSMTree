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


    virtual MemoryRun *mergeLevel(MemoryRun *memoRun) = 0;

    virtual bool hasSpace() = 0;

    virtual bool add(MemoryRun *data, RunMetadata *meta) = 0;


    int getRuns();

protected:
    char *nameConvert(string filename);

    MemoryRun *readEntries(RunMetadata *meta, char dlete);

};

class TieringLevel : public Level {
public:

    TieringLevel();

//    bool insert(DiskRun run);

    MemoryRun *mergeLevel(MemoryRun *memoRun);

    bool hasSpace();

    bool add(MemoryRun *data, RunMetadata *meta);

};

class LevelingLevel : public Level {
    int entriesPerLevel;
    int currentEntriesInLevel;
public:
    LevelingLevel();

//    bool insert(DiskRun run);

    MemoryRun *mergeLevel(MemoryRun *memoRun);

    bool hasSpace();

    bool add(MemoryRun *data, RunMetadata *meta);
};


#endif /* LEVEL_H_ */
