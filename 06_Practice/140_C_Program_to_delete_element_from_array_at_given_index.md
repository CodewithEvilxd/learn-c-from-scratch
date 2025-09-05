# 🎯 Practical 140: Delete Element from Array at Given Index

## 📋 Problem Statement

C Program to delete element from array at given index.

## 🎯 Learning Objectives

- Understand index-based deletion
- Practice position-based removal
- Learn array shifting
- Understand bounds checking
- Practice array manipulation

## 📝 Requirements

1. Accept array of integers
2. Accept index to delete from
3. Delete element at specified index
4. Shift remaining elements left
5. Display original and modified arrays

## 💡 Hints

- Validate index bounds
- Store element to delete
- Shift elements left from index
- Decrement array size
- Handle invalid index case

## 🔧 Solution

```c
// Practical 140: Delete Element from Array at Given Index
// Demonstrates deleting element at specific index position

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n, index;

    printf("Delete Element from Array at Given Index\n");
    printf("=========================================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid array size!\n");
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter index to delete (0 to %d): ", n - 1);
    scanf("%d", &index);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Validate index
    if (index < 0 || index >= n) {
        printf("Invalid index! Must be between 0 and %d.\n", n - 1);
        return 1;
    }

    // Store element to delete
    int deletedElement = arr[index];

    // Shift elements left
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }

    n--; // Decrement size

    printf("Array after deletion: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Element %d deleted successfully from index %d\n", deletedElement, index);
    printf("New array size: %d\n", n);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Delete from Middle
```
Input: 5 elements: 1 2 3 4 5, Index: 2
Expected Output:
Original array: 1 2 3 4 5
Array after deletion: 1 2 4 5
Element 3 deleted successfully from index 2
New array size: 4
```

### Test Case 2: Delete from Beginning
```
Input: 4 elements: 10 20 30 40, Index: 0
Expected Output:
Original array: 10 20 30 40
Array after deletion: 20 30 40
Element 10 deleted successfully from index 0
New array size: 3
```

### Test Case 3: Delete from End
```
Input: 3 elements: 1 2 3, Index: 2
Expected Output:
Original array: 1 2 3
Array after deletion: 1 2
Element 3 deleted successfully from index 2
New array size: 2
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Index Input**: Read index to delete from
3. **Validation**: Check index bounds
4. **Original Display**: Show original array
5. **Deletion Process**: Store element and shift left
6. **Result Display**: Show modified array

## 🎯 Key Concepts Covered

- Index-based deletion
- Array shifting
- Bounds validation
- Size management
- Position tracking

## 🚀 Extensions

1. Delete multiple indices
2. Delete range of indices
3. Handle dynamic arrays
4. Delete by value instead of index