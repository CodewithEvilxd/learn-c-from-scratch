# 🎯 Practical 164: Multi-line Macro and Conditional Macros

## 📋 Problem Statement

Program to implement multi line macro and Conditional Macros.

## 🎯 Learning Objectives

- Understand advanced macro techniques
- Practice multi-line macro definitions
- Learn conditional compilation
- Understand macro debugging
- Practice complex macro usage

## 📝 Requirements

1. Demonstrate multi-line macros
2. Show conditional macro compilation
3. Implement macro functions
4. Handle macro parameters
5. Display macro expansion results

## 💡 Hints

- Use backslash for multi-line macros
- Implement conditional compilation
- Create parameterized macros
- Show macro expansion
- Handle compilation flags

## 🔧 Solution

```c
// Practical 164: Multi-line Macro and Conditional Macros
// Demonstrates advanced macro techniques

#include <stdio.h>
#include <stdlib.h>

// 1. Multi-line macro
#define PRINT_ARRAY(arr, size, type) \
    do { \
        printf("Array contents (" #type "):\n"); \
        for (int i = 0; i < size; i++) { \
            printf("%d ", arr[i]); \
        } \
        printf("\n"); \
    } while(0)

// 2. Conditional macros
#define DEBUG_LEVEL 2

#if DEBUG_LEVEL >= 1
    #define DEBUG_PRINT(msg) printf("DEBUG: %s\n", msg)
#else
    #define DEBUG_PRINT(msg)
#endif

#if DEBUG_LEVEL >= 2
    #define DEBUG_PRINT_LEVEL(level, msg) \
        if (level <= DEBUG_LEVEL) printf("DEBUG L%d: %s\n", level, msg)
#else
    #define DEBUG_PRINT_LEVEL(level, msg)
#endif

// 3. Complex multi-line macro with parameters
#define CREATE_AND_PRINT_ARRAY(name, size) \
    do { \
        int name[size]; \
        printf("Created array '" #name "' with size %d\n", size); \
        for (int i = 0; i < size; i++) { \
            name[i] = i * 10; \
        } \
        PRINT_ARRAY(name, size, int); \
    } while(0)

// 4. Conditional macro based on platform
#ifdef _WIN32
    #define PLATFORM "Windows"
    #define CLEAR_SCREEN system("cls")
#elif defined(__linux__)
    #define PLATFORM "Linux"
    #define CLEAR_SCREEN system("clear")
#else
    #define PLATFORM "Unknown"
    #define CLEAR_SCREEN printf("\n")
#endif

// 5. Macro for error handling
#define CHECK_NULL(ptr, msg) \
    do { \
        if (ptr == NULL) { \
            fprintf(stderr, "ERROR: %s\n", msg); \
            exit(1); \
        } \
    } while(0)

int main() {
    printf("Multi-line Macro and Conditional Macros Demo\n");
    printf("=============================================\n");

    // Demonstrate multi-line macro
    printf("\n1. Multi-line Macro:\n");
    int arr[] = {1, 2, 3, 4, 5};
    PRINT_ARRAY(arr, 5, int);

    // Demonstrate conditional macros
    printf("\n2. Conditional Macros:\n");
    DEBUG_PRINT("This is a debug message");
    DEBUG_PRINT_LEVEL(1, "Level 1 debug");
    DEBUG_PRINT_LEVEL(2, "Level 2 debug");
    DEBUG_PRINT_LEVEL(3, "Level 3 debug");

    // Demonstrate complex multi-line macro
    printf("\n3. Complex Multi-line Macro:\n");
    CREATE_AND_PRINT_ARRAY(myArray, 3);

    // Demonstrate platform-specific macro
    printf("\n4. Platform-specific Macro:\n");
    printf("Running on: %s\n", PLATFORM);
    printf("Clearing screen...\n");
    CLEAR_SCREEN;

    // Demonstrate error handling macro
    printf("\n5. Error Handling Macro:\n");
    int *ptr = (int *)malloc(sizeof(int));
    CHECK_NULL(ptr, "Memory allocation failed");
    *ptr = 42;
    printf("Allocated memory contains: %d\n", *ptr);
    free(ptr);

    printf("\nDemo completed successfully!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Full Debug Level
```
Expected Output:
Multi-line Macro and Conditional Macros Demo
=============================================

1. Multi-line Macro:
Array contents (int):
1 2 3 4 5

2. Conditional Macros:
DEBUG: This is a debug message
DEBUG L1: Level 1 debug
DEBUG L2: Level 2 debug

3. Complex Multi-line Macro:
Created array 'myArray' with size 3
Array contents (int):
0 10 20

4. Platform-specific Macro:
Running on: Windows/Linux/Unknown
Clearing screen...

5. Error Handling Macro:
Allocated memory contains: 42

Demo completed successfully!
```

## 🔍 Explanation

1. **Multi-line Macros**: Use backslash continuation
2. **Conditional Compilation**: Based on DEBUG_LEVEL
3. **Complex Macros**: Create and print arrays
4. **Platform Detection**: Different behavior per platform
5. **Error Handling**: Null pointer checks

## 🎯 Key Concepts Covered

- Multi-line macro syntax
- Conditional compilation
- Macro parameters
- Platform-specific code
- Error handling macros

## 🚀 Extensions

1. Add more complex conditional logic
2. Implement macro-based logging system
3. Create cross-platform compatibility layer
4. Add macro performance profiling