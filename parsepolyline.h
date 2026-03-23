#ifndef PARSEPOLYLINE_H
#define PARSEPOLYLINE_H

#include <fstream>
#include <string>
#include "Diagram.h"

class ParsePolyline {
public:
    static void parse(std::ifstream& file,
                      std::string line,
                      Diagram& diagram);
};

#endif
