# 🎯 Practical 50: Factors of a Number

## 📋 Problem Statement

Write a C program to display factors of a number.

## 🎯 Learning Objectives

- Understand factor concept
- Practice divisibility checks
- Learn loop optimization
- Understand factor pairs
- Practice input validation

## 📝 Requirements

1. Accept a number from user
2. Find all factors
3. Display factors
4. Show factor count
5. Handle edge cases

## 💡 Hints

- Check divisibility from 1 to number
- Use modulo operator
- Handle 1 and prime numbers
- Count total factors
- Display in order

## 🔧 Solution

```c
// Practical 50: Factors of a Number
// Displays all factors of a given number

#include <stdio.h>

int main() {
    int number, count = 0;

    printf("Factors of a Number\n");
    printf("===================\n");

    printf("Enter a positive integer: ");
    scanf("%d", &number);

    if (number <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    printf("Factors of %d are: ", number);

    // Find and display factors
    for (int i = 1; i <= number; i++) {
        if (number % i == 0) {
            printf("%d ", i);
            count++;
        }
    }

    printf("\nTotal number of factors: %d\n", count);

    // Check if prime
    if (count == 2) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is a composite number.\n", number);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Composite Number
```
Input: 12
Expected Output:
Factors of 12 are: 1 2 3 4 6 12
Total number of factors: 6
12 is a composite number.
```

### Test Case 2: Prime Number
```
Input: 7
Expected Output:
Factors of 7 are: 1 7
Total number of factors: 2
7 is a prime number.
```

### Test Case 3: Perfect Square
```
Input: 9
Expected Output:
Factors of 9 are: 1 3 9
Total number of factors: 3
9 is a composite number.
```

## 🔍 Explanation

1. **Input**: Accept positive integer
2. **Loop**: Check divisibility from 1 to number
3. **Factor Check**: number % i == 0
4. **Count**: Track total factors
5. **Classification**: Prime vs composite

## 🎯 Key Concepts Covered

- Factor finding
- Divisibility rules
- Loop implementation
- Prime number check
- Input validation

## 🚀 Extensions

1. Find prime factors only
2. Display factor pairs
3. Find greatest common factor
4. Check for perfect numbers