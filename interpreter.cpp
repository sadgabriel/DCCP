#include "interpreter.h"


void removeSpace(string& str) {
    // remove all space character from string.

    unsigned int i = 0;
    while (i < str.size()) {
        if (str[i] == ' ') {
            str.erase(i, 1);
        }
        else i++;
    }
}

Interpreter::Interpreter() {
    printSheet();
}

void Interpreter::pushOutput(string str) {
    outputs.push_back(str);
}

void Interpreter::pushOutput(const char* str) {
    string s{ str };
    pushOutput(s);
}

void Interpreter::printSheet() {
    system("cls");
    myprinter.print(octave, mode, mysheet);
    for (string output : outputs) {
        cout << output << endl;
    }
    cout << endl << "Enter Your Command." << endl;

    outputs.clear();
}

void Interpreter::execute(string command) {

    try {
        if (command[0] == ':' && executeKeywordCommand(command.substr(1))) {
            throw(1);
        }
        else {
            if (executeKeywordCommand(command))
                executeModeCommand(command);
        }
    }
    catch (...) {
        pushOutput("Invalid command.");
    }

    printSheet();
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

        if (user_commands.count(A) == 0)
            user_commands.insert(pair<string, string>(A, B));
        else throw(1);

        return 0;
    }


    removeSpace(command);
    // user-defined keyword handle
    if (user_commands.find(command) != user_commands.end()) {
        execute((*user_commands.find(command)).second);
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
                if (mysheet.getNote().is_NULL) goto END_LOOP;

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
    }
    else if (command == "od") {
        // octave down
        if (octave > 0) octave--;
    }
    else if (command.find("ot") == 0) {
        // octave to n
        int n = stoi(command.substr(2));
        if (n >= 0 && n <= 7) octave = n;
        else if (n > 7) octave = 7;
        else octave = 0;
    }

    // change BPM
    else if (command.find("BPM") == 0) {
        int new_bpm = stoi(command.substr(3));
        if (new_bpm > 0) mysheet.BPM = new_bpm;
    }
    else {
        return 1;
    }
    return 0;
}

void Interpreter::executeModeCommand(string command) {
    if (mode == REMOVE) {
        mysheet.remove(stoi(command));
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

                    
                    Note note;
                    if (mode == INSERT) {
                        note = mysheet.insert(myconverter.convertToPitch(pitch, temp_octave),
                            myconverter.convertToRhythm(rhythm, dot));
                    }
                    else if (mode == REPLACE) {
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