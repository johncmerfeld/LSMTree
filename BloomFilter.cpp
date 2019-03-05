/*
 * BloomFilter.cpp
 */

#include "BloomFilter.h"

BloomFilter::BloomFilter(int size = 1024, int numHashes = 5) {
    this->size = size;
    this->numHashes = numHashes;
    this->bitVector = new char[size];
}

bool BloomFilter::contains(int key){
        unsigned int bytePos, bitPos, hashValue;
        char current, newByte;

        for (int i=0; i<this->numHashes; i++){

            //Get Hash value, byte position and bit position
            hashValue = 0 ;   //Add hash value, probably will use murmur hash
            bytePos = (hashValue / 8) % this->size;
            bitPos = hashValue % 8;

            //Get current byte
            current = this->bitVector[bytePos];

            //Create byte with 1 in specific bit position
            newByte = 1<< bitPos;

            //Combine new byte with with old byte value
            newByte = newByte | current;

            //If current value and newByte are different, this means there was a new bit added which did not exist,
            //meaning the key does not exist in the bloomfilter
            if ((newByte ^ current) !=0)
                return false;
        }
        return true;
}
