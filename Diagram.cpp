#include "Diagram.h"
#include <sstream>


using namespace std;

Diagram::Diagram(double width, double height){
    this -> width = width;
    this -> height = height;
}

void Diagram::addObject(unique_ptr<GraphicsObject> obj){

    objects.push_back(std::move(obj));
}

void Diagram::moveAll(double dx, double dy){

    for (const auto &obj : objects){

        obj -> move(dx, dy);
    }
}

string Diagram::toSVG(const QColor& bgColor) const {
    ostringstream oss;

    oss << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"100vw\" height=\"100vh\" "
        << "viewBox=\"0 0 " << width << " " << height << "\" "
        << "style=\"margin:0; padding:0; display:block;\">\n";


    // bg rect
    oss << "  <rect width=\"100%\" height=\"100%\" fill=\""
        << bgColor.name().toStdString()
        << "\" />\n";


    for (const auto& obj : objects) {

        oss << "  " << obj->toSVG() << "\n";
    }

    oss << "</svg>";

    return oss.str();
}


const vector<unique_ptr<GraphicsObject>>& Diagram::getObjects() const {
    return objects;
}

void Diagram::executeCommand(std::unique_ptr<Command> cmd) {

    cmd->execute();

    undoStack.push(std::move(cmd));

    while (!redoStack.empty()){
        redoStack.pop();
    }
}

void Diagram::undo() {

    if (undoStack.empty()){
        return;
    }

    auto cmd = std::move(undoStack.top());

    undoStack.pop();

    cmd->undo();
    redoStack.push(std::move(cmd));
}

void Diagram::redo() {
    if (redoStack.empty())
        return;

    auto cmd = std::move(redoStack.top());

    redoStack.pop();

    cmd->execute();
    undoStack.push(std::move(cmd));
}


std::unique_ptr<GraphicsObject> Diagram::removeLastObject() {
    if (objects.empty()){
        return nullptr;
    }

    auto obj = std::move(objects.back());
    objects.pop_back();

    return obj;
}

GraphicsObject* Diagram::selectObjectAt(double x, double y) {

    for (auto it = objects.rbegin(); it != objects.rend(); ++it) {

        if ((*it)->getBoundingBox().contains(x, y)) {  //alll

            selectedObject = it->get();
            return selectedObject;
        }
    }

    selectedObject = nullptr;

    return nullptr;
}


