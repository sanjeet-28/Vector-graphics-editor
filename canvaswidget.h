#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QLineEdit>


#include "ResizeHandle.h"

#include "Diagram.h"

enum class ToolMode {
    Select,
    Rectangle,
    RoundedRectangle,
    Circle,
    Line,
    Hexagon,
    Freehand,
    Text

};

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    CanvasWidget(Diagram& diagram, QWidget* parent = nullptr);
    void setToolMode(ToolMode mode);

    void setStrokeColor(const QString& color);
    void setFillColor(const QString& color);
    void setStrokeWidth(int width);
    void setBackgroundColor(const QColor& color);

    QColor getBackgroundColor() const;
    QRectF getSelectionBox() const;


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    Diagram& diagram;
    bool dragging = false;
    QPointF lastMousePos;
    QPointF dragStartPos;

    ToolMode currentTool = ToolMode::Select;

    bool isDrawing = false;
    QPointF startPoint;
    QPointF currentPoint;

    std::unique_ptr<GraphicsObject> previewObject;

    QString currentStrokeColor = "black";
    QString currentFillColor = "none";
    int currentStrokeWidth = 2;

    bool isResizing = false;

    ResizeHandle activeHandle = ResizeHandle::None;

    QRectF resizeStartBox;

    QColor backgroundColor = Qt::white;

    QLineEdit* textEditor = nullptr;
    QPointF textPosition;


};




#endif
