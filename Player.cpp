#include "Player.h"

void Player::play(int octave, Cursor& cursor, Page& page, Sheet& sheet, Printer& printer) {

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
