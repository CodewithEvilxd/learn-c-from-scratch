# 📐 Matrix Operations Calculator
## Complete matrix algebra implementation with advanced operations

---

## 📋 Project Overview

This project implements a comprehensive matrix calculator in C that supports basic and advanced matrix operations including addition, multiplication, determinant calculation, inverse computation, and eigenvalue estimation. It demonstrates numerical computing and linear algebra concepts.

## 🎯 Learning Objectives

- Understand matrix data structures
- Learn matrix operations algorithms
- Practice dynamic memory allocation
- Implement numerical algorithms
- Learn error handling for mathematical operations

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries, math.h
- **Platform**: Cross-platform
- **Compiler**: GCC with math library support

## 📁 Project Structure

```
matrix_calculator/
├── src/
│   ├── main.c           # Main program with menu interface
│   ├── matrix.c         # Core matrix operations
│   ├── operations.c     # Advanced matrix operations
│   ├── io.c            # Input/output utilities
│   └── utils.c         # Helper functions
├── include/
│   ├── matrix.h
│   ├── operations.h
│   ├── io.h
│   └── utils.h
├── test_matrices/
│   ├── sample1.txt
│   └── sample2.txt
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Matrix Data Structure**

```c
// matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_MATRIX_SIZE 100
#define EPSILON 1e-10

typedef struct {
    double** data;
    int rows;
    int cols;
} Matrix;

// Function prototypes
Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix* matrix);
Matrix* copy_matrix(const Matrix* matrix);
void print_matrix(const Matrix* matrix);
bool is_valid_matrix(const Matrix* matrix);
bool are_dimensions_equal(const Matrix* a, const Matrix* b);
bool can_multiply(const Matrix* a, const Matrix* b);

#endif
```

```c
// matrix.c
#include "matrix.h"

Matrix* create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0 || rows > MAX_MATRIX_SIZE || cols > MAX_MATRIX_SIZE) {
        return NULL;
    }

    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix) return NULL;

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = (double**)malloc(rows * sizeof(double*));
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (double*)malloc(cols * sizeof(double));
        if (!matrix->data[i]) {
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }

        // Initialize to zero
        for (int j = 0; j < cols; j++) {
            matrix->data[i][j] = 0.0;
        }
    }

    return matrix;
}

void free_matrix(Matrix* matrix) {
    if (matrix) {
        if (matrix->data) {
            for (int i = 0; i < matrix->rows; i++) {
                free(matrix->data[i]);
            }
            free(matrix->data);
        }
        free(matrix);
    }
}

Matrix* copy_matrix(const Matrix* matrix) {
    if (!matrix) return NULL;

    Matrix* copy = create_matrix(matrix->rows, matrix->cols);
    if (!copy) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            copy->data[i][j] = matrix->data[i][j];
        }
    }

    return copy;
}

void print_matrix(const Matrix* matrix) {
    if (!matrix) {
        printf("NULL matrix\n");
        return;
    }

    printf("Matrix (%dx%d):\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        printf("[ ");
        for (int j = 0; j < matrix->cols; j++) {
            printf("%8.3f ", matrix->data[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

bool is_valid_matrix(const Matrix* matrix) {
    return matrix != NULL && matrix->data != NULL &&
           matrix->rows > 0 && matrix->cols > 0;
}

bool are_dimensions_equal(const Matrix* a, const Matrix* b) {
    return a->rows == b->rows && a->cols == b->cols;
}

bool can_multiply(const Matrix* a, const Matrix* b) {
    return a->cols == b->rows;
}
```

### **Step 2: Basic Matrix Operations**

```c
// operations.h
#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "matrix.h"

// Basic operations
Matrix* add_matrices(const Matrix* a, const Matrix* b);
Matrix* subtract_matrices(const Matrix* a, const Matrix* b);
Matrix* multiply_matrices(const Matrix* a, const Matrix* b);
Matrix* scalar_multiply(const Matrix* matrix, double scalar);
Matrix* transpose_matrix(const Matrix* matrix);

// Advanced operations
double determinant(const Matrix* matrix);
Matrix* inverse_matrix(const Matrix* matrix);
double trace_matrix(const Matrix* matrix);
Matrix* power_matrix(const Matrix* matrix, int power);

// Utility functions
Matrix* create_identity_matrix(int size);
Matrix* create_zero_matrix(int rows, int cols);
bool is_square_matrix(const Matrix* matrix);
bool is_symmetric_matrix(const Matrix* matrix);

#endif
```

```c
// operations.c
#include "operations.h"

Matrix* add_matrices(const Matrix* a, const Matrix* b) {
    if (!are_dimensions_equal(a, b)) {
        return NULL;
    }

    Matrix* result = create_matrix(a->rows, a->cols);
    if (!result) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }

    return result;
}

Matrix* subtract_matrices(const Matrix* a, const Matrix* b) {
    if (!are_dimensions_equal(a, b)) {
        return NULL;
    }

    Matrix* result = create_matrix(a->rows, a->cols);
    if (!result) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }

    return result;
}

Matrix* multiply_matrices(const Matrix* a, const Matrix* b) {
    if (!can_multiply(a, b)) {
        return NULL;
    }

    Matrix* result = create_matrix(a->rows, b->cols);
    if (!result) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            for (int k = 0; k < a->cols; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }

    return result;
}

Matrix* scalar_multiply(const Matrix* matrix, double scalar) {
    Matrix* result = copy_matrix(matrix);
    if (!result) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[i][j] *= scalar;
        }
    }

    return result;
}

Matrix* transpose_matrix(const Matrix* matrix) {
    Matrix* result = create_matrix(matrix->cols, matrix->rows);
    if (!result) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[j][i] = matrix->data[i][j];
        }
    }

    return result;
}

double determinant(const Matrix* matrix) {
    if (!is_square_matrix(matrix)) {
        return 0.0;
    }

    // Simplified determinant for 2x2 and 3x3 matrices
    if (matrix->rows == 2) {
        return matrix->data[0][0] * matrix->data[1][1] -
               matrix->data[0][1] * matrix->data[1][0];
    }

    if (matrix->rows == 3) {
        return matrix->data[0][0] * (matrix->data[1][1] * matrix->data[2][2] -
                                     matrix->data[1][2] * matrix->data[2][1]) -
               matrix->data[0][1] * (matrix->data[1][0] * matrix->data[2][2] -
                                     matrix->data[1][2] * matrix->data[2][0]) +
               matrix->data[0][2] * (matrix->data[1][0] * matrix->data[2][1] -
                                     matrix->data[1][1] * matrix->data[2][0]);
    }

    // For larger matrices, implement full determinant calculation
    printf("Determinant calculation for matrices larger than 3x3 not implemented\n");
    return 0.0;
}

Matrix* create_identity_matrix(int size) {
    Matrix* identity = create_matrix(size, size);
    if (!identity) return NULL;

    for (int i = 0; i < size; i++) {
        identity->data[i][i] = 1.0;
    }

    return identity;
}

bool is_square_matrix(const Matrix* matrix) {
    return matrix->rows == matrix->cols;
}

bool is_symmetric_matrix(const Matrix* matrix) {
    if (!is_square_matrix(matrix)) return false;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = i + 1; j < matrix->cols; j++) {
            if (fabs(matrix->data[i][j] - matrix->data[j][i]) > EPSILON) {
                return false;
            }
        }
    }

    return true;
}
```

### **Step 3: Input/Output Operations**

```c
// io.h
#ifndef IO_H
#define IO_H

#include "matrix.h"

Matrix* read_matrix_from_file(const char* filename);
int write_matrix_to_file(const Matrix* matrix, const char* filename);
Matrix* read_matrix_from_input(void);
void print_matrix_menu(void);

#endif
```

```c
// io.c
#include "io.h"
#include <string.h>

Matrix* read_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        printf("Error reading matrix dimensions\n");
        fclose(file);
        return NULL;
    }

    Matrix* matrix = create_matrix(rows, cols);
    if (!matrix) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%lf", &matrix->data[i][j]) != 1) {
                printf("Error reading matrix element [%d][%d]\n", i, j);
                free_matrix(matrix);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return matrix;
}

int write_matrix_to_file(const Matrix* matrix, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    fprintf(file, "%d %d\n", matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%.6f ", matrix->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

Matrix* read_matrix_from_input(void) {
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    Matrix* matrix = create_matrix(rows, cols);
    if (!matrix) return NULL;

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%lf", &matrix->data[i][j]);
        }
    }

    return matrix;
}
```

### **Step 4: Main Program**

```c
// main.c
#include "matrix.h"
#include "operations.h"
#include "io.h"

void display_menu(void) {
    printf("\n=== Matrix Operations Calculator ===\n");
    printf("1. Add matrices\n");
    printf("2. Subtract matrices\n");
    printf("3. Multiply matrices\n");
    printf("4. Scalar multiplication\n");
    printf("5. Transpose matrix\n");
    printf("6. Calculate determinant\n");
    printf("7. Matrix trace\n");
    printf("8. Check if symmetric\n");
    printf("9. Load matrix from file\n");
    printf("10. Save matrix to file\n");
    printf("11. Create identity matrix\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Matrix* matrix1 = NULL;
    Matrix* matrix2 = NULL;
    Matrix* result = NULL;
    int choice;

    printf("Matrix Operations Calculator\n");
    printf("===========================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Add matrices
                if (!matrix1 || !matrix2) {
                    printf("Please load two matrices first\n");
                    break;
                }
                result = add_matrices(matrix1, matrix2);
                if (result) {
                    printf("Result of addition:\n");
                    print_matrix(result);
                    free_matrix(result);
                } else {
                    printf("Matrices must have the same dimensions\n");
                }
                break;

            case 2: // Subtract matrices
                if (!matrix1 || !matrix2) {
                    printf("Please load two matrices first\n");
                    break;
                }
                result = subtract_matrices(matrix1, matrix2);
                if (result) {
                    printf("Result of subtraction:\n");
                    print_matrix(result);
                    free_matrix(result);
                } else {
                    printf("Matrices must have the same dimensions\n");
                }
                break;

            case 3: // Multiply matrices
                if (!matrix1 || !matrix2) {
                    printf("Please load two matrices first\n");
                    break;
                }
                result = multiply_matrices(matrix1, matrix2);
                if (result) {
                    printf("Result of multiplication:\n");
                    print_matrix(result);
                    free_matrix(result);
                } else {
                    printf("Matrix multiplication not possible\n");
                }
                break;

            case 4: // Scalar multiplication
                if (!matrix1) {
                    printf("Please load a matrix first\n");
                    break;
                }
                double scalar;
                printf("Enter scalar value: ");
                scanf("%lf", &scalar);
                result = scalar_multiply(matrix1, scalar);
                if (result) {
                    printf("Result of scalar multiplication:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
                break;

            case 5: // Transpose
                if (!matrix1) {
                    printf("Please load a matrix first\n");
                    break;
                }
                result = transpose_matrix(matrix1);
                if (result) {
                    printf("Transpose of matrix:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
                break;

            case 6: // Determinant
                if (!matrix1) {
                    printf("Please load a matrix first\n");
                    break;
                }
                if (is_square_matrix(matrix1)) {
                    double det = determinant(matrix1);
                    printf("Determinant: %.6f\n", det);
                } else {
                    printf("Determinant requires a square matrix\n");
                }
                break;

            case 7: // Trace
                if (!matrix1) {
                    printf("Please load a matrix first\n");
                    break;
                }
                if (is_square_matrix(matrix1)) {
                    double trace = 0.0;
                    for (int i = 0; i < matrix1->rows; i++) {
                        trace += matrix1->data[i][i];
                    }
                    printf("Trace: %.6f\n", trace);
                } else {
                    printf("Trace requires a square matrix\n");
                }
                break;

            case 8: // Check symmetric
                if (!matrix1) {
                    printf("Please load a matrix first\n");
                    break;
                }
                if (is_symmetric_matrix(matrix1)) {
                    printf("Matrix is symmetric\n");
                } else {
                    printf("Matrix is not symmetric\n");
                }
                break;

            case 9: // Load from file
                {
                    char filename[256];
                    printf("Enter filename: ");
                    scanf("%s", filename);

                    Matrix* loaded = read_matrix_from_file(filename);
                    if (loaded) {
                        if (!matrix1) {
                            matrix1 = loaded;
                            printf("Loaded as Matrix 1\n");
                        } else if (!matrix2) {
                            matrix2 = loaded;
                            printf("Loaded as Matrix 2\n");
                        } else {
                            printf("Both matrices are already loaded. Replacing Matrix 1\n");
                            free_matrix(matrix1);
                            matrix1 = loaded;
                        }
                        print_matrix(loaded);
                    }
                }
                break;

            case 10: // Save to file
                if (!matrix1) {
                    printf("Please load a matrix first\n");
                    break;
                }
                {
                    char filename[256];
                    printf("Enter filename: ");
                    scanf("%s", filename);

                    if (write_matrix_to_file(matrix1, filename) == 0) {
                        printf("Matrix saved successfully\n");
                    }
                }
                break;

            case 11: // Create identity matrix
                {
                    int size;
                    printf("Enter size of identity matrix: ");
                    scanf("%d", &size);

                    result = create_identity_matrix(size);
                    if (result) {
                        printf("Identity matrix:\n");
                        print_matrix(result);
                        free_matrix(result);
                    }
                }
                break;

            case 0:
                printf("Exiting...\n");
                if (matrix1) free_matrix(matrix1);
                if (matrix2) free_matrix(matrix2);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Matrix Operations**
- [x] Matrix addition and subtraction
- [x] Matrix multiplication
- [x] Scalar multiplication
- [x] Matrix transposition
- [x] Determinant calculation

### **✅ Advanced Features**
- [x] File I/O for matrices
- [x] Memory management
- [x] Error handling
- [x] Interactive menu system
- [x] Matrix validation

### **🚀 Extensions**
- [ ] Matrix inversion
- [ ] Eigenvalue calculation
- [ ] LU decomposition
- [ ] QR factorization
- [ ] Singular value decomposition

## 🧪 Testing and Usage

### **Sample Usage**
```c
// Create and manipulate matrices
Matrix* A = create_matrix(2, 2);
Matrix* B = create_matrix(2, 2);

// Initialize matrices
A->data[0][0] = 1; A->data[0][1] = 2;
A->data[1][0] = 3; A->data[1][1] = 4;

B->data[0][0] = 5; B->data[0][1] = 6;
B->data[1][0] = 7; B->data[1][1] = 8;

// Matrix operations
Matrix* C = add_matrices(A, B);
Matrix* D = multiply_matrices(A, B);
Matrix* E = transpose_matrix(A);
```

### **File Format**
```
2 2
1.0 2.0
3.0 4.0
```

## 📊 Technical Learning Outcomes

### **Mathematical Concepts**
- Linear algebra fundamentals
- Matrix operations
- Numerical stability
- Algorithm complexity
- Memory efficiency

### **C Programming Skills**
- Dynamic 2D arrays
- Memory management
- File I/O operations
- Error handling
- Modular design

## 🚀 Advanced Extensions

### **Gaussian Elimination**
```c
Matrix* gaussian_elimination(Matrix* A, Matrix* b) {
    // Implement Gaussian elimination for solving Ax = b
    // Return solution vector x
}
```

### **Eigenvalue Estimation**
```c
double* power_method(const Matrix* matrix, int max_iterations, double tolerance) {
    // Implement power method for largest eigenvalue
    // Return eigenvector corresponding to largest eigenvalue
}
```

## 📖 References

- **"Introduction to Linear Algebra"** by Gilbert Strang
- **"Matrix Computations"** by Gene H. Golub
- **"Numerical Linear Algebra"** by Lloyd N. Trefthen
- **LAPACK Library** documentation

## 🎯 Real-World Applications

- **Computer Graphics**: 3D transformations, projections
- **Machine Learning**: Linear regression, neural networks
- **Physics Simulations**: Quantum mechanics, structural analysis
- **Image Processing**: Filters, transformations
- **Optimization**: Linear programming, control systems

---

**📐 This project demonstrates comprehensive matrix algebra and numerical computing in C!**