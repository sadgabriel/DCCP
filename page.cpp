#include "page.h"

// 페이지의 책임.
// pos가 0과 29 사이에 있게 한다.

void Page::ps() {
    pos = 0;
}

void Page::pe() {
    pos = 29;
}

void Page::pt(int num) {
    if (num > 29) pe();
    else if (num < 0) ps();
    else pos = num;
}

void Page::pr(int num) {
    pt(pos + num);
}

void Page::pl(int num) {
    pt(pos - num);
}

int Page::getPosition() {
    return pos;
}