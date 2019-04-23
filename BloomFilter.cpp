/*
 * BloomFilter.cpp
 */

#include "BloomFilter.h"
#include <iostream>
#include <bitset>
#include <cstring>

using namespace std;

BloomFilter::BloomFilter(int size, int numHashes) {
    this->size = size;
    this->numHashes = numHashes;
    this->bitVector = new char[size];
}

bool BloomFilter::contains(int key) {
    unsigned int bytePos, bitPos, hashValue;
    char current, newByte;

    for (int i = 0; i < this->numHashes; i++) {

        //Get Hash value, byte position and bit position
        hashValue = this->murmurhash(&key, sizeof(key), i);   //Add hash value, probably will use murmur hash
        bytePos = (hashValue / 8) % this->size;
        bitPos = hashValue % 8;

        //Get current byte
        current = this->bitVector[bytePos];

        //Create byte with 1 in specific bit position
        newByte = 1 << bitPos;

        //Combine new byte with with old byte value
        newByte = newByte | current;

        //If current value and newByte are different, this means there was a new bit added which did not exist,
        //meaning the key does not exist in the bloomfilter
        if ((newByte ^ current) != 0)
            return false;
    }
    return true;
}

void BloomFilter::add(int key) {
    unsigned int bytePos, bitPos, hashValue;

    for (int i = 0; i < this->numHashes; i++) {

        //Get Hash value, byte position and bit position
        hashValue = this->murmurhash(&key, sizeof(key), i);   //Add hash value, probably will use murmur hash
        bytePos = (hashValue / 8) % this->size;
        bitPos = hashValue % 8;

        //Combine current byte with the byte created from hashing the key value
        this->bitVector[bytePos] |= 1 << bitPos;
    }
    return;
}

void BloomFilter::reset() {
    memset(this->bitVector, this->size, 0);
}

uint32_t BloomFilter::murmurhash(const int *key, uint32_t len, uint32_t seed) {
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t r2 = 13;
    uint32_t m = 5;
    uint32_t n = 0xe6546b64;
    uint32_t h = 0;
    uint32_t k = 0;
    uint8_t *d = (uint8_t *) key; // 32 bit extract from `key'
    const uint32_t *chunks = nullptr;
    const uint8_t *tail = nullptr; // tail - last 8 bytes
    int i = 0;
    int l = len / 4; // chunk length

    h = seed;

    chunks = (const uint32_t *) (d + l * 4); // body
    tail = (const uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

    // for each 4 byte chunk of `key'
    for (i = -l; i != 0; ++i) {
        // next 4 byte chunk of `key'
        k = chunks[i];

        // encode next 4 byte chunk of `key'
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        // append to hash
        h ^= k;
        h = (h << r2) | (h >> (32 - r2));
        h = h * m + n;
    }

    k = 0;

    // remainder
    switch (len & 3) { // `len % 4'
        case 3:
            k ^= (tail[2] << 16);
            break;
        case 2:
            k ^= (tail[1] << 8);
            break;
        case 1:
            k ^= tail[0];
            k *= c1;
            k = (k << r1) | (k >> (32 - r1));
            k *= c2;
            h ^= k;
    }

    h ^= len;

    h ^= (h >> 16);
    h *= 0x85ebca6b;
    h ^= (h >> 13);
    h *= 0xc2b2ae35;
    h ^= (h >> 16);

    return h;
}


int BloomFilter::getSize() { return this->size; }
