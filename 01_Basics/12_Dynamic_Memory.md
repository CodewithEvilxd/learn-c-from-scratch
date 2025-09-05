# 💾 Lesson 12: Dynamic Memory Allocation in C
## Managing Memory at Runtime

---

## 🎯 Learning Objectives

- Understand dynamic memory allocation functions
- Master heap vs stack memory concepts
- Learn memory leak prevention techniques
- Debug memory-related errors
- Implement efficient memory management

---

## 📖 Dynamic Memory Allocation Kya Hai?

**Dynamic memory allocation** programs ko runtime pe operating system se memory request karne deta hai, instead of compile time pe fixed memory requirements.

### **Dynamic Memory Kyun Use Karein?**
- **Variable-sized data**: Arrays jinka size runtime pe decide hota hai
- **Large data structures**: Structures jo stack ke liye bahut bade hain
- **Efficient memory usage**: Sirf jo chahiye allocate karo
- **Data persistence**: Memory function scope ke bahar bhi persist karta hai

### **Advanced Memory Concepts**
- **Memory pools aur custom allocators**
- **Memory fragmentation handling**
- **Garbage collection simulation**
- **Memory profiling aur optimization**

---

## 🔧 Memory Allocation Functions

### **1. malloc() - Memory Allocation**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for 5 integers
    int *arr = (int*)malloc(5 * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Use the allocated memory
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Free the allocated memory
    free(arr);
    arr = NULL;  // Good practice

    return 0;
}
```

### **2. calloc() - Contiguous Allocation**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate and initialize memory for 5 integers
    int *arr = (int*)calloc(5, sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // calloc initializes memory to zero
    printf("Initialized values: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);  // Will print 0 0 0 0 0
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return 0;
}
```

### **3. realloc() - Reallocate Memory**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initial allocation
    int *arr = (int*)malloc(5 * sizeof(int));
    if (arr == NULL) return 1;

    // Initialize
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    printf("Original array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Resize to 10 elements
    int *new_arr = (int*)realloc(arr, 10 * sizeof(int));
    if (new_arr == NULL) {
        free(arr);
        return 1;
    }
    arr = new_arr;

    // Initialize new elements
    for (int i = 5; i < 10; i++) {
        arr[i] = i + 1;
    }

    printf("Resized array: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return 0;
}
```

### **4. free() - Deallocate Memory**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) return 1;

    *ptr = 42;
    printf("Value: %d\n", *ptr);

    // Always free allocated memory
    free(ptr);

    // Set pointer to NULL to prevent dangling pointer
    ptr = NULL;

    // This would be dangerous if ptr wasn't NULL
    // *ptr = 100;  // Segmentation fault

    return 0;
}
```

---

## 🏗️ Heap vs Stack Memory

### **Stack Memory**
```c
#include <stdio.h>

void stack_function() {
    int stack_var = 42;  // Allocated on stack
    printf("Stack variable: %d\n", stack_var);
    // Automatically deallocated when function returns
}

int main() {
    stack_function();
    // stack_var is no longer accessible
    return 0;
}
```

### **Heap Memory**
```c
#include <stdio.h>
#include <stdlib.h>

int* heap_function() {
    int *heap_var = (int*)malloc(sizeof(int));  // Allocated on heap
    if (heap_var != NULL) {
        *heap_var = 42;
        printf("Heap variable: %d\n", *heap_var);
    }
    return heap_var;  // Must be freed by caller
}

int main() {
    int *ptr = heap_function();
    if (ptr != NULL) {
        printf("Still accessible: %d\n", *ptr);
        free(ptr);  // Manual deallocation required
        ptr = NULL;
    }
    return 0;
}
```

### **Stack vs Heap Comparison**

| Feature | Stack | Heap |
|---------|-------|------|
| **Allocation** | Automatic | Manual (`malloc`) |
| **Deallocation** | Automatic | Manual (`free`) |
| **Size** | Limited, fixed | Large, flexible |
| **Speed** | Fast | Slower |
| **Lifetime** | Function scope | Program lifetime |
| **Fragmentation** | No | Yes |
| **Thread Safety** | Thread-local | Needs synchronization |

---

## 🔄 Memory Allocation Strategies

### **1. Single Large Allocation**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate one large block
    int *arr = (int*)malloc(1000 * sizeof(int));
    if (arr == NULL) return 1;

    // Use the memory
    for (int i = 0; i < 1000; i++) {
        arr[i] = i;
    }

    free(arr);
    arr = NULL;

    return 0;
}
```

### **2. Multiple Small Allocations**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate multiple small blocks
    int **arr = (int**)malloc(10 * sizeof(int*));
    if (arr == NULL) return 1;

    for (int i = 0; i < 10; i++) {
        arr[i] = (int*)malloc(100 * sizeof(int));
        if (arr[i] == NULL) {
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return 1;
        }
    }

    // Use the 2D array
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 100; j++) {
            arr[i][j] = i * j;
        }
    }

    // Free memory
    for (int i = 0; i < 10; i++) {
        free(arr[i]);
    }
    free(arr);
    arr = NULL;

    return 0;
}
```

### **3. Dynamic Array Implementation**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;

DynamicArray* create_array(size_t initial_capacity) {
    DynamicArray *arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr == NULL) return NULL;

    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->capacity = initial_capacity;
    return arr;
}

int resize_array(DynamicArray *arr, size_t new_capacity) {
    int *new_data = (int*)realloc(arr->data, new_capacity * sizeof(int));
    if (new_data == NULL) return 0;

    arr->data = new_data;
    arr->capacity = new_capacity;
    return 1;
}

void add_element(DynamicArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        if (!resize_array(arr, arr->capacity * 2)) {
            printf("Failed to resize array\n");
            return;
        }
    }
    arr->data[arr->size++] = value;
}

void free_array(DynamicArray *arr) {
    free(arr->data);
    free(arr);
}

int main() {
    DynamicArray *arr = create_array(4);
    if (arr == NULL) return 1;

    for (int i = 0; i < 10; i++) {
        add_element(arr, i * 10);
    }

    printf("Array contents: ");
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");

    free_array(arr);
    return 0;
}
```

### **4. Custom Memory Allocators**

#### **Memory Pool Allocator**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 1024
#define BLOCK_SIZE 64

typedef struct MemoryPool {
    char pool[POOL_SIZE];
    char used[POOL_SIZE / BLOCK_SIZE];  // Bitmap for used blocks
    size_t block_size;
    size_t num_blocks;
} MemoryPool;

MemoryPool* create_pool(size_t block_size) {
    if (block_size == 0 || POOL_SIZE % block_size != 0) {
        return NULL;
    }

    MemoryPool *mp = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (mp == NULL) return NULL;

    mp->block_size = block_size;
    mp->num_blocks = POOL_SIZE / block_size;
    memset(mp->used, 0, sizeof(mp->used));

    return mp;
}

void* pool_alloc(MemoryPool *mp) {
    for (size_t i = 0; i < mp->num_blocks; i++) {
        if (mp->used[i] == 0) {
            mp->used[i] = 1;
            return &mp->pool[i * mp->block_size];
        }
    }
    return NULL;  // No free blocks
}

void pool_free(MemoryPool *mp, void *ptr) {
    if (ptr < (void*)&mp->pool[0] ||
        ptr >= (void*)&mp->pool[POOL_SIZE]) {
        return;  // Invalid pointer
    }

    size_t offset = (char*)ptr - mp->pool;
    size_t block_index = offset / mp->block_size;

    if (block_index < mp->num_blocks) {
        mp->used[block_index] = 0;
    }
}

void destroy_pool(MemoryPool *mp) {
    free(mp);
}

int main() {
    MemoryPool *pool = create_pool(64);
    if (pool == NULL) return 1;

    // Allocate some blocks
    void *ptr1 = pool_alloc(pool);
    void *ptr2 = pool_alloc(pool);
    void *ptr3 = pool_alloc(pool);

    printf("Allocated blocks: %p, %p, %p\n", ptr1, ptr2, ptr3);

    // Use the memory
    strcpy((char*)ptr1, "Hello");
    strcpy((char*)ptr2, "World");
    *(int*)ptr3 = 42;

    printf("Data: %s, %s, %d\n",
           (char*)ptr1, (char*)ptr2, *(int*)ptr3);

    // Free some blocks
    pool_free(pool, ptr2);

    // Allocate again (should reuse freed block)
    void *ptr4 = pool_alloc(pool);
    printf("Reallocated block: %p\n", ptr4);

    destroy_pool(pool);
    return 0;
}
```

#### **Buddy Memory Allocator**
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Simple buddy allocator simulation
#define MIN_BLOCK_SIZE 64
#define MAX_BLOCK_SIZE 1024

typedef struct BuddyBlock {
    size_t size;
    int free;
    struct BuddyBlock *buddy;
    struct BuddyBlock *next;
} BuddyBlock;

BuddyBlock* create_buddy_system(size_t total_size) {
    BuddyBlock *root = (BuddyBlock*)malloc(sizeof(BuddyBlock));
    if (root == NULL) return NULL;

    root->size = total_size;
    root->free = 1;
    root->buddy = NULL;
    root->next = NULL;

    return root;
}

BuddyBlock* find_free_block(BuddyBlock *root, size_t size) {
    BuddyBlock *current = root;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            // Check if we can split
            if (current->size / 2 >= size && current->size / 2 >= MIN_BLOCK_SIZE) {
                // Split the block
                BuddyBlock *buddy = (BuddyBlock*)malloc(sizeof(BuddyBlock));
                if (buddy == NULL) return NULL;

                buddy->size = current->size / 2;
                buddy->free = 1;
                buddy->buddy = current;
                buddy->next = current->next;

                current->size /= 2;
                current->buddy = buddy;
                current->next = buddy;

                continue;  // Try again with smaller block
            } else {
                return current;  // Found suitable block
            }
        }
        current = current->next;
    }

    return NULL;  // No suitable block found
}

void* buddy_alloc(BuddyBlock *root, size_t size) {
    BuddyBlock *block = find_free_block(root, size);
    if (block == NULL) return NULL;

    block->free = 0;
    return (void*)(block + 1);  // Return memory after block header
}

void buddy_free(BuddyBlock *root, void *ptr) {
    if (ptr == NULL) return;

    BuddyBlock *block = (BuddyBlock*)ptr - 1;
    block->free = 1;

    // Try to merge with buddy
    if (block->buddy && block->buddy->free &&
        block->size == block->buddy->size) {
        // Merge blocks
        block->size *= 2;
        block->buddy = block->buddy->buddy;
        free(block->next);
        block->next = block->buddy;
    }
}

int main() {
    BuddyBlock *buddy_system = create_buddy_system(1024);
    if (buddy_system == NULL) return 1;

    // Allocate some memory
    void *ptr1 = buddy_alloc(buddy_system, 128);
    void *ptr2 = buddy_alloc(buddy_system, 256);

    printf("Allocated: %p, %p\n", ptr1, ptr2);

    // Use the memory
    if (ptr1) strcpy((char*)ptr1, "Buddy allocation works!");
    if (ptr2) *(int*)ptr2 = 12345;

    printf("Data: %s, %d\n",
           ptr1 ? (char*)ptr1 : "NULL",
           ptr2 ? *(int*)ptr2 : 0);

    // Free memory
    buddy_free(buddy_system, ptr1);
    buddy_free(buddy_system, ptr2);

    // Cleanup (simplified)
    free(buddy_system);

    return 0;
}
```

#### **Memory Profiling and Tracking**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Memory allocation tracker
typedef struct Allocation {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    time_t timestamp;
    struct Allocation *next;
} Allocation;

static Allocation *allocation_list = NULL;
static size_t total_allocated = 0;
static size_t peak_allocated = 0;

// Debug malloc with tracking
void* debug_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (ptr == NULL) return NULL;

    // Create allocation record
    Allocation *alloc = (Allocation*)malloc(sizeof(Allocation));
    if (alloc == NULL) {
        free(ptr);
        return NULL;
    }

    alloc->ptr = ptr;
    alloc->size = size;
    alloc->file = file;
    alloc->line = line;
    alloc->timestamp = time(NULL);
    alloc->next = allocation_list;

    allocation_list = alloc;
    total_allocated += size;

    if (total_allocated > peak_allocated) {
        peak_allocated = total_allocated;
    }

    printf("Allocated %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
    return ptr;
}

// Debug free with tracking
void debug_free(void *ptr, const char *file, int line) {
    if (ptr == NULL) return;

    // Find allocation record
    Allocation *prev = NULL;
    Allocation *current = allocation_list;

    while (current != NULL) {
        if (current->ptr == ptr) {
            // Remove from list
            if (prev == NULL) {
                allocation_list = current->next;
            } else {
                prev->next = current->next;
            }

            total_allocated -= current->size;
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    printf("Freed %p (%s:%d)\n", ptr, file, line);
    free(ptr);
}

// Memory usage report
void print_memory_report() {
    printf("\n=== Memory Report ===\n");
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Peak allocated: %zu bytes\n", peak_allocated);

    if (allocation_list != NULL) {
        printf("\nUnfreed allocations:\n");
        Allocation *current = allocation_list;
        while (current != NULL) {
            printf("  %p: %zu bytes (%s:%d)\n",
                   current->ptr, current->size,
                   current->file, current->line);
            current = current->next;
        }
    } else {
        printf("No unfreed allocations!\n");
    }
}

// Cleanup tracking (call at program end)
void cleanup_memory_tracking() {
    Allocation *current = allocation_list;
    while (current != NULL) {
        Allocation *temp = current;
        current = current->next;
        free(temp);
    }
    allocation_list = NULL;
}

#define DEBUG_MALLOC(size) debug_malloc(size, __FILE__, __LINE__)
#define DEBUG_FREE(ptr) debug_free(ptr, __FILE__, __LINE__)

int main() {
    // Use debug allocation functions
    int *arr1 = (int*)DEBUG_MALLOC(10 * sizeof(int));
    char *str = (char*)DEBUG_MALLOC(50 * sizeof(char));

    // Use memory
    for (int i = 0; i < 10; i++) {
        arr1[i] = i * 10;
    }
    strcpy(str, "Memory tracking example");

    // Free some memory
    DEBUG_FREE(arr1);

    // Print report
    print_memory_report();

    // Cleanup
    DEBUG_FREE(str);
    cleanup_memory_tracking();

    return 0;
}
```

---

## 🚨 Memory Leaks and Prevention

### **What is a Memory Leak?**
A memory leak occurs when dynamically allocated memory is not properly deallocated, causing the program to consume more and more memory over time.

### **Common Causes of Memory Leaks**
```c
#include <stdio.h>
#include <stdlib.h>

// Leak 1: Forgetting to free
void leak1() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    // Forgot: free(ptr);
}

// Leak 2: Losing pointer reference
void leak2() {
    int *ptr = (int*)malloc(sizeof(int));
    ptr = NULL;  // Lost reference to allocated memory
    // Memory still allocated but inaccessible
}

// Leak 3: Early return without freeing
int leak3() {
    int *ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        return -1;  // Leak: didn't free on error
    }
    // Some processing...
    if (some_condition) {
        return -1;  // Leak: didn't free
    }
    free(ptr);
    return 0;
}
```

### **Memory Leak Prevention**
```c
#include <stdio.h>
#include <stdlib.h>

// ✅ Good: Always free on all paths
int safe_function() {
    int *ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        return -1;
    }

    // Processing...
    *ptr = 42;

    if (some_error_condition) {
        free(ptr);  // Free on error
        return -1;
    }

    free(ptr);  // Free on success
    return 0;
}

// ✅ Better: Use goto for cleanup
int better_function() {
    int *ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        return -1;
    }

    // Processing...
    *ptr = 42;

    if (some_error_condition) {
        goto cleanup;
    }

    // Success path
    free(ptr);
    return 0;

    cleanup:
    free(ptr);
    return -1;
}
```

---

## 🐛 Debugging Memory Errors

### **1. Using Valgrind (Linux)**
```bash
# Install Valgrind
sudo apt install valgrind

# Compile with debug info
gcc -g program.c -o program

# Run with Valgrind
valgrind --leak-check=full ./program

# Check for memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./program
```

### **2. AddressSanitizer (GCC/Clang)**
```bash
# Compile with AddressSanitizer
gcc -fsanitize=address -g program.c -o program

# Run program (will detect memory errors)
./program
```

### **3. Common Memory Errors**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Buffer overflow
    int *arr = (int*)malloc(5 * sizeof(int));
    arr[10] = 42;  // Out of bounds - undefined behavior

    // Use after free
    free(arr);
    *arr = 100;  // Dangling pointer - undefined behavior

    // Double free
    free(arr);  // Already freed - undefined behavior

    // Memory leak
    int *leak = (int*)malloc(sizeof(int));
    // Forgot to free 'leak'

    return 0;
}
```

### **4. Memory Debugging Techniques**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom allocation wrapper for debugging
void* debug_malloc(size_t size, const char* file, int line) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed at %s:%d\n", file, line);
        exit(1);
    }
    printf("Allocated %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
    return ptr;
}

#define DEBUG_MALLOC(size) debug_malloc(size, __FILE__, __LINE__)

// Usage
int main() {
    int *arr = (int*)DEBUG_MALLOC(10 * sizeof(int));
    // Use arr...
    free(arr);
    return 0;
}
```

---

## 🔄 Memory Fragmentation

### **What is Memory Fragmentation?**
Memory fragmentation occurs when free memory is divided into small, non-contiguous blocks, making it difficult to allocate large contiguous memory blocks.

### **Types of Fragmentation**
1. **External Fragmentation**: Free memory scattered in small chunks
2. **Internal Fragmentation**: Allocated more memory than needed

### **Managing Fragmentation**
```c
#include <stdio.h>
#include <stdlib.h>

// Strategy 1: Pre-allocate large blocks
#define POOL_SIZE 1000
static char memory_pool[POOL_SIZE];
static size_t pool_used = 0;

void* pool_alloc(size_t size) {
    if (pool_used + size > POOL_SIZE) {
        return NULL;
    }
    void *ptr = &memory_pool[pool_used];
    pool_used += size;
    return ptr;
}

// Strategy 2: Use memory pools for same-sized objects
typedef struct {
    int data;
    struct Node *next;
} Node;

#define NODE_POOL_SIZE 100
static Node node_pool[NODE_POOL_SIZE];
static int next_free_node = 0;

Node* alloc_node() {
    if (next_free_node >= NODE_POOL_SIZE) {
        return NULL;
    }
    return &node_pool[next_free_node++];
}

void free_node_pool() {
    next_free_node = 0;  // Reset pool
}
```

---

## 🎯 Best Practices

### **1. Always Check Allocation Success**
```c
// ✅ Good
int *arr = (int*)malloc(10 * sizeof(int));
if (arr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
}

// ❌ Bad
int *arr = (int*)malloc(10 * sizeof(int));
// No check - program may crash later
```

### **2. Set Pointers to NULL After Freeing**
```c
// ✅ Good
free(ptr);
ptr = NULL;

// ❌ Bad
free(ptr);
// ptr still points to freed memory
```

### **3. Use Appropriate Allocation Functions**
```c
// Use malloc for single objects
int *num = (int*)malloc(sizeof(int));

// Use calloc for arrays (initializes to zero)
int *arr = (int*)calloc(10, sizeof(int));

// Use realloc to resize
arr = (int*)realloc(arr, 20 * sizeof(int));
```

### **4. Handle Memory Allocation in Loops**
```c
// ✅ Good: Check each allocation
for (int i = 0; i < 10; i++) {
    arr[i] = (int*)malloc(sizeof(int));
    if (arr[i] == NULL) {
        // Free previously allocated memory
        for (int j = 0; j < i; j++) {
            free(arr[j]);
        }
        return 1;
    }
}

// ❌ Bad: No error checking
for (int i = 0; i < 10; i++) {
    arr[i] = (int*)malloc(sizeof(int));
}
```

---

## 🐛 Common Mistakes and Solutions

### **1. Uninitialized Pointers**
```c
// Wrong
int *ptr;
*ptr = 10;  // Crash!

// Correct
int *ptr = (int*)malloc(sizeof(int));
if (ptr != NULL) {
    *ptr = 10;
}
```

### **2. Incorrect Size Calculation**
```c
// Wrong
int *arr = (int*)malloc(10);  // Only 10 bytes for 10 integers?

// Correct
int *arr = (int*)malloc(10 * sizeof(int));
```

### **3. Casting malloc Return Value**
```c
// In C, casting is optional but recommended for clarity
int *arr = (int*)malloc(10 * sizeof(int));

// In C++, casting is required
// int *arr = (int*)malloc(10 * sizeof(int));
```

### **4. sizeof with Pointers**
```c
int *ptr = (int*)malloc(5 * sizeof(int));
// sizeof(ptr) gives pointer size (8 bytes)
// Not the allocated memory size
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic Memory Allocation**
- Create a dynamic array of integers
- Implement a simple stack using dynamic memory
- Build a dynamic string buffer

### **Exercise 2: Memory Management**
- Implement a memory pool allocator
- Create a garbage collector simulation
- Build a dynamic 2D array

### **Exercise 3: Error Handling**
- Add proper error checking to all allocation functions
- Implement cleanup functions for complex data structures
- Create memory usage tracking

### **Exercise 4: Advanced Memory**
- Implement a custom realloc function
- Create a memory defragmentation utility
- Build a memory leak detector

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
Which function initializes allocated memory to zero?
a) `malloc()`
b) `calloc()`
c) `realloc()`
d) `free()`

### **Question 2:**
What happens if `malloc()` returns NULL?
a) Program crashes
b) Memory is allocated anyway
c) Allocation failed, handle error
d) Function returns garbage pointer

### **Question 3:**
Which memory is automatically managed?
a) Heap memory
b) Stack memory
c) Both heap and stack
d) Neither

### **Question 4:**
What is a memory leak?
a) Accessing freed memory
b) Forgetting to free allocated memory
c) Double freeing memory
d) Buffer overflow

### **Question 5:**
Which tool helps detect memory leaks?
a) `gcc`
b) `valgrind`
c) `make`
d) `gdb`

---

## 🔗 Additional Resources

### **Memory Management**
- [Dynamic Memory Allocation](https://en.cppreference.com/w/c/memory)
- [Valgrind Manual](https://valgrind.org/docs/manual/manual.html)
- [AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)

### **Further Reading**
- [C Memory Management](https://www.programiz.com/c-programming/c-dynamic-memory-allocation)
- [Memory Leaks](https://www.geeksforgeeks.org/memory-leak-in-c-and-how-to-avoid-it/)
- [Memory Debugging](https://www.ibm.com/developerworks/aix/library/au-memorydebugging/)

---

## 🎯 Next Steps

**Great job!** You've mastered:
- ✅ Dynamic memory allocation functions
- ✅ Heap vs stack memory concepts
- ✅ Memory leak prevention
- ✅ Memory debugging techniques
- ✅ Memory fragmentation handling

**Next Lesson Preview:**
- File handling basics
- Reading and writing files
- File modes and error handling
- Practical file operations

---

**🚀 Ready to work with files?**

[⬅️ Previous: Structures & Unions](11_Structures_Unions.md) | [Next: File Handling ➡️](13_File_Handling.md)