# 🎯 Practical 130: Find Largest and Smallest Number in Array

## 📋 Problem Statement

Write a program in C to find largest and smallest number in array.

## 🎯 Learning Objectives

- Understand min/max finding
- Practice array traversal
- Learn comparison techniques
- Understand boundary value handling
- Practice result display

## 📝 Requirements

1. Accept array of integers
2. Find minimum and maximum values
3. Display both results
4. Handle edge cases
5. Show array contents

## 💡 Hints

- Initialize min and max with first element
- Traverse array comparing each element
- Update min and max as needed
- Handle single element arrays
- Display clear results

## 🔧 Solution

```c
// Practical 130: Find Largest and Smallest Number in Array
// Finds both minimum and maximum values in an array

#include <stdio.h>
#include <limits.h>

void findMinMax(int arr[], int n, int *min, int *max) {
    if (n == 0) {
        *min = *max = 0;
        return;
    }
    
    *min = *max = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

int main() {
    int n;
    int arr[1000];

    printf("Find Min and Max in Array\n");
    printf("=========================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array must have at least one element!\n");
        return 1;
    }

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int min_val, max_val;
    findMinMax(arr, n, &min_val, &max_val);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Smallest number: %d\n", min_val);
    printf("Largest number: %d\n", max_val);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Numbers
```
Input: 5, 1 8 3 9 2
Expected Output:
Array: 1 8 3 9 2
Smallest number: 1
Largest number: 9
```

### Test Case 2: Negative Numbers
```
Input: 4, -5 -1 -9 -3
Expected Output:
Array: -5 -1 -9 -3
Smallest number: -9
Largest number: -1
```

### Test Case 3: Single Element
```
Input: 1, 42
Expected Output:
Array: 42
Smallest number: 42
Largest number: 42
```

### Test Case 4: All Same
```
Input: 3, 7 7 7
Expected Output:
Array: 7 7 7
Smallest number: 7
Largest number: 7
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Initialization**: Set min and max to first element
3. **Traversal**: Compare each element with current min/max
4. **Updates**: Update min/max when smaller/larger found
5. **Output**: Display results clearly

## 🎯 Key Concepts Covered

- Array traversal
- Comparison operations
- Pointer usage for return values
- Edge case handling
- Boundary value analysis

## 🚀 Extensions

1. Find second largest/smallest
2. Find k-th largest/smallest
3. Handle floating point numbers
4. Find positions of min/max