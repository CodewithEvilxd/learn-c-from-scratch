# 🎯 Practical 1: Half Pyramid of *

## 📋 Problem Statement

Write a C Program to implement a half pyramid of * (stars).

## 🎯 Learning Objectives

- Understand nested loops
- Practice pattern printing
- Learn loop control and iteration
- Understand row and column relationships

## 📝 Requirements

1. Accept number of rows from user
2. Print half pyramid pattern using *
3. Use nested loops
4. Handle input validation
5. Display pattern with proper formatting

## 💡 Hints

- Use outer loop for rows
- Use inner loop for columns
- Print * for each column in current row
- Use printf("\n") for new line after each row

## 🔧 Solution

```c
// Practical 1: Half Pyramid of Stars
// This program prints a half pyramid pattern using stars

#include <stdio.h>

int main() {
    int rows;

    // Get number of rows from user
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    // Input validation
    if (rows <= 0) {
        printf("Please enter a positive number!\n");
        return 1;
    }

    printf("Half Pyramid of Stars:\n");
    printf("====================\n");

    // Outer loop for rows
    for (int i = 1; i <= rows; i++) {
        // Inner loop for columns
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Input
```
Input: 5
Expected Output:
Half Pyramid of Stars:
====================
*
* *
* * *
* * * *
* * * * *
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Half Pyramid of Stars:
====================
*
```

### Test Case 3: Larger Pattern
```
Input: 8
Expected Output:
Half Pyramid of Stars:
====================
*
* *
* * *
* * * *
* * * * *
* * * * * *
* * * * * * *
* * * * * * * *
```

## 🔍 Explanation

1. **Outer Loop**: Controls the number of rows (i from 1 to rows)
2. **Inner Loop**: Controls the number of stars in each row (j from 1 to i)
3. **Pattern Logic**: Each row i has i number of stars
4. **Spacing**: " " after each star for better visual appearance
5. **New Line**: printf("\n") moves to next row

## 🎯 Key Concepts Covered

- Nested loops
- Pattern printing
- Loop variables relationship
- User input handling
- Input validation

## 🚀 Extensions

1. Print pyramid without spaces between stars
2. Add border/frame around the pyramid
3. Print pyramid in reverse (upside down)
4. Allow user to choose the symbol to print