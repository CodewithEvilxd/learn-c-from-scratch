# 🎯 Practical 25: Arithmetic Progression Sum

## 📋 Problem Statement

Write a C program to find the sum of arithmetic progression series.

## 🎯 Learning Objectives

- Understand arithmetic progression
- Practice mathematical formulas
- Learn series summation
- Understand AP properties
- Practice input validation

## 📝 Requirements

1. Accept first term, common difference, number of terms
2. Calculate sum using formula
3. Calculate sum using loop
4. Display results
5. Show series

## 💡 Hints

- Formula: sum = n/2 * (2a + (n-1)d)
- Loop: accumulate terms
- Use float for precision
- Validate inputs
- Display series

## 🔧 Solution

```c
// Practical 25: Arithmetic Progression Sum
// Calculates sum of AP series

#include <stdio.h>

// Formula method
float sumAPFormula(float a, float d, int n) {
    return n / 2.0 * (2 * a + (n - 1) * d);
}

// Iterative method
float sumAPIterative(float a, float d, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a + i * d;
    }
    return sum;
}

int main() {
    float first_term, common_diff, sum_formula, sum_iter;
    int num_terms;

    printf("Arithmetic Progression Sum Calculator\n");
    printf("=====================================\n");

    printf("Enter first term: ");
    scanf("%f", &first_term);

    printf("Enter common difference: ");
    scanf("%f", &common_diff);

    printf("Enter number of terms: ");
    scanf("%d", &num_terms);

    if (num_terms <= 0) {
        printf("Number of terms must be positive!\n");
        return 1;
    }

    sum_formula = sumAPFormula(first_term, common_diff, num_terms);
    sum_iter = sumAPIterative(first_term, common_diff, num_terms);

    printf("\nArithmetic Progression: ");
    for (int i = 0; i < num_terms; i++) {
        printf("%.1f", first_term + i * common_diff);
        if (i < num_terms - 1) {
            printf(", ");
        }
    }

    printf("\nSum using formula: %.2f\n", sum_formula);
    printf("Sum using iteration: %.2f\n", sum_iter);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Common Difference
```
Input: 2, 3, 5
Expected Output:
Series: 2.0, 5.0, 8.0, 11.0, 14.0
Sum: 40.00
```

### Test Case 2: Negative Common Difference
```
Input: 10, -2, 4
Expected Output:
Series: 10.0, 8.0, 6.0, 4.0
Sum: 28.00
```

### Test Case 3: Single Term
```
Input: 5, 1, 1
Expected Output:
Series: 5.0
Sum: 5.00
```

## 🔍 Explanation

1. **Formula**: n/2 * (2a + (n-1)d)
2. **Iterative**: Sum each term in loop
3. **Series Display**: Show all terms
4. **Validation**: Positive n
5. **Precision**: Float for decimals

## 🎯 Key Concepts Covered

- Arithmetic progression
- Series summation
- Mathematical formulas
- Loop implementation
- Input validation

## 🚀 Extensions

1. Find nth term
2. Check if number is in AP
3. Generate AP with given sum
4. Handle geometric progression