#include "Key.h"

Key::Key() : num(0), chr('\0'), type(NUMBER) {}

Key::Key(int n) : num(n), chr('\0'), type(NUMBER) {}

Key::Key(char c) {
    chr = c;
    if (c >= 'A' && c <= 'Z') type = UPPERCASE;
    else if (c >= 'a' && c <= 'z') type = LOWERCASE;
    else type = NUMBER; // Para caracteres no alfabéticos
}

bool Key::operator<(const Key& other) const {
    if (type != other.type) return type < other.type;
    return (type == NUMBER) ? (num < other.num) : (chr < other.chr);
}

bool Key::operator==(const Key& other) const {
    return type == other.type && 
           ((type == NUMBER) ? num == other.num : chr == other.chr);
}

bool Key::operator>(const Key& other) const {
    return !(*this < other || *this == other);
}

std::ostream& operator<<(std::ostream& os, const Key& k) {
    if (k.type == NUMBER) os << k.num;
    else os << k.chr;
    return os;
}
