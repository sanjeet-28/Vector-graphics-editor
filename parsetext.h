#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <fstream>
#include <string>
#include "Diagram.h"

class ParseText {
public:
    static void parse(std::ifstream& file,
                      std::string line,
                      Diagram& diagram);
};

#endif
