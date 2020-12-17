#include "Sheet.h"
#include <cassert>


Sheet::Sheet() {
	for (int i = 0; i < 30; ++i) {
		Paper* new_paper = new Paper;
		paper_array[i] = new_paper;
	}
}

Sheet::~Sheet() {
	for (int i = 0; i < 30; ++i) {
		delete paper_array[i];
	}
}

// ���� Ŀ���� ������ ��ġ�� �־��� ���̸��� ������ ��Ʈ�� ���� �����Ѵ�.
Note* Sheet::insert(const char* pitch, const char* rhythm) {
	Note* new_note = new Note{ pitch, rhythm }; // �������� ��Ʈ ����

	// Paper�� ��Ʈ�� �ִ´�. �ڷ� �з��� �������� ��Ʈ�� ������ �����͸� �����Ѵ�.
	Note* pulled_note = paper_array[page.getPosition()]->insert(cursor.getPosition(), new_note);

	int temp_page_pos = page.getPosition() + 1;
	while (pulled_note != nullptr && temp_page_pos < 30) {
		pulled_note = paper_array[temp_page_pos]->insert(0, pulled_note); // �������� ��Ʈ�� �ݺ��ؼ� ���� Paper�� �ִ´�.
	}
	if (pulled_note != nullptr) {
		delete pulled_note; // ���������� ���� ���� ��Ʈ�� �����.
	}

	// �߰� ���Ŀ� �� ĭ �ڷ� �̵��Ѵ�.
	cr();

	// ���ָ� ���� ��Ʈ�� �����Ѵ�.
	return new_note;
}

void Sheet::remove(int number) {
	for (int i = 0; i < number; ++i) { // number �� �ݺ��Ѵ�.
		bool more = paper_array[page.getPosition()]->remove(cursor.getPosition(), true); // ���� ���������� ��ܿ;� �ϴ���.

		int temp_page_pos = page.getPosition();
		while (more && temp_page_pos <= 28) {
			paper_array[temp_page_pos]->replace(47, paper_array[temp_page_pos + 1]->getNote(0));
			// ���� �������� ù ��Ʈ�� ������ ���� �������� �������� �ִ´�.
			more = paper_array[temp_page_pos]->remove(0, false);
			temp_page_pos++;
		}
	}
}

Note* Sheet::replace(const char* pitch, const char* rhythm) {
	Note* new_note = new Note{ pitch, rhythm };

	paper_array[page.getPosition()]->replace(cursor.getPosition(), new_note);

	// ���� ���Ŀ� �� ĭ �ڷ� �̵��Ѵ�.
	cr();

	// ���ָ� ���� ��Ʈ�� �����Ѵ�.
	return new_note;
}

// --------- Ŀ�� ���� �Լ�

void Sheet::cs() {
	cursor.cs();
}

void Sheet::ce() {
	// ù null��.
	for (int i = 0; i < 48; i++) {
		if (paper_array[page.getPosition()]->getNote(i)->is_NULL) {
			ct(i);
			break;
		}
	}
}

void Sheet::ct(int num) {
	cursor.ct(num);
}

void Sheet::cr(int num) {
	// Ŀ���� ���� ������ ���� �������� �Ѿ�� Ŀ���� 0���� �ű��.
	if (cursor.getPosition() == 47 && page.getPosition() < 29) {
		page.pr();
		cursor.cs();
	}
	else {
		cursor.cr(num);
	}
}

void Sheet::cl(int num) {
	// Ŀ���� ó���� ������ ���� �������� �Ѿ�� Ŀ���� 29�� �ű��.
	if (cursor.getPosition() == 0 && page.getPosition() > 0) {
		page.pl();
		cursor.ce();
	}
	else {
		cursor.cl(num);
	}
}

// --------- ������ ���� �Լ�

void Sheet::ps() {
	page.ps();
}

void Sheet::pe() {
	page.pe();
}

void Sheet::pt(int num) {
	// ������ �̵� �� Ŀ���� ù null�� �ű��.
	page.pt(num);
	ce();
}

void Sheet::pr(int num) {
	pt(page.getPosition() + num);
}

void Sheet::pl(int num) {
	pt(page.getPosition() - num);
}

// ===================================== Paper Ŭ���� =============================================

Paper::Paper() {
	for (int i = 0; i < 48; ++i) {
		Note* new_note = new Note; // ��Ʈ�� �������� �����Ѵ�.
		note_array[i] = new_note; // �迭�� �ִ´�.
	}
}

Paper::~Paper() {
	for (int i = 0; i < 48; ++i) {
		delete note_array[i]; // ��Ʈ�� ��� �����.
	}
}

Note* Paper::insert(int idx, Note* note) {
	if (note_array[idx]->is_NULL) { // �ְ��� �ϴ� �ڸ��� �γ�Ʈ�� ������
		delete note_array[idx]; // �γ�Ʈ�� �����
		note_array[idx] = note; // �ִ´�.
		return nullptr; // �� �����͸� ��ȯ�Ѵ�.
	}
	else { // �γ�Ʈ�� �ƴ� ���
		Note* old_note = note_array[idx]; // ������ ��Ʈ�� �����ϰ�
		note_array[idx] = note; // �� ��Ʈ�� ��ü�Ѵ�.

		// ������ ��Ʈ��
		if (idx < 47) { // �� �����ۿ� ���� ���� �ڸ��� �ִٸ�
			return insert(idx + 1, old_note); // �� ĭ �ڿ� �ִ´�.
		}
		else {
			return old_note; // �ƴϸ� �ۿ� �ѱ��.
		}
	}
}

bool Paper::remove(int idx, bool del) {
	// ���� null��Ʈ�� �ε������ �ƹ� �͵� ���� �ʴ´�.
	if (note_array[idx]->is_NULL == true) {
		return false;
	}
	// �׷��� �ʰ� ���� ���� �ִٸ�
	else {
		if (del) delete note_array[idx]; // �����. del�� false�� ������ �ʴ´�.

		int i = idx;
		for (; i < 47; ++i) {
			if (note_array[i + 1]->is_NULL) { // ��ܿ;� �� �� �γ�Ʈ��
				note_array[i] = new Note; // ���� �γ�Ʈ�� ����� �ְ�
				break; // �׸� ��ܿ´�.
			}

			note_array[i] = note_array[i + 1]; // �ϳ��� ��ܿ´�.
		}
		
		if (i == 47) { // �� ��ܿ;� �ϸ�
			note_array[47] = new Note; // �ϴ� �γ�Ʈ�� �־�ΰ�
			return true; // true�� ��ȯ.
		}
		else return false;
	}
}

void Paper::replace(int idx, Note* note) {
	delete note_array[idx]; // �ְ��� �ϴ� ��ġ�� �ִ� ��Ʈ�� �����.
	note_array[idx] = note; // �׸��� �ִ´�.
}
