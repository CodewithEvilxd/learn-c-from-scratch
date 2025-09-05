# 🎯 Practical 36: Positive Negative Checker

## 📋 Problem Statement

Write a C program to check whether a number is positive or negative.

## 🎯 Learning Objectives

- Understand number classification
- Practice conditional statements
- Learn comparison operators
- Understand zero case
- Practice input handling

## 📝 Requirements

1. Accept number input
2. Check positive/negative/zero
3. Display result
4. Handle decimal numbers
5. Clear output

## 💡 Hints

- Use if-else statements
- Check > 0, < 0, == 0
- Use float for decimals
- Clear messages
- Handle edge cases

## 🔧 Solution

```c
// Practical 36: Positive Negative Checker
// Checks if a number is positive, negative, or zero

#include <stdio.h>

int main() {
    float number;

    printf("Positive/Negative Checker\n");
    printf("=========================\n");

    printf("Enter a number: ");
    scanf("%f", &number);

    if (number > 0) {
        printf("%.2f is a positive number.\n", number);
    } else if (number < 0) {
        printf("%.2f is a negative number.\n", number);
    } else {
        printf("The number is zero.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Number
```
Input: 5.5
Expected Output:
5.50 is a positive number.
```

### Test Case 2: Negative Number
```
Input: -3.2
Expected Output:
-3.20 is a negative number.
```

### Test Case 3: Zero
```
Input: 0
Expected Output:
The number is zero.
```

## 🔍 Explanation

1. **Input**: Accepts float number
2. **Positive**: number > 0
3. **Negative**: number < 0
4. **Zero**: number == 0
5. **Output**: Clear classification

## 🎯 Key Concepts Covered

- Conditional statements
- Comparison operators
- Number classification
- Input handling
- Float precision

## 🚀 Extensions

1. Check multiple numbers
2. Add range checking
3. Handle very large numbers
4. Add absolute value