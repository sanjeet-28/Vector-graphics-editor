

#include <QPen>
#include <QBrush>
#include <QColor>
#include <QRectF>

using namespace std;

#include "Rectangle.h"


Rectangle::Rectangle(double x, double y,
                     double width, double height,
                     const string &strokeColor,
                     const string &fillColor,
                     double strokeWidth)
    : GraphicsObject(strokeColor, fillColor, strokeWidth)
{
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
}

void Rectangle::move(double dx, double dy) {
    x += dx;
    y += dy;
}


QRectF Rectangle::getBoundingBox() const {
    return QRectF(x, y, width, height);
}


void Rectangle::draw(QPainter& painter) const {

    QPen pen(QColor(QString::fromStdString(strokeColor)));

    pen.setWidth(strokeWidth);

    painter.setPen(pen);

    if (fillColor == "none") {
        painter.setBrush(Qt::NoBrush);
    }
    else {
        painter.setBrush(QColor(QString::fromStdString(fillColor)));
    }

    painter.drawRect(x, y, width, height);
}


string Rectangle::toSVG() const {
    return "<rect x=\"" + to_string(x) +
           "\" y=\"" + to_string(y) +
           "\" width=\"" + to_string(width) +
           "\" height=\"" + to_string(height) +
           "\" stroke=\"" + strokeColor +
           "\" stroke-width=\"" + to_string(strokeWidth) +
           "\" fill=\"" + fillColor +
           "\" />";
}

std::unique_ptr<GraphicsObject> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

double Rectangle::getX() const {
    return x;
}

double Rectangle::getY() const {
    return y;
}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::getHeight() const {
    return height;
}

void Rectangle::setX(double newX) {
    x = newX;
}

void Rectangle::setY(double newY) {
    y = newY;
}

void Rectangle::setWidth(double newWidth) {
    width = newWidth;
}

void Rectangle::setHeight(double newHeight) {
    height = newHeight;
}

void Rectangle::setFromBoundingBox(const QRectF& box){
    x = box.x();
    y = box.y();
    width = box.width();
    height = box.height();
}



