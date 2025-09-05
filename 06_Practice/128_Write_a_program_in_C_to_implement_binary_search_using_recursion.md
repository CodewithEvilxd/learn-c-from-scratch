# 🎯 Practical 128: Binary Search using Recursion

## 📋 Problem Statement

Write a C program to implement binary search algorithm using recursion.

## 🎯 Learning Objectives

- Understand recursive algorithms
- Practice binary search implementation
- Learn recursive function calls
- Understand base cases and recursive cases
- Practice array manipulation with recursion

## 📝 Requirements

1. Accept sorted array from user
2. Accept search element
3. Implement binary search recursively
4. Return index if found, -1 if not found
5. Handle edge cases (empty array, single element)
6. Display search result with position

## 💡 Hints

- Binary search works on sorted arrays
- Divide array into halves recursively
- Base case: element found or array empty
- Use low, high, mid indices
- Recursive call with updated bounds

## 🔧 Solution

```c
// Practical 128: Binary Search using Recursion
// Implements binary search algorithm recursively

#include <stdio.h>

// Recursive binary search function
int binarySearchRecursive(int arr[], int low, int high, int target) {
    // Base case: element not found
    if (low > high) {
        return -1;
    }

    // Calculate mid index
    int mid = low + (high - low) / 2;

    // Base case: element found
    if (arr[mid] == target) {
        return mid;
    }

    // Recursive case: search left half
    if (arr[mid] > target) {
        return binarySearchRecursive(arr, low, mid - 1, target);
    }

    // Recursive case: search right half
    return binarySearchRecursive(arr, mid + 1, high, target);
}

int main() {
    int n, target;

    printf("Binary Search using Recursion\n");
    printf("=============================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d sorted elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &target);

    int result = binarySearchRecursive(arr, 0, n - 1, target);

    if (result != -1) {
        printf("Element %d found at index %d (position %d)\n",
               target, result, result + 1);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Element Found in Middle
```
Input: n=5, arr=[1,3,5,7,9], target=5
Expected Output:
Element 5 found at index 2 (position 3)
```

### Test Case 2: Element Not Found
```
Input: n=5, arr=[1,3,5,7,9], target=4
Expected Output:
Element 4 not found in the array
```

### Test Case 3: Single Element Array
```
Input: n=1, arr=[5], target=5
Expected Output:
Element 5 found at index 0 (position 1)
```

## 🔍 Explanation

1. **Recursive Function**: binarySearchRecursive takes array, low, high, target
2. **Base Cases**:
   - low > high: element not found
   - arr[mid] == target: element found
3. **Recursive Cases**:
   - arr[mid] > target: search left half
   - arr[mid] < target: search right half
4. **Mid Calculation**: Uses (low + high)/2 to avoid overflow

## 🎯 Key Concepts Covered

- Recursive algorithms
- Binary search algorithm
- Array indexing
- Base cases and recursive cases
- Function parameters

## 🚀 Extensions

1. Implement iterative binary search
2. Add duplicate element handling
3. Find first/last occurrence of duplicates
4. Implement ternary search
5. Add performance comparison with linear search