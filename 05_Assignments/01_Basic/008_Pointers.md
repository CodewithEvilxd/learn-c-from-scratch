# 🎯 Assignment 1.8: Pointers in C

## 📋 Problem Statement

Create a C program that demonstrates pointer operations including declaration, dereferencing, arithmetic, and function pointers. Implement functions for array manipulation, string operations, and dynamic memory allocation using pointers.

## 🎯 Learning Objectives

- Understand pointer declaration and initialization
- Learn pointer dereferencing and address-of operator
- Practice pointer arithmetic
- Understand relationship between arrays and pointers
- Work with pointers to pointers
- Implement function pointers

## 📝 Requirements

1. Demonstrate basic pointer operations
2. Show pointer arithmetic with arrays
3. Implement string manipulation with pointers
4. Create function that returns pointer
5. Use pointers with structures
6. Demonstrate dynamic memory allocation
7. Handle pointer errors safely

## 💡 Hints

- Use `&` to get address, `*` to dereference
- Pointer arithmetic depends on data type size
- Arrays decay to pointers in function calls
- Always check for NULL before dereferencing
- Free dynamically allocated memory

## 🔧 Solution

```c
// Assignment 1.8: Pointers in C
// Comprehensive pointer operations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Function prototypes
void demonstrate_basic_pointers();
void demonstrate_pointer_arithmetic();
void demonstrate_array_pointers();
void demonstrate_string_pointers();
char* reverse_string(const char* str);
void demonstrate_function_pointers();
void demonstrate_double_pointers();
void demonstrate_dynamic_allocation();

// Function for function pointer demonstration
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main() {
    printf("=== Pointer Operations Demonstration ===\n\n");

    demonstrate_basic_pointers();
    demonstrate_pointer_arithmetic();
    demonstrate_array_pointers();
    demonstrate_string_pointers();
    demonstrate_function_pointers();
    demonstrate_double_pointers();
    demonstrate_dynamic_allocation();

    return 0;
}

void demonstrate_basic_pointers() {
    printf("1. Basic Pointer Operations\n");

    int num = 42;
    int* ptr = &num;

    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", &num);
    printf("Value of ptr: %p\n", ptr);
    printf("Value pointed by ptr: %d\n", *ptr);

    // Modifying value through pointer
    *ptr = 100;
    printf("After modification: num = %d\n\n", num);
}

void demonstrate_pointer_arithmetic() {
    printf("2. Pointer Arithmetic\n");

    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;

    printf("Array elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d (address: %p)\n", i, *(ptr + i), ptr + i);
    }

    // Pointer difference
    int* ptr2 = &arr[3];
    printf("Pointer difference: %ld elements\n\n", ptr2 - ptr);
}

void demonstrate_array_pointers() {
    printf("3. Arrays and Pointers\n");

    int arr[] = {1, 2, 3, 4, 5};
    int* ptr = arr;

    printf("Accessing array elements:\n");
    printf("arr[2] = %d\n", arr[2]);
    printf("*(arr + 2) = %d\n", *(arr + 2));
    printf("ptr[2] = %d\n", ptr[2]);
    printf("*(ptr + 2) = %d\n\n", *(ptr + 2));
}

void demonstrate_string_pointers() {
    printf("4. String Pointers\n");

    char str[] = "Hello, World!";
    char* ptr = str;

    printf("String: %s\n", ptr);
    printf("First character: %c\n", *ptr);
    printf("String length: %lu\n", strlen(ptr));

    // Reverse string using pointers
    char* reversed = reverse_string(str);
    printf("Reversed: %s\n", reversed);
    free(reversed);

    printf("\n");
}

char* reverse_string(const char* str) {
    int len = strlen(str);
    char* reversed = malloc(len + 1);

    if (!reversed) return NULL;

    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';

    return reversed;
}

void demonstrate_function_pointers() {
    printf("5. Function Pointers\n");

    // Function pointer declaration
    int (*operation)(int, int);

    // Point to add function
    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));

    // Point to subtract function
    operation = subtract;
    printf("5 - 3 = %d\n", operation(5, 3));

    // Point to multiply function
    operation = multiply;
    printf("5 * 3 = %d\n", operation(5, 3));

    // Array of function pointers
    int (*operations[3])(int, int) = {add, subtract, multiply};
    char* names[] = {"Addition", "Subtraction", "Multiplication"};

    printf("\nUsing function pointer array:\n");
    for (int i = 0; i < 3; i++) {
        printf("%s: %d\n", names[i], operations[i](10, 4));
    }

    printf("\n");
}

void demonstrate_double_pointers() {
    printf("6. Double Pointers\n");

    int num = 42;
    int* ptr = &num;
    int** double_ptr = &ptr;

    printf("Value: %d\n", num);
    printf("Single pointer: %d\n", *ptr);
    printf("Double pointer: %d\n", **double_ptr);

    // Modifying through double pointer
    **double_ptr = 100;
    printf("After modification: %d\n\n", num);
}

void demonstrate_dynamic_allocation() {
    printf("7. Dynamic Memory Allocation\n");

    // Allocate memory for integer array
    int* arr = malloc(5 * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Initialize array
    for (int i = 0; i < 5; i++) {
        arr[i] = (i + 1) * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Reallocate memory
    arr = realloc(arr, 10 * sizeof(int));
    if (!arr) {
        printf("Memory reallocation failed!\n");
        return;
    }

    // Initialize new elements
    for (int i = 5; i < 10; i++) {
        arr[i] = (i + 1) * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Free memory
    free(arr);
    printf("Memory freed successfully\n\n");
}
```

## 📊 Test Cases

### Test Case 1: Basic Pointers
```
Expected Output:
Value of num: 42
Address of num: 0x7ffd...
Value of ptr: 0x7ffd...
Value pointed by ptr: 42
After modification: num = 100
```

### Test Case 2: Pointer Arithmetic
```
Expected Output:
arr[0] = 10 (address: 0x7ffd...)
arr[1] = 20 (address: 0x7ffd...)
...
Pointer difference: 3 elements
```

### Test Case 3: Function Pointers
```
Expected Output:
5 + 3 = 8
5 - 3 = 2
5 * 3 = 15
```

### Test Case 4: Dynamic Allocation
```
Expected Output:
arr[0] = 10
arr[1] = 20
...
arr[9] = 100
Memory freed successfully
```

## 🔍 Explanation

1. **Pointer Declaration**: `int* ptr;` declares a pointer to integer
2. **Address-of Operator**: `&variable` gets memory address
3. **Dereference Operator**: `*ptr` accesses value at address
4. **Pointer Arithmetic**: Adding/subtracting moves by data type size
5. **Arrays as Pointers**: Array names decay to pointers
6. **Function Pointers**: Can point to functions for callbacks
7. **Dynamic Allocation**: `malloc()`, `realloc()`, `free()`

## 🎯 Key Concepts Covered

- Pointer declaration and initialization
- Pointer dereferencing and arithmetic
- Relationship between arrays and pointers
- Function pointers and callbacks
- Double pointers and complex types
- Dynamic memory management

## 🚀 Extensions

1. Implement linked list using pointers
2. Create pointer-based string functions
3. Implement function pointer callbacks
4. Add error handling for NULL pointers