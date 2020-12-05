#pragma once
#include <stdexcept>

using namespace std;

class Page {
public:
    void pr();
    void pl();
    void pt(int num);
    void ps();
    void pe();
    int getPosition();
private:
    int pos = 0;
};