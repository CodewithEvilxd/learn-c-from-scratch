# 🎯 Practical 31: Exponential Series Sum

## 📋 Problem Statement

Write a C program to find sum of series 1/1! + 2/2! + 3/3! + …… + N/N!.

## 🎯 Learning Objectives

- Understand exponential series
- Practice factorial calculation
- Learn series summation
- Understand convergence to e
- Practice precision handling

## 📝 Requirements

1. Accept N
2. Calculate factorial for each term
3. Sum the series
4. Display result
5. Show convergence to e

## 💡 Hints

- Calculate factorial iteratively
- Sum i/i! for i from 1 to N
- Use double for precision
- Series approaches e ≈ 2.718
- Handle large factorials

## 🔧 Solution

```c
// Practical 31: Exponential Series Sum
// Calculates sum of 1/1! + 2/2! + 3/3! + ... + N/N!

#include <stdio.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

double exponentialSum(int n) {
    double sum = 0.0;
    
    for (int i = 1; i <= n; i++) {
        unsigned long long fact = factorial(i);
        sum += (double)i / fact;
    }
    
    return sum;
}

int main() {
    int n;
    double sum;

    printf("Exponential Series Sum Calculator\n");
    printf("=================================\n");

    printf("Enter N: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("N must be positive!\n");
        return 1;
    }

    if (n > 20) {
        printf("Warning: Factorials get very large for N > 20\n");
    }

    sum = exponentialSum(n);

    printf("\nExponential Series: 1/1!");
    for (int i = 2; i <= n; i++) {
        if (i <= 10) { // Show first 10 terms
            printf(" + %d/%d!", i, i);
        } else if (i == 11) {
            printf(" + ...");
            break;
        }
    }
    if (n > 10) {
        printf(" + %d/%d!", n, n);
    }

    printf("\nSum of first %d terms: %.10f\n", n, sum);
    printf("Euler's number e ≈ 2.7182818284\n");

    if (n >= 10) {
        printf("The series converges to e as N approaches infinity\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small N
```
Input: 5
Expected Output:
Series: 1/1! + 2/2! + 3/3! + 4/4! + 5/5!
Sum: 2.7166666667
```

### Test Case 2: N = 1
```
Input: 1
Expected Output:
Series: 1/1!
Sum: 1.0000000000
```

### Test Case 3: Larger N
```
Input: 10
Expected Output:
Series: 1/1! + 2/2! + 3/3! + 4/4! + 5/5! + 6/6! + 7/7! + 8/8! + 9/9! + 10/10!
Sum: 2.7182818011
```

## 🔍 Explanation

1. **Series**: Sum of i/i! from 1 to N
2. **Factorial**: Calculate n! for each term
3. **Precision**: Use double for accuracy
4. **Convergence**: Approaches e as N increases
5. **Display**: Show partial series

## 🎯 Key Concepts Covered

- Exponential series
- Factorial calculation
- Series summation
- Precision handling
- Mathematical convergence

## 🚀 Extensions

1. Calculate e using more terms
2. Compare with exp(1)
3. Calculate alternating series
4. Find N for given precision