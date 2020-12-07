#pragma once
#include <stdexcept>

using namespace std;

class Page {
public:
    void ps();
    void pe();
    void pt(int);
    void pr(int = 1);
    void pl(int = 1);
    
    
    int getPosition();
private:
    int pos = 0;
};