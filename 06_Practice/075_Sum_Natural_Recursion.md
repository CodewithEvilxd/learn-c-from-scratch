# 🎯 Practical 75: Sum of Natural Numbers using Recursion

## 📋 Problem Statement

Write a C program to find the sum of natural numbers using recursion.

## 🎯 Learning Objectives

- Understand recursive functions
- Practice recursion implementation
- Learn base cases
- Understand call stack
- Practice recursive thinking

## 📝 Requirements

1. Accept a number n
2. Calculate sum using recursive function
3. Display the result
4. Handle base cases
5. Show the series

## 💡 Hints

- Base case: sum(0) = 0 or sum(1) = 1
- Recursive case: sum(n) = n + sum(n-1)
- Use function with return value
- Handle negative numbers
- Clear recursive logic

## 🔧 Solution

```c
// Practical 75: Sum of Natural Numbers using Recursion
// Calculates sum of first n natural numbers recursively

#include <stdio.h>

// Recursive function to calculate sum
int sumNatural(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sumNatural(n - 1);
}

int main() {
    int n, result;

    printf("Sum of Natural Numbers (Recursive)\n");
    printf("===================================\n");

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    result = sumNatural(n);

    printf("Sum of first %d natural numbers: %d\n", n, result);

    // Show the series
    printf("Series: ");
    for (int i = 1; i <= n; i++) {
        printf("%d", i);
        if (i < n) {
            printf(" + ");
        } else {
            printf(" = %d\n", result);
        }
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Number
```
Input: 5
Expected Output:
Sum of first 5 natural numbers: 15
Series: 1 + 2 + 3 + 4 + 5 = 15
```

### Test Case 2: Single Number
```
Input: 1
Expected Output:
Sum of first 1 natural numbers: 1
Series: 1 = 1
```

### Test Case 3: Zero
```
Input: 0
Expected Output:
Sum of first 0 natural numbers: 0
Series: = 0
```

## 🔍 Explanation

1. **Recursive Function**: sumNatural(n) calls itself
2. **Base Case**: n <= 0 returns 0
3. **Recursive Case**: n + sumNatural(n-1)
4. **Call Stack**: Builds up recursive calls
5. **Unwinding**: Returns values back up the stack

## 🎯 Key Concepts Covered

- Recursive functions
- Base cases
- Recursive calls
- Call stack
- Recursive thinking

## 🚀 Extensions

1. Calculate sum of squares recursively
1 + 2² + 3² + ... + n² = n(n+1)(2n+1)/6
2. Sum of cubes recursively
1³ + 2³ + 3³ + ... + n³ = [n(n+1)/2]²
3. Sum of even natural numbers
4. Sum of odd natural numbers
5. Handle very large n values