/*
 * Run.h
 *
 */

#include "Entry.h"

#ifndef RUN_H_
#define RUN_H_

class Run {

private:
	Entry * entries;
	int nextPos;
    int size;
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
