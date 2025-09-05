# 🎯 Practical 145: Right Rotation of Array by 2 Positions

## 📋 Problem Statement

C program to perform right rotation in array by 2 positions.

## 🎯 Learning Objectives

- Understand array rotation
- Practice element shifting
- Learn rotation algorithms
- Understand circular movement
- Practice array manipulation

## 📝 Requirements

1. Accept array of integers
2. Rotate elements right by 2 positions
3. Display original and rotated arrays
4. Handle different array sizes
5. Show rotation effect

## 💡 Hints

- Store last two elements
- Shift remaining elements right
- Place stored elements at beginning
- Handle small arrays
- Display clear results

## 🔧 Solution

```c
// Practical 145: Right Rotation of Array by 2 Positions
// Demonstrates rotating array elements to the right by 2 positions

#include <stdio.h>

#define MAX_SIZE 100

void rightRotateByTwo(int arr[], int n) {
    if (n < 2) {
        return; // Cannot rotate by 2 positions if array has less than 2 elements
    }
    
    // Store last two elements
    int last = arr[n - 1];
    int secondLast = arr[n - 2];
    
    // Shift elements to the right by 2 positions
    for (int i = n - 1; i >= 2; i--) {
        arr[i] = arr[i - 2];
    }
    
    // Place stored elements at the beginning
    arr[0] = secondLast;
    arr[1] = last;
}

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Right Rotation by Two Positions\n");
    printf("================================\n");

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

    rightRotateByTwo(arr, n);

    printf("Array after right rotation by 2 positions: ");
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
Array after right rotation by 2 positions: 5 6 1 2 3 4
```

### Test Case 2: Two Elements
```
Input: 2 elements: 10 20
Expected Output:
Original array: 10 20
Array after right rotation by 2 positions: 10 20
```

### Test Case 3: Four Elements
```
Input: 4 elements: 1 2 3 4
Expected Output:
Original array: 1 2 3 4
Array after right rotation by 2 positions: 3 4 1 2
```

### Test Case 4: Single Element
```
Input: 1 element: 5
Expected Output:
Original array: 5
Array after right rotation by 2 positions: 5
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Original Display**: Show original array
3. **Rotation Process**: Store last two, shift right, place at beginning
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
2. Left rotation instead of right
3. Rotate in place without extra space
4. Handle large arrays efficiently