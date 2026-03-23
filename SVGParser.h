#ifndef SVGPARSER_H
#define SVGPARSER_H

#include "Diagram.h"
#include <string>

class SVGParser {
public:
    static Diagram parseFromFile(const std::string& filename);
};

#endif
