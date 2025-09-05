# 🎯 Practical 35: Leap Year Checker

## 📋 Problem Statement

Write a C program to check leap year.

## 🎯 Learning Objectives

- Understand leap year rules
- Practice conditional statements
- Learn calendar logic
- Understand modulo operations
- Practice input validation

## 📝 Requirements

1. Accept year input
2. Check leap year conditions
3. Display result
4. Handle edge cases
5. Validate input

## 💡 Hints

- Year % 4 == 0
- Year % 100 != 0 or year % 400 == 0
- Use logical operators
- Handle negative years
- Clear output

## 🔧 Solution

```c
// Practical 35: Leap Year Checker
// Checks if a year is a leap year

#include <stdio.h>

int isLeapYear(int year) {
    if (year % 4 != 0) {
        return 0;
    } else if (year % 100 != 0) {
        return 1;
    } else if (year % 400 != 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int year;

    printf("Leap Year Checker\n");
    printf("=================\n");

    printf("Enter a year: ");
    scanf("%d", &year);

    if (year <= 0) {
        printf("Please enter a valid year (positive integer)!\n");
        return 1;
    }

    if (isLeapYear(year)) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Common Leap Year
```
Input: 2024
Expected Output:
2024 is a leap year.
```

### Test Case 2: Century Year
```
Input: 1900
Expected Output:
1900 is not a leap year.
```

### Test Case 3: Century Leap Year
```
Input: 2000
Expected Output:
2000 is a leap year.
```

## 🔍 Explanation

1. **Rule 1**: Year divisible by 4
2. **Rule 2**: Not divisible by 100 unless divisible by 400
3. **Function**: isLeapYear() implements logic
4. **Validation**: Checks for positive year
5. **Output**: Clear result message

## 🎯 Key Concepts Covered

- Leap year rules
- Conditional statements
- Logical operators
- Modulo operations
- Input validation

## 🚀 Extensions

1. Check range of years
2. Display next leap year
3. Calculate days in year
4. Add calendar display