# 🎯 Practical 135: Calculate Length of an Array

## 📋 Problem Statement

C Program to calculate length of an array.

## 🎯 Learning Objectives

- Understand array size calculation
- Practice sizeof operator
- Learn array properties
- Understand compile-time vs runtime
- Practice size determination

## 📝 Requirements

1. Accept array of integers
2. Calculate array length
3. Display the length
4. Show array contents
5. Explain calculation method

## 💡 Hints

- Use sizeof(arr) / sizeof(arr[0])
- Works for static arrays
- Calculate at compile time
- Display clear results
- Handle different array sizes

## 🔧 Solution

```c
// Practical 135: Calculate Length of an Array
// Demonstrates array size calculation using sizeof

#include <stdio.h>

int main() {
    int arr[1000];
    int n;

    printf("Calculate Length of an Array\n");
    printf("=============================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 1000) {
        printf("Invalid array size! Must be between 1 and 1000.\n");
        return 1;
    }

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Calculate array length
    int length = sizeof(arr) / sizeof(arr[0]);

    printf("Array contents: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Logical length (elements entered): %d\n", n);
    printf("Physical length (array capacity): %d\n", length);
    printf("Memory used: %lu bytes\n", sizeof(arr));

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Array
```
Input: 5, 1 2 3 4 5
Expected Output:
Array contents: 1 2 3 4 5
Logical length (elements entered): 5
Physical length (array capacity): 1000
Memory used: 4000 bytes
```

### Test Case 2: Small Array
```
Input: 3, 10 20 30
Expected Output:
Array contents: 10 20 30
Logical length (elements entered): 3
Physical length (array capacity): 1000
Memory used: 4000 bytes
```

### Test Case 3: Single Element
```
Input: 1, 42
Expected Output:
Array contents: 42
Logical length (elements entered): 1
Physical length (array capacity): 1000
Memory used: 4000 bytes
```

## 🔍 Explanation

1. **Input Reading**: Read number of elements and values
2. **Size Calculation**: Use sizeof operator
3. **Logical vs Physical**: Distinguish between used and allocated size
4. **Memory Info**: Show memory usage
5. **Output**: Display all relevant information

## 🎯 Key Concepts Covered

- Array size calculation
- sizeof operator usage
- Memory allocation
- Logical vs physical size
- Array properties

## 🚀 Extensions

1. Calculate length of dynamic arrays
2. Handle different data types
3. Calculate string length
4. Compare different size methods