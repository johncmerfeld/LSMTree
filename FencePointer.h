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
	FencePointer(int low = 0, int high = 0);
	int getLowest();
	int getHighest();
	void setLowest(int newLow);
	void setHighest(int newHigh);
	void setPointers(int low, int high);
	int isInRange(int query);
	bool rangeOverlaps(int low, int high);

};



#endif /* FENCEPOINTER_H_ */
