#include "parsepolygon.h"
#include "SVGUtils.h"
#include "Hexagon.h"
#include "Diagram.h"
#include <vector>
#include <sstream>
#include <memory>
#include <cmath>

using namespace std;

void ParsePolygon::parse(ifstream& file,
                         string line,
                         Diagram& diagram){

    string tag = readFullTag(file, line);
    string value;

    vector<QPointF> points;
    string stroke = "black";
    string fill = "none";

    double strokeWidth = 1;

    if (extractAttribute(tag, "stroke", value)) {
        stroke = value;
    }

    if (extractAttribute(tag, "fill", value)) {
        fill = value;
    }

    if (extractAttribute(tag, "stroke-width", value)) {
        safeStod(value, strokeWidth);
    }

    if (extractAttribute(tag, "points", value)){
        stringstream ss(value);
        string pair;

        while (ss >> pair){
            size_t comma = pair.find(",");

            if (comma != string::npos){

                double x = stod(pair.substr(0, comma));
                double y = stod(pair.substr(comma + 1));
                points.emplace_back(x, y);
            }
        }
    }

    // convert points -> hexagon
    if (points.size() == 6){
        double cx = 0;
        double cy = 0;

        for (const auto& p : points){

            cx += p.x();
            cy += p.y();
        }

        cx /= 6.0;
        cy /= 6.0;

        double radius = sqrt((points[0].x() - cx) * (points[0].x() - cx) + (points[0].y() - cy) * (points[0].y() - cy));

        diagram.addObject(make_unique<Hexagon>(cx, cy, radius, stroke, fill, strokeWidth));
    }
}
