#pragma once
#include "Note.h"
#include "Cursor.h"
#include "Page.h"
#include <vector>

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
	// 연산자
	void insert(Cursor&, Page&, Note);
	void remove(Cursor&, Page&, int number = 1);
	void replace(Cursor&, Page&, Note);
	Note getNote(int pos, Page& page) {
		return paper_array[page.getPosition()].getNote(pos);
	}
};


