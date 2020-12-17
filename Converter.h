#pragma once

#include "Note.h"
#include <vector>


/// <summary>
/// 컨버터의 역할: 노트와 관련된 문자열 명령어를 인터프리터로 부터 받아서, 노트에 저장할 문자열 계이름과 박자로 전환한다.]
/// 전환한 문자열을 리턴한다.
/// </summary>
class Converter{
public:
	const char* convertToPitch(char, int);
	const char* convertToRhythm(char, bool dotted = false);
};

