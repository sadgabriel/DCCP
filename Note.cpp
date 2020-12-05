#include "Note.h"

//안_녕
// 문자열로 받은 계이름과 박자를 주파수와 밀리초 단위 길이로 환산하여 노트 객체를 생성한다.
Note::Note(int octave, char pitch, char rhythm) {
	// 문자 처리는 서브 함수에 맡김.

	// 옥타브 더해서 관리
	oct += octave;
	
	// 길이 
	length = rhythmToLength(rhythm) * 150;		//bpm = 200으로 가정

	// 만약 음표라면  
	if (pitch == '@' || pitch == ',') {
		freq = 0;
		is_rest = true;	// 음표 여부 
	}
	// 음표가 아니라 정상 음표라면
	else {
		// 주파수
		double double_freq = pitchToFreq(pitch);
		// 제곱과정 
		int square = 1;
		for (int i = 1; i < octave; ++i) {
			square *= 2;
		}
		freq = double_freq * square;

		is_rest = false; // 음표 여부 
	}
	is_NULL = false;	// 당연히 널노트 아님
	
	//'0' + a
	pit[1] = '0' + oct;
}

// 정수로 생성될 경우 바로 주파수와 길이에 대입한다.
Note::Note(int f, int l) {
	freq = f;
	length = l;

	is_NULL = false;
	is_rest = false; // 음표 여부 체크
}

void Note::beep() {
	if (is_NULL == true) {
		// do nothing
	}
	else {
		Beep(freq, length);
	}
}


// pit[0] = 계이름 C~B
// pit[1] =  옥타브
// pit[2] =  샾# 여부, 플랫b은 없다.
// pit[3] = '\0'
double Note::pitchToFreq(char pitch) {
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
		pit[1] = '#';
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
		pit[1] = '#';
		return 46.2493;
	}
	if (pitch == 'b') { 
		pit[0] = 'G';
		return 48.9994;
	}
	if (pitch == 'h') {  
		pit[0] = 'G'; 
		pit[1] = '#';
		return 51.9130;
	}
	if (pitch == 'n') { 
		pit[0] = 'A';
		return 55.0000;
	}
	if (pitch == 'j') {
		pit[0] = 'A';
		pit[1] = '#';
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
	if (pitch == 'o') {return 146.8324; oct += 2; pit[0] = 'D';
}
	if (pitch == '0'){return 155.5635; oct += 2; pit[0] = 'D'; pit[2] = '#'; }
	if (pitch == 'p') { return 164.8138; oct += 2; pit[0] = 'E'; }

	return 0;	// exception!
}

int Note::rhythmToLength(char rhythm) {
	if (rhythm == 'z') return 8;
	if (rhythm == 'x') return 4;
	if (rhythm == 'c') return 2;	// 300밀리초
	if (rhythm == 'v') return 1;	

	return 0;	// exception!
}


const char* Note::getPitch() {

	// 널노트라면
	if (is_NULL == true) {
		return "NUL\0";
	}
	// 음표라면 
	else if (is_rest == true) {
		return "@\0";
	}
	// 음표가 아니라면
	else {
		return pit;
	}
}

const char* Note::getLength() {

	// 널노트라면
	if (is_NULL == true) {
		return "0\0";
	}
	// 음표가 아니라면
	else {
		if (length == 1) {
			return "1/8\0";
		}
		else if (length == 2) {
			return "1/4\0";
		}
		else if (length == 4) {
			return "1/2\0";
		}
		else if (length == 8) {
			return "1/1\0";
		}
	}
}
