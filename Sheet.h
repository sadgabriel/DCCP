#pragma once
#include "Note.h"

#include <vector>

#include "cursor.h"
#include "page.h"

class Paper {
private:
	// 한 페이지의 최대 note 수는 48인 것으로 가정한다.
	Note note_array[48];
	int size = 0;
public:
	Paper();

	bool isFull() { return size == 48; }
	bool isEmpty() { return size == 0; }
	bool getSize() { return size; }

	void insert(int, Note);
	void remove(int);
	void replace(int, Note);
	Note getNote(int idx) {
		return note_array[idx];
	}
};

class Sheet{
private:
	// Paper객체에 Note를 담고, Sheet에 Paper를 담는다.
	// 최대 페이지 수는 30이고,
	// 한 페이지의 최대 note 수는 48인 것으로 가정한다.
	Paper paper_array[30];	// 비어있는 페이퍼가 가득 찬 형태로 초기화된다.

public:
	Sheet();

	// 커서와 페이지 객체
	Cursor cursor;
	Page page;


	// -------- 연산자 --------
	// 현재 커서와 페이지 위치에 주어진 계이름과 리듬의 노트를 만들어서 삽입한다.
	Note insert(const char*, const char*);		// 노트를 악보에 삽입할 때 마다 소리가 나야한다.
	// 현재 커서와 페이지에 있는 노트를 삭제한다.
	void remove(int number = 1);
	// 현재 커서와 페이지에 있는 노트를 주어진 계이름과 리듬의 노트로 변경한다.
	Note replace(const char*, const char*);

	// 현재 커서와 페이지 위치에 있는 노트를 리턴한다.
	Note getNote() {
		return paper_array[page.getPosition()].getNote(cursor.getPosition());
	}

	// 페이지의 끝이 어디인지 알려주는 정수
	int eop = 0;	// End Of Page
	// 추가 구현이 필요하다.

	void update_eop() {
		int count = 0;
		// 사용되고 있는 Paper의 개수 만큼 i를 증가시킨다.
		while (paper_array[count].isEmpty() != true) {
			++count;
		}

		// eop는 사용되고 있는 Paper의 개수가 아니라, 마지막 page의 끝을 나타내는 정수이므로 1을 뺀다.
		eop = count - 1;
	}

	int BPM = 200;
};

