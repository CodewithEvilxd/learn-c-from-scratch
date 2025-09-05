# 🎯 Practical 12: Floyd’s Triangle

## 📋 Problem Statement

Write a C Program to print Floyd’s triangle.

## 🎯 Learning Objectives

- Understand consecutive number patterns
- Practice nested loops with counters
- Learn sequential number generation
- Understand triangular number sequences

## 📝 Requirements

1. Accept number of rows from user
2. Print Floyd’s triangle with consecutive numbers
3. Use proper formatting
4. Handle input validation
5. Start from 1 in top-left corner

## 💡 Hints

- Use a counter variable starting from 1
- Outer loop for rows
- Inner loop for numbers in each row
- Increment counter for each number printed
- Print numbers with space separation

## 🔧 Solution

```c
// Practical 12: Floyd’s Triangle
// This program prints Floyd’s triangle using consecutive numbers

#include <stdio.h>

int main() {
    int rows, num = 1;

    // Get number of rows from user
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    // Input validation
    if (rows <= 0) {
        printf("Please enter a positive number!\n");
        return 1;
    }

    printf("Floyd’s Triangle:\n");
    printf("================\n");

    // Outer loop for rows
    for (int i = 1; i <= rows; i++) {
        // Inner loop for numbers in each row
        for (int j = 1; j <= i; j++) {
            printf("%d ", num);
            num++;
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
Floyd’s Triangle:
================
1
2 3
4 5 6
7 8 9 10
11 12 13 14 15
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Floyd’s Triangle:
================
1
```

### Test Case 3: Larger Pattern
```
Input: 6
Expected Output:
Floyd’s Triangle:
================
1
2 3
4 5 6
7 8 9 10
11 12 13 14 15
16 17 18 19 20 21
```

## 🔍 Explanation

1. **Counter Variable**: num starts from 1
2. **Outer Loop**: Controls the number of rows (i from 1 to rows)
3. **Inner Loop**: Controls numbers in each row (j from 1 to i)
4. **Increment**: num++ after each print
5. **Consecutive Numbers**: Each number is one more than previous

## 🎯 Key Concepts Covered

- Consecutive number generation
- Counter variables in loops
- Triangular patterns
- Sequential number printing
- Nested loop counters

## 🚀 Extensions

1. Print Floyd’s triangle in reverse order
2. Print only even numbers in sequence
3. Calculate sum of numbers in each row
4. Print Floyd’s triangle with different starting number