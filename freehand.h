#ifndef FREEHAND_H
#define FREEHAND_H

#include "GraphicsObject.h"
#include <vector>
#include <QPointF>

class Freehand : public GraphicsObject {
private:
    std::vector<QPointF> points;

public:
    Freehand(const std::vector<QPointF>& pts,
             const std::string& strokeColor,
             double strokeWidth);

    void addPoint(double x, double y);

    void draw(QPainter& painter) const override;
    void move(double dx, double dy) override;
    std::string toSVG() const override;
    QRectF getBoundingBox() const override;

    std::unique_ptr<GraphicsObject> clone() const override;
    void setFromBoundingBox(const QRectF& box) override;
};

#endif
