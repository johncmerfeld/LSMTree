//
// Created by Stathis on 3/11/2019.
//

#include "RunMetadata.h"
#include "BloomFilter.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void) {;

    BloomFilter *bf = new BloomFilter(100, 5);
    bf->add(20);
    cout << bf->contains(20)<<endl;
    cout << getpagesize();
    return 0;
}
