#include "parserect.h"
#include "SVGUtils.h"

#include "Rectangle.h"
#include "RoundedRectangle.h"

#include <memory>

using namespace std;

void ParseRect::parse(ifstream& file,
                      string line,
                      Diagram& diagram)
{
    string tag = readFullTag(file, line);

    if (tag.find("width=\"100%\"") != string::npos &&
        tag.find("height=\"100%\"") != string::npos){

        string value;
        string fill = "white";

        if (extractAttribute(tag, "fill", value)) {
            fill = value;
        }

        diagram.setBackgroundColor(fill);
        return;
    }

    string value;

    double x = 0, y = 0;
    double rectWidth = 0, rectHeight = 0;
    double strokeWidth = 1;
    double rx = 0, ry = 0;

    string stroke = "black";
    string fill = "none";

    if (extractAttribute(tag, "x", value)) {
        safeStod(value, x);
    }

    if (extractAttribute(tag, "y", value)) {
        safeStod(value, y);
    }

    if (extractAttribute(tag, "width", value)) {
        safeStod(value, rectWidth);
    }

    if (extractAttribute(tag, "height", value)) {
        safeStod(value, rectHeight);
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

    bool hasRX = extractAttribute(tag, "rx", value) && safeStod(value, rx);
    bool hasRY = extractAttribute(tag, "ry", value) && safeStod(value, ry);

    if (rectWidth > 0 && rectHeight > 0){
        if (hasRX || hasRY){
            diagram.addObject(make_unique<RoundedRectangle>(
                x, y,
                rectWidth, rectHeight,
                rx, ry,
                stroke, fill,
                strokeWidth
                ));
        }
        else{
            diagram.addObject(make_unique<Rectangle>(
                x, y,
                rectWidth, rectHeight,
                stroke, fill,
                strokeWidth
                ));
        }
    }
}
