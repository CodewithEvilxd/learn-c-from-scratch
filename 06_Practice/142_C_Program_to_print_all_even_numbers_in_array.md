# 🎯 Practical 142: Print All Even Numbers in Array

## 📋 Problem Statement

C Program to print all even numbers in array.

## 🎯 Learning Objectives

- Understand even number identification
- Practice modulo operator usage
- Learn array filtering
- Understand conditional output
- Practice result display

## 📝 Requirements

1. Accept array of integers
2. Identify even numbers
3. Display all even numbers
4. Show count of even numbers
5. Handle arrays with no even numbers

## 💡 Hints

- Use modulo operator (%)
- Check if number % 2 == 0
- Collect even numbers
- Display count
- Handle empty result case

## 🔧 Solution

```c
// Practical 142: Print All Even Numbers in Array
// Demonstrates filtering and displaying even numbers

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Print All Even Numbers in Array\n");
    printf("=================================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid array size! Must be between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Even numbers: ");
    int evenCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            printf("%d ", arr[i]);
            evenCount++;
        }
    }
    
    if (evenCount == 0) {
        printf("None");
    }
    
    printf("\n");
    printf("Total even numbers: %d\n", evenCount);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Numbers
```
Input: 6 elements: 1 2 3 4 5 6
Expected Output:
Original array: 1 2 3 4 5 6
Even numbers: 2 4 6
Total even numbers: 3
```

### Test Case 2: All Even
```
Input: 4 elements: 2 4 6 8
Expected Output:
Original array: 2 4 6 8
Even numbers: 2 4 6 8
Total even numbers: 4
```

### Test Case 3: No Even Numbers
```
Input: 3 elements: 1 3 5
Expected Output:
Original array: 1 3 5
Even numbers: None
Total even numbers: 0
```

### Test Case 4: Negative Even Numbers
```
Input: 4 elements: -2 3 -4 5
Expected Output:
Original array: -2 3 -4 5
Even numbers: -2 -4
Total even numbers: 2
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Original Display**: Show all elements
3. **Even Filtering**: Check each number with modulo
4. **Display Results**: Show even numbers and count
5. **Handle Edge Cases**: Manage no even numbers

## 🎯 Key Concepts Covered

- Even number identification
- Modulo operator usage
- Array filtering
- Count tracking
- Conditional output

## 🚀 Extensions

1. Print odd numbers instead
2. Print numbers divisible by specific value
3. Print numbers in range
4. Sort even numbers before printing