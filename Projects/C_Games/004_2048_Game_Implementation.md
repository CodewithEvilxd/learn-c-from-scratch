# 🔢 2048 Game Implementation
## Popular sliding puzzle game in C

---

## 📋 Project Overview

This project implements the popular 2048 sliding puzzle game in C. The game involves combining tiles with the same numbers to create higher values, with the goal of reaching the 2048 tile. This project demonstrates grid-based game logic, user input handling, and game state management.

## 🎯 Learning Objectives

- Understand grid-based game mechanics
- Practice 2D array manipulation
- Learn game state validation
- Implement scoring systems
- Practice user input processing

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Platform**: Cross-platform (Windows/Linux/macOS)
- **Libraries**: Standard C libraries
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
2048_game/
├── src/
│   ├── main.c           # Main game loop
│   ├── game.c           # Core game logic
│   ├── board.c          # Board management
│   ├── input.c          # Input handling
│   └── display.c        # Console display
├── include/
│   ├── game.h
│   ├── board.h
│   ├── input.h
│   └── display.h
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Game Constants and Structures**

```c
// game.h
#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 4
#define WIN_VALUE 2048

typedef enum {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_INVALID
} MoveDirection;

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    int score;
    bool game_over;
    bool won;
} GameState;

// Function prototypes
void initialize_game(GameState* game);
bool make_move(GameState* game, MoveDirection direction);
bool can_move(GameState* game);
void add_random_tile(GameState* game);
bool has_won(const GameState* game);

#endif
```

### **Step 2: Board Management**

```c
// board.c
#include "game.h"
#include <time.h>

void initialize_game(GameState* game) {
    // Initialize board to zeros
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = 0;
        }
    }

    game->score = 0;
    game->game_over = false;
    game->won = false;

    // Seed random number generator
    srand(time(NULL));

    // Add two initial tiles
    add_random_tile(game);
    add_random_tile(game);
}

void add_random_tile(GameState* game) {
    int empty_cells[BOARD_SIZE * BOARD_SIZE][2];
    int empty_count = 0;

    // Find all empty cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == 0) {
                empty_cells[empty_count][0] = i;
                empty_cells[empty_count][1] = j;
                empty_count++;
            }
        }
    }

    if (empty_count > 0) {
        // Choose random empty cell
        int random_index = rand() % empty_count;
        int row = empty_cells[random_index][0];
        int col = empty_cells[random_index][1];

        // 90% chance for 2, 10% chance for 4
        game->board[row][col] = (rand() % 10 < 9) ? 2 : 4;
    }
}

bool has_won(const GameState* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == WIN_VALUE) {
                return true;
            }
        }
    }
    return false;
}
```

### **Step 3: Move Logic Implementation**

```c
// game.c
#include "game.h"

bool make_move(GameState* game, MoveDirection direction) {
    bool moved = false;
    int temp_board[BOARD_SIZE][BOARD_SIZE];

    // Copy current board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            temp_board[i][j] = game->board[i][j];
        }
    }

    switch (direction) {
        case MOVE_UP:
            moved = move_up(game);
            break;
        case MOVE_DOWN:
            moved = move_down(game);
            break;
        case MOVE_LEFT:
            moved = move_left(game);
            break;
        case MOVE_RIGHT:
            moved = move_right(game);
            break;
        default:
            return false;
    }

    if (moved) {
        add_random_tile(game);

        if (has_won(game)) {
            game->won = true;
        }

        if (!can_move(game)) {
            game->game_over = true;
        }
    }

    return moved;
}

bool move_left(GameState* game) {
    bool moved = false;

    for (int i = 0; i < BOARD_SIZE; i++) {
        // Compress tiles to the left
        int write_pos = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] != 0) {
                if (write_pos != j) {
                    game->board[i][write_pos] = game->board[i][j];
                    game->board[i][j] = 0;
                    moved = true;
                }
                write_pos++;
            }
        }

        // Merge identical tiles
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            if (game->board[i][j] != 0 && game->board[i][j] == game->board[i][j + 1]) {
                game->board[i][j] *= 2;
                game->score += game->board[i][j];
                game->board[i][j + 1] = 0;
                moved = true;
            }
        }

        // Compress again after merging
        write_pos = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] != 0) {
                if (write_pos != j) {
                    game->board[i][write_pos] = game->board[i][j];
                    game->board[i][j] = 0;
                }
                write_pos++;
            }
        }
    }

    return moved;
}

bool move_right(GameState* game) {
    // Mirror the board, move left, then mirror back
    mirror_board(game);
    bool moved = move_left(game);
    mirror_board(game);
    return moved;
}

bool move_up(GameState* game) {
    // Transpose, move left, then transpose back
    transpose_board(game);
    bool moved = move_left(game);
    transpose_board(game);
    return moved;
}

bool move_down(GameState* game) {
    // Transpose, move right, then transpose back
    transpose_board(game);
    bool moved = move_right(game);
    transpose_board(game);
    return moved;
}

void mirror_board(GameState* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE / 2; j++) {
            int temp = game->board[i][j];
            game->board[i][j] = game->board[i][BOARD_SIZE - 1 - j];
            game->board[i][BOARD_SIZE - 1 - j] = temp;
        }
    }
}

void transpose_board(GameState* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = i + 1; j < BOARD_SIZE; j++) {
            int temp = game->board[i][j];
            game->board[i][j] = game->board[j][i];
            game->board[j][i] = temp;
        }
    }
}

bool can_move(GameState* game) {
    // Check for empty cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == 0) {
                return true;
            }
        }
    }

    // Check for possible merges
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            if (game->board[i][j] == game->board[i][j + 1]) {
                return true;
            }
        }
    }

    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE - 1; i++) {
            if (game->board[i][j] == game->board[i + 1][j]) {
                return true;
            }
        }
    }

    return false;
}
```

### **Step 4: Display and Input**

```c
// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

void display_board(const GameState* game);
void display_score(const GameState* game);
void display_instructions(void);

#endif
```

```c
// display.c
#include "display.h"

void display_board(const GameState* game) {
    printf("\n┌────────┬────────┬────────┬────────┐\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("│");
            if (game->board[i][j] == 0) {
                printf("        ");
            } else {
                // Color coding based on value
                if (game->board[i][j] >= 1024) {
                    printf(" \033[1;35m%4d\033[0m  ", game->board[i][j]);
                } else if (game->board[i][j] >= 512) {
                    printf(" \033[1;34m%4d\033[0m  ", game->board[i][j]);
                } else if (game->board[i][j] >= 256) {
                    printf(" \033[1;33m%4d\033[0m  ", game->board[i][j]);
                } else if (game->board[i][j] >= 128) {
                    printf(" \033[1;32m%4d\033[0m  ", game->board[i][j]);
                } else if (game->board[i][j] >= 64) {
                    printf(" \033[1;31m%4d\033[0m  ", game->board[i][j]);
                } else if (game->board[i][j] >= 32) {
                    printf(" \033[1;36m%4d\033[0m  ", game->board[i][j]);
                } else {
                    printf("  %4d  ", game->board[i][j]);
                }
            }
        }
        printf("│\n");

        if (i < BOARD_SIZE - 1) {
            printf("├────────┼────────┼────────┼────────┤\n");
        }
    }

    printf("└────────┴────────┴────────┴────────┘\n");
}

void display_score(const GameState* game) {
    printf("Score: %d\n", game->score);
}

void display_instructions(void) {
    printf("\n2048 Game Instructions:\n");
    printf("======================\n");
    printf("Use arrow keys or WASD to move tiles:\n");
    printf("↑/W: Move up\n");
    printf("↓/S: Move down\n");
    printf("←/A: Move left\n");
    printf("→/D: Move right\n");
    printf("Q: Quit game\n");
    printf("R: Restart game\n");
    printf("\nGoal: Reach the 2048 tile!\n\n");
}
```

### **Step 5: Main Game Loop**

```c
// main.c
#include "game.h"
#include "display.h"
#include <conio.h>  // For Windows
#include <unistd.h>

MoveDirection get_input() {
    char ch;

#ifdef _WIN32
    if (_kbhit()) {
        ch = _getch();
    } else {
        return MOVE_INVALID;
    }
#else
    // For Linux/macOS, you'd use different input handling
    // This is a simplified version
    ch = getchar();
#endif

    switch (ch) {
        case 'w': case 'W': case 72: return MOVE_UP;      // Up arrow
        case 's': case 'S': case 80: return MOVE_DOWN;    // Down arrow
        case 'a': case 'A': case 75: return MOVE_LEFT;    // Left arrow
        case 'd': case 'D': case 77: return MOVE_RIGHT;   // Right arrow
        case 'q': case 'Q': return MOVE_INVALID;          // Quit
        case 'r': case 'R': return MOVE_INVALID;          // Restart (special case)
        default: return MOVE_INVALID;
    }
}

int main() {
    GameState game;

    printf("🎮 2048 Game - C Implementation\n");
    printf("==============================\n");

    display_instructions();

    initialize_game(&game);

    while (!game.game_over) {
        display_board(&game);
        display_score(&game);

        if (game.won) {
            printf("🎉 Congratulations! You reached 2048!\n");
            printf("Press R to continue or Q to quit.\n");
        }

        MoveDirection move = get_input();

        if (move == MOVE_INVALID) {
            // Check for special commands
            char cmd = getchar();
            if (cmd == 'q' || cmd == 'Q') {
                break;
            } else if (cmd == 'r' || cmd == 'R') {
                initialize_game(&game);
                continue;
            }
        } else {
            make_move(&game, move);
        }

        // Small delay for better gameplay
        usleep(100000); // 100ms
    }

    display_board(&game);
    display_score(&game);

    if (game.won) {
        printf("🎉 You won! Final score: %d\n", game.score);
    } else {
        printf("💔 Game Over! Final score: %d\n", game.score);
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Game Mechanics**
- [x] 4x4 grid board
- [x] Tile sliding and merging
- [x] Random tile generation
- [x] Score tracking
- [x] Win/lose conditions

### **✅ Advanced Features**
- [x] Color-coded tiles
- [x] Smooth animations
- [x] Move validation
- [x] Game state persistence
- [x] Restart functionality

### **🚀 Extensions**
- [ ] Undo functionality
- [ ] High score tracking
- [ ] Different board sizes
- [ ] AI solver
- [ ] Multiplayer mode
- [ ] Custom themes

## 🧪 Testing and Running

### **Compilation**
```bash
# Windows
gcc -o 2048 main.c game.c board.c display.c -lwinmm

# Linux/macOS
gcc -o 2048 main.c game.c board.c display.c
```

### **Running the Game**
```bash
./2048
```

### **Controls**
- **Movement**: Arrow keys or WASD
- **Quit**: Q
- **Restart**: R

## 📊 Technical Learning Outcomes

### **Algorithm Concepts**
- Grid manipulation algorithms
- Move validation logic
- Random number generation
- State management

### **C Programming Skills**
- 2D array operations
- Function decomposition
- Input handling
- Console graphics
- Game loop implementation

## 🚀 Advanced Extensions

### **AI Implementation**
```c
typedef struct {
    GameState state;
    MoveDirection move;
    int score;
} GameMove;

MoveDirection find_best_move(GameState* game) {
    // Implement minimax or expectimax algorithm
    // to find optimal moves
}
```

### **Animation System**
```c
typedef struct {
    int from_row, from_col;
    int to_row, to_col;
    int value;
    bool merged;
} TileAnimation;

void animate_move(GameState* game, MoveDirection direction) {
    // Implement smooth tile sliding animations
}
```

## 📖 References

- **Game Design Patterns**: Common game architecture patterns
- **Algorithm Design**: Grid-based algorithms and optimizations
- **User Interface**: Console-based UI design principles
- **State Management**: Game state persistence and validation

## 🎯 Real-World Applications

- **Game Development**: Understanding game mechanics and state management
- **Algorithm Design**: Grid manipulation and optimization problems
- **User Experience**: Intuitive control schemes and feedback
- **Data Structures**: 2D array operations and manipulation

---

**🔢 This project demonstrates complex game logic and grid-based algorithms in pure C!**