#include "ParseSVGRoot.h"
#include "SVGUtils.h"
#include "Diagram.h"

#include <sstream>

using namespace std;

void ParseSVGRoot::parse(ifstream& file,
                         string line,
                         Diagram& diagram)
{
    string tag = readFullTag(file, line);
    string value;

    double width = 500;
    double height = 500;

    string viewBoxValue;

    if (extractAttribute(tag, "viewBox", viewBoxValue)) {
        stringstream ss(viewBoxValue);

        double x = 0;
        double y = 0;

        ss >> x >> y >> width >> height;
    }
    else {
        if (extractAttribute(tag, "width", value)) {
            safeStod(value, width);
        }

        if (extractAttribute(tag, "height", value)) {
            safeStod(value, height);
        }
    }

    diagram = Diagram(width, height);
}
