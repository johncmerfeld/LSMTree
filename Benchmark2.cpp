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

    string type, key, val;
    char command;
    int k, v;

    int i = 0;

    TierLsmTree *tree = new TierLsmTree(runSize, levelSize, bloomSize);
    uint64 start = GetTimeMs64();

    if(file.is_open()) {
    	if (i < numLines) {
    		while(getline(file, type,  ',')) {

    			command = type[0];

				if ((type == "i") || (type == "u") || (type == "r")) {
					getline(file, key, ',');
					k = stoi(key);

					getline(file, val);
					v = stoi(val);
				}
				else {
					//cerr << "second type" << endl;
					getline(file, key);
					k = stoi(key);
				}
				//cerr << keys[i] << endl;
				//cout << numLines - i << endl;
				i++;

				switch (command) {
					case 'i':
						tree->insert(k, v);
						break;
					case 'd':
						tree->remove(k);
						break;
					case 'u':
						tree->insert(k, v);
						break;
					case 'g':
						tree->get(k);
						break;
					case 'r':
						tree->getRange(k, v);
						break;
				}

    		}
    	}
	  file.close();
    }
    cerr << "Setup0" << endl;

    uint64 end = GetTimeMs64();

    cerr << "Setup1" << endl;

    cout << end - start << endl;

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








