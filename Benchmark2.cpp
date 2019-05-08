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

    if (file.is_open()) {
        while (i < numLines + numLines / 2) {
            getline(file, type, ',');
            command = type[0];

            if ((type == "i") || (type == "u") || (type == "r")) {
                getline(file, key, ',');
                k = stoi(key);

                getline(file, val);
                v = stoi(val);
            }
            else {
                getline(file, key);
                k = stoi(key);
            }
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
        file.close();
    }

    uint64 end = GetTimeMs64();

    //Print total time elapsed
    cout << end - start << endl;

    return 0;

}








