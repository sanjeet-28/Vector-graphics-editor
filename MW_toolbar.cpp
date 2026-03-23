#include "Mainwindow.h"
#include "StyleChangeCommand.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QToolBar>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include "BackgroundColorCommand.h"

void MainWindow::createToolBar(){

    toolBar = new QToolBar("Tools", this);

    addToolBar(Qt::LeftToolBarArea, toolBar);

    toolBar -> setOrientation(Qt::Vertical);
    toolBar -> setMovable(true);

    toolBar -> setIconSize(QSize(24, 24));
    toolBar -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    // shape tools create
    rectTool = new QAction("Rectangle", this);
    roundedRectTool = new QAction("RoundedRect", this);
    circleTool = new QAction("Circle", this);
    lineTool = new QAction("Line", this);
    hexagonTool = new QAction("Hexagon", this);
    freehandTool = new QAction("Freehand", this);
    textTool = new QAction("Text", this);

    selectTool = new QAction("Select", this);

    toolBar -> addAction(selectTool);

    toolBar -> addSeparator();

    removeButton = new QPushButton("Remove");
    toolBar -> addWidget(removeButton);

    toolBar -> addSeparator();

    toolBar -> addAction(rectTool);
    toolBar -> addAction(roundedRectTool);
    toolBar -> addAction(circleTool);
    toolBar -> addAction(lineTool);
    toolBar -> addAction(hexagonTool);
    toolBar -> addAction(freehandTool);
    toolBar -> addAction(textTool);

    toolBar -> addSeparator();

    // Styling Tools
    strokeColorButton = new QPushButton("Stroke");
    fillColorButton = new QPushButton("Fill");

    backgroundColorButton = new QPushButton("Background");
    toolBar -> addWidget(backgroundColorButton);

    strokeWidthSpin = new QSpinBox();

    strokeWidthSpin -> setRange(1, 20);
    strokeWidthSpin -> setValue(2);

    toolBar -> addWidget(strokeColorButton);
    toolBar -> addWidget(fillColorButton);
    toolBar -> addWidget(strokeWidthSpin);

    connect(rectTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::Rectangle);
    });

    connect(roundedRectTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::RoundedRectangle);
    });

    connect(circleTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::Circle);
    });

    connect(lineTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::Line);
    });

    connect(hexagonTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::Hexagon);
    });

    connect(freehandTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::Freehand);
    });

    connect(textTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::Text);
    });

    connect(strokeColorButton, &QPushButton::clicked, [this]() {

        QColor color = QColorDialog::getColor(Qt::black, this);

        if (!color.isValid())
            return;

        auto obj = diagram.getSelectedObject();

        if (obj) {
            diagram.executeCommand(
                std::make_unique<StyleChangeCommand>(
                    obj,
                    color.name().toStdString(),
                    obj -> getFillColor(),
                    obj -> getStrokeWidth()
                    )
                );
            canvas -> update();
        }

        canvas -> setStrokeColor(color.name());
    });


    connect(fillColorButton, &QPushButton::clicked, [this]() {

        QColor color = QColorDialog::getColor(Qt::white, this);

        if (!color.isValid())
            return;

        auto obj = diagram.getSelectedObject();

        if (obj) {
            diagram.executeCommand(
                std::make_unique<StyleChangeCommand>(

                    obj,
                    obj -> getStrokeColor(),
                    color.name().toStdString(),
                    obj -> getStrokeWidth()
                    )
                );

            canvas -> update();
        }

        canvas -> setFillColor(color.name());
    });

    connect(strokeWidthSpin,
            QOverload<int>::of(&QSpinBox::valueChanged), [this](int value) {

                auto obj = diagram.getSelectedObject();

                if (obj) {
                    diagram.executeCommand(
                        std::make_unique<StyleChangeCommand>(

                            obj,
                            obj -> getStrokeColor(),
                            obj -> getFillColor(),
                            value
                            )
                        );

                    canvas -> update();
                }

                canvas -> setStrokeWidth(value);
            });

    connect(selectTool, &QAction::triggered, [this]() {

        canvas -> setToolMode(ToolMode::Select);
    });

    connect(backgroundColorButton, &QPushButton::clicked, [this]() {

        QColor color = QColorDialog::getColor(Qt::white, this);

        if (!color.isValid())
            return;

        QColor oldColor = canvas -> getBackgroundColor();

        diagram.executeCommand(
            std::make_unique<BackgroundColorCommand>(

                canvas,
                oldColor,
                color
                )
            );
    });

    connect(removeButton, &QPushButton::clicked, [this]() {

        if (diagram.getSelectedObject()) {

            diagram.deleteSelected();
            canvas -> update();
        }
    });
}
