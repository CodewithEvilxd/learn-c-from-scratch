# 🎯 Practical 45: Reverse a Number

## 📋 Problem Statement

Write a C program to reverse a number using looping concepts.

## 🎯 Learning Objectives

- Understand number reversal logic
- Practice loop implementation
- Learn digit extraction
- Understand modulo and division operations
- Practice input validation

## 📝 Requirements

1. Accept a number from user
2. Reverse the digits using loop
3. Display the reversed number
4. Handle negative numbers
5. Validate input

## 💡 Hints

- Use while loop
- Extract last digit with % 10
- Remove last digit with / 10
- Build reversed number
- Handle negative sign separately

## 🔧 Solution

```c
// Practical 45: Reverse a Number
// Reverses digits of a number using looping

#include <stdio.h>

int main() {
    int number, reversed = 0, remainder, original;

    printf("Number Reversal Program\n");
    printf("=======================\n");

    printf("Enter an integer: ");
    scanf("%d", &number);

    original = number;

    // Handle negative numbers
    if (number < 0) {
        printf("Reversal of negative numbers will be positive.\n");
        number = -number;
    }

    // Reverse using loop
    while (number != 0) {
        remainder = number % 10;
        reversed = reversed * 10 + remainder;
        number /= 10;
    }

    printf("Original number: %d\n", original);
    printf("Reversed number: %d\n", reversed);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Number
```
Input: 12345
Expected Output:
Original number: 12345
Reversed number: 54321
```

### Test Case 2: Negative Number
```
Input: -987
Expected Output:
Reversal of negative numbers will be positive.
Original number: -987
Reversed number: 789
```

### Test Case 3: Single Digit
```
Input: 7
Expected Output:
Original number: 7
Reversed number: 7
```

## 🔍 Explanation

1. **Input**: Accept integer from user
2. **Negative Handling**: Convert to positive for reversal
3. **Loop Logic**: Extract digits using % 10, build reversed number
4. **Reversal Process**: Multiply by 10 and add remainder each iteration
5. **Output**: Display original and reversed numbers

## 🎯 Key Concepts Covered

- Loop implementation
- Modulo operation
- Integer division
- Digit manipulation
- Input validation

## 🚀 Extensions

1. Reverse floating point numbers
2. Check if number is palindrome
3. Handle very large numbers
4. Add binary reversal