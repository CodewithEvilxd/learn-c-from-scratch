# 🎯 Practical 156: Showcase Use of DMA

## 📋 Problem Statement

C Program to showcase use of DMA (Dynamic Memory Allocation).

## 🎯 Learning Objectives

- Understand dynamic memory allocation
- Practice malloc, calloc, realloc, free
- Learn memory management
- Understand heap memory
- Practice error handling

## 📝 Requirements

1. Demonstrate malloc usage
2. Show calloc functionality
3. Illustrate realloc usage
4. Show proper memory cleanup
5. Handle allocation failures

## 💡 Hints

- Use malloc for single allocation
- Use calloc for zero-initialized arrays
- Use realloc to resize memory
- Always free allocated memory
- Check for NULL after allocation

## 🔧 Solution

```c
// Practical 156: Showcase Use of DMA
// Demonstrates Dynamic Memory Allocation functions

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr1, *ptr2, *ptr3;
    int n = 5;

    printf("Dynamic Memory Allocation Demo\n");
    printf("==============================\n");

    // 1. malloc - allocate memory
    printf("\n1. Using malloc:\n");
    ptr1 = (int *)malloc(n * sizeof(int));

    if (ptr1 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Memory allocated using malloc\n");
    for (int i = 0; i < n; i++) {
        ptr1[i] = i + 1;
        printf("ptr1[%d] = %d\n", i, ptr1[i]);
    }

    // 2. calloc - allocate and initialize to zero
    printf("\n2. Using calloc:\n");
    ptr2 = (int *)calloc(n, sizeof(int));

    if (ptr2 == NULL) {
        printf("Memory allocation failed!\n");
        free(ptr1);
        return 1;
    }

    printf("Memory allocated using calloc (initialized to zero)\n");
    for (int i = 0; i < n; i++) {
        printf("ptr2[%d] = %d\n", i, ptr2[i]);
    }

    // 3. realloc - resize memory
    printf("\n3. Using realloc:\n");
    n = 8;
    ptr3 = (int *)realloc(ptr1, n * sizeof(int));

    if (ptr3 == NULL) {
        printf("Memory reallocation failed!\n");
        free(ptr1);
        free(ptr2);
        return 1;
    }

    ptr1 = ptr3; // Update pointer
    printf("Memory reallocated to size %d\n", n);

    // Initialize new elements
    for (int i = 5; i < n; i++) {
        ptr1[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        printf("ptr1[%d] = %d\n", i, ptr1[i]);
    }

    // 4. free - deallocate memory
    printf("\n4. Freeing memory:\n");
    free(ptr1);
    free(ptr2);
    printf("Memory freed successfully!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Allocation
```
Expected Output:
Dynamic Memory Allocation Demo
==============================
1. Using malloc:
Memory allocated using malloc
ptr1[0] = 1
ptr1[1] = 2
ptr1[2] = 3
ptr1[3] = 4
ptr1[4] = 5

2. Using calloc:
Memory allocated using calloc (initialized to zero)
ptr2[0] = 0
ptr2[1] = 0
ptr2[2] = 0
ptr2[3] = 0
ptr2[4] = 0

3. Using realloc:
Memory reallocated to size 8
ptr1[0] = 1
ptr1[1] = 2
ptr1[2] = 3
ptr1[3] = 4
ptr1[4] = 5
ptr1[5] = 6
ptr1[6] = 7
ptr1[7] = 8

4. Freeing memory:
Memory freed successfully!
```

## 🔍 Explanation

1. **malloc**: Allocates memory block
2. **calloc**: Allocates and initializes to zero
3. **realloc**: Resizes existing memory block
4. **free**: Deallocates memory
5. **Error Handling**: Checks for allocation failures

## 🎯 Key Concepts Covered

- Dynamic memory allocation
- malloc, calloc, realloc, free functions
- Memory management
- Pointer operations
- Error handling

## 🚀 Extensions

1. Implement dynamic arrays
2. Create linked lists with DMA
3. Handle memory fragmentation
4. Implement custom memory pool