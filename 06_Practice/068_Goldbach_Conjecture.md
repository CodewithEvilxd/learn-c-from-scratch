# 🎯 Practical 68: Goldbach Conjecture Check

## 📋 Problem Statement

Write a C program to check whether a number can be expressed as sum of two prime numbers.

## 🎯 Learning Objectives

- Understand Goldbach's conjecture
- Practice prime number checking
- Learn nested loops
- Understand mathematical conjectures
- Practice function implementation

## 📝 Requirements

1. Accept an even number
2. Find two prime numbers that sum to it
3. Display the prime pairs
4. Handle odd numbers
5. Validate input

## 💡 Hints

- Goldbach conjecture: every even number > 2 is sum of two primes
- Check all pairs (i, n-i) where i is prime
- Handle 2 as special case
- Use prime checking function
- Display all possible pairs

## 🔧 Solution

```c
// Practical 68: Goldbach Conjecture Check
// Checks if a number can be expressed as sum of two primes

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

int main() {
    int number, found = 0;

    printf("Goldbach Conjecture Checker\n");
    printf("===========================\n");

    printf("Enter an even integer greater than 2: ");
    scanf("%d", &number);

    if (number <= 2) {
        printf("Number must be greater than 2.\n");
        return 1;
    }

    if (number % 2 != 0) {
        printf("Goldbach conjecture applies to even numbers only.\n");
        printf("For odd numbers, it may or may not be possible.\n");
        return 1;
    }

    printf("%d can be expressed as sum of two primes:\n", number);

    for (int i = 2; i <= number / 2; i++) {
        if (isPrime(i) && isPrime(number - i)) {
            printf("%d + %d = %d\n", i, number - i, number);
            found = 1;
        }
    }

    if (!found) {
        printf("No prime pairs found (should not happen for even numbers > 2).\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Even Number
```
Input: 10
Expected Output:
10 can be expressed as sum of two primes:
3 + 7 = 10
5 + 5 = 10
```

### Test Case 2: Larger Even Number
```
Input: 24
Expected Output:
24 can be expressed as sum of two primes:
5 + 19 = 24
7 + 17 = 24
11 + 13 = 24
```

### Test Case 3: Odd Number
```
Input: 15
Expected Output:
Goldbach conjecture applies to even numbers only.
For odd numbers, it may or may not be possible.
```

## 🔍 Explanation

1. **Goldbach Conjecture**: Every even integer > 2 is sum of two primes
2. **Prime Check**: Use isPrime function for validation
3. **Pair Finding**: Check all combinations (i, n-i)
4. **Multiple Pairs**: Display all possible combinations
5. **Validation**: Handle odd numbers and small values

## 🎯 Key Concepts Covered

- Goldbach's conjecture
- Prime number checking
- Nested loops
- Mathematical conjectures
- Function implementation

## 🚀 Extensions

1. Check Goldbach for odd numbers
2. Find all prime pairs for a range
3. Verify Goldbach up to certain limit
4. Implement optimized prime checking