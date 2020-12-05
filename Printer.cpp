#include "Printer.h"

void Printer::print(int octave, Cursor& cursor, Page& page, Sheet& sheet) {
	
	// 타이틀
	std::cout << "DCCP: DGIST Convergence Composer Program" << std::endl;

	std::cout << std::endl;

	// 윗쪽 경계 줄1
	std::cout << std::setw(11) << std::left << "BPM: 200, ";
	std::cout << std::setw(16) << std::left << "Current Octave: " << std::setw(2) << std::left  << octave;
	for (int i = 0; i < 90; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// Cursor 커서 줄1
	std::cout << std::setw(8) << std::left << "Cursor";
	int pos = cursor.getPosition();
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


	// Order 순서 줄1
	std::cout << std::setw(8) << std::left << "Order";
	for (int i = 0; i < 24; ++i) {
		std::cout << std::setw(4) << std::left << i;
	}	

	std::cout << std::endl;
	std::cout << std::endl;

	// Pitch 계이름 줄1
	std::cout << std::setw(8) << std::left << "Pitch";
	for (int i = 0; i < 24; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote(i, page).getPitch();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// length 길이 줄1
	std::cout << std::setw(8) << std::left << "Length";
	for (int i = 0; i < 24; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote(i, page).getLength();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 아랫쪽 경계 줄1
	for (int i = 0; i < 119; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;
	std::cout << std::endl;

	
	// 윗쪽 경계 줄2
	for (int i = 0; i < 119; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// Cursor 커서 줄2
	std::cout << std::setw(8) << std::left << "Cursor";
	for (int i = 24; i < 48; ++i) {
		if (i == cursor.getPosition()) {
			std::cout << "V   ";
		}
		else {
			std::cout << "    ";
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;


	// Order 순서 줄2
	std::cout << std::setw(8) << std::left << "Order";
	for (int i = 24; i < 48; ++i) {
		std::cout << std::setw(4) << std::left << i;
	}	

	std::cout << std::endl;
	std::cout << std::endl;

	// Pitch 계이름 줄2
	std::cout << std::setw(8) << std::left << "Pitch";
	for (int i = 24; i < 48; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote(i, page).getPitch();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// length 길이 줄2
	std::cout << std::setw(8) << std::left << "Length";
	for (int i = 24; i < 48; ++i) {
		std::cout << std::setw(4) << std::left << sheet.getNote(i, page).getLength();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 아랫쪽 경계 줄2
	for (int i = 0; i < 53; ++i) {
		std::cout << '-';
	}
	std::cout << std::setw(7) << std::left << " page: " << std::setw(5) << std::left << page.getPosition();
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