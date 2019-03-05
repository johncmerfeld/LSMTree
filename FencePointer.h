/*
 * FencePointer.h
 *
 */

#ifndef FENCEPOINTER_H_
#define FENCEPOINTER_H_

class FencePointer {

private:
	int lowest; // should these be ints or something more general?
	int highest;

public:
	FencePointer(int low, int high);

};



#endif /* FENCEPOINTER_H_ */
