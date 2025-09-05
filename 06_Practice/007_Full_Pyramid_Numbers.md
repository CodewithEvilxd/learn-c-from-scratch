# 🎯 Practical 7: Full Pyramid of Numbers

## 📋 Problem Statement

Write a C Program to implement a full pyramid of numbers.

## 🎯 Learning Objectives

- Understand number pattern in full pyramid
- Practice complex nested loops with numbers
- Learn number sequencing in pyramid format
- Understand centered number patterns

## 📝 Requirements

1. Accept number of rows from user
2. Print numbers in full pyramid pattern
3. Center the pyramid with spaces
4. Use sequential numbers
5. Handle input validation

## 💡 Hints

- Use three nested loops (spaces, numbers, spaces)
- Calculate spaces for centering
- Print numbers sequentially
- Use proper alignment

## 🔧 Solution

```c
// Practical 7: Full Pyramid of Numbers
// This program prints a full pyramid pattern using numbers

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

    printf("Full Pyramid of Numbers:\n");
    printf("========================\n");

    // Outer loop for rows
    for (int i = 1; i <= rows; i++) {
        // First inner loop for leading spaces
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Second inner loop for numbers
        for (int k = 1; k <= i; k++) {
            printf("%d ", k);
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
Full Pyramid of Numbers:
========================
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
Full Pyramid of Numbers:
========================
1
```

### Test Case 3: Larger Pattern
```
Input: 6
Expected Output:
Full Pyramid of Numbers:
========================
     1
    1 2
   1 2 3
  1 2 3 4
 1 2 3 4 5
1 2 3 4 5 6
```

## 🔍 Explanation

1. **Leading Spaces**: rows - i spaces for centering
2. **Number Sequence**: Prints 1 to i for each row
3. **Centering**: Pyramid perfectly centered
4. **Sequential Pattern**: Each row starts from 1
5. **Increasing Length**: Row length increases by 1 each time

## 🎯 Key Concepts Covered

- Complex nested loop patterns
- Number sequencing in patterns
- Space calculation for centering
- Pyramid alignment techniques
- Sequential number generation

## 🚀 Extensions

1. Print numbers in reverse order per row
2. Print only odd numbers in each row
3. Add sum calculation for each row
4. Print numbers in descending order