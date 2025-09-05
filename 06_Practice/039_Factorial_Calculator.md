# 🎯 Practical 39: Factorial Calculator

## 📋 Problem Statement

Write a C program to find factorial of a number.

## 🎯 Learning Objectives

- Understand factorial calculation
- Practice iterative and recursive approaches
- Learn function implementation
- Understand large number handling
- Practice input validation

## 📝 Requirements

1. Accept positive integer
2. Calculate factorial
3. Handle large numbers
4. Display result
5. Validate input

## 💡 Hints

- Use long long for large factorials
- Implement iterative loop
- Optional recursive function
- Check for overflow
- Handle 0! = 1

## 🔧 Solution

```c
// Practical 39: Factorial Calculator
// Calculates factorial of a number

#include <stdio.h>

// Iterative factorial function
unsigned long long factorialIterative(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive factorial function
unsigned long long factorialRecursive(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorialRecursive(n - 1);
}

int main() {
    int n;
    unsigned long long fact_iter, fact_recur;

    printf("Factorial Calculator\n");
    printf("===================\n");

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is not defined for negative numbers!\n");
        return 1;
    }

    if (n > 20) {
        printf("Warning: Factorial of %d is very large and may overflow!\n", n);
    }

    fact_iter = factorialIterative(n);
    fact_recur = factorialRecursive(n);

    printf("Factorial of %d:\n", n);
    printf("Iterative: %llu\n", fact_iter);
    printf("Recursive: %llu\n", fact_recur);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Number
```
Input: 5
Expected Output:
Factorial of 5:
Iterative: 120
Recursive: 120
```

### Test Case 2: Zero
```
Input: 0
Expected Output:
Factorial of 0:
Iterative: 1
Recursive: 1
```

### Test Case 3: Large Number
```
Input: 10
Expected Output:
Factorial of 10:
Iterative: 3628800
Recursive: 3628800
```

## 🔍 Explanation

1. **Iterative**: Uses loop to multiply
2. **Recursive**: Calls itself with n-1
3. **Base Case**: 0! = 1! = 1
4. **Data Type**: unsigned long long for large values
5. **Validation**: Checks for negative input

## 🎯 Key Concepts Covered

- Factorial mathematics
- Iterative vs recursive
- Function implementation
- Large number handling
- Input validation

## 🚀 Extensions

1. Calculate factorial with floating point
2. Add gamma function
3. Handle very large factorials
4. Add factorial series