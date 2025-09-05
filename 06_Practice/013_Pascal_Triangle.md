# 🎯 Practical 13: Pascal Triangle

## 📋 Problem Statement

Write a C Program to print Pascal triangle.

## 🎯 Learning Objectives

- Understand binomial coefficients
- Practice mathematical computations in programming
- Learn recursive and iterative approaches
- Understand triangular number patterns
- Practice function implementation

## 📝 Requirements

1. Accept number of rows from user
2. Print Pascal triangle with binomial coefficients
3. Center the triangle with spaces
4. Use proper formatting
5. Handle input validation

## 💡 Hints

- Use binomial coefficient formula C(n,k) = n! / (k! * (n-k)!)
- Implement iterative calculation to avoid large factorials
- Use nested loops for rows and columns
- Calculate spaces for centering
- Print coefficients with proper spacing

## 🔧 Solution

```c
// Practical 13: Pascal Triangle
// This program prints Pascal triangle using binomial coefficients

#include <stdio.h>

// Function to calculate binomial coefficient C(n, k)
long long binomialCoeff(int n, int k) {
    long long res = 1;

    // Since C(n, k) = C(n, n-k)
    if (k > n - k)
        k = n - k;

    // Calculate value of [n * (n-1) * ... * (n-k+1)] / [k * (k-1) * ... * 1]
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

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

    printf("Pascal Triangle:\n");
    printf("===============\n");

    // Outer loop for rows
    for (int i = 0; i < rows; i++) {
        // Print leading spaces for centering
        for (int j = 0; j < rows - i - 1; j++) {
            printf(" ");
        }

        // Print binomial coefficients for current row
        for (int j = 0; j <= i; j++) {
            printf("%lld ", binomialCoeff(i, j));
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
Pascal Triangle:
===============
    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Pascal Triangle:
===============
1
```

### Test Case 3: Larger Pattern
```
Input: 6
Expected Output:
Pascal Triangle:
===============
     1
    1 1
   1 2 1
  1 3 3 1
 1 4 6 4 1
1 5 10 10 5 1
```

## 🔍 Explanation

1. **Binomial Coefficient**: C(n,k) = n! / (k! * (n-k)!)
2. **Iterative Calculation**: Avoids computing large factorials
3. **Centering**: Uses spaces to center each row
4. **Row Loop**: i from 0 to rows-1
5. **Column Loop**: j from 0 to i for each row

## 🎯 Key Concepts Covered

- Mathematical computations in C
- Function implementation
- Binomial coefficients
- Triangular patterns
- Space calculation for centering

## 🚀 Extensions

1. Print Pascal triangle without centering
2. Calculate sum of each row
3. Print only specific rows
4. Use recursive function for binomial coefficients