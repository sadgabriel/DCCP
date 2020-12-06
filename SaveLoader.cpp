#include "SaveLoader.h"



void SaveLoader::save(std::string filename, Sheet& mysheet) {
    static std::string old_filename = std::string("default.txt");

    if (filename.size() == 0) filename = old_filename;

    old_filename = filename;

    std::ofstream output(filename, std::ios::out);
    
    
    mysheet.cursor.cs();
    mysheet.page.ps();
    for (int page_idx = 0; page_idx < 30; page_idx++) {
        for (int cursor_idx = 0; cursor_idx < 48; cursor_idx++) {
            if (mysheet.getNote().is_NULL) goto END_LOOP1;
            Note mynote = mysheet.getNote();
            output << mynote.getPitch() << ':' << mynote.getRhythm() << std::endl;
            mysheet.cursor.cr();
        }
        mysheet.cursor.cs();
        mysheet.page.pr();
    }
    END_LOOP1:

    mysheet.cursor.cs();
    mysheet.page.ps();

    output.close();
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
            if (line.size() == 0) goto END_LOOP2;
            int delimiter_pos = line.find(':');

            pitch = line.substr(0, delimiter_pos);
            rhythm = line.substr(delimiter_pos+1);
            
            char *pitch_pointer = new char[4];
            char *rhythm_pointer = new char[5];

            for (int i = 0; i < 4; i++) {
                pitch_pointer[i] = '\0';
            }

            for (int i = 0; i < pitch.size(); i++) {
                pitch_pointer[i] = pitch[i];
            }

            for (int i = 0; i < 5; i++) {
                rhythm_pointer[i] = '\0';
            }

            for (int i = 0; i < rhythm.size(); i++) {
                rhythm_pointer[i] = rhythm[i];
            }

            mysheet.insert(pitch_pointer, rhythm_pointer);
        }
        mysheet.cursor.cs();
        mysheet.page.pr();
    }

    END_LOOP2:

    mysheet.cursor.cs();
    mysheet.page.ps();

    input.close();
}