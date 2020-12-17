#pragma once
#include "Note.h"

#include <vector>

#include "cursor.h"
#include "page.h"

class Paper {
private:
	// 한 페이지의 최대 note 수는 48인 것으로 가정한다.
	Note* note_array[48]; // Note 의 포인터가 48개 들어가는 배열.
	int size = 0;
public:
	Paper();
	~Paper();

	Note* insert(int, Note*);
	bool remove(int, bool);
	void replace(int, Note*);
	Note* getNote(int idx) {
		return note_array[idx];
	}
};

class Sheet{
private:
	// Paper객체에 Note를 담고, Sheet에 Paper를 담는다.
	// 최대 페이지 수는 30이고,
	// 한 페이지의 최대 note 수는 48인 것으로 가정한다.
	Paper *paper_array[30];	// 비어있는 페이퍼가 가득 찬 형태로 초기화된다. 페이퍼 포인터의 배열.

public:
	Sheet();
	~Sheet();

	// 커서와 페이지 객체
	Cursor cursor;
	Page page;


	// -------- 연산자 --------
	// 현재 커서와 페이지 위치에 주어진 계이름과 리듬의 노트를 만들어서 삽입한다.
	Note* insert(const char*, const char*);		// 노트를 악보에 삽입할 때 마다 소리가 나야한다.
	// 현재 커서와 페이지에 있는 노트를 삭제한다.
	void remove(int number = 1);
	// 현재 커서와 페이지에 있는 노트를 주어진 계이름과 리듬의 노트로 변경한다.
	Note* replace(const char*, const char*);

	// 현재 커서와 페이지 위치에 있는 노트를 리턴한다.
	Note* getNote() {
		return paper_array[page.getPosition()]->getNote(cursor.getPosition());
	}

	int BPM = 200;

	// 커서 관련 함수
	void cs();
	void ce();
	void ct(int);
	void cr(int = 1);
	void cl(int = 1);

	// 페이지 관련 함수
	void ps();
	void pe();
	void pt(int);
	void pr(int = 1);
	void pl(int = 1);
};

