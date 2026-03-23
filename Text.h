#ifndef TEXT_H
#define TEXT_H

#include "GraphicsObject.h"

using namespace std;

class Text : public GraphicsObject {
public:
    Text(double x,
         double y,
         const std::string& content,
         const std::string& strokeColor,
         double strokeWidth,
         double fontSize = 16.0);


    void move(double dx, double dy) override;
    void draw(QPainter& painter) const override;
    string toSVG() const override;
    QRectF getBoundingBox() const override;

    std::unique_ptr<GraphicsObject> clone() const override;

    void setFromBoundingBox(const QRectF& box) override;
    void setX(double value);
    void setY(double value);
    void setFontSize(double size);


private:
    double x;
    double y;
    string content;
    double fontSize;

};

#endif
