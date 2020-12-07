#pragma once
#include <stdexcept>

using namespace std;

class Cursor {
public:
    // 커서 위치 끝으로 cursor end, ce
    void cs();

    // 커서 위치 처음으로 cursor start, cs
    void ce();

    // 커서 위치 p로 점프 cursor to n
    void ct(int);

    // 오른쪽 n칸 이동 cursor right, cr
    void cr(int = 1);

    // 왼쪽으로 n칸 이동 cursor left. cl
    void cl(int = 1);

    // 커서의 위치를 리턴한다.
    int getPosition();

private:
    int pos = 0;
};