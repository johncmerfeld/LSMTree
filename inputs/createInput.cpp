//
// Created by Stathis on 4/29/2019.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {
    int lines = stoi(argv[1]);
    printf("%d\n", lines);
    srand(time(NULL));


    int dels = stoi(argv[2]);
    int upds = stoi(argv[3]) * lines;
    int existGets;
    int nonExistGets;

    for (int i = 0; i < lines; i++) {
        if (rand()% 100 < dels)
            printf("d %d\n", rand() % (2 * i));
        else
            printf("i %d %d\n", i, i);
    }
}