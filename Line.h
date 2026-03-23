#ifndef LINE_H
#define LINE_H

#include "GraphicsObject.h"
using namespace std;

class Line : public GraphicsObject {
public:
    Line(double x1, double y1,
         double x2, double y2,
         const string &strokeColor,
         double strokeWidth);

    void move(double dx, double dy) override;
    void draw(QPainter& painter) const override;
    string toSVG() const override;
    QRectF getBoundingBox() const override;

    std::unique_ptr<GraphicsObject> clone() const override;


    double getX1() const;
    double getY1() const;
    double getX2() const;
    double getY2() const;

    void setX1(double);
    void setY1(double);
    void setX2(double);
    void setY2(double);

    void setFromBoundingBox(const QRectF& box) override;


private:
    double x1;
    double y1;
    double x2;
    double y2;
};

#endif
