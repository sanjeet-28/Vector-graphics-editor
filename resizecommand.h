#ifndef RESIZECOMMAND_H
#define RESIZECOMMAND_H

#include "Command.h"
#include "GraphicsObject.h"
#include <QRectF>

class ResizeCommand : public Command
{
public:
    ResizeCommand(GraphicsObject* obj,
                  const QRectF& oldBox,
                  const QRectF& newBox);

    void execute() override;
    void undo() override;

private:
    GraphicsObject* object;

    QRectF oldBox;
    QRectF newBox;
};

#endif
