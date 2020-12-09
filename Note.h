﻿#pragma once
#include <windows.h>
#include "color.h"


/*
class BaseNote {
public:
	virtual ~BaseNote() = 0;
	bool is_null();
	bool is_rest();

	virtual const char* getPitch() = 0;
	virtual const char* getRhythm() = 0;

	void setColor(int);
	int getColor();
public:
	bool null;
	bool rest;
	int color;
};

class Note : public BaseNote {
public:
	Note(const char*, const char*);
	~Note();

	const char* getPitch();
	const char* getRhythm();
private:
	Note();
	const char* pitch;
	const char* rhythm;
};

class RestNote : public BaseNote {
public:
	RestNote(const char*);
	~RestNote();

	const char* getPitch();
	const char* getRhythm();
private:
	RestNote();
	const char* rhythm;
};

class NullNote : public BaseNote {
public:
	NullNote();
	const char* getPitch();
	const char* getRhythm();
};
*/

class Note{
public:
	// NULL_Note는 주파수는 상관없고, 길이가 0이다.
	// 쉼표는 주파수가 0이고 길이를 갖는다.
	bool is_NULL;		// 사용되는 노트인지 구분.
	bool is_rest;		// 
	

	Note() {
		pitch = nullptr;
		rhythm = nullptr;
		is_NULL = true;
		is_rest = true;
		color = GRAY;
	}

	// 노트 생성자
	Note(const char*, const char*);

	// 노트 소멸자
	~Note() { release(); }

	// 동적 할당 해제
	void release() {
		delete[] pitch;
		delete[] rhythm;

		is_NULL = true;
		is_rest = true;
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

	int getColor() { return color; }
	int setColor(int i) { if (i <= 15 && i >= 0) color = i; else throw(1); }

private:
	int color;
};