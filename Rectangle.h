#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GraphicsObject.h"
#include "ResizeHandle.h"


using namespace std;

class Rectangle : public GraphicsObject {
public:
    Rectangle(double x, double y,
              double width, double height,
              const string &strokeColor,
              const string &fillColor,
              double strokeWidth);

    void move(double dx, double dy) override;
    void draw(QPainter& painter) const override;
    string toSVG() const override;
    QRectF getBoundingBox() const override;

    std::unique_ptr<GraphicsObject> clone() const override;

    void setX(double newX);
    void setY(double newY);
    void setWidth(double newWidth);
    void setHeight(double newHeight);

    double getX() const;
    double getY() const;
    double getWidth() const;
    double getHeight() const;


    void setFromBoundingBox(const QRectF& box) override;

private:
    double x;
    double y;
    double width;
    double height;
};

#endif
