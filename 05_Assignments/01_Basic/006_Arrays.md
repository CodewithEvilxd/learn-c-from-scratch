# 🎯 Assignment 1.6: Arrays in C

## 📋 Problem Statement

Create a C program that demonstrates array operations including initialization, traversal, searching, sorting, and multi-dimensional arrays. Implement functions to find maximum, minimum, sum, and average of array elements.

## 🎯 Learning Objectives

- Understand array declaration and initialization
- Learn array traversal and manipulation
- Implement linear and binary search
- Practice bubble sort algorithm
- Work with multi-dimensional arrays
- Understand array bounds and memory layout

## 📝 Requirements

1. Create arrays of different data types
2. Implement array traversal and display
3. Find maximum, minimum, sum, and average
4. Implement linear search
5. Implement bubble sort
6. Work with 2D arrays (matrices)
7. Handle array bounds properly

## 💡 Hints

- Use loops to traverse arrays
- Remember arrays are zero-indexed
- Use `sizeof()` to get array size
- Pass arrays to functions using pointers
- Be careful with array bounds

## 🔧 Solution

```c
// Assignment 1.6: Arrays in C
// Array operations and algorithms

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Function prototypes
void display_array(int arr[], int size);
int find_maximum(int arr[], int size);
int find_minimum(int arr[], int size);
int calculate_sum(int arr[], int size);
double calculate_average(int arr[], int size);
int linear_search(int arr[], int size, int target);
void bubble_sort(int arr[], int size);
void display_matrix(int matrix[][3], int rows, int cols);

int main() {
    // 1D Array operations
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("=== 1D Array Operations ===\n");
    printf("Original array: ");
    display_array(numbers, size);

    printf("Maximum: %d\n", find_maximum(numbers, size));
    printf("Minimum: %d\n", find_minimum(numbers, size));
    printf("Sum: %d\n", calculate_sum(numbers, size));
    printf("Average: %.2f\n", calculate_average(numbers, size));

    // Linear search
    int target = 22;
    int position = linear_search(numbers, size, target);
    if (position != -1) {
        printf("Element %d found at position %d\n", target, position);
    } else {
        printf("Element %d not found\n", target);
    }

    // Bubble sort
    printf("\nSorting array...\n");
    bubble_sort(numbers, size);
    printf("Sorted array: ");
    display_array(numbers, size);

    // 2D Array operations
    printf("\n=== 2D Array Operations ===\n");
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("Matrix:\n");
    display_matrix(matrix, 3, 3);

    return 0;
}

void display_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int find_maximum(int arr[], int size) {
    if (size == 0) return 0;

    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int find_minimum(int arr[], int size) {
    if (size == 0) return 0;

    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int calculate_sum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double calculate_average(int arr[], int size) {
    if (size == 0) return 0.0;
    return (double)calculate_sum(arr, size) / size;
}

int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void display_matrix(int matrix[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
```

## 📊 Test Cases

### Test Case 1: Array Operations
```
Input Array: [64, 34, 25, 12, 22, 11, 90]
Expected Output:
Maximum: 90
Minimum: 11
Sum: 258
Average: 36.86
```

### Test Case 2: Linear Search
```
Target: 22
Expected Output: Element 22 found at position 4
```

### Test Case 3: Bubble Sort
```
Original: [64, 34, 25, 12, 22, 11, 90]
Expected Output: [11, 12, 22, 25, 34, 64, 90]
```

### Test Case 4: 2D Array
```
Matrix:
1 2 3
4 5 6
7 8 9
```

## 🔍 Explanation

1. **Array Declaration**: `int numbers[] = {64, 34, 25, 12, 22, 11, 90};`
2. **Array Traversal**: Using for loops to access each element
3. **Linear Search**: Sequential search through array elements
4. **Bubble Sort**: Compare adjacent elements and swap if needed
5. **2D Arrays**: Matrix representation with row and column indices
6. **Array Bounds**: Careful indexing to prevent out-of-bounds access

## 🎯 Key Concepts Covered

- Array declaration and initialization
- Array traversal and manipulation
- Linear search algorithm
- Bubble sort algorithm
- Multi-dimensional arrays
- Array bounds checking

## 🚀 Extensions

1. Implement binary search for sorted arrays
2. Add insertion sort and selection sort
3. Create matrix operations (addition, multiplication)
4. Implement dynamic arrays with realloc