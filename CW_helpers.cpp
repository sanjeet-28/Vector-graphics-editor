#include "canvaswidget.h"


void CanvasWidget::mouseDoubleClickEvent(QMouseEvent* event){
    QPointF pos = event -> position();

    auto obj = diagram.selectObjectAt(pos.x(), pos.y());

    if (obj) {
        setCursor(Qt::SizeAllCursor);

        currentTool = ToolMode::Select;

        dragging = false;
        isResizing = false;

        setCursor(Qt::ArrowCursor);
    }

    else {
        diagram.clearSelection();
    }

    update();
}

void CanvasWidget::setBackgroundColor(const QColor& color){

    backgroundColor = color;
    update();
}

QColor CanvasWidget::getBackgroundColor() const {
    return backgroundColor;
}

QRectF CanvasWidget::getSelectionBox() const{
    auto obj = diagram.getSelectedObject();

    if (!obj){
        return QRectF();
    }

    QRectF box = obj -> getBoundingBox();
    box.adjust(-6, -6, 6, 6);   // padding

    return box;
}

void CanvasWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // drawing background
    painter.fillRect(rect(), backgroundColor);

    // drawing all obj
    for (const auto& obj : diagram.getObjects()) {
        obj -> draw(painter);
    }

    // selection (draw)
    auto selected = diagram.getSelectedObject();

    if (selected) {

        QRectF box = selected -> getBoundingBox();

        box.adjust(-6, -6, 6, 6);

        QPen dashedPen(Qt::black);
        dashedPen.setWidth(1);

        dashedPen.setStyle(Qt::DashLine);

        painter.setPen(dashedPen);
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(box);

        const double size = 8;

        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);

        painter.drawRect(box.topLeft().x() - size/2, box.topLeft().y() - size/2, size, size);

        painter.drawRect(box.topRight().x() - size/2, box.topRight().y() - size/2, size, size);

        painter.drawRect(box.bottomLeft().x() - size/2, box.bottomLeft().y() - size/2, size, size);

        painter.drawRect(box.bottomRight().x() - size/2, box.bottomRight().y() - size/2, size, size);
    }

    if (previewObject) {
        previewObject -> draw(painter);
    }
}
