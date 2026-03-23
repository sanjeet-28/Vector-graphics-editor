#ifndef STYLECHANGECOMMAND_H
#define STYLECHANGECOMMAND_H

#include "Command.h"
#include "GraphicsObject.h"
#include <string>

class StyleChangeCommand : public Command
{
public:
    StyleChangeCommand(GraphicsObject* obj,
                       const std::string& newStroke,
                       const std::string& newFill,
                       double newWidth);

    void execute() override;
    void undo() override;

private:
    GraphicsObject* object;

    std::string oldStroke;
    std::string oldFill;
    double oldWidth;

    std::string newStroke;
    std::string newFill;
    double newWidth;
};

#endif
