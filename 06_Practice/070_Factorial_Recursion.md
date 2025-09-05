# 🎯 Practical 70: Factorial using Recursion

## 📋 Problem Statement

Write a C program to find factorial of a number using recursion.

## 🎯 Learning Objectives

- Understand recursive factorial
- Practice recursive functions
- Learn base cases for factorial
- Understand recursive multiplication
- Practice input validation

## 📝 Requirements

1. Accept a number n
2. Calculate n! using recursive function
3. Display the result
4. Handle base cases
5. Validate input

## 💡 Hints

- Base case: 0! = 1, 1! = 1
- Recursive case: n! = n * (n-1)!
- Use unsigned long long for large factorials
- Handle negative numbers
- Clear recursive logic

## 🔧 Solution

```c
// Practical 70: Factorial using Recursion
// Calculates factorial recursively

#include <stdio.h>

// Recursive factorial function
unsigned long long factorialRecursive(int n) {
    if (n < 0) {
        return 0; // Error case
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return (unsigned long long)n * factorialRecursive(n - 1);
}

int main() {
    int n;
    unsigned long long result;

    printf("Factorial Calculator (Recursive)\n");
    printf("=================================\n");

    printf("Enter a non-negative integer: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return 1;
    }

    if (n > 20) {
        printf("Warning: Factorial of %d is very large and may overflow!\n", n);
    }

    result = factorialRecursive(n);

    printf("%d! = %llu\n", n, result);

    // Show the expansion
    printf("Expansion: %d! = ", n);
    for (int i = n; i >= 1; i--) {
        printf("%d", i);
        if (i > 1) {
            printf(" × ");
        }
    }
    printf(" = %llu\n", result);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Number
```
Input: 5
Expected Output:
5! = 120
Expansion: 5! = 5 × 4 × 3 × 2 × 1 = 120
```

### Test Case 2: Base Case
```
Input: 0
Expected Output:
0! = 1
Expansion: 0! = 1
```

### Test Case 3: Larger Number
```
Input: 10
Expected Output:
10! = 3628800
Expansion: 10! = 10 × 9 × 8 × 7 × 6 × 5 × 4 × 3 × 2 × 1 = 3628800
```

## 🔍 Explanation

1. **Base Case**: n = 0 or n = 1 returns 1
2. **Recursive Case**: n * factorialRecursive(n-1)
3. **Call Stack**: Builds up recursive calls
4. **Return Values**: Multiplies on the way back
5. **Data Type**: unsigned long long for large values

## 🎯 Key Concepts Covered

- Recursive functions
- Factorial calculation
- Base cases
- Call stack
- Large number handling

## 🚀 Extensions

1. Calculate factorial iteratively
2. Handle very large factorials
3. Calculate double factorial
4. Compare recursive vs iterative performance