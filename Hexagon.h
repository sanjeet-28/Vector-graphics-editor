#ifndef HEXAGON_H
#define HEXAGON_H

#include "GraphicsObject.h"

using namespace std;

class Hexagon : public GraphicsObject {
public:
    Hexagon(double cx, double cy, double radius,
            const string &strokeColor,
            const string &fillColor,
            double strokeWidth);

    void move(double dx, double dy) override;
    void draw(QPainter& painter) const override;
    string toSVG() const override;
    QRectF getBoundingBox() const override;

    std::unique_ptr<GraphicsObject> clone() const override;


    double getCx() const;
    double getCy() const;
    double getRadius() const;

    void setCx(double value);
    void setCy(double value);
    void setRadius(double value);
    void setFromBoundingBox(const QRectF& box) override;


private:
    double cx;
    double cy;
    double radius;
};

#endif
