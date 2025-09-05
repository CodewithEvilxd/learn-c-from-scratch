# 🎯 Practical 129: Compare Two Arrays for Equal Size

## 📋 Problem Statement

Write a program in C for, How to compare two array is equal in size or not.

## 🎯 Learning Objectives

- Understand array size comparison
- Practice array length handling
- Learn size equality checking
- Understand array properties
- Practice conditional output

## 📝 Requirements

1. Accept two arrays
2. Compare their sizes
3. Display comparison result
4. Handle different scenarios
5. Show array details

## 💡 Hints

- Get size of both arrays
- Compare size values
- Display clear result
- Handle edge cases
- Show array contents

## 🔧 Solution

```c
// Practical 129: Compare Two Arrays for Equal Size
// Compares whether two arrays have equal sizes

#include <stdio.h>

void compareArraySizes(int arr1[], int n1, int arr2[], int n2) {
    printf("Array 1 size: %d\n", n1);
    printf("Array 2 size: %d\n", n2);
    
    if (n1 == n2) {
        printf("Result: Arrays are equal in size\n");
    } else {
        printf("Result: Arrays are not equal in size\n");
        if (n1 > n2) {
            printf("Array 1 is larger by %d elements\n", n1 - n2);
        } else {
            printf("Array 2 is larger by %d elements\n", n2 - n1);
        }
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Compare Array Sizes\n");
    printf("===================\n");

    printf("Array 1: ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("Array 2: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    compareArraySizes(arr1, n1, arr2, n2);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Equal Sizes
```
Array 1: 1 2 3 4 5
Array 2: 10 20 30 40 50
Expected Output:
Array 1 size: 5
Array 2 size: 5
Result: Arrays are equal in size
```

### Test Case 2: Different Sizes
```
Array 1: 1 2 3 4 5
Array 2: 10 20 30
Expected Output:
Array 1 size: 5
Array 2 size: 3
Result: Arrays are not equal in size
Array 1 is larger by 2 elements
```

### Test Case 3: Empty Arrays
```
Array 1: (empty)
Array 2: (empty)
Expected Output:
Array 1 size: 0
Array 2 size: 0
Result: Arrays are equal in size
```

## 🔍 Explanation

1. **Array Setup**: Define or input two arrays
2. **Size Calculation**: Get sizes using sizeof
3. **Comparison**: Compare the sizes
4. **Result Display**: Show comparison result
5. **Difference**: Show size difference if unequal

## 🎯 Key Concepts Covered

- Array size calculation
- Size comparison
- Conditional logic
- Array properties
- Output formatting

## 🚀 Extensions

1. Compare array contents for equality
2. Handle dynamic arrays
3. Compare multiple arrays
4. Check memory sizes vs logical sizes