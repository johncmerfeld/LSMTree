# LSMTree
Implementation of the Log-Structured Merge Tree data structure

by Efstathios Karatsiolis & John C. Merfeld

## To run
Compile the Benchmark.cpp code by linking to the other source files. Something like:
```
g++ -std=c++11 -stdlib=libc++ Benchmark.cpp LsmTree.cpp RunMetadata.cpp BloomFilter.cpp Entry.cpp MemoryRun.cpp Level.cpp FencePointer.cpp ResultSet.cpp -o Benchmark
```

To benchmark on a certain workload, run the newly-created Benchmark script with the following arguments:
```
./Benchmark runSize levelSize bloomSize file lines
```
Where `runSize` is the number of entries in the memory run, `levelSize` is the number of runs in a level (and thus the scale factor of the "tree"), `bloomSize` is the number of bits in a bloom filter, `file` is the name of the workload file, and `lines` is the number of lines in that file.

The workload file should be a CSV of this format:
```
i,5,5
i,4,4
i,8,8
u,5,10
u,5,11
d,4
g,5
g,8
r,3,6
```
where `i,k,v` inserts key `k` and value `v`; `u,k,v` updates key `k` with new value `v` (same as inserting but it is useful for evaulation to know what is an update); `d,k` tries to delete key `k` from the tree; `g,k` tries to read key `k` from the tree, `r,l,h` gets all values in the range from low `l` to high `h`.

The program will output how long the writing and reading portions took.

## Learn more about the data model
Request access to our [report](https://docs.google.com/document/d/1aiCbnJg5yD3l76P94VKcshdjGhhWwCCbiu9C8AN-hqc/edit) and [slides](https://docs.google.com/presentation/d/1a4LdrVUd1Ng1kvCgmm9wlFmXZA3SsGBnbjlhzKDQPww/edit#slide=id.g58f6518e26_0_777) on this project.



