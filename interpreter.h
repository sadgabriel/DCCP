#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <map>

#include "cursor.h"
#include "page.h"
#include "Sheet.h"
#include "Printer.h"
#include "Player.h"
#include "SaveLoader.h"
#include "Converter.h"

#define INSERT 0
#define REPLACE 1
#define REMOVE 2

using namespace std;

class Interpreter {
public:
    void execute(string command);
    void print();
private:
    Sheet mysheet;
    Printer myprinter;
    Player myplayer;
    SaveLoader mysaveloader;
    Converter myconverter;

    int mode = INSERT;
    int octave = 4; // 1 ~ 7

    map<string, string> user_commands;

    void executeKeywordCommand(string command);
    void executeModeCommand(string command);

};