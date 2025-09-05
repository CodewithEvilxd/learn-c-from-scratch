# 🎯 Practical 17: Tic-Tac-Toe Game

## 📋 Problem Statement

Write a program that plays tic-tac-toe between user and computer.

## 🎯 Learning Objectives

- Understand 2D arrays for game board
- Practice game logic implementation
- Learn win condition checking
- Understand turn-based games
- Practice random number generation

## 📝 Requirements

1. 3x3 game board
2. Display board after each move
3. User inputs row and column
4. Computer makes random moves
5. Check for win conditions
6. Handle draw games
7. Input validation

## 💡 Hints

- Use 2D char array for board
- Check rows, columns, diagonals for wins
- Use rand() for computer moves
- Validate user input
- Clear display each turn

## 🔧 Solution

```c
// Practical 17: Tic-Tac-Toe Game
// User vs Computer tic-tac-toe

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

// Function to display the board
void displayBoard(char board[SIZE][SIZE]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Function to check for winner
int checkWinner(char board[SIZE][SIZE]) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return (board[i][0] == 'X') ? 1 : 2;
        }
    }

    // Check columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return (board[0][j] == 'X') ? 1 : 2;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return (board[0][0] == 'X') ? 1 : 2;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return (board[0][2] == 'X') ? 1 : 2;
    }

    return 0; // No winner
}

// Function to check if board is full
int isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

// Function for computer move
void computerMove(char board[SIZE][SIZE]) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (board[row][col] != ' ');

    board[row][col] = 'O';
    printf("Computer plays: Row %d, Column %d\n", row + 1, col + 1);
}

int main() {
    char board[SIZE][SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int row, col, winner, turn = 1;

    srand(time(NULL));

    printf("Tic-Tac-Toe Game\n");
    printf("================\n");
    printf("You are X, Computer is O\n");
    printf("Enter row and column (1-3)\n");

    displayBoard(board);

    while (1) {
        if (turn == 1) {
            // Player's turn
            printf("Your turn (X): ");
            scanf("%d %d", &row, &col);
            row--; col--; // Convert to 0-based

            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') {
                printf("Invalid move! Try again.\n");
                continue;
            }

            board[row][col] = 'X';
        } else {
            // Computer's turn
            computerMove(board);
        }

        displayBoard(board);

        winner = checkWinner(board);
        if (winner == 1) {
            printf("You win!\n");
            break;
        } else if (winner == 2) {
            printf("Computer wins!\n");
            break;
        } else if (isBoardFull(board)) {
            printf("It's a draw!\n");
            break;
        }

        turn = 3 - turn; // Switch turns
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Player Wins
```
Input: 1 1, 2 2, 3 3
Expected Output:
Player gets three in a row and wins
```

### Test Case 2: Computer Wins
```
Computer makes winning moves
Expected Output:
Computer wins the game
```

### Test Case 3: Draw
```
Input: Alternating moves leading to draw
Expected Output:
It's a draw!
```

## 🔍 Explanation

1. **Board Representation**: 3x3 char array
2. **Display Function**: Shows current board state
3. **Win Check**: Checks rows, columns, diagonals
4. **Computer Move**: Random valid move
5. **Game Loop**: Alternates turns until win or draw

## 🎯 Key Concepts Covered

- 2D arrays
- Game logic
- Win condition algorithms
- Random number generation
- Input validation

## 🚀 Extensions

1. Add smarter AI
2. Allow player vs player
3. Add score tracking
4. Improve board display