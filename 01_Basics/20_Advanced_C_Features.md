# 🚀 Lesson 20: Advanced C Features
## Mastering Sophisticated C Programming Techniques

---

## 🎯 Learning Objectives

- Master function pointers and callback mechanisms
- Understand variable argument functions
- Learn advanced preprocessor techniques
- Implement inline functions and optimizations
- Use volatile and restrict keywords effectively

---

## 📖 Advanced C Concepts Kya Hain?

**Advanced C features** system programming, embedded development, aur high-performance applications ke liye powerful capabilities provide karte hain. In features ko carefully understand aur properly use karna zaroori hai.

### **Modern C Standards Overview**
- **C89/C90**: Original ANSI/ISO standard
- **C99**: Major update with new features
- **C11**: Concurrency, security, multi-threading support
- **C18**: Bug fixes and clarifications
- **C23**: Latest standard (upcoming features)

---

## 🎯 Function Pointers and Callbacks

### **1. Basic Function Pointers**
```c
#include <stdio.h>

// Function pointer declaration
typedef int (*MathOperation)(int, int);

// Functions to be pointed to
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    // Declare function pointer
    MathOperation operation;

    // Point to different functions
    operation = add;
    printf("10 + 5 = %d\n", operation(10, 5));

    operation = multiply;
    printf("10 * 5 = %d\n", operation(10, 5));

    return 0;
}
```

### **2. Function Pointer Arrays**
```c
#include <stdio.h>

#define NUM_OPERATIONS 4

typedef int (*Operation)(int, int);

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    // Array of function pointers
    Operation operations[NUM_OPERATIONS] = {add, subtract, multiply, divide};
    char *names[] = {"Add", "Subtract", "Multiply", "Divide"};

    int a = 20, b = 4;

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        printf("%s(%d, %d) = %d\n", names[i], a, b, operations[i](a, b));
    }

    return 0;
}
```

### **3. Function Pointers as Arguments**
```c
#include <stdio.h>

typedef int (*Comparator)(int, int);

// Comparison functions
int ascending(int a, int b) { return a - b; }
int descending(int a, int b) { return b - a; }

// Sort function with callback
void bubble_sort(int arr[], int size, Comparator compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(arr[j], arr[j + 1]) > 0) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    print_array(arr, size);

    bubble_sort(arr, size, ascending);
    printf("Sorted ascending: ");
    print_array(arr, size);

    bubble_sort(arr, size, descending);
    printf("Sorted descending: ");
    print_array(arr, size);

    return 0;
}
```

### **4. Callback Systems**
```c
#include <stdio.h>
#include <stdlib.h>

// Event types
typedef enum {
    EVENT_CLICK,
    EVENT_HOVER,
    EVENT_KEYPRESS
} EventType;

// Callback function type
typedef void (*EventCallback)(EventType, void*);

// Event handler structure
typedef struct {
    EventType type;
    EventCallback callback;
    void* user_data;
} EventHandler;

#define MAX_HANDLERS 10
EventHandler handlers[MAX_HANDLERS];
int handler_count = 0;

// Register event handler
void register_handler(EventType type, EventCallback callback, void* user_data) {
    if (handler_count < MAX_HANDLERS) {
        handlers[handler_count].type = type;
        handlers[handler_count].callback = callback;
        handlers[handler_count].user_data = user_data;
        handler_count++;
    }
}

// Trigger event
void trigger_event(EventType type, void* event_data) {
    for (int i = 0; i < handler_count; i++) {
        if (handlers[i].type == type) {
            handlers[i].callback(type, event_data);
        }
    }
}

// Sample callback functions
void on_click(EventType type, void* data) {
    printf("Click event triggered with data: %s\n", (char*)data);
}

void on_hover(EventType type, void* data) {
    printf("Hover event triggered\n");
}

void on_keypress(EventType type, void* data) {
    printf("Key pressed: %c\n", *(char*)data);
}

int main() {
    // Register handlers
    register_handler(EVENT_CLICK, on_click, "Button clicked");
    register_handler(EVENT_HOVER, on_hover, NULL);
    register_handler(EVENT_KEYPRESS, on_keypress, NULL);

    // Trigger events
    trigger_event(EVENT_CLICK, "Button clicked");
    trigger_event(EVENT_HOVER, NULL);

    char key = 'A';
    trigger_event(EVENT_KEYPRESS, &key);

    return 0;
}
```

### **5. Advanced Function Pointer Techniques**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generic function pointer for any return type and arguments
typedef void (*GenericFunction)(void);

// Function registry
#define MAX_FUNCTIONS 100
typedef struct {
    char name[64];
    GenericFunction function;
    const char* description;
} FunctionRegistry;

FunctionRegistry function_registry[MAX_FUNCTIONS];
int function_count = 0;

// Register a function
void register_function(const char* name, GenericFunction func, const char* desc) {
    if (function_count < MAX_FUNCTIONS) {
        strncpy(function_registry[function_count].name, name, sizeof(function_registry[function_count].name) - 1);
        function_registry[function_count].function = func;
        function_registry[function_count].description = desc;
        function_count++;
    }
}

// Find and call a function by name
void call_function(const char* name) {
    for (int i = 0; i < function_count; i++) {
        if (strcmp(function_registry[i].name, name) == 0) {
            printf("Calling function: %s\n", name);
            printf("Description: %s\n", function_registry[i].description);
            function_registry[i].function();
            return;
        }
    }
    printf("Function '%s' not found\n", name);
}

// Sample functions to register
void greet_english() {
    printf("Hello, World!\n");
}

void greet_hindi() {
    printf("Namaste, Duniya!\n");
}

void greet_spanish() {
    printf("¡Hola, Mundo!\n");
}

void show_time() {
    time_t now = time(NULL);
    printf("Current time: %s", ctime(&now));
}

int main() {
    // Register functions
    register_function("english", (GenericFunction)greet_english, "Greet in English");
    register_function("hindi", (GenericFunction)greet_hindi, "Hindi mein greet karo");
    register_function("spanish", (GenericFunction)greet_spanish, "Saludar en español");
    register_function("time", (GenericFunction)show_time, "Show current time");

    // Call functions by name
    call_function("hindi");
    call_function("time");
    call_function("english");

    return 0;
}
```

### **6. C11/C18 Features and Modern C**
```c
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>  // C11 threads
#include <stdatomic.h>  // C11 atomics
#include <stdnoreturn.h>  // C11 noreturn

// C11: Generic selections
#define print_value(X) _Generic((X), \
    int: printf("Integer: %d\n", X), \
    float: printf("Float: %.2f\n", X), \
    double: printf("Double: %.2f\n", X), \
    char*: printf("String: %s\n", X), \
    default: printf("Unknown type\n") \
)

// C11: Static assertions
_Static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
_Static_assert(__STDC_VERSION__ >= 201112L, "C11 or later required");

// C11: Thread-local storage
_Thread_local int thread_counter = 0;

// C11: Atomic variables
atomic_int shared_counter = ATOMIC_VAR_INIT(0);

// C11: Noreturn functions
noreturn void fatal_error(const char* message) {
    fprintf(stderr, "Fatal error: %s\n", message);
    exit(EXIT_FAILURE);
}

// C11: Alignment
struct AlignedStruct {
    int value;
} __attribute__((aligned(16)));  // GCC extension, C23 has alignas

// C11: Anonymous unions/structs
struct DataContainer {
    int type;
    union {
        int int_value;
        float float_value;
        char* string_value;
    };  // Anonymous union
};

// Thread function for C11 threads
int thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d started\n", thread_id);

    // Use thread-local variable
    thread_counter++;
    printf("Thread %d counter: %d\n", thread_id, thread_counter);

    // Use atomic operations
    atomic_fetch_add(&shared_counter, 1);
    printf("Shared counter: %d\n", atomic_load(&shared_counter));

    return 0;
}

int main() {
    // Test generic selection
    print_value(42);
    print_value(3.14f);
    print_value("Hello");

    // Test anonymous union
    struct DataContainer data;
    data.type = 1;
    data.int_value = 100;
    printf("Data value: %d\n", data.int_value);

    // Test C11 threads
    thrd_t thread1, thread2;
    int id1 = 1, id2 = 2;

    if (thrd_create(&thread1, thread_function, &id1) != thrd_success) {
        fatal_error("Failed to create thread 1");
    }

    if (thrd_create(&thread2, thread_function, &id2) != thrd_success) {
        fatal_error("Failed to create thread 2");
    }

    // Wait for threads to complete
    thrd_join(thread1, NULL);
    thrd_join(thread2, NULL);

    printf("All threads completed\n");
    printf("Final shared counter: %d\n", atomic_load(&shared_counter));

    return 0;
}
```

### **7. Advanced Memory Management**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom memory pool
#define POOL_SIZE 1024
#define BLOCK_SIZE 64

typedef struct MemoryBlock {
    struct MemoryBlock* next;
    char data[BLOCK_SIZE];
} MemoryBlock;

typedef struct {
    MemoryBlock* free_list;
    char pool[POOL_SIZE * sizeof(MemoryBlock)];
    size_t used_blocks;
} MemoryPool;

// Initialize memory pool
void init_pool(MemoryPool* pool) {
    pool->free_list = NULL;
    pool->used_blocks = 0;

    // Initialize free list
    for (size_t i = 0; i < POOL_SIZE; i++) {
        MemoryBlock* block = (MemoryBlock*)&pool->pool[i * sizeof(MemoryBlock)];
        block->next = pool->free_list;
        pool->free_list = block;
    }
}

// Allocate from pool
void* pool_alloc(MemoryPool* pool, size_t size) {
    if (size > BLOCK_SIZE || pool->free_list == NULL) {
        return NULL;  // No suitable block available
    }

    MemoryBlock* block = pool->free_list;
    pool->free_list = block->next;
    pool->used_blocks++;

    return block->data;
}

// Free to pool
void pool_free(MemoryPool* pool, void* ptr) {
    if (ptr == NULL) return;

    // Find the block containing this pointer
    for (size_t i = 0; i < POOL_SIZE; i++) {
        MemoryBlock* block = (MemoryBlock*)&pool->pool[i * sizeof(MemoryBlock)];
        if (block->data == ptr) {
            // Return to free list
            block->next = pool->free_list;
            pool->free_list = block;
            pool->used_blocks--;
            return;
        }
    }
}

// Memory arena (region-based allocation)
typedef struct {
    char* buffer;
    size_t size;
    size_t used;
} MemoryArena;

void init_arena(MemoryArena* arena, size_t size) {
    arena->buffer = (char*)malloc(size);
    arena->size = size;
    arena->used = 0;
}

void* arena_alloc(MemoryArena* arena, size_t size) {
    if (arena->used + size > arena->size) {
        return NULL;  // Out of memory
    }

    void* ptr = &arena->buffer[arena->used];
    arena->used += size;
    return ptr;
}

void reset_arena(MemoryArena* arena) {
    arena->used = 0;
}

void destroy_arena(MemoryArena* arena) {
    free(arena->buffer);
    arena->buffer = NULL;
    arena->size = 0;
    arena->used = 0;
}

// Reference counting
typedef struct {
    int ref_count;
    void* data;
    void (*destroy)(void*);  // Custom destructor
} RefCounted;

RefCounted* create_ref_counted(void* data, void (*destroy_func)(void*)) {
    RefCounted* ref = (RefCounted*)malloc(sizeof(RefCounted));
    if (ref == NULL) return NULL;

    ref->ref_count = 1;
    ref->data = data;
    ref->destroy = destroy_func;

    return ref;
}

void retain(RefCounted* ref) {
    if (ref != NULL) {
        ref->ref_count++;
    }
}

void release(RefCounted* ref) {
    if (ref == NULL) return;

    ref->ref_count--;
    if (ref->ref_count <= 0) {
        if (ref->destroy) {
            ref->destroy(ref->data);
        }
        free(ref);
    }
}

int main() {
    // Test memory pool
    MemoryPool pool;
    init_pool(&pool);

    char* str1 = (char*)pool_alloc(&pool, 32);
    char* str2 = (char*)pool_alloc(&pool, 32);

    if (str1 && str2) {
        strcpy(str1, "Hello from pool!");
        strcpy(str2, "Another string");
        printf("Pool strings: %s, %s\n", str1, str2);

        pool_free(&pool, str1);
        pool_free(&pool, str2);
    }

    // Test memory arena
    MemoryArena arena;
    init_arena(&arena, 1024);

    int* numbers = (int*)arena_alloc(&arena, 10 * sizeof(int));
    if (numbers) {
        for (int i = 0; i < 10; i++) {
            numbers[i] = i * 2;
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    reset_arena(&arena);  // All allocations freed at once
    destroy_arena(&arena);

    // Test reference counting
    int* data = (int*)malloc(sizeof(int));
    *data = 42;

    RefCounted* ref = create_ref_counted(data, free);
    printf("Reference count: %d\n", ref->ref_count);

    retain(ref);
    printf("After retain: %d\n", ref->ref_count);

    release(ref);
    printf("After first release: %d\n", ref->ref_count);

    release(ref);  // This will free the data
    printf("After second release: object freed\n");

    return 0;
}
```

---

## 📊 Variable Arguments (va_list)

### **1. Basic Variable Arguments**
```c
#include <stdio.h>
#include <stdarg.h>

// Function with variable arguments
int sum(int count, ...) {
    va_list args;
    int total = 0;

    va_start(args, count);  // Initialize va_list

    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);  // Get next argument
    }

    va_end(args);  // Clean up
    return total;
}

int main() {
    printf("Sum of 1, 2, 3: %d\n", sum(3, 1, 2, 3));
    printf("Sum of 5, 10, 15, 20: %d\n", sum(4, 5, 10, 15, 20));
    printf("Sum of single number 42: %d\n", sum(1, 42));

    return 0;
}
```

### **2. Advanced Variable Arguments**
```c
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// Print function with variable arguments
void print_values(const char* format, ...) {
    va_list args;
    va_start(args, format);

    const char* ptr = format;
    while (*ptr) {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr) {
                case 'd':
                    printf("%d", va_arg(args, int));
                    break;
                case 'f':
                    printf("%.2f", va_arg(args, double));
                    break;
                case 's':
                    printf("%s", va_arg(args, char*));
                    break;
                case 'c':
                    printf("%c", va_arg(args, int));
                    break;
                default:
                    printf("%%%c", *ptr);
                    break;
            }
        } else {
            printf("%c", *ptr);
        }
        ptr++;
    }

    va_end(args);
    printf("\n");
}

// Average function with variable arguments
double average(int count, ...) {
    va_list args;
    double sum = 0.0;

    va_start(args, count);
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);
    }
    va_end(args);

    return count > 0 ? sum / count : 0.0;
}

int main() {
    print_values("Name: %s, Age: %d, Height: %.1f",
                 "Alice", 25, 5.6);

    print_values("Character: %c, Number: %d",
                 'A', 42);

    printf("Average of 1.5, 2.5, 3.5: %.2f\n",
           average(3, 1.5, 2.5, 3.5));

    return 0;
}
```

### **3. Type-Safe Variable Arguments**
```c
#include <stdio.h>
#include <stdarg.h>

// Structure to hold different types
typedef struct {
    enum { INT_TYPE, DOUBLE_TYPE, STRING_TYPE } type;
    union {
        int int_val;
        double double_val;
        char* string_val;
    } value;
} Variant;

// Function to print variants
void print_variant(const char* format, ...) {
    va_list args;
    va_start(args, format);

    const char* ptr = format;
    while (*ptr) {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr) {
                case 'v': {
                    Variant* var = va_arg(args, Variant*);
                    switch (var->type) {
                        case INT_TYPE:
                            printf("%d", var->value.int_val);
                            break;
                        case DOUBLE_TYPE:
                            printf("%.2f", var->value.double_val);
                            break;
                        case STRING_TYPE:
                            printf("%s", var->value.string_val);
                            break;
                    }
                    break;
                }
                default:
                    printf("%%%c", *ptr);
                    break;
            }
        } else {
            printf("%c", *ptr);
        }
        ptr++;
    }

    va_end(args);
    printf("\n");
}

int main() {
    Variant v1 = {INT_TYPE, {.int_val = 42}};
    Variant v2 = {DOUBLE_TYPE, {.double_val = 3.14}};
    Variant v3 = {STRING_TYPE, {.string_val = "Hello"}};

    print_variant("Values: %v, %v, %v", &v1, &v2, &v3);

    return 0;
}
```

---

## 🔧 Advanced Preprocessor Techniques

### **1. Macro Metaprogramming**
```c
#include <stdio.h>

// String concatenation
#define CONCAT(a, b) a##b
#define CREATE_VAR(name) int CONCAT(var_, name)

// Stringification
#define STRINGIFY(x) #x
#define PRINT_VAR(x) printf(#x " = %d\n", x)

// Conditional macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Loop unrolling macro
#define UNROLL_LOOP(n) \
    for (int i = 0; i < n; i++) { \
        printf("Iteration %d\n", i); \
    }

int main() {
    CREATE_VAR(counter) = 10;
    printf("var_counter = %d\n", var_counter);

    int value = 42;
    PRINT_VAR(value);

    printf("Max of 10, 20: %d\n", MAX(10, 20));
    printf("Min of 10, 20: %d\n", MIN(10, 20));

    UNROLL_LOOP(3);

    return 0;
}
```

### **2. Token Pasting and Advanced Macros**
```c
#include <stdio.h>

// Generic swap macro
#define SWAP(a, b) do { \
    typeof(a) temp = a; \
    a = b; \
    b = temp; \
} while(0)

// Array size macro
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Foreach macro
#define FOREACH(item, array, size) \
    for (size_t i = 0, item = array[0]; i < size; item = array[++i])

// Function name macro
#define FUNC_NAME __func__

void test_function() {
    printf("Function name: %s\n", FUNC_NAME);
}

int main() {
    int x = 10, y = 20;
    printf("Before swap: x=%d, y=%d\n", x, y);
    SWAP(x, y);
    printf("After swap: x=%d, y=%d\n", x, y);

    int arr[] = {1, 2, 3, 4, 5};
    printf("Array size: %zu\n", ARRAY_SIZE(arr));

    printf("Array elements: ");
    FOREACH(item, arr, ARRAY_SIZE(arr)) {
        printf("%d ", item);
    }
    printf("\n");

    test_function();

    return 0;
}
```

### **3. Conditional Compilation with Macros**
```c
#include <stdio.h>

#define DEBUG 1
#define VERSION "1.2.3"
#define PLATFORM "Linux"

// Debug logging macro
#if DEBUG
    #define LOG(message) printf("[DEBUG] %s:%d: %s\n", __FILE__, __LINE__, message)
    #define LOGF(format, ...) printf("[DEBUG] %s:%d: " format "\n", __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG(message)
    #define LOGF(format, ...)
#endif

// Platform-specific code
#ifdef PLATFORM
    #if PLATFORM == "Windows"
        #define PATH_SEPARATOR "\\"
    #elif PLATFORM == "Linux" || PLATFORM == "macOS"
        #define PATH_SEPARATOR "/"
    #else
        #define PATH_SEPARATOR "/"
    #endif
#endif

int main() {
    LOG("Program started");
    LOGF("Version: %s", VERSION);
    LOGF("Platform: %s", PLATFORM);

    printf("Path separator: %s\n", PATH_SEPARATOR);

    // Conditional compilation based on version
    #if VERSION >= "1.0.0"
        printf("New features available\n");
    #endif

    return 0;
}
```

---

## ⚡ Inline Functions and Optimizations

### **1. Inline Functions**
```c
#include <stdio.h>

// Inline function
inline int square(int x) {
    return x * x;
}

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function that benefits from inlining
inline int is_even(int n) {
    return (n & 1) == 0;
}

int main() {
    int num = 5;
    printf("Square of %d: %d\n", num, square(num));
    printf("Max of 10, 20: %d\n", max(10, 20));
    printf("Is %d even? %s\n", num, is_even(num) ? "Yes" : "No");

    return 0;
}
```

### **2. Static Inline Functions**
```c
#include <stdio.h>

// Static inline function (internal linkage)
static inline int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Header file function
static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    printf("Factorial of 5: %d\n", factorial(5));

    int x = 10, y = 20;
    printf("Before swap: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After swap: x=%d, y=%d\n", x, y);

    return 0;
}
```

---

## 🔒 Volatile and Restrict Keywords

### **1. Volatile Keyword**
```c
#include <stdio.h>

// Volatile variables
volatile int flag = 0;
volatile int* volatile_ptr;

// Function that might be called by interrupt
void interrupt_handler() {
    flag = 1;  // This change must be visible to main loop
}

int main() {
    // Hardware register access
    volatile int* hardware_register = (volatile int*)0x12345678;

    // Memory-mapped I/O
    volatile char* uart_status = (volatile char*)0x40001000;

    printf("Waiting for interrupt...\n");

    while (!flag) {
        // Busy wait - compiler won't optimize this away
        // because flag is volatile
    }

    printf("Interrupt received!\n");

    return 0;
}
```

### **2. Restrict Keyword**
```c
#include <stdio.h>
#include <string.h>

// Function with restrict pointers
void copy_data(char* restrict dest, const char* restrict src, size_t n) {
    // Compiler can assume dest and src don't overlap
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Optimized memory copy
void* memcpy_optimized(void* restrict dest, const void* restrict src, size_t n) {
    char* restrict d = dest;
    const char* restrict s = src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}

int main() {
    char buffer1[100] = "Hello, World!";
    char buffer2[100];

    copy_data(buffer2, buffer1, strlen(buffer1) + 1);
    printf("Copied: %s\n", buffer2);

    return 0;
}
```

### **3. Combined Volatile and Restrict**
```c
#include <stdio.h>

// Memory-mapped device with restrict
void write_to_device(volatile int* restrict device_register, int value) {
    *device_register = value;  // Volatile write
}

// DMA transfer function
void dma_transfer(volatile void* restrict dest,
                  const void* restrict src,
                  size_t size) {
    // Compiler can optimize knowing buffers don't overlap
    volatile char* d = (volatile char*)dest;
    const char* s = (const char*)src;

    for (size_t i = 0; i < size; i++) {
        d[i] = s[i];
    }
}

int main() {
    // Example usage
    volatile int device_reg;
    write_to_device(&device_reg, 42);

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Use Function Pointers Wisely**
```c
// ✅ Good: Clear purpose
typedef void (*Logger)(const char* message);
void file_logger(const char* message) { /* ... */ }
void console_logger(const char* message) { /* ... */ }

// ❌ Bad: Overusing function pointers
typedef int (*ComplexOperation)(int, int, char*, void*);
// This becomes hard to maintain
```

### **2. Handle Variable Arguments Carefully**
```c
// ✅ Good: Validate argument count
int sum(int count, ...) {
    if (count <= 0) return 0;

    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

// ❌ Bad: No validation
int bad_sum(int count, ...) {
    va_list args;
    va_start(args, count);
    // What if count is wrong?
}
```

### **3. Use Volatile for Hardware Access**
```c
// ✅ Good: Hardware registers
volatile unsigned int* gpio_port = (volatile unsigned int*)0x40020000;

// ✅ Good: Shared variables in multi-threaded code
volatile int shared_counter = 0;

// ❌ Bad: Unnecessary volatile
volatile int normal_variable = 0;  // Slows down operations
```

### **4. Inline Functions for Small Operations**
```c
// ✅ Good candidates for inline
inline int is_power_of_two(int n) { return (n & (n - 1)) == 0; }
inline double deg_to_rad(double deg) { return deg * 3.14159 / 180.0; }

// ❌ Bad candidates for inline
inline void complex_algorithm() { /* 100 lines of code */ }
```

---

## 🐛 Common Mistakes

### **1. Incorrect Function Pointer Usage**
```c
// Wrong
int (*func_ptr)(int, int);
func_ptr = add;  // add is not defined
func_ptr(5, 3);  // Crash

// Correct
int add(int a, int b) { return a + b; }
int (*func_ptr)(int, int) = add;
int result = func_ptr(5, 3);
```

### **2. Variable Arguments Without va_end**
```c
// Wrong - memory leak
int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    // Forgot va_end(args);
    return total;
}

// Correct
int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}
```

### **3. Volatile Misuse**
```c
// Wrong - volatile doesn't make operations atomic
volatile int counter = 0;
counter++;  // Not thread-safe despite volatile

// Correct - use proper synchronization
// (This would require mutexes or atomic operations)
```

### **4. Restrict Violations**
```c
// Wrong - overlapping memory regions
char buffer[100];
copy_data(buffer + 5, buffer, 10);  // Overlap!

// Correct - ensure no overlap
char src[100] = "Hello";
char dest[100];
copy_data(dest, src, strlen(src) + 1);
```

---

## 📝 Practice Exercises

### **Exercise 1: Function Pointers**
- Create a calculator using function pointer arrays
- Implement a callback system for event handling
- Build a plugin system using function pointers

### **Exercise 2: Variable Arguments**
- Create a printf-like function with variable arguments
- Implement a sum function that accepts any number of arguments
- Build a logging function with formatted output

### **Exercise 3: Advanced Macros**
- Create macros for loop unrolling
- Implement generic swap and comparison macros
- Build debugging and logging macros

### **Exercise 4: System Programming**
- Use volatile for hardware register access
- Implement restrict-qualified functions for performance
- Create inline functions for mathematical operations

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the correct syntax for declaring a function pointer?
a) `int *func_ptr(int, int);`
b) `int (*func_ptr)(int, int);`
c) `int func_ptr*(int, int);`
d) `int (int, int)* func_ptr;`

### **Question 2:**
Which header file is required for variable arguments?
a) `<stdio.h>`
b) `<stdlib.h>`
c) `<stdarg.h>`
d) `<string.h>`

### **Question 3:**
When should you use the volatile keyword?
a) For all variables
b) For hardware registers and shared variables
c) For local variables only
d) Never

### **Question 4:**
What does the restrict keyword tell the compiler?
a) The pointer is read-only
b) The pointer is write-only
c) The memory regions don't overlap
d) The pointer is null

### **Question 5:**
Which is true about inline functions?
a) They always improve performance
b) They force the compiler to inline the function
c) They suggest inlining to the compiler
d) They prevent function calls

---

## 🔗 Additional Resources

### **Advanced C Features**
- [Function Pointers](https://en.cppreference.com/w/c/language/function_pointer)
- [Variable Arguments](https://en.cppreference.com/w/c/variadic)
- [Inline Functions](https://en.cppreference.com/w/c/language/inline)
- [Volatile and Restrict](https://en.cppreference.com/w/c/language/restrict)

### **Further Reading**
- [C Programming: A Modern Approach](https://www.amazon.com/Programming-Modern-Approach-2nd/dp/0393979504)
- [Expert C Programming](https://www.amazon.com/Expert-Programming-Peter-van-Linden/dp/0131774298)
- [C Traps and Pitfalls](https://www.amazon.com/Traps-Pitfalls-Andrew-Koenig/dp/0201179288)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ Function pointers and callback systems
- ✅ Variable argument functions
- ✅ Advanced preprocessor techniques
- ✅ Inline functions and optimizations
- ✅ Volatile and restrict keywords

**Next Lesson Preview:**
- Final project implementation
- Code optimization techniques
- Best practices and coding standards
- Professional C development

---

**🚀 Ready to build your final project?**

[⬅️ Previous: Data Structures](19_Data_Structures.md) | [Next: Final Project ➡️](21_Final_Project.md)