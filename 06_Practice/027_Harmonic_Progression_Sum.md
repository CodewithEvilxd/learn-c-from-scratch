# 🎯 Practical 27: Harmonic Progression Sum

## 📋 Problem Statement

Write a C program to find the sum of harmonic progression series.

## 🎯 Learning Objectives

- Understand harmonic progression
- Practice series summation
- Learn reciprocal calculations
- Understand HP properties
- Practice input validation

## 📝 Requirements

1. Accept first term, common difference, number of terms
2. Calculate sum using loop
3. Display results
4. Show series
5. Handle division by zero

## 💡 Hints

- HP terms: 1/a, 1/(a+d), 1/(a+2d), ...
- No simple closed formula
- Use loop to accumulate
- Check for zero terms
- Use float for precision

## 🔧 Solution

```c
// Practical 27: Harmonic Progression Sum
// Calculates sum of HP series

#include <stdio.h>

// Iterative method
double sumHP(double a, double d, int n) {
    double sum = 0;
    double term = a;
    
    for (int i = 0; i < n; i++) {
        if (term == 0) {
            printf("Error: Division by zero at term %d\n", i + 1);
            return -1; // Error
        }
        sum += 1.0 / term;
        term += d;
    }
    return sum;
}

int main() {
    double first_term, common_diff, sum;
    int num_terms;

    printf("Harmonic Progression Sum Calculator\n");
    printf("===================================\n");

    printf("Enter first term: ");
    scanf("%lf", &first_term);

    printf("Enter common difference: ");
    scanf("%lf", &common_diff);

    printf("Enter number of terms: ");
    scanf("%d", &num_terms);

    if (num_terms <= 0) {
        printf("Number of terms must be positive!\n");
        return 1;
    }

    if (first_term == 0) {
        printf("First term cannot be zero!\n");
        return 1;
    }

    sum = sumHP(first_term, common_diff, num_terms);

    if (sum == -1) {
        return 1;
    }

    printf("\nHarmonic Progression: ");
    double term = first_term;
    for (int i = 0; i < num_terms; i++) {
        printf("1/%.2f", term);
        if (i < num_terms - 1) {
            printf(" + ");
        }
        term += common_diff;
    }

    printf("\nSum: %.6f\n", sum);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Simple HP
```
Input: 1, 1, 3
Expected Output:
Series: 1/1.00 + 1/2.00 + 1/3.00
Sum: 1.833333
```

### Test Case 2: Fractional Terms
```
Input: 0.5, 0.5, 2
Expected Output:
Series: 1/0.50 + 1/1.00
Sum: 2.500000
```

### Test Case 3: Negative Difference
```
Input: 2, -1, 2
Expected Output:
Series: 1/2.00 + 1/1.00
Sum: 1.500000
```

## 🔍 Explanation

1. **HP Terms**: Reciprocals of AP terms
2. **Sum**: Accumulate 1/term in loop
3. **Validation**: Check for zero terms
4. **Display**: Show reciprocal notation
5. **Precision**: Use double for accuracy

## 🎯 Key Concepts Covered

- Harmonic progression
- Reciprocal calculations
- Series summation
- Error handling
- Input validation

## 🚀 Extensions

1. Find nth term
2. Check if sequence is HP
3. Calculate harmonic mean
4. Handle infinite HP