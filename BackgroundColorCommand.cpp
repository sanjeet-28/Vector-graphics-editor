#include "BackgroundColorCommand.h"
#include "canvaswidget.h"

BackgroundColorCommand::BackgroundColorCommand(
    CanvasWidget* canvas,
    const QColor& oldColor,
    const QColor& newColor)
    : canvas(canvas),
    oldColor(oldColor),
    newColor(newColor) {

}

void BackgroundColorCommand::execute(){
    canvas->setBackgroundColor(newColor);
}

void BackgroundColorCommand::undo(){
    canvas->setBackgroundColor(oldColor);
}
