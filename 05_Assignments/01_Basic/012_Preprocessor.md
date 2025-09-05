# 🎯 Assignment 1.12: Preprocessor Directives

## 📋 Problem Statement

Create a C program that demonstrates various preprocessor directives including macros, conditional compilation, file inclusion, and predefined macros. Implement a configurable logging system using preprocessor features.

## 🎯 Learning Objectives

- Understand preprocessor directives
- Learn macro definition and usage
- Practice conditional compilation
- Use predefined macros
- Implement header guards
- Create configurable code with macros

## 📝 Requirements

1. Define and use object-like macros
2. Create function-like macros
3. Use conditional compilation (#ifdef, #ifndef)
4. Demonstrate file inclusion
5. Use predefined macros (__LINE__, __FILE__, etc.)
6. Implement header guards
7. Create a configurable logging system

## 💡 Hints

- Macros are processed before compilation
- Use #define for macro definition
- #ifdef checks if macro is defined
- Include guards prevent multiple inclusion
- Predefined macros provide compile-time information

## 🔧 Solution

```c
// Assignment 1.12: Preprocessor Directives
// Demonstrating macros, conditional compilation, and logging

#include <stdio.h>
#include <stdlib.h>

// Header guard
#ifndef UTILS_H
#define UTILS_H

// Object-like macros
#define PI 3.14159
#define MAX_BUFFER_SIZE 1024
#define DEBUG_MODE 1

// Function-like macros
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// String manipulation macros
#define STR(x) #x
#define CONCAT(a, b) a##b

// Logging macros
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3

// Current log level (can be changed at compile time)
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

// Logging macros with conditional compilation
#define LOG_DEBUG(msg) \
    do { \
        if (CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG) { \
            printf("[DEBUG] %s:%d: %s\n", __FILE__, __LINE__, msg); \
        } \
    } while(0)

#define LOG_INFO(msg) \
    do { \
        if (CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO) { \
            printf("[INFO] %s:%d: %s\n", __FILE__, __LINE__, msg); \
        } \
    } while(0)

#define LOG_WARN(msg) \
    do { \
        if (CURRENT_LOG_LEVEL <= LOG_LEVEL_WARN) { \
            printf("[WARN] %s:%d: %s\n", __FILE__, __LINE__, msg); \
        } \
    } while(0)

#define LOG_ERROR(msg) \
    do { \
        if (CURRENT_LOG_LEVEL <= LOG_LEVEL_ERROR) { \
            printf("[ERROR] %s:%d: %s\n", __FILE__, __LINE__, msg); \
        } \
    } while(0)

// Utility macros
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define SWAP(a, b) do { typeof(a) temp = a; a = b; b = temp; } while(0)

// Platform-specific code
#ifdef _WIN32
#define PLATFORM "Windows"
#elif __linux__
#define PLATFORM "Linux"
#elif __APPLE__
#define PLATFORM "macOS"
#else
#define PLATFORM "Unknown"
#endif

#endif // UTILS_H

// Main program
int main() {
    printf("=== Preprocessor Directives Demonstration ===\n\n");

    // Basic macros
    printf("1. Basic Macros:\n");
    printf("PI = %f\n", PI);
    printf("Square of 5 = %d\n", SQUARE(5));
    printf("Max of 10, 20 = %d\n", MAX(10, 20));
    printf("Min of 10, 20 = %d\n", MIN(10, 20));

    // String manipulation
    printf("\n2. String Manipulation:\n");
    printf("Stringified PI: %s\n", STR(PI));
    int CONCAT(var, 1) = 42;
    printf("Concatenated variable: %d\n", var1);

    // Logging system
    printf("\n3. Logging System:\n");
    LOG_DEBUG("This is a debug message");
    LOG_INFO("Program started");
    LOG_WARN("This is a warning");
    LOG_ERROR("This is an error");

    // Array utilities
    printf("\n4. Array Utilities:\n");
    int arr[] = {1, 2, 3, 4, 5};
    printf("Array size: %zu\n", ARRAY_SIZE(arr));

    // Swap demonstration
    int x = 10, y = 20;
    printf("Before swap: x=%d, y=%d\n", x, y);
    SWAP(x, y);
    printf("After swap: x=%d, y=%d\n", x, y);

    // Platform information
    printf("\n5. Platform Information:\n");
    printf("Platform: %s\n", PLATFORM);
    printf("Compiled on: %s %s\n", __DATE__, __TIME__);
    printf("Compiler: %s\n", __VERSION__);

    // Conditional compilation demonstration
    printf("\n6. Conditional Compilation:\n");
#ifdef DEBUG_MODE
    printf("Debug mode is enabled\n");
    printf("Buffer size: %d\n", MAX_BUFFER_SIZE);
#else
    printf("Debug mode is disabled\n");
#endif

    // Version information
    printf("\n7. Version Information:\n");
    printf("File: %s\n", __FILE__);
    printf("Line: %d\n", __LINE__);
    printf("Function: %s\n", __func__);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Basic Macros
```
Expected Output:
PI = 3.141590
Square of 5 = 25
Max of 10, 20 = 20
Min of 10, 20 = 10
```

### Test Case 2: Logging System
```
Expected Output:
[DEBUG] preprocessor.c:85: This is a debug message
[INFO] preprocessor.c:86: Program started
[WARN] preprocessor.c:87: This is a warning
[ERROR] preprocessor.c:88: This is an error
```

### Test Case 3: Platform Information
```
Expected Output:
Platform: Linux (or Windows/macOS)
Compiled on: Sep 5 2025 13:18:38
Compiler: gcc version...
```

### Test Case 4: Conditional Compilation
```
Expected Output:
Debug mode is enabled
Buffer size: 1024
```

## 🔍 Explanation

1. **Object-like Macros**: `#define PI 3.14159` - simple value replacement
2. **Function-like Macros**: `#define SQUARE(x) ((x) * (x))` - parameterized macros
3. **Conditional Compilation**: `#ifdef DEBUG_MODE` - compile-time conditions
4. **Predefined Macros**: `__FILE__`, `__LINE__` - compiler-provided information
5. **Header Guards**: Prevent multiple inclusion of header files
6. **Stringification**: `#x` converts macro parameter to string
7. **Token Concatenation**: `a##b` joins tokens together

## 🎯 Key Concepts Covered

- Macro definition and expansion
- Conditional compilation
- Predefined macros
- Header guards
- Function-like macros
- String manipulation in macros

## 🚀 Extensions

1. Create a more advanced logging system with timestamps
2. Implement platform-specific optimizations
3. Add configuration file parsing with macros
4. Create a simple unit testing framework using macros