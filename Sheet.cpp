#include "Sheet.h"


Sheet::Sheet() {
	for (int i = 0; i < 30; ++i) {
		Paper new_paper;
		paper_array[i] = new_paper;
	}
}

// 현재 커서와 페이지 위치에 주어진 계이름과 리듬의 노트를 만들어서 삽입한다.
Note& Sheet::insert(const char* pitch, const char* rhythm) {
	Note new_note{ pitch, rhythm };

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

Note& Sheet::replace(const char* pitch, const char* rhythm) {
	Note new_note{ pitch, rhythm };

	paper_array[page.getPosition()].insert(cursor.getPosition(), new_note);

	// 변경 이후에 한 칸 뒤로 이동한다.
	cursor.cr();

	// 연주를 위해 노트를 리턴한다.
	return new_note;
}



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
			for (int i = 47; i >= idx; --i) {
				note_array[i] = note_array[i - 1];
			}
			note_array[idx] = note;
		}

		++size;	//사이즈 증가
	}
}

void Paper::remove(int idx) {
	// 만약 null노트 없는 인덱스라면 아무 것도 하지 않는다.
	if (note_array[idx].is_NULL == true) {
		// do nothing
	}
	// 그렇지 않고 만약 무언가 있다면
	else {
		// 빈 null노트를 넣어서 삭제 처리한다.
		note_array[idx] = Note();

		--size;	// 사이즈 감소
	}
}

void Paper::replace(int idx, Note note) {
	note_array[idx] = note;
}
