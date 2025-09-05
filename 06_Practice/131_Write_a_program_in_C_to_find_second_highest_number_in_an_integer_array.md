# 🎯 Practical 131: Find Second Highest Number in Integer Array

## 📋 Problem Statement

Write a program in C to find second highest number in an integer array.

## 🎯 Learning Objectives

- Understand finding second maximum
- Practice array traversal
- Learn comparison techniques
- Understand edge case handling
- Practice result validation

## 📝 Requirements

1. Accept array of integers
2. Find second highest value
3. Handle duplicates appropriately
4. Display clear result
5. Handle edge cases

## 💡 Hints

- Track both max and second max
- Initialize with appropriate values
- Update both during traversal
- Handle arrays with less than 2 elements
- Consider duplicate maximums

## 🔧 Solution

```c
// Practical 131: Find Second Highest Number in Integer Array
// Finds the second largest element in an array

#include <stdio.h>
#include <limits.h>

int findSecondHighest(int arr[], int n) {
    if (n < 2) {
        printf("Array must have at least 2 elements!\n");
        return INT_MIN;
    }
    
    int max1 = INT_MIN, max2 = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2 && arr[i] != max1) {
            max2 = arr[i];
        }
    }
    
    if (max2 == INT_MIN) {
        printf("No second highest element found!\n");
        return INT_MIN;
    }
    
    return max2;
}

int main() {
    int n;
    int arr[1000];

    printf("Find Second Highest Number\n");
    printf("==========================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int secondHighest = findSecondHighest(arr, n);

    if (secondHighest != INT_MIN) {
        printf("Array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Second highest number: %d\n", secondHighest);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Case
```
Input: 5, 10 20 30 40 50
Expected Output:
Array: 10 20 30 40 50
Second highest number: 40
```

### Test Case 2: With Duplicates
```
Input: 4, 10 20 20 30
Expected Output:
Array: 10 20 20 30
Second highest number: 20
```

### Test Case 3: All Same
```
Input: 3, 5 5 5
Expected Output:
No second highest element found!
```

### Test Case 4: Two Elements
```
Input: 2, 15 25
Expected Output:
Array: 15 25
Second highest number: 15
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

1. Find third highest number
2. Find k-th highest number
3. Handle floating point numbers
4. Find positions of second highest