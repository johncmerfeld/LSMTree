/*
 * Level.h
 */


#ifndef LEVEL_H_
#define LEVEL_H_


#include "MemoryRun.h"


class Level {

protected:
    RunMetadata **levelMetadata;
    int runsInLevel;
    static int maxRuns;

    char *nameConvert(string filename);

public:
    Level();

    static void setRunsPerLevel(int runs);

    virtual MemoryRun *mergeLevel(MemoryRun *memoRun) = 0;

    virtual bool hasSpace() = 0;

    virtual bool add(MemoryRun *data, RunMetadata *meta) = 0;

    MemoryRun *readEntries(RunMetadata *meta, char dlete, int offset);

    MemoryRun *readEntries(RunMetadata *meta, char dlete);

    int getRuns();

    RunMetadata **getMetadata();

    void printMeta();

    ~Level();
};

class TieringLevel : public Level {
public:

    TieringLevel();

    MemoryRun *mergeLevel(MemoryRun *memoRun);

    bool hasSpace();

    bool add(MemoryRun *data, RunMetadata *meta);

};

class LevelingLevel : public Level {
    int entriesPerLevel;
    int currentEntriesInLevel;

public:
    LevelingLevel();

    MemoryRun *mergeLevel(MemoryRun *memoRun);

    bool hasSpace();

    bool add(MemoryRun *data, RunMetadata *meta);
};


#endif /* LEVEL_H_ */
