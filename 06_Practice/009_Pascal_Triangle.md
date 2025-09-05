# 🎯 Practical 9: Pascal Triangle

## 📋 Problem Statement

Write a C Program to implement Pascal's triangle.

## 🎯 Learning Objectives

- Understand binomial coefficients
- Practice mathematical computations in programming
- Learn triangular number patterns
- Understand iterative calculation methods
- Practice proper output formatting

## 📝 Requirements

1. Accept number of rows from user
2. Calculate binomial coefficients for each position
3. Print Pascal triangle with proper alignment
4. Use efficient calculation method
5. Handle input validation

## 💡 Hints

- Use binomial coefficient formula C(n,k) = n! / (k! * (n-k)!)
- Implement iterative calculation to avoid factorial overflow
- Use nested loops for rows and columns
- Add spaces for centering the triangle
- Validate user input for positive numbers

## 🔧 Solution

```c
// Practical 9: Pascal Triangle
// This program prints Pascal's triangle using binomial coefficients

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

    printf("Pascal's Triangle:\n");
    printf("=================\n");

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
Pascal's Triangle:
=================
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
Pascal's Triangle:
=================
1
```

### Test Case 3: Larger Pattern
```
Input: 6
Expected Output:
Pascal's Triangle:
=================
     1
    1 1
   1 2 1
  1 3 3 1
 1 4 6 4 1
1 5 10 10 5 1
```

### Test Case 4: Invalid Input
```
Input: -2
Expected Output:
Please enter a positive number!
```

## 🔍 Explanation

1. **Binomial Coefficient**: C(n,k) represents the number of ways to choose k items from n items
2. **Iterative Calculation**: Uses efficient loop to avoid computing large factorials
3. **Centering**: Adds leading spaces to center each row of the triangle
4. **Row Structure**: Each row i contains coefficients C(i,0) through C(i,i)
5. **Pattern Property**: Each number is the sum of the two numbers above it

## 🎯 Key Concepts Covered

- Mathematical computations in C
- Binomial coefficients calculation
- Triangular pattern generation
- Input validation
- Proper output formatting

## 🚀 Extensions

1. Print Pascal triangle without centering
2. Calculate sum of each row (should be 2^n)
3. Print only specific rows
4. Use recursive function for binomial coefficients
5. Add color formatting to the output