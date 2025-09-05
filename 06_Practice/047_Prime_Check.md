# 🎯 Practical 47: Prime Number Check

## 📋 Problem Statement

Write a C program to check whether a number is prime or not.

## 🎯 Learning Objectives

- Understand prime number concept
- Practice loop implementation
- Learn optimization techniques
- Understand divisibility rules
- Practice input validation

## 📝 Requirements

1. Accept a number from user
2. Check if number is prime
3. Use efficient algorithm
4. Display result
5. Handle edge cases

## 💡 Hints

- Check divisibility from 2 to sqrt(n)
- Handle 1 and negative numbers
- 2 is the only even prime
- Use flag variable
- Optimize loop condition

## 🔧 Solution

```c
// Practical 47: Prime Number Check
// Checks if a number is prime

#include <stdio.h>
#include <math.h>

int main() {
    int number, isPrime = 1;

    printf("Prime Number Checker\n");
    printf("====================\n");

    printf("Enter a positive integer: ");
    scanf("%d", &number);

    // Handle edge cases
    if (number <= 1) {
        printf("%d is not a prime number.\n", number);
        printf("Prime numbers are greater than 1.\n");
        return 0;
    }

    if (number == 2) {
        printf("2 is a prime number.\n");
        return 0;
    }

    if (number % 2 == 0) {
        printf("%d is not a prime number (even number).\n", number);
        return 0;
    }

    // Check divisibility from 3 to sqrt(number)
    for (int i = 3; i <= sqrt(number); i += 2) {
        if (number % i == 0) {
            isPrime = 0;
            break;
        }
    }

    if (isPrime) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is not a prime number.\n", number);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Prime Number
```
Input: 17
Expected Output:
17 is a prime number.
```

### Test Case 2: Non-Prime Number
```
Input: 15
Expected Output:
15 is not a prime number.
```

### Test Case 3: Edge Case - 1
```
Input: 1
Expected Output:
1 is not a prime number.
Prime numbers are greater than 1.
```

### Test Case 4: Even Number
```
Input: 18
Expected Output:
18 is not a prime number (even number).
```

## 🔍 Explanation

1. **Edge Cases**: Handle 1, negative numbers, 2
2. **Even Check**: Quick check for even numbers > 2
3. **Loop Optimization**: Check only odd numbers up to sqrt(n)
4. **Flag Variable**: Use isPrime to track status
5. **Result**: Clear output message

## 🎯 Key Concepts Covered

- Prime number definition
- Loop optimization
- Mathematical functions (sqrt)
- Conditional logic
- Input validation

## 🚀 Extensions

1. Find all primes in a range
2. Implement Sieve of Eratosthenes
3. Check for prime factors
4. Find next prime number