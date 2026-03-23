#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>
#include <QSpinBox>

#include "canvaswidget.h"
#include "Diagram.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    void createMenus();

    Diagram diagram;
    CanvasWidget* canvas;

    QMenu* fileMenu;
    QMenu* editMenu;

    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* closeAction;

    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* undoAction;
    QAction* redoAction;

    QString currentFilePath;


    QToolBar* toolBar;

    QAction* rectTool;
    QAction* roundedRectTool;
    QAction* circleTool;
    QAction* lineTool;
    QAction* hexagonTool;
    QAction* freehandTool;
    QAction* textTool;
    QAction* selectTool;


    QPushButton* strokeColorButton;
    QPushButton* fillColorButton;
    QSpinBox* strokeWidthSpin;
    QPushButton* backgroundColorButton;

    QPushButton* removeButton;



    void createToolBar();


private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();

    void cut();
    void copy();
    void paste();
    void undo();
    void redo();

};

#endif
