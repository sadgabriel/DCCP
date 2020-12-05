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

void Interpreter::print() {
    //myprinter.print(octave, mycursor, mypage, mysheet);
}

void Interpreter::execute(string command) {

    if (command[0] == ':') {
        executeKeywordCommand(command.substr(1));
    }
    else {
        executeModeCommand(command);
    }
}

void Interpreter::executeKeywordCommand(string command) {
    // define command
    if (command.find("define") == 0) {
        // define A B
        string A;
        string B;
        unsigned int i = 6;

        while (i < command.size() && command[i] == ' ') i++;

        while (i < command.size() && command[i] != ' ') {
            A.append(command.substr(i, 1));
        }

        if (i < command.size())
            B.append(command.substr(i));
        else throw(invalid_argument("error from define"));

        if (user_commands.count(A) == 0)
            user_commands.insert(pair<string, string>(A, B));
        else throw(invalid_argument("error from define"));

        return;
    }
    

    removeSpace(command);
    
    // pre-defined keyword handle
    // cursor command
    if (command == "cs") {
        // cursor start
        mysheet.cursor.cs();
    }
    else if (command == "ce") {
        // cursor end
        mysheet.cursor.ce();
    }
    else if (command.find("ct") == 0) {
        // cursor to n
        mysheet.cursor.ct(stoi(command.substr(2)));
    }
    else if (command.find("cr") == 0) {
        // cursor right
        // cursor right n
        if (command.size() == 2) mysheet.cursor.cr();
        else mysheet.cursor.cr(stoi(command.substr(2)));
    }
    else if (command.find("cl") == 0) {
        // cursor left
        // cursor left n
        if (command.size() == 2) mysheet.cursor.cl();
        else mysheet.cursor.cl(stoi(command.substr(2)));
    }

    // page command
    
    else if (command == "pr") {
        // page right
        mysheet.page.pr();
    }
    else if (command == "pl") {
        // page left
        mysheet.page.pl();
    }
    else if (command.find("pt") == 0) {
        // page to n
        mysheet.page.pt(stoi(command.substr(2)));
    }
    else if (command == "ps") {
        // page start
        mysheet.page.ps();
    }
    else if (command == "pe") {
        // page end
        mysheet.page.pe();
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

    // system
    else if (command == "exit") {
        exit(0);
    }
    else if (command == "play") {
        // play the music
        // myplayer.play(octave, mycursor, mypage, mysheet, myprinter);
    }
    else if (command.find("save") == 0) {
        mysaveloader.save(command.substr(4), mysheet);
    }
    else if (command.find("load") == 0) {
        mysaveloader.load(command.substr(4), mysheet);
    }
    

    // user-defined keyword handle
    else if (user_commands.find(command) != user_commands.end()) {
        execute((*user_commands.find(command)).second);
    }
    


}

void Interpreter::executeModeCommand(string command) {
    if (mode == REMOVE) {
        mysheet.remove(stoi(command));
    }
    else {

        int phase = 0, temp_octave;
        char pitch = '\0', rhythm = '\0';

        for (char c : command) {
            if (phase == 0) {
                pitch = c;
                phase++;
                temp_octave = octave;
            }
            else if (phase == 1) {
                if (c == '+') temp_octave++;
                else if (c == '-') temp_octave--;
                else {
                    rhythm = c;

                    if (mode == INSERT) {
                        Note note = mysheet.insert(myconverter.convertToPitch(pitch, temp_octave),
                            myconverter.convertToRhythm(rhythm, temp_octave));

                        myplayer.playNote(note);
                    }
                    else if (mode == REPLACE) {
                        Note note = mysheet.replace(myconverter.convertToPitch(pitch, temp_octave), 
                            myconverter.convertToRhythm(rhythm, temp_octave));

                        myplayer.playNote(note);
                    }
                    phase--;
                }
            }
        }
    }
}