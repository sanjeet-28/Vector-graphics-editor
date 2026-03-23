#include "addcommand.h"
#include "deletecommand.h"
#include "Diagram.h"


GraphicsObject* Diagram::getSelectedObject() const {
    return selectedObject;
}

void Diagram::clearSelection() {
    selectedObject = nullptr;
}

std::unique_ptr<GraphicsObject> Diagram::removeObjectAt(size_t index) {

    if (index >= objects.size()){
        return nullptr;
    }

    auto obj = std::move(objects[index]);
    objects.erase(objects.begin() + index);

    return obj;
}

void Diagram::insertObjectAt(size_t index, std::unique_ptr<GraphicsObject> obj) {
    if (index > objects.size()){
        index = objects.size();
    }

    objects.insert(objects.begin() + index, std::move(obj));
}

void Diagram::copySelected() {
    if (selectedObject){
        clipboard = selectedObject->clone();
    }
}

void Diagram::paste() {

    if (!clipboard)
        return;

    auto newObj = clipboard->clone();

    // offset
    newObj->move(10, 10);

    executeCommand(

        std::make_unique<AddCommand>(

            *this,

            std::move(newObj)
            )
        );
}

void Diagram::deleteSelected() {
    if (!selectedObject){
        return;
    }

    for (size_t i = 0; i < objects.size(); ++i) {

        if (objects[i].get() == selectedObject) {

            executeCommand(

                std::make_unique<DeleteCommand>(
                    *this,
                    i
                    )
                );

            selectedObject = nullptr;

            break;
        }
    }
}


void Diagram::clear() {
    objects.clear();

    while (!undoStack.empty())
        undoStack.pop();

    while (!redoStack.empty())
        redoStack.pop();

    selectedObject = nullptr;
}

void Diagram::setSize(double w, double h) {

    width = w;
    height = h;
}

void Diagram::loadFrom(const Diagram& other) {

    clear();

    width = other.width;
    height = other.height;

    for (const auto& obj : other.getObjects()) {

        addObject(obj->clone());
    }
}

std::string backgroundColor = "white";

void Diagram::setBackgroundColor(const std::string& color) {

    backgroundColor = color;
}

std::string Diagram::getBackgroundColor() const {

    return backgroundColor;
}
