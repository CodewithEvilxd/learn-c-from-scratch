# 🎯 Practical 74: Prime Armstrong Check with Functions

## 📋 Problem Statement

Write a C program to check prime or Armstrong number using user-defined function.

## 🎯 Learning Objectives

- Understand function implementation
- Practice modular programming
- Learn function calls
- Understand return values
- Practice code organization

## 📝 Requirements

1. Create functions for prime and Armstrong check
2. Accept number from user
3. Use functions to check both properties
4. Display results
5. Handle edge cases

## 💡 Hints

- Create isPrime() function
- Create isArmstrong() function
- Call both functions
- Display clear results
- Handle function returns

## 🔧 Solution

```c
// Practical 74: Prime Armstrong Check with Functions
// Checks if number is prime or Armstrong using functions

#include <stdio.h>
#include <math.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }
    if (num == 2) {
        return 1;
    }
    if (num % 2 == 0) {
        return 0;
    }

    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to check if a number is Armstrong
int isArmstrong(int num) {
    int original = num, sum = 0, digits = 0;

    // Count digits
    int temp = num;
    if (temp == 0) {
        digits = 1;
    } else {
        while (temp != 0) {
            digits++;
            temp /= 10;
        }
    }

    // Calculate sum of digits raised to power of digits
    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        sum += pow(remainder, digits);
        temp /= 10;
    }

    return (sum == original);
}

int main() {
    int number;

    printf("Prime and Armstrong Number Checker\n");
    printf("===================================\n");

    printf("Enter a positive integer: ");
    scanf("%d", &number);

    if (number <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    printf("Number: %d\n", number);

    // Check prime
    if (isPrime(number)) {
        printf("✓ %d is a prime number.\n", number);
    } else {
        printf("✗ %d is not a prime number.\n", number);
    }

    // Check Armstrong
    if (isArmstrong(number)) {
        printf("✓ %d is an Armstrong number.\n", number);
    } else {
        printf("✗ %d is not an Armstrong number.\n", number);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Prime Number
```
Input: 17
Expected Output:
Number: 17
✓ 17 is a prime number.
✗ 17 is not an Armstrong number.
```

### Test Case 2: Armstrong Number
```
Input: 153
Expected Output:
Number: 153
✗ 153 is not a prime number.
✓ 153 is an Armstrong number.
```

### Test Case 3: Both Prime and Armstrong
```
Input: 2
Expected Output:
Number: 2
✓ 2 is a prime number.
✗ 2 is not an Armstrong number.
```

### Test Case 4: Neither
```
Input: 10
Expected Output:
Number: 10
✗ 10 is not a prime number.
✗ 10 is not an Armstrong number.
```

## 🔍 Explanation

1. **isPrime Function**: Checks prime using loop
2. **isArmstrong Function**: Calculates Armstrong sum
3. **Main Function**: Calls both functions
4. **Display**: Clear results with checkmarks
5. **Validation**: Handle positive integers

## 🎯 Key Concepts Covered

- Function implementation
- Modular programming
- Return values
- Function calls
- Code organization

## 🚀 Extensions

1. Add more number properties
2. Create menu for different checks
3. Handle multiple numbers
4. Add function for perfect numbers