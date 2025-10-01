#ifndef KEY_H
#define KEY_H

#include <iostream>

enum KeyType { NUMBER, UPPERCASE, LOWERCASE };

struct Key {
    int num;
    char chr;
    KeyType type;

    Key();
    Key(int n);
    Key(char c);

    bool operator<(const Key& other) const;
    bool operator==(const Key& other) const;
    bool operator>(const Key& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Key& k);
};

#endif
