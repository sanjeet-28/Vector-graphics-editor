#ifndef RECTPARSER_H
#define RECTPARSER_H

#include <fstream>
#include <string>
#include "Diagram.h"

class ParseRect {
public:
    static void parse(std::ifstream& file,
                      std::string line,
                      Diagram& diagram);
};

#endif
