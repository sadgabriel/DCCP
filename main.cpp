#include "interpreter.h"

int main() {
	Interpreter interpreter;

	system("cls");
	interpreter.print();
	cout << "Enter Your Command. " << endl;

	while (true) {
		std::string enter;
		getline(cin, enter);

		interpreter.execute(enter);
	}


	return 0;
}