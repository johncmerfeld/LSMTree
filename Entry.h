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
    Entry();

    Entry(int key, int value, bool isDelete = false);

    Entry(int key, int value);

    int getKey();

    int getValue();

    bool isRemove();

    void updateValue(int newValue);

    void updateRemove(bool newRemoveBit);

    void setEntry(Entry *e);

    void printer();
};


#endif /* ENTRY_H_ */
