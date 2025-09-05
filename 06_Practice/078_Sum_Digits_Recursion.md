# 🎯 Practical 78: Sum of Digits Using Recursion

## 📋 Problem Statement

Write a C program to find the sum of digits of a number using recursion.

## 🎯 Learning Objectives

- Understand recursive digit processing
- Practice recursive functions
- Learn digit extraction
- Understand base cases
- Practice mathematical recursion

## 📝 Requirements

1. Accept a number
2. Calculate sum of digits recursively
3. Display the result
4. Handle negative numbers
5. Show digit extraction process

## 💡 Hints

- Base case: number == 0 return 0
- Recursive case: (number % 10) + sumDigits(number / 10)
- Handle negative numbers
- Show individual digits
- Use proper base cases

## 🔧 Solution

```c
// Practical 78: Sum of Digits Using Recursion
// Calculates sum of digits recursively

#include <stdio.h>

// Recursive function to calculate sum of digits
int sumOfDigits(int number) {
    // Base case
    if (number == 0) {
        return 0;
    }

    // Handle negative numbers
    if (number < 0) {
        return sumOfDigits(-number);
    }

    // Recursive case: last digit + sum of remaining digits
    return (number % 10) + sumOfDigits(number / 10);
}

int main() {
    int number, result;

    printf("Sum of Digits Calculator (Recursive)\n");
    printf("====================================\n");

    printf("Enter a number: ");
    scanf("%d", &number);

    result = sumOfDigits(number);

    printf("Sum of digits of %d is: %d\n", number, result);

    // Show the digit extraction process
    if (number != 0) {
        printf("\nDigit extraction process:\n");
        int temp = (number < 0) ? -number : number;
        printf("%d", temp);
        while (temp > 0) {
            printf(" -> %d + %d", temp % 10, temp / 10);
            temp /= 10;
            if (temp > 0) {
                printf(" -> ...");
                break;
            }
        }
        printf(" = %d\n", result);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multi-digit Number
```
Input: 12345
Expected Output:
Sum of digits of 12345 is: 15
Digit extraction process:
12345 -> 5 + 1234 -> 4 + 123 -> 3 + 12 -> 2 + 1 -> 1 + 0 = 15
```

### Test Case 2: Single Digit
```
Input: 7
Expected Output:
Sum of digits of 7 is: 7
```

### Test Case 3: Zero
```
Input: 0
Expected Output:
Sum of digits of 0 is: 0
```

### Test Case 4: Negative Number
```
Input: -456
Expected Output:
Sum of digits of -456 is: 15
```

## 🔍 Explanation

1. **Base Case**: number == 0 returns 0
2. **Negative Handling**: Convert to positive
3. **Recursive Case**: (number % 10) + sumOfDigits(number / 10)
4. **Digit Extraction**: number % 10 gets last digit
5. **Process Display**: Show step-by-step extraction

## 🎯 Key Concepts Covered

- Recursive functions
- Digit manipulation
- Base cases
- Mathematical recursion
- Process visualization

## 🚀 Extensions

1. Find product of digits recursively
2. Reverse digits recursively
3. Count digits recursively
4. Find largest digit recursively