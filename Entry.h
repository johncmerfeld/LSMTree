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

    public:
        Entry(int k, int v);
        void update(int newValue);
        int getKey();
        int getValue();
};

#endif /* ENTRY_H_ */
