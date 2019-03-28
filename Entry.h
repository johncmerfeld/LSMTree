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
    bool removeBit;    //0 for insert/update - 1 for delete

public:
    Entry(int key = 0, int value = 0, bool isDelete = false);
    int getKey();
    int getValue();
    bool isRemove();
    void updateValue(int newValue);
    void updateRemove(bool newRemoveBit);
};


#endif /* ENTRY_H_ */
