#include "Note.h"

/*
bool BaseNote::is_null() {
	return null;
}

bool BaseNote::is_rest() {
	return rest;
}

void BaseNote::setColor(int i) {
	if (i >= 0 && i <= 15) {
		color = i;
	}
	else {
		throw(1);
	}
}

int BaseNote::getColor() {
	return color;
}

Note::Note(const char* pit, const char* rhy) {
	pitch = pit;
	rhythm = rhy;
	color = WHITE;
	null = false;
	rest = false;
}

Note::~Note() {
	delete[] pitch;
	delete[] rhythm;
}

const char* Note::getPitch() {
	return pitch;
}

const char* Note::getRhythm() {
	return rhythm;
}

RestNote::RestNote(const char* rhy) {
	rhythm = rhy;
	color = WHITE;
	null = false;
	rest = true;
}

RestNote::~RestNote() {
	delete rhythm;
}

const char* RestNote::getPitch() {
	return "@";
}

const char* RestNote::getRhythm() {
	return rhythm;
}

NullNote::NullNote() {
	color = GRAY;
	null = true;
	rest = false;
}

const char* NullNote::getPitch() {
	return "NUL";
}

const char* NullNote::getRhythm() {
	return "NUL";
}*/




Note::Note(const char* pit, const char* rhy) {
	is_NULL = false;

	pitch = pit;
	rhythm = rhy;
	color = WHITE;

	if ((pit[0] == '@') || (pit[0] == ',')) {
		is_rest = true;
	}
	else {
		is_rest = false;
	}
}
