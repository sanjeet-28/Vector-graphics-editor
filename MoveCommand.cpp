#include "MoveCommand.h"

MoveCommand::MoveCommand(GraphicsObject* obj,
                         double dx,
                         double dy)
    : object(obj),
    dx(dx),
    dy(dy) {}

void MoveCommand::execute() {
    if (object){
        object->move(dx, dy);
    }
}

void MoveCommand::undo() {
    if (object){
        object->move(-dx, -dy);
    }
}
