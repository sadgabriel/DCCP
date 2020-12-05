#pragma once
#include "Sheet.h"


class Player{

public:
	void playNote(Sheet&);
	void playNote(Note&, int BPM);

private:

	// pitch to freq
	int convertToFreq(char*);

	// rhythm to milisec
	int convertToMilisec(char*, int BPM);
};

