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
	Run();
	void insert(Entry e);
	void insert(Entry e, int pos);
	void/*?*/ remove(Entry e);
	void/*?*/ remove(int pos);
	Entry get(int pos);

};



#endif /* RUN_H_ */
