#include "StyleChangeCommand.h"

StyleChangeCommand::StyleChangeCommand(
    GraphicsObject* obj,
    const std::string& newStroke,
    const std::string& newFill,
    double newWidth)
    : object(obj),
    newStroke(newStroke),
    newFill(newFill),
    newWidth(newWidth)
{
    if (object) {
        oldStroke = object->getStrokeColor();
        oldFill = object->getFillColor();
        oldWidth = object->getStrokeWidth();
    }
}

void StyleChangeCommand::execute()
{
    if (!object) return;

    object->setStrokeColor(newStroke);

    object->setFillColor(newFill);

    object->setStrokeWidth(newWidth);
}

void StyleChangeCommand::undo()
{
    if (!object) return;


    object->setStrokeColor(oldStroke);

    object->setFillColor(oldFill);

    object->setStrokeWidth(oldWidth);
}
