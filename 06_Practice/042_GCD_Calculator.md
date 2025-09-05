# 🎯 Practical 42: GCD Calculator

## 📋 Problem Statement

Write a C program to find GCD of two numbers.

## 🎯 Learning Objectives

- Understand GCD concept
- Practice Euclidean algorithm
- Learn recursive and iterative approaches
- Understand mathematical algorithms
- Practice function implementation

## 📝 Requirements

1. Accept two numbers
2. Calculate GCD
3. Use Euclidean algorithm
4. Handle validation
5. Display result

## 💡 Hints

- Euclidean algorithm: gcd(a,b) = gcd(b, a%b)
- Base case: gcd(a,0) = a
- Handle negative numbers
- Use recursion or iteration
- Validate inputs

## 🔧 Solution

```c
// Practical 42: GCD Calculator
// Calculates GCD using Euclidean algorithm

#include <stdio.h>

// Iterative GCD
int gcdIterative(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Recursive GCD
int gcdRecursive(int a, int b) {
    a = abs(a);
    b = abs(b);

    if (b == 0) {
        return a;
    }
    return gcdRecursive(b, a % b);
}

int main() {
    int num1, num2, gcd_iter, gcd_recur;

    printf("GCD Calculator\n");
    printf("==============\n");

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    if (num1 == 0 && num2 == 0) {
        printf("GCD of 0 and 0 is undefined!\n");
        return 1;
    }

    gcd_iter = gcdIterative(num1, num2);
    gcd_recur = gcdRecursive(num1, num2);

    printf("GCD of %d and %d:\n", num1, num2);
    printf("Iterative: %d\n", gcd_iter);
    printf("Recursive: %d\n", gcd_recur);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Coprime Numbers
```
Input: 15, 28
Expected Output:
GCD: 1
```

### Test Case 2: Common Factors
```
Input: 24, 36
Expected Output:
GCD: 12
```

### Test Case 3: One Zero
```
Input: 10, 0
Expected Output:
GCD: 10
```

## 🔍 Explanation

1. **Euclidean Algorithm**: gcd(a,b) = gcd(b, a%b)
2. **Iterative**: Uses while loop
3. **Recursive**: Calls itself with smaller numbers
4. **Absolute Values**: Handles negative numbers
5. **Base Case**: When remainder is 0

## 🎯 Key Concepts Covered

- GCD calculation
- Euclidean algorithm
- Recursive functions
- Mathematical algorithms
- Input validation

## 🚀 Extensions

1. Calculate LCM
2. Handle multiple numbers
3. Add extended Euclidean algorithm
4. Performance comparison