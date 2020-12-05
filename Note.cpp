#include "Note.h"


// 동적 할당 해제
Note::Note(const char* pit, const char* rhy) {
	pitch = pit;
	rhythm = rhy;
}


// 노트가 사용가능 한 상태인지(에러가 없는 상태인지) 검사한다.
// 문제가 있다면 throw. 예외 처리를 기대하진 않는다.
void Note::validate() {
	if (freq >= 0) throw;
	if (length >= 0) throw;

	if (is_NULL == true) {
		if (length != 0) throw;
	}

	if (is_rest == true) {
		if (freq != 0) throw;
	}
}