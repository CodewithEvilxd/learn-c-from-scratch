# 🔧 Lesson 14: Preprocessor in C
## Macros, Directives, and Conditional Compilation

---

## 🎯 Learning Objectives

- Understand preprocessor directives and their usage
- Master macro definition and expansion
- Learn conditional compilation techniques
- Work with header files and multi-file programs
- Understand the complete compilation process

---

## 📖 Preprocessor Kya Hai?

**Preprocessor** ek program hai jo compilation se pehle source code ko process karta hai. Ye directives (instructions starting with `#`) handle karta hai aur source code pe text manipulation perform karta hai.

### **Preprocessor ke Tasks**
1. **File Inclusion** - `#include`
2. **Macro Expansion** - `#define`
3. **Conditional Compilation** - `#ifdef`, `#ifndef`
4. **Line Control** - `#line`
5. **Error Generation** - `#error`
6. **Pragma Directives** - `#pragma`

### **Advanced Preprocessor Concepts**
- **Metaprogramming techniques**
- **Code generation aur templates**
- **Cross-platform compatibility**
- **Build system integration**
- **Debugging aur profiling support**

---

## 📁 File Inclusion

### **1. #include Directive**
```c
// Method 1: Standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Method 2: User-defined headers
#include "myheader.h"

// Method 3: System headers with full path
#include "/usr/include/stdio.h"
```

### **2. Header File Creation**
```c
// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Function declarations
int add(int a, int b);
int multiply(int a, int b);
float divide(int a, int b);

// Constants
#define PI 3.14159
#define MAX_VALUE 100

#endif // MATH_UTILS_H
```

```c
// math_utils.c
#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

float divide(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    }
    return 0.0f;
}
```

```c
// main.c
#include <stdio.h>
#include "math_utils.h"

int main() {
    printf("Add: %d\n", add(5, 3));
    printf("Multiply: %d\n", multiply(5, 3));
    printf("Divide: %.2f\n", divide(10, 3));
    printf("PI: %.5f\n", PI);

    return 0;
}
```

---

## 🔧 Macro Definition

### **1. Object-like Macros**
```c
#include <stdio.h>

// Simple constant macro
#define PI 3.14159
#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0

// String macro
#define GREETING "Hello, World!"
#define AUTHOR "John Doe"

// Expression macro
#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    printf("PI: %.5f\n", PI);
    printf("Square of 5: %d\n", SQUARE(5));
    printf("Cube of 3: %d\n", CUBE(3));
    printf("Max of 10, 20: %d\n", MAX(10, 20));
    printf("Min of 10, 20: %d\n", MIN(10, 20));

    return 0;
}
```

### **2. Function-like Macros**
```c
#include <stdio.h>

// Simple function-like macro
#define ADD(a, b) ((a) + (b))
#define SUBTRACT(a, b) ((a) - (b))

// Multi-line macro
#define PRINT_ARRAY(arr, size) \
    do { \
        printf("Array: "); \
        for (int i = 0; i < size; i++) { \
            printf("%d ", arr[i]); \
        } \
        printf("\n"); \
    } while(0)

// Conditional macro
#define DEBUG_PRINT(x) \
    do { \
        if (DEBUG) { \
            printf("DEBUG: %s = %d\n", #x, x); \
        } \
    } while(0)

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    printf("Add: %d\n", ADD(10, 5));
    printf("Subtract: %d\n", SUBTRACT(10, 5));

    PRINT_ARRAY(arr, 5);

    int value = 42;
    DEBUG_PRINT(value);

    return 0;
}
```

### **3. Advanced Macro Techniques**
```c
#include <stdio.h>

// Token concatenation
#define CONCAT(a, b) a##b
#define CREATE_VAR(name, value) int CONCAT(var_, name) = value

// Stringification
#define STRINGIFY(x) #x
#define PRINT_VAR(x) printf(#x " = %d\n", x)

// Variadic macros (C99)
#define LOG(format, ...) printf(format, __VA_ARGS__)
#define SUM(...) sum_function(__VA_ARGS__, 0)

// Utility macros
#define SWAP(a, b) do { typeof(a) temp = a; a = b; b = temp; } while(0)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Generic programming macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(value, min, max) (MAX(min, MIN(max, value)))

// Loop unrolling macro
#define UNROLL_LOOP(count, body) \
    do { \
        int i = 0; \
        switch (count % 4) { \
            case 3: body; i++; \
            case 2: body; i++; \
            case 1: body; i++; \
        } \
        for (; i < count; i += 4) { \
            body; body; body; body; \
        } \
    } while(0)

int sum_function(int first, ...) {
    int sum = 0;
    va_list args;
    va_start(args, first);

    for (int num = first; num != 0; num = va_arg(args, int)) {
        sum += num;
    }

    va_end(args);
    return sum;
}

int main() {
    // Token concatenation
    CREATE_VAR(counter, 10);
    printf("var_counter = %d\n", var_counter);

    // Stringification
    int age = 25;
    PRINT_VAR(age);

    // Variadic macro
    LOG("Sum of 1, 2, 3, 4: %d\n", SUM(1, 2, 3, 4));

    // Swap macro
    int x = 10, y = 20;
    printf("Before swap: x=%d, y=%d\n", x, y);
    SWAP(x, y);
    printf("After swap: x=%d, y=%d\n", x, y);

    // Clamp macro
    int value = 15;
    int clamped = CLAMP(value, 10, 20);
    printf("Clamped value: %d\n", clamped);

    // Loop unrolling example
    int sum = 0;
    UNROLL_LOOP(10, sum += i);
    printf("Sum with unrolled loop: %d\n", sum);

    return 0;
}
```

### **4. Metaprogramming with Macros**

#### **Code Generation Macros**
```c
#include <stdio.h>

// Generic array operations
#define DEFINE_ARRAY_TYPE(type) \
    typedef struct { \
        type *data; \
        size_t size; \
        size_t capacity; \
    } CONCAT(type, Array); \
    \
    CONCAT(type, Array)* CONCAT(create_, CONCAT(type, _array))(size_t capacity) { \
        CONCAT(type, Array) *arr = (CONCAT(type, Array)*)malloc(sizeof(CONCAT(type, Array))); \
        if (arr == NULL) return NULL; \
        arr->data = (type*)malloc(capacity * sizeof(type)); \
        if (arr->data == NULL) { free(arr); return NULL; } \
        arr->size = 0; \
        arr->capacity = capacity; \
        return arr; \
    } \
    \
    void CONCAT(add_, CONCAT(type, _element))(CONCAT(type, Array) *arr, type value) { \
        if (arr->size >= arr->capacity) { \
            arr->capacity *= 2; \
            arr->data = (type*)realloc(arr->data, arr->capacity * sizeof(type)); \
        } \
        arr->data[arr->size++] = value; \
    }

// Generate array types
DEFINE_ARRAY_TYPE(int)
DEFINE_ARRAY_TYPE(float)
DEFINE_ARRAY_TYPE(char)

int main() {
    // Use generated types
    intArray *int_arr = create_int_array(10);
    floatArray *float_arr = create_float_array(10);
    charArray *char_arr = create_char_array(10);

    // Add elements
    add_int_element(int_arr, 42);
    add_float_element(float_arr, 3.14f);
    add_char_element(char_arr, 'A');

    printf("Integer array size: %zu\n", int_arr->size);
    printf("Float array size: %zu\n", float_arr->size);
    printf("Char array size: %zu\n", char_arr->size);

    // Cleanup
    free(int_arr->data); free(int_arr);
    free(float_arr->data); free(float_arr);
    free(char_arr->data); free(char_arr);

    return 0;
}
```

#### **Cross-Platform Compatibility Macros**
```c
#include <stdio.h>

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
    #define PATH_SEPARATOR "\\"
    #define PLATFORM_NAME "Windows"
#elif defined(__linux__)
    #define PLATFORM_LINUX
    #define PATH_SEPARATOR "/"
    #define PLATFORM_NAME "Linux"
#elif defined(__APPLE__)
    #define PLATFORM_MACOS
    #define PATH_SEPARATOR "/"
    #define PLATFORM_NAME "macOS"
#else
    #define PLATFORM_UNKNOWN
    #define PATH_SEPARATOR "/"
    #define PLATFORM_NAME "Unknown"
#endif

// Compiler detection
#if defined(__GNUC__)
    #define COMPILER_GCC
    #define COMPILER_NAME "GCC"
#elif defined(_MSC_VER)
    #define COMPILER_MSVC
    #define COMPILER_NAME "MSVC"
#elif defined(__clang__)
    #define COMPILER_CLANG
    #define COMPILER_NAME "Clang"
#else
    #define COMPILER_UNKNOWN
    #define COMPILER_NAME "Unknown"
#endif

// Architecture detection
#if defined(__x86_64__) || defined(_M_X64)
    #define ARCHITECTURE_64BIT
    #define ARCH_NAME "x86_64"
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCHITECTURE_32BIT
    #define ARCH_NAME "x86"
#elif defined(__arm__)
    #define ARCHITECTURE_ARM
    #define ARCH_NAME "ARM"
#else
    #define ARCHITECTURE_UNKNOWN
    #define ARCH_NAME "Unknown"
#endif

// Platform-specific function declarations
#ifdef PLATFORM_WINDOWS
    #define SLEEP_MS(ms) Sleep(ms)
    #include <windows.h>
#else
    #define SLEEP_MS(ms) usleep((ms) * 1000)
    #include <unistd.h>
#endif

// Endianness detection
#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1

static int get_endianness() {
    union {
        uint32_t i;
        char c[4];
    } test = {0x01020304};
    return test.c[0] == 1 ? BIG_ENDIAN : LITTLE_ENDIAN;
}

#define ENDIANNESS get_endianness()
#define IS_LITTLE_ENDIAN (ENDIANNESS == LITTLE_ENDIAN)
#define IS_BIG_ENDIAN (ENDIANNESS == BIG_ENDIAN)

int main() {
    printf("Platform: %s\n", PLATFORM_NAME);
    printf("Compiler: %s\n", COMPILER_NAME);
    printf("Architecture: %s\n", ARCH_NAME);

    #ifdef ARCHITECTURE_64BIT
        printf("64-bit system\n");
    #elif defined(ARCHITECTURE_32BIT)
        printf("32-bit system\n");
    #else
        printf("Unknown architecture\n");
    #endif

    printf("Endianness: %s\n", IS_LITTLE_ENDIAN ? "Little Endian" : "Big Endian");

    // Platform-specific sleep
    printf("Sleeping for 1 second...\n");
    SLEEP_MS(1000);
    printf("Done!\n");

    return 0;
}
```

#### **Build System Integration**
```c
// config.h - Configuration header generated by build system
#ifndef CONFIG_H
#define CONFIG_H

// Version information
#define VERSION_MAJOR 1
#define VERSION_MINOR 2
#define VERSION_PATCH 3
#define VERSION_STRING "1.2.3"

// Build configuration
#define BUILD_TYPE "Release"
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__

// Feature flags
#define FEATURE_NETWORKING 1
#define FEATURE_ENCRYPTION 1
#define FEATURE_DEBUG_LOGGING 0

// Platform-specific paths
#ifdef PLATFORM_WINDOWS
    #define DEFAULT_CONFIG_PATH "C:\\ProgramData\\MyApp\\config.ini"
    #define DEFAULT_LOG_PATH "C:\\ProgramData\\MyApp\\logs\\"
#else
    #define DEFAULT_CONFIG_PATH "/etc/myapp/config.ini"
    #define DEFAULT_LOG_PATH "/var/log/myapp/"
#endif

// Compiler-specific optimizations
#ifdef COMPILER_GCC
    #define LIKELY(x) __builtin_expect(!!(x), 1)
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define LIKELY(x) (x)
    #define UNLIKELY(x) (x)
#endif

#endif // CONFIG_H
```

#### **Debugging and Profiling Macros**
```c
#include <stdio.h>
#include <time.h>

// Debug levels
#define DEBUG_LEVEL_NONE 0
#define DEBUG_LEVEL_ERROR 1
#define DEBUG_LEVEL_WARNING 2
#define DEBUG_LEVEL_INFO 3
#define DEBUG_LEVEL_DEBUG 4
#define DEBUG_LEVEL_TRACE 5

#ifndef DEBUG_LEVEL
    #define DEBUG_LEVEL DEBUG_LEVEL_INFO
#endif

// Logging macros
#define LOG_ERROR(format, ...) \
    do { \
        if (DEBUG_LEVEL >= DEBUG_LEVEL_ERROR) { \
            fprintf(stderr, "[ERROR] %s:%d: " format "\n", \
                    __FILE__, __LINE__, ##__VA_ARGS__); \
        } \
    } while(0)

#define LOG_WARNING(format, ...) \
    do { \
        if (DEBUG_LEVEL >= DEBUG_LEVEL_WARNING) { \
            fprintf(stderr, "[WARNING] %s:%d: " format "\n", \
                    __FILE__, __LINE__, ##__VA_ARGS__); \
        } \
    } while(0)

#define LOG_INFO(format, ...) \
    do { \
        if (DEBUG_LEVEL >= DEBUG_LEVEL_INFO) { \
            printf("[INFO] " format "\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define LOG_DEBUG(format, ...) \
    do { \
        if (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG) { \
            printf("[DEBUG] %s:%d: " format "\n", \
                   __FILE__, __LINE__, ##__VA_ARGS__); \
        } \
    } while(0)

// Performance profiling
#define PROFILE_START() \
    clock_t CONCAT(profile_start_, __LINE__) = clock()

#define PROFILE_END(message) \
    do { \
        clock_t end = clock(); \
        double time_taken = ((double)(end - CONCAT(profile_start_, __LINE__))) / CLOCKS_PER_SEC; \
        printf("[PROFILE] %s: %.6f seconds\n", message, time_taken); \
    } while(0)

// Assertion with detailed information
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "[ASSERT] %s:%d: %s\n", \
                    __FILE__, __LINE__, message); \
            abort(); \
        } \
    } while(0)

// Memory debugging
#define MALLOC(size) debug_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) debug_free(ptr, __FILE__, __LINE__)

void* debug_malloc(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        LOG_ERROR("Memory allocation failed at %s:%d", file, line);
        return NULL;
    }
    LOG_DEBUG("Allocated %zu bytes at %p", size, ptr);
    return ptr;
}

void debug_free(void* ptr, const char* file, int line) {
    if (ptr == NULL) {
        LOG_WARNING("Attempted to free NULL pointer at %s:%d", file, line);
        return;
    }
    LOG_DEBUG("Freeing pointer %p", ptr);
    free(ptr);
}

int main() {
    LOG_INFO("Application started");

    // Profiling example
    PROFILE_START();
    for (int i = 0; i < 1000000; i++) {
        // Some work
    }
    PROFILE_END("Loop execution");

    // Memory debugging
    int* arr = (int*)MALLOC(10 * sizeof(int));
    if (arr != NULL) {
        for (int i = 0; i < 10; i++) {
            arr[i] = i * 2;
        }
        FREE(arr);
    }

    // Assertion
    int x = 5;
    ASSERT(x > 0, "x must be positive");

    LOG_INFO("Application finished");
    return 0;
}
```

---

## ❓ Conditional Compilation

### **1. Basic Conditional Compilation**
```c
#include <stdio.h>

// Define a symbol
#define DEBUG 1
#define VERSION 2

int main() {
    printf("Program started\n");

    #ifdef DEBUG
        printf("Debug mode enabled\n");
        printf("Version: %d\n", VERSION);
    #endif

    #ifndef RELEASE
        printf("Not in release mode\n");
    #endif

    return 0;
}
```

### **2. if-elif-else Structure**
```c
#include <stdio.h>

#define OS_WINDOWS 1
#define OS_LINUX 2
#define OS_MAC 3

#define CURRENT_OS OS_LINUX

int main() {
    #if CURRENT_OS == OS_WINDOWS
        printf("Running on Windows\n");
    #elif CURRENT_OS == OS_LINUX
        printf("Running on Linux\n");
    #elif CURRENT_OS == OS_MAC
        printf("Running on macOS\n");
    #else
        printf("Unknown operating system\n");
    #endif

    return 0;
}
```

### **3. Nested Conditions**
```c
#include <stdio.h>

#define DEBUG 1
#define VERBOSE 1
#define LOG_LEVEL 2

int main() {
    #if DEBUG
        printf("Debug build\n");

        #if VERBOSE
            printf("Verbose logging enabled\n");
        #endif

        #if LOG_LEVEL >= 2
            printf("Detailed logging enabled\n");
        #endif
    #else
        printf("Release build\n");
    #endif

    return 0;
}
```

### **4. defined Operator**
```c
#include <stdio.h>

#define FEATURE_A
#define FEATURE_B

int main() {
    #if defined(FEATURE_A) && defined(FEATURE_B)
        printf("Both features enabled\n");
    #endif

    #if defined(FEATURE_A) || defined(FEATURE_C)
        printf("At least one feature enabled\n");
    #endif

    #ifdef FEATURE_A
        printf("Feature A is enabled\n");
    #endif

    #ifndef FEATURE_C
        printf("Feature C is not enabled\n");
    #endif

    return 0;
}
```

---

## 🔗 Multi-File Compilation

### **1. Header File Structure**
```c
// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

// Function declarations
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
float divide(int a, int b);

// Constants
#define PI 3.14159
#define E 2.71828

#endif
```

```c
// calculator.c
#include "calculator.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

float divide(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    }
    return 0.0f;
}
```

```c
// main.c
#include <stdio.h>
#include "calculator.h"

int main() {
    int a = 10, b = 5;

    printf("Add: %d\n", add(a, b));
    printf("Subtract: %d\n", subtract(a, b));
    printf("Multiply: %d\n", multiply(a, b));
    printf("Divide: %.2f\n", divide(a, b));

    return 0;
}
```

### **2. Compilation Commands**
```bash
# Compile individual files
gcc -c calculator.c -o calculator.o
gcc -c main.c -o main.o

# Link object files
gcc calculator.o main.o -o program

# Single command compilation
gcc main.c calculator.c -o program

# With debugging
gcc -g main.c calculator.c -o program

# Optimized compilation
gcc -O2 main.c calculator.c -o program
```

### **3. Makefile for Multi-file Projects**
```makefile
# Makefile for calculator project

CC = gcc
CFLAGS = -Wall -g
TARGET = calculator
OBJS = main.o calculator.o

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c calculator.h
    $(CC) $(CFLAGS) -c main.c

calculator.o: calculator.c calculator.h
    $(CC) $(CFLAGS) -c calculator.c

clean:
    rm -f $(OBJS) $(TARGET)

.PHONY: all clean
```

---

## 🔍 Preprocessor Operators

### **1. Stringification Operator (#)**
```c
#include <stdio.h>

#define PRINT_VAR(x) printf(#x " = %d\n", x)
#define CREATE_STRING(x) #x

int main() {
    int value = 42;
    PRINT_VAR(value);

    printf("String: %s\n", CREATE_STRING(Hello World));

    return 0;
}
```

### **2. Token Pasting Operator (##)**
```c
#include <stdio.h>

#define CONCAT(a, b) a##b
#define CREATE_VAR(name, value) int CONCAT(var_, name) = value
#define DECLARE_ARRAY(type, name, size) type name##Array[size]

int main() {
    CREATE_VAR(counter, 10);
    printf("var_counter = %d\n", var_counter);

    DECLARE_ARRAY(int, numbers, 5);
    for (int i = 0; i < 5; i++) {
        numbersArray[i] = i * 2;
        printf("%d ", numbersArray[i]);
    }
    printf("\n");

    return 0;
}
```

### **3. Defined Operator**
```c
#include <stdio.h>

#define FEATURE_A
#define FEATURE_B

int main() {
    #if defined(FEATURE_A)
        printf("Feature A is defined\n");
    #endif

    #if !defined(FEATURE_C)
        printf("Feature C is not defined\n");
    #endif

    return 0;
}
```

---

## 🛠️ Advanced Preprocessor Features

### **1. #error and #warning**
```c
#include <stdio.h>

#define MIN_VERSION 3
#define CURRENT_VERSION 2

#if CURRENT_VERSION < MIN_VERSION
    #error "Current version is too old. Please upgrade."
#endif

#ifndef REQUIRED_HEADER
    #warning "Required header not included"
#endif

int main() {
    printf("Program compiled successfully\n");
    return 0;
}
```

### **2. #line Directive**
```c
#include <stdio.h>

// Change line number and filename for error reporting
#line 100 "custom_file.c"

int main() {
    printf("This is line %d in file %s\n", __LINE__, __FILE__);
    return 0;
}
```

### **3. #pragma Directive**
```c
#include <stdio.h>

// Compiler-specific pragmas
#pragma warning(disable: 4996)  // Disable specific warning
#pragma once                    // Include guard alternative

// Pack structures
#pragma pack(1)
struct PackedStruct {
    char c;
    int i;
};
#pragma pack()

int main() {
    printf("Size of packed struct: %zu\n", sizeof(struct PackedStruct));
    return 0;
}
```

---

## 🔍 Compilation Process Details

### **1. Preprocessing Phase**
```c
// Source code with preprocessor directives
#include <stdio.h>
#define PI 3.14159

int main() {
    printf("PI = %f\n", PI);
    return 0;
}
```

**After preprocessing:**
```c
// Preprocessed code (simplified)
// ... stdio.h contents ...
int main() {
    printf("PI = %f\n", 3.14159);
    return 0;
}
```

### **2. Compilation Steps**
```bash
# 1. Preprocessing only
gcc -E main.c -o main.i

# 2. Compile to assembly
gcc -S main.c -o main.s

# 3. Assemble to object file
gcc -c main.c -o main.o

# 4. Link object files
gcc main.o -o main

# 5. View preprocessor output
gcc -E main.c | head -20
```

### **3. Common Preprocessor Flags**
```bash
# Show all include paths
gcc -v main.c

# Define macros from command line
gcc -DDEBUG -DVERSION=2 main.c -o program

# Undefine macros
gcc -U DEBUG main.c -o program

# Include additional directories
gcc -I/include/path main.c -o program

# Preprocess only, keep comments
gcc -E -C main.c -o main.i
```

---

## 🎯 Best Practices

### **1. Use Include Guards**
```c
// ✅ Good
#ifndef MYHEADER_H
#define MYHEADER_H

// Header content

#endif

// ❌ Bad - no include guards
// Header content
```

### **2. Parenthesize Macro Parameters**
```c
// ✅ Good
#define SQUARE(x) ((x) * (x))
#define ADD(a, b) ((a) + (b))

// ❌ Bad
#define SQUARE(x) x * x        // Won't work with expressions
#define ADD(a, b) a + b        // Operator precedence issues
```

### **3. Use Meaningful Macro Names**
```c
// ✅ Good
#define MAX_BUFFER_SIZE 1024
#define DEBUG_MODE 1
#define PI_VALUE 3.14159

// ❌ Bad
#define A 1024
#define B 1
#define C 3.14159
```

### **4. Avoid Side Effects in Macros**
```c
// ✅ Good
#define SQUARE(x) ((x) * (x))

// ❌ Bad - side effects
#define INCREMENT(x) ((x)++)
```

---

## 🐛 Common Mistakes

### **1. Missing Parentheses in Macros**
```c
// Wrong
#define SQUARE(x) x * x

// Problem: SQUARE(3 + 2) becomes 3 + 2 * 3 + 2 = 11
// Correct: SQUARE(3 + 2) becomes ((3 + 2) * (3 + 2)) = 25
#define SQUARE(x) ((x) * (x))
```

### **2. Multiple Inclusion**
```c
// Wrong - no include guards
// File: header.h
int global_var;

// File: main.c
#include "header.h"
#include "header.h"  // Multiple inclusion error

// Correct - with include guards
#ifndef HEADER_H
#define HEADER_H
int global_var;
#endif
```

### **3. Macro Name Conflicts**
```c
// Wrong - conflicts with standard library
#define malloc my_malloc

// Correct - use unique names
#define MY_MALLOC my_malloc
```

### **4. Conditional Compilation Errors**
```c
// Wrong - missing endif
#define DEBUG
#ifdef DEBUG
    printf("Debug\n");
// Missing #endif

// Correct
#define DEBUG
#ifdef DEBUG
    printf("Debug\n");
#endif
```

---

## 📝 Practice Exercises

### **Exercise 1: Macro Creation**
- Create macros for common mathematical operations
- Build string manipulation macros
- Implement debugging macros

### **Exercise 2: Conditional Compilation**
- Create platform-specific code
- Implement feature toggles
- Build version-specific functionality

### **Exercise 3: Multi-file Programs**
- Split a large program into multiple files
- Create header files for function declarations
- Build a library with multiple modules

### **Exercise 4: Advanced Preprocessor**
- Create complex macro functions
- Implement conditional compilation for different environments
- Build a simple build system with Makefiles

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What does the `#include` directive do?
a) Includes source code from another file
b) Includes compiled code
c) Includes only function declarations
d) Includes only macro definitions

### **Question 2:**
Which is the correct syntax for a function-like macro?
a) `#define SQUARE x * x`
b) `#define SQUARE(x) x * x`
c) `#define SQUARE(x) (x * x)`
d) Both b and c

### **Question 3:**
What does `#ifndef` check for?
a) If a macro is defined
b) If a macro is not defined
c) If a file exists
d) If a function is declared

### **Question 4:**
Which operator converts a token to a string?
a) `##`
b) `#`
c) `@@`
d) `$$`

### **Question 5:**
What is the purpose of include guards?
a) Prevent multiple inclusion of header files
b) Protect against viruses
c) Encrypt header files
d) Compress header files

---

## 🔗 Additional Resources

### **Preprocessor**
- [C Preprocessor](https://en.cppreference.com/w/c/preprocessor)
- [Macro Programming](https://gcc.gnu.org/onlinedocs/cpp/Macros.html)
- [Conditional Compilation](https://en.cppreference.com/w/c/preprocessor/conditional)

### **Further Reading**
- [Preprocessor Directives](https://www.programiz.com/c-programming/c-preprocessor)
- [Header Files](https://www.geeksforgeeks.org/header-files-in-c/)
- [Makefiles](https://www.gnu.org/software/make/manual/make.html)

---

## 🎯 Next Steps

**Great job!** You've mastered:
- ✅ Preprocessor directives and usage
- ✅ Macro definition and expansion
- ✅ Conditional compilation techniques
- ✅ Header files and multi-file programs
- ✅ Complete compilation process

**Next Lesson Preview:**
- Enumerations and typedef
- Advanced data types
- Bit manipulation
- Command-line arguments

---

**🚀 Ready to explore advanced C features?**

[⬅️ Previous: File Handling](13_File_Handling.md) | [Next: Enumerations & Typedef ➡️](15_Enumerations_Typedef.md)