# 🎯 Practical 124: Find Missing Number in Array 1-100

## 📋 Problem Statement

Write a program in C for, In array 1-100 numbers are stored, one number is missing how do you find it.

## 🎯 Learning Objectives

- Understand array processing
- Practice sum-based algorithms
- Learn mathematical approach to find missing number
- Understand expected vs actual sum
- Practice input validation

## 📝 Requirements

1. Accept array of 99 numbers (1-100 with one missing)
2. Calculate expected sum for 1-100
3. Calculate actual sum of given numbers
4. Find missing number by difference
5. Display the missing number

## 💡 Hints

- Use formula: sum = n*(n+1)/2
- Calculate expected sum for 100 numbers
- Sum the given array elements
- Missing number = expected - actual sum
- Handle input validation

## 🔧 Solution

```c
// Practical 124: Find Missing Number in Array 1-100
// Finds the missing number using sum formula

#include <stdio.h>

#define MAX_SIZE 99

int findMissingNumber(int arr[], int n) {
    // Calculate expected sum for 1 to 100
    int expected_sum = 100 * 101 / 2;
    
    // Calculate actual sum of given numbers
    int actual_sum = 0;
    for (int i = 0; i < n; i++) {
        actual_sum += arr[i];
    }
    
    // Missing number is the difference
    return expected_sum - actual_sum;
}

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Find Missing Number (1-100)\n");
    printf("============================\n");

    printf("Enter the number of elements (should be 99): ");
    scanf("%d", &n);

    if (n != 99) {
        printf("Error: Array should contain 99 elements!\n");
        return 1;
    }

    printf("Enter %d numbers (1-100, one missing): ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int missing = findMissingNumber(arr, n);

    printf("Missing number: %d\n", missing);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Missing 50
```
Input: 1 2 3 ... 49 51 52 ... 100
Expected Output:
Missing number: 50
```

### Test Case 2: Missing 1
```
Input: 2 3 4 ... 100
Expected Output:
Missing number: 1
```

### Test Case 3: Missing 100
```
Input: 1 2 3 ... 99
Expected Output:
Missing number: 100
```

## 🔍 Explanation

1. **Input Reading**: Read 99 numbers from user
2. **Expected Sum**: Calculate sum of 1 to 100 using formula
3. **Actual Sum**: Sum all elements in the array
4. **Difference**: Missing number = expected - actual
5. **Output**: Display the missing number

## 🎯 Key Concepts Covered

- Array summation
- Mathematical formulas
- Sum-based algorithms
- Input validation
- Problem-solving techniques

## 🚀 Extensions

1. Find multiple missing numbers
2. Handle unsorted arrays
3. Use XOR method
4. Find missing number in any range