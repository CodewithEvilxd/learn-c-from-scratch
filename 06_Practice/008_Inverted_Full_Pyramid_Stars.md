# 🎯 Practical 8: Inverted Full Pyramid of *

## 📋 Problem Statement

Write a C Program to implement an inverted full pyramid of * (stars).

## 🎯 Learning Objectives

- Understand inverted pyramid patterns
- Practice complex nested loops with spaces and stars
- Learn space calculation for centering
- Understand decreasing pattern sequences

## 📝 Requirements

1. Accept number of rows from user
2. Print inverted full pyramid pattern using *
3. Center the pyramid with spaces
4. Use nested loops for spaces and stars
5. Handle input validation

## 💡 Hints

- Use outer loop from rows down to 1
- First inner loop for leading spaces
- Second inner loop for stars
- Calculate spaces as rows - i
- Print stars equal to current row number

## 🔧 Solution

```c
// Practical 8: Inverted Full Pyramid of Stars
// This program prints an inverted full pyramid pattern using stars

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

    printf("Inverted Full Pyramid of Stars:\n");
    printf("==============================\n");

    // Outer loop for rows
    for (int i = rows; i >= 1; i--) {
        // First inner loop for leading spaces
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Second inner loop for stars
        for (int k = 1; k <= i; k++) {
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
Inverted Full Pyramid of Stars:
==============================
*****
 ****
  ***
   **
    *
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Inverted Full Pyramid of Stars:
==============================
*
```

### Test Case 3: Larger Pattern
```
Input: 6
Expected Output:
Inverted Full Pyramid of Stars:
==============================
******
 *****
  ****
   ***
    **
     *
```

## 🔍 Explanation

1. **Outer Loop**: Controls rows from rows down to 1 (i from rows to 1)
2. **Leading Spaces**: rows - i spaces for centering each row
3. **Stars Loop**: Prints i stars for current row
4. **Centering**: Pyramid perfectly centered with increasing spaces
5. **Decreasing Pattern**: Number of stars decreases by 1 each row

## 🎯 Key Concepts Covered

- Inverted pyramid patterns
- Complex nested loop patterns
- Space calculation for centering
- Decreasing sequence patterns
- Loop variable relationships

## 🚀 Extensions

1. Print inverted pyramid with numbers instead of stars
2. Add alternating colors or symbols
3. Print hollow inverted pyramid
4. Allow user to choose the symbol