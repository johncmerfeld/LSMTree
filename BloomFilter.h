/*
 * bloomFilter.h
 *
 */

using bitVector = bool*[];

#ifndef BLOOMFILTER_H_
#define BLOOMFILTER_H_

class BloomFilter {

private:

	int size;
	int numHashes;
	bitVector bits;
	// however we do hashing

public:

	BloomFilter(int s, int nh);
	int getSize();
	void put(int key);
	bool contains(int key);

};

#endif /* BLOOMFILTER_H_ */
