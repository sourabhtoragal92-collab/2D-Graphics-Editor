/* * Mini-project: 2D Graphics Editor
 * Student Name: Sourabh Toragal
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

extern GraphicObject objectList[MAX_OBJECTS];
extern int objectCount;
static int nextId = 1;

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

int main() {
    initializeCanvas();
    int choice = 0;

    while (choice != 5) {
        displayCanvas();
        printf("\n=== 2D GRAPHICS EDITOR ===\n");
        printf("1. Add Object\n2. Delete Object\n3. Modify Object\n4. List Objects\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int typeChoice;
            printf("Select Shape (1: Line, 2: Rect, 3: Circle, 4: Triangle): ");
            scanf("%d", &typeChoice);
            GraphicObject obj;
            obj.id = nextId++;
            obj.active = 1;

            if (typeChoice == 1) {
                obj.type = LINE;
                printf("Enter r1 c1 r2 c2: ");
                scanf("%d %d %d %d", &obj.p1, &obj.p2, &obj.p3, &obj.p4);
            } else if (typeChoice == 2) {
                obj.type = RECTANGLE;
                printf("Enter top left height width: ");
                scanf("%d %d %d %d", &obj.p1, &obj.p2, &obj.p3, &obj.p4);
            } else if (typeChoice == 3) {
                obj.type = CIRCLE;
                printf("Enter centerR centerC radius: ");
                scanf("%d %d %d", &obj.p1, &obj.p2, &obj.p3);
            } else if (typeChoice == 4) {
                obj.type = TRIANGLE;
                printf("Enter r1 c1 r2 c2 r3 c3: ");
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
            if (!found) printf("Object not found.\n");
            redrawCanvas();
        } else if (choice == 3) {
            int modId, found = 0;
            printf("Enter Object ID to modify: ");
            scanf("%d", &modId);
            for (int i = 0; i < objectCount; i++) {
                if (objectList[i].id == modId && objectList[i].active) {
                    found = 1;
                    if (objectList[i].type == LINE) {
                        printf("Enter new parameters (r1 c1 r2 c2): ");
                        scanf("%d %d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3, &objectList[i].p4);
                    } else if (objectList[i].type == RECTANGLE) {
                        printf("Enter new parameters (topRow leftCol height width): ");
                        scanf("%d %d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3, &objectList[i].p4);
                    } else if (objectList[i].type == CIRCLE) {
                        printf("Enter new parameters (centerR centerC radius): ");
                        scanf("%d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3);
                    } else if (objectList[i].type == TRIANGLE) {
                        printf("Enter new parameters (r1 c1 r2 c2 r3 c3): ");
                        scanf("%d %d %d %d %d %d", &objectList[i].p1, &objectList[i].p2, &objectList[i].p3, &objectList[i].p4, &objectList[i].p5, &objectList[i].p6);
                    }
                    break;
                }
            }
            if (!found) printf("Active object not found.\n");
            redrawCanvas();
        } else if (choice == 4) {
            printf("\n--- Active Artifacts ---\n");
            for (int i = 0; i < objectCount; i++) {
                if (objectList[i].active) {
                    char* typeStr = (objectList[i].type == LINE) ? "Line" : 
                                    (objectList[i].type == RECTANGLE) ? "Rectangle" : 
                                    (objectList[i].type == CIRCLE) ? "Circle" : "Triangle";
                    printf("ID: %d | Type: %s\n", objectList[i].id, typeStr);
                }
            }
        }
    }
    return 0;
}