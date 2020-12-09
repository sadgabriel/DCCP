#include "interpreter.h"

int main() {
	Interpreter* interpreter = new Interpreter; // 인터프리터를 생성한다.

	while (true) {
		std::string command;
		getline(cin, command); // 명령을 string으로 받아서

		interpreter->execute(command); // 인터프리터의 execute 함수에 넣는다.

	}
	return 0;
}