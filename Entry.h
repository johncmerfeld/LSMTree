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
        Entry(int key = 0, int value = 0);
        void update(int newValue);
        int getKey();
        int getValue();
};

#endif /* ENTRY_H_ */
