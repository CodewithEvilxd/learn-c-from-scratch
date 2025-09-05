# 🎯 Practical 22: Complex Number Calculator

## 📋 Problem Statement

Write a C program to add two complex numbers.

## 🎯 Learning Objectives

- Understand structures in C
- Practice complex number operations
- Learn user-defined data types
- Understand mathematical operations
- Practice function implementation

## 📝 Requirements

1. Define complex number structure
2. Accept two complex numbers
3. Perform addition
4. Display result
5. Handle input validation

## 💡 Hints

- Use struct for complex numbers
- Separate real and imaginary parts
- Implement addition function
- Format output properly
- Handle negative imaginary parts

## 🔧 Solution

```c
// Practical 22: Complex Number Calculator
// Performs operations on complex numbers

#include <stdio.h>

// Structure for complex number
typedef struct {
    float real;
    float imag;
} Complex;

Complex addComplex(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

Complex multiplyComplex(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

void displayComplex(Complex c) {
    if (c.imag >= 0) {
        printf("%.2f + %.2fi", c.real, c.imag);
    } else {
        printf("%.2f - %.2fi", c.real, -c.imag);
    }
}

int main() {
    Complex num1, num2, sum, product;

    printf("Complex Number Calculator\n");
    printf("=========================\n");

    printf("Enter first complex number:\n");
    printf("Real part: ");
    scanf("%f", &num1.real);
    printf("Imaginary part: ");
    scanf("%f", &num1.imag);

    printf("Enter second complex number:\n");
    printf("Real part: ");
    scanf("%f", &num2.real);
    printf("Imaginary part: ");
    scanf("%f", &num2.imag);

    sum = addComplex(num1, num2);
    product = multiplyComplex(num1, num2);

    printf("\nFirst number: ");
    displayComplex(num1);
    printf("\nSecond number: ");
    displayComplex(num2);

    printf("\n\nSum: ");
    displayComplex(sum);

    printf("\nProduct: ");
    displayComplex(product);
    printf("\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Imaginary
```
Input: (3, 4), (1, 2)
Expected Output:
Sum: 4.00 + 6.00i
Product: 3.00 + 10.00i
```

### Test Case 2: Negative Imaginary
```
Input: (5, -2), (2, 3)
Expected Output:
Sum: 7.00 + 1.00i
Product: 16.00 + 11.00i
```

### Test Case 3: Zero Imaginary
```
Input: (4, 0), (3, 5)
Expected Output:
Sum: 7.00 + 5.00i
Product: 12.00 + 20.00i
```

## 🔍 Explanation

1. **Structure**: Complex with real and imag
2. **Addition**: Add real and imag separately
3. **Multiplication**: (a+bi)(c+di) = ac + adi + bci + bdi^2
4. **Display**: Handle negative imaginary
5. **Functions**: Modular design

## 🎯 Key Concepts Covered

- Structures
- User-defined types
- Complex number mathematics
- Function implementation
- Formatted output

## 🚀 Extensions

1. Add subtraction and division
2. Calculate magnitude and argument
3. Support complex conjugate
4. Add more operations