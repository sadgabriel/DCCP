#pragma once
#include <windows.h>

class Note{
public:
	// 1, 0은 초기화되지 않은 NULL_NOTE를 뜻함
	// 쉼표는 0, length
	Note() {
		freq = 0;
		length = 0;
		is_NULL = true;
		is_rest = false;
	}
	Note(int, char, char);
	Note(int, int);

	bool is_NULL;
	bool is_rest;
	int freq;
	int length;
	void beep();

	const char* getPitch();
	const char* getLength();

private:
	// 제곱 연산의 정확도를 위해 double을 사용. 제곱 연산 정수로 변환할 때이후 소수점 이하는 버림.
	double pitchToFreq(char);
	int rhythmToLength(char);

	// 계이름을 리턴하기 위해서 관리하는 
	int oct = 0;
	char pit[4] = { '\0' , '\0' , '\0' , '\0' };
};

