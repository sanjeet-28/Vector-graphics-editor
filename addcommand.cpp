#include "addcommand.h"
#include "Diagram.h"

using namespace std;

AddCommand::AddCommand(Diagram& d, unique_ptr<GraphicsObject> obj)
    : diagram(d), object(std::move(obj)) {
}

void AddCommand::execute() {
    diagram.addObject(std::move(object));
}

void AddCommand::undo() {
    object = diagram.removeLastObject();
}

