# 🎯 Practical 15: Pyramid Patterns in C

## 📋 Problem Statement

Write a C program that displays various pyramid patterns.

## 🎯 Learning Objectives

- Understand different pyramid implementations
- Practice pattern variations
- Learn number and alphabet pyramids
- Understand pattern scaling

## 📝 Requirements

1. Display menu of pyramid patterns
2. Allow user to choose pattern type
3. Accept number of rows
4. Handle input validation
5. Use proper formatting

## 💡 Hints

- Use switch-case for pattern selection
- Implement functions for each pyramid type
- Handle numbers and alphabets
- Use proper spacing
- Clear menu display

## 🔧 Solution

```c
// Practical 15: Pyramid Patterns in C
// This program displays various pyramid patterns

#include <stdio.h>

// Function to print Star Pyramid
void starPyramid(int rows) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }
        printf("\n");
    }
}

// Function to print Number Pyramid
void numberPyramid(int rows) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= i; k++) {
            printf("%d ", k);
        }
        printf("\n");
    }
}

// Function to print Alphabet Pyramid
void alphabetPyramid(int rows) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= i; k++) {
            printf("%c ", 'A' + k - 1);
        }
        printf("\n");
    }
}

// Function to print Inverted Star Pyramid
void invertedStarPyramid(int rows) {
    for (int i = rows; i >= 1; i--) {
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
        printf("\nPyramid Patterns:\n");
        printf("================\n");
        printf("1. Star Pyramid\n");
        printf("2. Number Pyramid\n");
        printf("3. Alphabet Pyramid\n");
        printf("4. Inverted Star Pyramid\n");
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
                printf("Star Pyramid:\n");
                starPyramid(rows);
                break;
            case 2:
                printf("Number Pyramid:\n");
                numberPyramid(rows);
                break;
            case 3:
                printf("Alphabet Pyramid:\n");
                alphabetPyramid(rows);
                break;
            case 4:
                printf("Inverted Star Pyramid:\n");
                invertedStarPyramid(rows);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Star Pyramid
```
Choice: 1
Rows: 5
Expected Output:
Star Pyramid:
    *
   ***
  *****
 *******
*********
```

### Test Case 2: Number Pyramid
```
Choice: 2
Rows: 5
Expected Output:
Number Pyramid:
    1
   1 2
  1 2 3
 1 2 3 4
1 2 3 4 5
```

### Test Case 3: Alphabet Pyramid
```
Choice: 3
Rows: 5
Expected Output:
Alphabet Pyramid:
    A
   A B
  A B C
 A B C D
A B C D E
```

## 🔍 Explanation

1. **Menu System**: Uses while loop and switch-case
2. **Pattern Functions**: Separate functions for each type
3. **Variations**: Star, number, and alphabet pyramids
4. **Centering**: Proper space calculation
5. **Inverted Pattern**: Shows reverse pyramid

## 🎯 Key Concepts Covered

- Multiple pyramid types
- Character and number patterns
- Pattern variations
- Menu-driven interface
- Function organization

## 🚀 Extensions

1. Add hollow pyramids
2. Include more pattern types
3. Allow custom symbols
4. Add pattern saving feature