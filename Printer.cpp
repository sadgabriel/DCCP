#include "Printer.h"

void Printer::print(int octave, int mode, Sheet& sheet) {
	// 0 ���� ���
	// 1 ��ü ���
	// 2 ���� ���




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

	if (mode == 0) {//���� �ʷ� 10
		printLine(3, 10);
	}
	if (mode == 1) {//��ü ȸ�� 8
		printLine(3, 8);
	}
	if (mode == 2) {// ���� ���� 12
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

	if (mode == 0) {//���� �ʷ� 10
		printLine(74, 10);
	}
	if (mode == 1) {//��ü ȸ�� 8
		printLine(74, 8);
	}
	if (mode == 2) {// ���� ���� 12
		printLine(74, 12);
	}
	std::cout << std::endl;

	// ��3
	std::cout << std::endl;

	// ��4
	// ù��° Cursor Ŀ�� ��
	std::cout << std::setw(8) << std::left << "Cursor";	//	8

	int cursor_pos = sheet.cursor.getPosition();

	for (int i = 0; i < 24; ++i) {						//	24*4 = 96
		if (i == cursor_pos) {
			setColor(14);
			std::cout << "V   ";
			resetColor();
		}
		else {
			std::cout << "    ";
		}
	}
	std::cout << std::endl;

	// ��5
	std::cout << std::endl;

	// ��6
	// ù��° Order ���� ��
	std::cout << std::setw(8) << std::left << "Order";	//	8
	for (int i = 0; i < 24; ++i) {						//	24*4 = 96
		std::cout << std::setw(4) << std::left << i;
	}
	std::cout << std::endl;

	// ��7
	std::cout << std::endl;

	// ��8
	// ù��° Pitch ���̸� ��
	std::cout << std::setw(8) << std::left << "Pitch";			//	8

	// *�߿�* 'Ŀ��'�� ó������ ���������鼭 ��Ʈ�� ������ �о�´�.
	sheet.cursor.cs();
	for (int i = 0; i < 24; ++i) {								//	24*4 = 96
		
		if (sheet.getNote().is_NULL == true) {
			std::cout << "NUL ";			// �γ�Ʈ�� ���̸��� �� ����.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// ��9
	std::cout << std::endl;

	// ��10
	// ù��° ���� Rhythm ��
	std::cout << std::setw(8) << std::left << "Rhythm";			//	8
		//  Ŀ���� ����ġ Ŀ���� ����ġ 
	sheet.cursor.cs();
	for (int i = 0; i < 24; ++i) {								//	24*4 = 96

		if (sheet.getNote().is_NULL) {
			std::cout << "0   ";
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// ��11
	std::cout << std::endl;

	// ��12
	// ù��° �Ʒ��� ��� ��
	if (mode == 0) {//���� �ʷ� 10
		printLine(120, 10);
	}
	if (mode == 1) {//��ü ȸ�� 8
		printLine(120, 8);
	}
	if (mode == 2) {// ���� ���� 12
		printLine(120, 12);
	}
	std::cout << std::endl;

	// ��13
	std::cout << std::endl;

	// ��14
	// �ι�° ���� ��� ��
	if (mode == 0) {//���� �ʷ� 10
		printLine(120, 10);
	}
	if (mode == 1) {//��ü ȸ�� 8
		printLine(120, 8);
	}
	if (mode == 2) {// ���� ���� 12
		printLine(120, 12);
	}
	std::cout << std::endl;

	// ��15
	std::cout << std::endl;

	// ��16
	// �ι�° Cursor Ŀ�� ��
	std::cout << std::setw(8) << std::left << "Cursor";	//	8
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		if (i == cursor_pos) {
			setColor(14);
			std::cout << "V   ";
			resetColor();
		}
		else {
			std::cout << "    ";
		}
	}
	std::cout << std::endl;

	// ��17
	std::cout << std::endl;

	// ��18
	// �ι�° Order ���� ��
	std::cout << std::setw(8) << std::left << "Order";	//	8
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96
		std::cout << std::setw(4) << std::left << i;
	}	
	std::cout << std::endl;

	// ��19
	std::cout << std::endl;

	// ��20
	// �ι�° Pitch ���̸� ��
	std::cout << std::setw(8) << std::left << "Pitch";	//	8

	sheet.cursor.ct(24);
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96

		if (sheet.getNote().is_NULL == true) {
			std::cout << "NUL ";			// �γ�Ʈ�� ���̸��� �� ����.
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getPitch();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// ��21
	std::cout << std::endl;

	// ��22
	// �ι�° ���� Rhythm ��
	std::cout << std::setw(8) << std::left << "Rhythm";	//	8

	sheet.cursor.ct(24);
	for (int i = 24; i < 48; ++i) {						//	24*4 = 96

		if (sheet.getNote().is_NULL) {
			std::cout << "0   ";
		}
		else {
			std::cout << std::setw(4) << std::left << sheet.getNote().getRhythm();
		}
		sheet.cursor.cr();
	}
	std::cout << std::endl;

	// ��23
	std::cout << std::endl;

	// ��24
	// �ι�° �Ʒ��� ��� ��
	if (mode == 0) {//���� �ʷ� 10
		printLine(55, 10);
	}
	if (mode == 1) {//��ü ȸ�� 8
		printLine(55, 8);
	}
	if (mode == 2) {// ���� ���� 12
		printLine(55, 12);
	}
	std::cout << " page: ";												//	7
	std::cout << std::setw(3) << std::left << sheet.page.getPosition();	//	3

	if (mode == 0) {//���� �ʷ� 10
		printLine(55, 10);
	}
	if (mode == 1) {//��ü ȸ�� 8
		printLine(55, 8);
	}
	if (mode == 2) {// ���� ���� 12
		printLine(55, 12);
	}

	std::cout << std::endl;

	// ��25
	std::cout << std::endl;


	// Ŀ�� ����ġ 
	sheet.cursor.ct(cursor_pos);
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