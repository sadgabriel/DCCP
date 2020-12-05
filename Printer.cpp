#include "Printer.h"

void Printer::print(int octave, Sheet& sheet) {
	
	// 줄0
	// 타이틀
	std::cout << "DCCP: DGIST Convergence Composer Program" << std::endl;
	
	// 줄1
	std::cout << std::endl;

	// 줄2
	// 첫번째 윗쪽 경계 
	std::cout << std::setw(11) << std::left << "BPM: " << sheet.BPM << ", ";
	std::cout << std::setw(16) << std::left << "Current Octave: " << std::setw(2) << std::left  << octave;
	for (int i = 0; i < 90; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 첫번째 Cursor 커서 줄
	std::cout << std::setw(8) << std::left << "Cursor";
	int pos = sheet.cursor.getPosition();
	for (int i = 0; i < 24; ++i) {
		if (i == pos) {
			std::cout << "V   ";
		}
		else {
			std::cout << "    ";
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;


	// 첫번째 Order 순서 줄
	std::cout << std::setw(8) << std::left << "Order";
	for (int i = 0; i < 24; ++i) {
		std::cout << std::setw(4) << std::left << i;
	}	

	std::cout << std::endl;
	std::cout << std::endl;

	// 첫번째 Pitch 계이름 줄
	std::cout << std::setw(8) << std::left << "Pitch";
	for (int i = 0; i < 24; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 첫번째 length 길이 줄
	std::cout << std::setw(8) << std::left << "Rhythm";
	for (int i = 0; i < 24; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 첫번째 아랫쪽 경계 줄
	for (int i = 0; i < 119; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;
	std::cout << std::endl;

	
	// 두번째 윗쪽 경계 줄
	for (int i = 0; i < 119; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 두번째 Cursor 커서 줄
	std::cout << std::setw(8) << std::left << "Cursor";
	for (int i = 24; i < 48; ++i) {
		if (i == sheet.cursor.getPosition()) {
			std::cout << "V   ";
		}
		else {
			std::cout << "    ";
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;


	// 두번째 Order 순서 줄
	std::cout << std::setw(8) << std::left << "Order";
	for (int i = 24; i < 48; ++i) {
		std::cout << std::setw(4) << std::left << i;
	}	

	std::cout << std::endl;
	std::cout << std::endl;

	// 두번째 Pitch 계이름 줄
	std::cout << std::setw(8) << std::left << "Pitch";
	for (int i = 24; i < 48; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 두번째 length 길이 줄
	std::cout << std::setw(8) << std::left << "Rhythm";
	for (int i = 24; i < 48; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 두번째 아랫쪽 경계 줄
	for (int i = 0; i < 53; ++i) {
		std::cout << '-';
	}
	std::cout << std::setw(7) << std::left << " page: " << std::setw(5) << std::left << sheet.page.getPosition();
	for (int i = 0; i < 54; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;
}

// x is the column, y is the row. The origin (0,0) is top-left.
void Printer::setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}