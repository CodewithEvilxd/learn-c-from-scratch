# 🎯 Practical 136: Insert an Element at End of an Array

## 📋 Problem Statement

C program to insert an element at end of an Array.

## 🎯 Learning Objectives

- Understand array insertion
- Practice array modification
- Learn array bounds checking
- Understand size management
- Practice element addition

## 📝 Requirements

1. Accept array of integers
2. Accept element to insert
3. Insert at end of array
4. Display original and modified arrays
5. Handle array capacity

## 💡 Hints

- Check array capacity before insertion
- Insert at current size position
- Increment size after insertion
- Handle full array case
- Display clear results

## 🔧 Solution

```c
// Practical 136: Insert an Element at End of an Array
// Demonstrates appending an element to array end

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n, element;

    printf("Insert Element at End of Array\n");
    printf("===============================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n < 0 || n >= MAX_SIZE) {
        printf("Invalid array size! Must be between 0 and %d.\n", MAX_SIZE - 1);
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter element to insert at end: ");
    scanf("%d", &element);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Insert at end
    if (n < MAX_SIZE) {
        arr[n] = element;
        n++; // Increment size

        printf("Array after insertion: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Element %d inserted successfully at position %d\n", element, n);
    } else {
        printf("Array is full! Cannot insert element.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Insertion
```
Input: 5 elements: 1 2 3 4 5, Insert: 6
Expected Output:
Original array: 1 2 3 4 5
Array after insertion: 1 2 3 4 5 6
Element 6 inserted successfully at position 6
```

### Test Case 2: Single Element
```
Input: 1 element: 10, Insert: 20
Expected Output:
Original array: 10
Array after insertion: 10 20
Element 20 inserted successfully at position 2
```

### Test Case 3: Empty Array
```
Input: 0 elements, Insert: 5
Expected Output:
Original array: 
Array after insertion: 5
Element 5 inserted successfully at position 1
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Element Input**: Read element to insert
3. **Original Display**: Show original array
4. **Insertion**: Add element at end position
5. **Size Update**: Increment array size
6. **Result Display**: Show modified array

## 🎯 Key Concepts Covered

- Array insertion
- Size management
- Bounds checking
- Array modification
- Position tracking

## 🚀 Extensions

1. Insert at beginning
2. Insert at specific position
3. Handle dynamic arrays
4. Insert multiple elements