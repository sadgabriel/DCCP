#pragma once
#include "Sheet.h"
#include <iostream>
#include <iomanip>
#include "color.h"

#define INSERT 0
#define REPLACE 1
#define REMOVE 2

#define CURSOR_COLOR YELLOW

// colored text with cout
// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// you can loop k higher to see more color choices
// for (int k = 1; k < 255; k++)
// {
	// pick the colorattribute k you want
//	SetConsoleTextAttribute(hConsole, k);
//	cout << k << " I want to be nice today!" << endl;
//}




class Printer{
public:
	void print(int octave, int mode, Sheet&);

    // x is the column, y is the row. The origin (0,0) is top-left.
    void setCursorPosition(int x, int y);

    // x, y좌표에 txt를 출력한다.
    void printAt(const char* txt, int x, int y);

private:
    void colorPrintExample() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int k = 1; k < 16; ++k) {
            SetConsoleTextAttribute(hConsole, k);
            std::cout << k << " Color Text is AWESOME!" << std::endl;
        }
    }
    void setColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
    void resetColor() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
    }
    
    int cursor_pos;

    // 콘솔에 프린트하는 함수들
    // 활용도를 위해서 마지막에 endl 출력 안함
    void printLine(int count, int color) {
        setColor(color);
        for (int i = 0; i < count; ++i) {
            std::cout << '-';
        }
        resetColor();
    }

    void printLineByMode(int count, int mode) {
        if (mode == INSERT) printLine(count, GREEN);
        else if (mode == REPLACE) printLine(count, GRAY);
        else if (mode == REMOVE) printLine(count, RED);
    }

    void printCursorLine(int start, int end, Sheet& sheet);
    void printOrderLine(int start, int end, Sheet& sheet);
    void printPitchLine(int start, int end, Sheet& sheet);
    void printRhythmLine(int start, int end, Sheet& sheet);
};

