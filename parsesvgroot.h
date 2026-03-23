#ifndef PARSESVGROOT_H
#define PARSESVGROOT_H

#include <fstream>
#include <string>
#include "Diagram.h"

class ParseSVGRoot {
public:
    static void parse(std::ifstream& file,
                      std::string line,
                      Diagram& diagram);
};

#endif
