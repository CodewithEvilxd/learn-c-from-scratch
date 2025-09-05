# 🎯 Practical 88: Dynamic Memory Largest

## 📋 Problem Statement

Write a C program to find largest number using dynamic memory allocation.

## 🎯 Learning Objectives

- Understand dynamic memory allocation
- Practice malloc() and free()
- Learn memory management
- Understand heap allocation
- Practice error handling

## 📝 Requirements

1. Accept array size from user
2. Allocate memory dynamically
3. Input array elements
4. Find largest element
5. Free allocated memory

## 💡 Hints

- Use malloc() to allocate memory
- Check if allocation successful
- Use free() to deallocate memory
- Handle memory allocation failures
- Use pointers for dynamic arrays

## 🔧 Solution

```c
// Practical 88: Dynamic Memory Largest
// Finds largest number using dynamic memory allocation

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *array;
    
    printf("Find Largest Using Dynamic Memory\n");
    printf("==================================\n");
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Number of elements must be positive!\n");
        return 1;
    }
    
    // Allocate memory dynamically
    array = (int *)malloc(n * sizeof(int));
    
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Input array elements
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    
    // Find largest element
    int largest = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > largest) {
            largest = array[i];
        }
    }
    
    // Display results
    printf("\nArray elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    
    printf("\nLargest element: %d\n", largest);
    
    // Free allocated memory
    free(array);
    printf("Memory freed successfully.\n");
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Input
```
Input: n=5, elements=[12, 45, 23, 67, 34]
Expected Output:
Largest element: 67
Memory freed successfully.
```

### Test Case 2: Single Element
```
Input: n=1, elements=[42]
Expected Output:
Largest element: 42
Memory freed successfully.
```

### Test Case 3: Negative Numbers
```
Input: n=4, elements=[-10, -5, -20, -1]
Expected Output:
Largest element: -1
Memory freed successfully.
```

## 🔍 Explanation

1. **Dynamic Allocation**: malloc(n * sizeof(int))
2. **Memory Check**: Verify allocation success
3. **Array Operations**: Use pointer like regular array
4. **Largest Finding**: Standard comparison algorithm
5. **Memory Cleanup**: free() to prevent leaks

## 🎯 Key Concepts Covered

- Dynamic memory allocation
- malloc() and free()
- Memory management
- Pointer usage
- Error handling

## 🚀 Extensions

1. Find smallest element dynamically
2. Sort array using dynamic memory
3. Resize array dynamically
4. Handle memory allocation failures gracefully