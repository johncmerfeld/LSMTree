/*
 * Entry.h
 *
 */

#ifndef ENTRY_H_
#define ENTRY_H_

class Entry {
private:
    int key;
    int value;
    bool status;    //0 for insert/update - 1 for delete

public:
    Entry(int key = 0, int value = 0, int status = 0);

    void update(int newValue);

    int getKey();

    int getValue();
};


#endif /* ENTRY_H_ */
