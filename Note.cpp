#include "Note.h"


Note::Note(const char* pit, const char* rhy) {
	is_NULL = false;

	pitch = pit;
	rhythm = rhy;

	if ((pit[0] == '@') || (pit[0] == ',')) {
		is_rest = true;
	}
	else {
		is_rest = false;
	}
}
