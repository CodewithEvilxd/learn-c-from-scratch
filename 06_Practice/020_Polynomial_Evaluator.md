# 🎯 Practical 20: Polynomial Evaluator

## 📋 Problem Statement

Write a C program to evaluate the given polynomial equation.

## 🎯 Learning Objectives

- Understand polynomial evaluation
- Practice array manipulation
- Learn Horner's method
- Understand mathematical computations
- Practice user input handling

## 📝 Requirements

1. Accept polynomial coefficients
2. Accept degree of polynomial
3. Accept value of x
4. Evaluate polynomial at x
5. Display result

## 💡 Hints

- Use array for coefficients
- Implement Horner's method for efficiency
- Handle different degrees
- Validate input
- Clear output

## 🔧 Solution

```c
// Practical 20: Polynomial Evaluator
// Evaluates polynomial at given value

#include <stdio.h>
#include <math.h>

int main() {
    int degree;
    float x, result = 0;

    printf("Polynomial Evaluator\n");
    printf("===================\n");

    printf("Enter the degree of polynomial: ");
    scanf("%d", &degree);

    if (degree < 0) {
        printf("Degree cannot be negative!\n");
        return 1;
    }

    float coefficients[degree + 1];

    printf("Enter coefficients from highest degree to constant:\n");
    for (int i = degree; i >= 0; i--) {
        printf("Coefficient of x^%d: ", i);
        scanf("%f", &coefficients[i]);
    }

    printf("Enter the value of x: ");
    scanf("%f", &x);

    // Evaluate using Horner's method
    result = coefficients[degree];
    for (int i = degree - 1; i >= 0; i--) {
        result = result * x + coefficients[i];
    }

    printf("Polynomial: ");
    for (int i = degree; i >= 0; i--) {
        if (i == 0) {
            printf("%.2f", coefficients[i]);
        } else if (i == 1) {
            printf("%.2fx + ", coefficients[i]);
        } else {
            printf("%.2fx^%d + ", coefficients[i], i);
        }
    }
    printf("\n");

    printf("At x = %.2f, result = %.2f\n", x, result);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Quadratic
```
Degree: 2
Coefficients: 1, 2, 3
x: 2
Expected Output:
Polynomial: 1.00x^2 + 2.00x + 3.00
At x = 2.00, result = 11.00
```

### Test Case 2: Linear
```
Degree: 1
Coefficients: 2, 5
x: 3
Expected Output:
Polynomial: 2.00x + 5.00
At x = 3.00, result = 11.00
```

### Test Case 3: Constant
```
Degree: 0
Coefficients: 7
x: 10
Expected Output:
Polynomial: 7.00
At x = 10.00, result = 7.00
```

## 🔍 Explanation

1. **Input**: Degree and coefficients
2. **Horner's Method**: Efficient evaluation
3. **Display**: Shows polynomial equation
4. **Result**: Computes and displays value
5. **Validation**: Checks for valid degree

## 🎯 Key Concepts Covered

- Polynomial mathematics
- Array usage
- Horner's method
- Input validation
- Mathematical computation

## 🚀 Extensions

1. Support multiple evaluations
2. Add polynomial addition
3. Support complex coefficients
4. Plot polynomial graph