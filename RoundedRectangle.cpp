
#include <QPen>
#include <QBrush>
#include <QColor>

using namespace std;

#include "RoundedRectangle.h"


RoundedRectangle::RoundedRectangle(double x, double y,
                                   double width, double height,
                                   double rx, double ry,
                                   const string &strokeColor,
                                   const string &fillColor,
                                   double strokeWidth)
    : GraphicsObject(strokeColor, fillColor, strokeWidth)
{
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    this -> rx = rx;
    this -> ry = ry;
}

void RoundedRectangle::move(double dx, double dy) {
    x += dx;
    y += dy;
}

QRectF RoundedRectangle::getBoundingBox() const {

    return QRectF(x, y, width, height);
}


void RoundedRectangle::draw(QPainter& painter) const {

    QPen pen(QColor(QString::fromStdString(strokeColor)));

    pen.setWidth(strokeWidth);
    painter.setPen(pen);

    if (fillColor == "none") {
        painter.setBrush(Qt::NoBrush);
    }
    else {
        painter.setBrush(QColor(QString::fromStdString(fillColor)));
    }

    painter.drawRoundedRect(x, y, width, height, rx, ry);
}


string RoundedRectangle::toSVG() const {
    return "<rect x=\"" + to_string(x) +
           "\" y=\"" + to_string(y) +
           "\" width=\"" + to_string(width) +
           "\" height=\"" + to_string(height) +
           "\" rx=\"" + to_string(rx) +
           "\" ry=\"" + to_string(ry) +
           "\" stroke=\"" + strokeColor +
           "\" stroke-width=\"" + to_string(strokeWidth) +
           "\" fill=\"" + fillColor +
           "\" />";
}

std::unique_ptr<GraphicsObject> RoundedRectangle::clone() const {

    return std::make_unique<RoundedRectangle>(*this);
}

void RoundedRectangle::resize(ResizeHandle handle, double dx, double dy)
{
    switch (handle) {

    case ResizeHandle::TopLeft:
        x += dx;
        y += dy;
        width -= dx;
        height -= dy;
        break;

    case ResizeHandle::TopRight:
        y += dy;
        width += dx;
        height -= dy;
        break;

    case ResizeHandle::BottomLeft:
        x += dx;
        width -= dx;
        height += dy;
        break;

    case ResizeHandle::BottomRight:
        width += dx;
        height += dy;
        break;

    default:
        break;
    }
}


double RoundedRectangle::getX() const {
    return x;
}

double RoundedRectangle::getY() const {
    return y;
}

double RoundedRectangle::getWidth() const {
    return width;
}

double RoundedRectangle::getHeight() const {
    return height;
}

void RoundedRectangle::setX(double newX) {
    x = newX;
}

void RoundedRectangle::setY(double newY) {
    y = newY;
}

void RoundedRectangle::setWidth(double newWidth) {
    width = newWidth;
}

void RoundedRectangle::setHeight(double newHeight) {
    height = newHeight;
}



void RoundedRectangle::setFromBoundingBox(const QRectF& box)
{
    double newX = box.x();
    double newY = box.y();
    double newW = box.width();
    double newH = box.height();

    // If width is negative → flip horizontally
    if (newW < 0) {
        newX += newW;
        newW = -newW;
    }

    // If height is negative → flip vertically
    if (newH < 0) {
        newY += newH;
        newH = -newH;
    }

    x = newX;
    y = newY;
    width = newW;
    height = newH;
}


