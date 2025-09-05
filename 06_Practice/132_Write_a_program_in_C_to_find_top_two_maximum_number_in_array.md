# 🎯 Practical 132: Find Top Two Maximum Numbers in Array

## 📋 Problem Statement

Write a program in C to find top two maximum number in array.

## 🎯 Learning Objectives

- Understand finding top two maximums
- Practice array traversal
- Learn comparison techniques
- Understand edge case handling
- Practice result validation

## 📝 Requirements

1. Accept array of integers
2. Find top two maximum values
3. Handle duplicates appropriately
4. Display both results
5. Handle edge cases

## 💡 Hints

- Track both max1 and max2
- Initialize with appropriate values
- Update both during traversal
- Handle arrays with less than 2 elements
- Consider duplicate maximums

## 🔧 Solution

```c
// Practical 132: Find Top Two Maximum Numbers in Array
// Finds the two largest elements in an array

#include <stdio.h>
#include <limits.h>

void findTopTwoMax(int arr[], int n, int *max1, int *max2) {
    *max1 = INT_MIN;
    *max2 = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > *max1) {
            *max2 = *max1;
            *max1 = arr[i];
        } else if (arr[i] > *max2 && arr[i] != *max1) {
            *max2 = arr[i];
        }
    }
}

int main() {
    int n;
    int arr[1000];

    printf("Find Top Two Maximum Numbers\n");
    printf("=============================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Array must have at least 2 elements!\n");
        return 1;
    }

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max1, max2;
    findTopTwoMax(arr, n, &max1, &max2);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (max2 == INT_MIN) {
        printf("Top maximum: %d\n", max1);
        printf("No second maximum found (all elements are same)!\n");
    } else {
        printf("Top two maximum numbers: %d and %d\n", max1, max2);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Case
```
Input: 5, 10 50 30 40 20
Expected Output:
Array: 10 50 30 40 20
Top two maximum numbers: 50 and 40
```

### Test Case 2: With Duplicates
```
Input: 4, 10 20 20 30
Expected Output:
Array: 10 20 20 30
Top two maximum numbers: 30 and 20
```

### Test Case 3: All Same
```
Input: 3, 5 5 5
Expected Output:
Array: 5 5 5
Top maximum: 5
No second maximum found (all elements are same)!
```

### Test Case 4: Two Elements
```
Input: 2, 15 25
Expected Output:
Array: 15 25
Top two maximum numbers: 25 and 15
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Initialization**: Set max1 and max2 to minimum values
3. **Traversal**: Compare each element with current max values
4. **Updates**: Update max1 and max2 appropriately
5. **Validation**: Check if second max was found

## 🎯 Key Concepts Covered

- Array traversal
- Comparison operations
- Edge case handling
- Duplicate management
- Boundary value analysis

## 🚀 Extensions

1. Find top three maximum numbers
2. Find k maximum numbers
3. Handle floating point numbers
4. Find positions of maximums