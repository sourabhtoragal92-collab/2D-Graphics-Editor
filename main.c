#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 50
#define MAX_OBJECTS 100

// Canvas 2D Array (Requirement 3)
char canvas[ROWS][COLS];

// Enum and Struct to manage dynamic objects for modification/deletion (Requirement 2)
typedef enum { LINE, RECTANGLE, CIRCLE, TRIANGLE } ShapeType;

typedef struct {
    int id;
    ShapeType type;
    int p1, p2, p3, p4, p5, p6; // Generic parameters for shapes
    int active;                 // 1 if active, 0 if deleted
} GraphicObject;

GraphicObject objectList[MAX_OBJECTS];
int objectCount = 0;
int nextId = 1;

// Requirement 4: Function to display the picture canvas
void displayCanvas() {
    // Top Border
    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("|"); // Left boundary
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n"); // Right boundary
    }

    // Bottom Border
    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");
}

// Clear canvas with space gaps or underscores
void initializeCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = ' '; 
        }
    }
}

// --- Phase 3: Shape Rendering Logic (Requirement 1) ---

void drawLine(int r1, int c1, int r2, int c2, char ch) {
    int dr = abs(r2 - r1);
    int dc = abs(c2 - c1);
    int sr = (r1 < r2) ? 1 : -1;
    int sc = (c1 < c2) ? 1 : -1;
    int err = dc - dr;

    while (1) {
        if (r1 >= 0 && r1 < ROWS && c1 >= 0 && c1 < COLS) {
            canvas[r1][c1] = ch;
        }
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
            if (abs(dist - radius) < 0.6) {
                canvas[r][c] = ch;
            }
        }
    }
}

void drawTriangle(int r1, int c1, int r2, int c2, int r3, int c3, char ch) {
    drawLine(r1, c1, r2, c2, ch);
    drawLine(r2, c2, r3, c3, ch);
    drawLine(r3, c3, r1, c1, ch);
}

// Redraws tracking stack from scratch
void redrawCanvas() {
    initializeCanvas();
    for (int i = 0; i < objectCount; i++) {
        if (objectList[i].active) {
            GraphicObject obj = objectList[i];
            if (obj.type == LINE) drawLine(obj.p1, obj.p2, obj.p3, obj.p4, '*');
            else if (obj.type == RECTANGLE) drawRectangle(obj.p1, obj.p2, obj.p3, obj.p4, '*');
            else if (obj.type == CIRCLE) drawCircle(obj.p1, obj.p2, obj.p3, '*');
            else if (obj.type == TRIANGLE) drawTriangle(obj.p1, obj.p2, obj.p3, obj.p4, obj.p5, obj.p6, '*');
        }
    }
}

// --- Phase 4: Dynamic Terminal Interface ---
int main() {
    initializeCanvas();
    int choice = 0;

    while (choice != 5) {
        displayCanvas();
        printf("\n=== 2D GRAPHICS EDITOR (C-Edition) ===\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. List Active Objects\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (objectCount >= MAX_OBJECTS) {
                printf("Error: Max object limits reached!\n");
                continue;
            }
            int typeChoice;
            printf("Select Shape (1: Line, 2: Rect, 3: Circle, 4: Triangle): ");
            scanf("%d", &typeChoice);

            GraphicObject obj;
            obj.id = nextId++;
            obj.active = 1;

            if (typeChoice == 1) {
                obj.type = LINE;
                printf("Enter start row, start col, end row, end col: ");
                scanf("%d %d %d %d", &obj.p1, &obj.p2, &obj.p3, &obj.p4);
            } else if (typeChoice == 2) {
                obj.type = RECTANGLE;
                printf("Enter top row, left col, height, width: ");
                scanf("%d %d %d %d", &obj.p1, &obj.p2, &obj.p3, &obj.p4);
            } else if (typeChoice == 3) {
                obj.type = CIRCLE;
                printf("Enter center row, center col, radius: ");
                scanf("%d %d %d", &obj.p1, &obj.p2, &obj.p3);
            } else if (typeChoice == 4) {
                obj.type = TRIANGLE;
                printf("Enter r1 c1 r2 c2 r3 c3 coordinates: ");
                scanf("%d %d %d %d %d %d", &obj.p1, &obj.p2, &obj.p3, &obj.p4, &obj.p5, &obj.p6);
            }

            objectList[objectCount++] = obj;
            redrawCanvas();

        } else if (choice == 2) {
            int delId, found = 0;
            printf("Enter Object ID to delete: ");
            scanf("%d", &delId);
            for (int i = 0; i < objectCount; i++) {
                if (objectList[i].id == delId && objectList[i].active) {
                    objectList[i].active = 0;
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Object ID not found.\n");
            redrawCanvas();

        } else if (choice == 3) {
            int modId, found = 0;
            printf("Enter Object ID to modify configuration: ");
            scanf("%d", &modId);
            for (int i = 0; i < objectCount; i++) {
                if (objectList[i].id == modId && objectList[i].active) {
                    found = 1;
                    if (objectList[i].type == LINE) {
                        printf("Enter new line coordinates (r1 c1 r2 c2): ");
                        scanf("%d %d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3, &objectList[i].p4);
                    } else if (objectList[i].type == RECTANGLE) {
                        printf("Enter new rect metrics (topRow leftCol height width): ");
                        scanf("%d %d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3, &objectList[i].p4);
                    } else if (objectList[i].type == CIRCLE) {
                        printf("Enter new circle configuration (centerR centerC radius): ");
                        scanf("%d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3);
                    } else if (objectList[i].type == TRIANGLE) {
                        printf("Enter new triangle metrics (r1 c1 r2 c2 r3 c3): ");
                        scanf("%d %d %d %d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3, &objectList[i].p4, &objectList[i].p5, &objectList[i].p6);
                    }
                    break;
                }
            }
            if (!found) printf("Active Object ID not found.\n");
            redrawCanvas();

        } else if (choice == 4) {
            printf("\n--- Active Canvas Artifacts ---\n");
            for (int i = 0; i < objectCount; i++) {
                if (objectList[i].active) {
                    char* typeStr = (objectList[i].type == LINE) ? "Line" : 
                                    (objectList[i].type == RECTANGLE) ? "Rectangle" : 
                                    (objectList[i].type == CIRCLE) ? "Circle" : "Triangle";
                    printf("ID: %d | Type: %s\n", objectList[i].id, typeStr);
                }
            }
            printf("-------------------------------\n");
        }
    }
    return 0;
}