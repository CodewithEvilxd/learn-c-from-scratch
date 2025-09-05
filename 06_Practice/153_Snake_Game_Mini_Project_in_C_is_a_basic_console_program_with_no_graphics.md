# 🎯 Practical 153: Snake Game Mini Project in C

## 📋 Problem Statement

Snake Game Mini Project in C is a basic console program with no graphics. You may play the famous "Snake Game" in this project exactly as you would anywhere else. To move the snake, use the up, down, right, and left arrows. Food is placed at various co-ordinates on the screen for the snake to consume. The snake's length and score will both rise by one element each time it consumes the food.

## 🎯 Learning Objectives

- Understand game development basics
- Practice console-based graphics
- Learn keyboard input handling
- Understand game loop implementation
- Practice coordinate system management

## 📝 Requirements

1. Create console-based snake game
2. Handle arrow key inputs
3. Generate food at random positions
4. Increase snake length and score on food consumption
5. Handle collision detection
6. Display game over conditions

## 💡 Hints

- Use conio.h for keyboard input
- Implement game loop with timing
- Use 2D array for game board
- Track snake body as linked list or array
- Handle boundary collisions

## 🔧 Solution

```c
// Practical 153: Snake Game Mini Project in C
// Console-based Snake Game with arrow key controls

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 100

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    char direction;
} Snake;

typedef struct {
    Position pos;
    int active;
} Food;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBorder() {
    for (int i = 0; i <= WIDTH + 1; i++) {
        gotoxy(i, 0);
        printf("█");
        gotoxy(i, HEIGHT + 1);
        printf("█");
    }
    for (int i = 0; i <= HEIGHT + 1; i++) {
        gotoxy(0, i);
        printf("█");
        gotoxy(WIDTH + 1, i);
        printf("█");
    }
}

void drawSnake(Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        gotoxy(snake->body[i].x, snake->body[i].y);
        if (i == 0) {
            printf("●"); // Snake head
        } else {
            printf("○"); // Snake body
        }
    }
}

void drawFood(Food *food) {
    if (food->active) {
        gotoxy(food->pos.x, food->pos.y);
        printf("★");
    }
}

void generateFood(Food *food, Snake *snake) {
    int valid = 0;
    while (!valid) {
        food->pos.x = rand() % WIDTH + 1;
        food->pos.y = rand() % HEIGHT + 1;
        valid = 1;
        
        // Check if food spawns on snake
        for (int i = 0; i < snake->length; i++) {
            if (food->pos.x == snake->body[i].x && food->pos.y == snake->body[i].y) {
                valid = 0;
                break;
            }
        }
    }
    food->active = 1;
}

void moveSnake(Snake *snake) {
    // Move body
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    
    // Move head based on direction
    switch (snake->direction) {
        case 'U': snake->body[0].y--; break;
        case 'D': snake->body[0].y++; break;
        case 'L': snake->body[0].x--; break;
        case 'R': snake->body[0].x++; break;
    }
}

int checkCollision(Snake *snake) {
    Position head = snake->body[0];
    
    // Wall collision
    if (head.x <= 0 || head.x > WIDTH || head.y <= 0 || head.y > HEIGHT) {
        return 1;
    }
    
    // Self collision
    for (int i = 1; i < snake->length; i++) {
        if (head.x == snake->body[i].x && head.y == snake->body[i].y) {
            return 1;
        }
    }
    
    return 0;
}

int main() {
    Snake snake;
    Food food;
    int score = 0;
    char input;
    
    // Initialize snake
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
    snake.length = 1;
    snake.direction = 'R';
    
    // Initialize food
    srand(time(NULL));
    generateFood(&food, &snake);
    
    system("cls");
    drawBorder();
    
    while (1) {
        // Clear previous snake position
        for (int i = 0; i < snake.length; i++) {
            gotoxy(snake.body[i].x, snake.body[i].y);
            printf(" ");
        }
        
        // Handle input
        if (kbhit()) {
            input = getch();
            if (input == -32) { // Arrow key prefix
                input = getch();
                switch (input) {
                    case 72: if (snake.direction != 'D') snake.direction = 'U'; break; // Up
                    case 80: if (snake.direction != 'U') snake.direction = 'D'; break; // Down
                    case 75: if (snake.direction != 'R') snake.direction = 'L'; break; // Left
                    case 77: if (snake.direction != 'L') snake.direction = 'R'; break; // Right
                }
            }
        }
        
        moveSnake(&snake);
        
        // Check food collision
        if (snake.body[0].x == food.pos.x && snake.body[0].y == food.pos.y) {
            snake.length++;
            score += 10;
            generateFood(&food, &snake);
        }
        
        // Check collisions
        if (checkCollision(&snake)) {
            gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
            printf("GAME OVER!");
            gotoxy(WIDTH / 2 - 5, HEIGHT / 2 + 1);
            printf("Score: %d", score);
            gotoxy(0, HEIGHT + 2);
            getch();
            break;
        }
        
        // Draw everything
        drawSnake(&snake);
        drawFood(&food);
        
        // Display score
        gotoxy(0, HEIGHT + 2);
        printf("Score: %d  Length: %d", score, snake.length);
        
        Sleep(150); // Game speed
    }
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Basic Gameplay
```
Expected: Snake moves with arrow keys, eats food, grows, displays score
```

### Test Case 2: Collision Detection
```
Expected: Game ends when snake hits wall or itself
```

## 🔍 Explanation

1. **Game Setup**: Initialize snake, food, and game board
2. **Input Handling**: Process arrow key inputs
3. **Game Loop**: Move snake, check collisions, update display
4. **Food System**: Generate food, handle consumption
5. **Collision Detection**: Check wall and self collisions

## 🎯 Key Concepts Covered

- Console graphics
- Keyboard input handling
- Game loop implementation
- Coordinate system management
- Collision detection

## 🚀 Extensions

1. Add levels with increasing speed
2. Implement high score system
3. Add obstacles
4. Create multiple food types