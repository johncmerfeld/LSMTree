#include "RunMetadata.h"
#include "BloomFilter.h"
#include "LsmTree.h"
#include "getTimeInMicroseconds.h"
#include <iostream>
#include <unistd.h>
#include <random>

using namespace std;

int main(int argc, char *argv[]) {

	if (argc < 7) {
		cout << "Insufficient arguments." << endl;
		cout << "Usage: './Benchmark runSize levelSize bloomSize writes deletes reads'" << endl;
		return 1;
	}

	int runSize = stoi(argv[1]);
	int levelSize = stoi(argv[2]);
	int bloomSize = stoi(argv[3]);

	int writes = stoi(argv[4]);
	int deletes = stoi(argv[5]);
	int reads = stoi(argv[6]);

	// only used once to initialise (seed) engine
	std::random_device rd;

	// random-number engine used (Mersenne-Twister in this case)
	std::mt19937 rng(rd());

	// guaranteed unbiased
	std::uniform_int_distribution<int> uni(-1000000000,1000000000);

    //ResultSet *rs;
    TierLsmTree *tree = new TierLsmTree(runSize, levelSize, bloomSize);

    /* load random numbers */
    int n_rands = 1000000;
    int r [n_rands];
    for (int i = 0; i < n_rands; i++) {
    	r[i] = uni(rng);
    }



    uint64 start = GetTimeMs64();
    for (int i = 1; i < writes; i++) {
    	tree->insert(r[i], r[i]);
    }
    uint64 end = GetTimeMs64();
    cout << end - start << endl;
/*
    for (int i = 1; i < deletes; i++) {
    	r = uni(rng);
        tree->insert(i, i, 0);
    }
/*
    int result;
    for (int i = 1; i < reads; i++) {
    	r = uni(rng);
    	result = tree->get(r);
    	cout << result << endl;
    } */

}




