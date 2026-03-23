#include "Circle.h"

#include <QPen>
#include <QBrush>
#include <QRectF>

using namespace std;

Circle::Circle(double cx, double cy, double r,
               const string &strokeColor,
               const string &fillColor,
               double strokeWidth)
    :GraphicsObject(strokeColor, fillColor, strokeWidth)
{
    this -> cx = cx;
    this -> cy = cy;
    this -> r = r;

}


QRectF Circle::getBoundingBox() const {
    return QRectF(cx-r, cy-r, 2*r, 2*r);
}

void Circle::move(double dx, double dy){
    cx += dx;
    cy += dy;
}

void Circle::draw(QPainter& painter) const{
    QPen pen(QColor(QString::fromStdString(strokeColor)));

    pen.setWidth(strokeWidth);
    painter.setPen(pen);


    if (fillColor == "none") {
        painter.setBrush(Qt::NoBrush);
    } else {
        painter.setBrush(QColor(QString::fromStdString(fillColor)));
    }

    painter.drawEllipse(cx - r, cy - r, 2*r, 2*r);
}

string Circle::toSVG() const {
    return "<circle cx=\"" + to_string(cx) +
           "\" cy=\"" + to_string(cy) +
           "\" r=\"" + to_string(r) +
           "\" stroke=\"" + strokeColor +
           "\" stroke-width=\"" + to_string(strokeWidth) +
           "\" fill=\"" + fillColor +
           "\" />";
}

std::unique_ptr<GraphicsObject> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

double Circle::getCx() const {
    return cx;
}

double Circle::getCy() const {
    return cy;
}

double Circle::getRadius() const {
    return r;
}

void Circle::setRadius(double radius){
    r = std::abs(radius);
}


void Circle::setFromBoundingBox(const QRectF& box){
    double newRadius = min(box.width(), box.height()) / 2.0;

    cx = box.center().x();
    cy = box.center().y();

    r = newRadius;
}


void Circle::setCx(double value) {
    cx = value;
}


void Circle::setCy(double value) {
    cy = value;
}


