# 🎯 Practical 146: Merge Two Arrays

## 📋 Problem Statement

C Program to merge two arrays.

## 🎯 Learning Objectives

- Understand array merging
- Practice array combination
- Learn element copying
- Understand size management
- Practice multiple array handling

## 📝 Requirements

1. Accept two arrays of integers
2. Merge them into one array
3. Display original and merged arrays
4. Handle different array sizes
5. Show merging process

## 💡 Hints

- Create result array with combined size
- Copy first array elements
- Copy second array elements
- Handle size calculations
- Display clear results

## 🔧 Solution

```c
// Practical 146: Merge Two Arrays
// Demonstrates merging two arrays into one

#include <stdio.h>

#define MAX_SIZE 100

void mergeArrays(int arr1[], int n1, int arr2[], int n2, int result[]) {
    // Copy first array
    for (int i = 0; i < n1; i++) {
        result[i] = arr1[i];
    }
    
    // Copy second array
    for (int i = 0; i < n2; i++) {
        result[n1 + i] = arr2[i];
    }
}

int main() {
    int arr1[MAX_SIZE], arr2[MAX_SIZE], result[MAX_SIZE * 2];
    int n1, n2;

    printf("Merge Two Arrays\n");
    printf("=================\n");

    printf("Enter size of first array: ");
    scanf("%d", &n1);

    if (n1 <= 0 || n1 > MAX_SIZE) {
        printf("Invalid first array size!\n");
        return 1;
    }

    printf("Enter %d elements for first array: ", n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter size of second array: ");
    scanf("%d", &n2);

    if (n2 <= 0 || n2 > MAX_SIZE) {
        printf("Invalid second array size!\n");
        return 1;
    }

    printf("Enter %d elements for second array: ", n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &arr2[i]);
    }

    printf("First array: ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("Second array: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    mergeArrays(arr1, n1, arr2, n2, result);

    printf("Merged array: ");
    for (int i = 0; i < n1 + n2; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    printf("Merged array size: %d\n", n1 + n2);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Equal Size Arrays
```
Input: First: 3 elements (1 2 3), Second: 3 elements (4 5 6)
Expected Output:
First array: 1 2 3
Second array: 4 5 6
Merged array: 1 2 3 4 5 6
Merged array size: 6
```

### Test Case 2: Different Size Arrays
```
Input: First: 2 elements (10 20), Second: 4 elements (30 40 50 60)
Expected Output:
First array: 10 20
Second array: 30 40 50 60
Merged array: 10 20 30 40 50 60
Merged array size: 6
```

### Test Case 3: One Empty Array
```
Input: First: 3 elements (1 2 3), Second: 0 elements
Expected Output:
First array: 1 2 3
Second array: 
Merged array: 1 2 3
Merged array size: 3
```

## 🔍 Explanation

1. **Input Reading**: Read sizes and elements of both arrays
2. **Display Originals**: Show both input arrays
3. **Merging Process**: Copy first array, then second array
4. **Result Display**: Show merged array and size
5. **Size Management**: Handle combined array size

## 🎯 Key Concepts Covered

- Array merging
- Element copying
- Size calculation
- Multiple array handling
- Memory management

## 🚀 Extensions

1. Merge in sorted order
2. Remove duplicates during merge
3. Merge more than two arrays
4. Handle dynamic memory allocation