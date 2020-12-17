#pragma once
#include "Note.h"

#include <vector>

#include "cursor.h"
#include "page.h"

class Paper {
private:
	// �� �������� �ִ� note ���� 48�� ������ �����Ѵ�.
	Note* note_array[48]; // Note �� �����Ͱ� 48�� ���� �迭.
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
	// Paper��ü�� Note�� ���, Sheet�� Paper�� ��´�.
	// �ִ� ������ ���� 30�̰�,
	// �� �������� �ִ� note ���� 48�� ������ �����Ѵ�.
	Paper *paper_array[30];	// ����ִ� �����۰� ���� �� ���·� �ʱ�ȭ�ȴ�. ������ �������� �迭.

public:
	Sheet();
	~Sheet();

	// Ŀ���� ������ ��ü
	Cursor cursor;
	Page page;


	// -------- ������ --------
	// ���� Ŀ���� ������ ��ġ�� �־��� ���̸��� ������ ��Ʈ�� ���� �����Ѵ�.
	Note* insert(const char*, const char*);		// ��Ʈ�� �Ǻ��� ������ �� ���� �Ҹ��� �����Ѵ�.
	// ���� Ŀ���� �������� �ִ� ��Ʈ�� �����Ѵ�.
	void remove(int number = 1);
	// ���� Ŀ���� �������� �ִ� ��Ʈ�� �־��� ���̸��� ������ ��Ʈ�� �����Ѵ�.
	Note* replace(const char*, const char*);

	// ���� Ŀ���� ������ ��ġ�� �ִ� ��Ʈ�� �����Ѵ�.
	Note* getNote() {
		return paper_array[page.getPosition()]->getNote(cursor.getPosition());
	}

	int BPM = 200;

	// Ŀ�� ���� �Լ�
	void cs();
	void ce();
	void ct(int);
	void cr(int = 1);
	void cl(int = 1);

	// ������ ���� �Լ�
	void ps();
	void pe();
	void pt(int);
	void pr(int = 1);
	void pl(int = 1);
};

