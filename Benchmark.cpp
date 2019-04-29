#include "RunMetadata.h"
#include "BloomFilter.h"
#include "LsmTree.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <random>
#include "GetTimeMs64.h"

using namespace std;

/* TODO have this use averages, or put it in the R */
int main(int argc, char *argv[]) {

	if (argc < 6) {
		cout << "Insufficient arguments." << endl;
		cout << "Usage: './Benchmark runSize levelSize bloomSize file lines'" << endl;
		return 1;
	}

	int runSize = stoi(argv[1]);
	int levelSize = stoi(argv[2]);
	int bloomSize = stoi(argv[3]);
	string filename = argv[4];
	int numLines = stoi(argv[5]);
    ifstream file(filename.c_str());

    char *commands = new char[numLines];
    int *keys = new int[numLines];
    int *vals = new int[numLines];

    string type, key, val;
    int k, v;

    int i = 0;
    if(file.is_open()) {
    	while(getline(file, type,  ',')) {
    		if (i < numLines) {
    			commands[i] = type[0];

				if ((type == "i") || (type == "u") || (type == "r")) {
					getline(file, key, ',');
					keys[i] = stoi(key);

					getline(file, val);
					vals[i] = stoi(val);
				}
				else {
					//cerr << "second type" << endl;
					getline(file, key);
					keys[i] = stoi(key);
				}
				//cerr << keys[i] << endl;
				//cout << numLines - i << endl;
				i++;
    		}
    	}
	  file.close();
    }

    TierLsmTree *tree = new TierLsmTree(runSize, levelSize, bloomSize);

    uint64 start = GetTimeMs64();
    for (int i = 0; i < numLines; i++) {
    	switch (commands[i]) {
    		case 'i':
    			tree->insert(keys[i], vals[i]);
    			break;
    		case 'd':
    			tree->remove(keys[i]);
    			break;
    		case 'u':
    			tree->insert(keys[i], vals[i]);
    			break;
    		case 'g':
    			tree->get(keys[i]);
    			break;
    		case 'r':
    			tree->getRange(keys[i], vals[i]);
    			break;
    	}
    }
    uint64 end = GetTimeMs64();

    cerr << "Setup1" << endl;

    cout << end - start << endl;

    delete [] commands;
    delete [] keys;
    delete [] vals;

    return 0;

    //

    //

	/*
	// only used once to initialise (seed) engine
	std::random_device rd;

	// random-number engine used (Mersenne-Twister in this case)
	std::mt19937 rng(rd());

	// guaranteed unbiased
	std::uniform_int_distribution<int> uni(-1000,1000); */

    //ResultSet *rs;
}




