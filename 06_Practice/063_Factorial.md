# 🎯 Practical 63: Factorial Calculator

## 📋 Problem Statement

Write a C program to find factorial of a number.

## 🎯 Learning Objectives

- Understand factorial concept
- Practice iterative multiplication
- Learn loop implementation
- Understand large number handling
- Practice input validation

## 📝 Requirements

1. Accept a number n
2. Calculate n!
3. Display the result
4. Handle edge cases
5. Show multiplication series

## 💡 Hints

- Use loop from 1 to n
- Multiply result by each number
- Handle 0! = 1
- Use unsigned long long for large values
- Display the series

## 🔧 Solution

```c
// Practical 63: Factorial Calculator
// Calculates factorial of a number

#include <stdio.h>

int main() {
    int n;
    unsigned long long factorial = 1;

    printf("Factorial Calculator\n");
    printf("====================\n");

    printf("Enter a non-negative integer: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return 1;
    }

    if (n > 20) {
        printf("Warning: Factorial of %d is very large and may overflow!\n", n);
    }

    // Calculate factorial
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    printf("%d! = %llu\n", n, factorial);

    // Display the series
    if (n > 0) {
        printf("Series: ");
        for (int i = n; i >= 1; i--) {
            printf("%d", i);
            if (i > 1) {
                printf(" × ");
            } else {
                printf(" = %llu\n", factorial);
            }
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
5! = 120
Series: 5 × 4 × 3 × 2 × 1 = 120
```

### Test Case 2: Zero
```
Input: 0
Expected Output:
0! = 1
```

### Test Case 3: Single Number
```
Input: 1
Expected Output:
1! = 1
Series: 1 = 1
```

### Test Case 4: Larger Number
```
Input: 10
Expected Output:
10! = 3628800
Series: 10 × 9 × 8 × 7 × 6 × 5 × 4 × 3 × 2 × 1 = 3628800
```

## 🔍 Explanation

1. **Input**: Accept non-negative integer
2. **Loop**: Multiply from 1 to n
3. **Factorial**: Accumulate product
4. **Series Display**: Show multiplication steps
5. **Validation**: Handle negative numbers

## 🎯 Key Concepts Covered

- Factorial calculation
- Loop implementation
- Large number handling
- Input validation
- Series display

## 🚀 Extensions

1. Calculate factorial recursively
2. Handle very large factorials
3. Calculate double factorial
4. Find factorial of floating point numbers