#pragma once
#include "Sheet.h"
#include <iostream>
#include <iomanip>


class Printer{
public:
	void print(int octave, int mode, Sheet&);
    // 0 삽입 모드
    // 1 대체 모드
    // 2 삭제 모드

    // x is the column, y is the row. The origin (0,0) is top-left.
    void setCursorPosition(int x, int y);

    // x, y좌표에 txt를 출력한다.
    void printAt(const char* txt, int x, int y);
};

