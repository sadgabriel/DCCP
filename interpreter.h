#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <map>
#include <cassert>

#include "cursor.h"
#include "page.h"
#include "Sheet.h"
#include "Printer.h"
#include "Player.h"
#include "SaveLoader.h"
#include "Converter.h"
#include "helper.h"

#define INSERT 0
#define REPLACE 1
#define REMOVE 2

using namespace std;

class Interpreter {
public:
    Interpreter();
    void execute(string command);

private:
    Sheet mysheet;
    Printer myprinter;
    Player myplayer;
    SaveLoader mysaveloader;
    Converter myconverter;
    Helper myhelper;
    vector<string> outputs;

    int mode = INSERT;
    int octave = 4; // 1 ~ 7

    map<string, string> user_commands;

    // insert string into outputs
    void pushOutput(string&); 
    void pushOutput(const char*);

    // print mysheet and outputs on screen
    void printSheet(); 

    // execute command as keyword command. if fails, return 1. else 0.
    int executeKeywordCommand(string command);

    // execute user-defined command. if fails, return 1. else 0.
    int executeUserCommand(string command);

    // execute command as Help command. if fails, return 1. else 0.
    int executeHelpCommand(string command);

    // execute command as Mode command (insert, remove, replace). if fails, throw 1.
    void executeModeCommand(string command);
};