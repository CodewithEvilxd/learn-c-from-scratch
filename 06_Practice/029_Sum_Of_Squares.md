# 🎯 Practical 29: Sum of Squares

## 📋 Problem Statement

Write a C program to find sum of series 1^2 + 2^2 + …. + n^2.

## 🎯 Learning Objectives

- Understand sum of squares formula
- Practice mathematical formulas
- Learn series summation
- Understand quadratic series
- Practice input validation

## 📝 Requirements

1. Accept n
2. Calculate sum using formula
3. Calculate sum using loop
4. Display results
5. Show series

## 💡 Hints

- Formula: n(n+1)(2n+1)/6
- Loop: sum i*i from 1 to n
- Use long long for large sums
- Validate n > 0
- Compare methods

## 🔧 Solution

```c
// Practical 29: Sum of Squares
// Calculates sum of 1^2 + 2^2 + ... + n^2

#include <stdio.h>

// Formula method
long long sumSquaresFormula(int n) {
    return (long long)n * (n + 1) * (2 * n + 1) / 6;
}

// Iterative method
long long sumSquaresIterative(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i;
    }
    return sum;
}

int main() {
    int n;
    long long sum_formula, sum_iter;

    printf("Sum of Squares Calculator\n");
    printf("=========================\n");

    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("n must be positive!\n");
        return 1;
    }

    sum_formula = sumSquaresFormula(n);
    sum_iter = sumSquaresIterative(n);

    printf("\nSum of squares: 1^2");
    for (int i = 2; i <= n; i++) {
        if (i <= 10) { // Show first 10 terms
            printf(" + %d^2", i);
        } else if (i == 11) {
            printf(" + ...");
            break;
        }
    }
    if (n > 10) {
        printf(" + %d^2", n);
    }

    printf("\nSum using formula: %lld\n", sum_formula);
    printf("Sum using iteration: %lld\n", sum_iter);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small n
```
Input: 5
Expected Output:
Series: 1^2 + 2^2 + 3^2 + 4^2 + 5^2
Sum: 55
```

### Test Case 2: n = 1
```
Input: 1
Expected Output:
Series: 1^2
Sum: 1
```

### Test Case 3: Larger n
```
Input: 10
Expected Output:
Series: 1^2 + 2^2 + 3^2 + 4^2 + 5^2 + 6^2 + 7^2 + 8^2 + 9^2 + 10^2
Sum: 385
```

## 🔍 Explanation

1. **Formula**: n(n+1)(2n+1)/6
2. **Iterative**: Sum i*i in loop
3. **Data Type**: long long for large sums
4. **Series Display**: Show partial series
5. **Validation**: Positive n

## 🎯 Key Concepts Covered

- Sum of squares formula
- Mathematical formulas
- Loop implementation
- Large number handling
- Series summation

## 🚀 Extensions

1. Sum of cubes
2. Sum of fourth powers
3. General power sum
4. Compare formula vs loop performance