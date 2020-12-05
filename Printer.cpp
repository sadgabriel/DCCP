#include "Printer.h"

void Printer::print(int octave, Sheet& sheet) {
	
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

	for (int i = 0; i < 91; ++i) {
		std::cout << '-';
	}
	std::cout << std::endl;

	// 줄3
	std::cout << std::endl;

	// 줄4
	// 첫번째 Cursor 커서 줄
	std::cout << std::setw(8) << std::left << "Cursor";	//	8

	int pos = sheet.cursor.getPosition();
	for (int i = 0; i < 24; ++i) {						//	24*4 = 96
		if (i == pos) {
			std::cout << "V   ";
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
		std::cout << std::setw(4) << std::left << i;
	}
	std::cout << std::endl;

	// 줄7
	std::cout << std::endl;

	// 줄8
	// 첫번째 Pitch 계이름 줄
	std::cout << std::setw(8) << std::left << "Pitch";			//	8

	for (int i = 0; i < 24; ++i) {								//	24*4 = 96
		Note cur_note = sheet.getNote();

		if (cur_note.is_NULL == true) {
			std::cout << "    ";			// 널노트의 계이름은 빈 공간.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 줄9
	std::cout << std::endl;

	// 줄10
	// 첫번째 박자 Rhythm 줄
	std::cout << std::setw(8) << std::left << "Rhythm";			//	8
	for (int i = 0; i < 24; ++i) {								//	24*4 = 96
		if (sheet.getNote().is_NULL) {
			std::cout << "    ";
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 즐11
	std::cout << std::endl;

	// 줄12
	// 첫번째 아랫쪽 경계 줄
	for (int i = 0; i < 120; ++i) {
		std::cout << '-';
	}
	std::cout << std::endl;

	// 줄13
	std::cout << std::endl;

	// 줄14
	// 두번째 윗쪽 경계 줄
	for (int i = 0; i < 120; ++i) {
		std::cout << '-';
	}
	std::cout << std::endl;

	// 줄15
	std::cout << std::endl;

	// 줄16
	// 두번째 Cursor 커서 줄
	std::cout << std::setw(8) << std::left << "Cursor";	//	8
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		if (i == sheet.cursor.getPosition()) {
			std::cout << "V   ";
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
		std::cout << std::setw(4) << std::left << i;
	}	
	std::cout << std::endl;

	// 줄19
	std::cout << std::endl;

	// 줄20
	// 두번째 Pitch 계이름 줄
	std::cout << std::setw(8) << std::left << "Pitch";	//	8
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		Note cur_note = sheet.getNote();

		if (cur_note.is_NULL == true) {
			std::cout << "    ";			// 널노트의 계이름은 빈 공간.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 줄21
	std::cout << std::endl;

	// 줄22
	// 두번째 박자 Rhythm 줄
	std::cout << std::setw(8) << std::left << "Rhythm";	//	8
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		if (sheet.getNote().is_NULL) {
			std::cout << "    ";
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// 줄23
	std::cout << std::endl;

	// 줄24
	// 두번째 아랫쪽 경계 줄
	for (int i = 0; i < 55; ++i) {										// 55
		std::cout << '-';
	}

	std::cout << " page: ";												//	7
	std::cout << std::setw(3) << std::left << sheet.page.getPosition();	//	3

	for (int i = 0; i < 55; ++i) {										// 55
		std::cout << '-';
	}

	std::cout << std::endl;

	// 줄25
	std::cout << std::endl;
}

// x is the column, y is the row. The origin (0,0) is top-left.
void Printer::setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}