#include "Converter.h"


// pitch[0] = 계이름 C~B
// pitch[1] = 옥타브
// pitch[2] = 샾# 여부, 플랫b은 없다.
// pitch[3] = '\0'
const char* Converter::convertToPitch(char command_pitch, int oct) {
	//char pitch[4];
	// 동적할당
	char* pitch = new char[4];

	if (command_pitch == 'z') {
		pitch[0] = 'C';
	}
	if (command_pitch == 's') {
		pitch[0] = 'C';
		pitch[2] = '#';
	}
	if (command_pitch == 'x') {
		pitch[0] = 'D';
	}
	if (command_pitch == 'd') {
		pitch[0] = 'D';
		pitch[2] = '#';
	}
	if (command_pitch == 'c') {
		pitch[0] = 'E';
	}
	if (command_pitch == 'v') {
		pitch[0] = 'F';
	}
	if (command_pitch == 'g') {
		pitch[0] = 'F';
		pitch[2] = '#';
	}
	if (command_pitch == 'b') {
		pitch[0] = 'G';
	}
	if (command_pitch == 'h') {
		pitch[0] = 'G';
		pitch[2] = '#';
	}
	if (command_pitch == 'n') {
		pitch[0] = 'A';
	}
	if (command_pitch == 'j') {
		pitch[0] = 'A';
		pitch[2] = '#';
	}
	if (command_pitch == 'm') {
		pitch[0] = 'B';
	}

	if (command_pitch == 'q') {
		oct += 1;
		pitch[0] = 'C';
	}
	if (command_pitch == '2') {
		oct += 1;
		pitch[0] = 'C';
		pitch[2] = '#';
	}
	if (command_pitch == 'w') {
		oct += 1;
		pitch[0] = 'D';
	}
	if (command_pitch == '3') {
		oct += 1;
		pitch[0] = 'D';
		pitch[2] = '#';
	}
	if (command_pitch == 'e') {
		oct += 1;
		pitch[0] = 'E';
	}
	if (command_pitch == 'r') {
		oct += 1;
		pitch[0] = 'F';
	}
	if (command_pitch == '5') {
		oct += 1;
		pitch[0] = 'F';
		pitch[2] = '#';
	}
	if (command_pitch == 't') {
		oct += 1;
		pitch[0] = 'G';
	}
	if (command_pitch == '6') {
		oct += 1;
		pitch[0] = 'G';
		pitch[2] = '#';
	}
	if (command_pitch == 'y') {
		oct += 1;
		pitch[0] = 'A';
	}
	if (command_pitch == '7') {
		oct += 1;
		pitch[0] = 'A';
		pitch[2] = '#';
	}
	if (command_pitch == 'u') {
		oct += 1;
		pitch[0] = 'B';
	}


	if (command_pitch == 'i') { oct += 2; pitch[0] = 'C'; }
	if (command_pitch == '9') { oct += 2; pitch[0] = 'C'; pitch[2] = '#'; }
	if (command_pitch == 'o') {
		oct += 2; pitch[0] = 'D';
	}
	if (command_pitch == '0') { oct += 2; pitch[0] = 'D'; pitch[2] = '#'; }
	if (command_pitch == 'p') { oct += 2; pitch[0] = 'E'; }

	// int to char. 옥타브 입력
	pitch[1] = '0' + oct;

	return pitch;
}

// rhythm[0] = 1
// rhythm[1] = /
// rhythm[2] = 4	(ex)
// rhythm[3] = '\0' OR 6 when rhythm is 1/16.
// rhythm[4] = '\0'                        zxcvb -> 1/4* 1/8 1/16 /// C#1/8* / z1/8* / zv* / zf (C#4 - 1/8*) zxcvb asdf
const char* Converter::convertToRhythm(char command_rhythm, bool is_dotted) {
	//char rhythm[5];
	char* rhythm = new char[5];

	if (command_rhythm == 'z') {
		rhythm[0] = '1';
		rhythm[1] = '/';
		rhythm[2] = '1';
	}
	else if (command_rhythm == 'x') {
		rhythm[0] = '1';
		rhythm[1] = '/';
		rhythm[2] = '2';
	}
	else if (command_rhythm == 'c') {
		rhythm[0] = '1';
		rhythm[1] = '/';
		rhythm[2] = '4';
	}
	else if (command_rhythm == 'v') {
		rhythm[0] = '1';
		rhythm[1] = '/';
		rhythm[2] = '8';
	}
	else if (command_rhythm == 'b') {
		rhythm[0] = '1';
		rhythm[1] = '/';
		rhythm[2] = '1';
		rhythm[3] = '6';
	}
	else throw;

	// 점음표
	// 1/16*은 없다.
	if ((is_dotted == true) && (command_rhythm == 'b')) {
		rhythm[3] = '*';
	}

	return rhythm;
}
