#ifndef CIRCLE_H
#define CIRCLE_H

#include "GraphicsObject.h"

using namespace std;

class Circle : public GraphicsObject{
public:
    Circle(double cx, double cy, double r,
            const string &strokeColor,
            const string &fillColor,
            double strokeWidth);

    void move(double dx, double dy) override;

    string toSVG() const override;

    void draw(QPainter& painter) const override;
    QRectF getBoundingBox() const override;

    std::unique_ptr<GraphicsObject> clone() const override;

    double getCx() const;
    double getCy() const;
    double getRadius() const;

    void setRadius(double r);
    void setFromBoundingBox(const QRectF& box) override;

    void setCx(double value);
    void setCy(double value);


private:
    double cx;
    double cy;
    double r;
};

#endif
