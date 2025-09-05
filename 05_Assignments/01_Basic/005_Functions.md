# 🎯 Assignment 1.5: Functions in C

## 📋 Problem Statement

Write a C program that implements various mathematical functions and demonstrates function calls, parameters, and return values. Create functions for factorial, fibonacci, prime checking, and basic calculator operations.

## 🎯 Learning Objectives

- Understand function declaration and definition
- Learn parameter passing and return values
- Practice function prototypes
- Understand local vs global variables
- Implement recursive functions

## 📝 Requirements

1. Implement factorial function (recursive)
2. Implement fibonacci function (recursive)
3. Create prime number checker
4. Build calculator functions (add, subtract, multiply, divide)
5. Create a menu-driven interface
6. Handle errors appropriately

## 💡 Hints

- Declare function prototypes at the top
- Use `long long` for factorial to handle larger numbers
- Implement base cases for recursive functions
- Check for division by zero in calculator functions
- Use meaningful function and parameter names

## 🔧 Solution

```c
// Assignment 1.5: Functions in C
// Mathematical functions and calculator

#include <stdio.h>
#include <stdbool.h>

// Function prototypes
long long factorial(int n);
long long fibonacci(int n);
bool is_prime(int n);
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

void display_menu();
void perform_calculation(int choice);

int main() {
    int choice;

    do {
        display_menu();
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            perform_calculation(choice);
        } else if (choice == 5) {
            printf("Thank you for using the program!\n");
        } else {
            printf("Invalid choice! Please enter 1-5.\n");
        }

    } while (choice != 5);

    return 0;
}

void display_menu() {
    printf("\n=== Mathematical Functions Calculator ===\n");
    printf("1. Factorial\n");
    printf("2. Fibonacci\n");
    printf("3. Prime Check\n");
    printf("4. Basic Calculator\n");
    printf("5. Exit\n");
    printf("Enter your choice (1-5): ");
}

void perform_calculation(int choice) {
    int num;
    double a, b, result;

    switch (choice) {
        case 1:  // Factorial
            printf("Enter a number: ");
            scanf("%d", &num);
            if (num < 0) {
                printf("Error: Factorial of negative number is undefined!\n");
            } else {
                printf("Factorial of %d is %lld\n", num, factorial(num));
            }
            break;

        case 2:  // Fibonacci
            printf("Enter a number: ");
            scanf("%d", &num);
            if (num < 0) {
                printf("Error: Fibonacci of negative number is undefined!\n");
            } else {
                printf("Fibonacci of %d is %lld\n", num, fibonacci(num));
            }
            break;

        case 3:  // Prime Check
            printf("Enter a number: ");
            scanf("%d", &num);
            if (is_prime(num)) {
                printf("%d is a prime number\n", num);
            } else {
                printf("%d is not a prime number\n", num);
            }
            break;

        case 4:  // Basic Calculator
            printf("Enter first number: ");
            scanf("%lf", &a);
            printf("Enter second number: ");
            scanf("%lf", &b);

            printf("Addition: %.2f + %.2f = %.2f\n", a, b, add(a, b));
            printf("Subtraction: %.2f - %.2f = %.2f\n", a, b, subtract(a, b));
            printf("Multiplication: %.2f * %.2f = %.2f\n", a, b, multiply(a, b));

            if (b != 0) {
                printf("Division: %.2f / %.2f = %.2f\n", a, b, divide(a, b));
            } else {
                printf("Division: Cannot divide by zero!\n");
            }
            break;
    }
}

// Recursive factorial function
long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;  // Base case
    }
    return n * factorial(n - 1);  // Recursive case
}

// Recursive fibonacci function
long long fibonacci(int n) {
    if (n == 0) {
        return 0;  // Base case
    }
    if (n == 1) {
        return 1;  // Base case
    }
    return fibonacci(n - 1) + fibonacci(n - 2);  // Recursive case
}

// Prime number checker
bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

// Calculator functions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}
```

## 📊 Test Cases

### Test Case 1: Factorial
```
Input: 5
Expected Output: Factorial of 5 is 120
```

### Test Case 2: Fibonacci
```
Input: 8
Expected Output: Fibonacci of 8 is 21
```

### Test Case 3: Prime Check
```
Input: 17
Expected Output: 17 is a prime number
```

### Test Case 4: Calculator
```
Input: 10, 3
Expected Output:
Addition: 10.00 + 3.00 = 13.00
Subtraction: 10.00 - 3.00 = 7.00
Multiplication: 10.00 * 3.00 = 30.00
Division: 10.00 / 3.00 = 3.33
```

## 🔍 Explanation

1. **Function Prototypes**: Declared at top for compiler
2. **Recursive Functions**: factorial() and fibonacci() call themselves
3. **Base Cases**: Stop recursion to prevent infinite loops
4. **Parameter Passing**: Values passed to functions
5. **Return Values**: Functions return calculated results
6. **Error Handling**: Check for invalid inputs

## 🎯 Key Concepts Covered

- Function declaration and definition
- Recursive functions
- Parameter passing
- Return values
- Function prototypes
- Local and global scope

## 🚀 Extensions

1. Add more mathematical functions (power, square root)
2. Implement iterative versions of recursive functions
3. Add function to calculate series (sum, product)
4. Create a scientific calculator with trigonometric functions