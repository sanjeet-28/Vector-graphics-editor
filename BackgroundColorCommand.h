#ifndef BACKGROUNDCOLORCOMMAND_H
#define BACKGROUNDCOLORCOMMAND_H

#include "Command.h"
#include <QColor>

class CanvasWidget;

class BackgroundColorCommand : public Command
{
public:
    BackgroundColorCommand(CanvasWidget* canvas,
                           const QColor& oldColor,
                           const QColor& newColor);

    void execute() override;
    void undo() override;

private:
    CanvasWidget* canvas;
    QColor oldColor;
    QColor newColor;
};

#endif
