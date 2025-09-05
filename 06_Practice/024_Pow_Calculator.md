# 🎯 Practical 24: Pow Calculator

## 📋 Problem Statement

Write a C program to calculate pow(x,n).

## 🎯 Learning Objectives

- Understand power calculation
- Practice iterative methods
- Learn function implementation
- Understand exponential operations
- Practice input validation

## 📝 Requirements

1. Accept base x and exponent n
2. Calculate x^n
3. Handle negative exponents
4. Display result
5. Validate input

## 💡 Hints

- Use iterative multiplication
- Handle negative n
- Use double for precision
- Validate inputs
- Clear output

## 🔧 Solution

```c
// Practical 24: Pow Calculator
// Calculates x raised to power n

#include <stdio.h>

double power(double x, int n) {
    double result = 1.0;
    int abs_n = abs(n);

    for (int i = 0; i < abs_n; i++) {
        result *= x;
    }

    if (n < 0) {
        result = 1.0 / result;
    }

    return result;
}

int main() {
    double x, result;
    int n;

    printf("Pow Calculator\n");
    printf("==============\n");

    printf("Enter base (x): ");
    scanf("%lf", &x);

    printf("Enter exponent (n): ");
    scanf("%d", &n);

    result = power(x, n);

    printf("%.2f ^ %d = %.6f\n", x, n, result);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Exponent
```
Input: 2, 3
Expected Output:
2.00 ^ 3 = 8.000000
```

### Test Case 2: Negative Exponent
```
Input: 2, -2
Expected Output:
2.00 ^ -2 = 0.250000
```

### Test Case 3: Zero Exponent
```
Input: 5, 0
Expected Output:
5.00 ^ 0 = 1.000000
```

## 🔍 Explanation

1. **Iterative**: Multiply x, n times
2. **Negative**: Use reciprocal
3. **Precision**: Double for accuracy
4. **Abs**: Handle negative exponents
5. **Result**: Proper formatting

## 🎯 Key Concepts Covered

- Power calculation
- Iterative methods
- Negative exponents
- Precision handling
- Input validation

## 🚀 Extensions

1. Add fractional exponents
2. Use binary exponentiation
3. Handle very large exponents
4. Add logarithmic calculation