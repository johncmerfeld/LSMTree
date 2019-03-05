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

Anyway, then there's the question of a `DiskTree` and how information about `Levels` is stored. Is it just an array of pointers to the levels? Do we have some kind of other struct containing the pointer to the level, its fence pointer, and its bloom filter all together?


