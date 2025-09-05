# 🎯 Practical 41: Fibonacci Sequence

## 📋 Problem Statement

Write a C program to display Fibonacci sequence.

## 🎯 Learning Objectives

- Understand Fibonacci sequence
- Practice iterative and recursive approaches
- Learn sequence generation
- Understand large number handling
- Practice loop control

## 📝 Requirements

1. Accept number of terms
2. Generate Fibonacci sequence
3. Display sequence
4. Handle large numbers
5. Validate input

## 💡 Hints

- Use iterative for efficiency
- Handle overflow with long long
- Start with 0, 1
- Each term is sum of previous two
- Clear output formatting

## 🔧 Solution

```c
// Practical 41: Fibonacci Sequence
// Generates Fibonacci sequence

#include <stdio.h>

// Iterative Fibonacci
void fibonacciIterative(int n) {
    unsigned long long a = 0, b = 1, next;

    printf("Fibonacci Sequence (Iterative):\n");
    for (int i = 0; i < n; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = a + b;
            a = b;
            b = next;
        }
        printf("%llu ", next);
    }
    printf("\n");
}

// Recursive Fibonacci
unsigned long long fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;

    printf("Fibonacci Sequence Generator\n");
    printf("===========================\n");

    printf("Enter number of terms: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of terms must be positive!\n");
        return 1;
    }

    if (n > 50) {
        printf("Warning: Large n may cause overflow!\n");
    }

    fibonacciIterative(n);

    printf("Fibonacci Sequence (Recursive):\n");
    for (int i = 0; i < n; i++) {
        printf("%llu ", fibonacciRecursive(i));
    }
    printf("\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Sequence
```
Input: 8
Expected Output:
0 1 1 2 3 5 8 13
```

### Test Case 2: First Term
```
Input: 1
Expected Output:
0
```

### Test Case 3: Two Terms
```
Input: 2
Expected Output:
0 1
```

## 🔍 Explanation

1. **Iterative**: Uses loop with two variables
2. **Recursive**: Calls itself for each term
3. **Sequence**: F(n) = F(n-1) + F(n-2)
4. **Base Cases**: F(0) = 0, F(1) = 1
5. **Data Type**: unsigned long long for large values

## 🎯 Key Concepts Covered

- Fibonacci mathematics
- Iterative vs recursive
- Sequence generation
- Large number handling
- Loop control

## 🚀 Extensions

1. Find nth Fibonacci number
2. Check if number is Fibonacci
3. Generate Fibonacci with different starting values
4. Add golden ratio calculation