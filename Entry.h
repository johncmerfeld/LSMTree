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
        bool isRemove;

    public:
        Entry(int k, int v, bool remove);
        void update(int newValue);
};

#endif /* ENTRY_H_ */
