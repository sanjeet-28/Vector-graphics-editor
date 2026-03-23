#include "ParseText.h"
#include "SVGUtils.h"
#include "Text.h"

#include <memory>

using namespace std;

void ParseText::parse(ifstream& file,
                      string line,
                      Diagram& diagram)
{
    string tag = line;

    while (tag.find("</text>") == string::npos && file.good()){

        string nextLine;
        getline(file, nextLine);

        tag += nextLine;
    }

    string value;

    double x = 0;
    double y = 0;

    double strokeWidth = 1;
    string stroke = "black";
    string content = "";

    if (extractAttribute(tag, "x", value)) {
        safeStod(value, x);
    }

    if (extractAttribute(tag, "y", value)) {
        safeStod(value, y);
    }

    if (extractAttribute(tag, "stroke", value)) {
        stroke = value;
    }

    if (extractAttribute(tag, "stroke-width", value)) {
        safeStod(value, strokeWidth);
    }

    size_t start = tag.find(">");
    size_t end = tag.find("</text>");

    if (start != string::npos && end != string::npos && end > start){
        content = tag.substr(start + 1, end - start - 1);

        size_t first = content.find_first_not_of(" \n\r\t");

        if (first != string::npos){
            content.erase(0, first);
        }

        size_t last = content.find_last_not_of(" \n\r\t");

        if (last != string::npos){
            content.erase(last + 1);
        }
    }

    diagram.addObject(make_unique<Text>(
        x, y,
        content,
        stroke,
        strokeWidth
        ));
}
