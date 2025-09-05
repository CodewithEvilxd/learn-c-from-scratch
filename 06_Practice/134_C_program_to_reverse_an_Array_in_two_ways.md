# 🎯 Practical 134: Reverse an Array in Two Ways

## 📋 Problem Statement

C program to reverse an Array in two ways.

## 🎯 Learning Objectives

- Understand array reversal
- Practice iterative approach
- Learn recursive approach
- Understand in-place modification
- Practice algorithm comparison

## 📝 Requirements

1. Accept array of integers
2. Implement two reversal methods
3. Show iterative and recursive approaches
4. Display original and reversed arrays
5. Compare both methods

## 💡 Hints

- Method 1: Use two pointers (iterative)
- Method 2: Use recursion
- Swap elements from ends
- Handle base cases in recursion
- Show both implementations

## 🔧 Solution

```c
// Practical 134: Reverse an Array in Two Ways
// Demonstrates iterative and recursive array reversal

#include <stdio.h>

// Method 1: Iterative approach using two pointers
void reverseIterative(int arr[], int start, int end) {
    while (start < end) {
        // Swap elements
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        start++;
        end--;
    }
}

// Method 2: Recursive approach
void reverseRecursive(int arr[], int start, int end) {
    if (start >= end) {
        return; // Base case
    }
    
    // Swap elements
    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
    
    // Recursive call
    reverseRecursive(arr, start + 1, end - 1);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    int arr1[1000], arr2[1000];

    printf("Reverse Array in Two Ways\n");
    printf("==========================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array must have at least one element!\n");
        return 1;
    }

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
        arr2[i] = arr1[i]; // Copy for second method
    }

    printf("Original array: ");
    printArray(arr1, n);

    // Method 1: Iterative
    printf("\nMethod 1 (Iterative): ");
    reverseIterative(arr1, 0, n - 1);
    printArray(arr1, n);

    // Method 2: Recursive
    printf("Method 2 (Recursive): ");
    reverseRecursive(arr2, 0, n - 1);
    printArray(arr2, n);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Array
```
Input: 5, 1 2 3 4 5
Expected Output:
Original array: 1 2 3 4 5
Method 1 (Iterative): 5 4 3 2 1
Method 2 (Recursive): 5 4 3 2 1
```

### Test Case 2: Even Elements
```
Input: 4, 10 20 30 40
Expected Output:
Original array: 10 20 30 40
Method 1 (Iterative): 40 30 20 10
Method 2 (Recursive): 40 30 20 10
```

### Test Case 3: Single Element
```
Input: 1, 42
Expected Output:
Original array: 42
Method 1 (Iterative): 42
Method 2 (Recursive): 42
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Method 1**: Iterative two-pointer approach
3. **Method 2**: Recursive swapping approach
4. **Comparison**: Both produce same result
5. **Output**: Display results from both methods

## 🎯 Key Concepts Covered

- Array reversal algorithms
- Iterative vs recursive approaches
- Two-pointer technique
- In-place modification
- Recursion base cases

## 🚀 Extensions

1. Reverse only part of array
2. Reverse using extra space
3. Compare time complexity
4. Handle different data types