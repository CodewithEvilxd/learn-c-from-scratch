# 🎯 Practical 48: Armstrong Number Check

## 📋 Problem Statement

Write a C program to check Armstrong number.

## 🎯 Learning Objectives

- Understand Armstrong number concept
- Practice digit manipulation
- Learn power calculations
- Understand loop implementation
- Practice input validation

## 📝 Requirements

1. Accept a number from user
2. Calculate sum of digits raised to power of number of digits
3. Compare with original number
4. Display result
5. Handle edge cases

## 💡 Hints

- Count number of digits first
- Extract each digit
- Calculate digit^num_digits
- Sum all powered digits
- Compare with original

## 🔧 Solution

```c
// Practical 48: Armstrong Number Check
// Checks if a number is Armstrong number

#include <stdio.h>
#include <math.h>

int main() {
    int number, original, remainder, sum = 0, num_digits = 0;

    printf("Armstrong Number Checker\n");
    printf("========================\n");

    printf("Enter an integer: ");
    scanf("%d", &number);

    original = number;

    // Handle negative numbers
    if (number < 0) {
        printf("Armstrong numbers are defined for positive numbers only.\n");
        return 0;
    }

    // Count number of digits
    int temp = number;
    while (temp != 0) {
        num_digits++;
        temp /= 10;
    }

    // Handle 0 as special case
    if (number == 0) {
        num_digits = 1;
    }

    // Calculate sum of digits raised to power of num_digits
    temp = number;
    while (temp != 0) {
        remainder = temp % 10;
        sum += pow(remainder, num_digits);
        temp /= 10;
    }

    printf("Number of digits: %d\n", num_digits);
    printf("Sum of digits^%d: %d\n", num_digits, sum);

    if (sum == original) {
        printf("%d is an Armstrong number.\n", original);
    } else {
        printf("%d is not an Armstrong number.\n", original);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Armstrong Number
```
Input: 153
Expected Output:
Number of digits: 3
Sum of digits^3: 153
153 is an Armstrong number.
```

### Test Case 2: Non-Armstrong Number
```
Input: 123
Expected Output:
Number of digits: 3
Sum of digits^3: 36
123 is not an Armstrong number.
```

### Test Case 3: Single Digit
```
Input: 5
Expected Output:
Number of digits: 1
Sum of digits^1: 5
5 is an Armstrong number.
```

### Test Case 4: Zero
```
Input: 0
Expected Output:
Number of digits: 1
Sum of digits^1: 0
0 is an Armstrong number.
```

## 🔍 Explanation

1. **Digit Count**: Count total number of digits
2. **Power Calculation**: Each digit raised to power of total digits
3. **Sum**: Accumulate powered digits
4. **Comparison**: Check if sum equals original
5. **Edge Cases**: Handle 0 and negative numbers

## 🎯 Key Concepts Covered

- Digit manipulation
- Power calculations
- Loop implementation
- Armstrong number concept
- Input validation

## 🚀 Extensions

1. Find all Armstrong numbers in a range
2. Check Armstrong numbers in different bases
3. Find next Armstrong number
4. Handle very large numbers