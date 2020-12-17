#pragma once
#include "Sheet.h"


class Player{

public:
	void playNote(Sheet&);
	void playNote(Note*, int BPM);

private:

	// pitch to freq
	int convertToFreq(const char*);

	// rhythm to milisec
	int convertToMilisec(const char*, int BPM);
};

