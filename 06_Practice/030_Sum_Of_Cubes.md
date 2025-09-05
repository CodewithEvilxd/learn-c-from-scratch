# 🎯 Practical 30: Sum of Cubes

## 📋 Problem Statement

Write a C program to find sum of series 1^3 + 2^3 + 3^3 + … + n^3.

## 🎯 Learning Objectives

- Understand sum of cubes formula
- Practice mathematical formulas
- Learn series summation
- Understand cubic series
- Practice input validation

## 📝 Requirements

1. Accept n
2. Calculate sum using formula
3. Calculate sum using loop
4. Display results
5. Show series

## 💡 Hints

- Formula: [n(n+1)/2]^2
- Loop: sum i*i*i from 1 to n
- Use long long for large sums
- Validate n > 0
- Compare methods

## 🔧 Solution

```c
// Practical 30: Sum of Cubes
// Calculates sum of 1^3 + 2^3 + ... + n^3

#include <stdio.h>

// Formula method
long long sumCubesFormula(int n) {
    long long sum = (long long)n * (n + 1) / 2;
    return sum * sum;
}

// Iterative method
long long sumCubesIterative(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i * i;
    }
    return sum;
}

int main() {
    int n;
    long long sum_formula, sum_iter;

    printf("Sum of Cubes Calculator\n");
    printf("=======================\n");

    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("n must be positive!\n");
        return 1;
    }

    sum_formula = sumCubesFormula(n);
    sum_iter = sumCubesIterative(n);

    printf("\nSum of cubes: 1^3");
    for (int i = 2; i <= n; i++) {
        if (i <= 10) { // Show first 10 terms
            printf(" + %d^3", i);
        } else if (i == 11) {
            printf(" + ...");
            break;
        }
    }
    if (n > 10) {
        printf(" + %d^3", n);
    }

    printf("\nSum using formula: %lld\n", sum_formula);
    printf("Sum using iteration: %lld\n", sum_iter);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small n
```
Input: 3
Expected Output:
Series: 1^3 + 2^3 + 3^3
Sum: 36
```

### Test Case 2: n = 1
```
Input: 1
Expected Output:
Series: 1^3
Sum: 1
```

### Test Case 3: Larger n
```
Input: 5
Expected Output:
Series: 1^3 + 2^3 + 3^3 + 4^3 + 5^3
Sum: 225
```

## 🔍 Explanation

1. **Formula**: [n(n+1)/2]^2
2. **Iterative**: Sum i*i*i in loop
3. **Data Type**: long long for large sums
4. **Series Display**: Show partial series
5. **Validation**: Positive n

## 🎯 Key Concepts Covered

- Sum of cubes formula
- Mathematical formulas
- Loop implementation
- Large number handling
- Series summation

## 🚀 Extensions

1. Sum of fourth powers
2. General power sum
3. Compare formula vs loop performance
4. Calculate sum of odd cubes