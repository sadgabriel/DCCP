#include "Player.h"

// 시트의 현재 페이지의 현재 커서의 노트 하나를 Beep한다.
void Player::playNote(Sheet& sheet) {
	Note playing_note = sheet.getNote();

	if (playing_note.is_NULL == true) {
		// do nothing
	}
	else {
		Beep(convertToFreq(playing_note.pitch), convertToMilisec(playing_note.rhythm, sheet.BPM));
	}
}

void Player::playNote(Note& note, int BPM) {
	if (!note.is_NULL) {
		Beep(convertToFreq(note.pitch), convertToMilisec(note.rhythm, BPM));
	}

}

int Player::convertToFreq(const char* pitch) {
	// length of pitch is 4
	// pitch[0] = 계이름 C~B
	// pitch[1] = 옥타브
	// pitch[2] = 샾# 여부, 플랫b은 없다.
	// pitch[3] = '\0'

	char tune = pitch[0];	// C, D, E, F, G, A, B. 도레미파솔라시.
	int octave = pitch[1] - '0';

	bool is_sharp;
	if (pitch[2] == '#') {
		is_sharp = true;
	}
	else {
		is_sharp = false;
	}

	int frequency = 0;
	// 옥타브가 1일 때 기준 음정의 주파수를 대입.
	if (tune == 'C') {
		if (is_sharp == false) frequency = (int)32.7032;
		else frequency = (int)34.6478;
	}
	else if (tune == 'D') {
		if (is_sharp == false) frequency = (int)36.7081;
		else frequency = (int)38.8909;		// # sharp
	}
	else if (tune == 'E') {
		if (is_sharp == false) frequency = (int)41.2034;
	}
	else if (tune == 'F') {
		if (is_sharp == false) frequency = (int)43.6535;
		else frequency = (int)46.2493;
	}
	else if (tune == 'G') {
		if (is_sharp == false) frequency = (int)48.9994;
		else frequency = (int)51.9130;
	}
	else if (tune == 'A') {
		if (is_sharp == false) frequency = (int)55.0000;
		else frequency = (int)58.2705;
	}
	else if (tune == 'B') frequency = (int)61.7354;
	else throw; // ERROR

	return frequency;
}




int Player::convertToMilisec(const char* rhythm, int BPM) {
	
	// <인수 rhythm>
	// rhythm[0] = 1
	// rhythm[1] = /
	// rhythm[2] = 4	(ex)
	// rhythm[3] = '\0' OR 6 when rhythm is 1/16. 점 음표라면 '*'이다.
	// rhythm[4] = '\0'


	// rhythm[0] = 1, rhythm[1] = / 이라고 가정.
	char temp1 = rhythm[2];	// 박자가 몇개의 단위 비트로 이루어져 있는지 판단하기 위해서.
	char temp2 = rhythm[3];


	// 점음표인지 판단한다.
	bool is_dotted;
	if (temp2 == '*') is_dotted = true;
	else is_dotted = false;


	//						  1/1   1/2   1/4   1/8   1/16
	bool rhythm_array[5] = { false,false,false,false,false };


	if ((temp1 == '1') && (temp2 != '6')) {	// 1/1
		rhythm_array[0] = true;
		if (is_dotted == true) {			// 1/1*
			rhythm_array[1] = true;
		}
	}
	else if (temp1 == '2') {		//	1/2
		rhythm_array[1] = true;
		if (is_dotted == true) {	//	1/2*
			rhythm_array[2] = true;
		}
	}
	else if (temp1 == '4') {
		rhythm_array[2] = true;
		if (is_dotted == true) {
			rhythm_array[3] = true;
		}
	}
	else if (temp1 == '8') {		// 1/8
		rhythm_array[3] = true;
		if (is_dotted == true) {
			rhythm_array[4] = true;
		}
	}
	else if ((temp1 == '1') && (temp2 == '6')) {	// 1/16
		rhythm_array[4] = true;
		if (is_dotted == true) {
			// This NEVER happen. 1/16*은 프로그램에서 지원하지 않는다.
			throw;
		}
	}
	// rhythm_array가 모두 false라면 이상한 상황.
	else {
		throw;
	}

	
	// 바로 위의 조건문 뭉치에서 구한 rhythm_array를 정수로 전환한다.
	int unit_bit_num = 0;		// 1단위 비트는 1/16박자이다. 1/32/박자는 현재의 구현에서 존재할 수도, 필요도 없다.

	// rhythm_array에서 루프를 돈다.
	for (int i = 0; i < 5; ++i) {
		int temp_unit_bit_num = 1;

		// REMEMBER Remember remember
		//							  1/1   1/2   1/4   1/8   1/16
		//	bool rhythm_array[5] = { false,false,false,false,false };
		//							  16     8     4     2     1  <== 단위 박자의 개수
		if (rhythm_array[i] == true) {
			// 2의 거듭제곱 구하기. unit_bit_num는 2^(4-i)가 된다.
			for (int j = 0; j < (4 - i); ++j) {
				temp_unit_bit_num *= 2;
			}
		}

		unit_bit_num += temp_unit_bit_num;		/// 1/16박자를 단위로한 음의 길이
	} // end for
	
	// 이제 BPM을 고려해서 실제로 사용되는 밀리초 단위의 정수를 구한다.
	// unit_bit_milisec은 프로그램에서 최소인 1/16박자의 실제 시간이다.
	
	// BPM은 노래의 속도를 나타내는 척도이다.
	// BPM의 정의는 1/4박자의 분당 개수이다. 따라서 클수록 같은 시간에 많은 박자(비트)의 음표가 연주된다.
	// BPM = 1분 / (1/4박자의 실제시간)으로 구한다. (1/4박자의 실제시간) = 1분 / BPM

	int unit_bit_milisec = 60000 / (BPM * 4);		// 1분은 6만 밀리초이다.
													// 1/16박자가 단위이므로 (1/16박자의 실제시간) = 1분 / (BPM * 4).

	int real_length = unit_bit_num * unit_bit_milisec;	// 음표의 길이는 (단위의 개수) * (단위시간)
}