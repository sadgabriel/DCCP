#include "interpreter.h"

int main() {
	Interpreter* interpreter = new Interpreter; // ���������͸� �����Ѵ�.

	while (true) {
		std::string command;
		getline(cin, command); // ����� string���� �޾Ƽ�

		interpreter->execute(command); // ������������ execute �Լ��� �ִ´�.

	}
	return 0;
}