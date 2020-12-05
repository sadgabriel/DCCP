#include "cursor.h"


void Cursor::cs() {
    pos = 0;
}

void Cursor::ce() {
    pos = 47;
}

void Cursor::ct(int num) {
    if (num > 47) {
        ce();
    }
    else if (num < 0) {
        cs();
    }
    else {
        pos = num;
    }
}

void Cursor::cr(int num) {
    if (pos+num >= 0 && pos+num < 48) {
        pos += num;
    }
    else if (num > 47){
        ce();
    }
    else {
        cs();
    }
}

void Cursor::cl(int num) {
    if (pos-num >= 0 && pos-num < 48) {
        pos -= num;
    }
    else if (num > 47) {
        ce();
    }
    else {
        cs();
    }
}

int Cursor::getPosition() {
    return pos;
}

