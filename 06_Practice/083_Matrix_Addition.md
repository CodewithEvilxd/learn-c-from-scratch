# 🎯 Practical 83: Matrix Addition

## 📋 Problem Statement

Write a C program to add two matrices using multi-dimensional arrays.

## 🎯 Learning Objectives

- Understand multi-dimensional arrays
- Practice matrix operations
- Learn nested loops
- Understand matrix addition rules
- Practice input validation

## 📝 Requirements

1. Accept matrix dimensions
2. Input two matrices
3. Add corresponding elements
4. Display result matrix
5. Validate matrix sizes

## 💡 Hints

- Use 2D arrays for matrices
- Check if matrices have same dimensions
- Use nested loops for input/output
- Add corresponding elements
- Display matrices clearly

## 🔧 Solution

```c
// Practical 83: Matrix Addition
// Adds two matrices using multi-dimensional arrays

#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int rows, cols;
    
    printf("Matrix Addition\n");
    printf("===============\n");
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    if (rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS) {
        printf("Invalid matrix dimensions!\n");
        return 1;
    }
    
    int matrix1[MAX_ROWS][MAX_COLS];
    int matrix2[MAX_ROWS][MAX_COLS];
    int result[MAX_ROWS][MAX_COLS];
    
    // Input first matrix
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix1[i][j]);
        }
    }
    
    // Input second matrix
    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix2[i][j]);
        }
    }
    
    // Add matrices
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    
    // Display first matrix
    printf("\nFirst Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    
    // Display second matrix
    printf("\nSecond Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    
    // Display result matrix
    printf("\nResult Matrix (Addition):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
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
Input: rows=2, cols=2
Matrix1: [1, 2, 3, 4]
Matrix2: [5, 6, 7, 8]
Expected Output:
Result: [6, 8, 10, 12]
```

### Test Case 2: 3x3 Matrices
```
Input: rows=3, cols=3
Matrix1: [1, 0, 0, 0, 1, 0, 0, 0, 1]
Matrix2: [1, 1, 1, 1, 1, 1, 1, 1, 1]
Expected Output:
Result: [2, 1, 1, 1, 2, 1, 1, 1, 2]
```

## 🔍 Explanation

1. **Input Dimensions**: Rows and columns
2. **Matrix Input**: Nested loops for 2D arrays
3. **Addition**: Add corresponding elements
4. **Display**: Show all three matrices
5. **Validation**: Check dimensions

## 🎯 Key Concepts Covered

- Multi-dimensional arrays
- Nested loops
- Matrix operations
- Input validation
- Array indexing

## 🚀 Extensions

1. Matrix subtraction
2. Scalar multiplication
3. Matrix multiplication
4. Transpose matrix