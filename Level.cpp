//
// Created by Stathis on 3/13/2019.
//

#include "Level.h"
#include "RunMetadata.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "MemoryRun.h"

/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

int Level::maxRuns;

//-------------------- Constructors --------------------
Level::Level() {
    this->runsInLevel = 0;
    this->levelMetadata = new RunMetadata *[Level::maxRuns];
    for (int i = 0; i < maxRuns; i++) {
        levelMetadata[i] = nullptr;
    }
}

Level::~Level() {
//    for (int i = 0; i < runsInLevel; i++)
//        delete levelMetadata[i];
//    delete[] levelMetadata;
}

//-------------------- Common methods --------------------
void Level::setRunsPerLevel(int runs) {
    Level::maxRuns = runs;
}

int Level::getRuns() {
    return this->runsInLevel;
}

char *Level::nameConvert(string filename) {

    char *fname = new char[filename.length() + 1];
    memcpy(fname, filename.c_str(), filename.length());
    fname[filename.length()] = '\0';
    return fname;
}

RunMetadata **Level::getMetadata() {
    return levelMetadata;
}


//---------- Reads whole run for merging and deletes file if flag is specified ----------
MemoryRun *Level::readEntries(RunMetadata *meta, char dlete) {

    int filedesc, numOfEntries = meta->getSize();
    char *fname = nameConvert(meta->getFilename());
    Entry *data = new Entry[meta->getSize()];


    //printf("just read %d\n", meta->getSize());
    //---------- Read from filedescriptor ----------
    filedesc = open(fname, O_RDONLY);
    if (filedesc < 0)
        write(2, "An error occurred in the read.\n", 31);

    if (read(filedesc, data, numOfEntries * sizeof(Entry)) < 0)
        write(2, "An error occurred in the read.\n", 31);


    close(filedesc);
    if (dlete)
        remove(fname);

    delete[] fname;
    return new MemoryRun(data, numOfEntries);;
}


void Level::printMeta() {
    for (int i = 0; i < this->runsInLevel; i++) {
        printf("meta has %d\n", levelMetadata[i]->getSize());
    }
}


//-------------------- Tier Level Methods --------------------


TieringLevel::TieringLevel() : Level() {}


bool TieringLevel::hasSpace() {
    return (runsInLevel < (Level::maxRuns - 1));
}


MemoryRun *TieringLevel::mergeLevel(MemoryRun *memoRun) {
    MemoryRun *older, *newer, *merged;


    if (runsInLevel > 0)
        older = readEntries(levelMetadata[0], 1);
    else
        return memoRun;


    for (int i = 1; i < runsInLevel; i++) {
        newer = readEntries(levelMetadata[i], 1);
        merged = MemoryRun::merge(older, newer);

        delete older;
        delete newer;

        older = merged;
        delete levelMetadata[i];
    }

    merged = MemoryRun::merge(older, memoRun);
    delete older;
    this->runsInLevel = 0;
    return merged;
}


bool TieringLevel::add(MemoryRun *mdata, RunMetadata *meta) {

    char *fname = nameConvert(meta->getFilename());
    int filedesc = open(fname, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
    if (filedesc < 0)
        return 2;




    int size = mdata->getSize() * sizeof(Entry);
    Entry *entries = mdata->getEntries();

    if (write(filedesc, entries, size) < 0) {
        cout << "Error while writing" << endl;
        return 2;
    }

    levelMetadata[runsInLevel] = meta;
    runsInLevel += 1;
    close(filedesc);

    delete[] fname;
    return 1;

}



//-------------------- Leveling Level Methods --------------------

MemoryRun *LevelingLevel::mergeLevel(MemoryRun *memRunData) {}


bool LevelingLevel::hasSpace() {
    return ((entriesPerLevel * Level::maxRuns) > currentEntriesInLevel);
}

bool LevelingLevel::add(MemoryRun *data, RunMetadata *meta) {
    this->add(data, meta);
    this->levelMetadata[this->runsInLevel] = meta;
}
