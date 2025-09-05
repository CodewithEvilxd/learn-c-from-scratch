# 🎯 Assignment 1.11: Dynamic Memory Allocation

## 📋 Problem Statement

Create a C program that demonstrates dynamic memory allocation using malloc, calloc, realloc, and free. Implement a dynamic array that can grow and shrink, and a simple memory pool allocator.

## 🎯 Learning Objectives

- Understand dynamic memory allocation
- Learn malloc, calloc, realloc, and free functions
- Practice memory management
- Handle memory allocation errors
- Understand memory leaks and how to prevent them
- Implement custom memory management

## 📝 Requirements

1. Demonstrate malloc, calloc, realloc usage
2. Create a dynamic array that can resize
3. Implement a simple memory pool
4. Handle memory allocation failures
5. Properly free all allocated memory
6. Show memory usage statistics

## 💡 Hints

- Always check return value of allocation functions
- Use `sizeof()` to calculate correct sizes
- Free memory in reverse order of allocation
- Set pointers to NULL after freeing
- Handle realloc failures properly

## 🔧 Solution

```c
// Assignment 1.11: Dynamic Memory Allocation
// Dynamic arrays and memory pool implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 4
#define MEMORY_POOL_SIZE 1024
#define BLOCK_SIZE 64

// Dynamic Array structure
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} DynamicArray;

// Memory Pool structure
typedef struct {
    void* pool;
    size_t pool_size;
    size_t used;
    void* free_list;
} MemoryPool;

// Function prototypes
void dynamic_array_init(DynamicArray* arr);
void dynamic_array_add(DynamicArray* arr, int value);
void dynamic_array_remove(DynamicArray* arr, size_t index);
void dynamic_array_free(DynamicArray* arr);
void dynamic_array_print(const DynamicArray* arr);

MemoryPool* memory_pool_create(size_t size);
void* memory_pool_alloc(MemoryPool* pool, size_t size);
void memory_pool_free(MemoryPool* pool, void* ptr);
void memory_pool_destroy(MemoryPool* pool);

void demonstrate_basic_allocation();
void demonstrate_dynamic_array();
void demonstrate_memory_pool();

int main() {
    printf("=== Dynamic Memory Allocation Demonstration ===\n\n");

    demonstrate_basic_allocation();
    demonstrate_dynamic_array();
    demonstrate_memory_pool();

    return 0;
}

void demonstrate_basic_allocation() {
    printf("1. Basic Memory Allocation\n");

    // malloc - allocate uninitialized memory
    int* arr1 = (int*)malloc(5 * sizeof(int));
    if (!arr1) {
        printf("malloc failed!\n");
        return;
    }

    printf("Allocated array with malloc:\n");
    for (int i = 0; i < 5; i++) {
        arr1[i] = i * 10;
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // calloc - allocate and initialize to zero
    int* arr2 = (int*)calloc(5, sizeof(int));
    if (!arr2) {
        printf("calloc failed!\n");
        free(arr1);
        return;
    }

    printf("Allocated array with calloc (initialized to 0):\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    // realloc - resize allocated memory
    arr1 = (int*)realloc(arr1, 10 * sizeof(int));
    if (!arr1) {
        printf("realloc failed!\n");
        free(arr2);
        return;
    }

    printf("Reallocated array to size 10:\n");
    for (int i = 5; i < 10; i++) {
        arr1[i] = i * 10;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // Free memory
    free(arr1);
    free(arr2);
    printf("Memory freed\n\n");
}

void dynamic_array_init(DynamicArray* arr) {
    arr->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    if (!arr->data) {
        printf("Failed to initialize dynamic array!\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
}

void dynamic_array_add(DynamicArray* arr, int value) {
    if (arr->size >= arr->capacity) {
        // Double the capacity
        size_t new_capacity = arr->capacity * 2;
        int* new_data = (int*)realloc(arr->data, new_capacity * sizeof(int));

        if (!new_data) {
            printf("Failed to resize dynamic array!\n");
            return;
        }

        arr->data = new_data;
        arr->capacity = new_capacity;
        printf("Array resized to capacity %zu\n", new_capacity);
    }

    arr->data[arr->size++] = value;
}

void dynamic_array_remove(DynamicArray* arr, size_t index) {
    if (index >= arr->size) {
        printf("Invalid index!\n");
        return;
    }

    // Shift elements left
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
}

void dynamic_array_free(DynamicArray* arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void dynamic_array_print(const DynamicArray* arr) {
    printf("Dynamic Array (size: %zu, capacity: %zu): [",
           arr->size, arr->capacity);

    for (size_t i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) printf(", ");
    }
    printf("]\n");
}

void demonstrate_dynamic_array() {
    printf("2. Dynamic Array Implementation\n");

    DynamicArray arr;
    dynamic_array_init(&arr);

    printf("Adding elements to dynamic array:\n");
    for (int i = 1; i <= 10; i++) {
        dynamic_array_add(&arr, i * 5);
        dynamic_array_print(&arr);
    }

    printf("\nRemoving element at index 3:\n");
    dynamic_array_remove(&arr, 3);
    dynamic_array_print(&arr);

    dynamic_array_free(&arr);
    printf("Dynamic array freed\n\n");
}

MemoryPool* memory_pool_create(size_t size) {
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    pool->pool = malloc(size);
    if (!pool->pool) {
        free(pool);
        return NULL;
    }

    pool->pool_size = size;
    pool->used = 0;
    pool->free_list = pool->pool;

    return pool;
}

void* memory_pool_alloc(MemoryPool* pool, size_t size) {
    if (pool->used + size > pool->pool_size) {
        return NULL;  // Not enough space
    }

    void* ptr = (char*)pool->pool + pool->used;
    pool->used += size;

    return ptr;
}

void memory_pool_free(MemoryPool* pool, void* ptr) {
    // Simple pool doesn't support individual deallocation
    // In a real implementation, you'd need a more complex free list
    (void)pool;
    (void)ptr;
}

void memory_pool_destroy(MemoryPool* pool) {
    if (pool) {
        free(pool->pool);
        free(pool);
    }
}

void demonstrate_memory_pool() {
    printf("3. Memory Pool Implementation\n");

    MemoryPool* pool = memory_pool_create(MEMORY_POOL_SIZE);
    if (!pool) {
        printf("Failed to create memory pool!\n");
        return;
    }

    printf("Memory pool created (size: %zu bytes)\n", MEMORY_POOL_SIZE);

    // Allocate from pool
    int* num1 = (int*)memory_pool_alloc(pool, sizeof(int));
    if (num1) {
        *num1 = 42;
        printf("Allocated int: %d\n", *num1);
    }

    char* str = (char*)memory_pool_alloc(pool, 20 * sizeof(char));
    if (str) {
        strcpy(str, "Hello from pool!");
        printf("Allocated string: %s\n", str);
    }

    printf("Pool usage: %zu/%zu bytes\n", pool->used, pool->pool_size);

    memory_pool_destroy(pool);
    printf("Memory pool destroyed\n\n");
}
```

## 📊 Test Cases

### Test Case 1: Basic Allocation
```
Expected Output:
Allocated array with malloc:
0 10 20 30 40
Allocated array with calloc (initialized to 0):
0 0 0 0 0
Reallocated array to size 10:
0 10 20 30 40 50 60 70 80 90
Memory freed
```

### Test Case 2: Dynamic Array
```
Expected Output:
Adding elements to dynamic array:
Dynamic Array (size: 1, capacity: 4): [5]
Dynamic Array (size: 2, capacity: 4): [5, 10]
...
Array resized to capacity 8
Dynamic Array (size: 5, capacity: 8): [5, 10, 15, 20, 25]
```

### Test Case 3: Memory Pool
```
Expected Output:
Memory pool created (size: 1024 bytes)
Allocated int: 42
Allocated string: Hello from pool!
Pool usage: 24/1024 bytes
Memory pool destroyed
```

## 🔍 Explanation

1. **malloc()**: Allocates uninitialized memory
2. **calloc()**: Allocates and initializes memory to zero
3. **realloc()**: Resizes previously allocated memory
4. **free()**: Deallocates memory
5. **Dynamic Arrays**: Arrays that can grow/shrink at runtime
6. **Memory Pools**: Pre-allocated memory for efficient allocation

## 🎯 Key Concepts Covered

- Dynamic memory allocation functions
- Memory management and cleanup
- Dynamic arrays and resizing
- Memory pool implementation
- Error handling for allocation failures
- Memory leak prevention

## 🚀 Extensions

1. Implement garbage collection
2. Add memory defragmentation
3. Create thread-safe memory allocator
4. Add memory usage profiling