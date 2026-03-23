#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <string>
#include <QPainter>
#include <QRectF>

class GraphicsObject {
protected:
    std::string strokeColor;
    std::string fillColor;
    double strokeWidth;

public:
    GraphicsObject(const std::string& strokeColor,
                   const std::string& fillColor,
                   double strokeWidth);

    virtual void draw(QPainter& painter) const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual std::string toSVG() const = 0;

    virtual QRectF getBoundingBox() const = 0;

    virtual ~GraphicsObject() = default;

    virtual std::unique_ptr<GraphicsObject> clone() const = 0;

    void setStrokeColor(const std::string& color);
    void setFillColor(const std::string& color);
    void setStrokeWidth(double width);

    std::string getStrokeColor() const;
    std::string getFillColor() const;
    double getStrokeWidth() const;
    virtual void setFromBoundingBox(const QRectF& box) = 0;


};

#endif
