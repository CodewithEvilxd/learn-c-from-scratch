# 🎯 Practical 46: Palindrome Check

## 📋 Problem Statement

Write a C program to check whether a number is palindrome or not.

## 🎯 Learning Objectives

- Understand palindrome concept
- Practice number reversal
- Learn comparison logic
- Understand digit manipulation
- Practice input validation

## 📝 Requirements

1. Accept a number from user
2. Reverse the number
3. Compare original with reversed
4. Display result
5. Handle negative numbers

## 💡 Hints

- Use loop to reverse number
- Compare original with reversed
- Handle single digit numbers
- Negative numbers are not palindromes
- Use temporary variable

## 🔧 Solution

```c
// Practical 46: Palindrome Check
// Checks if a number is palindrome

#include <stdio.h>

int main() {
    int number, reversed = 0, remainder, original;

    printf("Palindrome Number Checker\n");
    printf("=========================\n");

    printf("Enter an integer: ");
    scanf("%d", &number);

    original = number;

    // Handle negative numbers
    if (number < 0) {
        printf("%d is not a palindrome (negative numbers cannot be palindromes).\n", original);
        return 0;
    }

    // Store original for comparison
    int temp = number;

    // Reverse the number
    while (number != 0) {
        remainder = number % 10;
        reversed = reversed * 10 + remainder;
        number /= 10;
    }

    printf("Original number: %d\n", original);
    printf("Reversed number: %d\n", reversed);

    if (original == reversed) {
        printf("%d is a palindrome number.\n", original);
    } else {
        printf("%d is not a palindrome number.\n", original);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Palindrome Number
```
Input: 121
Expected Output:
Original number: 121
Reversed number: 121
121 is a palindrome number.
```

### Test Case 2: Non-Palindrome Number
```
Input: 123
Expected Output:
Original number: 123
Reversed number: 321
123 is not a palindrome number.
```

### Test Case 3: Single Digit
```
Input: 7
Expected Output:
Original number: 7
Reversed number: 7
7 is a palindrome number.
```

### Test Case 4: Negative Number
```
Input: -121
Expected Output:
-121 is not a palindrome (negative numbers cannot be palindromes).
```

## 🔍 Explanation

1. **Input**: Accept integer from user
2. **Negative Check**: Negative numbers cannot be palindromes
3. **Reversal**: Use loop to reverse digits
4. **Comparison**: Check if original equals reversed
5. **Result**: Display palindrome status

## 🎯 Key Concepts Covered

- Number reversal
- Comparison logic
- Loop implementation
- Input validation
- Palindrome concept

## 🚀 Extensions

1. Check palindrome strings
2. Find next palindrome number
3. Check palindrome in different bases
4. Handle very large numbers