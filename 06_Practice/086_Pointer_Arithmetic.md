# 🎯 Practical 86: Pointer Arithmetic

## 📋 Problem Statement

Write a C program to illustrate pointer arithmetic.

## 📋 Problem Statement

Write a C program to illustrate pointer arithmetic.

## 🎯 Learning Objectives

- Understand pointer arithmetic
- Practice pointer operations
- Learn memory addressing
- Understand pointer increment/decrement
- Practice array-pointer relationship

## 📝 Requirements

1. Create array and pointer
2. Demonstrate pointer arithmetic
3. Show address calculations
4. Display pointer operations
5. Illustrate array access via pointers

## 💡 Hints

- Use array name as pointer
- Show ptr++, ptr--
- Demonstrate ptr + n, ptr - n
- Display memory addresses
- Show equivalent array access

## 🔧 Solution

```c
// Practical 86: Pointer Arithmetic
// Demonstrates pointer arithmetic operations

#include <stdio.h>

int main() {
    int array[5] = {10, 20, 30, 40, 50};
    int *ptr;

    printf("Pointer Arithmetic Demonstration\n");
    printf("=================================\n");

    // Initialize pointer to array
    ptr = array;

    printf("Array elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");

    // Basic pointer operations
    printf("Basic Pointer Operations:\n");
    printf("-----------------------\n");
    printf("ptr = array; // ptr points to array[0]\n");
    printf("Value at ptr: %d\n", *ptr);
    printf("Address of ptr: %p\n", ptr);
    printf("Address of array[0]: %p\n", &array[0]);
    printf("\n");

    // Pointer increment
    printf("Pointer Increment:\n");
    printf("------------------\n");
    printf("Before increment: ptr = %p, *ptr = %d\n", ptr, *ptr);
    ptr++;
    printf("After ptr++: ptr = %p, *ptr = %d\n", ptr, *ptr);
    printf("This is equivalent to array[1]\n\n");

    // Pointer decrement
    printf("Pointer Decrement:\n");
    printf("------------------\n");
    ptr--;
    printf("After ptr--: ptr = %p, *ptr = %d\n", ptr, *ptr);
    printf("Back to original position\n\n");

    // Pointer addition
    printf("Pointer Addition:\n");
    printf("-----------------\n");
    printf("ptr + 2: %p, *(ptr + 2) = %d\n", ptr + 2, *(ptr + 2));
    printf("This is equivalent to array[2]\n\n");

    // Pointer subtraction
    printf("Pointer Subtraction:\n");
    printf("--------------------\n");
    printf("ptr - 1: %p, *(ptr - 1) = %d\n", ptr - 1, *(ptr - 1));
    printf("This would be array[-1] (invalid!)\n\n");

    // Array access using pointers
    printf("Array Access Using Pointers:\n");
    printf("----------------------------\n");
    ptr = array; // Reset to beginning
    for (int i = 0; i < 5; i++) {
        printf("array[%d] = %d, *(ptr + %d) = %d, ptr[%d] = %d\n",
               i, array[i], i, *(ptr + i), i, ptr[i]);
    }
    printf("\n");

    // Pointer difference
    printf("Pointer Difference:\n");
    printf("------------------\n");
    int *ptr2 = &array[3];
    printf("ptr points to array[0]: %p\n", ptr);
    printf("ptr2 points to array[3]: %p\n", ptr2);
    printf("ptr2 - ptr = %ld (difference in elements)\n", ptr2 - ptr);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Standard Output
```
Expected Output:
Array elements: 10 20 30 40 50

Basic Pointer Operations:
-----------------------
ptr = array; // ptr points to array[0]
Value at ptr: 10
Address of ptr: 0x7ffd...
Address of array[0]: 0x7ffd...

Pointer Increment:
------------------
Before increment: ptr = 0x7ffd..., *ptr = 10
After ptr++: ptr = 0x7ffd..., *ptr = 20
This is equivalent to array[1]
```

## 🔍 Explanation

1. **Pointer Initialization**: ptr = array
2. **Increment/Decrement**: ptr++, ptr--
3. **Addition/Subtraction**: ptr + n, ptr - n
4. **Array Access**: *(ptr + i), ptr[i]
5. **Address Display**: Memory locations

## 🎯 Key Concepts Covered

- Pointer arithmetic
- Array-pointer equivalence
- Memory addressing
- Pointer operations
- Address calculations

## 🚀 Extensions

1. Pointer arithmetic with different data types
2. Function pointers
3. Pointer to pointer
4. Dynamic memory with pointers