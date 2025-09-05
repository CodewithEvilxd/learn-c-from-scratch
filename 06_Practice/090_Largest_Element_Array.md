# 🎯 Practical 90: Largest Element in Array

## 📋 Problem Statement

Write a C program to find largest element in an array.

## 🎯 Learning Objectives

- Understand array traversal
- Practice comparison operations
- Learn maximum finding algorithm
- Understand loop implementation
- Practice input validation

## 📝 Requirements

1. Accept array elements
2. Find the largest element
3. Display the result
4. Show array elements
5. Handle edge cases

## 💡 Hints

- Initialize max with first element
- Traverse array and compare
- Update max when larger value found
- Handle empty array
- Use appropriate data types

## 🔧 Solution

```c
// Practical 90: Largest Element in Array
// Finds the largest element in an array

#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    
    printf("Find Largest Element in Array\n");
    printf("==============================\n");
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Array must have at least one element!\n");
        return 1;
    }
    
    int array[n];
    int largest;
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    
    // Initialize largest with first element
    largest = array[0];
    
    // Find largest element
    for (int i = 1; i < n; i++) {
        if (array[i] > largest) {
            largest = array[i];
        }
    }
    
    // Display array
    printf("\nArray elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    
    printf("\nLargest element: %d\n", largest);
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Array
```
Input: n=5, elements=[12, 45, 23, 67, 34]
Expected Output:
Largest element: 67
```

### Test Case 2: First Element Largest
```
Input: n=4, elements=[100, 20, 30, 40]
Expected Output:
Largest element: 100
```

### Test Case 3: All Equal Elements
```
Input: n=3, elements=[5, 5, 5]
Expected Output:
Largest element: 5
```

### Test Case 4: Negative Numbers
```
Input: n=4, elements=[-10, -5, -20, -1]
Expected Output:
Largest element: -1
```

## 🔍 Explanation

1. **Array Input**: Read n elements into array
2. **Initialization**: Set largest to first element
3. **Traversal**: Compare each element with current largest
4. **Update**: Replace largest when larger value found
5. **Display**: Show array and largest element

## 🎯 Key Concepts Covered

- Array traversal
- Comparison operations
- Maximum finding algorithm
- Loop implementation
- Input validation

## 🚀 Extensions

1. Find second largest element
2. Find smallest element
3. Find kth largest element
4. Handle duplicate maximum values