#ifndef PARSEPOLYGON_H
#define PARSEPOLYGON_H

#include <fstream>
#include <string>
#include "Diagram.h"

class ParsePolygon {
public:
    static void parse(std::ifstream& file,
                      std::string line,
                      Diagram& diagram);
};

#endif
