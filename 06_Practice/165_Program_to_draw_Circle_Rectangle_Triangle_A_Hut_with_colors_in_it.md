# 🎯 Practical 165: Draw Shapes with Colors

## 📋 Problem Statement

Program to draw Circle/Rectangle/Triangle/A Hut with colors in it.

## 📋 Problem Statement

Program to draw Circle/Rectangle/Triangle/A Hut with colors in it.

## 🎯 Learning Objectives

- Understand console graphics
- Practice color manipulation
- Learn shape drawing algorithms
- Understand coordinate systems
- Practice ASCII art with colors

## 📝 Requirements

1. Implement shape drawing functions
2. Add color support
3. Draw multiple shapes
4. Handle console output
5. Display colored graphics

## 💡 Hints

- Use Windows console colors
- Implement shape algorithms
- Handle coordinate mapping
- Use gotoxy for positioning
- Combine shapes for complex drawings

## 🔧 Solution

```c
// Practical 165: Draw Shapes with Colors
// Demonstrates console graphics with colored shapes

#include <stdio.h>
#include <windows.h>
#include <math.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Default white
}

void drawRectangle(int x, int y, int width, int height, int color) {
    setColor(color);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gotoxy(x + j, y + i);
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("█");
            } else {
                printf(" ");
            }
        }
    }
    resetColor();
}

void drawTriangle(int x, int y, int height, int color) {
    setColor(color);
    for (int i = 0; i < height; i++) {
        gotoxy(x - i, y + i);
        for (int j = 0; j < (2 * i + 1); j++) {
            printf("▲");
        }
    }
    resetColor();
}

void drawCircle(int centerX, int centerY, int radius, int color) {
    setColor(color);
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                gotoxy(centerX + x, centerY + y);
                printf("●");
            }
        }
    }
    resetColor();
}

void drawHut(int x, int y) {
    // Roof (triangle)
    setColor(12); // Red
    for (int i = 0; i < 5; i++) {
        gotoxy(x - i, y + i);
        for (int j = 0; j < (2 * i + 1); j++) {
            printf("/");
        }
    }
    
    // House body (rectangle)
    setColor(6); // Yellow
    for (int i = 0; i < 4; i++) {
        gotoxy(x - 4, y + 5 + i);
        for (int j = 0; j < 9; j++) {
            if (i == 0 || i == 3 || j == 0 || j == 8) {
                printf("█");
            } else {
                printf(" ");
            }
        }
    }
    
    // Door
    setColor(1); // Blue
    for (int i = 0; i < 2; i++) {
        gotoxy(x - 1, y + 6 + i);
        for (int j = 0; j < 3; j++) {
            printf("█");
        }
    }
    
    resetColor();
}

int main() {
    system("cls");
    
    printf("Drawing Shapes with Colors\n");
    printf("==========================\n");
    
    // Draw individual shapes
    printf("Drawing Rectangle...");
    drawRectangle(5, 5, 15, 8, 10); // Green rectangle
    
    printf("\rDrawing Triangle...");
    drawTriangle(25, 5, 6, 13); // Purple triangle
    
    printf("\rDrawing Circle...");
    drawCircle(45, 8, 5, 14); // Yellow circle
    
    printf("\rDrawing Hut...");
    drawHut(60, 5);
    
    // Reset cursor position
    gotoxy(0, 20);
    printf("\nShapes drawn successfully!\n");
    printf("Colors: Green Rectangle, Purple Triangle, Yellow Circle, Colored Hut\n");
    
    getchar();
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Shape Drawing
```
Expected Output: Colored shapes displayed on console
- Green rectangle at (5,5)
- Purple triangle at (25,5) 
- Yellow circle at (45,8)
- Colored hut at (60,5)
```

## 🔍 Explanation

1. **Color Setup**: Use Windows console colors
2. **Shape Algorithms**: Implement drawing functions
3. **Coordinate System**: Use gotoxy for positioning
4. **Color Application**: Apply different colors to shapes
5. **Complex Drawing**: Combine shapes for hut

## 🎯 Key Concepts Covered

- Console graphics
- Color manipulation
- Shape drawing algorithms
- Coordinate positioning
- Windows console functions

## 🚀 Extensions

1. Add more shapes
2. Implement animation
3. Add user interaction
4. Create shape editor