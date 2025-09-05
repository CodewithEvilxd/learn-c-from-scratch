# 🎯 Practical 49: Armstrong Numbers in Range

## 📋 Problem Statement

Write a C program to display Armstrong numbers between two intervals.

## 🎯 Learning Objectives

- Understand range processing
- Practice Armstrong number logic
- Learn nested loops
- Understand interval handling
- Practice output formatting

## 📝 Requirements

1. Accept lower and upper limits
2. Check each number in range
3. Display all Armstrong numbers found
4. Handle invalid ranges
5. Show count of Armstrong numbers

## 💡 Hints

- Use nested loops for digit processing
- Reuse Armstrong checking logic
- Validate lower < upper
- Handle large ranges efficiently
- Display results clearly

## 🔧 Solution

```c
// Practical 49: Armstrong Numbers in Range
// Displays Armstrong numbers between two intervals

#include <stdio.h>
#include <math.h>

int main() {
    int lower, upper, count = 0;

    printf("Armstrong Numbers Between Two Intervals\n");
    printf("========================================\n");

    printf("Enter lower limit: ");
    scanf("%d", &lower);

    printf("Enter upper limit: ");
    scanf("%d", &upper);

    if (lower > upper) {
        printf("Lower limit should be less than upper limit.\n");
        return 1;
    }

    if (lower < 0) {
        printf("Armstrong numbers are defined for positive numbers. Setting lower limit to 0.\n");
        lower = 0;
    }

    printf("Armstrong numbers between %d and %d:\n", lower, upper);

    // Check each number in the range
    for (int number = lower; number <= upper; number++) {
        int original = number, sum = 0, num_digits = 0;

        // Count digits
        int temp = number;
        if (temp == 0) {
            num_digits = 1;
        } else {
            while (temp != 0) {
                num_digits++;
                temp /= 10;
            }
        }

        // Calculate sum of digits raised to power of num_digits
        temp = number;
        while (temp != 0) {
            int remainder = temp % 10;
            sum += pow(remainder, num_digits);
            temp /= 10;
        }

        // Check if Armstrong number
        if (sum == original) {
            printf("%d ", original);
            count++;
        }
    }

    if (count == 0) {
        printf("No Armstrong numbers found in the given range.\n");
    } else {
        printf("\nTotal Armstrong numbers found: %d\n", count);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Range
```
Input: Lower: 1, Upper: 200
Expected Output:
Armstrong numbers between 1 and 200:
1 2 3 4 5 6 7 8 9 153
Total Armstrong numbers found: 10
```

### Test Case 2: Larger Range
```
Input: Lower: 100, Upper: 1000
Expected Output:
Armstrong numbers between 100 and 1000:
153 370 371 407
Total Armstrong numbers found: 4
```

### Test Case 3: No Armstrong Numbers
```
Input: Lower: 200, Upper: 300
Expected Output:
No Armstrong numbers found in the given range.
```

## 🔍 Explanation

1. **Range Input**: Accept lower and upper limits
2. **Validation**: Check lower < upper, handle negative lower
3. **Loop**: Check each number in range
4. **Armstrong Check**: Count digits and calculate sum
5. **Display**: Show found numbers and count

## 🎯 Key Concepts Covered

- Range processing
- Armstrong number logic
- Loop implementation
- Input validation
- Result formatting

## 🚀 Extensions

1. Find Armstrong numbers with specific digit count
2. Optimize for large ranges
3. Save results to file
4. Find Armstrong numbers in different bases