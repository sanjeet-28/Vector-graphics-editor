#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Command.h"
#include "GraphicsObject.h"

class MoveCommand : public Command {
private:
    GraphicsObject* object;
    double dx;
    double dy;

public:
    MoveCommand(GraphicsObject* obj,
                double dx,
                double dy);

    void execute() override;
    void undo() override;
};

#endif
