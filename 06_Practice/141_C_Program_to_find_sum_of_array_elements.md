# 🎯 Practical 141: Find Sum of Array Elements

## 📋 Problem Statement

C Program to find sum of array elements.

## 🎯 Learning Objectives

- Understand array summation
- Practice loop-based accumulation
- Learn sum calculation
- Understand data types for sum
- Practice result display

## 📝 Requirements

1. Accept array of integers
2. Calculate sum of all elements
3. Display array and sum
4. Handle different array sizes
5. Show clear output

## 💡 Hints

- Initialize sum to zero
- Loop through all elements
- Add each element to sum
- Handle large numbers
- Display clear results

## 🔧 Solution

```c
// Practical 141: Find Sum of Array Elements
// Demonstrates calculating sum of all array elements

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n;
    long long sum = 0; // Use long long to handle large sums

    printf("Find Sum of Array Elements\n");
    printf("===========================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid array size! Must be between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i]; // Accumulate sum
    }

    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Sum of all elements: %lld\n", sum);

    // Calculate and display average
    double average = (double)sum / n;
    printf("Average of elements: %.2f\n", average);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Numbers
```
Input: 5 elements: 1 2 3 4 5
Expected Output:
Array elements: 1 2 3 4 5
Sum of all elements: 15
Average of elements: 3.00
```

### Test Case 2: Mixed Numbers
```
Input: 4 elements: -1 5 -3 10
Expected Output:
Array elements: -1 5 -3 10
Sum of all elements: 11
Average of elements: 2.75
```

### Test Case 3: Single Element
```
Input: 1 element: 42
Expected Output:
Array elements: 42
Sum of all elements: 42
Average of elements: 42.00
```

### Test Case 4: Large Numbers
```
Input: 3 elements: 100000 200000 300000
Expected Output:
Array elements: 100000 200000 300000
Sum of all elements: 600000
Average of elements: 200000.00
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Sum Calculation**: Accumulate sum during input
3. **Display Array**: Show all elements
4. **Display Sum**: Show total sum
5. **Display Average**: Calculate and show average

## 🎯 Key Concepts Covered

- Array summation
- Loop accumulation
- Data type selection
- Average calculation
- Result formatting

## 🚀 Extensions

1. Find sum of even/odd elements
2. Find sum within range
3. Handle floating point arrays
4. Find running sum