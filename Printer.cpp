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
		if (sheet.cursor.getPosition() == cursor_pos) setColor(CURSOR_COLOR); // Ŀ���� ����Ű�� ������ ���� ����.
		else setColor(sheet.getNote()->getColor());

		if (sheet.getNote()->is_NULL == true) {
			std::cout << "NUL ";			// �γ�Ʈ�� ���̸��� �� ����.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote()->getPitch();
		}

		resetColor(); // ���� ������� �����д�.
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
	// ��0
	// Ÿ��Ʋ
	std::cout << "DCCP: DGIST Convergence Composer Program" << std::endl;
	
	// ��1
	std::cout << std::endl;

	// ��2
	// ù��° ���� ��� 
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

	// ��3
	std::cout << std::endl;

	// ��4
	// ù��° Cursor Ŀ�� ��
	printCursorLine(0, 24, sheet);

	// ��5
	std::cout << std::endl;

	// ��6
	// ù��° Order ���� ��
	printOrderLine(0, 24, sheet);

	// ��7
	std::cout << std::endl;

	// ��8
	// ù��° Pitch ���̸� ��
	printPitchLine(0, 24, sheet);

	// ��9
	std::cout << std::endl;

	// ��10
	// ù��° ���� Rhythm ��
	printRhythmLine(0, 24, sheet);

	// ��11
	std::cout << std::endl;

	// ��12
	// ù��° �Ʒ��� ��� ��
	printLineByMode(120, mode);
	std::cout << std::endl;

	// ��13
	std::cout << std::endl;

	// ��14
	// �ι�° ���� ��� ��
	printLineByMode(120, mode);

	// ��15
	std::cout << std::endl;

	// ��16
	// �ι�° Cursor Ŀ�� ��
	printCursorLine(24, 48, sheet);

	// ��17
	std::cout << std::endl;

	// ��18
	// �ι�° Order ���� ��
	printOrderLine(24, 48, sheet);

	// ��19
	std::cout << std::endl;

	// ��20
	// �ι�° Pitch ���̸� ��
	printPitchLine(24, 48, sheet);

	// ��21
	std::cout << std::endl;

	// ��22
	// �ι�° ���� Rhythm ��
	printRhythmLine(24, 48, sheet);

	// ��23
	std::cout << std::endl;

	// ��24
	// �ι�° �Ʒ��� ��� ��
	printLineByMode(55, mode);
	
	std::cout << " page: ";												//	7
	std::cout << std::setw(3) << std::left << sheet.page.getPosition();	//	3

	printLineByMode(55, mode);

	std::cout << std::endl;

	// ��25
	std::cout << std::endl;


	// Ŀ�� ����ġ 
	sheet.ct(cursor_pos);
}

// x is the column, y is the row. The origin (0,0) is top-left.
void Printer::setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

// �ܼ��� ������ ��ǥ�� txt�� ������Ʈ �Ѵ�.
void Printer::printAt(const char* txt, int x, int y) {
	setCursorPosition(x, y);
	std::cout << txt;
}