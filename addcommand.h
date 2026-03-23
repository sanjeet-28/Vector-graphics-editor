#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "Command.h"
#include "Diagram.h"
#include "GraphicsObject.h"
#include <memory>

class AddCommand : public Command {
private:
    Diagram& diagram;
    std::unique_ptr<GraphicsObject> object;

public:
    AddCommand(Diagram& d,
               std::unique_ptr<GraphicsObject> obj);

    void execute() override;
    void undo() override;
};

#endif
