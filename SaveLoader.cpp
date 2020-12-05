#include "SaveLoader.h"



void SaveLoader::save(std::string filename, Sheet& mysheet) {
    std::ofstream output(filename, std::ios::out);

    for (int page_idx = 0; page_idx < 30; page_idx++) {
        for (int cursor_idx = 0; cursor_idx < 48; cursor_idx++) {
            Note mynote = mysheet.getNote(cursor_idx, page_idx);
            output << mynote.freq << ':' << mynote.length << std::endl;
        }
    }
}

void SaveLoader::load(std::string filename, Sheet& mysheet, Cursor mycursor, Page mypage) {
    std::ifstream input(filename, std::ios::in);

    if (!input.is_open()) return;

    int freq;
    int length;
    
    mycursor.cs();
    mypage.ps();

    std::string line;
    int delimiter_pos;

    for (int page_idx = 0; page_idx < 30; page_idx++) {
        for (int cursor_idx = 0; cursor_idx < 48; cursor_idx++) {
            getline(input, line);
            int delimiter_pos = line.find(':');
            freq = stoi(line.substr(0, 3));
            length = 
            
        }
    }
}