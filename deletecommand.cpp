#include "deletecommand.h"

DeleteCommand::DeleteCommand(Diagram& d, size_t index)
    : diagram(d), index(index) {}

void DeleteCommand::execute() {

    removedObject = diagram.removeObjectAt(index);
}

void DeleteCommand::undo() {

    if (removedObject){
        diagram.insertObjectAt(index, std::move(removedObject));
    }
}
