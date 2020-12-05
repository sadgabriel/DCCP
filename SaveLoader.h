#pragma once

#include <string>
#include <fstream>

#include "Sheet.h"
#include "cursor.h"
#include "page.h"

class SaveLoader {
public:
    void save(std::string filename, Sheet& mysheet);
    void load(std::string filename, Sheet& mysheet);
};

