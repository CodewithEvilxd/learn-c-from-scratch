# 🎯 Practical 161: Implement Macro Handling

## 📋 Problem Statement

Implement macro handling.

## 🎯 Learning Objectives

- Understand C preprocessor macros
- Practice macro definition and usage
- Learn macro expansion
- Understand conditional compilation
- Practice advanced macro techniques

## 📝 Requirements

1. Demonstrate various macro types
2. Show macro expansion
3. Implement conditional macros
4. Handle macro parameters
5. Display macro functionality

## 💡 Hints

- Use #define for simple macros
- Implement parameterized macros
- Use conditional compilation
- Demonstrate macro pitfalls
- Show debugging techniques

## 🔧 Solution

```c
// Practical 161: Implement Macro Handling
// Demonstrates various macro techniques in C

#include <stdio.h>

// 1. Simple macro definition
#define PI 3.14159
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 2. String manipulation macros
#define STR(x) #x
#define CONCAT(a, b) a##b

// 3. Conditional compilation macros
#define DEBUG 1
#define VERSION "1.0.0"

// 4. Multi-line macro
#define PRINT_ARRAY(arr, size) \
    do { \
        printf("Array elements: "); \
        for (int i = 0; i < size; i++) { \
            printf("%d ", arr[i]); \
        } \
        printf("\n"); \
    } while(0)

// 5. Debug macro
#if DEBUG
    #define LOG(msg) printf("DEBUG: %s\n", msg)
    #define LOGF(format, ...) printf("DEBUG: " format "\n", __VA_ARGS__)
#else
    #define LOG(msg)
    #define LOGF(format, ...)
#endif

int main() {
    printf("Macro Handling Demonstration\n");
    printf("===========================\n");

    // Simple macro usage
    printf("\n1. Simple Macros:\n");
    printf("PI = %f\n", PI);
    printf("Square of 5 = %d\n", SQUARE(5));
    printf("Max of 10 and 20 = %d\n", MAX(10, 20));
    printf("Min of 10 and 20 = %d\n", MIN(10, 20));

    // String manipulation
    printf("\n2. String Manipulation:\n");
    printf("STR(hello) = %s\n", STR(hello));
    int CONCAT(var, 1) = 42;
    printf("var1 = %d\n", var1);

    // Array demonstration
    printf("\n3. Multi-line Macro:\n");
    int arr[] = {1, 2, 3, 4, 5};
    PRINT_ARRAY(arr, 5);

    // Debug macros
    printf("\n4. Debug Macros:\n");
    LOG("This is a debug message");
    LOGF("Value of PI: %.2f", PI);

    // Version info
    printf("\n5. Version Info:\n");
    printf("Software Version: %s\n", VERSION);

    // Conditional compilation demo
    printf("\n6. Conditional Compilation:\n");
    #ifdef DEBUG
        printf("Debug mode is enabled\n");
    #else
        printf("Debug mode is disabled\n");
    #endif

    // Macro expansion pitfalls
    printf("\n7. Macro Pitfalls:\n");
    int x = 5;
    printf("SQUARE(++x) = %d, x = %d\n", SQUARE(++x), x); // x incremented twice!

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Execution
```
Expected Output:
Macro Handling Demonstration
===========================

1. Simple Macros:
PI = 3.141590
Square of 5 = 25
Max of 10 and 20 = 20
Min of 10 and 20 = 10

2. String Manipulation:
STR(hello) = hello
var1 = 42

3. Multi-line Macro:
Array elements: 1 2 3 4 5

4. Debug Macros:
DEBUG: This is a debug message
DEBUG: Value of PI: 3.14

5. Version Info:
Software Version: 1.0.0

6. Conditional Compilation:
Debug mode is enabled

7. Macro Pitfalls:
SQUARE(++x) = 49, x = 7
```

## 🔍 Explanation

1. **Simple Macros**: Basic constant and function-like macros
2. **String Macros**: Stringification and concatenation
3. **Multi-line Macros**: Complex macro definitions
4. **Conditional Macros**: Debug and version control
5. **Macro Pitfalls**: Demonstrating common issues

## 🎯 Key Concepts Covered

- Macro definition and expansion
- Parameterized macros
- Conditional compilation
- String manipulation in macros
- Macro debugging techniques

## 🚀 Extensions

1. Implement macro processor
2. Add macro expansion tracing
3. Create macro libraries
4. Handle recursive macros