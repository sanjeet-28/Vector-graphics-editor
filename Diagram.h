#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <vector>
#include <memory>
#include <string>
#include <stack>
#include <memory>
#include <QColor>



#include "Command.h"
#include "GraphicsObject.h"

using namespace std;

class Diagram {
public:
    Diagram(double width, double height);

    void addObject(unique_ptr<GraphicsObject> obj);
    void moveAll(double dx, double dy);
    string toSVG(const QColor& bgColor) const;


    const vector<unique_ptr<GraphicsObject>>& getObjects() const;

    void executeCommand(std::unique_ptr<Command> cmd);
    void undo();
    void redo();

    std::unique_ptr<GraphicsObject> removeLastObject();

    GraphicsObject* selectedObject = nullptr;

    GraphicsObject* selectObjectAt(double x, double y);
    GraphicsObject* getSelectedObject() const;
    void clearSelection();

    std::unique_ptr<GraphicsObject> removeObjectAt(size_t index);
    void insertObjectAt(size_t index, std::unique_ptr<GraphicsObject> obj);

    std::unique_ptr<GraphicsObject> clipboard;

    void copySelected();
    void paste();
    void deleteSelected();


    void clear();
    void setSize(double w, double h);
    void loadFrom(const Diagram& other);
    void setBackgroundColor(const std::string& color);
    std::string getBackgroundColor() const;





private:
    double width;
    double height;
    vector<unique_ptr<GraphicsObject>> objects;
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

};

#endif 
