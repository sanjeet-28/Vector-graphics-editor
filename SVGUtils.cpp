#include "SVGUtils.h"

std::string readFullTag(std::ifstream& file, std::string firstLine) {
    std::string tag = firstLine;

    while (tag.find(">") == std::string::npos && file.good()) {

        std::string nextLine;

        std::getline(file, nextLine);

        tag += nextLine;
    }

    return tag;
}

bool extractAttribute(const std::string& line, const std::string& attr, std::string& value) {

    size_t pos = line.find(attr + "=");

    if (pos == std::string::npos) {
        return false;
    }

    pos = line.find("\"", pos);
    if (pos == std::string::npos) {
        return false;
    }

    size_t end = line.find("\"", pos + 1);
    if (end == std::string::npos) {
        return false;
    }

    value = line.substr(pos + 1, end - pos - 1);
    return true;

}

bool safeStod(const std::string& s, double& result) {
    try {

        size_t idx;

        result = std::stod(s, &idx);

        return idx == s.length();
    }
    catch (...) {
        return false;
    }
}
