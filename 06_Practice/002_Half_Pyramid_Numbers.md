# 🎯 Practical 2: Half Pyramid of Numbers

## 📋 Problem Statement

Write a C Program to implement a half pyramid of numbers.

## 🎯 Learning Objectives

- Understand nested loops with numbers
- Practice number pattern printing
- Learn loop variable manipulation
- Understand row-column number relationships

## 📝 Requirements

1. Accept number of rows from user
2. Print numbers in half pyramid pattern
3. Use nested loops
4. Display numbers with proper spacing
5. Handle input validation

## 💡 Hints

- Use outer loop for rows
- Use inner loop for printing numbers
- Print numbers from 1 to current row number
- Use loop variable j for number printing

## 🔧 Solution

```c
// Practical 2: Half Pyramid of Numbers
// This program prints a half pyramid pattern using numbers

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

    printf("Half Pyramid of Numbers:\n");
    printf("=======================\n");

    // Outer loop for rows
    for (int i = 1; i <= rows; i++) {
        // Inner loop for numbers in each row
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
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
Half Pyramid of Numbers:
=======================
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Half Pyramid of Numbers:
=======================
1
```

### Test Case 3: Larger Pattern
```
Input: 7
Expected Output:
Half Pyramid of Numbers:
=======================
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
1 2 3 4 5 6
1 2 3 4 5 6 7
```

## 🔍 Explanation

1. **Outer Loop**: Controls rows (i from 1 to rows)
2. **Inner Loop**: Prints numbers 1 to i for each row
3. **Number Printing**: Uses inner loop variable j
4. **Pattern Logic**: Row i contains numbers 1 to i
5. **Spacing**: " " between numbers for readability

## 🎯 Key Concepts Covered

- Nested loops with number printing
- Loop variable relationships
- Sequential number generation
- Pattern recognition
- User input validation

## 🚀 Extensions

1. Print numbers in reverse order (i down to 1)
2. Print only odd numbers in each row
3. Print numbers in descending order per row
4. Add sum of numbers in each row