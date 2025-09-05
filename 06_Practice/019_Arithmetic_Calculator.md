# 🎯 Practical 19: Arithmetic Calculator

## 📋 Problem Statement

Write a C program to simulate a simple arithmetic calculator.

## 🎯 Learning Objectives

- Understand arithmetic operations
- Practice switch-case statements
- Learn input validation
- Handle division by zero
- Practice user interaction

## 📝 Requirements

1. Support +, -, *, / operations
2. Take two numbers as input
3. Display results clearly
4. Handle division by zero
5. Allow multiple calculations

## 💡 Hints

- Use switch-case for operations
- Validate operator input
- Check for division by zero
- Use float for decimal results
- Clear output formatting

## 🔧 Solution

```c
// Practical 19: Arithmetic Calculator
// Simple calculator with basic operations

#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;
    int continue_calc = 1;

    printf("Simple Arithmetic Calculator\n");
    printf("===========================\n");

    while (continue_calc) {
        printf("Enter first number: ");
        scanf("%f", &num1);

        printf("Enter operator (+, -, *, /): ");
        scanf(" %c", &operator);

        printf("Enter second number: ");
        scanf("%f", &num2);

        switch (operator) {
            case '+':
                result = num1 + num2;
                printf("%.2f + %.2f = %.2f\n", num1, num2, result);
                break;
            case '-':
                result = num1 - num2;
                printf("%.2f - %.2f = %.2f\n", num1, num2, result);
                break;
            case '*':
                result = num1 * num2;
                printf("%.2f * %.2f = %.2f\n", num1, num2, result);
                break;
            case '/':
                if (num2 == 0) {
                    printf("Error: Division by zero!\n");
                } else {
                    result = num1 / num2;
                    printf("%.2f / %.2f = %.2f\n", num1, num2, result);
                }
                break;
            default:
                printf("Error: Invalid operator!\n");
                break;
        }

        printf("Do you want to perform another calculation? (1 for Yes, 0 for No): ");
        scanf("%d", &continue_calc);
        printf("\n");
    }

    printf("Calculator closed.\n");
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Addition
```
Input: 5, +, 3
Expected Output:
5.00 + 3.00 = 8.00
```

### Test Case 2: Division
```
Input: 10, /, 2
Expected Output:
10.00 / 2.00 = 5.00
```

### Test Case 3: Division by Zero
```
Input: 5, /, 0
Expected Output:
Error: Division by zero!
```

## 🔍 Explanation

1. **Input Handling**: Takes two numbers and operator
2. **Switch Case**: Handles different operations
3. **Division Check**: Prevents division by zero
4. **Float Precision**: Uses float for decimal results
5. **Loop**: Allows multiple calculations

## 🎯 Key Concepts Covered

- Arithmetic operations
- Switch-case statements
- Input validation
- Error handling
- Loop control

## 🚀 Extensions

1. Add more operations (%, ^)
2. Support multiple operations in sequence
3. Add memory functions
4. Support complex numbers