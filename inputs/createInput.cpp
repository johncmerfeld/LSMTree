//
// Created by Stathis on 4/29/2019.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <time.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    int lines = stoi(argv[1]);
    printf("%d\n", lines + lines / 2);
    srand(time(NULL));


    int dels = stoi(argv[2]);
    int upds = stoi(argv[3]);
    int existGets = stoi(argv[4]);
    int nonExistGets = 100 - existGets;

    vector<int> g1;

    for (int i = 0; i < lines; i++) {
        if (rand() % 100 < dels + upds) {
            if (rand() % 2 == 0)
                printf("r,%d\n", g1[rand() % (g1.size())]);
            else {
                if (g1.size() != 0) {
                    printf("u,%d,%d\n", g1[rand() % g1.size()], rand() % lines);
                }
            }
        }
        else {
            int elem = rand() % (lines * 100);
            g1.push_back(elem);
            printf("i,%d,%d\n", elem, rand() % lines);
        }
    }

    for (int i = 0; i < lines / 2; i++) {
        if (rand() % 100 < existGets) {
            printf("g,%d\n", g1[rand() % g1.size()]);
        }
        else {
            printf("g,%d\n", rand() % (lines * 100));
        }
    }
}