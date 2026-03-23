# Micro Vector Editor (SVG)

## 📌 Overview

This project is a **micro vector graphics editor** developed in **C++**, capable of reading, rendering, editing, and writing SVG (Scalable Vector Graphics) files. The application is built with a **custom XML/SVG parser** (without using third-party parsing libraries) and uses **Qt** for GUI rendering.

The editor allows users to create and modify vector graphics interactively, with all changes reflected in real-time and saved back into valid SVG format.

---

## 🚀 Features

* Custom-built **SVG/XML parser** (no external libraries)
* Support for multiple shapes:

  * Rectangle
  * Rounded Rectangle
  * Circle
  * Line
  * Hexagon
  * Freehand Sketch
  * Text
* Editing capabilities:

  * Create, move, resize shapes
  * Change stroke and fill colors
* File operations:

  * Open SVG (restricted subset)
  * Save / Save As
* Clipboard operations:

  * Cut, Copy, Paste
* Undo / Redo functionality
* Real-time rendering using Qt GUI
* Modular and clean **object-oriented design**

---

## 🛠️ Tech Stack

* **Language:** C++
* **GUI Framework:** Qt (Community Edition)
* **Build System:** CMake
* **Concepts Used:**

  * Object-Oriented Programming (OOP)
  * Smart Pointers
  * Custom Parsing (XML/SVG)
  * Data Structures (for undo/redo)

---

## ⚙️ Build Instructions

### Prerequisites

* C++ compiler (g++ / clang++)
* CMake
* Qt installed

### Steps
* Open Qt Creator
* click "open Project"
* Navigate to the project directory and select the CMakeLists.txt file
* Press Ctrl + R or click the Run button to build and execute the application


## 📖 How It Works

* The program reads an SVG file and parses it using a custom XML parser.
* Each SVG element is mapped to a corresponding C++ object.
* The GUI displays these objects on a canvas.
* Any modification updates the internal model and is reflected instantly.
* The updated model is serialized back into an SVG file.


## ⚠️ Notes

* Only a **restricted subset of SVG** is supported.
* No third-party parsing libraries are used for XML/SVG.
* Designed as part of a programming assignment.

---

## 👤 Author

* Sanjeet

---

