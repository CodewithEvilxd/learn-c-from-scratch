# 🚀 Lesson 7: Modern C Standards (C11/C18/C2x)
## Advanced C Features and Best Practices

---

## 🎯 Learning Objectives

- Understand modern C standards evolution
- Learn C11/C18 advanced features
- Practice modern C programming techniques
- Understand backwards compatibility
- Learn best practices for modern C development

---

## 📚 C Standards Evolution

### **C11 Standard (2011)**
Major revision with significant new features:
- Threading support (`<threads.h>`)
- Atomic operations
- Unicode support
- Generic programming with `_Generic`
- Anonymous structures and unions
- Bounds checking interfaces
- No-return functions (`_Noreturn`)

### **C18 Standard (2018)**
Minor revision focused on:
- Bug fixes and clarifications
- Technical corrigenda
- Improved compatibility
- Security enhancements

### **C2x/C23 Standard (Upcoming)**
Expected features:
- Better error handling
- Modules system
- Improved Unicode support
- Enhanced generics
- Binary literals and digit separators

---

## 🧵 Multi-threading in C11

### **Thread Creation and Management**

```c
#include <threads.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function
int threadFunction(void* arg) {
    int threadId = *(int*)arg;
    printf("Thread %d is running\n", threadId);

    // Simulate work
    thrd_sleep(&(struct timespec){1, 0}, NULL);

    printf("Thread %d finished\n", threadId);
    return threadId * 10;
}

int main() {
    thrd_t thread1, thread2;
    int id1 = 1, id2 = 2;
    int result1, result2;

    // Create threads
    if (thrd_create(&thread1, threadFunction, &id1) != thrd_success) {
        fprintf(stderr, "Failed to create thread 1\n");
        return 1;
    }

    if (thrd_create(&thread2, threadFunction, &id2) != thrd_success) {
        fprintf(stderr, "Failed to create thread 2\n");
        return 1;
    }

    // Wait for threads to complete
    thrd_join(thread1, &result1);
    thrd_join(thread2, &result2);

    printf("Thread 1 returned: %d\n", result1);
    printf("Thread 2 returned: %d\n", result2);

    return 0;
}
```

### **Mutex and Synchronization**

```c
#include <threads.h>
#include <stdio.h>

mtx_t mutex;
int sharedCounter = 0;

int incrementCounter(void* arg) {
    for (int i = 0; i < 100000; i++) {
        mtx_lock(&mutex);
        sharedCounter++;
        mtx_unlock(&mutex);
    }
    return 0;
}

int main() {
    thrd_t threads[10];

    // Initialize mutex
    mtx_init(&mutex, mtx_plain);

    // Create threads
    for (int i = 0; i < 10; i++) {
        thrd_create(&threads[i], incrementCounter, NULL);
    }

    // Wait for all threads
    for (int i = 0; i < 10; i++) {
        thrd_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", sharedCounter);

    mtx_destroy(&mutex);
    return 0;
}
```

---

## ⚛️ Atomic Operations

### **Atomic Variables**

```c
#include <stdatomic.h>
#include <threads.h>
#include <stdio.h>

atomic_int atomicCounter = ATOMIC_VAR_INIT(0);

int incrementAtomic(void* arg) {
    for (int i = 0; i < 100000; i++) {
        atomic_fetch_add(&atomicCounter, 1);
    }
    return 0;
}

int main() {
    thrd_t threads[10];

    // Create threads
    for (int i = 0; i < 10; i++) {
        thrd_create(&threads[i], incrementAtomic, NULL);
    }

    // Wait for threads
    for (int i = 0; i < 10; i++) {
        thrd_join(threads[i], NULL);
    }

    printf("Atomic counter value: %d\n", atomic_load(&atomicCounter));

    return 0;
}
```

### **Memory Ordering**

```c
#include <stdatomic.h>

// Relaxed ordering - no synchronization
atomic_int relaxedVar = ATOMIC_VAR_INIT(0);

// Acquire/Release ordering - synchronizes with other operations
atomic_int acquireReleaseVar = ATOMIC_VAR_INIT(0);

// Sequentially consistent - strongest ordering
atomic_int seqConsistentVar = ATOMIC_VAR_INIT(0);

void relaxedOperation() {
    atomic_store_explicit(&relaxedVar, 42, memory_order_relaxed);
    int value = atomic_load_explicit(&relaxedVar, memory_order_relaxed);
}

void acquireReleaseOperation() {
    atomic_store_explicit(&acquireReleaseVar, 42, memory_order_release);
    int value = atomic_load_explicit(&acquireReleaseVar, memory_order_acquire);
}
```

---

## 🎯 Generic Programming with _Generic

### **Type-Generic Functions**

```c
#include <stdio.h>

// Generic print function
#define printValue(X) _Generic((X), \
    int: printInt, \
    float: printFloat, \
    double: printDouble, \
    char*: printString \
)(X)

void printInt(int x) { printf("Integer: %d\n", x); }
void printFloat(float x) { printf("Float: %.2f\n", x); }
void printDouble(double x) { printf("Double: %.2f\n", x); }
void printString(char* x) { printf("String: %s\n", x); }

int main() {
    printValue(42);           // Integer: 42
    printValue(3.14f);        // Float: 3.14
    printValue(2.71828);      // Double: 2.72
    printValue("Hello");      // String: Hello

    return 0;
}
```

### **Generic Math Operations**

```c
#include <math.h>
#include <stdio.h>

#define square(X) _Generic((X), \
    int: squareInt, \
    float: squareFloat, \
    double: squareDouble \
)(X)

int squareInt(int x) { return x * x; }
float squareFloat(float x) { return x * x; }
double squareDouble(double x) { return x * x; }

#define sqrtValue(X) _Generic((X), \
    int: sqrtInt, \
    float: sqrtFloat, \
    double: sqrtDouble \
)(X)

int sqrtInt(int x) { return (int)sqrt(x); }
float sqrtFloat(float x) { return sqrtf(x); }
double sqrtDouble(double x) { return sqrt(x); }

int main() {
    printf("Square of 5: %d\n", square(5));
    printf("Square of 3.5f: %.2f\n", square(3.5f));
    printf("Square of 2.25: %.2f\n", square(2.25));

    printf("Sqrt of 16: %d\n", sqrtValue(16));
    printf("Sqrt of 9.0f: %.2f\n", sqrtValue(9.0f));
    printf("Sqrt of 100.0: %.2f\n", sqrtValue(100.0));

    return 0;
}
```

---

## 📝 Anonymous Structures and Unions

### **Anonymous Structures**

```c
#include <stdio.h>

struct Person {
    char name[50];
    int age;

    // Anonymous structure
    struct {
        int houseNumber;
        char street[50];
        char city[50];
    };  // No name - members accessed directly

    // Anonymous union
    union {
        int employeeId;
        char department[20];
    };  // No name - members accessed directly
};

int main() {
    struct Person person = {
        .name = "John Doe",
        .age = 30,
        .houseNumber = 123,
        .street = "Main Street",
        .city = "New York",
        .employeeId = 1001
    };

    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);
    printf("Address: %d %s, %s\n",
           person.houseNumber, person.street, person.city);
    printf("Employee ID: %d\n", person.employeeId);

    // Switch to department
    strcpy(person.department, "Engineering");
    printf("Department: %s\n", person.department);

    return 0;
}
```

---

## 🔍 Static Assertions

### **Compile-time Assertions**

```c
#include <assert.h>

// Static assertion - checked at compile time
static_assert(sizeof(int) == 4, "int must be 4 bytes");
static_assert(__STDC_VERSION__ >= 201112L, "C11 or later required");

// Array size validation
#define ARRAY_SIZE 10
static_assert(ARRAY_SIZE > 0, "Array size must be positive");

int main() {
    int arr[ARRAY_SIZE];

    // Runtime assertion
    assert(ARRAY_SIZE > 5);

    printf("Array size: %d\n", ARRAY_SIZE);
    printf("Array element size: %zu bytes\n", sizeof(arr[0]));

    return 0;
}
```

---

## 🌍 Unicode and Wide Characters

### **Unicode Support**

```c
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    // Set locale for Unicode support
    setlocale(LC_ALL, "");

    // Wide character string
    wchar_t* unicodeString = L"Hello, 世界! 🌍";

    // Print wide string
    wprintf(L"Unicode string: %ls\n", unicodeString);

    // Wide character I/O
    wprintf(L"Enter your name: ");
    wchar_t name[100];
    fgetws(name, 100, stdin);

    // Remove newline
    name[wcscspn(name, L"\n")] = L'\0';

    wprintf(L"Hello, %ls!\n", name);

    return 0;
}
```

---

## 🚫 No-Return Functions

### **Functions that Never Return**

```c
#include <stdlib.h>
#include <stdio.h>

// No-return function
_Noreturn void fatalError(const char* message) {
    fprintf(stderr, "Fatal error: %s\n", message);
    exit(EXIT_FAILURE);
    // This code is never reached
}

_Noreturn void infiniteLoop() {
    while (1) {
        printf("This loop never ends\n");
        // No return statement needed
    }
}

int divide(int a, int b) {
    if (b == 0) {
        fatalError("Division by zero");
    }
    return a / b;
}

int main() {
    printf("Result: %d\n", divide(10, 2));

    // This would cause fatal error
    // printf("Result: %d\n", divide(10, 0));

    return 0;
}
```

---

## 🔒 Bounds Checking Interfaces (Optional)

### **Safe Array Access**

```c
// Note: Bounds checking interfaces are optional in C11
// and may not be available in all implementations

#ifdef __STDC_LIB_EXT1__

#include <stdio.h>
#include <stdlib.h>

// Use bounds checking functions if available
int main() {
    char buffer[100];

    // Safe string copy
    errno_t result = strcpy_s(buffer, sizeof(buffer), "Hello, World!");

    if (result != 0) {
        fprintf(stderr, "String copy failed\n");
        return 1;
    }

    printf("Buffer: %s\n", buffer);
    return 0;
}

#else

#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100];

    // Traditional unsafe version
    strcpy(buffer, "Hello, World!");
    printf("Buffer: %s\n", buffer);

    return 0;
}

#endif
```

---

## 🏗️ Modern C Best Practices

### **Code Organization**

```c
// Modern header file structure
#pragma once  // Alternative to include guards

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // C99 boolean type

// Use inline functions for small utilities
inline bool isEven(int x) {
    return x % 2 == 0;
}

// Use restrict keyword for optimization hints
void copyArray(int* restrict dest, const int* restrict src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Use designated initializers
struct Point {
    int x, y;
};

int main() {
    // Designated initializers
    struct Point p = {.x = 10, .y = 20};

    // Compound literals
    int* arr = (int[]){1, 2, 3, 4, 5};

    printf("Point: (%d, %d)\n", p.x, p.y);
    printf("Array[2]: %d\n", arr[2]);

    free(arr);
    return 0;
}
```

---

## 📋 Compiler Support

### **GCC Modern C Support**

```bash
# Compile with C11 standard
gcc -std=c11 -o program program.c

# Compile with C18 standard
gcc -std=c18 -o program program.c

# Enable all warnings
gcc -std=c11 -Wall -Wextra -Wpedantic -o program program.c

# Enable threading support
gcc -std=c11 -pthread -o program program.c

# Check compiler version
gcc --version
```

### **Clang Modern C Support**

```bash
# Compile with modern C
clang -std=c11 -o program program.c

# Enable additional checks
clang -std=c11 -Weverything -o program program.c

# Static analysis
clang -std=c11 --analyze program.c
```

---

## 🎯 Practice Exercises

### **Exercise 1: Thread-Safe Counter**
Implement a thread-safe counter using atomic operations.

### **Exercise 2: Generic Swap Function**
Create a generic swap function using `_Generic`.

### **Exercise 3: Anonymous Structures**
Design a data structure using anonymous structures and unions.

### **Exercise 4: Unicode Text Processing**
Write a program that processes Unicode text using wide characters.

---

## 🚀 Migration from Older C Standards

### **C89/C90 to C99**
- Add `//` comments
- Use `bool` from `<stdbool.h>`
- Use `inline` functions
- Variable declarations anywhere in blocks

### **C99 to C11**
- Use threading functions
- Atomic operations
- Generic selections
- Unicode support

### **Backwards Compatibility**
```c
// Check for C standard version
#if __STDC_VERSION__ >= 201112L
    // C11 features available
    #include <threads.h>
#else
    // Fallback for older compilers
    #include <pthread.h>
#endif
```

---

## 📚 Further Reading

- **C11 Standard**: ISO/IEC 9899:2011
- **C18 Standard**: ISO/IEC 9899:2018
- **GCC Documentation**: Modern C features
- **Clang Documentation**: C language extensions

---

## 🎯 Next Steps

**Congratulations!** You've learned modern C programming techniques.

**Next Topics:**
- System programming with POSIX
- Network programming with sockets
- Performance optimization techniques
- Cross-platform development

---

**🚀 Keep exploring modern C features and best practices!**