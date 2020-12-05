#include "Converter.h"

// pit[0] = 계이름 C~B
	// pit[1] =  옥타브
	// pit[2] =  샾# 여부, 플랫b은 없다.
	// pit[3] = '\0'
double Converter::pitchToFreq(char pitch) {
	if (pitch == 'z') {
		pit[0] = 'C';
		return 32.7032;
	}
	if (pitch == 's') {
		pit[0] = 'C';
		pit[2] = '#';
		return 34.6478;
	}
	if (pitch == 'x') {
		pit[0] = 'D';
		return 36.7081;
	}
	if (pitch == 'd') {
		pit[0] = 'D';
		pit[2] = '#';
		return 38.8909;
	}
	if (pitch == 'c') {
		pit[0] = 'E';
		return 41.2034;
	}
	if (pitch == 'v') {
		pit[0] = 'F';
		return 43.6535;
	}
	if (pitch == 'g') {
		pit[0] = 'F';
		pit[2] = '#';
		return 46.2493;
	}
	if (pitch == 'b') {
		pit[0] = 'G';
		return 48.9994;
	}
	if (pitch == 'h') {
		pit[0] = 'G';
		pit[2] = '#';
		return 51.9130;
	}
	if (pitch == 'n') {
		pit[0] = 'A';
		return 55.0000;
	}
	if (pitch == 'j') {
		pit[0] = 'A';
		pit[2] = '#';
		return 58.2705;
	}
	if (pitch == 'm') {
		pit[0] = 'B';
		return 61.7354;
	}

	if (pitch == 'q') {
		oct += 1;
		pit[0] = 'C';
		return 65.4064;
	}
	if (pitch == '2') {
		oct += 1;
		pit[0] = 'C';
		pit[2] = '#';
		return 69.2957;
	}
	if (pitch == 'w') {
		oct += 1;
		pit[0] = 'D';
		return 73.4162;
	}
	if (pitch == '3') {
		oct += 1;
		pit[0] = 'D';
		pit[2] = '#';
		return 77.7817;
	}
	if (pitch == 'e') {
		oct += 1;
		pit[0] = 'E';
		return 82.4069;
	}
	if (pitch == 'r') {
		oct += 1;
		pit[0] = 'F';
		return 87.3071;
	}
	if (pitch == '5') {
		oct += 1;
		pit[0] = 'F';
		pit[2] = '#';
		return 92.4986;
	}
	if (pitch == 't') {
		oct += 1;
		pit[0] = 'G';
		return 97.9989;
	}
	if (pitch == '6') {
		oct += 1;
		pit[0] = 'G';
		pit[2] = '#';
		return 103.8262;
	}
	if (pitch == 'y') {
		oct += 1;
		pit[0] = 'A';
		return 110.0000;
	}
	if (pitch == '7') {
		oct += 1;
		pit[0] = 'A';
		pit[2] = '#';
		return 116.5409;
	}
	if (pitch == 'u') {
		oct += 1;
		pit[0] = 'B';
		return 123.4708;
	}


	if (pitch == 'i') { return 130.8128; oct += 2; pit[0] = 'C'; }
	if (pitch == '9') { return 138.5913; oct += 2; pit[0] = 'C'; pit[2] = '#'; }
	if (pitch == 'o') {
		return 146.8324; oct += 2; pit[0] = 'D';
	}
	if (pitch == '0') { return 155.5635; oct += 2; pit[0] = 'D'; pit[2] = '#'; }
	if (pitch == 'p') { return 164.8138; oct += 2; pit[0] = 'E'; }

	return 0;	// exception!
}


// pitch[0] = 계이름 C~B
// pitch[1] =  옥타브
// pitch[2] =  샾# 여부, 플랫b은 없다.
// pitch[3] = '\0'
const char* Converter::convertToPitch(char command_pitch, int oct) {
	char pitch[4];

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
		return 65.4064;
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

	return 0;	// exception!
}

const char* Converter::convertToRhythm(char command_rhythm, bool dotted) {

}