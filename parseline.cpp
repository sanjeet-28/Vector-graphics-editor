#include "parseline.h"
#include "SVGUtils.h"
#include "Line.h"

#include <memory>

using namespace std;

void ParseLine::parse(ifstream& file,
                      string line,
                      Diagram& diagram)
{
    string tag = readFullTag(file, line);
    string value;

    double x1 = 0, y1 = 0;
    double x2 = 0, y2 = 0;
    double strokeWidth = 1;

    string stroke = "black";

    if (extractAttribute(tag, "x1", value))
        safeStod(value, x1);

    if (extractAttribute(tag, "y1", value))
        safeStod(value, y1);

    if (extractAttribute(tag, "x2", value))
        safeStod(value, x2);

    if (extractAttribute(tag, "y2", value))
        safeStod(value, y2);

    if (extractAttribute(tag, "stroke", value))
        stroke = value;

    if (extractAttribute(tag, "stroke-width", value))
        safeStod(value, strokeWidth);

    diagram.addObject(make_unique<Line>(x1, y1, x2, y2, stroke, strokeWidth));
}


