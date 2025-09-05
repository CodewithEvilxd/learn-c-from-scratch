# 🎯 Practical 71: G.C.D Using Recursion

## 📋 Problem Statement

Write a C program to find G.C.D using recursion.

## 🎯 Learning Objectives

- Understand G.C.D concept
- Practice recursive functions
- Learn Euclid's algorithm
- Understand base cases
- Practice mathematical recursion

## 📝 Requirements

1. Accept two numbers
2. Calculate G.C.D recursively
3. Display the result
4. Handle edge cases
5. Show algorithm steps

## 💡 Hints

- Use Euclid's algorithm: gcd(a,b) = gcd(b, a%b)
- Base case: gcd(a, 0) = a
- Recursive case: gcd(a, b) = gcd(b, a % b)
- Handle negative numbers
- Show calculation steps

## 🔧 Solution

```c
// Practical 71: G.C.D Using Recursion
// Calculates G.C.D using recursive Euclid's algorithm

#include <stdio.h>

// Recursive function to calculate G.C.D
int gcdRecursive(int a, int b) {
    // Base case
    if (b == 0) {
        return a;
    }

    // Recursive case
    return gcdRecursive(b, a % b);
}

int main() {
    int num1, num2, result;

    printf("G.C.D Calculator (Recursive)\n");
    printf("=============================\n");

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    // Handle negative numbers
    int a = (num1 < 0) ? -num1 : num1;
    int b = (num2 < 0) ? -num2 : num2;

    result = gcdRecursive(a, b);

    printf("G.C.D of %d and %d is: %d\n", num1, num2, result);

    // Show the algorithm steps
    printf("\nAlgorithm steps:\n");
    int x = a, y = b;
    while (y != 0) {
        printf("gcd(%d, %d) = gcd(%d, %d %% %d) = gcd(%d, %d)\n",
               x, y, y, x, y, y, x % y);
        int temp = y;
        y = x % y;
        x = temp;
    }
    printf("Final result: %d\n", x);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Different Numbers
```
Input: 48, 18
Expected Output:
G.C.D of 48 and 18 is: 6
Algorithm steps:
gcd(48, 18) = gcd(18, 48 % 18) = gcd(18, 6)
gcd(18, 6) = gcd(6, 18 % 6) = gcd(6, 0)
Final result: 6
```

### Test Case 2: Prime Numbers
```
Input: 17, 13
Expected Output:
G.C.D of 17 and 13 is: 1
Algorithm steps:
gcd(17, 13) = gcd(13, 17 % 13) = gcd(13, 4)
gcd(13, 4) = gcd(4, 13 % 4) = gcd(4, 1)
gcd(4, 1) = gcd(1, 4 % 1) = gcd(1, 0)
Final result: 1
```

### Test Case 3: Same Numbers
```
Input: 25, 25
Expected Output:
G.C.D of 25 and 25 is: 25
Algorithm steps:
gcd(25, 25) = gcd(25, 25 % 25) = gcd(25, 0)
Final result: 25
```

## 🔍 Explanation

1. **Recursive Function**: gcdRecursive(a, b) calls itself
2. **Base Case**: When b == 0, return a
3. **Recursive Case**: gcd(b, a % b)
4. **Negative Handling**: Convert to positive
5. **Steps Display**: Show algorithm progression

## 🎯 Key Concepts Covered

- Recursive functions
- Euclid's algorithm
- G.C.D calculation
- Base cases
- Mathematical recursion

## 🚀 Extensions

1. Calculate L.C.M using G.C.D
2. Find G.C.D of multiple numbers
3. Implement iterative version
4. Handle very large numbers