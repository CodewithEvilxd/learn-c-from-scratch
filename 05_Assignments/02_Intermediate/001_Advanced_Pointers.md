# 🎯 Assignment 2.1: Advanced Pointers

## 📋 Problem Statement

Create a C program that demonstrates advanced pointer concepts including function pointers, pointer to pointers, dynamic memory allocation with pointers, and complex data structures using pointers.

## 🎯 Learning Objectives

- Master function pointers and callbacks
- Understand pointer arithmetic in detail
- Work with pointers to pointers
- Implement dynamic data structures
- Practice memory management with pointers
- Understand pointer type casting

## 📝 Requirements

1. Implement function pointers for callbacks
2. Create pointer-based generic data structures
3. Demonstrate pointer arithmetic with arrays
4. Work with double and triple pointers
5. Implement custom memory allocator
6. Handle complex pointer operations safely

## 💡 Hints

- Function pointers store addresses of functions
- Use `(*ptr)()` syntax to call function through pointer
- Double pointers useful for dynamic allocation
- Pointer arithmetic depends on data type size
- Always validate pointers before dereferencing

## 🔧 Solution

```c
// Assignment 2.1: Advanced Pointers
// Function pointers, pointer arithmetic, and complex operations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function pointer types
typedef int (*MathOperation)(int, int);
typedef void (*PrintFunction)(void* data);
typedef int (*CompareFunction)(const void*, const void*);

// Generic data structure using void pointers
typedef struct {
    void* data;
    size_t size;
    size_t element_size;
    PrintFunction print_func;
    CompareFunction compare_func;
} GenericArray;

// Function prototypes
void demonstrate_function_pointers();
void demonstrate_pointer_arithmetic();
void demonstrate_double_pointers();
void demonstrate_generic_arrays();
void demonstrate_custom_allocator();

// Math operations for function pointers
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

// Print functions for different types
void print_int(void* data) { printf("%d", *(int*)data); }
void print_float(void* data) { printf("%.2f", *(float*)data); }
void print_string(void* data) { printf("%s", (char*)data); }

// Compare functions
int compare_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int compare_string(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main() {
    printf("=== Advanced Pointers Demonstration ===\n\n");

    demonstrate_function_pointers();
    demonstrate_pointer_arithmetic();
    demonstrate_double_pointers();
    demonstrate_generic_arrays();
    demonstrate_custom_allocator();

    return 0;
}

void demonstrate_function_pointers() {
    printf("1. Function Pointers\n");

    // Array of function pointers
    MathOperation operations[] = {add, subtract, multiply, divide};
    const char* op_names[] = {"Addition", "Subtraction", "Multiplication", "Division"};

    int a = 20, b = 4;

    for (int i = 0; i < 4; i++) {
        printf("%s: %d %s %d = %d\n",
               op_names[i], a,
               (i == 0) ? "+" : (i == 1) ? "-" : (i == 2) ? "*" : "/",
               b, operations[i](a, b));
    }

    // Function pointer as callback
    MathOperation callback = add;
    printf("Callback result: %d\n", callback(10, 5));

    printf("\n");
}

void demonstrate_pointer_arithmetic() {
    printf("2. Pointer Arithmetic\n");

    // Array and pointer relationship
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;

    printf("Array elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d (address: %p)\n", i, *(ptr + i), ptr + i);
    }

    // Pointer difference
    int* ptr2 = &arr[3];
    ptrdiff_t difference = ptr2 - ptr;
    printf("Pointer difference: %td elements\n", difference);

    // Pointer comparison
    if (ptr < ptr2) {
        printf("ptr points to earlier element than ptr2\n");
    }

    // Character pointer arithmetic
    char str[] = "Hello";
    char* char_ptr = str;

    printf("Character pointer arithmetic:\n");
    for (int i = 0; i < strlen(str); i++) {
        printf("str[%d] = '%c' (address: %p)\n", i, *(char_ptr + i), char_ptr + i);
    }

    printf("\n");
}

void demonstrate_double_pointers() {
    printf("3. Double Pointers\n");

    int value = 42;
    int* single_ptr = &value;
    int** double_ptr = &single_ptr;

    printf("Value: %d\n", value);
    printf("Single pointer: %d\n", *single_ptr);
    printf("Double pointer: %d\n", **double_ptr);

    // Modifying through double pointer
    **double_ptr = 100;
    printf("After modification: %d\n", value);

    // Array of pointers
    int* ptr_array[3];
    int a = 1, b = 2, c = 3;

    ptr_array[0] = &a;
    ptr_array[1] = &b;
    ptr_array[2] = &c;

    printf("Array of pointers: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", *ptr_array[i]);
    }
    printf("\n");

    // Pointer to array of pointers
    int** ptr_to_array = ptr_array;
    printf("Pointer to array: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", *ptr_to_array[i]);
    }
    printf("\n");

    printf("\n");
}

void demonstrate_generic_arrays() {
    printf("4. Generic Arrays with Pointers\n");

    // Integer array
    int int_data[] = {5, 2, 8, 1, 9};
    GenericArray int_array = {
        .data = int_data,
        .size = 5,
        .element_size = sizeof(int),
        .print_func = print_int,
        .compare_func = compare_int
    };

    printf("Integer array: ");
    for (size_t i = 0; i < int_array.size; i++) {
        int_array.print_func((char*)int_array.data + i * int_array.element_size);
        if (i < int_array.size - 1) printf(", ");
    }
    printf("\n");

    // String array
    const char* str_data[] = {"Apple", "Banana", "Cherry", "Date"};
    GenericArray str_array = {
        .data = &str_data,
        .size = 4,
        .element_size = sizeof(char*),
        .print_func = print_string,
        .compare_func = compare_string
    };

    printf("String array: ");
    for (size_t i = 0; i < str_array.size; i++) {
        char** str_ptr = (char**)str_array.data + i;
        str_array.print_func(*str_ptr);
        if (i < str_array.size - 1) printf(", ");
    }
    printf("\n");

    printf("\n");
}

void demonstrate_custom_allocator() {
    printf("5. Custom Memory Allocator\n");

    // Simple bump allocator
    typedef struct {
        void* memory;
        size_t size;
        size_t used;
    } BumpAllocator;

    BumpAllocator allocator;
    allocator.size = 1024;
    allocator.memory = malloc(allocator.size);
    allocator.used = 0;

    if (!allocator.memory) {
        printf("Failed to allocate memory for allocator!\n");
        return;
    }

    // Allocate from our custom allocator
    void* ptr1 = (char*)allocator.memory + allocator.used;
    allocator.used += sizeof(int);
    *(int*)ptr1 = 42;

    void* ptr2 = (char*)allocator.memory + allocator.used;
    allocator.used += sizeof(double);
    *(double*)ptr2 = 3.14159;

    printf("Custom allocator results:\n");
    printf("Integer: %d\n", *(int*)ptr1);
    printf("Double: %f\n", *(double*)ptr2);
    printf("Memory used: %zu/%zu bytes\n", allocator.used, allocator.size);

    free(allocator.memory);
    printf("\n");
}
```

## 📊 Test Cases

### Test Case 1: Function Pointers
```
Expected Output:
Addition: 20 + 4 = 24
Subtraction: 20 - 4 = 16
Multiplication: 20 * 4 = 80
Division: 20 / 4 = 5
Callback result: 15
```

### Test Case 2: Pointer Arithmetic
```
Expected Output:
arr[0] = 10 (address: 0x...)
arr[1] = 20 (address: 0x...)
...
Pointer difference: 3 elements
```

### Test Case 3: Double Pointers
```
Expected Output:
Value: 42
Single pointer: 42
Double pointer: 42
After modification: 100
```

### Test Case 4: Generic Arrays
```
Expected Output:
Integer array: 5, 2, 8, 1, 9
String array: Apple, Banana, Cherry, Date
```

## 🔍 Explanation

1. **Function Pointers**: Store addresses of functions for callbacks
2. **Pointer Arithmetic**: Add/subtract integers to move through memory
3. **Double Pointers**: Pointers that point to other pointers
4. **Generic Programming**: Using void pointers for type-agnostic code
5. **Custom Allocators**: Implementing memory management strategies

## 🎯 Key Concepts Covered

- Function pointers and callbacks
- Advanced pointer arithmetic
- Multi-level pointers
- Generic programming with void pointers
- Custom memory allocation
- Type casting with pointers

## 🚀 Extensions

1. Implement function pointer tables for polymorphism
2. Create a complete generic container library
3. Add bounds checking to pointer arithmetic
4. Implement garbage collection with pointers