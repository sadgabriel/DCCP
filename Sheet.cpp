#include "Sheet.h"
#include <cassert>


Sheet::Sheet() {
	for (int i = 0; i < 30; ++i) {
		Paper new_paper;
		paper_array[i] = new_paper;
	}
}

// ���� Ŀ���� ������ ��ġ�� �־��� ���̸��� ������ ��Ʈ�� ���� �����Ѵ�.
Note Sheet::insert(const char* pitch, const char* rhythm) {
	Note new_note = Note{ pitch, rhythm };

	paper_array[page.getPosition()].insert(cursor.getPosition(), new_note);

	// �߰� ���Ŀ� �� ĭ �ڷ� �̵��Ѵ�.
	cursor.cr();

	// ���ָ� ���� ��Ʈ�� �����Ѵ�.
	return new_note;
}

void Sheet::remove(int number) {
	for (int i = 0; i < number; ++i) {
		// ������ Ŭ�������� �ڵ����� ��Ʈ���� �����ش�.
		paper_array[page.getPosition()].remove(cursor.getPosition());
	}
}

Note Sheet::replace(const char* pitch, const char* rhythm) {
	Note new_note = Note{ pitch, rhythm };

	paper_array[page.getPosition()].replace(cursor.getPosition(), new_note);

	// ���� ���Ŀ� �� ĭ �ڷ� �̵��Ѵ�.
	cursor.cr();

	// ���ָ� ���� ��Ʈ�� �����Ѵ�.
	return new_note;
}


// ===================================== Paper Ŭ���� =============================================

Paper::Paper() {
	for (int i = 0; i < 48; ++i) {
		Note new_note;
		note_array[i] = new_note;
	}
}

void Paper::insert(int idx, Note note) {
	// ���� ������ ��������� �ƹ��͵� ���� �ʴ´�. �ٸ��� ����� �ؾ� ��.
	if (isFull() == true) {
		//do nothing
	}
	else {
		// �ش� �ε����� �ٸ� ��Ʈ�� �ִ��� �˻��Ѵ�. (�γ�Ʈ�� ��������� ����ִٴ� ��)
		if (note_array[idx].is_NULL== true) {
			note_array[idx] = note;	// ���� ���ٸ� �׳� �����Ѵ�.
		}
		// ���� �ش� �ε����� ���ڰ� �ִٸ� �� ĭ�� �ڷ� �̷�� �ִ´�.
		else {
			// ������ �ڸ��� ��Ʈ�� �Ҵ� ����.
			note_array[47].release();

			for (int i = 47; i >= idx; --i) {
				note_array[i] = note_array[i - 1];
			}
			note_array[idx] = note;
		}

		++size;	//������ ����
	}
}

void Paper::remove(int idx) {
	// ���� null��Ʈ�� �ε������ �ƹ� �͵� ���� �ʴ´�.
	if (note_array[idx].is_NULL == true) {
		// do nothing
	}
	// �׷��� �ʰ� ���� ���� �ִٸ�
	else {
		// release�ϰ� ���� ��Ʈ�鸦 ���� �־ ���� ó���Ѵ�.
		note_array[idx].release();

		for (int i = idx; i < 47; ++i) {
			note_array[i] = note_array[i + 1];
		}
		// ������ ��Ʈ���� NULL��Ʈ�� �ִ´�.
		note_array[47] = Note();

		--size;	// ������ ����
	}
}

void Paper::replace(int idx, Note note) {
	note_array[idx].release();
	note_array[idx] = note;
}
