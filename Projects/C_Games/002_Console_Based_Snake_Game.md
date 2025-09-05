# 🐍 **Project 2: Advanced Snake Game in C**
## 🎯 **Console-Based Game with AI Pathfinding & Multiplayer**

---

## 📋 **Project Overview**

**English:** A console-based Snake game featuring basic AI opponents, multiplayer mode, custom levels, scoring system, and save/load functionality.

**Hinglish:** Ek console-based Snake game jisme basic AI opponents, multiplayer mode, custom levels, scoring system, aur save/load functionality included hai.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Game loop implementation
- Keyboard input handling
- Collision detection algorithms
- File I/O for game saves
- Multi-threading concepts

✅ **Problem Solving:**
- Real-time game mechanics
- AI pathfinding algorithms
- Memory management in games
- User interface design

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Core game logic | Handles game mechanics and rendering |
| **Windows API** | Console manipulation | Controls cursor position and colors |
| **Multi-threading** | Concurrent operations | Separate threads for input and game logic |
| **File I/O** | Save/load system | Binary file operations for game states |
| **Time Library** | Game timing | Controls game speed and frame rate |

---

## 🎮 **Game Features**

### **Core Gameplay**
- ✅ Classic Snake movement mechanics
- ✅ Food spawning and consumption
- ✅ Score tracking and high scores
- ✅ Progressive difficulty increase
- ✅ Collision detection (walls, self, obstacles)

### **Advanced Features**
- ✅ **AI Opponent:** Basic computer-controlled snake
- ✅ **Multiplayer Mode:** Two-player simultaneous gameplay
- ✅ **Custom Levels:** User-designed mazes and obstacles
- ✅ **Power-ups:** Speed boost, score multipliers, shield
- ✅ **Save/Load System:** Resume games from saved states

---

## 🔧 **Core Implementation**

### **Game Structure**

```c
// game.h
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 100

typedef enum {
    UP, DOWN, LEFT, RIGHT
} Direction;

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    Direction direction;
    int score;
    int alive;
} Snake;

typedef struct {
    Position position;
    int value;
    int active;
} Food;

typedef struct {
    Snake player1;
    Snake player2;  // For multiplayer
    Snake ai;       // For AI mode
    Food food;
    int obstacles[HEIGHT][WIDTH];
    int game_mode;  // 0: single, 1: multiplayer, 2: AI
    int level;
    int speed;
} GameState;

#endif
```

### **Main Game Loop**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "game.h"

void game_loop(GameState *game) {
    while (game->player1.alive || (game->game_mode == 1 && game->player2.alive)) {
        // Handle input
        if (_kbhit()) {
            handle_input(game);
        }

        // Update game state
        update_snake(&game->player1);
        if (game->game_mode == 1) {
            update_snake(&game->player2);
        }
        if (game->game_mode == 2) {
            update_ai_snake(&game->ai, game);
        }

        // Check collisions
        check_collisions(game);

        // Update food
        update_food(game);

        // Render game
        render_game(game);

        // Control game speed
        Sleep(game->speed);
    }
}

int main() {
    GameState game;

    // Initialize game
    initialize_game(&game);

    // Main menu
    int choice = display_menu();

    switch (choice) {
        case 1:
            game.game_mode = 0;  // Single player
            break;
        case 2:
            game.game_mode = 1;  // Multiplayer
            break;
        case 3:
            game.game_mode = 2;  // AI mode
            break;
        case 4:
            load_game(&game);
            break;
    }

    // Start game loop
    game_loop(&game);

    // Game over
    display_game_over(&game);

    // Save high score
    save_high_score(game.player1.score);

    return 0;
}
```

### **AI Implementation**

```c
// ai.c
void update_ai_snake(Snake *ai, GameState *game) {
    // Basic AI: move towards food when possible
    Position target = game->food.position;

    // Calculate direction to food
    int dx = target.x - ai->body[0].x;
    int dy = target.y - ai->body[0].y;

    // Simple movement logic
    if (abs(dx) > abs(dy)) {
        // Try horizontal movement first
        if (dx > 0 && can_move(ai, RIGHT, game)) {
            ai->direction = RIGHT;
        } else if (dx < 0 && can_move(ai, LEFT, game)) {
            ai->direction = LEFT;
        } else {
            // Try vertical if horizontal not possible
            try_vertical_movement(ai, dy, game);
        }
    } else {
        // Try vertical movement first
        if (dy > 0 && can_move(ai, DOWN, game)) {
            ai->direction = DOWN;
        } else if (dy < 0 && can_move(ai, UP, game)) {
            ai->direction = UP;
        } else {
            // Try horizontal if vertical not possible
            try_horizontal_movement(ai, dx, game);
        }
    }

    // Move snake
    move_snake(ai);
}

int can_move(Snake *snake, Direction dir, GameState *game) {
    Position next_pos = get_next_position(snake, dir);

    // Check boundaries
    if (next_pos.x < 0 || next_pos.x >= WIDTH ||
        next_pos.y < 0 || next_pos.y >= HEIGHT) {
        return 0;
    }

    // Check obstacles
    if (game->obstacles[next_pos.y][next_pos.x]) {
        return 0;
    }

    // Check self collision
    for (int i = 0; i < snake->length; i++) {
        if (next_pos.x == snake->body[i].x &&
            next_pos.y == snake->body[i].y) {
            return 0;
        }
    }

    return 1;
}
```

### **Multiplayer Implementation**

```c
// multiplayer.c
void handle_multiplayer_input(GameState *game) {
    // Player 1 controls (WASD)
    if (GetAsyncKeyState('W') & 0x8000 && game->player1.direction != DOWN) {
        game->player1.direction = UP;
    }
    if (GetAsyncKeyState('S') & 0x8000 && game->player1.direction != UP) {
        game->player1.direction = DOWN;
    }
    if (GetAsyncKeyState('A') & 0x8000 && game->player1.direction != RIGHT) {
        game->player1.direction = LEFT;
    }
    if (GetAsyncKeyState('D') & 0x8000 && game->player1.direction != LEFT) {
        game->player1.direction = RIGHT;
    }

    // Player 2 controls (Arrow keys)
    if (GetAsyncKeyState(VK_UP) & 0x8000 && game->player2.direction != DOWN) {
        game->player2.direction = UP;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000 && game->player2.direction != UP) {
        game->player2.direction = DOWN;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && game->player2.direction != RIGHT) {
        game->player2.direction = LEFT;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && game->player2.direction != LEFT) {
        game->player2.direction = RIGHT;
    }
}
```

---

## 🎯 **Game Flow & Architecture**

### **System Architecture**

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Main Menu     │───▶│  Game Loop      │───▶│   Input         │
│   Selection     │    │  Processing     │    │   Handling      │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Game State    │    │   Rendering      │    │   Collision     │
│   Management    │    │   System         │    │   Detection     │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### **Game States**

1. **Menu State:** Game mode selection
2. **Playing State:** Active gameplay
3. **Paused State:** Game paused
4. **Game Over State:** Display results

---

## 🎮 **Advanced Features**

### **1. Custom Level Editor**

```c
void create_custom_level(GameState *game) {
    printf("Custom Level Editor\n");
    printf("Use WASD to move cursor, SPACE to toggle wall\n");

    int cursor_x = 0, cursor_y = 0;

    while (1) {
        // Display level editor
        display_level_editor(game, cursor_x, cursor_y);

        // Handle input
        if (_kbhit()) {
            char key = _getch();

            switch (key) {
                case 'w': if (cursor_y > 0) cursor_y--; break;
                case 's': if (cursor_y < HEIGHT-1) cursor_y++; break;
                case 'a': if (cursor_x > 0) cursor_x--; break;
                case 'd': if (cursor_x < WIDTH-1) cursor_x++; break;
                case ' ': game->obstacles[cursor_y][cursor_x] ^= 1; break;
                case 27: return; // ESC to exit
            }
        }
    }
}
```

### **2. Save/Load System**

```c
void save_game(GameState *game, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error saving game!\n");
        return;
    }

    fwrite(game, sizeof(GameState), 1, file);
    fclose(file);
    printf("Game saved successfully!\n");
}

void load_game(GameState *game, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error loading game!\n");
        return;
    }

    fread(game, sizeof(GameState), 1, file);
    fclose(file);
    printf("Game loaded successfully!\n");
}
```

### **3. Power-up System**

```c
typedef enum {
    SPEED_BOOST,
    SCORE_MULTIPLIER,
    SHIELD,
    GROWTH_INHIBITOR
} PowerUpType;

typedef struct {
    Position position;
    PowerUpType type;
    int active;
    int duration;
} PowerUp;

void spawn_power_up(GameState *game) {
    if (rand() % 100 < 10) { // 10% chance
        PowerUp *powerup = &game->powerups[game->powerup_count++];
        powerup->position.x = rand() % WIDTH;
        powerup->position.y = rand() % HEIGHT;
        powerup->type = rand() % 4;
        powerup->active = 1;
        powerup->duration = 100; // 10 seconds at 10 FPS
    }
}
```

---

## 📊 **Performance & Scoring**

### **Scoring System**

```c
void update_score(Snake *snake, int points) {
    snake->score += points;

    // Level progression
    if (snake->score > snake->level * 100) {
        snake->level++;
        // Increase speed or add obstacles
    }
}

void calculate_final_score(GameState *game) {
    int final_score = game->player1.score;

    // Bonus for length
    final_score += game->player1.length * 10;

    // Bonus for level
    final_score += game->level * 50;

    // Time bonus
    final_score += game->time_remaining / 10;

    return final_score;
}
```

### **High Score Management**

```c
typedef struct {
    char name[20];
    int score;
    int level;
    char date[20];
} HighScore;

void save_high_score(int score, int level) {
    HighScore hs;
    printf("Enter your name: ");
    scanf("%s", hs.name);
    hs.score = score;
    hs.level = level;
    // Get current date
    strcpy(hs.date, __DATE__);

    // Save to file
    FILE *file = fopen("highscores.dat", "ab");
    if (file) {
        fwrite(&hs, sizeof(HighScore), 1, file);
        fclose(file);
    }
}
```

---

## 🎯 **Presentation Outline**

### **Slide 1: Game Introduction**
- **English:** "Advanced Snake Game in C - Multiplayer & AI Features"
- **Hinglish:** "C mein Advanced Snake Game - Multiplayer aur AI Features"

### **Slide 2: Game Features**
- ✅ Classic Snake gameplay
- ✅ Basic AI opponent
- ✅ Multiplayer mode
- ✅ Custom level creation
- ✅ Basic power-up system
- ✅ Save/load functionality

### **Slide 3: Technologies Used**
- **C Programming Language** - Core game logic and rendering
- **Windows Console API** - Screen manipulation and colors
- **File I/O** - Save/load game states and high scores
- **Multi-threading** - Concurrent input processing
- **Time Library** - Game timing and frame rate control

### **Slide 4: How the Game Works**
```
Main Menu → Game Mode Selection → Game Initialization
     ↓              ↓                        ↓
Input Processing → Game Logic Update → Collision Detection
     ↓              ↓                        ↓
Rendering → Score Update → Difficulty Adjustment
```

### **Slide 5: AI Implementation**
```c
// Basic AI movement
Position target = food.position;
int dx = target.x - snake.x;
int dy = target.y - snake.y;

// Simple direction choice
if (abs(dx) > abs(dy)) {
    try_horizontal_first(dx, dy);
} else {
    try_vertical_first(dx, dy);
}
```

### **Slide 6: Multiplayer Features**
- **Player 1:** WASD keys for movement
- **Player 2:** Arrow keys for movement
- **Collision Detection:** Both snakes can die
- **Score Tracking:** Individual and combined scores
- **Power-ups:** Shared or competitive

### **Slide 7: Technical Challenges**
- **Real-time Input:** Handling keyboard input without blocking
- **Screen Rendering:** Efficient console output updates
- **AI Pathfinding:** Intelligent movement algorithms
- **Memory Management:** Game state persistence
- **Cross-platform Compatibility:** Windows-specific features

### **Slide 8: Code Architecture**
```c
typedef struct {
    Snake player1, player2, ai;
    Food food;
    PowerUp powerups[10];
    int obstacles[HEIGHT][WIDTH];
    int game_mode, level, speed;
} GameState;
```

### **Slide 9: Future Enhancements**
- **Graphical Interface:** SDL-based graphics
- **Network Multiplayer:** Online competitive play
- **3D Snake:** Three-dimensional gameplay
- **Customizable Skins:** Different snake appearances
- **Sound Effects:** Audio feedback system

### **Slide 10: Conclusion**
- **English:** "This Snake game demonstrates advanced C programming concepts including game development, AI implementation, and multi-threading."
- **Hinglish:** "Ye Snake game advanced C programming concepts ko demonstrate karta hai jisme game development, AI implementation, aur multi-threading included hai."

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Game loop implementation
- ✅ Real-time input handling
- ✅ Collision detection algorithms
- ✅ AI pathfinding implementation
- ✅ File I/O for game persistence

### **Game Development Concepts:**
- ✅ State management
- ✅ Scoring systems
- ✅ Level progression
- ✅ User interface design
- ✅ Performance optimization

---

## 📞 **Contact & Support**

**Project Developer:** C Game Development Student
**Email:** snakegame@cprojects.com
**GitHub:** https://github.com/c-games/snake-ai

---

**🎮 This comprehensive Snake game serves as an excellent portfolio project demonstrating advanced C programming skills and game development concepts suitable for assignments, hackathons, and technical presentations.**