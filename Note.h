#pragma once
#include <windows.h>

class Note{
public:
	// NULL_Note는 주파수는 상관없고, 길이가 0이다.
	// 쉼표는 주파수가 0이고 길이를 갖는다.
	bool is_NULL;		// 사용되는 노트인지 구분.
	bool is_rest;		// 

	Note() {
		freq = 0;
		length = 0;
		is_NULL = true;
		is_rest = true;
	}

	// 노트 생성자
	Note(const char*, const char*);

	// 노트 소멸자. 동적 배열 해제한다.
	~Note() {
		delete[] pitch;
		delete[] rhythm;
	}


	// 길이4 배열
	// length of pitch is 4
	// pitch[0] = 계이름 C~B
	// pitch[1] = 옥타브
	// pitch[2] = 샾# 여부, 플랫b은 없다.
	// pitch[3] = '\0'
	const char* pitch;


	// 길이5 배열
	// rhythm[0] = 1
	// rhythm[1] = /
	// rhythm[2] = 4 (ex) 1/4
	// rhythm[3] = '\0' OR 6 when rhythm is 1/16. OR dot*(점음표)
	// rhythm[4] = '\0'
	const char* rhythm;

	const char* getPitch() { return pitch; }	// 노트의 계이름을 리턴한다.
	const char* getRhythm() { return rhythm; }	// 노트의 박자를 리턴한다.

	int freq;		// 노트에 해당하는 음의 주파수를 정수로 저장.
	int length;		// 노트에 해당하는 음에 길이를 정수로 저장.
	

private:
	// 노트가 사용가능 한 상태인지(에러가 없는 상태인지) 검사한다.
	// 문제가 있다면 throw
	void validate();
};

