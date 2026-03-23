#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include "GraphicsObject.h"
#include "ResizeHandle.h"

using namespace std;

class RoundedRectangle : public GraphicsObject {
public:
    RoundedRectangle(double x, double y,
                     double width, double height,
                     double rx, double ry,
                     const string &strokeColor,
                     const string &fillColor,
                     double strokeWidth);

    void move(double dx, double dy) override;
    void draw(QPainter& painter) const override;
    string toSVG() const override;
    QRectF getBoundingBox() const override;

    std::unique_ptr<GraphicsObject> clone() const override;
    void resize(ResizeHandle handle, double dx, double dy);

    double getX() const;
    double getY() const;
    double getWidth() const;
    double getHeight() const;

    void setX(double newX);
    void setY(double newY);
    void setWidth(double newWidth);
    void setHeight(double newHeight);

    void setFromBoundingBox(const QRectF& box);




private:
    double x;
    double y;
    double width;
    double height;
    double rx;
    double ry;
};

#endif
