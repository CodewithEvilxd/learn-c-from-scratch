# 🎯 Practical 144: Left Rotation of Array Elements by Two Positions

## 📋 Problem Statement

C program to perform left rotation of array elements by two positions.

## 🎯 Learning Objectives

- Understand array rotation
- Practice element shifting
- Learn rotation algorithms
- Understand circular movement
- Practice array manipulation

## 📝 Requirements

1. Accept array of integers
2. Rotate elements left by 2 positions
3. Display original and rotated arrays
4. Handle different array sizes
5. Show rotation effect

## 💡 Hints

- Store first two elements
- Shift remaining elements left
- Place stored elements at end
- Handle small arrays
- Display clear results

## 🔧 Solution

```c
// Practical 144: Left Rotation of Array Elements by Two Positions
// Demonstrates rotating array elements to the left by 2 positions

#include <stdio.h>

#define MAX_SIZE 100

void leftRotateByTwo(int arr[], int n) {
    if (n < 2) {
        return; // Cannot rotate by 2 positions if array has less than 2 elements
    }
    
    // Store first two elements
    int first = arr[0];
    int second = arr[1];
    
    // Shift elements to the left by 2 positions
    for (int i = 0; i < n - 2; i++) {
        arr[i] = arr[i + 2];
    }
    
    // Place stored elements at the end
    arr[n - 2] = first;
    arr[n - 1] = second;
}

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Left Rotation by Two Positions\n");
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

    leftRotateByTwo(arr, n);

    printf("Array after left rotation by 2 positions: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Rotation
```
Input: 6 elements: 1 2 3 4 5 6
Expected Output:
Original array: 1 2 3 4 5 6
Array after left rotation by 2 positions: 3 4 5 6 1 2
```

### Test Case 2: Two Elements
```
Input: 2 elements: 10 20
Expected Output:
Original array: 10 20
Array after left rotation by 2 positions: 10 20
```

### Test Case 3: Four Elements
```
Input: 4 elements: 1 2 3 4
Expected Output:
Original array: 1 2 3 4
Array after left rotation by 2 positions: 3 4 1 2
```

### Test Case 4: Single Element
```
Input: 1 element: 5
Expected Output:
Original array: 5
Array after left rotation by 2 positions: 5
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Original Display**: Show original array
3. **Rotation Process**: Store first two, shift left, place at end
4. **Result Display**: Show rotated array
5. **Edge Cases**: Handle small arrays appropriately

## 🎯 Key Concepts Covered

- Array rotation
- Element shifting
- Position manipulation
- Edge case handling
- Circular movement

## 🚀 Extensions

1. Rotate by any number of positions
2. Right rotation instead of left
3. Rotate in place without extra space
4. Handle large arrays efficiently