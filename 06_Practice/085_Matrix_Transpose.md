# 🎯 Practical 85: Matrix Transpose

## 📋 Problem Statement

Write a C program to find transpose of a matrix.

## 🎯 Learning Objectives

- Understand matrix transpose operation
- Practice 2D array manipulation
- Learn row-column swapping
- Understand matrix properties
- Practice nested loops

## 📝 Requirements

1. Accept matrix dimensions
2. Input matrix elements
3. Create transpose matrix
4. Display original and transpose
5. Handle different dimensions

## 💡 Hints

- Transpose: swap matrix[i][j] with matrix[j][i]
- For transpose, rows become columns
- Use separate array for result
- Handle rectangular matrices
- Display clearly formatted output

## 🔧 Solution

```c
// Practical 85: Matrix Transpose
// Finds transpose of a matrix

#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int rows, cols;
    
    printf("Matrix Transpose\n");
    printf("================\n");
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    if (rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS) {
        printf("Invalid matrix dimensions!\n");
        return 1;
    }
    
    int matrix[MAX_ROWS][MAX_COLS];
    int transpose[MAX_COLS][MAX_ROWS];
    
    // Input matrix
    printf("Enter elements of matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // Create transpose
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
    
    // Display original matrix
    printf("\nOriginal Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Display transpose matrix
    printf("\nTranspose Matrix (%dx%d):\n", cols, rows);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Square Matrix
```
Input: rows=3, cols=3
Matrix: [1, 2, 3, 4, 5, 6, 7, 8, 9]
Expected Output:
Transpose: [1, 4, 7, 2, 5, 8, 3, 6, 9]
```

### Test Case 2: Rectangular Matrix
```
Input: rows=2, cols=3
Matrix: [1, 2, 3, 4, 5, 6]
Expected Output:
Transpose: [1, 4, 2, 5, 3, 6]
```

### Test Case 3: Single Row
```
Input: rows=1, cols=4
Matrix: [1, 2, 3, 4]
Expected Output:
Transpose: [1, 2, 3, 4]
```

## 🔍 Explanation

1. **Input Matrix**: Accept dimensions and elements
2. **Transpose Logic**: transpose[j][i] = matrix[i][j]
3. **Dimension Swap**: rows ↔ columns
4. **Display**: Show both matrices clearly
5. **Validation**: Check dimensions

## 🎯 Key Concepts Covered

- Matrix transpose operation
- 2D array manipulation
- Nested loops
- Row-column swapping
- Matrix properties

## 🚀 Extensions

1. In-place transpose for square matrices
2. Check if matrix equals its transpose
3. Transpose sparse matrices
4. Multiple matrix operations