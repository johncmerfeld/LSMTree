//
// Created by Stathis on 3/13/2019.
//

#include "Level.h"
#include "RunMetadata.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

int Level::maxRuns;

Level::Level() {
    this->runsInLevel = 0;
    this->levelMetadata = new RunMetadata *[Level::maxRuns];

}

void Level::setRunsPerLevel(int runs) {
    Level::maxRuns = runs;
}


//bool Level::insert(Run run) {}


//---------- Tier Level Methods ----------

TieringLevel::TieringLevel() : Level() {}

bool TieringLevel::hasSpace() {
    string test;
    cin >> test;
    return (this->runsInLevel < Level::maxRuns);
}

MemoryRun *TieringLevel::mergeLevel(MemoryRun *memoRun) {
    //Entry * mergedEntries = new Entry[maxRuns* sizeof(Entry)];
    //load and merge
    //delete old metadata
    //delete old files
    MemoryRun * memRun = new MemoryRun(memoRun->getEntries(), memoRun->getSize());
    return memRun;
}

//bool TieringLevel::insert(Run run) {}

bool TieringLevel::add(Entry *entries, int numOfEntries) {
    Entry *data = (Entry *) malloc(sizeof(Entry) * numOfEntries);

    int filedesc = open("testfile", O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
    if (filedesc < 0)
        return 5;

    if (write(filedesc, entries, numOfEntries * sizeof(Entry)) != numOfEntries * sizeof(Entry)) {
        cout << "Error while writing" << endl;
        return 5;
    }

    runsInLevel++;
    close(filedesc);
    filedesc = open("testfile", O_RDONLY);
    if (filedesc < 0)
        return 5;

    if (read(filedesc, data, numOfEntries * sizeof(Entry)) < 0)
        write(2, "An error occurred in the read.\n", 31);

    cout << data[1].getKey() << "hoho" << endl;

    return 1;

}

//---------- Level Level Methods ----------
LevelingLevel::LevelingLevel() : Level() {}


MemoryRun *LevelingLevel::mergeLevel(MemoryRun *memRunData) {}

//bool LevelingLevel::insert(Run run) {}

bool LevelingLevel::hasSpace() {
    return ((entriesPerLevel * Level::maxRuns) > currentEntriesInLevel);
}

bool LevelingLevel::add(Entry *entries, int numOfEntries) {}
