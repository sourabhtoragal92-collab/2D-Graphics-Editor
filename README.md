# 2D Graphics Editor (C Mini-Project)

A professional, terminal-based 2D graphics rendering application written in C using a modular architecture.

## 📋 Project Overview
This project implements a virtual canvas buffer using a 2D character array grid (20x50). Users can interactively add, modify, list, and delete geometric shapes via a command-line menu interface.

## 🛠️ Modular System Architecture
The project is split into a structured, professional multi-file format:
- **`graphics.h`**: The blueprint header file containing structure definitions and core function declarations.
- **`graphics.c`**: The functional rendering engine implementing drawing algorithms for shapes.
- **`main.c`**: The execution driver managing the user input loop and menu state.
- **`editor.exe`**: The pre-compiled, standalone Windows executable version of the program.

## 🚀 Features Implemented
- Primitive Shapes: Complete mathematical rendering routines for Lines (`*`), Rectangles, Circles, and Triangles.
- State Manipulation: Complete CRUD capabilities (Create, Read, Update, Delete) for active shapes on the canvas tracking stack.
