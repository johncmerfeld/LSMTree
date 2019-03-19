/*
 * Run.h
 *
 */

#ifndef RUN_H_
#define RUN_H_

#include "Entry.h"
#include "RunMetadata.h"

class Run {
protected:
    static int maxEntries;

public:
	Run(int size);
    Run();

    static void setMaxEntries(int max);
};

class MemoryRun : private Run {
private:
    Entry *entries;
    int nextPos;

    
public:
    MemoryRun(int size);

    bool insert(Entry e);
    bool insert(Entry e, int pos);

    bool remove(Entry e);
    bool remove(int pos);

    int numElements();
    Entry get(int pos);

public:
    Entry *getEntries();
    int search(int key);

};

class DiskRun : private Run {
private:
    int runId;
    RunMetadata metadata;
};

#endif /* RUN_H_ */
