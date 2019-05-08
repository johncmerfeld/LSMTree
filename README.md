# LSMTree
Implementation of the Log-Structured Merge Tree data structure

by Efstathios Karatsiolis & John C. Merfeld

## To run
Compile the Benchmark.cpp code by linking to the other source files. Something like:
```
g++ Benchmark2.cpp LsmTree.cpp RunMetadata.cpp BloomFilter.cpp Entry.cpp MemoryRun.cpp Level.cpp FencePointer.cpp ResultSet.cpp -o lsmTree
```
To benchmark on a certain workload, run the newly-created Benchmark script with the following arguments:
```
./Benchmark [runSize] [runs per level] [bits per entry] [filename] [lines]
```
Folder inputs contains inputs files that you can test:</br>
All input files have lines inserts/updates/deletes plus lines/2 point queries. All files have 10% deletes and 10% updates and for all files about 50% of the queries exist in the tree and the other 50% does not.

mini_output 1000 inserts 500 queries </br>
medium_output 100000 inserts 50000 queries </br>
large_output 1000000 inserts 500000 queries </br>
large_output2 1000000 inserts 500000 queries </br>

In order to use these files as input to the lsmTree use the file name using the local path and the number of inserts as the lines number</br>

Where `runSize` is the number of entries in the memory run, `levelSize` is the number of runs in a level (and thus the scale factor of the "tree"), `bloomSize` is the number of bits in a bloom filter, `file` is the name of the workload file, and `lines` is the number of lines in that file. So, for example:
```
 ./Benchmark2 4000 4 5 inputs/mini_output 1500
```

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

The program will output how long the writing and reading portions took in total.
Further tests were performed in other implementations

</br>
In folder inputs you can compile the file `createInput.cp` using the command: </br>

``` 
g++ -o createInput.cpp inputs
```
You can run inputs as follows to create input files:

```
inputs [number of insers] [deletes as percentage of the total inserts] [updates as percentage of total inserts] [percentage of point queries that will exist in the tree]
```
Example run :

```
inputs 1000 10 10 80 > output
```
That command will create an file output with approximately 800 inserts, 100 updates, 100 deletes and 500 point queries out of which 400 will exist in the tree and 100 will not

## Learn more about the data model
Request access to our [report](https://docs.google.com/document/d/1aiCbnJg5yD3l76P94VKcshdjGhhWwCCbiu9C8AN-hqc/edit) and [slides](https://docs.google.com/presentation/d/1a4LdrVUd1Ng1kvCgmm9wlFmXZA3SsGBnbjlhzKDQPww/edit#slide=id.g58f6518e26_0_777) on this project.



