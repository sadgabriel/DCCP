#pragma once
#include <windows.h>

class Note{
public:
	// NULL_Note는 주파수는 상관없고, 길이가 0이다.
	// 쉼표는 주파수가 0이고 길이를 갖는다.
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

	int freq;		// 노트에 해당하는 음의 주파수를 정수로 저장.
	int length;		// 노트에 해당하는 음에 길이를 정수로 저장.
	const char* getPitch();		// 노트의 계이름을 리턴한다. private 변수로 pit (char배열)을 따로 관리해준다.
	const char* getLength();	// 노트의 정수 길이를 박자로 전환하여 리턴한다. ex) 1200 / lengthPerBit -> "1/1".
	
	void beep();

	int lengthPerBit = 150;		// Bpm은 200으로 가정한다.



private:
	// 제곱 연산의 정확도를 위해 double을 사용. 제곱 연산 정수로 변환할 때이후 소수점 이하는 버림.
	double pitchToFreq(char);
	int rhythmToLength(char);

	// 계이름을 리턴하기 위해서 관리하는 
	int oct = 0;
	char pit[4] = { '\0' , '\0' , '\0' , '\0' };
};

