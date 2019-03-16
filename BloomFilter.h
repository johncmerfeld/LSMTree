/*
 * BloomFilter.h
 *
 */

#ifndef BLOOMFILTER_H_
#define BLOOMFILTER_H_
#include <stdint.h>

class BloomFilter {

private:
    int size;
    int numHashes;
    char *bitVector;

public:
    BloomFilter(int size, int numHashes);

    void add(int key);

    bool contains(int key);

    int getSize();

    void reset();

    static uint32_t murmurhash (const int *key, uint32_t len, uint32_t seed);

};

#endif /* BLOOMFILTER_H_ */
