#include "Printer.h"
#include "color.h"


void Printer::printCursorLine(int start, int end, Sheet& sheet) {
	std::cout << std::setw(8) << std::left << "Cursor";	//	8

	for (int i = start; i < end; ++i) {						//	24*4 = 96
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
}


void Printer::printOrderLine(int start, int end, Sheet& sheet) {
	std::cout << std::setw(8) << std::left << "Order";	//	8
	for (int i = start; i < end; ++i) {						//	24*4 = 96
		if (i == cursor_pos) setColor(CURSOR_COLOR);
		std::cout << std::setw(4) << std::left << i;
		resetColor();
	}
	std::cout << std::endl;
}

void Printer::printPitchLine(int start, int end, Sheet& sheet) {
	std::cout << std::setw(8) << std::left << "Pitch";			//	8

	sheet.ct(start);
	for (int i = start; i < end; ++i) {								//	24*4 = 96
		if (sheet.cursor.getPosition() == cursor_pos) setColor(CURSOR_COLOR); // 커서가 가리키고 있으면 색을 변경.
		else setColor(sheet.getNote()->getColor());

		if (sheet.getNote()->is_NULL == true) {
			std::cout << "NUL ";			// 널노트의 계이름은 빈 공간.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote()->getPitch();
		}

		resetColor(); // 색을 원래대로 돌려둔다.
		sheet.cr();
	}
	std::cout << std::endl;
}

void Printer::printRhythmLine(int start, int end, Sheet& sheet) {
	std::cout << std::setw(8) << std::left << "Rhythm";			//	8
	sheet.ct(start);
	for (int i = start; i < end; ++i) {								//	24*4 = 96
		if (sheet.cursor.getPosition() == cursor_pos) setColor(CURSOR_COLOR);
		else setColor(sheet.getNote()->getColor());
		if (sheet.getNote()->is_NULL) {
			std::cout << "NUL ";
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote()->getRhythm();
		}

		resetColor();
		sheet.cr();
	}
	std::cout << std::endl;
}

void Printer::print(int octave, int mode, Sheet& sheet) {

	cursor_pos = sheet.cursor.getPosition();
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

	printLineByMode(3, mode);

	if (mode == INSERT) {
		std::cout << std::setw(14) << std::left << " Mode: Insert";
	}
	if (mode == REPLACE) {
		std::cout << std::setw(14) << std::left << " Mode: Replace";
	}
	if (mode == REMOVE) {
		std::cout << std::setw(14) << std::left << " Mode: Remove";
	}

	printLineByMode(74, mode);

	std::cout << std::endl;

	// 줄3
	std::cout << std::endl;

	// 줄4
	// 첫번째 Cursor 커서 줄
	printCursorLine(0, 24, sheet);

	// 줄5
	std::cout << std::endl;

	// 줄6
	// 첫번째 Order 순서 줄
	printOrderLine(0, 24, sheet);

	// 줄7
	std::cout << std::endl;

	// 줄8
	// 첫번째 Pitch 계이름 줄
	printPitchLine(0, 24, sheet);

	// 줄9
	std::cout << std::endl;

	// 줄10
	// 첫번째 박자 Rhythm 줄
	printRhythmLine(0, 24, sheet);

	// 즐11
	std::cout << std::endl;

	// 줄12
	// 첫번째 아랫쪽 경계 줄
	printLineByMode(120, mode);
	std::cout << std::endl;

	// 줄13
	std::cout << std::endl;

	// 줄14
	// 두번째 윗쪽 경계 줄
	printLineByMode(120, mode);

	// 줄15
	std::cout << std::endl;

	// 줄16
	// 두번째 Cursor 커서 줄
	printCursorLine(24, 48, sheet);

	// 줄17
	std::cout << std::endl;

	// 줄18
	// 두번째 Order 순서 줄
	printOrderLine(24, 48, sheet);

	// 줄19
	std::cout << std::endl;

	// 줄20
	// 두번째 Pitch 계이름 줄
	printPitchLine(24, 48, sheet);

	// 줄21
	std::cout << std::endl;

	// 줄22
	// 두번째 박자 Rhythm 줄
	printRhythmLine(24, 48, sheet);

	// 줄23
	std::cout << std::endl;

	// 줄24
	// 두번째 아랫쪽 경계 줄
	printLineByMode(55, mode);
	
	std::cout << " page: ";												//	7
	std::cout << std::setw(3) << std::left << sheet.page.getPosition();	//	3

	printLineByMode(55, mode);

	std::cout << std::endl;

	// 줄25
	std::cout << std::endl;


	// 커서 원위치 
	sheet.ct(cursor_pos);
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