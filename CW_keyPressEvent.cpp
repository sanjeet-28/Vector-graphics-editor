#include "canvaswidget.h"

using namespace std;

void CanvasWidget::keyPressEvent(QKeyEvent* event){

    if (event->key() == Qt::Key_C) {
        diagram.copySelected();
    }

    if (event->key() == Qt::Key_V) {
        diagram.paste();
        update();
    }

    if (event->key() == Qt::Key_Delete) {
        diagram.deleteSelected();
        update();
    }

    if (event->key() == Qt::Key_Z) {
        diagram.undo();
        update();
    }

    if (event->key() == Qt::Key_Y) {
        diagram.redo();
        update();
    }

    // TODO rest
    // save
    // save as
}
