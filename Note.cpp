#include "Note.h"


// 동적 할당 해제
Note::Note(int octave, char pitch, char rhythm) {
	// 문자 처리는 서브 함수에 맡김.

	// 옥타브 더해서 관리
	oct += octave;
	
	// 길이 
	length = rhythmToLength(rhythm) * lengthPerBit;

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
	// 길이가 0이면 NULL_Note이다.
	if (l == 0) {
		is_NULL = true;
	}
	else {
		is_NULL = false;
	}

	// 주파수가 0이면 음표이다.
	if (f == 0) {
		is_rest = true;
	}
	else {
		is_rest = false;
	}

	freq = f;
	length = l;
}

void Note::beep() {
	if (is_NULL == true) {
		// do nothing
	}
	else {
		Beep(freq, length);
	}
}




const char* Note::getPitch() {

	// 널노트라면, 만약 노트가 널이 동시에 음표라면 널이 먼저 처리된다.
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
		int bit_num = length / lengthPerBit;

		// 원래는 1/4박자를 기준으로 1로 해야하지만, 내부 구현은 가장 작은 1/8을 기준으로 하고 있다.
		// 추후 수정 필요
		if (bit_num == 1) {
			return "1/8\0";
		}
		else if (bit_num == 2) {
			return "1/4\0";
		}
		else if (bit_num == 4) {
			return "1/2\0";
		}
		else if (bit_num == 8) {
			return "1/1\0";
		}
		else {
			return "ERR\0";
		}
	}
}



// 노트가 사용가능 한 상태인지(에러가 없는 상태인지) 검사한다.
// 문제가 있다면 throw. 예외 처리를 기대하진 않는다.
void Note::validate() {
	if (freq >= 0) throw;
	if (length >= 0) throw;

	if (is_NULL == true) {
		if (length != 0) throw;
	}

	if (is_rest == true) {
		if (freq != 0) throw;
	}
}