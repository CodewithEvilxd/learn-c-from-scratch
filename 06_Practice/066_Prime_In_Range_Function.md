# 🎯 Practical 66: Prime Numbers in Range Using Function

## 📋 Problem Statement

Write a C program to display prime numbers between intervals using function.

## 🎯 Learning Objectives

- Understand function implementation
- Practice prime number generation
- Learn range processing
- Understand modular programming
- Practice function calls

## 📝 Requirements

1. Accept lower and upper limits
2. Create function to check prime
3. Display all primes in range
4. Count total primes found
5. Handle edge cases

## 💡 Hints

- Create isPrime() function
- Loop through range
- Call function for each number
- Display results clearly
- Handle 1 and negative numbers

## 🔧 Solution

```c
// Practical 66: Prime Numbers in Range Using Function
// Displays prime numbers between two intervals using functions

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

// Function to display prime numbers in range
void displayPrimes(int lower, int upper) {
    int count = 0;
    printf("Prime numbers between %d and %d:\n", lower, upper);

    for (int num = lower; num <= upper; num++) {
        if (isPrime(num)) {
            printf("%d ", num);
            count++;
        }
    }

    if (count == 0) {
        printf("No prime numbers found in the given range.\n");
    } else {
        printf("\nTotal prime numbers found: %d\n", count);
    }
}

int main() {
    int lower, upper;

    printf("Prime Numbers Between Intervals\n");
    printf("================================\n");

    printf("Enter lower limit: ");
    scanf("%d", &lower);

    printf("Enter upper limit: ");
    scanf("%d", &upper);

    if (lower > upper) {
        printf("Lower limit should be less than or equal to upper limit.\n");
        return 1;
    }

    if (lower < 2) {
        printf("Note: Prime numbers start from 2. Setting lower limit to 2.\n");
        lower = 2;
    }

    displayPrimes(lower, upper);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Range
```
Input: Lower: 1, Upper: 20
Expected Output:
Prime numbers between 2 and 20:
2 3 5 7 11 13 17 19
Total prime numbers found: 8
```

### Test Case 2: Larger Range
```
Input: Lower: 10, Upper: 50
Expected Output:
Prime numbers between 10 and 50:
11 13 17 19 23 29 31 37 41 43 47
Total prime numbers found: 11
```

### Test Case 3: No Primes
```
Input: Lower: 14, Upper: 16
Expected Output:
No prime numbers found in the given range.
```

## 🔍 Explanation

1. **isPrime Function**: Checks if number is prime
2. **displayPrimes Function**: Shows primes in range
3. **Range Validation**: Ensures lower <= upper
4. **Edge Handling**: Starts from 2 for primes
5. **Count Display**: Shows total primes found

## 🎯 Key Concepts Covered

- Function implementation
- Prime number logic
- Range processing
- Modular programming
- Input validation

## 🚀 Extensions

1. Find prime factors
2. Check for twin primes
3. Generate prime table
4. Optimize for large ranges