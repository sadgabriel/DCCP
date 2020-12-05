#include "Player.h"

void Player::playNote(const Sheet& sheet) {

	page.ps();
	int end_page = 1;

	for (int i = 0; i < end_page; ++i) {
		cursor.cs();

		for (int j = 0; j < 48; ++j) {

			system("cls");
			printer.print(octave, cursor, page, sheet);
			sheet.getNote().beep();
			if (j != 47) {
				cursor.cr();
			}
		}

		if (i != end_page) {
			page.pr();
		}
	}

	// 재생이 끝나면 악보의 처음으로 돌아간다. 도담록:처음이 아니라 커서 있던곳으로 가면 안되용?
	// 남현우: 그러면 안됩니다. 그렇게 하려면 커서의 기존 위치를 저장해야 정수형으로 저장해야 합니다.
	// 정수형을 저장하려면 4바이트가 필요합니다, 하지만 그러면 저희는 메모리를 아껴써야합니다.
	// 1234
	page.ps();
	cursor.cs();
	system("cls");
	printer.print(octave, cursor, page, sheet);
}


int Player::convertToFreq(char* pitch) {
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

	int frequency;
	// 옥타브가 1일 때 기준 음정의 주파수를 대입.
	if (tune == 'C') {
		if (is_sharp == false) frequency = 32.7032;
		else frequency = 34.6478;
	}
	else if (tune == 'D') {
		if (is_sharp == false) frequency = 36.7081;
		else frequency = 38.8909;		// # sharp
	}
	else if (tune == 'E') {
		if (is_sharp == false) frequency = 41.2034;
	}
	else if (tune == 'F') {
		if (is_sharp == false) frequency = 43.6535;
		else frequency = 46.2493;
	}
	else if (tune == 'G') {
		if (is_sharp == false) frequency = 48.9994;
		else frequency = 51.9130;
	}
	else if (tune == 'A') {
		if (is_sharp == false) frequency = 55.0000;
		else frequency = 58.2705;
	}
	else if (tune == 'B') frequency = 61.7354;
	else throw; // ERROR

}
int Player::convertToMilisec(char* rhythm, int BPM) {
	// rhythm[0] = 1
	// rhythm[1] = /
	// rhythm[2] = 4	(ex)
	// rhythm[3] = '\0' OR 6 when rhythm is 1/16. 점 음표라면 '*'이다.
	// rhythm[4] = '\0'
	

	//						  1/1   1/2   1/4   1/8   1/16
	bool rhythm_array[5] = { false,false,false,false,false };

	// rhythm[0] = 1, rhythm[1] = / 이라고 가정.
	char temp1 = rhythm[2];	// 박자가 몇개의 단위 비트로 이루어져 있는지 판단하기 위해서.
	char temp2 = rhythm[3];


	// 점음표인지 판단한다.
	bool is_dotted;
	if (temp2 == '*') is_dotted = true;
	else is_dotted = false;


	// 박자를 단위 비트 수로 전환한다.
	int unit_bit_num;	// 단위 비트 수

	if ((temp1 == '1') && (temp2 != '6')) {
	}
	if(temp1 == '2')
	if(temp1 == '4')
	if(temp1 == '8')

	if(temp2 == '6')
	if(temp2 == '*')
}