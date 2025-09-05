# 🎯 Assignment 1.3: Arithmetic Operators

## 📋 Problem Statement

Write a C program that demonstrates all arithmetic operators (+, -, *, /, %) with user input values. The program should perform calculations and display results with proper formatting.

## 🎯 Learning Objectives

- Understand arithmetic operators in C
- Practice user input with `scanf()`
- Learn operator precedence
- Handle division by zero
- Format output properly

## 📝 Requirements

1. Accept two integer inputs from user
2. Perform all arithmetic operations
3. Display results with clear labels
4. Handle division by zero gracefully
5. Show remainder for modulus operation
6. Include input validation

## 💡 Hints

- Use `scanf()` for input: `scanf("%d %d", &a, &b);`
- Check for division by zero before using `/` or `%`
- Use meaningful variable names
- Format output with descriptive text

## 🔧 Solution

```c
// Assignment 1.3: Arithmetic Operators
// This program demonstrates arithmetic operations

#include <stdio.h>

int main() {
    int num1, num2;

    // Get user input
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    // Display input values
    printf("\nInput values: %d and %d\n", num1, num2);
    printf("================================\n");

    // Addition
    printf("Addition: %d + %d = %d\n", num1, num2, num1 + num2);

    // Subtraction
    printf("Subtraction: %d - %d = %d\n", num1, num2, num1 - num2);

    // Multiplication
    printf("Multiplication: %d * %d = %d\n", num1, num2, num1 * num2);

    // Division with zero check
    if (num2 != 0) {
        printf("Division: %d / %d = %.2f\n", num1, num2, (float)num1 / num2);
        printf("Integer Division: %d / %d = %d\n", num1, num2, num1 / num2);
    } else {
        printf("Division: Cannot divide by zero!\n");
    }

    // Modulus with zero check
    if (num2 != 0) {
        printf("Modulus: %d %% %d = %d\n", num1, num2, num1 % num2);
    } else {
        printf("Modulus: Cannot perform modulus with zero!\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Operation
```
Input: 15 4
Expected Output:
Input values: 15 and 4
================================
Addition: 15 + 4 = 19
Subtraction: 15 - 4 = 11
Multiplication: 15 * 4 = 60
Division: 15 / 4 = 3.75
Integer Division: 15 / 4 = 3
Modulus: 15 % 4 = 3
```

### Test Case 2: Division by Zero
```
Input: 10 0
Expected Output:
...
Division: Cannot divide by zero!
Modulus: Cannot perform modulus with zero!
```

### Test Case 3: Negative Numbers
```
Input: -8 3
Expected Output:
...
Addition: -8 + 3 = -5
Subtraction: -8 - 3 = -11
Multiplication: -8 * 3 = -24
Division: -8 / 3 = -2.67
Integer Division: -8 / 3 = -2
Modulus: -8 % 3 = -2
```

## 🔍 Explanation

1. **Addition (+)**: Adds two numbers
2. **Subtraction (-)**: Subtracts second number from first
3. **Multiplication (*)**: Multiplies two numbers
4. **Division (/)**: Divides first number by second (floating point result)
5. **Integer Division**: Same as division but result is truncated to integer
6. **Modulus (%)**: Returns remainder of division
7. **Zero Check**: Prevents division by zero errors

## 🎯 Key Concepts Covered

- Arithmetic operators
- User input with scanf
- Type casting for floating point division
- Error handling for division by zero
- Operator precedence
- Formatted output

## 🚀 Extensions

1. Add floating point number support
2. Implement calculator with multiple operations
3. Add input validation for non-numeric input
4. Create a loop for continuous calculations