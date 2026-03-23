#include <cmath>
#include <QPen>
#include <QBrush>
#include <QPolygonF>
#include <QColor>
#include <cmath>
#include "Hexagon.h"

using namespace std;

Hexagon::Hexagon(double cx, double cy, double radius,
                 const string &strokeColor,
                 const string &fillColor,
                 double strokeWidth)
    : GraphicsObject(strokeColor, fillColor, strokeWidth){

    this->cx = cx;
    this->cy = cy;
    this->radius = radius;
}

void Hexagon::move(double dx, double dy) {

    cx += dx;
    cy += dy;
}

QRectF Hexagon::getBoundingBox() const {

    return QRectF(cx - radius, cy - radius, 2 * radius, 2 * radius);
}

void Hexagon::draw(QPainter& painter) const {

    QPen pen(QColor(QString::fromStdString(strokeColor)));

    pen.setWidth(strokeWidth);
    painter.setPen(pen);

    if (fillColor == "none") {
        painter.setBrush(Qt::NoBrush);
    }
    else {
        painter.setBrush(QColor(QString::fromStdString(fillColor)));
    }

    QPolygonF polygon;

    double pi = acos(-1);

    for (int i = 0; i < 6; i++) {

        double angle = pi / 3 * i;
        double px = cx + radius * cos(angle);
        double py = cy + radius * sin(angle);

        polygon << QPointF(px, py);
    }

    painter.drawPolygon(polygon);
}


string Hexagon::toSVG() const {

    string points = "";

    double pi = acos(-1);

    for (int i = 0; i < 6; i++) {

        double angle = pi / 3 * i;

        double x = cx + radius * cos(angle);
        double y = cy + radius * sin(angle);

        points += to_string(x) + "," + to_string(y) + " ";
    }

    return "<polygon points=\"" + points +
           "\" stroke=\"" + strokeColor +
           "\" stroke-width=\"" + to_string(strokeWidth) +
           "\" fill=\"" + fillColor +
           "\" />";
}

std::unique_ptr<GraphicsObject> Hexagon::clone() const {

    return std::make_unique<Hexagon>(*this);
}


double Hexagon::getCx() const {
    return cx;
}

double Hexagon::getCy() const {
    return cy;
}

double Hexagon::getRadius() const {
    return radius;
}

void Hexagon::setCx(double value) {
    cx = value;
}

void Hexagon::setCy(double value) {
    cy = value;
}

void Hexagon::setRadius(double value) {
    radius = std::abs(value);
}

void Hexagon::setFromBoundingBox(const QRectF& box)
{
    cx = box.center().x();
    cy = box.center().y();

    radius = std::min(box.width(), box.height()) / 2.0;
}
