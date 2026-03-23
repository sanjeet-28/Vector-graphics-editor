#include "canvaswidget.h"
#include <memory>
#include "MoveCommand.h"
#include "addcommand.h"
#include "resizecommand.h"


void CanvasWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QPointF pos = event -> position();

    if (currentTool == ToolMode::Select && dragging) {

        dragging = false;

        auto obj = diagram.getSelectedObject();

        if (!obj){
            return;
        }

        double totalDx = pos.x() - dragStartPos.x();
        double totalDy = pos.y() - dragStartPos.y();

        obj -> move(-totalDx, -totalDy);

        if (totalDx != 0 || totalDy != 0) {

            diagram.executeCommand(std::make_unique<MoveCommand>(obj, totalDx, totalDy));
        }

        update();

        setCursor(Qt::ArrowCursor);

        return;
    }

    if (isDrawing && previewObject) {

        diagram.executeCommand(

            std::make_unique<AddCommand>(
                diagram,

                std::move(previewObject)

                )
            );

        isDrawing = false;

        previewObject.reset();

        update();
    }

    if (isResizing) {

        auto obj = diagram.getSelectedObject();

        QRectF resizeEndBox = obj -> getBoundingBox();

        diagram.executeCommand(

            std::make_unique<ResizeCommand>(
                obj,
                resizeStartBox,
                resizeEndBox
                )
            );

        isResizing = false;

        activeHandle = ResizeHandle::None;

        update();

        setCursor(Qt::ArrowCursor);

        return;
    }

}
