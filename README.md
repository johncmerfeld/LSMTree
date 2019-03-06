# LSMTree
Implementation of the Log-Structured Merge Tree data structure

by Stathis Karatsiolis & John C. Merfeld

## Data model (correct me if I'm wrong)

Let's say that at its core, the LSM tree stores integers. This makes the `key` field a little redundant but more modular, of course. Each integer is stored in an `Entry` object, like this:

```
---------
| k : 1 |
+-------+
| v : 1 |
+-------+
| r : 0 |
---------
```
The `r` bit indicates whether this is a "remove" `Entry`: 0 for 'no' and 1 for 'yes.' Whenever a new `Entry` is inserted into the tree, it is added to a sorted array of Entries in main memory called a `Run`. Main memory only contains a single `Run`, and it looks like this:

```
-------------------------
| k : 1 | k : 3 | k : 6 |
+-------+-------+-------+
| v : 1 | v : 3 | v : 6 |
-------------------------
```
Or, on a macro level:

```
[r_main] = [1 3 6 7 32 96]
```
Once `r_main` reaches capacity, we write it to disk. This involves three steps:

  1. Record the highest and lowest values contained in `r_main` into a new `FencePointer` (**How does the FencePointer know where its run is in the Disk Tree?**) and hold the `FencePointer` in memory.
  2. Hash all the values of `r_main` into a new `BloomFilter` (**same question**) and hold the `BloomFilter` in memory.
  3. Insert `r_main` into the topmost `Level` of the `DiskTree`.
  
A `Level` is... well, maybe we need two implementations of `Levels`?

Because if the `DiskTree` is tierd, a `Level` is just an array of `Runs`, where an insert just appends the new `Run` to the end of the array. If the `DiskTree` is leveled, each `Level` contains one run, and an insert merges the new `Run` into the original one.

Then again, it could be better to hide that information fromt eh tree itself and just have some kind of boolean flag for leveling or tiering.

Anyway, then there's the question of a `DiskTree` and how information about `Levels` is stored. Is it just an array of pointers to the levels? Do we have some kind of other struct containing the pointer to the level, its fence pointers, and its bloom filters all together?

I decided that the answer is "yes," so I added the `Searchable` class (I'm not married to this name because it sounds like an interface, but...). In memory, the levels of the tree can be represented as a 2D array of `Searchable` objects (for a leveled tree, this degenerates into a 1D array. A `Searchable` has the pointer to the `Run` and its associated `BloomFilter` and `FencePointer`. They are ordered left-to-right within the tree levels. So in main memory for a tiered tree with T = 3, this would look like:
```
0: 0 1 _ 
1: 222 333 444
2: 555555555 666666666 _________
```
Where the number of repeated digits represents the size of the run. In this example, inserting a new run into the tree would cause a cascading merge that would fill the bottom level.

When our `Run` in memory fills up, we use its endpoints to make a new `FencePointer`, insert all of its keys into a new `BloomFilter`, and write the `Run` to disk, adding a pointer to it to the new `Searchable` object.

So main memory just contains a sorted array and a 2D array of searchables. That's what's in our cache.

