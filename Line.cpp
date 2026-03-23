
#include <QPen>
#include <QColor>
#include <algorithm>

using namespace std;

#include "Line.h"


Line::Line(double x1, double y1,
           double x2, double y2,
           const string &strokeColor,
           double strokeWidth)
    : GraphicsObject(strokeColor, "none", strokeWidth){
    this -> x1 = x1;
    this -> y1 = y1;
    this -> x2 = x2;
    this -> y2 = y2;
}

void Line::move(double dx, double dy) {
    x1 += dx;
    y1 += dy;
    x2 += dx;
    y2 += dy;
}


QRectF Line::getBoundingBox() const {

    double minX = std::min(x1, x2);

    double minY = std::min(y1, y2);

    double maxX = std::max(x1, x2);

    double maxY = std::max(y1, y2);

    return QRectF(minX, minY, maxX - minX, maxY - minY);
}

void Line::draw(QPainter& painter) const {
    QPen pen(QColor(QString::fromStdString(strokeColor)));
    pen.setWidth(strokeWidth);
    painter.setPen(pen);

    painter.drawLine(x1, y1, x2, y2);
}


string Line::toSVG() const {
    return "<line x1=\"" + to_string(x1) +
           "\" y1=\"" + to_string(y1) +
           "\" x2=\"" + to_string(x2) +
           "\" y2=\"" + to_string(y2) +
           "\" stroke=\"" + strokeColor +
           "\" stroke-width=\"" + to_string(strokeWidth) +
           "\" />";
}

std::unique_ptr<GraphicsObject> Line::clone() const {

    return std::make_unique<Line>(*this);
}

double Line::getX1() const {
    return x1;
}

double Line::getY1() const {
    return y1;
}

double Line::getX2() const {
    return x2;
}

double Line::getY2() const {
    return y2;
}

void Line::setX1(double value) {
    x1 = value;
}

void Line::setY1(double value) {
    y1 = value;
}

void Line::setX2(double value) {
    x2 = value;
}

void Line::setY2(double value) {
    y2 = value;
}

void Line::setFromBoundingBox(const QRectF& box){
    x1 = box.left();
    y1 = box.top();
    x2 = box.right();
    y2 = box.bottom();
}
