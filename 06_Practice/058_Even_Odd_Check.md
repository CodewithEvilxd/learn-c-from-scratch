# 🎯 Practical 58: Even Odd Check

## 📋 Problem Statement

Write a C program to check whether a number is even or odd.

## 🎯 Learning Objectives

- Understand even/odd concept
- Practice modulo operator
- Learn conditional statements
- Understand binary representation
- Practice input validation

## 📝 Requirements

1. Accept a number from user
2. Check if even or odd using modulo
3. Display result
4. Handle zero case
5. Clear output

## 💡 Hints

- Use number % 2 == 0 for even
- Handle negative numbers
- Zero is even
- Use if-else statements
- Clear result messages

## 🔧 Solution

```c
// Practical 58: Even Odd Check
// Checks if a number is even or odd

#include <stdio.h>

int main() {
    int number;

    printf("Even or Odd Checker\n");
    printf("===================\n");

    printf("Enter an integer: ");
    scanf("%d", &number);

    if (number % 2 == 0) {
        printf("%d is an even number.\n", number);
    } else {
        printf("%d is an odd number.\n", number);
    }

    // Additional information
    if (number == 0) {
        printf("Note: Zero is considered an even number.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Even Number
```
Input: 4
Expected Output:
4 is an even number.
```

### Test Case 2: Odd Number
```
Input: 7
Expected Output:
7 is an odd number.
```

### Test Case 3: Zero
```
Input: 0
Expected Output:
0 is an even number.
Note: Zero is considered an even number.
```

### Test Case 4: Negative Even
```
Input: -6
Expected Output:
-6 is an even number.
```

### Test Case 5: Negative Odd
```
Input: -9
Expected Output:
-9 is an odd number.
```

## 🔍 Explanation

1. **Modulo Operation**: number % 2 == 0 for even
2. **Even Numbers**: Divisible by 2
3. **Odd Numbers**: Not divisible by 2
4. **Zero**: Considered even
5. **Negative Numbers**: Same rules apply

## 🎯 Key Concepts Covered

- Modulo operator
- Conditional statements
- Even/odd concept
- Input validation
- Number properties

## 🚀 Extensions

1. Check multiple numbers
2. Find sum of even/odd in range
3. Check even/odd without modulo
4. Handle floating point numbers