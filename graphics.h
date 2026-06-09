#ifndef GRAPHICS_H
#define GRAPHICS_H

#define ROWS 20
#define COLS 50
#define MAX_OBJECTS 100

// Shared canvas array across files
extern char canvas[ROWS][COLS];

// Shape categorizations
typedef enum { LINE, RECTANGLE, CIRCLE, TRIANGLE } ShapeType;

// Structural tracker for tracking individual objects
typedef struct {
    int id;
    ShapeType type;
    int p1, p2, p3, p4, p5, p6;
    int active;
} GraphicObject;

// Core engine function declarations
void initializeCanvas();
void displayCanvas();
void redrawCanvas();

// Shape math function declarations
void drawLine(int r1, int c1, int r2, int c2, char ch);
void drawRectangle(int topRow, int leftCol, int height, int width, char ch);
void drawCircle(int centerR, int centerC, int radius, char ch);
void drawTriangle(int r1, int c1, int r2, int c2, int r3, int c3, char ch);

#endif