cmake_minimum_required(VERSION 3.16)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(MyProject
    main.cpp

    GraphicsObject.cpp GraphicsObject.h
    Circle.cpp Circle.h
    Diagram.cpp Diagram.h
    SVGParser.cpp SVGParser.h
    Hexagon.cpp Hexagon.h
    Line.cpp Line.h
    Rectangle.cpp Rectangle.h
    RoundedRectangle.cpp RoundedRectangle.h
    Text.cpp Text.h
    canvaswidget.h canvaswidget.cpp
    freehand.h freehand.cpp
    command.h command.cpp
    addcommand.h addcommand.cpp
    MoveCommand.h MoveCommand.cpp
    deletecommand.h deletecommand.cpp
    Mainwindow.h Mainwindow.cpp
    StyleChangeCommand.h StyleChangeCommand.cpp
    resizehandle.h resizehandle.cpp
    resizecommand.h resizecommand.cpp
    BackgroundColorCommand.h BackgroundColorCommand.cpp

    CW_mousePressEvent.cpp
    CW_mouseMoveEvent.cpp
    CW_mouseReleaseEvent.cpp
    CW_keyPressEvent.cpp
    CW_helpers.cpp
    Diagram2.cpp
    MW_toolbar.cpp

    SVGUtils.h SVGUtils.cpp
    parsesvgroot.h parsesvgroot.cpp
    parsecircle.h parsecircle.cpp
    parserect.h parserect.cpp
    parseline.h parseline.cpp
    parsepolygon.h parsepolygon.cpp
    parsetext.h parsetext.cpp
    parsepolyline.h parsepolyline.cpp


)

target_link_libraries(MyProject Qt6::Widgets)
