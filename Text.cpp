#include "Text.h"
#include <QPen>
#include <QColor>
#include <QFontMetrics>

using namespace std;

Text::Text(double x, double y,
           const string &content,
           const string &strokeColor,
           double strokeWidth,
           double fontSize)
    : GraphicsObject(strokeColor, "none", strokeWidth),
    fontSize(fontSize)
{
    this -> x = x;
    this -> y = y;
    this -> content = content;
}


void Text::move(double dx, double dy) {
    x += dx;
    y += dy;
}


QRectF Text::getBoundingBox() const {

    QFont font;

    font.setPointSizeF(fontSize);

    QFontMetrics fm(font);

    QRect rect = fm.boundingRect(QString::fromStdString(content));

    return QRectF(x, y - rect.height(), rect.width(), rect.height());
}

void Text::draw(QPainter& painter) const {

    QPen pen(QColor(QString::fromStdString(strokeColor)));

    pen.setWidth(strokeWidth);

    painter.setPen(pen);

    QFont font;

    font.setPointSizeF(fontSize);

    painter.setFont(font);

    font.setPointSizeF(fontSize);

    painter.setFont(font);

    painter.drawText(x, y, QString::fromStdString(content));
}


string Text::toSVG() const {
    return "<text x=\"" + to_string(x) +
           "\" y=\"" + to_string(y) +
           "\" fill=\"" + strokeColor +
           "\" stroke-width=\"" + to_string(strokeWidth) +
           "\">" + content + "</text>";

}

std::unique_ptr<GraphicsObject> Text::clone() const {

    return std::make_unique<Text>(*this);
}


void Text::setFromBoundingBox(const QRectF& newBox){

    QRectF oldBox = getBoundingBox();

    if (oldBox.height() == 0)
        return;

    double scaleY = newBox.height() / oldBox.height();

    fontSize *= scaleY;

    x = newBox.x();
    y = newBox.bottom();
}

void Text::setX(double value) {
    x = value;
}

void Text::setY(double value) {
    y = value;
}

void Text::setFontSize(double size) {
    fontSize = size;
}



