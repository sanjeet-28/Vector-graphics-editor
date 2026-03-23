#include "SVGParser.h"
#include <fstream>
#include <string>
#include "parsecircle.h"
#include "parserect.h"
#include "parseline.h"
#include "parsepolygon.h"
#include "parsepolyline.h"
#include "parsetext.h"
#include "parsesvgroot.h"

using namespace std;

static string readFullTag(ifstream& file, string firstLine) {
    string tag = firstLine;

    while (tag.find(">") == string::npos && file.good()) {
        string nextLine;

        getline(file, nextLine);

        tag += nextLine;
    }

    return tag;
}

static bool extractAttribute(const std::string& line, const std::string& attr, std::string& value){
    size_t pos = line.find(attr + "=");

    if (pos == std::string::npos) {
        return false;
    }

    pos = line.find("=", pos);
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

static bool safeStod(const std::string& s, double& result) {
    try {

        size_t idx;

        result = std::stod(s, &idx);

        return idx == s.length();
    }
    catch (...) {
        return false;
    }
}

Diagram SVGParser::parseFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return Diagram(500, 500);
    }

    string line;
    double width = 500;
    double height = 500;

    Diagram diagram(width, height);

    while (getline(file, line)) {

        if (line.find("<svg") != string::npos) {
            ParseSVGRoot::parse(file, line, diagram);
        }

        if (line.find("<circle") != string::npos) {
            ParseCircle::parse(file, line, diagram);
        }

        else if (line.find("<rect") != string::npos) {
            ParseRect::parse(file, line, diagram);
        }

        else if (line.find("<line") != string::npos) {
            ParseLine::parse(file, line, diagram);
        }

        else if (line.find("<polygon") != std::string::npos) {
            ParsePolygon::parse(file, line, diagram);
        }

        else if (line.find("<text") != string::npos) {
            ParseText::parse(file, line, diagram);
        }

        else if (line.find("<polyline") != std::string::npos) {
            ParsePolyline::parse(file, line, diagram);
        }
    }

    return diagram;
}
