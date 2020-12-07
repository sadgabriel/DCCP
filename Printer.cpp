#include "Printer.h"

#define YELLOW 14
#define GRAY 8
#define CURSOR_COLOR YELLOW
#define EMPTY_COLOR GRAY

void Printer::print(int octave, int mode, Sheet& sheet) {
	// 0 삽입 모드
	// 1 대체 모드
	// 2 삭제 모드




	// 줄0
	// 타이틀
	std::cout << "DCCP: DGIST Convergence Composer Program" << std::endl;
	
	// 줄1
	std::cout << std::endl;

	// 줄2
	// 첫번째 윗쪽 경계 
	std::cout << "BPM: ";	// BPM,										5
	std::cout << std::setw(4) << std::left << sheet.BPM << ", ";	//	6

	std::cout << "Current Octave: ";								//	16
	std::cout << std::setw(2) << std::left << octave;				//	2

	if (mode == 0) {//삽입 초록 10
		printLine(3, 10);
	}
	if (mode == 1) {//대체 회색 8
		printLine(3, 8);
	}
	if (mode == 2) {// 삭제 빨강 12
		printLine(3, 12);
	}

	resetColor();
	if (mode == 0) {
		std::cout << std::setw(14) << std::left << " Mode: Insert";
	}
	else if (mode == 1) {
		std::cout << std::setw(14) << std::left  << " Mode: Replace";
	}
	else {
		std::cout << std::setw(14) << std::left  << " Mode: Remove";
	}

	if (mode == 0) {//삽입 초록 10
		printLine(74, 10);
	}
	if (mode == 1) {//대체 회색 8
		printLine(74, 8);
	}
	if (mode == 2) {// 삭제 빨강 12
		printLine(74, 12);
	}
	std::cout << std::endl;

	// 줄3
	std::cout << std::endl;

	// 줄4
	// 첫번째 Cursor 커서 줄
	std::cout << std::setw(8) << std::left << "Cursor";	//	8

	int cursor_pos = sheet.cursor.getPosition();

	for (int i = 0; i < 24; ++i) {						//	24*4 = 96
		if (i == cursor_pos) {
			setColor(CURSOR_COLOR);
			std::cout << "V   ";
			resetColor();
		}
		else {
			std::cout << "    ";
		}
	}
	std::cout << std::endl;

	// 줄5
	std::cout << std::endl;

	// 줄6
	// 첫번째 Order 순서 줄
	std::cout << std::setw(8) << std::left << "Order";	//	8
	for (int i = 0; i < 24; ++i) {						//	24*4 = 96
		if (i == cursor_pos) setColor(CURSOR_COLOR);
		std::cout << std::setw(4) << std::left << i;
		resetColor();
	}
	std::cout << std::endl;

	// 줄7
	std::cout << std::endl;

	// 줄8
	// 첫번째 Pitch 계이름 줄
	std::cout << std::setw(8) << std::left << "Pitch";			//	8

	// *중요* '커서'를 처음부터 움직여가면서 노트의 정보를 읽어온다.
	sheet.cursor.cs();
	for (int i = 0; i < 24; ++i) {								//	24*4 = 96
		if (sheet.cursor.getPosition() == cursor_pos) setColor(CURSOR_COLOR); // 커서가 가리키고 있으면 색을 변경.

		if (sheet.getNote().is_NULL == true) {
			setColor(EMPTY_COLOR);
			std::cout << "NUL ";			// 널노트의 계이름은 빈 공간.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
		}

		resetColor(); // 색을 원래대로 돌려둔다.
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 줄9
	std::cout << std::endl;

	// 줄10
	// 첫번째 박자 Rhythm 줄
	std::cout << std::setw(8) << std::left << "Rhythm";			//	8
		//  커서를 원위치 커서를 원위치 
	sheet.cursor.cs();
	for (int i = 0; i < 24; ++i) {								//	24*4 = 96
		if (sheet.cursor.getPosition() == cursor_pos) setColor(CURSOR_COLOR);

		if (sheet.getNote().is_NULL) {
			setColor(EMPTY_COLOR);
			std::cout << "0   ";
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
		}

		resetColor();
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 즐11
	std::cout << std::endl;

	// 줄12
	// 첫번째 아랫쪽 경계 줄
	if (mode == 0) {//삽입 초록 10
		printLine(120, 10);
	}
	if (mode == 1) {//대체 회색 8
		printLine(120, 8);
	}
	if (mode == 2) {// 삭제 빨강 12
		printLine(120, 12);
	}
	std::cout << std::endl;

	// 줄13
	std::cout << std::endl;

	// 줄14
	// 두번째 윗쪽 경계 줄
	if (mode == 0) {//삽입 초록 10
		printLine(120, 10);
	}
	if (mode == 1) {//대체 회색 8
		printLine(120, 8);
	}
	if (mode == 2) {// 삭제 빨강 12
		printLine(120, 12);
	}
	std::cout << std::endl;

	// 줄15
	std::cout << std::endl;

	// 줄16
	// 두번째 Cursor 커서 줄
	std::cout << std::setw(8) << std::left << "Cursor";	//	8
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		if (i == cursor_pos) {
			setColor(CURSOR_COLOR);
			std::cout << "V   ";
			resetColor();
		}
		else {
			std::cout << "    ";
		}
	}
	std::cout << std::endl;

	// 줄17
	std::cout << std::endl;

	// 줄18
	// 두번째 Order 순서 줄
	std::cout << std::setw(8) << std::left << "Order";	//	8
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		if (i == cursor_pos) setColor(CURSOR_COLOR);
		std::cout << std::setw(4) << std::left << i;
		resetColor();
	}	
	std::cout << std::endl;

	// 줄19
	std::cout << std::endl;

	// 줄20
	// 두번째 Pitch 계이름 줄
	std::cout << std::setw(8) << std::left << "Pitch";	//	8

	sheet.cursor.ct(24);
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		if (sheet.cursor.getPosition() == cursor_pos) setColor(CURSOR_COLOR);

		if (sheet.getNote().is_NULL == true) {
			setColor(EMPTY_COLOR);
			std::cout << "NUL ";			// 널노트의 계이름은 빈 공간.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
		}

		resetColor();
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 줄21
	std::cout << std::endl;

	// 줄22
	// 두번째 박자 Rhythm 줄
	std::cout << std::setw(8) << std::left << "Rhythm";	//	8

	sheet.cursor.ct(24);
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96

		if (sheet.cursor.getPosition() == cursor_pos) setColor(CURSOR_COLOR);
		if (sheet.getNote().is_NULL) {
			setColor(EMPTY_COLOR);
			std::cout << "0   ";
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
		}

		resetColor();
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 줄23
	std::cout << std::endl;

	// 줄24
	// 두번째 아랫쪽 경계 줄
	if (mode == 0) {//삽입 초록 10
		printLine(55, 10);
	}
	if (mode == 1) {//대체 회색 8
		printLine(55, 8);
	}
	if (mode == 2) {// 삭제 빨강 12
		printLine(55, 12);
	}
	std::cout << " page: ";												//	7
	std::cout << std::setw(3) << std::left << sheet.page.getPosition();	//	3

	if (mode == 0) {//삽입 초록 10
		printLine(55, 10);
	}
	if (mode == 1) {//대체 회색 8
		printLine(55, 8);
	}
	if (mode == 2) {// 삭제 빨강 12
		printLine(55, 12);
	}

	std::cout << std::endl;

	// 줄25
	std::cout << std::endl;


	// 커서 원위치 
	sheet.cursor.ct(cursor_pos);
}

// x is the column, y is the row. The origin (0,0) is top-left.
void Printer::setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

// 콘솔의 지정된 좌표에 txt를 업데이트 한다.
void Printer::printAt(const char* txt, int x, int y) {
	setCursorPosition(x, y);
	std::cout << txt;
}