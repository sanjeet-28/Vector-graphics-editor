#include "canvaswidget.h"
#include <algorithm>
#include "Rectangle.h"
#include "freehand.h"
#include "RoundedRectangle.h"
#include "Text.h"
#include "Circle.h"
#include "Line.h"
#include "Hexagon.h"

using namespace std;

void CanvasWidget::mouseMoveEvent(QMouseEvent* event){

    QPointF pos = event->position();

    if (currentTool == ToolMode::Select && diagram.getSelectedObject() && !dragging && !isResizing){

        QRectF box = getSelectionBox();

        double size = 8;
        double half = size / 2;

        QRectF tl(box.topLeft() - QPointF(half, half), QSizeF(size, size));
        QRectF tr(box.topRight() - QPointF(half, half), QSizeF(size, size));
        QRectF bl(box.bottomLeft() - QPointF(half, half), QSizeF(size, size));
        QRectF br(box.bottomRight() - QPointF(half, half), QSizeF(size, size));

        if (tl.contains(pos) || br.contains(pos)) {
            setCursor(Qt::SizeFDiagCursor);
        }

        else if (tr.contains(pos) || bl.contains(pos)) {
            setCursor(Qt::SizeBDiagCursor);
        }

        else {
            setCursor(Qt::ArrowCursor);
        }
    }

    if (currentTool == ToolMode::Select && dragging) {
        setCursor(Qt::SizeAllCursor);

        double dx = pos.x() - lastMousePos.x();
        double dy = pos.y() - lastMousePos.y();

        auto obj = diagram.getSelectedObject();
        if (obj){
            obj -> move(dx, dy);
        }

        lastMousePos = pos;
        update();

        return;
    }

    if (isDrawing) {
        currentPoint = pos;

        // rect
        if (currentTool == ToolMode::Rectangle) {

            double x = min(startPoint.x(), currentPoint.x());
            double y = min(startPoint.y(), currentPoint.y());
            double w = abs(startPoint.x() - currentPoint.x());
            double h = abs(startPoint.y() - currentPoint.y());

            previewObject = make_unique<Rectangle>(
                x, y, w, h,
                currentStrokeColor.toStdString(),
                currentFillColor.toStdString(),
                currentStrokeWidth
                );
        }

        //rrect
        else if (currentTool == ToolMode::RoundedRectangle) {

            double x = min(startPoint.x(), currentPoint.x());

            double y = min(startPoint.y(), currentPoint.y());

            double w = abs(startPoint.x() - currentPoint.x());

            double h = abs(startPoint.y() - currentPoint.y());

            previewObject = make_unique<RoundedRectangle>(
                x, y, w, h,
                15, 15,
                currentStrokeColor.toStdString(),
                currentFillColor.toStdString(),
                currentStrokeWidth
                );
        }

        // circle
        else if (currentTool == ToolMode::Circle) {
            double dx = currentPoint.x() - startPoint.x();
            double dy = currentPoint.y() - startPoint.y();

            double r = sqrt(dx * dx + dy * dy);

            previewObject = make_unique<Circle>(
                startPoint.x(),
                startPoint.y(),
                r,
                currentStrokeColor.toStdString(),
                currentFillColor.toStdString(),
                currentStrokeWidth
                );
        }

        // line
        else if (currentTool == ToolMode::Line) {

            previewObject = make_unique<Line>(
                startPoint.x(),
                startPoint.y(),
                currentPoint.x(),
                currentPoint.y(),
                currentStrokeColor.toStdString(),
                currentStrokeWidth
                );
        }

        // hexagon
        else if (currentTool == ToolMode::Hexagon) {
            double dx = currentPoint.x() - startPoint.x();
            double dy = currentPoint.y() - startPoint.y();
            double r = sqrt(dx * dx + dy * dy);

            previewObject = make_unique<Hexagon>(
                startPoint.x(),
                startPoint.y(),
                r,
                currentStrokeColor.toStdString(),
                currentFillColor.toStdString(),
                currentStrokeWidth
                );
        }

        //freehnd
        else if (currentTool == ToolMode::Freehand) {
            auto freehand = dynamic_cast<Freehand*>(previewObject.get());
            if (freehand) {
                freehand->addPoint(pos.x(), pos.y());
            }
        }

        update();
    }

    if (isResizing) {

        auto obj = diagram.getSelectedObject();
        if (!obj) {
            return;
        }

        QRectF startBox = resizeStartBox;

        QPointF anchor;

        if (activeHandle == ResizeHandle::TopLeft) {
            anchor = startBox.bottomRight();
        }

        else if (activeHandle == ResizeHandle::TopRight) {
            anchor = startBox.bottomLeft();
        }

        else if (activeHandle == ResizeHandle::BottomLeft) {
            anchor = startBox.topRight();
        }

        else if (activeHandle == ResizeHandle::BottomRight) {
            anchor = startBox.topLeft();
        }

        else {
            return;
        }

        // circl
        if (auto circle = dynamic_cast<Circle*>(obj)) {

            QPointF anchor;

            if (activeHandle == ResizeHandle::TopLeft) {
                anchor = resizeStartBox.bottomRight();
            }

            else if (activeHandle == ResizeHandle::TopRight) {
                anchor = resizeStartBox.bottomLeft();
            }

            else if (activeHandle == ResizeHandle::BottomLeft) {
                anchor = resizeStartBox.topRight();
            }

            else if (activeHandle == ResizeHandle::BottomRight) {
                anchor = resizeStartBox.topLeft();
            }

            else {
                return;
            }

            double dx = pos.x() - anchor.x();
            double dy = pos.y() - anchor.y();

            double side = max(abs(dx), abs(dy));

            double signX;
            if (dx >= 0) {
                signX = 1.0;
            }
            else {
                signX = -1.0;
            }

            double signY;
            if (dy >= 0) {
                signY = 1.0;
            }
            else {
                signY = -1.0;
            }

            double newCx = anchor.x() + signX * side / 2.0;
            double newCy = anchor.y() + signY * side / 2.0;

            circle -> setCx(newCx);
            circle -> setCy(newCy);
            circle -> setRadius(side / 2.0);

            update();

            return;

        }

        // hexagon
        if (auto hex = dynamic_cast<Hexagon*>(obj)) {

            QPointF anchor;

            if (activeHandle == ResizeHandle::TopLeft) {
                anchor = resizeStartBox.bottomRight();
            }

            else if (activeHandle == ResizeHandle::TopRight) {
                anchor = resizeStartBox.bottomLeft();
            }

            else if (activeHandle == ResizeHandle::BottomLeft) {
                anchor = resizeStartBox.topRight();
            }

            else if (activeHandle == ResizeHandle::BottomRight) {
                anchor = resizeStartBox.topLeft();
            }

            else {
                return;
            }

            double dx = pos.x() - anchor.x();
            double dy = pos.y() - anchor.y();

            double side = max(abs(dx), abs(dy));

            double signX;
            if (dx >= 0) {
                signX = 1.0;
            } else {
                signX = -1.0;
            }

            double signY;
            if (dy >= 0) {
                signY = 1.0;
            } else {
                signY = -1.0;
            }

            double newCx = anchor.x() + signX * side / 2.0;
            double newCy = anchor.y() + signY * side / 2.0;

            hex->setCx(newCx);
            hex->setCy(newCy);

            hex->setRadius(side / 2.0);

            update();

            return;
        }

        if (auto text = dynamic_cast<Text*>(obj)) {

            QRectF startBox = resizeStartBox;

            QPointF anchor;

            if (activeHandle == ResizeHandle::TopLeft) {
                anchor = startBox.bottomRight();
            }

            else if (activeHandle == ResizeHandle::TopRight) {
                anchor = startBox.bottomLeft();
            }

            else if (activeHandle == ResizeHandle::BottomLeft) {
                anchor = startBox.topRight();
            }

            else if (activeHandle == ResizeHandle::BottomRight) {
                anchor = startBox.topLeft();
            }

            else {
                return;
            }

            double dx = pos.x() - anchor.x();
            double dy = pos.y() - anchor.y();

            double side = max(abs(dx), abs(dy));
            double newFontSize = max(6.0, side / 5.0);

            text->setFontSize(newFontSize);

            QRectF newBox = text->getBoundingBox();

            QPointF newAnchor;

            if (activeHandle == ResizeHandle::TopLeft) {
                newAnchor = newBox.bottomRight();
            }

            else if (activeHandle == ResizeHandle::TopRight) {
                newAnchor = newBox.bottomLeft();
            }

            else if (activeHandle == ResizeHandle::BottomLeft) {
                newAnchor = newBox.topRight();
            }

            else if (activeHandle == ResizeHandle::BottomRight) {
                newAnchor = newBox.topLeft();
            }

            else {
                return;
            }

            double shiftX = anchor.x() - newAnchor.x();
            double shiftY = anchor.y() - newAnchor.y();

            text -> move(shiftX, shiftY);

            update();

            return;
        }

        // rect amd rrectangle
        QRectF newBox = startBox;

        QPointF clampedPos = pos;
        const double MIN_SIZE = 2.0;

        if (activeHandle == ResizeHandle::TopLeft) {

            if (abs(startBox.bottomRight().x() - pos.x()) < MIN_SIZE){
                clampedPos.setX(startBox.bottomRight().x() - MIN_SIZE);
            }

            if (abs(startBox.bottomRight().y() - pos.y()) < MIN_SIZE){
                clampedPos.setY(startBox.bottomRight().y() - MIN_SIZE);
            }

            newBox.setTopLeft(clampedPos);
        }

        else if (activeHandle == ResizeHandle::TopRight) {

            if (abs(startBox.bottomLeft().x() - pos.x()) < MIN_SIZE){
                clampedPos.setX(startBox.bottomLeft().x() + MIN_SIZE);
            }

            if (abs(startBox.bottomLeft().y() - pos.y()) < MIN_SIZE){
                clampedPos.setY(startBox.bottomLeft().y() - MIN_SIZE);
            }

            newBox.setTopRight(clampedPos);
        }

        else if (activeHandle == ResizeHandle::BottomLeft) {

            if (abs(startBox.topRight().x() - pos.x()) < MIN_SIZE){
                clampedPos.setX(startBox.topRight().x() - MIN_SIZE);
            }

            if (abs(startBox.topRight().y() - pos.y()) < MIN_SIZE){
                clampedPos.setY(startBox.topRight().y() + MIN_SIZE);
            }

            newBox.setBottomLeft(clampedPos);
        }

        else if (activeHandle == ResizeHandle::BottomRight) {

            if (abs(startBox.topLeft().x() - pos.x()) < MIN_SIZE){
                clampedPos.setX(startBox.topLeft().x() + MIN_SIZE);
            }

            if (abs(startBox.topLeft().y() - pos.y()) < MIN_SIZE){
                clampedPos.setY(startBox.topLeft().y() + MIN_SIZE);
            }

            newBox.setBottomRight(clampedPos);
        }

        else {
            // nthng to to
        }


        newBox = newBox.normalized();

        obj->setFromBoundingBox(newBox);

        update();

        return;

    }

}
