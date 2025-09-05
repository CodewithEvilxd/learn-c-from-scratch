# 🎯 Practical 127: Remove Duplicate Elements from Array

## 📋 Problem Statement

Write a program in C to remove duplicate elements from array in C.

## 🎯 Learning Objectives

- Understand duplicate removal
- Practice array manipulation
- Learn in-place modification
- Understand unique element preservation
- Practice efficient algorithms

## 📝 Requirements

1. Accept array with possible duplicates
2. Remove all duplicate occurrences
3. Keep only unique elements
4. Maintain relative order
5. Display modified array

## 💡 Hints

- Use frequency array or hash set
- Track seen elements
- Create new array with unique elements
- Preserve original order
- Handle array size changes

## 🔧 Solution

```c
// Practical 127: Remove Duplicate Elements from Array
// Removes all duplicate elements, keeping only unique ones

#include <stdio.h>

int removeDuplicates(int arr[], int n) {
    int temp[1000];
    int seen[1001] = {0}; // Assuming numbers 0-1000
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] <= 1000 && seen[arr[i]] == 0) {
            temp[j++] = arr[i];
            seen[arr[i]] = 1;
        }
    }
    
    // Copy back to original array
    for (int i = 0; i < j; i++) {
        arr[i] = temp[i];
    }
    
    return j; // New size
}

int main() {
    int n;
    int arr[1000];

    printf("Remove Duplicate Elements from Array\n");
    printf("=====================================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int newSize = removeDuplicates(arr, n);

    printf("Array after removing duplicates: ");
    for (int i = 0; i < newSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("New array size: %d\n", newSize);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multiple Duplicates
```
Input: 1 2 2 3 3 3 4 5
Expected Output:
Original array: 1 2 2 3 3 3 4 5
Array after removing duplicates: 1 2 3 4 5
New array size: 5
```

### Test Case 2: No Duplicates
```
Input: 1 2 3 4 5
Expected Output:
Original array: 1 2 3 4 5
Array after removing duplicates: 1 2 3 4 5
New array size: 5
```

### Test Case 3: All Duplicates
```
Input: 1 1 1 1 1
Expected Output:
Original array: 1 1 1 1 1
Array after removing duplicates: 1
New array size: 1
```

## 🔍 Explanation

1. **Input Reading**: Read array elements from user
2. **Duplicate Removal**: Use frequency array to track seen elements
3. **Unique Storage**: Store only first occurrence of each number
4. **Array Update**: Copy unique elements back to original array
5. **Size Return**: Return new array size

## 🎯 Key Concepts Covered

- Duplicate removal
- Frequency tracking
- Array manipulation
- In-place modification
- Size management

## 🚀 Extensions

1. Remove duplicates without extra space
2. Preserve last occurrence instead of first
3. Handle negative numbers
4. Remove duplicates from sorted array