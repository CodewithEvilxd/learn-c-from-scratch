# 📊 Lesson 4: Variables & Data Types
## Understanding Data Storage in C

---

## 🎯 Learning Objectives

- Understand different data types in C
- Learn variable declaration and initialization
- Master type qualifiers and modifiers
- Understand memory allocation for different types
- Learn type conversion techniques

---

## 📖 What are Variables?

**Variables** are named memory locations that store data values. In C, every variable must be declared with a specific data type before use.

### **Variable Declaration Syntax**
```c
data_type variable_name;

// Examples
int age;
float salary;
char grade;
```

### **Variable Initialization**
```c
// Declaration with initialization
int age = 25;
float pi = 3.14159;
char letter = 'A';

// Multiple declarations
int a = 1, b = 2, c = 3;
```

---

## 🔢 Primitive Data Types

C provides several built-in data types for different kinds of data.

### **1. Integer Types (`int`)**

```c
// Basic integer
int number = 42;

// Size modifiers
short int small_num = 100;    // At least 16 bits
long int big_num = 100000;    // At least 32 bits
long long int huge_num = 1000000000LL;  // At least 64 bits

// Sign modifiers
signed int positive = 100;    // Default, includes negative
unsigned int only_positive = 100;  // Only non-negative
```

**Size and Range (Typical 32-bit system):**
- `short int`: 2 bytes (-32,768 to 32,767)
- `int`: 4 bytes (-2,147,483,648 to 2,147,483,647)
- `long int`: 4 bytes (-2,147,483,648 to 2,147,483,647)
- `long long int`: 8 bytes (-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807)

### **2. Floating-Point Types (`float`, `double`)**

```c
// Single precision
float temperature = 36.5f;
float pi = 3.14159f;

// Double precision (more accurate)
double precise_pi = 3.141592653589793;
double large_number = 123456789.123456789;

// Long double (highest precision)
long double very_precise = 3.141592653589793238L;
```

**Precision and Range:**
- `float`: 4 bytes, 6-7 decimal digits, range: ±3.4E-38 to ±3.4E+38
- `double`: 8 bytes, 15-16 decimal digits, range: ±1.7E-308 to ±1.7E+308
- `long double`: 10-16 bytes, 18-19 decimal digits

### **3. Character Type (`char`)**

```c
// Single character
char letter = 'A';
char digit = '5';
char symbol = '@';

// ASCII value
char newline = 10;  // Same as '\n'
char null_char = 0; // String terminator
```

**Size:** 1 byte (8 bits), range: -128 to 127 (signed) or 0 to 255 (unsigned)

### **4. Void Type (`void`)**

```c
// Functions that don't return a value
void print_message() {
    printf("Hello!");
}

// Pointers to void (generic pointers)
void *generic_ptr;
int *int_ptr = &some_int;
generic_ptr = int_ptr;  // Valid conversion
```

---

## 📏 Sizeof Operator

The `sizeof` operator returns the size of a data type or variable in bytes.

### **Basic Usage**
```c
#include <stdio.h>

int main() {
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Size of char: %zu bytes\n", sizeof(char));

    return 0;
}
```

### **Advanced Usage**
```c
// Size of variables
int num = 10;
printf("Size of variable num: %zu bytes\n", sizeof(num));

// Size of expressions
printf("Size of expression: %zu bytes\n", sizeof(num + 1));

// Size of arrays
int arr[10];
printf("Size of array: %zu bytes\n", sizeof(arr));
printf("Number of elements: %zu\n", sizeof(arr) / sizeof(int));
```

---

## 🔄 Type Conversion

Type conversion changes a value from one data type to another.

### **1. Implicit Conversion (Automatic)**

```c
#include <stdio.h>

int main() {
    int num = 10;
    float result;

    result = num;  // int to float (automatic)
    printf("Result: %f\n", result);  // Output: 10.000000

    // Character to integer
    char ch = 'A';
    int ascii = ch;  // 'A' = 65 in ASCII
    printf("ASCII value of A: %d\n", ascii);

    return 0;
}
```

### **2. Explicit Conversion (Casting)**

```c
#include <stdio.h>

int main() {
    // Float to int (data loss possible)
    float pi = 3.14159;
    int truncated = (int)pi;  // Explicit cast
    printf("Original: %f, Truncated: %d\n", pi, truncated);

    // Larger to smaller type
    long big_num = 100000;
    short small_num = (short)big_num;
    printf("Big: %ld, Small: %d\n", big_num, small_num);

    // Pointer casting
    int num = 42;
    void *void_ptr = &num;
    int *int_ptr = (int*)void_ptr;  // Cast void* to int*
    printf("Value: %d\n", *int_ptr);

    return 0;
}
```

### **Type Conversion Hierarchy**
```
long double  ←  Highest precedence
     ↓
   double
     ↓
    float
     ↓
   unsigned long long
     ↓
    long long
     ↓
   unsigned long
     ↓
     long
     ↓
   unsigned int
     ↓
     int
     ↓
   unsigned short
     ↓
    short
     ↓
   unsigned char
     ↓
     char    ←  Lowest precedence
```

### **Advanced Type Conversion Examples**

#### **Complex Type Conversions**
```c
#include <stdio.h>

int main() {
    // Pointer conversions
    int num = 42;
    void *void_ptr = &num;
    int *int_ptr = (int*)void_ptr;
    printf("Pointer conversion: %d\n", *int_ptr);

    // Function pointer conversions
    int (*func_ptr)(int, int);
    func_ptr = (int (*)(int, int))add;  // Cast function pointer

    // Array to pointer decay
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;  // Implicit conversion
    printf("Array decay: %d\n", *(ptr + 2));

    return 0;
}
```

#### **Type Conversion with Structures**
```c
#include <stdio.h>

struct Small {
    char c;
    short s;
};

struct Large {
    char c;
    int i;
    double d;
};

int main() {
    struct Small small = {'A', 42};
    struct Large large;

    // Dangerous: copying different structures
    // memcpy(&large, &small, sizeof(struct Small));

    // Safe: member-wise conversion
    large.c = small.c;
    large.i = small.s;  // Type conversion
    large.d = 0.0;

    printf("Converted: %c, %d, %.1f\n", large.c, large.i, large.d);

    return 0;
}
```

#### **Union-Based Type Conversion**
```c
#include <stdio.h>

union Converter {
    int i;
    float f;
    unsigned char bytes[4];
};

int main() {
    union Converter conv;

    // Float to int conversion through union
    conv.f = 3.14159f;
    printf("Float as int: %d\n", conv.i);

    // Int to bytes
    conv.i = 0x12345678;
    printf("Bytes: %02X %02X %02X %02X\n",
           conv.bytes[0], conv.bytes[1],
           conv.bytes[2], conv.bytes[3]);

    return 0;
}
```

---

## 🏷️ Type Qualifiers

Type qualifiers modify the properties of variables.

### **1. `const` Qualifier**
```c
// Constant variable
const int MAX_SIZE = 100;
const float PI = 3.14159;

// Constant pointer
int num = 10;
const int *ptr1 = &num;     // Pointer to constant int
int *const ptr2 = &num;     // Constant pointer to int
const int *const ptr3 = &num;  // Constant pointer to constant int

// Arrays
const int days[7] = {1, 2, 3, 4, 5, 6, 7};
```

### **2. `volatile` Qualifier**
```c
// Variables that can be changed by external factors
volatile int sensor_reading;
volatile unsigned char *port = (unsigned char *)0x40000000;

// Used in embedded systems
volatile int interrupt_flag = 0;
```

### **3. `restrict` Qualifier (C99)**
```c
// Promises that pointers don't alias
void copy_array(int *restrict dest, int *restrict src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Advanced restrict usage
void process_data(int *restrict input, int *restrict output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = input[i] * 2;
        // Compiler can optimize knowing input != output
    }
}
```

### **4. `_Atomic` Qualifier (C11)**
```c
#include <stdatomic.h>

// Atomic variables for thread-safe operations
_Atomic int counter = 0;

void increment_counter() {
    atomic_fetch_add(&counter, 1);  // Thread-safe increment
}

int get_counter() {
    return atomic_load(&counter);  // Thread-safe read
}
```

### **5. `_Noreturn` Function Specifier (C11)**
```c
#include <stdlib.h>

// Function that never returns
_Noreturn void fatal_error(const char* message) {
    fprintf(stderr, "Fatal error: %s\n", message);
    exit(EXIT_FAILURE);
    // No return statement needed
}
```

### **6. `_Alignas` and `_Alignof` (C11)**
```c
// Specify alignment requirements
_Alignas(16) char buffer[1024];  // Align to 16-byte boundary

// Check alignment
size_t alignment = _Alignof(int);  // Get alignment of int
printf("int alignment: %zu\n", alignment);
```

---

## 📊 Storage Classes

Storage classes determine the lifetime and scope of variables.

### **1. Automatic Variables (`auto`)**
```c
void function() {
    auto int local_var = 10;  // Explicit auto (default)
    int another_var = 20;     // Implicit auto
    // Variables exist only within function scope
}
```

### **2. Static Variables (`static`)**
```c
void counter_function() {
    static int count = 0;  // Initialized only once
    count++;
    printf("Count: %d\n", count);
}

int main() {
    counter_function();  // Count: 1
    counter_function();  // Count: 2
    counter_function();  // Count: 3
    return 0;
}
```

### **3. External Variables (`extern`)**
```c
// File 1: main.c
#include <stdio.h>
extern int global_var;  // Declaration

int main() {
    printf("Global: %d\n", global_var);
    return 0;
}

// File 2: data.c
int global_var = 42;  // Definition
```

### **4. Register Variables (`register`)**
```c
// Suggest compiler to store in CPU register
register int fast_var = 100;
register char loop_counter;

// Commonly used in loops for performance
for (register int i = 0; i < 1000000; i++) {
    // Fast loop variable
}
```

---

## 🔍 Derived Data Types

### **1. Arrays**
```c
// One-dimensional arrays
int numbers[5] = {1, 2, 3, 4, 5};
char name[20] = "John Doe";

// Multi-dimensional arrays
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
```

### **2. Pointers**
```c
// Basic pointers
int num = 10;
int *ptr = &num;  // Pointer to int

// Pointer to pointer
int **ptr_to_ptr = &ptr;

// Function pointers
int (*func_ptr)(int, int) = &add_numbers;
```

### **3. Structures**
```c
// Structure definition
struct Student {
    char name[50];
    int roll_number;
    float marks;
};

// Structure usage
struct Student s1 = {"John", 101, 85.5};
struct Student *ptr = &s1;

// Nested structures
struct Address {
    char street[100];
    char city[50];
    char state[20];
    int zip_code;
};

struct Person {
    char name[50];
    int age;
    struct Address address;
};

// Anonymous structures (C11)
struct {
    int x, y;
} point = {10, 20};
```

### **Bit Fields in Structures**
```c
#include <stdio.h>

// Bit fields for memory-efficient storage
struct StatusFlags {
    unsigned int is_active : 1;    // 1 bit
    unsigned int is_admin : 1;     // 1 bit
    unsigned int priority : 2;     // 2 bits (0-3)
    unsigned int user_id : 12;     // 12 bits
    unsigned int reserved : 16;    // 16 bits
};

struct NetworkPacket {
    unsigned int version : 4;      // IP version
    unsigned int header_len : 4;   // Header length
    unsigned int type_of_service : 8;
    unsigned int total_length : 16;
    // ... more fields
};

int main() {
    struct StatusFlags flags = {0};

    flags.is_active = 1;
    flags.is_admin = 0;
    flags.priority = 3;  // Highest priority
    flags.user_id = 1234;

    printf("Active: %d, Admin: %d, Priority: %d, UserID: %d\n",
           flags.is_active, flags.is_admin, flags.priority, flags.user_id);

    printf("Size of struct: %zu bytes\n", sizeof(struct StatusFlags));

    return 0;
}
```

### **Advanced Structure Techniques**

#### **Flexible Array Members (C99)**
```c
#include <stdlib.h>
#include <string.h>

struct String {
    size_t length;
    char data[];  // Flexible array member
};

struct String* create_string(const char* str) {
    size_t len = strlen(str);
    struct String* s = malloc(sizeof(struct String) + len + 1);
    if (s) {
        s->length = len;
        strcpy(s->data, str);
    }
    return s;
}

int main() {
    struct String* str = create_string("Hello, World!");
    printf("Length: %zu, Content: %s\n", str->length, str->data);
    free(str);
    return 0;
}
```

#### **Structure Alignment and Padding**
```c
#include <stdio.h>

// Natural alignment
struct Natural {
    char c;      // 1 byte
    int i;       // 4 bytes (aligned to 4-byte boundary)
    char c2;     // 1 byte, but padded to 4-byte boundary
}; // Total: 12 bytes

// Packed structure
#pragma pack(1)
struct Packed {
    char c;      // 1 byte
    int i;       // 4 bytes
    char c2;     // 1 byte
}; // Total: 6 bytes
#pragma pack()

// Explicit alignment (C11)
struct Aligned {
    char c;
    _Alignas(8) int i;  // Force 8-byte alignment
    char c2;
};

int main() {
    printf("Natural: %zu, Packed: %zu, Aligned: %zu\n",
           sizeof(struct Natural),
           sizeof(struct Packed),
           sizeof(struct Aligned));
    return 0;
}
```

### **4. Unions**
```c
// Union definition
union Data {
    int i;
    float f;
    char str[20];
};

// Union usage
union Data data;
data.i = 10;
printf("Integer: %d\n", data.i);
```

---

## 📏 Memory Layout and Alignment

### **Structure Padding**
```c
#include <stdio.h>

struct Example {
    char c;      // 1 byte
    int i;       // 4 bytes
    char c2;     // 1 byte
};

int main() {
    printf("Size of struct: %zu bytes\n", sizeof(struct Example));
    // Output: 12 bytes (due to padding)
    return 0;
}
```

### **Controlling Alignment**
```c
// Packed structure (no padding)
#pragma pack(1)
struct PackedExample {
    char c;
    int i;
    char c2;
};
#pragma pack()

// Aligned structure
struct AlignedExample {
    char c;
    int i __attribute__((aligned(8)));
    char c2;
};
```

---

## 🎯 Best Practices

### **1. Choose Appropriate Data Types**
```c
// ✅ Good: Use smallest sufficient type
unsigned char age;        // 0-255 years
short int temperature;    // -32K to +32K Celsius

// ❌ Bad: Unnecessarily large types
long long int small_num;  // Waste of memory
double exact_int;         // Precision loss for integers
```

### **2. Use Meaningful Names**
```c
// ✅ Good
int student_age;
float account_balance;
char user_initial;

// ❌ Bad
int a;
float x;
char c;
```

### **3. Initialize Variables**
```c
// ✅ Always initialize
int count = 0;
float rate = 0.0f;
char *name = NULL;

// ❌ Uninitialized variables
int uninitialized;  // Contains garbage value
```

### **4. Use Constants for Fixed Values**
```c
// ✅ Use const for constants
const int MAX_STUDENTS = 100;
const float PI = 3.14159f;

// ❌ Don't use magic numbers
int grades[100];  // What does 100 represent?
```

---

## 🐛 Common Mistakes and Solutions

### **1. Integer Overflow**
```c
// Problem
int big_num = 2147483647;  // INT_MAX
big_num = big_num + 1;     // Overflow!

// Solution
long long safe_num = 2147483648LL;
```

### **2. Precision Loss**
```c
// Problem
float precise = 3.141592653589793;
printf("%.15f\n", precise);  // Loses precision

// Solution
double more_precise = 3.141592653589793;
printf("%.15f\n", more_precise);
```

### **3. Wrong Type Conversion**
```c
// Problem
int result = 5 / 2;        // Result: 2 (integer division)

// Solution
float result = 5.0f / 2.0f;  // Result: 2.5
// Or
float result = (float)5 / 2;
```

### **4. Uninitialized Pointers**
```c
// Problem
int *ptr;      // Points to random memory
*ptr = 10;     // Crash!

// Solution
int *ptr = NULL;
int value = 10;
ptr = &value;
```

---

## 📝 Practice Exercises

### **Exercise 1: Data Type Sizes**
Write a program to display the size of all primitive data types on your system.

### **Exercise 2: Type Conversion**
Create a program that demonstrates:
- Implicit conversion between numeric types
- Explicit casting with data loss examples
- Pointer type casting

### **Exercise 3: Memory Layout**
Create structures and observe how padding affects their size. Use `sizeof` to verify.

### **Exercise 4: Constants and Qualifiers**
Implement a program using:
- `const` variables
- `volatile` variables (simulate with a loop)
- Different storage classes

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the typical size of `int` on a 32-bit system?
a) 1 byte
b) 2 bytes
c) 4 bytes
d) 8 bytes

### **Question 2:**
Which type qualifier makes a variable read-only?
a) `static`
b) `volatile`
c) `const`
d) `register`

### **Question 3:**
What happens when you assign a `float` to an `int` variable?
a) Compilation error
b) Runtime error
c) Implicit conversion (decimal part lost)
d) No conversion needed

### **Question 4:**
Which storage class keeps the variable value between function calls?
a) `auto`
b) `static`
c) `extern`
d) `register`

### **Question 5:**
What is the size of `long double` typically?
a) 4 bytes
b) 8 bytes
c) 10-16 bytes
d) 2 bytes

---

## 🔗 Additional Resources

### **Platform-Specific Sizes**
```c
// Check sizes on your system
printf("char: %zu\n", sizeof(char));
printf("short: %zu\n", sizeof(short));
printf("int: %zu\n", sizeof(int));
printf("long: %zu\n", sizeof(long));
printf("long long: %zu\n", sizeof(long long));
```

### **Further Reading**
- [Data Types in C](https://en.cppreference.com/w/c/language/type)
- [Type Qualifiers](https://en.cppreference.com/w/c/language/qualifier)
- [Storage Classes](https://en.cppreference.com/w/c/language/storage_duration)

---

## 🎯 Next Steps

**Great progress!** You've mastered:
- ✅ Primitive and derived data types
- ✅ Variable declaration and initialization
- ✅ Type conversion techniques
- ✅ Storage classes and qualifiers
- ✅ Memory layout and alignment

**Next Lesson Preview:**
- Arithmetic, relational, and logical operators
- Bitwise and shift operators
- Ternary operator tricks
- Operator precedence table

---

**🚀 Ready to explore operators and expressions?**

[⬅️ Previous: Lexical Structure](03_Lexical_Structure.md) | [Next: Operators ➡️](05_Operators.md)