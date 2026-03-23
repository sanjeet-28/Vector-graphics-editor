#ifndef PARSELINE_H
#define PARSELINE_H

#include <fstream>
#include <string>
#include "Diagram.h"

class ParseLine {
public:
    static void parse(std::ifstream& file,
                      std::string line,
                      Diagram& diagram);
};

#endif
