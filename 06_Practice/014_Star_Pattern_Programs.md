# 🎯 Practical 14: Star Pattern Programs in C

## 📋 Problem Statement

Write a C program that displays various star pattern programs.

## 🎯 Learning Objectives

- Understand multiple pattern implementations
- Practice menu-driven programs
- Learn switch-case statements
- Understand different star pattern algorithms

## 📝 Requirements

1. Display menu of star patterns
2. Allow user to choose pattern
3. Accept number of rows for each pattern
4. Handle input validation
5. Use proper formatting

## 💡 Hints

- Use switch-case for pattern selection
- Implement separate functions for each pattern
- Use nested loops for patterns
- Handle user input properly
- Clear screen between patterns

## 🔧 Solution

```c
// Practical 14: Star Pattern Programs in C
// This program displays various star patterns

#include <stdio.h>

// Function to print Half Pyramid
void halfPyramid(int rows) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
}

// Function to print Full Pyramid
void fullPyramid(int rows) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= i; k++) {
            printf("* ");
        }
        printf("\n");
    }
}

// Function to print Inverted Half Pyramid
void invertedHalfPyramid(int rows) {
    for (int i = rows; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
}

// Function to print Diamond Pattern
void diamondPattern(int rows) {
    // Upper half
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }
        printf("\n");
    }
    // Lower half
    for (int i = rows - 1; i >= 1; i--) {
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }
        printf("\n");
    }
}

int main() {
    int choice, rows;

    while (1) {
        printf("\nStar Pattern Programs:\n");
        printf("=====================\n");
        printf("1. Half Pyramid\n");
        printf("2. Full Pyramid\n");
        printf("3. Inverted Half Pyramid\n");
        printf("4. Diamond Pattern\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting program...\n");
            break;
        }

        printf("Enter number of rows: ");
        scanf("%d", &rows);

        if (rows <= 0) {
            printf("Please enter a positive number!\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Half Pyramid:\n");
                halfPyramid(rows);
                break;
            case 2:
                printf("Full Pyramid:\n");
                fullPyramid(rows);
                break;
            case 3:
                printf("Inverted Half Pyramid:\n");
                invertedHalfPyramid(rows);
                break;
            case 4:
                printf("Diamond Pattern:\n");
                diamondPattern(rows);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Half Pyramid
```
Choice: 1
Rows: 5
Expected Output:
Half Pyramid:
*
* *
* * *
* * * *
* * * * *
```

### Test Case 2: Full Pyramid
```
Choice: 2
Rows: 5
Expected Output:
Full Pyramid:
    *
   * *
  * * *
 * * * *
* * * * *
```

### Test Case 3: Diamond Pattern
```
Choice: 4
Rows: 5
Expected Output:
Diamond Pattern:
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
```

## 🔍 Explanation

1. **Menu System**: Uses while loop and switch-case
2. **Pattern Functions**: Separate functions for each pattern
3. **User Input**: Validates choice and rows
4. **Exit Option**: Choice 5 to exit program
5. **Modular Design**: Each pattern in its own function

## 🎯 Key Concepts Covered

- Menu-driven programs
- Switch-case statements
- Function implementation
- Multiple pattern algorithms
- Input validation

## 🚀 Extensions

1. Add more star patterns
2. Allow user to choose symbol
3. Add pattern with numbers
4. Save patterns to file