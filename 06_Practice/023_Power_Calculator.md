# 🎯 Practical 23: Power Calculator

## 📋 Problem Statement

Write a C program to find power of a number.

## 🎯 Learning Objectives

- Understand exponentiation
- Practice mathematical functions
- Learn iterative power calculation
- Understand pow() function
- Practice input validation

## 📝 Requirements

1. Accept base and exponent
2. Calculate power
3. Handle negative exponents
4. Display result
5. Validate input

## 💡 Hints

- Use pow() from math.h
- Implement iterative multiplication
- Handle negative bases
- Use double for precision
- Clear output

## 🔧 Solution

```c
// Practical 23: Power Calculator
// Calculates base^exponent

#include <stdio.h>
#include <math.h>

// Iterative power function
double powerIterative(double base, int exponent) {
    double result = 1.0;
    int abs_exp = abs(exponent);

    for (int i = 0; i < abs_exp; i++) {
        result *= base;
    }

    if (exponent < 0) {
        result = 1.0 / result;
    }

    return result;
}

int main() {
    double base, result_pow, result_iter;
    int exponent;

    printf("Power Calculator\n");
    printf("================\n");

    printf("Enter base: ");
    scanf("%lf", &base);

    printf("Enter exponent: ");
    scanf("%d", &exponent);

    // Using pow() function
    result_pow = pow(base, exponent);

    // Using iterative method
    result_iter = powerIterative(base, exponent);

    printf("Result using pow(): %.6f\n", result_pow);
    printf("Result using iteration: %.6f\n", result_iter);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Exponent
```
Input: 2, 3
Expected Output:
Result: 8.000000
```

### Test Case 2: Negative Exponent
```
Input: 2, -2
Expected Output:
Result: 0.250000
```

### Test Case 3: Zero Exponent
```
Input: 5, 0
Expected Output:
Result: 1.000000
```

## 🔍 Explanation

1. **pow() Function**: Uses math.h library
2. **Iterative**: Multiplies base exponent times
3. **Negative Exponent**: Uses reciprocal
4. **Precision**: Uses double for accuracy
5. **Validation**: Handles edge cases

## 🎯 Key Concepts Covered

- Exponentiation
- Mathematical functions
- Iterative calculation
- Precision handling
- Input validation

## 🚀 Extensions

1. Handle fractional exponents
2. Add logarithmic calculation
3. Support complex exponents
4. Add power series