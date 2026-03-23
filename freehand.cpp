#include "Freehand.h"
#include <QPen>
#include <QPolygonF>
#include <sstream>
#include <algorithm>

Freehand::Freehand(const std::vector<QPointF>& pts,
                   const std::string& strokeColor,
                   double strokeWidth)
    : GraphicsObject(strokeColor, "none", strokeWidth),
    points(pts) {}

void Freehand::addPoint(double x, double y) {

    points.emplace_back(x, y);
}

void Freehand::draw(QPainter& painter) const {
    if (points.size() < 2){
        return;
    }

    QPen pen(QColor(QString::fromStdString(strokeColor)));

    pen.setWidth(strokeWidth);
    painter.setPen(pen);

    QPolygonF poly;

    for (const auto& p : points) {
        poly << p;
    }

    painter.drawPolyline(poly);
}

void Freehand::move(double dx, double dy) {

    for (auto& p : points) {

        p.setX(p.x() + dx);
        p.setY(p.y() + dy);
    }
}

std::string Freehand::toSVG() const {

    std::ostringstream oss;

    oss << "<polyline points=\"";

    for (const auto& p : points) {

        oss << p.x() << "," << p.y() << " ";
    }

    oss << "\" stroke=\"" << strokeColor
        << "\" stroke-width=\"" << strokeWidth
        << "\" fill=\"none\" />";

    return oss.str();
}

QRectF Freehand::getBoundingBox() const {

    if (points.empty())
        return QRectF();

    double minX = points[0].x();
    double minY = points[0].y();

    double maxX = minX;
    double maxY = minY;

    for (const auto& p : points) {

        minX = std::min(minX, p.x());
        minY = std::min(minY, p.y());
        maxX = std::max(maxX, p.x());
        maxY = std::max(maxY, p.y());
    }

    return QRectF(minX, minY, maxX - minX, maxY - minY);
}

std::unique_ptr<GraphicsObject> Freehand::clone() const {

    return std::make_unique<Freehand>(*this);
}

void Freehand::setFromBoundingBox(const QRectF& newBox){
    QRectF oldBox = getBoundingBox();

    if (oldBox.width() == 0 || oldBox.height() == 0)
        return;

    double scaleX = newBox.width() / oldBox.width();
    double scaleY = newBox.height() / oldBox.height();

    for (auto& p : points) {

        double relativeX = (p.x() - oldBox.x());
        double relativeY = (p.y() - oldBox.y());

        double newX = newBox.x() + relativeX * scaleX;
        double newY = newBox.y() + relativeY * scaleY;

        p.setX(newX);
        p.setY(newY);
    }
}

