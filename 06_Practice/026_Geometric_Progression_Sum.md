# 🎯 Practical 26: Geometric Progression Sum

## 📋 Problem Statement

Write a C program to find the sum of geometric progression series.

## 🎯 Learning Objectives

- Understand geometric progression
- Practice mathematical formulas
- Learn series summation
- Understand GP properties
- Practice input validation

## 📝 Requirements

1. Accept first term, common ratio, number of terms
2. Calculate sum using formula
3. Calculate sum using loop
4. Display results
5. Show series

## 💡 Hints

- Formula: sum = a * (r^n - 1) / (r - 1) for r ≠ 1
- Special case: r = 1, sum = n * a
- Loop: accumulate terms
- Use pow() for r^n
- Validate r ≠ 0

## 🔧 Solution

```c
// Practical 26: Geometric Progression Sum
// Calculates sum of GP series

#include <stdio.h>
#include <math.h>

// Formula method
double sumGPFormula(double a, double r, int n) {
    if (r == 1) {
        return n * a;
    } else {
        return a * (pow(r, n) - 1) / (r - 1);
    }
}

// Iterative method
double sumGPIterative(double a, double r, int n) {
    double sum = 0;
    double term = a;
    
    for (int i = 0; i < n; i++) {
        sum += term;
        term *= r;
    }
    return sum;
}

int main() {
    double first_term, common_ratio, sum_formula, sum_iter;
    int num_terms;

    printf("Geometric Progression Sum Calculator\n");
    printf("====================================\n");

    printf("Enter first term: ");
    scanf("%lf", &first_term);

    printf("Enter common ratio: ");
    scanf("%lf", &common_ratio);

    printf("Enter number of terms: ");
    scanf("%d", &num_terms);

    if (num_terms <= 0) {
        printf("Number of terms must be positive!\n");
        return 1;
    }

    sum_formula = sumGPFormula(first_term, common_ratio, num_terms);
    sum_iter = sumGPIterative(first_term, common_ratio, num_terms);

    printf("\nGeometric Progression: ");
    double term = first_term;
    for (int i = 0; i < num_terms; i++) {
        printf("%.2f", term);
        if (i < num_terms - 1) {
            printf(", ");
        }
        term *= common_ratio;
    }

    printf("\nSum using formula: %.2f\n", sum_formula);
    printf("Sum using iteration: %.2f\n", sum_iter);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Common Ratio ≠ 1
```
Input: 2, 3, 4
Expected Output:
Series: 2.00, 6.00, 18.00, 54.00
Sum: 80.00
```

### Test Case 2: Common Ratio = 1
```
Input: 5, 1, 3
Expected Output:
Series: 5.00, 5.00, 5.00
Sum: 15.00
```

### Test Case 3: Fractional Ratio
```
Input: 1, 0.5, 3
Expected Output:
Series: 1.00, 0.50, 0.25
Sum: 1.75
```

## 🔍 Explanation

1. **Formula**: a * (r^n - 1) / (r - 1) for r ≠ 1
2. **Special Case**: r = 1, sum = n * a
3. **Iterative**: Multiply term by r each time
4. **Series Display**: Show all terms
5. **Validation**: Positive n

## 🎯 Key Concepts Covered

- Geometric progression
- Series summation
- Mathematical formulas
- Loop implementation
- Special case handling

## 🚀 Extensions

1. Find nth term
2. Check if number is in GP
3. Generate GP with given sum
4. Handle infinite GP