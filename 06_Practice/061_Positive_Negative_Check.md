# 🎯 Practical 61: Positive Negative Check

## 📋 Problem Statement

Write a C program to check whether a number is positive or negative.

## 🎯 Learning Objectives

- Understand number classification
- Practice conditional statements
- Learn comparison operators
- Understand zero handling
- Practice input validation

## 📝 Requirements

1. Accept a number from user
2. Check if positive, negative, or zero
3. Display appropriate message
4. Handle decimal numbers
5. Clear output

## 💡 Hints

- Use if-else statements
- Check > 0 for positive
- Check < 0 for negative
- Handle zero separately
- Use double for decimals

## 🔧 Solution

```c
// Practical 61: Positive Negative Check
// Determines if a number is positive, negative, or zero

#include <stdio.h>

int main() {
    double number;

    printf("Positive or Negative Number Check\n");
    printf("==================================\n");

    printf("Enter a number: ");
    scanf("%lf", &number);

    if (number > 0) {
        printf("%.2f is a positive number.\n", number);
    } else if (number < 0) {
        printf("%.2f is a negative number.\n", number);
    } else {
        printf("The number is zero (neither positive nor negative).\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Number
```
Input: 15.7
Expected Output:
15.70 is a positive number.
```

### Test Case 2: Negative Number
```
Input: -8.3
Expected Output:
-8.30 is a negative number.
```

### Test Case 3: Zero
```
Input: 0
Expected Output:
The number is zero (neither positive nor negative).
```

### Test Case 4: Positive Integer
```
Input: 42
Expected Output:
42.00 is a positive number.
```

## 🔍 Explanation

1. **Input**: Accept double precision number
2. **Positive Check**: number > 0
3. **Negative Check**: number < 0
4. **Zero Check**: number == 0
5. **Output**: Clear classification message

## 🎯 Key Concepts Covered

- Conditional statements
- Comparison operators
- Number classification
- Input validation
- Precision handling

## 🚀 Extensions

1. Check for even/odd as well
2. Classify multiple numbers
3. Add range checking
4. Handle very large/small numbers