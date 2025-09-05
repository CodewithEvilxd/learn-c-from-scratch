# 🎯 Practical 143: Print All Odd Numbers in Array

## 📋 Problem Statement

C Program to print all odd numbers in array.

## 🎯 Learning Objectives

- Understand odd number identification
- Practice modulo operator usage
- Learn array filtering
- Understand conditional output
- Practice result display

## 📝 Requirements

1. Accept array of integers
2. Identify odd numbers
3. Display all odd numbers
4. Show count of odd numbers
5. Handle arrays with no odd numbers

## 💡 Hints

- Use modulo operator (%)
- Check if number % 2 != 0
- Collect odd numbers
- Display count
- Handle empty result case

## 🔧 Solution

```c
// Practical 143: Print All Odd Numbers in Array
// Demonstrates filtering and displaying odd numbers

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Print All Odd Numbers in Array\n");
    printf("===============================\n");

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

    printf("Odd numbers: ");
    int oddCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            printf("%d ", arr[i]);
            oddCount++;
        }
    }
    
    if (oddCount == 0) {
        printf("None");
    }
    
    printf("\n");
    printf("Total odd numbers: %d\n", oddCount);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Numbers
```
Input: 6 elements: 1 2 3 4 5 6
Expected Output:
Original array: 1 2 3 4 5 6
Odd numbers: 1 3 5
Total odd numbers: 3
```

### Test Case 2: All Odd
```
Input: 4 elements: 1 3 5 7
Expected Output:
Original array: 1 3 5 7
Odd numbers: 1 3 5 7
Total odd numbers: 4
```

### Test Case 3: No Odd Numbers
```
Input: 3 elements: 2 4 6
Expected Output:
Original array: 2 4 6
Odd numbers: None
Total odd numbers: 0
```

### Test Case 4: Negative Odd Numbers
```
Input: 4 elements: -1 2 -3 4
Expected Output:
Original array: -1 2 -3 4
Odd numbers: -1 -3
Total odd numbers: 2
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Original Display**: Show all elements
3. **Odd Filtering**: Check each number with modulo
4. **Display Results**: Show odd numbers and count
5. **Handle Edge Cases**: Manage no odd numbers

## 🎯 Key Concepts Covered

- Odd number identification
- Modulo operator usage
- Array filtering
- Count tracking
- Conditional output

## 🚀 Extensions

1. Print even numbers instead
2. Print numbers divisible by specific value
3. Print numbers in range
4. Sort odd numbers before printing