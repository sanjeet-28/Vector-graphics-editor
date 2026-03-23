#ifndef PARSECIRCLE_H
#define PARSECIRCLE_H

#include <fstream>
#include <string>
#include "Diagram.h"

class ParseCircle {
public:
    static void parse(std::ifstream& file,
                      std::string line,
                      Diagram& diagram);
};

#endif
