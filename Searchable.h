/*
 * Searchable.h
 *
 */

#include "FencePointer.h"
#include "BloomFilter.h"
#include "Run.h"

#ifndef SEARCHABLE_H_
#define SEARCHABLE_H_


class Searchable {

private:
	FencePointer fencePtr;
	BloomFilter bloomFtr;
	Run * run; // should this be a pointer?

public:
	Searchable(FencePointer fptr, BloomFilter bftr, Run * r);
	/* we can implement query types at this level, I think */

};


#endif /* SEARCHABLE_H_ */
