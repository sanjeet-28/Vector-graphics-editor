#include <QApplication>
#include "Mainwindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MainWindow window;
    window.showMaximized();


    return app.exec();
}
