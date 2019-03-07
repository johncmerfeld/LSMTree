/*
 * Level.h
 */

#include "Run.h"

#ifndef LEVEL_H_
#define LEVEL_H_

class Level {

private:
	Run * runs;
	int currentRun; /* the Run being inserted into */
	bool isTiered; // maybe?
	Run merge(Run r1, Run r2); // maybe

public:
	Level();
	void insert(Run run);

};



#endif /* LEVEL_H_ */
