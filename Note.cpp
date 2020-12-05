#include "Note.h"


// 동적 할당 해제
Note::Note(const char* pit, const char* rhy) {
	is_NULL = false;

	pitch = pit;
	rhythm = rhy;


	if ((pit[0] == '@') || (pit[0] == ',')) {
		is_rest = true;
	}
}
