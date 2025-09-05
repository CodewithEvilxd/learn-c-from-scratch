# 🎯 Practical 73: Power Using Recursion

## 📋 Problem Statement

Write a C program to calculate the power using recursion.

## 🎯 Learning Objectives

- Understand recursive power calculation
- Practice recursive functions
- Learn base cases for power
- Understand recursive multiplication
- Practice input validation

## 📝 Requirements

1. Accept base and exponent
2. Calculate power recursively
3. Handle negative exponents
4. Display the result
5. Show calculation steps

## 💡 Hints

- Base case: x^0 = 1
- Recursive case: x^n = x * x^(n-1)
- Handle negative exponents
- Use double for precision
- Show recursive calls

## 🔧 Solution

```c
// Practical 73: Power Using Recursion
// Calculates power using recursive function

#include <stdio.h>

// Recursive function to calculate power
double powerRecursive(double base, int exponent) {
    // Base case
    if (exponent == 0) {
        return 1;
    }

    // Handle negative exponents
    if (exponent < 0) {
        return 1 / powerRecursive(base, -exponent);
    }

    // Recursive case
    return base * powerRecursive(base, exponent - 1);
}

int main() {
    double base, result;
    int exponent;

    printf("Power Calculator (Recursive)\n");
    printf("=============================\n");

    printf("Enter base: ");
    scanf("%lf", &base);

    printf("Enter exponent: ");
    scanf("%d", &exponent);

    result = powerRecursive(base, exponent);

    printf("%.2f ^ %d = %.6f\n", base, exponent, result);

    // Show calculation steps for small exponents
    if (exponent >= 0 && exponent <= 5) {
        printf("\nCalculation steps:\n");
        for (int i = exponent; i >= 0; i--) {
            double step_result = powerRecursive(base, i);
            if (i == 0) {
                printf("%.2f^%d = %.6f\n", base, i, step_result);
            } else {
                printf("%.2f^%d = %.2f × ", base, i, base);
                if (i > 1) {
                    printf("%.2f^%d", base, i - 1);
                } else {
                    printf("%.2f^%d", base, i - 1);
                }
                printf(" = %.6f\n", step_result);
            }
        }
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Exponent
```
Input: Base=2, Exponent=3
Expected Output:
2.00 ^ 3 = 8.000000
Calculation steps:
2.00^3 = 2.00 × 2.00^2 = 8.000000
2.00^2 = 2.00 × 2.00^1 = 4.000000
2.00^1 = 2.00 × 2.00^0 = 2.000000
2.00^0 = 1.000000
```

### Test Case 2: Zero Exponent
```
Input: Base=5, Exponent=0
Expected Output:
5.00 ^ 0 = 1.000000
```

### Test Case 3: Negative Exponent
```
Input: Base=2, Exponent=-2
Expected Output:
2.00 ^ -2 = 0.250000
```

## 🔍 Explanation

1. **Base Case**: exponent == 0 returns 1
2. **Negative Handling**: Use reciprocal for negative exponents
3. **Recursive Case**: base * powerRecursive(base, exponent - 1)
4. **Steps Display**: Show calculation for small exponents
5. **Precision**: Use double for accurate results

## 🎯 Key Concepts Covered

- Recursive functions
- Power calculation
- Base cases
- Negative exponent handling
- Recursive thinking

## 🚀 Extensions

1. Implement faster exponentiation
2. Handle fractional exponents
3. Add iterative version
4. Calculate power series