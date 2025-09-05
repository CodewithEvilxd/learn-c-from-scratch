# 🎯 Practical 62: Sum of Natural Numbers

## 📋 Problem Statement

Write a C program to calculate the sum of natural numbers.

## 🎯 Learning Objectives

- Understand natural numbers
- Practice loop implementation
- Learn summation formulas
- Understand input validation
- Practice mathematical calculations

## 📝 Requirements

1. Accept a number n
2. Calculate sum of first n natural numbers
3. Display the result
4. Show the series
5. Handle edge cases

## 💡 Hints

- Use loop to sum 1 to n
- Formula: n(n+1)/2
- Handle n <= 0
- Display series clearly
- Use appropriate data types

## 🔧 Solution

```c
// Practical 62: Sum of Natural Numbers
// Calculates sum of first n natural numbers

#include <stdio.h>

int main() {
    int n;
    long long sum = 0;

    printf("Sum of Natural Numbers\n");
    printf("======================\n");

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    // Calculate sum using loop
    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    printf("Sum of first %d natural numbers: %lld\n", n, sum);

    // Display the series
    printf("Series: ");
    for (int i = 1; i <= n; i++) {
        printf("%d", i);
        if (i < n) {
            printf(" + ");
        } else {
            printf(" = %lld\n", sum);
        }
    }

    // Alternative: Using formula
    long long formula_sum = (long long)n * (n + 1) / 2;
    printf("Using formula n(n+1)/2: %lld\n", formula_sum);

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
Using formula n(n+1)/2: 15
```

### Test Case 2: Larger Number
```
Input: 10
Expected Output:
Sum of first 10 natural numbers: 55
Series: 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 = 55
Using formula n(n+1)/2: 55
```

### Test Case 3: Single Number
```
Input: 1
Expected Output:
Sum of first 1 natural numbers: 1
Series: 1 = 1
Using formula n(n+1)/2: 1
```

## 🔍 Explanation

1. **Input**: Accept positive integer n
2. **Loop Sum**: Add numbers from 1 to n
3. **Formula Sum**: Use n(n+1)/2
4. **Series Display**: Show all terms
5. **Validation**: Handle n <= 0

## 🎯 Key Concepts Covered

- Loop implementation
- Summation concepts
- Mathematical formulas
- Input validation
- Series display

## 🚀 Extensions

1. Sum of squares of natural numbers
1 + 2² + 3² + ... + n² = n(n+1)(2n+1)/6
2. Sum of cubes of natural numbers
1³ + 2³ + 3³ + ... + n³ = [n(n+1)/2]²
3. Sum of even natural numbers
4. Sum of odd natural numbers
5. Handle very large n values