# 🎯 Practical 4: Inverted Half Pyramid of *

## 📋 Problem Statement

Write a C Program to implement an inverted half pyramid of * (stars).

## 🎯 Learning Objectives

- Understand reverse pattern printing
- Practice nested loops in reverse
- Learn decreasing loop patterns
- Understand pattern inversion logic

## 📝 Requirements

1. Accept number of rows from user
2. Print inverted half pyramid pattern
3. Use nested loops with reverse logic
4. Handle input validation
5. Display pattern with proper formatting

## 💡 Hints

- Use outer loop from rows down to 1
- Use inner loop from 1 to current row number
- Print * for each position
- Use proper spacing

## 🔧 Solution

```c
// Practical 4: Inverted Half Pyramid of Stars
// This program prints an inverted half pyramid pattern

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

    printf("Inverted Half Pyramid of Stars:\n");
    printf("===============================\n");

    // Outer loop for rows (decreasing)
    for (int i = rows; i >= 1; i--) {
        // Inner loop for stars in each row
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
Inverted Half Pyramid of Stars:
===============================
* * * * *
* * * *
* * *
* *
*
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Inverted Half Pyramid of Stars:
===============================
*
```

### Test Case 3: Larger Pattern
```
Input: 7
Expected Output:
Inverted Half Pyramid of Stars:
===============================
* * * * * * *
* * * * * *
* * * * *
* * * *
* * *
* *
*
```

## 🔍 Explanation

1. **Outer Loop**: Starts from rows and decreases to 1
2. **Inner Loop**: Prints i stars for row i
3. **Reverse Logic**: Pattern starts with maximum stars
4. **Decreasing Pattern**: Each row has one less star than previous
5. **Spacing**: " " between stars for visual appeal

## 🎯 Key Concepts Covered

- Reverse loop patterns
- Decreasing sequence generation
- Pattern inversion logic
- Nested loop control
- User input validation

## 🚀 Extensions

1. Add spaces before stars to center the pattern
2. Print numbers instead of stars
3. Create a full inverted pyramid
4. Add user choice for symbol