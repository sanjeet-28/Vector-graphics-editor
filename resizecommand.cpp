#include "ResizeCommand.h"


ResizeCommand::ResizeCommand(GraphicsObject* obj,
                             const QRectF& oldBox,
                             const QRectF& newBox)
    : object(obj),
    oldBox(oldBox),
    newBox(newBox)
{
}

void ResizeCommand::execute()
{
    if (object) {
        object->setFromBoundingBox(newBox);
    }
}

void ResizeCommand::undo()
{
    if (object) {
        object->setFromBoundingBox(oldBox);
    }
}


