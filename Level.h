/*
 * Level.h
 */

#include "Run.h"

#ifndef LEVEL_H_
#define LEVEL_H_

class Level {

protected:
    Run *runs;
    int currentRun; /* the Run being inserted into */
    int runsPerLevel;

public:
    Level();

    Level(int runsPerLevel);

    static void setRunsPerLevel(int runs);

    virtual bool insert(Run run) = 0;

    virtual bool mergeLevels(Level *level) = 0;


};

class TieringLevel : public Level {
public:
    bool insert(Run run);

    bool mergeLevels(Level *level);
};

class LevelingLevel : public Level {
public:
    bool insert(Run run);

    bool mergeLevels(Level *level);
};


#endif /* LEVEL_H_ */
