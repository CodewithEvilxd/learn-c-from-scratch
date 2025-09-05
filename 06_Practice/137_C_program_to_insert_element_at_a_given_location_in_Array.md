# 🎯 Practical 137: Insert Element at a Given Location in Array

## 📋 Problem Statement

C program to insert element at a given location in Array.

## 🎯 Learning Objectives

- Understand array insertion at position
- Practice element shifting
- Learn position-based insertion
- Understand array bounds checking
- Practice array manipulation

## 📝 Requirements

1. Accept array of integers
2. Accept element and position to insert
3. Insert at specified position
4. Shift existing elements
5. Display original and modified arrays

## 💡 Hints

- Validate position bounds
- Shift elements from end to position
- Insert element at position
- Handle invalid positions
- Update array size

## 🔧 Solution

```c
// Practical 137: Insert Element at a Given Location in Array
// Demonstrates inserting element at specific position

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n, element, position;

    printf("Insert Element at Given Location\n");
    printf("=================================\n");

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

    printf("Enter element to insert: ");
    scanf("%d", &element);

    printf("Enter position to insert (1 to %d): ", n + 1);
    scanf("%d", &position);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Validate position
    if (position < 1 || position > n + 1) {
        printf("Invalid position! Must be between 1 and %d.\n", n + 1);
        return 1;
    }

    // Check if array has space
    if (n >= MAX_SIZE) {
        printf("Array is full! Cannot insert element.\n");
        return 1;
    }

    // Shift elements to right
    for (int i = n; i >= position; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert element at position
    arr[position - 1] = element;
    n++; // Increment size

    printf("Array after insertion: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Element %d inserted successfully at position %d\n", element, position);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Insert in Middle
```
Input: 5 elements: 1 2 3 4 5, Element: 99, Position: 3
Expected Output:
Original array: 1 2 3 4 5
Array after insertion: 1 2 99 3 4 5
Element 99 inserted successfully at position 3
```

### Test Case 2: Insert at Beginning
```
Input: 3 elements: 10 20 30, Element: 5, Position: 1
Expected Output:
Original array: 10 20 30
Array after insertion: 5 10 20 30
Element 5 inserted successfully at position 1
```

### Test Case 3: Insert at End
```
Input: 2 elements: 1 2, Element: 3, Position: 3
Expected Output:
Original array: 1 2
Array after insertion: 1 2 3
Element 3 inserted successfully at position 3
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Element and Position**: Read element and insertion position
3. **Validation**: Check position bounds and array capacity
4. **Element Shifting**: Move elements to right from insertion point
5. **Insertion**: Place element at specified position
6. **Size Update**: Increment array size

## 🎯 Key Concepts Covered

- Position-based insertion
- Element shifting
- Bounds validation
- Array manipulation
- Size management

## 🚀 Extensions

1. Insert multiple elements
2. Handle dynamic arrays
3. Insert in sorted array
4. Error handling for invalid positions