#include "SaveLoader.h"



void SaveLoader::save(std::string filename, Sheet& mysheet) {
    std::ofstream output(filename, std::ios::out);
    
    mysheet.cursor.cs();
    mysheet.page.ps();
    for (int page_idx = 0; page_idx < 30; page_idx++) {
        for (int cursor_idx = 0; cursor_idx < 48; cursor_idx++) {
            Note mynote = mysheet.getNote();
            output << mynote.getPitch() << ':' << mynote.getRyhthm() << std::endl;
            mysheet.cursor.cr();
        }
        mysheet.cursor.cs();
        mysheet.page.pr();
    }

    mysheet.cursor.cs();
    mysheet.page.ps();
}

void SaveLoader::load(std::string filename, Sheet& mysheet) {
    std::ifstream input(filename, std::ios::in);

    if (!input.is_open()) return;

    string pitch;
    string rhythm;
    

    std::string line;
    int delimiter_pos;

    mysheet.cursor.cs();
    mysheet.page.ps();

    for (int page_idx = 0; page_idx < 30; page_idx++) {
        for (int cursor_idx = 0; cursor_idx < 48; cursor_idx++) {
            getline(input, line);
            int delimiter_pos = line.find(':');

            pitch = line.substr(0, delimiter_pos);
            rhythm = line.substr(delimiter_pos+1);
            
            mysheet.insert(pitch.c_str(), rhythm.c_str());
        }
        mysheet.cursor.cs();
        mysheet.page.pr();
    }

    mysheet.cursor.cs();
    mysheet.page.ps();
}