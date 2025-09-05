# 🎯 Practical 139: Delete Given Element from Array

## 📋 Problem Statement

C Program to delete given element from Array.

## 🎯 Learning Objectives

- Understand value-based deletion
- Practice element searching
- Learn array shifting
- Understand element removal
- Practice array manipulation

## 📝 Requirements

1. Accept array of integers
2. Accept element to delete
3. Find and delete all occurrences
4. Shift remaining elements
5. Display original and modified arrays

## 💡 Hints

- Search for element in array
- Shift elements left when found
- Handle multiple occurrences
- Update array size
- Handle element not found case

## 🔧 Solution

```c
// Practical 139: Delete Given Element from Array
// Demonstrates deleting specific element value from array

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n, element;

    printf("Delete Given Element from Array\n");
    printf("=================================\n");

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

    printf("Enter element to delete: ");
    scanf("%d", &element);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Delete all occurrences of element
    int newSize = 0;
    int deletedCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] != element) {
            arr[newSize++] = arr[i];
        } else {
            deletedCount++;
        }
    }

    if (deletedCount == 0) {
        printf("Element %d not found in array!\n", element);
    } else {
        printf("Array after deletion: ");
        for (int i = 0; i < newSize; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Element %d deleted successfully (%d occurrence(s))\n", element, deletedCount);
        printf("New array size: %d\n", newSize);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Single Occurrence
```
Input: 5 elements: 1 2 3 4 5, Delete: 3
Expected Output:
Original array: 1 2 3 4 5
Array after deletion: 1 2 4 5
Element 3 deleted successfully (1 occurrence(s))
New array size: 4
```

### Test Case 2: Multiple Occurrences
```
Input: 6 elements: 1 2 2 3 2 4, Delete: 2
Expected Output:
Original array: 1 2 2 3 2 4
Array after deletion: 1 3 4
Element 2 deleted successfully (3 occurrence(s))
New array size: 3
```

### Test Case 3: Element Not Found
```
Input: 3 elements: 1 2 3, Delete: 5
Expected Output:
Original array: 1 2 3
Element 5 not found in array!
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Element Input**: Read element to delete
3. **Original Display**: Show original array
4. **Deletion Process**: Copy non-matching elements to front
5. **Result Display**: Show modified array and statistics

## 🎯 Key Concepts Covered

- Value-based deletion
- Element searching
- Array shifting
- Size management
- Multiple occurrence handling

## 🚀 Extensions

1. Delete by index instead of value
2. Delete only first occurrence
3. Handle case-sensitive deletion
4. Delete range of elements