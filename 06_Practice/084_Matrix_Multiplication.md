# 🎯 Practical 84: Matrix Multiplication

## 📋 Problem Statement

Write a C program to multiply two matrices using multi-dimensional arrays.

## 🎯 Learning Objectives

- Understand matrix multiplication
- Practice 2D array operations
- Learn nested loops for multiplication
- Understand matrix compatibility
- Practice result matrix handling

## 📝 Requirements

1. Accept matrix dimensions
2. Check multiplication compatibility
3. Input two matrices
4. Perform matrix multiplication
5. Display result matrix

## 💡 Hints

- Columns of first matrix = rows of second matrix
- Result dimensions: rows1 × columns2
- Use three nested loops
- Sum of products for each element
- Clear matrix display

## 🔧 Solution

```c
// Practical 84: Matrix Multiplication
// Multiplies two matrices using multi-dimensional arrays

#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int rows1, cols1, rows2, cols2;

    printf("Matrix Multiplication\n");
    printf("====================\n");

    // Input dimensions for first matrix
    printf("Enter rows and columns for first matrix: ");
    scanf("%d %d", &rows1, &cols1);

    // Input dimensions for second matrix
    printf("Enter rows and columns for second matrix: ");
    scanf("%d %d", &rows2, &cols2);

    // Check compatibility
    if (cols1 != rows2) {
        printf("Matrix multiplication not possible!\n");
        printf("Columns of first matrix (%d) must equal rows of second matrix (%d).\n",
               cols1, rows2);
        return 1;
    }

    if (rows1 > MAX_ROWS || cols1 > MAX_COLS || rows2 > MAX_ROWS || cols2 > MAX_COLS) {
        printf("Matrix dimensions too large!\n");
        return 1;
    }

    int matrix1[MAX_ROWS][MAX_COLS];
    int matrix2[MAX_ROWS][MAX_COLS];
    int result[MAX_ROWS][MAX_COLS] = {0};

    // Input first matrix
    printf("Enter elements of first matrix (%dx%d):\n", rows1, cols1);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix1[i][j]);
        }
    }

    // Input second matrix
    printf("Enter elements of second matrix (%dx%d):\n", rows2, cols2);
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix2[i][j]);
        }
    }

    // Matrix multiplication
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Display first matrix
    printf("\nFirst Matrix (%dx%d):\n", rows1, cols1);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }

    // Display second matrix
    printf("\nSecond Matrix (%dx%d):\n", rows2, cols2);
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    // Display result matrix
    printf("\nResult Matrix (%dx%d):\n", rows1, cols2);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: 2x2 Matrices
```
Input: Matrix1=[1,2,3,4], Matrix2=[5,6,7,8]
Expected Output:
Result: [19, 22, 43, 50]
```

### Test Case 2: 2x3 and 3x2
```
Input: Matrix1=[1,2,3,4,5,6], Matrix2=[7,8,9,10,11,12]
Expected Output:
Result: [58, 64, 139, 154]
```

## 🔍 Explanation

1. **Compatibility Check**: cols1 == rows2
2. **Result Dimensions**: rows1 × cols2
3. **Multiplication**: result[i][j] += matrix1[i][k] * matrix2[k][j]
4. **Three Loops**: i for rows, j for columns, k for summation
5. **Display**: All three matrices clearly

## 🎯 Key Concepts Covered

- Matrix multiplication algorithm
- 2D array operations
- Nested loops
- Matrix compatibility
- Result computation

## 🚀 Extensions

1. Add matrix addition/subtraction
2. Implement scalar multiplication
3. Add matrix transpose
4. Handle larger matrices