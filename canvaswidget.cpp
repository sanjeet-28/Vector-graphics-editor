#include "canvaswidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <cmath>
#include <QInputDialog>

using namespace std;

CanvasWidget::CanvasWidget(Diagram& d, QWidget* parent)
    : QWidget(parent), diagram(d){

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setFocusPolicy(Qt::StrongFocus);

    setMouseTracking(true);

    currentStrokeColor = "black";
    currentFillColor = "none";
}

void CanvasWidget::setToolMode(ToolMode mode){
    currentTool = mode;
}

void CanvasWidget::setStrokeColor(const QString& color){
    currentStrokeColor = color;
}

void CanvasWidget::setFillColor(const QString& color){
    currentFillColor = color;
}

void CanvasWidget::setStrokeWidth(int width){
    currentStrokeWidth = width;
}

void CanvasWidget::resizeEvent(QResizeEvent* event){
    diagram.setSize(width(), height());

    QWidget::resizeEvent(event);
}








