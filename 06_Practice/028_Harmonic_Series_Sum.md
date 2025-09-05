# 🎯 Practical 28: Harmonic Series Sum

## 📋 Problem Statement

Write a C program to find sum of series 1 + 1/2 + 1/3 + 1/4 + ……. + 1/N.

## 🎯 Learning Objectives

- Understand harmonic series
- Practice loop summation
- Learn reciprocal calculations
- Understand series convergence
- Practice input validation

## 📝 Requirements

1. Accept N (number of terms)
2. Calculate sum using loop
3. Display result
4. Show series terms
5. Handle large N

## 💡 Hints

- Use loop from 1 to N
- Sum 1.0/i for each i
- Use double for precision
- Display partial series
- Validate N > 0

## 🔧 Solution

```c
// Practical 28: Harmonic Series Sum
// Calculates sum of 1 + 1/2 + 1/3 + ... + 1/N

#include <stdio.h>

double harmonicSum(int n) {
    double sum = 0.0;
    
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    
    return sum;
}

int main() {
    int n;
    double sum;

    printf("Harmonic Series Sum Calculator\n");
    printf("===============================\n");

    printf("Enter N (number of terms): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("N must be positive!\n");
        return 1;
    }

    sum = harmonicSum(n);

    printf("\nHarmonic Series: 1");
    for (int i = 2; i <= n; i++) {
        if (i <= 10) { // Show first 10 terms
            printf(" + 1/%d", i);
        } else if (i == 11) {
            printf(" + ...");
            break;
        }
    }
    if (n > 10) {
        printf(" + 1/%d", n);
    }

    printf("\nSum of first %d terms: %.6f\n", n, sum);

    if (n > 100) {
        printf("Note: Harmonic series diverges as N approaches infinity\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small N
```
Input: 5
Expected Output:
Series: 1 + 1/2 + 1/3 + 1/4 + 1/5
Sum: 2.283333
```

### Test Case 2: Larger N
```
Input: 10
Expected Output:
Series: 1 + 1/2 + 1/3 + 1/4 + 1/5 + 1/6 + 1/7 + 1/8 + 1/9 + 1/10
Sum: 2.928968
```

### Test Case 3: N = 1
```
Input: 1
Expected Output:
Series: 1
Sum: 1.000000
```

## 🔍 Explanation

1. **Series**: Sum of reciprocals 1 + 1/2 + 1/3 + ...
2. **Loop**: Accumulate 1.0/i from 1 to N
3. **Precision**: Use double for accuracy
4. **Display**: Show partial series
5. **Convergence**: Note about divergence

## 🎯 Key Concepts Covered

- Harmonic series
- Reciprocal summation
- Loop implementation
- Precision handling
- Series properties

## 🚀 Extensions

1. Calculate harmonic number H_n
2. Compare with natural log approximation
3. Find N for sum > given value
4. Calculate alternating harmonic series