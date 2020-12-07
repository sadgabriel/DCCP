#include "Sheet.h"
#include <cassert>


Sheet::Sheet() {
	for (int i = 0; i < 30; ++i) {
		Paper new_paper;
		paper_array[i] = new_paper;
	}
}

// 현재 커서와 페이지 위치에 주어진 계이름과 리듬의 노트를 만들어서 삽입한다.
Note Sheet::insert(const char* pitch, const char* rhythm) {
	Note new_note = Note{ pitch, rhythm };

	paper_array[page.getPosition()].insert(cursor.getPosition(), new_note);

	// 추가 이후에 한 칸 뒤로 이동한다.
	cursor.cr();

	// 연주를 위해 노트를 리턴한다.
	return new_note;
}

void Sheet::remove(int number) {
	for (int i = 0; i < number; ++i) {
		// 페이퍼 클래스에서 자동으로 노트들을 땡겨준다.
		paper_array[page.getPosition()].remove(cursor.getPosition());
	}
}

Note Sheet::replace(const char* pitch, const char* rhythm) {
	Note new_note = Note{ pitch, rhythm };

	paper_array[page.getPosition()].replace(cursor.getPosition(), new_note);

	// 변경 이후에 한 칸 뒤로 이동한다.
	cursor.cr();

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
		if (paper_array[page.getPosition()].getNote(i).is_NULL) {
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
		Note new_note;
		note_array[i] = new_note;
	}
}

void Paper::insert(int idx, Note note) {
	// 만약 가득찬 페이지라면 아무것도 하지 않는다. 다른걸 지우고 해야 함.
	if (isFull() == true) {
		//do nothing
	}
	else {
		// 해당 인덱스에 다른 노트가 있는지 검사한다. (널노트가 들어있으면 비어있다는 뜻)
		if (note_array[idx].is_NULL== true) {
			note_array[idx] = note;	// 만약 없다면 그냥 대입한다.
		}
		// 만약 해당 인덱스에 임자가 있다면 한 칸씩 뒤로 미루고 넣는다.
		else {
			// 마지막 자리의 노트는 할당 해제.
			note_array[47].release();

			for (int i = 47; i >= idx; --i) {
				note_array[i] = note_array[i - 1];
			}
			note_array[idx] = note;
		}

		++size;	//사이즈 증가
	}
}

void Paper::remove(int idx) {
	// 만약 null노트의 인덱스라면 아무 것도 하지 않는다.
	if (note_array[idx].is_NULL == true) {
		// do nothing
	}
	// 그렇지 않고 만약 무언가 있다면
	else {
		// release하고 앞의 노트들를 땡겨 넣어서 삭제 처리한다.
		note_array[idx].release();

		for (int i = idx; i < 47; ++i) {
			note_array[i] = note_array[i + 1];
		}
		// 마지막 노트에는 NULL노트를 넣는다.
		note_array[47] = Note();

		--size;	// 사이즈 감소
	}
}

void Paper::replace(int idx, Note note) {
	note_array[idx].release();
	note_array[idx] = note;
}
