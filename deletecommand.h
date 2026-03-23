#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "Command.h"
#include "Diagram.h"
#include <memory>

class DeleteCommand : public Command {
private:
    Diagram& diagram;
    std::unique_ptr<GraphicsObject> removedObject;
    size_t index;

public:
    DeleteCommand(Diagram& d, size_t index);

    void execute() override;
    void undo() override;
};

#endif
