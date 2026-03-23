COP290 ASSIGNMENT 1: Vector Graphics Editor

DESCRIPTION:
This project is a GUI-based vector drawing application built using C++ and Qt framework.

It allows users to create and edit graphical objects on a canvas, including rectangles, circles, hexagons, lines, freehand drawings, and text.
Users can select, move, resize, and modify objects. The application supports undo/redo functionality using the Command design pattern.
The editor also supports saving drawings in SVG format and reopening them using a custom-built SVG parser.


SYSTEM REQUIREMENTS:
Operating System: Windows 10 
Programming Language: C++
C++ Standard: C++17
Framework: Qt 6 (Widgets module)
Build System: CMake (version 3.16 or higher)
Compiler: MinGW (Windows)


Compile and Run Instructions:
1) Build Instructions (Using CMake):
Step 1: Create a Build Directory
            mkdir build
            cd build
Step 2: Configure the Project
            cmake ..
        If Qt6 is not automatically detected, you may need to specify the Qt installation path:
            cmake -DCMAKE_PREFIX_PATH="path_to_qt6" ..
Step 3: Build the Project
        On Windows (MinGW):
            mingw32-make

2) Run Instructions
Run the application:
    On Windows:
            MyProject.exe


PROJECT STRUCTURE:
CMakeLists.txt

Header Files:
    GraphicsObject.h
    Circle.h
    Diagram.h
    SVGParser.h
    Hexagon.h
    Line.h
    Rectangle.h
    RoundedRectangle.h
    Text.h
    canvaswidget.h
    freehand.h
    command.h
    addcommand.h
    MoveCommand.h
    deletecommand.h
    Mainwindow.h
    StyleChangeCommand.h
    resizehandle.h
    resizecommand.h
    BackgroundColorCommand.h
    SVGUtils.h
    parsesvgroot.h
    parsecircle.h
    parserect.h
    parseline.h
    parsepolygon.h
    parsetext.h
    parsepolyline.h

Source files:
    main.cpp
    GraphicsObject.cpp
    Circle.cpp
    Diagram.cpp
    SVGParser.cpp
    Hexagon.cpp
    Line.cpp
    Rectangle.cpp
    RoundedRectangle.cpp
    Text.cpp
    canvaswidget.cpp
    freehand.cpp
    command.cpp
    addcommand.cpp
    MoveCommand.cpp
    deletecommand.cpp
    Mainwindow.cpp
    StyleChangeCommand.cpp
    resizehandle.cpp
    resizecommand.cpp
    BackgroundColorCommand.cpp
    CW_mousePressEvent.cpp
    CW_mouseMoveEvent.cpp
    CW_mouseReleaseEvent.cpp
    CW_keyPressEvent.cpp
    CW_helpers.cpp
    Diagram2.cpp
    MW_toolbar.cpp
    SVGUtils.cpp
    parsesvgroot.cpp
    parsecircle.cpp
    parserect.cpp
    parseline.cpp
    parsepolygon.cpp
    parsetext.cpp
    parsepolyline.cpp


FEATURES IMPLEMENTED:
    Double click the object to select
    
    Drawing Tools
        Draw Rectangle
        Draw Rounded Rectangle
        Draw Circle
        Draw Hexagon
        Draw Line
        Freehand drawing
        Add Text directly on canvas
    Object Manipulation
        Select objects
        Move objects using drag
        Resize objects using corner handles
        Proportional resizing for circle and hexagon
        Font resizing for text objects
    Styling Options
        Change stroke color
        Change fill color
        Change stroke width
        Change canvas background color
    Undo / Redo System
        Add object
        Delete object
        Move object
        Resize object
        Change style
        Change background color
    SVG Support
        Save drawing as SVG file
        Open SVG file