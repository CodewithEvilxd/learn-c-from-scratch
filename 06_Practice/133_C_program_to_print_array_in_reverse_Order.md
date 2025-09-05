# 🎯 Practical 133: Print Array in Reverse Order

## 📋 Problem Statement

C program to print array in reverse Order.

## 🎯 Learning Objectives

- Understand array printing
- Practice reverse iteration
- Learn array indexing
- Understand loop control
- Practice output formatting

## 📝 Requirements

1. Accept array of integers
2. Print elements in reverse order
3. Display original and reversed arrays
4. Handle different array sizes
5. Show clear output

## 💡 Hints

- Use loop from last to first index
- Access elements using arr[n-i-1]
- Display both original and reversed
- Handle empty arrays
- Format output clearly

## 🔧 Solution

```c
// Practical 133: Print Array in Reverse Order
// Prints array elements in reverse order

#include <stdio.h>

void printArrayReverse(int arr[], int n) {
    printf("Array in reverse order: ");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    int arr[1000];

    printf("Print Array in Reverse Order\n");
    printf("=============================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array must have at least one element!\n");
        return 1;
    }

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printArrayReverse(arr, n);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Array
```
Input: 5, 1 2 3 4 5
Expected Output:
Original array: 1 2 3 4 5
Array in reverse order: 5 4 3 2 1
```

### Test Case 2: Single Element
```
Input: 1, 42
Expected Output:
Original array: 42
Array in reverse order: 42
```

### Test Case 3: Even Number of Elements
```
Input: 4, 10 20 30 40
Expected Output:
Original array: 10 20 30 40
Array in reverse order: 40 30 20 10
```

### Test Case 4: Negative Numbers
```
Input: 3, -1 -2 -3
Expected Output:
Original array: -1 -2 -3
Array in reverse order: -3 -2 -1
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Original Display**: Print array in original order
3. **Reverse Printing**: Loop from last to first index
4. **Output**: Display reversed array
5. **Formatting**: Clear output with labels

## 🎯 Key Concepts Covered

- Array traversal
- Reverse iteration
- Loop control
- Output formatting
- Index manipulation

## 🚀 Extensions

1. Reverse array in place
2. Print every other element in reverse
3. Reverse only part of array
4. Handle different data types