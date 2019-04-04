/*
 * DiskRun.h
 *
 */

#ifndef DISKRUN_H_
#define DISKRUN_H_


class DiskRun {
private:
    int fileDesc;
    BloomFilter* bloomfilter;
    FencePointer* fencePointers;
};


#endif /* DISKRUN_H_ */
