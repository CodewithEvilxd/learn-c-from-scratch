# 🎯 Practical 57: Simple Calculator

## 📋 Problem Statement

Write a C program to make a simple calculator using switch...case.

## 🎯 Learning Objectives

- Understand switch-case statements
- Practice arithmetic operations
- Learn menu-driven programs
- Understand operator handling
- Practice input validation

## 📝 Requirements

1. Display menu of operations
2. Accept two numbers and operator
3. Use switch-case for operations
4. Display result
5. Handle invalid operators

## 💡 Hints

- Use switch-case for operator selection
- Handle +, -, *, / operations
- Check for division by zero
- Use float for decimal results
- Clear menu display

## 🔧 Solution

```c
// Practical 57: Simple Calculator
// Calculator using switch-case statements

#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;

    printf("Simple Calculator\n");
    printf("=================\n");
    printf("Operations: +, -, *, /\n\n");

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
            printf("Valid operators are: +, -, *, /\n");
            break;
    }

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

### Test Case 4: Invalid Operator
```
Input: 5, %, 3
Expected Output:
Error: Invalid operator!
Valid operators are: +, -, *, /
```

## 🔍 Explanation

1. **Input**: Two numbers and operator
2. **Switch-Case**: Handle different operators
3. **Operations**: +, -, *, / with proper calculations
4. **Error Handling**: Division by zero and invalid operators
5. **Output**: Formatted results

## 🎯 Key Concepts Covered

- Switch-case statements
- Arithmetic operations
- Input validation
- Error handling
- Operator handling

## 🚀 Extensions

1. Add more operations (%, ^)
2. Support multiple calculations
3. Add memory functions
4. Support complex numbers