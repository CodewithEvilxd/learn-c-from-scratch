# 🎯 Practical 6: Full Pyramid of *

## 📋 Problem Statement

Write a C Program to implement a full pyramid of * (stars).

## 🎯 Learning Objectives

- Understand full pyramid pattern printing
- Practice complex nested loops
- Learn space and star alignment
- Understand pyramid geometry

## 📝 Requirements

1. Accept number of rows from user
2. Print full pyramid pattern with proper alignment
3. Use spaces for left alignment
4. Center the pyramid
5. Handle input validation

## 💡 Hints

- Use three nested loops (spaces, stars, spaces)
- Calculate spaces needed for centering
- First loop prints leading spaces
- Second loop prints stars
- Use proper spacing formula

## 🔧 Solution

```c
// Practical 6: Full Pyramid of Stars
// This program prints a full pyramid pattern

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

    printf("Full Pyramid of Stars:\n");
    printf("=====================\n");

    // Outer loop for rows
    for (int i = 1; i <= rows; i++) {
        // First inner loop for leading spaces
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Second inner loop for stars
        for (int k = 1; k <= (2 * i - 1); k++) {
            printf("*");
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
Full Pyramid of Stars:
=====================
    *
   ***
  *****
 *******
*********
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Full Pyramid of Stars:
=====================
*
```

### Test Case 3: Larger Pattern
```
Input: 6
Expected Output:
Full Pyramid of Stars:
=====================
     *
    ***
   *****
  *******
 *********
***********
```

## 🔍 Explanation

1. **Leading Spaces**: rows - i spaces for centering
2. **Stars Formula**: (2 * i - 1) stars per row
3. **Alignment**: Pyramid centered with spaces
4. **Pattern Logic**: Each row wider than previous
5. **Symmetry**: Perfectly centered pattern

## 🎯 Key Concepts Covered

- Complex nested loop patterns
- Space calculation for centering
- Mathematical formula for star count
- Pyramid geometry understanding
- Pattern alignment techniques

## 🚀 Extensions

1. Print numbers instead of stars
2. Add borders around the pyramid
3. Create a hollow pyramid
4. Print pyramid upside down