# 🎯 Practical 138: Delete Element at End of Array

## 📋 Problem Statement

C Program to delete element at end of Array.

## 🎯 Learning Objectives

- Understand array deletion
- Practice end element removal
- Learn size management
- Understand array bounds
- Practice element removal

## 📝 Requirements

1. Accept array of integers
2. Delete last element
3. Display original and modified arrays
4. Handle empty array case
5. Update array size

## 💡 Hints

- Check if array is empty
- Simply decrement size
- No element shifting needed
- Handle edge cases
- Display clear results

## 🔧 Solution

```c
// Practical 138: Delete Element at End of Array
// Demonstrates removing the last element from array

#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Delete Element at End of Array\n");
    printf("===============================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array is empty! No element to delete.\n");
        return 1;
    }

    if (n > MAX_SIZE) {
        printf("Array size exceeds maximum limit!\n");
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

    // Delete last element by decrementing size
    int deletedElement = arr[n - 1];
    n--; // Decrement size

    printf("Array after deletion: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Element %d deleted successfully from end\n", deletedElement);
    printf("New array size: %d\n", n);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Deletion
```
Input: 5 elements: 1 2 3 4 5
Expected Output:
Original array: 1 2 3 4 5
Array after deletion: 1 2 3 4
Element 5 deleted successfully from end
New array size: 4
```

### Test Case 2: Two Elements
```
Input: 2 elements: 10 20
Expected Output:
Original array: 10 20
Array after deletion: 10
Element 20 deleted successfully from end
New array size: 1
```

### Test Case 3: Single Element
```
Input: 1 element: 42
Expected Output:
Original array: 42
Array after deletion: 
Element 42 deleted successfully from end
New array size: 0
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Original Display**: Show original array
3. **Deletion**: Store last element and decrement size
4. **Result Display**: Show modified array
5. **Confirmation**: Display deleted element and new size

## 🎯 Key Concepts Covered

- Array deletion
- Size management
- End element removal
- Bounds checking
- Array modification

## 🚀 Extensions

1. Delete from beginning
2. Delete from specific position
3. Delete multiple elements
4. Handle dynamic arrays