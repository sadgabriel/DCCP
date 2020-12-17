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

// 현재 커서와 페이지 위치에 주어진 계이름과 리듬의 노트를 만들어서 삽입한다.
Note* Sheet::insert(const char* pitch, const char* rhythm) {
	Note* new_note = new Note{ pitch, rhythm }; // 동적으로 노트 생성

	// Paper에 노트를 넣는다. 뒤로 밀려서 빠져나온 노트가 있으면 포인터를 리턴한다.
	Note* pulled_note = paper_array[page.getPosition()]->insert(cursor.getPosition(), new_note);

	int temp_page_pos = page.getPosition() + 1;
	while (pulled_note != nullptr && temp_page_pos < 30) {
		pulled_note = paper_array[temp_page_pos]->insert(0, pulled_note); // 빠져나온 노트는 반복해서 다음 Paper에 넣는다.
	}
	if (pulled_note != nullptr) {
		delete pulled_note; // 마지막까지 들어가지 못한 노트는 지운다.
	}

	// 추가 이후에 한 칸 뒤로 이동한다.
	cr();

	// 연주를 위해 노트를 리턴한다.
	return new_note;
}

void Sheet::remove(int number) {
	for (int i = 0; i < number; ++i) { // number 번 반복한다.
		bool more = paper_array[page.getPosition()]->remove(cursor.getPosition(), true); // 다음 페이지에서 당겨와야 하는지.

		int temp_page_pos = page.getPosition();
		while (more && temp_page_pos <= 28) {
			paper_array[temp_page_pos]->replace(47, paper_array[temp_page_pos + 1]->getNote(0));
			// 다음 페이지의 첫 노트를 가져와 지금 페이지의 마지막에 넣는다.
			more = paper_array[temp_page_pos]->remove(0, false);
			temp_page_pos++;
		}
	}
}

Note* Sheet::replace(const char* pitch, const char* rhythm) {
	Note* new_note = new Note{ pitch, rhythm };

	paper_array[page.getPosition()]->replace(cursor.getPosition(), new_note);

	// 변경 이후에 한 칸 뒤로 이동한다.
	cr();

	// 연주를 위해 노트를 리턴한다.
	return new_note;
}

// --------- 커서 관련 함수

void Sheet::cs() {
	cursor.cs();
}

void Sheet::ce() {
	// 첫 null로.
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
	// 커서가 끝에 있으면 다음 페이지로 넘어가고 커서를 0으로 옮긴다.
	if (cursor.getPosition() == 47 && page.getPosition() < 29) {
		page.pr();
		cursor.cs();
	}
	else {
		cursor.cr(num);
	}
}

void Sheet::cl(int num) {
	// 커서가 처음에 있으면 이전 페이지로 넘어가고 커서를 29로 옮긴다.
	if (cursor.getPosition() == 0 && page.getPosition() > 0) {
		page.pl();
		cursor.ce();
	}
	else {
		cursor.cl(num);
	}
}

// --------- 페이지 관련 함수

void Sheet::ps() {
	page.ps();
}

void Sheet::pe() {
	page.pe();
}

void Sheet::pt(int num) {
	// 페이지 이동 후 커서를 첫 null로 옮긴다.
	page.pt(num);
	ce();
}

void Sheet::pr(int num) {
	pt(page.getPosition() + num);
}

void Sheet::pl(int num) {
	pt(page.getPosition() - num);
}

// ===================================== Paper 클래스 =============================================

Paper::Paper() {
	for (int i = 0; i < 48; ++i) {
		Note* new_note = new Note; // 노트를 동적으로 생성한다.
		note_array[i] = new_note; // 배열에 넣는다.
	}
}

Paper::~Paper() {
	for (int i = 0; i < 48; ++i) {
		delete note_array[i]; // 노트를 모두 지운다.
	}
}

Note* Paper::insert(int idx, Note* note) {
	if (note_array[idx]->is_NULL) { // 넣고자 하는 자리에 널노트가 있으면
		delete note_array[idx]; // 널노트를 지우고
		note_array[idx] = note; // 넣는다.
		return nullptr; // 널 포인터를 반환한다.
	}
	else { // 널노트가 아닌 경우
		Note* old_note = note_array[idx]; // 기존의 노트를 저장하고
		note_array[idx] = note; // 새 노트로 대체한다.

		// 오래된 노트는
		if (idx < 47) { // 이 페이퍼에 아직 넣을 자리가 있다면
			return insert(idx + 1, old_note); // 한 칸 뒤에 넣는다.
		}
		else {
			return old_note; // 아니면 밖에 넘긴다.
		}
	}
}

bool Paper::remove(int idx, bool del) {
	// 만약 null노트의 인덱스라면 아무 것도 하지 않는다.
	if (note_array[idx]->is_NULL == true) {
		return false;
	}
	// 그렇지 않고 만약 무언가 있다면
	else {
		if (del) delete note_array[idx]; // 지운다. del이 false면 지우지 않는다.

		int i = idx;
		for (; i < 47; ++i) {
			if (note_array[i + 1]->is_NULL) { // 당겨와야 할 게 널노트면
				note_array[i] = new Note; // 새로 널노트를 만들어 넣고
				break; // 그만 당겨온다.
			}

			note_array[i] = note_array[i + 1]; // 하나씩 당겨온다.
		}
		
		if (i == 47) { // 더 당겨와야 하면
			note_array[47] = new Note; // 일단 널노트를 넣어두고
			return true; // true를 반환.
		}
		else return false;
	}
}

void Paper::replace(int idx, Note* note) {
	delete note_array[idx]; // 넣고자 하는 위치에 있던 노트를 지운다.
	note_array[idx] = note; // 그리고 넣는다.
}
