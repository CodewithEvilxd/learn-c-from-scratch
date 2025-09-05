# 🎯 Practical 11: Diamond Pattern

## 📋 Problem Statement

Write a C Program to print diamond pattern.

## 🎯 Learning Objectives

- Understand complex pattern printing
- Practice multiple nested loops
- Learn upper and lower half patterns
- Understand space and star calculations

## 📝 Requirements

1. Accept number of rows from user
2. Print diamond pattern using *
3. Center the diamond with spaces
4. Handle input validation
5. Use proper formatting

## 💡 Hints

- Use two separate loops for upper and lower halves
- Upper half: spaces decrease, stars increase
- Lower half: spaces increase, stars decrease
- Stars in row i: 2*i - 1
- Spaces: rows - i

## 🔧 Solution

```c
// Practical 11: Diamond Pattern
// This program prints a diamond pattern using stars

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

    printf("Diamond Pattern:\n");
    printf("===============\n");

    // Upper half of diamond
    for (int i = 1; i <= rows; i++) {
        // Print leading spaces
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Print stars
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }

        printf("\n");
    }

    // Lower half of diamond
    for (int i = rows - 1; i >= 1; i--) {
        // Print leading spaces
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Print stars
        for (int k = 1; k <= 2 * i - 1; k++) {
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
Diamond Pattern:
===============
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

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Diamond Pattern:
===============
*
```

### Test Case 3: Larger Pattern
```
Input: 6
Expected Output:
Diamond Pattern:
===============
     *
    ***
   *****
  *******
 *********
***********
 *********
  *******
   *****
    ***
     *
```

## 🔍 Explanation

1. **Upper Half**: i from 1 to rows
2. **Lower Half**: i from rows-1 down to 1
3. **Spaces**: rows - i spaces for centering
4. **Stars**: 2*i - 1 stars in row i
5. **Symmetry**: Lower half mirrors upper half

## 🎯 Key Concepts Covered

- Complex pattern printing
- Upper and lower half logic
- Space calculation for centering
- Symmetrical patterns
- Multiple loop structures

## 🚀 Extensions

1. Print hollow diamond pattern
2. Print diamond with numbers
3. Add colors to the diamond
4. Print diamond with different symbols