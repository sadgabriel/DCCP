#include "interpreter.h"


void removeSpace(string& str) {
    // 문자열의 공백을 제거한다.

    unsigned int i = 0;
    while (i < str.size()) {
        if (str[i] == ' ') {
            str.erase(i, 1);
        }
        else i++;
    }
}

Interpreter::Interpreter() { // 생성될 때 프린트를 한 번 해준다.
    printSheet();
}

void Interpreter::pushOutput(string& str) { // output에 문자열을 넣는다.
    outputs.push_back(str);
}

void Interpreter::pushOutput(const char* str) { // output에 문자열을 넣는다. 2
    string s{ str };
    pushOutput(s);
}

void Interpreter::printSheet() {
    system("cls"); // 창을 지우고
    myprinter.print(octave, mode, mysheet); // sheet를 출력하고
    for (string output : outputs) {
        cout << output << endl; // output 안의 string들을 차례로 출력하고
    }
    cout << endl << "Enter Your Command." << endl; // 커맨드를 입력받는다고 출력한다.

    outputs.clear(); // output을 비운다.
}

void Interpreter::execute(string command) { // 명령을 실행한다.

    try {
        if (command[0] == ':') {
            if (executeKeywordCommand(command.substr(1))) throw(1);
        }
        else if (command[0] == '/') {
            if (executeHelpCommand(command.substr(1))) throw (1);
        }
        else {
            if (executeKeywordCommand(command)) {
                executeModeCommand(command);
            }
        }
    }
    catch (int a) {
        if (a == 1) pushOutput("Invalid command.");
        else pushOutput("something worng");
    }

    catch (...) {
        pushOutput("Crash");
    }

    printSheet(); // 화면을 갱신한다.
}
int Interpreter::executeHelpCommand(string command) {
    string helpcommand = myhelper.whatCommand(command);
    pushOutput(helpcommand);
    return 0;
}

int Interpreter::executeKeywordCommand(string command) {
    // define command
    if (command.find("define") == 0) {
        // define A B
        string A;
        string B;
        unsigned int i = 6;

        while (i < command.size() && command[i] == ' ') i++;

        while (i < command.size() && command[i] != ' ') {
            A.append(command.substr(i, 1));
            i++;
        }

        if (i < command.size())
            B.append(command.substr(i));
        else throw(1);
        
        removeSpace(B);

        if (user_commands.count(A) == 0)
            user_commands.insert(pair<string, string>(A, B));
        else throw(1);

        return 0;
    }


    removeSpace(command);
    // user-defined keyword handle
    if (user_commands.find(command) != user_commands.end()) {
        executeModeCommand((*user_commands.find(command)).second);
    }

    // pre-defined keyword handle

    // system
    else if (command == "exit") {
        exit(0);
    }
    else if (command == "play") {
        int original_cursor_pos = mysheet.cursor.getPosition();
        int original_page_pos = mysheet.page.getPosition();

        mysheet.cs();
        mysheet.ps();

        for (int page_idx = 0; page_idx < 30; page_idx++) {
            for (int cursor_idx = 0; cursor_idx < 48; cursor_idx++) {
                if (mysheet.getNote()->is_NULL) goto END_LOOP;

                myplayer.playNote(mysheet);

                mysheet.cr();
                printSheet();
            }
            mysheet.cs();
        }
    END_LOOP:

        mysheet.ct(original_cursor_pos);
        mysheet.pt(original_page_pos);
    }
    else if (command.find("save") == 0) {
        string filename;

        if (command.size() >= 5) {
            filename = command.substr(4);
            removeSpace(filename);
        }

        mysaveloader.save(filename, mysheet);
    }
    else if (command.find("load") == 0) {
        if (command.size() >= 5) {
            string filename = command.substr(4);
            removeSpace(filename);
            mysaveloader.load(command.substr(4), mysheet);
        }
        else throw(1);
    }
    else if (command.find("color") == 0) {
        mysheet.getNote()->setColor(stoi(command.substr(5)));
    }

    // cursor command
    else if (command == "cs") {
        // cursor start
        mysheet.cs();
    }
    else if (command == "ce") {
        // cursor end
        mysheet.ce();
    }
    else if (command.find("ct") == 0) {
        // cursor to n
        mysheet.ct(stoi(command.substr(2)));
    }
    else if (command.find("cr") == 0) {
        // cursor right
        // cursor right n
        if (command.size() == 2) mysheet.cr();
        else mysheet.cr(stoi(command.substr(2)));
    }
    else if (command.find("cl") == 0) {
        // cursor left
        // cursor left n
        if (command.size() == 2) mysheet.cl();
        else mysheet.cl(stoi(command.substr(2)));
    }

    // page command
    else if (command.find("pr") == 0) {
        // page right
        if (command.size() == 2) mysheet.pr();
        else mysheet.pr(stoi(command.substr(2)));
    }
    else if (command.find("pl") == 0) {
        // page left
        if (command.size() == 2) mysheet.pl();
        else mysheet.pl(stoi(command.substr(2)));
    }
    else if (command.find("pt") == 0) {
        // page to n
        mysheet.pt(stoi(command.substr(2)));
    }
    else if (command == "ps") {
        // page start
        mysheet.ps();
    }
    else if (command == "pe") {
        // page end
        mysheet.pe();
    }


    // mode-change command
    else if (command == "++") {
        // insert mode
        mode = INSERT;
    }
    else if (command == "**") {
        // replace mode
        mode = REPLACE;
    }
    else if (command == "--") {
        // remove mode
        mode = REMOVE;
    }

    // octave command
    else if (command == "ou") {
        // octave up
        if (octave < 7) octave++;
        else {
            pushOutput("maximum octave");
        }
    }
    else if (command == "od") {
        // octave down
        if (octave > 0) octave--;
        else {
            pushOutput("minimum octave");
        }
    }
    else if (command.find("ot") == 0) {
        // octave to n
        int n = stoi(command.substr(2));
        if (n >= 0 && n <= 7) octave = n;
        else {
            pushOutput("Octave range exceed");
        }
    }
    else if (command.find("BPM") == 0) {
        int new_bpm = stoi(command.substr(3));
        if (new_bpm > 0) mysheet.BPM = new_bpm;
        else {
            pushOutput("bpm cannot go below zero");
        }
    }
    else return 1; // 어떤 키워드와도 일치하지 않음.

    return 0; 
}

void Interpreter::executeModeCommand(string command) {
    if (mode == REMOVE) {
        try {
            mysheet.remove(stoi(command));
        }
        catch (...) {
            throw(1);
        }
    }
    else {

        int phase = 0, temp_octave;
        char pitch = '\0', rhythm = '\0';
        bool dot = false;

        for (unsigned int i = 0; i < command.size(); i++) {
            if (phase == 0) {
                temp_octave = octave;
                pitch = rhythm = '\0';

                pitch = command[i];
                phase++;
            }
            else if (phase == 1) {
                if (command[i] == '+') {
                    temp_octave++;
                }
                else if (command[i] == '-') {
                    temp_octave--;
                }
                else {
                    rhythm = command[i];

                    if (command.size() > i + 1 && (command[i + 1] == '.' || command[i + 1] == '*')) {
                        dot = true;
                        i++;
                        
                    }
                    else {
                        dot = false;
                    }

                    
                    Note* note;
                    if (mode == INSERT) {
                        note = mysheet.insert(myconverter.convertToPitch(pitch, temp_octave),
                            myconverter.convertToRhythm(rhythm, dot));
                    }
                    else{
                        note = mysheet.replace(myconverter.convertToPitch(pitch, temp_octave),
                            myconverter.convertToRhythm(rhythm, dot));
                    }

                    myplayer.playNote(note, mysheet.BPM);
                    phase--;
                }
            }
        }
        if (phase == 1) throw(1);
    }
}