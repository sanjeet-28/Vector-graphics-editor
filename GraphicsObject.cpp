#include "GraphicsObject.h"

using namespace std;

GraphicsObject::GraphicsObject(const std::string& strokeColor,
                               const std::string& fillColor,
                               double strokeWidth)
    : strokeColor(strokeColor),
    fillColor(fillColor),
    strokeWidth(strokeWidth) {
}

void GraphicsObject::setStrokeColor(const std::string& color){

    strokeColor = color;
}

void GraphicsObject::setFillColor(const std::string& color){

    fillColor = color;
}

void GraphicsObject::setStrokeWidth(double width){

    strokeWidth = width;
}

std::string GraphicsObject::getStrokeColor() const{

    return strokeColor;
}

std::string GraphicsObject::getFillColor() const{

    return fillColor;
}

double GraphicsObject::getStrokeWidth() const{

    return strokeWidth;
}
