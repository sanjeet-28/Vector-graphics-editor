#include "parsecircle.h"
#include "SVGUtils.h"
#include "Circle.h"
#include "Diagram.h"
#include <memory>

using namespace std;

void ParseCircle::parse(ifstream& file,
                        string line,
                        Diagram& diagram) {

    string tag = readFullTag(file, line);
    string value;

    double cx = 0, cy = 0, r = 0, strokeWidth = 1;
    string stroke = "black";
    string fill = "none";

    if (extractAttribute(tag, "cx", value)) {
        safeStod(value, cx);
    }

    if (extractAttribute(tag, "cy", value)) {
        safeStod(value, cy);
    }

    if (extractAttribute(tag, "r", value)) {
        safeStod(value, r);
    }

    if (extractAttribute(tag, "stroke", value)) {
        stroke = value;
    }

    if (extractAttribute(tag, "fill", value)) {
        fill = value;
    }

    if (extractAttribute(tag, "stroke-width", value)) {
        safeStod(value, strokeWidth);
    }

    if (r > 0) {
        diagram.addObject(make_unique<Circle>(
            cx, cy, r,
            stroke, fill,
            strokeWidth
            ));
    }
}
