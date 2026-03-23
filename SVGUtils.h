#ifndef SVGUTILS_H
#define SVGUTILS_H

#include <string>
#include <fstream>

std::string readFullTag(std::ifstream& file, std::string firstLine);

bool extractAttribute(const std::string& line,
                      const std::string& attr,
                      std::string& value);

bool safeStod(const std::string& s, double& result);

#endif
