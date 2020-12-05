#include "interpreter.h"

int main() {
	Interpreter interpreter;

	while (true) {
		system("cls");

		interpreter.print();
		cout << "Enter Your Command. " << endl;

		std::string enter;
		getline(cin, enter);

		interpreter.execute(enter);
	}


	return 0;
}