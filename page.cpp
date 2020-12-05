#include "page.h"


void Page::pr() {
    if (pos < 29) pos++;
    else pe();
}

void Page::pl() {
    if (pos > 0) pos--;
    else ps();
}

void Page::pt(int num) {
    if (num > 29) pe();
    else if (num < 0) ps();
    else pos = num;
}

void Page::ps() {
    pos = 0;
}

void Page::pe() {
    pos = 29;
}

int Page::getPosition() {
    return pos;
}