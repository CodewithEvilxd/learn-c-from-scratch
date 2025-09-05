# 🎯 Practical 34: Quadratic Roots

## 📋 Problem Statement

Write a C program to find the roots of a quadratic equation.

## 🎯 Learning Objectives

- Understand quadratic equations
- Practice discriminant calculation
- Learn complex number handling
- Understand mathematical formulas
- Practice conditional logic

## 📝 Requirements

1. Accept coefficients a, b, c
2. Calculate discriminant
3. Find real or complex roots
4. Display results
5. Handle special cases

## 💡 Hints

- Discriminant: d = b^2 - 4ac
- Real roots: d >= 0
- Complex roots: d < 0
- Use sqrt() for square root
- Handle a = 0 case

## 🔧 Solution

```c
// Practical 34: Quadratic Roots
// Finds roots of quadratic equation ax^2 + bx + c = 0

#include <stdio.h>
#include <math.h>

int main() {
    float a, b, c, discriminant, root1, root2, real_part, imag_part;

    printf("Quadratic Equation Roots Calculator\n");
    printf("===================================\n");

    printf("Enter coefficient a: ");
    scanf("%f", &a);

    printf("Enter coefficient b: ");
    scanf("%f", &b);

    printf("Enter coefficient c: ");
    scanf("%f", &c);

    if (a == 0) {
        printf("This is not a quadratic equation (a cannot be zero)!\n");
        return 1;
    }

    printf("Equation: %.1fx^2 + %.1fx + %.1f = 0\n", a, b, c);

    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Roots are real and distinct:\n");
        printf("Root 1: %.2f\n", root1);
        printf("Root 2: %.2f\n", root2);
    } else if (discriminant == 0) {
        root1 = -b / (2 * a);
        printf("Roots are real and equal:\n");
        printf("Root: %.2f\n", root1);
    } else {
        real_part = -b / (2 * a);
        imag_part = sqrt(-discriminant) / (2 * a);
        printf("Roots are complex:\n");
        printf("Root 1: %.2f + %.2fi\n", real_part, imag_part);
        printf("Root 2: %.2f - %.2fi\n", real_part, imag_part);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Real Distinct Roots
```
Input: 1, -5, 6
Expected Output:
Equation: 1.0x^2 + -5.0x + 6.0 = 0
Roots: 2.00, 3.00
```

### Test Case 2: Real Equal Roots
```
Input: 1, -4, 4
Expected Output:
Equation: 1.0x^2 + -4.0x + 4.0 = 0
Roots: 2.00, 2.00
```

### Test Case 3: Complex Roots
```
Input: 1, 2, 5
Expected Output:
Equation: 1.0x^2 + 2.0x + 5.0 = 0
Roots: -1.00 + 2.00i, -1.00 - 2.00i
```

## 🔍 Explanation

1. **Discriminant**: b^2 - 4ac
2. **Real Roots**: d > 0, use ±sqrt(d)
3. **Equal Roots**: d = 0
4. **Complex Roots**: d < 0, use imaginary unit
5. **Formula**: [-b ± sqrt(d)] / 2a

## 🎯 Key Concepts Covered

- Quadratic equations
- Discriminant
- Complex numbers
- Mathematical formulas
- Conditional logic

## 🚀 Extensions

1. Plot quadratic graph
2. Find vertex
3. Solve cubic equations
4. Add root validation