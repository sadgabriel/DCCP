#include "cursor.h"


void Cursor::cs() {
    pos = 0;
}

void Cursor::ce() {
    pos = 47;
}

void Cursor::ct(int num) {
    if (num > 47) ce();
    else if (num < 0) cs();
    else pos = num;
}

void Cursor::cr(int num) {
    ct(pos + num);
}

void Cursor::cl(int num) {
    ct(pos - num);
}

int Cursor::getPosition() {
    return pos;
}

