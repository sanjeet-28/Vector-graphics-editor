#include "ParsePolyline.h"
#include "SVGUtils.h"
#include "Freehand.h"

#include <vector>
#include <sstream>
#include <memory>

using namespace std;

void ParsePolyline::parse(ifstream& file, string line, Diagram& diagram){

    string tag = readFullTag(file, line);
    string value;

    vector<QPointF> points;
    string stroke = "black";

    double strokeWidth = 1;

    if (extractAttribute(tag, "stroke", value)) {
        stroke = value;
    }

    if (extractAttribute(tag, "stroke-width", value)) {
        safeStod(value, strokeWidth);
    }

    if (extractAttribute(tag, "points", value)) {

        stringstream ss(value);
        string pair;

        while (ss >> pair) {
            size_t comma = pair.find(",");

            if (comma != string::npos) {

                double x = stod(pair.substr(0, comma));
                double y = stod(pair.substr(comma + 1));
                points.emplace_back(x, y);
            }
        }
    }

    if (!points.empty()) {

        diagram.addObject(make_unique<Freehand>(points, stroke, strokeWidth));
    }
}
