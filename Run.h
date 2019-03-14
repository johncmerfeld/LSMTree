/*
 * Run.h
 *
 */

#include "Entry.h"
#include "RunMetadata.h"

#ifndef RUN_H_
#define RUN_H_

class Run {

private:
	Entry * entries;
    static int maxEntries;
    int nextPos;
    RunMetadata metadata;

public:
	Run(int size);
	int numElements();
	bool insert(Entry e);
	bool insert(Entry e, int pos);
	bool remove(Entry e);
	bool remove(int pos);
	Entry get(int pos);

};



#endif /* RUN_H_ */
