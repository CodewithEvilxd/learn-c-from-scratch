# 🎯 Practical 87: Array Pointer Access

## 📋 Problem Statement

Write a C program to access array elements using pointer.

## 🎯 Learning Objectives

- Understand pointer arithmetic
- Practice array-pointer relationship
- Learn pointer increment/decrement
- Understand memory addressing
- Practice pointer operations

## 📝 Requirements

1. Create an array
2. Use pointer to access elements
3. Display elements using pointers
4. Modify elements using pointers
5. Show pointer arithmetic

## 💡 Hints

- Use array name as pointer
- Pointer increment: ptr++
- Access elements: *ptr
- Show both array and pointer methods
- Demonstrate pointer arithmetic

## 🔧 Solution

```c
// Practical 87: Array Pointer Access
// Accesses array elements using pointers

#include <stdio.h>

int main() {
    int n;
    
    printf("Array Pointer Access\n");
    printf("====================\n");
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Number of elements must be positive!\n");
        return 1;
    }
    
    int array[n];
    int *ptr;
    
    // Input array elements
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    
    // Display using array indexing
    printf("\nUsing array indexing:\n");
    for (int i = 0; i < n; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    // Display using pointers
    printf("\nUsing pointers:\n");
    ptr = array; // Point to first element
    for (int i = 0; i < n; i++) {
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    }
    
    // Demonstrate pointer arithmetic
    printf("\nPointer arithmetic demonstration:\n");
    ptr = array; // Reset to beginning
    printf("Initial pointer address: %p\n", ptr);
    printf("Value at pointer: %d\n", *ptr);
    
    ptr++; // Move to next element
    printf("After ptr++ address: %p\n", ptr);
    printf("Value at new pointer: %d\n", *ptr);
    
    ptr += 2; // Move two positions ahead
    printf("After ptr += 2 address: %p\n", ptr);
    printf("Value at new pointer: %d\n", *ptr);
    
    // Modify array using pointers
    printf("\nModifying array using pointers:\n");
    ptr = array; // Reset to beginning
    for (int i = 0; i < n; i++) {
        *(ptr + i) = *(ptr + i) * 2; // Double each element
    }
    
    printf("Modified array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Basic Access
```
Input: n=5, elements=[10, 20, 30, 40, 50]
Expected Output:
Using pointers:
*(ptr + 0) = 10
*(ptr + 1) = 20
*(ptr + 2) = 30
*(ptr + 3) = 40
*(ptr + 4) = 50
```

### Test Case 2: Pointer Arithmetic
```
Expected Output:
Initial pointer address: 0x7ffd...
After ptr++ address: 0x7ffd...
After ptr += 2 address: 0x7ffd...
```

## 🔍 Explanation

1. **Array-Pointer Relationship**: array name is pointer to first element
2. **Pointer Access**: *(ptr + i) equivalent to array[i]
3. **Pointer Arithmetic**: ptr++ moves to next element
4. **Modification**: Change values using pointers
5. **Memory Addresses**: Show pointer movement

## 🎯 Key Concepts Covered

- Pointer arithmetic
- Array-pointer equivalence
- Memory addressing
- Pointer increment/decrement
- Indirect access

## 🚀 Extensions

1. Reverse array using pointers
2. Search element using pointers
3. Sort array using pointers
4. Dynamic memory with pointers