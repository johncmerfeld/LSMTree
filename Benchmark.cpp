#include "RunMetadata.h"
#include "BloomFilter.h"
#include "LsmTree.h"
#include <iostream>
#include <unistd.h>
#include <random>
#include "GetTimeMs64.h"

using namespace std;


/* TODO have this use averages, or put it in the R */
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
	std::uniform_int_distribution<int> uni(-1000,1000);

    //ResultSet *rs;
    TierLsmTree *tree = new TierLsmTree(runSize, levelSize, bloomSize);

    /* load random numbers */
    int n_rands = 1000000;
    int r1 [n_rands];
    int r2 [n_rands];
    for (int i = 0; i < n_rands; i++) {
    	r1[i] = uni(rng);
    	r2[i] = uni(rng);
    }



    uint64 start = GetTimeMs64();
    for (int i = 0; i < writes; i++) {
    	tree->insert(r1[i], r1[i]);
    }

/*
    Entry* e;
    for (int i = 0; i < reads; i++) {
    	e = tree->get(r2[i]);
    	if (e != NULL) {
    		cout << i << ": " << e->getValue() << ", ";
    	}
    }
*/
    MemoryRun* range = tree->getRange(0, 10);

    range->print();
    uint64 end = GetTimeMs64();
    cout << runSize << ", " << end - start << endl;
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




