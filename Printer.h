#pragma once
#include "Sheet.h"
#include <iostream>
#include <iomanip>


class Printer{
public:
	void print(int, Cursor&, Page&, Sheet&);

    // x is the column, y is the row. The origin (0,0) is top-left.
    void setCursorPosition(int x, int y);
};

