#include "canvaswidget.h"
#include "freehand.h"
#include "Text.h"
#include "addcommand.h"

using namespace std;

void CanvasWidget::mousePressEvent(QMouseEvent* event){
    QPointF pos = event -> position();

    if (currentTool == ToolMode::Select) {

        auto obj = diagram.getSelectedObject();

        if (obj) {

            QRectF box = getSelectionBox();
            double size = 8;

            QRectF tl(box.topLeft() - QPointF(size/2, size/2), QSizeF(size, size));


            QRectF tr(box.topRight() - QPointF(size/2, size/2), QSizeF(size, size));

            QRectF bl(box.bottomLeft() - QPointF(size/2, size/2), QSizeF(size, size));

            QRectF br(box.bottomRight() - QPointF(size/2, size/2), QSizeF(size, size));

            if (tl.contains(pos)) {
                isResizing = true;

                activeHandle = ResizeHandle::TopLeft;
                setCursor(Qt::SizeFDiagCursor);

                resizeStartBox = obj -> getBoundingBox();

                lastMousePos = pos;

                return;
            }
            else if (tr.contains(pos)) {
                isResizing = true;

                activeHandle = ResizeHandle::TopRight;
                setCursor(Qt::SizeFDiagCursor);

                resizeStartBox = obj -> getBoundingBox();

                lastMousePos = pos;
                return;
            }
            else if (bl.contains(pos)) {
                isResizing = true;

                activeHandle = ResizeHandle::BottomLeft;
                setCursor(Qt::SizeFDiagCursor);

                resizeStartBox = obj -> getBoundingBox();
                lastMousePos = pos;

                return;
            }
            else if (br.contains(pos)) {
                isResizing = true;

                activeHandle = ResizeHandle::BottomRight;
                setCursor(Qt::SizeFDiagCursor);

                resizeStartBox = obj -> getBoundingBox();
                lastMousePos = pos;

                return;
            }
        }

        // If not resizing, tryin to select obj normally
        obj = diagram.selectObjectAt(pos.x(), pos.y());
        setCursor(Qt::ArrowCursor);

        if (obj) {
            dragging = true;

            lastMousePos = pos;
            dragStartPos = pos;

            setCursor(Qt::SizeAllCursor);
        }

        update();
        return;
    }

    if (currentTool == ToolMode::Freehand) {
        isDrawing = true;

        startPoint = pos;

        previewObject = std::make_unique<Freehand>(
            std::vector<QPointF>{pos},
            currentStrokeColor.toStdString(),
            currentStrokeWidth
            );

        return;
    }

    if (currentTool == ToolMode::Text) {

        if (textEditor){
            return;
        }

        textPosition = pos;

        textEditor = new QLineEdit(this);

        textEditor -> move(pos.x(), pos.y());

        textEditor -> setFixedWidth(150);
        textEditor -> show();

        textEditor -> setFocus();

        // When we press Enter
        connect(textEditor, &QLineEdit::editingFinished, [this]() {

            QString text = textEditor -> text();

            if (!text.isEmpty()) {

                diagram.executeCommand(

                    std::make_unique<AddCommand>(

                        diagram,

                        std::make_unique<Text>(
                            textPosition.x(),
                            textPosition.y(),
                            text.toStdString(),
                            currentStrokeColor.toStdString(),
                            currentStrokeWidth
                            )
                        )
                    );
            }

            textEditor -> deleteLater();
            textEditor = nullptr;

            update();
        });

        return;
    }

    isDrawing = true;
    startPoint = pos;
    currentPoint = pos;

}
