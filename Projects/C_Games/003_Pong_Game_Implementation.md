# 🏓 Pong Game Implementation
## Classic arcade game built from scratch in C

---

## 📋 Project Overview

This project implements the classic Pong game using C programming with console graphics. The game features two paddles, a ball, scoring system, and smooth gameplay mechanics, demonstrating game development concepts in pure C.

## 🎯 Learning Objectives

- Understand game loop architecture
- Practice real-time input handling
- Learn collision detection algorithms
- Implement game state management
- Practice console graphics and animation

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Platform**: Windows (with conio.h) or Cross-platform (with ncurses)
- **Libraries**: Standard C libraries, conio.h or ncurses
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
pong_game/
├── src/
│   ├── main.c           # Main game loop and initialization
│   ├── game.c           # Core game logic
│   ├── graphics.c       # Console graphics and rendering
│   ├── input.c          # Input handling
│   └── utils.c          # Utility functions
├── include/
│   ├── game.h
│   ├── graphics.h
│   ├── input.h
│   └── utils.h
├── assets/
│   └── sounds/          # Optional sound effects
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Game Structure and Constants**

```c
// game.h
#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define PADDLE_HEIGHT 4
#define BALL_SPEED 1
#define PADDLE_SPEED 1

typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
    int score;
} Paddle;

typedef struct {
    Ball ball;
    Paddle left_paddle;
    Paddle right_paddle;
    int left_score;
    int right_score;
    bool game_running;
} GameState;

// Function prototypes
void initialize_game(GameState* game);
void update_game(GameState* game);
void render_game(const GameState* game);
void handle_input(GameState* game);
bool check_collision(const Ball* ball, const Paddle* paddle);

#endif
```

### **Step 2: Core Game Logic**

```c
// game.c
#include "game.h"
#include <time.h>

void initialize_game(GameState* game) {
    // Initialize ball at center
    game->ball.x = SCREEN_WIDTH / 2;
    game->ball.y = SCREEN_HEIGHT / 2;
    game->ball.dx = BALL_SPEED;
    game->ball.dy = BALL_SPEED;

    // Initialize left paddle
    game->left_paddle.x = 2;
    game->left_paddle.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    game->left_paddle.score = 0;

    // Initialize right paddle
    game->right_paddle.x = SCREEN_WIDTH - 3;
    game->right_paddle.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    game->right_paddle.score = 0;

    game->left_score = 0;
    game->right_score = 0;
    game->game_running = true;

    // Seed random number generator
    srand(time(NULL));
}

void update_game(GameState* game) {
    // Update ball position
    game->ball.x += game->ball.dx;
    game->ball.y += game->ball.dy;

    // Ball collision with top and bottom walls
    if (game->ball.y <= 1 || game->ball.y >= SCREEN_HEIGHT - 2) {
        game->ball.dy = -game->ball.dy;
    }

    // Ball collision with paddles
    if (check_collision(&game->ball, &game->left_paddle) ||
        check_collision(&game->ball, &game->right_paddle)) {
        game->ball.dx = -game->ball.dx;
    }

    // Ball goes out of bounds (scoring)
    if (game->ball.x < 0) {
        game->right_score++;
        // Reset ball
        game->ball.x = SCREEN_WIDTH / 2;
        game->ball.y = SCREEN_HEIGHT / 2;
        game->ball.dx = BALL_SPEED;
    } else if (game->ball.x > SCREEN_WIDTH) {
        game->left_score++;
        // Reset ball
        game->ball.x = SCREEN_WIDTH / 2;
        game->ball.y = SCREEN_HEIGHT / 2;
        game->ball.dx = -BALL_SPEED;
    }

    // Check for game end condition
    if (game->left_score >= 5 || game->right_score >= 5) {
        game->game_running = false;
    }
}

bool check_collision(const Ball* ball, const Paddle* paddle) {
    return (ball->x >= paddle->x && ball->x <= paddle->x + 1 &&
            ball->y >= paddle->y && ball->y <= paddle->y + PADDLE_HEIGHT);
}
```

### **Step 3: Console Graphics and Rendering**

```c
// graphics.h
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"

void clear_screen(void);
void draw_border(void);
void draw_paddle(const Paddle* paddle);
void draw_ball(const Ball* ball);
void draw_score(int left_score, int right_score);
void render_game(const GameState* game);

#endif
```

```c
// graphics.c
#include "graphics.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
void clear_screen() {
    system("cls");
}
#else
void clear_screen() {
    printf("\033[2J\033[H");
}
#endif

void draw_border() {
    // Draw top border
    printf("┌");
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) {
        printf("─");
    }
    printf("┐\n");

    // Draw side borders
    for (int i = 0; i < SCREEN_HEIGHT - 2; i++) {
        printf("│");
        for (int j = 0; j < SCREEN_WIDTH - 2; j++) {
            printf(" ");
        }
        printf("│\n");
    }

    // Draw bottom border
    printf("└");
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) {
        printf("─");
    }
    printf("┘\n");
}

void draw_paddle(const Paddle* paddle) {
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        printf("\033[%d;%dH│", paddle->y + i + 1, paddle->x + 1);
    }
}

void draw_ball(const Ball* ball) {
    printf("\033[%d;%dH●", ball->y + 1, ball->x + 1);
}

void draw_score(int left_score, int right_score) {
    printf("\033[1;%dHPlayer 1: %d", SCREEN_WIDTH / 4, left_score);
    printf("\033[1;%dHPlayer 2: %d", 3 * SCREEN_WIDTH / 4, right_score);
}

void render_game(const GameState* game) {
    clear_screen();
    draw_border();
    draw_paddle(&game->left_paddle);
    draw_paddle(&game->right_paddle);
    draw_ball(&game->ball);
    draw_score(game->left_score, game->right_score);
    fflush(stdout);
}
```

### **Step 4: Input Handling**

```c
// input.h
#ifndef INPUT_H
#define INPUT_H

#include "game.h"

void handle_input(GameState* game);

#endif
```

```c
// input.c
#include "input.h"

#ifdef _WIN32
#include <conio.h>
void handle_input(GameState* game) {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                if (game->left_paddle.y > 1) {
                    game->left_paddle.y -= PADDLE_SPEED;
                }
                break;
            case 's':
            case 'S':
                if (game->left_paddle.y < SCREEN_HEIGHT - PADDLE_HEIGHT - 1) {
                    game->left_paddle.y += PADDLE_SPEED;
                }
                break;
            case 'i':
            case 'I':
                if (game->right_paddle.y > 1) {
                    game->right_paddle.y -= PADDLE_SPEED;
                }
                break;
            case 'k':
            case 'K':
                if (game->right_paddle.y < SCREEN_HEIGHT - PADDLE_HEIGHT - 1) {
                    game->right_paddle.y += PADDLE_SPEED;
                }
                break;
            case 'q':
            case 'Q':
                game->game_running = false;
                break;
        }
    }
}
#else
// Linux/macOS implementation using ncurses would go here
void handle_input(GameState* game) {
    // Simplified implementation for cross-platform compatibility
    // In a real implementation, you'd use ncurses for better input handling
}
#endif
```

### **Step 5: Main Game Loop**

```c
// main.c
#include "game.h"
#include "graphics.h"
#include "input.h"
#include <unistd.h>

int main() {
    GameState game;

    printf("Pong Game - C Implementation\n");
    printf("===========================\n");
    printf("Controls:\n");
    printf("Player 1 (Left): W/S to move paddle\n");
    printf("Player 2 (Right): I/K to move paddle\n");
    printf("Q: Quit game\n");
    printf("First to 5 points wins!\n\n");
    printf("Press any key to start...");
    getchar();

    initialize_game(&game);

    while (game.game_running) {
        handle_input(&game);
        update_game(&game);
        render_game(&game);

        // Game speed control
        usleep(50000); // 50ms delay
    }

    clear_screen();
    printf("Game Over!\n");
    printf("Final Score: Player 1: %d - Player 2: %d\n",
           game.left_score, game.right_score);

    if (game.left_score > game.right_score) {
        printf("Player 1 wins!\n");
    } else if (game.right_score > game.left_score) {
        printf("Player 2 wins!\n");
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Game Mechanics**
- [x] Two-player paddle control
- [x] Ball physics and collision detection
- [x] Scoring system
- [x] Game state management
- [x] Real-time rendering

### **✅ Advanced Features**
- [x] Smooth paddle movement
- [x] Ball bouncing physics
- [x] Collision detection
- [x] Score tracking
- [x] Game over conditions

### **🚀 Extensions**
- [ ] AI opponent
- [ ] Sound effects
- [ ] Power-ups and special abilities
- [ ] Multi-ball mode
- [ ] Different difficulty levels
- [ ] Tournament mode

## 🧪 Testing and Running

### **Compilation**
```bash
# Windows
gcc -o pong main.c game.c graphics.c input.c -lwinmm

# Linux/macOS
gcc -o pong main.c game.c graphics.c input.c -lncurses
```

### **Running the Game**
```bash
./pong
```

### **Controls**
- **Player 1 (Left Paddle)**: W (up), S (down)
- **Player 2 (Right Paddle)**: I (up), K (down)
- **Quit**: Q

## 📊 Technical Learning Outcomes

### **Game Development Concepts**
- Game loop architecture
- Real-time input processing
- Collision detection algorithms
- State management
- Frame rate control

### **C Programming Skills**
- Struct usage for game objects
- Pointer manipulation
- Platform-specific code
- Console I/O and graphics
- Timing and delays

## 🚀 Advanced Extensions

### **AI Implementation**
```c
void update_ai_paddle(GameState* game) {
    // Simple AI: follow the ball
    if (game->ball.y < game->right_paddle.y + PADDLE_HEIGHT / 2) {
        game->right_paddle.y -= PADDLE_SPEED;
    } else if (game->ball.y > game->right_paddle.y + PADDLE_HEIGHT / 2) {
        game->right_paddle.y += PADDLE_SPEED;
    }
}
```

### **Power-ups System**
```c
typedef enum {
    POWER_NONE,
    POWER_SPEED_UP,
    POWER_PADDLE_GROW,
    POWER_MULTI_BALL
} PowerUpType;

typedef struct {
    int x, y;
    PowerUpType type;
    bool active;
} PowerUp;
```

## 📖 References

- **Game Development Patterns**: Common game architecture patterns
- **Console Graphics**: ASCII art and terminal manipulation
- **Real-time Programming**: Timing and synchronization
- **Input Handling**: Cross-platform input management

## 🎯 Real-World Applications

- **Game Development**: Understanding core game mechanics
- **Real-time Systems**: Timing and synchronization
- **User Interface**: Console-based UI design
- **Algorithm Implementation**: Collision detection and physics

---

**🏓 This project demonstrates classic game development in pure C, showcasing real-time programming and interactive graphics!**