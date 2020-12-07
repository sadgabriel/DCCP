#include "interpreter.h"

int main() {
	Interpreter* interpreter = new Interpreter;

	while (true) {
		std::string command;
		getline(cin, command);

		interpreter->execute(command);
	}
	return 0;
}