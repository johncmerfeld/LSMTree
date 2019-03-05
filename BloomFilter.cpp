/*
 * BloomFilter.cpp
 */

#include "BloomFilter.h"

BloomFilter::BloomFilter(int s, int nh) {
	size = s;
	numHashes = nh;

	bits = new bitVector[s];
}


