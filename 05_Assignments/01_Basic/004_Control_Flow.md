# 🎯 Assignment 1.4: Control Flow Statements

## 📋 Problem Statement

Create a C program that demonstrates if-else statements, switch-case, and loops. The program should act as a simple calculator with menu-driven interface.

## 🎯 Learning Objectives

- Master conditional statements (if-else, switch)
- Understand different types of loops
- Practice nested control structures
- Learn break and continue statements
- Implement menu-driven programs

## 📝 Requirements

1. Display a menu with arithmetic operations
2. Accept user choice using switch-case
3. Perform calculations based on user input
4. Handle invalid inputs gracefully
5. Allow multiple calculations in a loop
6. Exit program when user chooses to quit

## 💡 Hints

- Use `do-while` loop for menu repetition
- Implement each operation in separate functions
- Use `switch-case` for menu options
- Validate user input before calculations
- Use `break` to exit switch and loops

## 🔧 Solution

```c
// Assignment 1.4: Control Flow Statements
// Simple calculator with menu-driven interface

#include <stdio.h>
#include <stdlib.h>

void display_menu() {
    printf("\n=== Simple Calculator ===\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("6. Exit\n");
    printf("Enter your choice (1-6): ");
}

double get_number(const char* prompt) {
    double num;
    printf("%s", prompt);
    scanf("%lf", &num);
    return num;
}

void perform_addition() {
    double a = get_number("Enter first number: ");
    double b = get_number("Enter second number: ");
    printf("Result: %.2f + %.2f = %.2f\n", a, b, a + b);
}

void perform_subtraction() {
    double a = get_number("Enter first number: ");
    double b = get_number("Enter second number: ");
    printf("Result: %.2f - %.2f = %.2f\n", a, b, a - b);
}

void perform_multiplication() {
    double a = get_number("Enter first number: ");
    double b = get_number("Enter second number: ");
    printf("Result: %.2f * %.2f = %.2f\n", a, b, a * b);
}

void perform_division() {
    double a = get_number("Enter first number: ");
    double b = get_number("Enter second number: ");

    if (b == 0) {
        printf("Error: Division by zero!\n");
    } else {
        printf("Result: %.2f / %.2f = %.2f\n", a, b, a / b);
    }
}

void perform_modulus() {
    int a = (int)get_number("Enter first integer: ");
    int b = (int)get_number("Enter second integer: ");

    if (b == 0) {
        printf("Error: Modulus by zero!\n");
    } else {
        printf("Result: %d %% %d = %d\n", a, b, a % b);
    }
}

int main() {
    int choice;

    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                perform_addition();
                break;
            case 2:
                perform_subtraction();
                break;
            case 3:
                perform_multiplication();
                break;
            case 4:
                perform_division();
                break;
            case 5:
                perform_modulus();
                break;
            case 6:
                printf("Thank you for using the calculator!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }

        // Add a small delay and clear input buffer
        if (choice != 6) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n');  // Clear input buffer
            getchar();  // Wait for Enter
        }

    } while (choice != 6);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Addition Operation
```
Menu Display
Choice: 1
Input: 5.5, 3.2
Expected Output: Result: 5.50 + 3.20 = 8.70
```

### Test Case 2: Division by Zero
```
Choice: 4
Input: 10, 0
Expected Output: Error: Division by zero!
```

### Test Case 3: Invalid Choice
```
Choice: 7
Expected Output: Invalid choice! Please enter 1-6.
```

### Test Case 4: Exit Program
```
Choice: 6
Expected Output: Thank you for using the calculator!
```

## 🔍 Explanation

1. **Menu Display**: Function to show available options
2. **do-while Loop**: Repeats menu until user chooses to exit
3. **switch-case**: Handles different menu options
4. **Function Calls**: Each operation in separate function for modularity
5. **Input Validation**: Checks for division by zero
6. **Buffer Clearing**: Handles leftover input from scanf

## 🎯 Key Concepts Covered

- if-else statements (in input validation)
- switch-case statements
- do-while loops
- Function calls and modularity
- User input handling
- Error handling

## 🚀 Extensions

1. Add more mathematical operations (power, square root)
2. Implement calculator history
3. Add scientific notation support
4. Create a GUI version using ncurses