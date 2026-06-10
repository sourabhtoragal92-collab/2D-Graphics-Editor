#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"

char canvas[ROWS][COLS];
GraphicObject objectList[MAX_OBJECTS];
int objectCount = 0;

void initializeCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = ' '; 
        }
    }
}

void displayCanvas() {
    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");
}

void drawLine(int r1, int c1, int r2, int c2, char ch) {
    int dr = abs(r2 - r1), dc = abs(c2 - c1);
    int sr = (r1 < r2) ? 1 : -1, sc = (c1 < c2) ? 1 : -1;
    int err = dc - dr;
    
    while (1) {
        if (r1 >= 0 && r1 < ROWS && c1 >= 0 && c1 < COLS) canvas[r1][c1] = ch;
        if (r1 == r2 && c1 == c2) break;
        int e2 = 2 * err;
        if (e2 > -dr) { err -= dr; c1 += sc; }
        if (e2 < dc) { err += dc; r1 += sr; }
    }
}

void drawRectangle(int topRow, int leftCol, int height, int width, char ch) {
    for (int c = leftCol; c < leftCol + width; c++) {
        if (topRow >= 0 && topRow < ROWS && c >= 0 && c < COLS) canvas[topRow][c] = ch;
        if (topRow + height - 1 >= 0 && topRow + height - 1 < ROWS && c >= 0 && c < COLS) canvas[topRow + height - 1][c] = ch;
    }
    for (int r = topRow; r < topRow + height; r++) {
        if (r >= 0 && r < ROWS && leftCol >= 0 && leftCol < COLS) canvas[r][leftCol] = ch;
        if (r >= 0 && r < ROWS && leftCol + width - 1 >= 0 && leftCol + width - 1 < COLS) canvas[r][leftCol + width - 1] = ch;
    }
}

void drawCircle(int centerR, int centerC, int radius, char ch) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            double dist = sqrt(pow(r - centerR, 2) + pow(c - centerC, 2));
            if (abs(dist - radius) < 0.6) canvas[r][c] = ch;
        }
    }
}

void drawTriangle(int r1, int c1, int r2, int c2, int r3, int c3, char ch) {
    drawLine(r1, c1, r2, c2, ch);
    drawLine(r2, c2, r3, c3, ch);
    drawLine(r3, c3, r1, c1, ch);
}