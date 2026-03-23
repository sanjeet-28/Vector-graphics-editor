#include <QMenuBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "SVGParser.h"
#include <QToolBar>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include "BackgroundColorCommand.h"
#include "Mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    diagram(1, 1)   // temporary small value
{
    canvas = new CanvasWidget(diagram, this);
    setCentralWidget(canvas);

    createMenus();
    createToolBar();

    showMaximized();
}

void MainWindow::createMenus()
{
    //  actions
    newAction = new QAction("New", this);
    openAction = new QAction("Open", this);
    saveAction = new QAction("Save", this);
    saveAsAction = new QAction("Save As", this);
    closeAction = new QAction("Close", this);

    cutAction = new QAction("Cut", this);
    copyAction = new QAction("Copy", this);
    pasteAction = new QAction("Paste", this);
    undoAction = new QAction("Undo", this);
    redoAction = new QAction("Redo", this);

    // adding to menubaar
    menuBar()->addAction(newAction);
    menuBar()->addAction(openAction);
    menuBar()->addAction(saveAction);
    menuBar()->addAction(saveAsAction);

    menuBar()->addSeparator();

    menuBar()->addAction(cutAction);
    menuBar()->addAction(copyAction);
    menuBar()->addAction(pasteAction);

    menuBar()->addSeparator();

    menuBar()->addAction(undoAction);
    menuBar()->addAction(redoAction);
    menuBar()->addAction(closeAction);


    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeFile);

    connect(cutAction, &QAction::triggered, this, &MainWindow::cut);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copy);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undo);
    connect(redoAction, &QAction::triggered, this, &MainWindow::redo);
}


void MainWindow::newFile(){
    diagram.clear();

    canvas->update();


    currentFilePath.clear();
}

void MainWindow::openFile(){

    QString fileName = QFileDialog::getOpenFileName(

        this,
        "Open SVG File",
        "",
        "SVG Files (*.svg)"
        );

    if (fileName.isEmpty())
        return;

    SVGParser parser;

    Diagram loadedDiagram = parser.parseFromFile(fileName.toStdString());

    diagram = std::move(loadedDiagram);

    diagram.setSize(canvas->width(), canvas->height());

    canvas->setBackgroundColor(
        QColor(QString::fromStdString(diagram.getBackgroundColor()))
        );

    canvas->update();

    currentFilePath = fileName;
}

void MainWindow::saveFile(){
    if (currentFilePath.isEmpty()) {
        saveFileAs();
        return;
    }

    QFile file(currentFilePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QMessageBox::warning(this, "Error", "Cannot save file.");

        return;
    }

    QTextStream out(&file);

    out << QString::fromStdString(
        diagram.toSVG(canvas->getBackgroundColor())
        );

    file.close();
}


void MainWindow::saveFileAs(){

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save SVG File",
        "",
        "SVG Files (*.svg)"
        );

    if (fileName.isEmpty())
        return;

    currentFilePath = fileName;

    saveFile();
}


void MainWindow::closeFile(){
    diagram.clear();

    diagram.setBackgroundColor("white");

    canvas->setBackgroundColor(Qt::white);

    currentFilePath.clear();

    canvas->update();
}

void MainWindow::cut(){
    diagram.copySelected();
    diagram.deleteSelected();
    canvas->update();
}

void MainWindow::copy(){
    diagram.copySelected();
}

void MainWindow::paste(){
    diagram.paste();
    canvas->update();
}

void MainWindow::undo(){
    diagram.undo();
    canvas->update();
}

void MainWindow::redo(){
    diagram.redo();
    canvas->update();
}
