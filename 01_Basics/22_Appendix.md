# 📚 Appendix: C Language Reference
## Reserved Keywords, ASCII Table, Escape Sequences, Standard Libraries, Interview Questions, C vs Other Languages

---

## 🎯 Learning Objectives

- Master C reserved keywords and their usage
- Understand ASCII character encoding
- Learn all escape sequences
- Explore standard libraries
- Prepare for C programming interviews
- Compare C with other programming languages

---

## 🔑 C Reserved Keywords

C language has **32 reserved keywords** that cannot be used as identifiers:

### **Data Type Keywords**
```c
// Primary data types
int     // Integer numbers
float   // Floating-point numbers
double  // Double precision floating-point
char    // Single characters
void    // No value/empty

// Type modifiers
short   // Short integer
long    // Long integer
signed  // Signed numbers (default)
unsigned // Unsigned numbers
```

### **Control Flow Keywords**
```c
// Conditional statements
if      // Conditional execution
else    // Alternative execution
switch  // Multi-way selection
case    // Case in switch
default // Default case

// Loops
for     // For loop
while   // While loop
do      // Do-while loop

// Jump statements
break   // Exit loop/switch
continue // Skip iteration
return  // Return from function
goto    // Unconditional jump
```

### **Storage Class Keywords**
```c
auto    // Automatic storage (default)
static  // Static storage
extern  // External linkage
register // Register storage
const   // Constant value
volatile // Volatile variable
```

### **Other Keywords**
```c
sizeof  // Size of data type
typedef // Type definition
enum    // Enumeration
struct  // Structure
union   // Union
```

### **C99/C11 Keywords**
```c
// C99 additions
_Bool       // Boolean type
_Complex    // Complex numbers
_Imaginary  // Imaginary numbers
inline      // Inline functions
restrict    // Restricted pointers

// C11 additions
_Alignas    // Alignment specification
_Alignof    // Alignment query
_Atomic     // Atomic operations
_Generic    // Generic selection
_Noreturn   // Function doesn't return
_Static_assert // Static assertion
_Thread_local // Thread-local storage
```

---

## 🔤 ASCII Character Set

### **ASCII Control Characters (0-31)**
| Dec | Hex | Char | Description |
|-----|-----|------|-------------|
| 0   | 00  | NUL  | Null character |
| 1   | 01  | SOH  | Start of Header |
| 2   | 02  | STX  | Start of Text |
| 3   | 03  | ETX  | End of Text |
| 4   | 04  | EOT  | End of Transmission |
| 5   | 05  | ENQ  | Enquiry |
| 6   | 06  | ACK  | Acknowledgment |
| 7   | 07  | BEL  | Bell |
| 8   | 08  | BS   | Backspace |
| 9   | 09  | HT   | Horizontal Tab |
| 10  | 0A  | LF   | Line Feed |
| 11  | 0B  | VT   | Vertical Tab |
| 12  | 0C  | FF   | Form Feed |
| 13  | 0D  | CR   | Carriage Return |
| 14  | 0E  | SO   | Shift Out |
| 15  | 0F  | SI   | Shift In |
| 16  | 10  | DLE  | Data Link Escape |
| 17  | 11  | DC1  | Device Control 1 |
| 18  | 12  | DC2  | Device Control 2 |
| 19  | 13  | DC3  | Device Control 3 |
| 20  | 14  | DC4  | Device Control 4 |
| 21  | 15  | NAK  | Negative Acknowledgment |
| 22  | 16  | SYN  | Synchronous Idle |
| 23  | 17  | ETB  | End of Transmission Block |
| 24  | 18  | CAN  | Cancel |
| 25  | 19  | EM   | End of Medium |
| 26  | 1A  | SUB  | Substitute |
| 27  | 1B  | ESC  | Escape |
| 28  | 1C  | FS   | File Separator |
| 29  | 1D  | GS   | Group Separator |
| 30  | 1E  | RS   | Record Separator |
| 31  | 1F  | US   | Unit Separator |

### **ASCII Printable Characters (32-126)**
| Dec | Hex | Char | Dec | Hex | Char | Dec | Hex | Char |
|-----|-----|------|-----|-----|------|-----|-----|------|
| 32  | 20  | Space| 64  | 40  | @    | 96  | 60  | `    |
| 33  | 21  | !    | 65  | 41  | A    | 97  | 61  | a    |
| 34  | 22  | "    | 66  | 42  | B    | 98  | 62  | b    |
| 35  | 23  | #    | 67  | 43  | C    | 99  | 63  | c    |
| 36  | 24  | $    | 68  | 44  | D    | 100 | 64  | d    |
| 37  | 25  | %    | 69  | 45  | E    | 101 | 65  | e    |
| 38  | 26  | &    | 70  | 46  | F    | 102 | 66  | f    |
| 39  | 27  | '    | 71  | 47  | G    | 103 | 67  | g    |
| 40  | 28  | (    | 72  | 48  | H    | 104 | 68  | h    |
| 41  | 29  | )    | 73  | 49  | I    | 105 | 69  | i    |
| 42  | 2A  | *    | 74  | 4A  | J    | 106 | 6A  | j    |
| 43  | 2B  | +    | 75  | 4B  | K    | 107 | 6B  | k    |
| 44  | 2C  | ,    | 76  | 4C  | L    | 108 | 6C  | l    |
| 45  | 2D  | -    | 77  | 4D  | M    | 109 | 6D  | m    |
| 46  | 2E  | .    | 78  | 4E  | N    | 110 | 6E  | n    |
| 47  | 2F  | /    | 79  | 4F  | O    | 111 | 6F  | o    |
| 48  | 30  | 0    | 80  | 50  | P    | 112 | 70  | p    |
| 49  | 31  | 1    | 81  | 51  | Q    | 113 | 71  | q    |
| 50  | 32  | 2    | 82  | 52  | R    | 114 | 72  | r    |
| 51  | 33  | 3    | 83  | 53  | S    | 115 | 73  | s    |
| 52  | 34  | 4    | 84  | 54  | T    | 116 | 74  | t    |
| 53  | 35  | 5    | 85  | 55  | U    | 117 | 75  | u    |
| 54  | 36  | 6    | 86  | 56  | V    | 118 | 76  | v    |
| 55  | 37  | 7    | 87  | 57  | W    | 119 | 77  | w    |
| 56  | 38  | 8    | 88  | 58  | X    | 120 | 78  | x    |
| 57  | 39  | 9    | 89  | 59  | Y    | 121 | 79  | y    |
| 58  | 3A  | :    | 90  | 5A  | Z    | 122 | 7A  | z    |
| 59  | 3B  | ;    | 91  | 5B  | [    | 123 | 7B  | {    |
| 60  | 3C  | <    | 92  | 5C  | \    | 124 | 7C  | \|   |
| 61  | 3D  | =    | 93  | 5D  | ]    | 125 | 7D  | }    |
| 62  | 3E  | >    | 94  | 5E  | ^    | 126 | 7E  | ~    |
| 63  | 3F  | ?    | 95  | 5F  | _    |      |     |      |

### **Extended ASCII (128-255)**
Extended ASCII characters vary by code page. Common examples:
- 128-159: Various symbols and accented characters
- 160-255: International characters, symbols, and line drawing characters

---

## 🎭 Escape Sequences

### **Common Escape Sequences**
| Escape Sequence | Character Represented | ASCII Value | Description |
|----------------|------------------------|-------------|-------------|
| `\a` | BEL | 7   | Alert (bell) |
| `\b` | BS  | 8   | Backspace |
| `\f` | FF  | 12  | Form feed |
| `\n` | LF  | 10  | Newline (line feed) |
| `\r` | CR  | 13  | Carriage return |
| `\t` | HT  | 9   | Horizontal tab |
| `\v` | VT  | 11  | Vertical tab |
| `\\` | \   | 92  | Backslash |
| `\'` | '   | 39  | Single quote |
| `\"` | "   | 34  | Double quote |
| `\?` | ?   | 63  | Question mark |
| `\0` | NUL | 0   | Null character |

### **Octal Escape Sequences**
```c
// \ followed by 1-3 octal digits
char ch1 = '\7';      // Bell (7 in octal)
char ch2 = '\77';     // ? (63 in decimal, 77 in octal)
char ch3 = '\377';    // ÿ (255 in decimal, 377 in octal)
```

### **Hexadecimal Escape Sequences**
```c
// \x followed by hexadecimal digits
char ch1 = '\x7';     // Bell (7 in hex)
char ch2 = '\x3F';    // ? (63 in decimal, 3F in hex)
char ch3 = '\xFF';    // ÿ (255 in decimal, FF in hex)
```

### **Universal Character Names (C99)**
```c
// \u followed by 4 hex digits (Unicode BMP)
// \U followed by 8 hex digits (full Unicode)
char ch1 = '\u0041';  // 'A' (Unicode U+0041)
char ch2 = '\U00000041'; // 'A' (same as above)
```

---

## 📚 Standard Libraries in C

### **Core Libraries**

#### **1. `<stdio.h>` - Standard Input/Output**
```c
// File operations
FILE* fopen(const char* filename, const char* mode);
int fclose(FILE* stream);
size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);

// Formatted I/O
int printf(const char* format, ...);
int scanf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);

// Character I/O
int getchar(void);
int putchar(int ch);
int getc(FILE* stream);
int putc(int ch, FILE* stream);

// String I/O
char* gets(char* str);  // Deprecated, use fgets
int puts(const char* str);
char* fgets(char* str, int n, FILE* stream);
int fputs(const char* str, FILE* stream);
```

#### **2. `<stdlib.h>` - Standard Library**
```c
// Memory management
void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

// Program control
void exit(int status);
int atexit(void (*func)(void));
int system(const char* command);

// Conversions
int atoi(const char* str);
long atol(const char* str);
double atof(const char* str);
long strtol(const char* str, char** endptr, int base);

// Random numbers
int rand(void);
void srand(unsigned int seed);

// Searching and sorting
void* bsearch(const void* key, const void* base, size_t num, size_t size,
              int (*compar)(const void*, const void*));
void qsort(void* base, size_t num, size_t size,
           int (*compar)(const void*, const void*));
```

#### **3. `<string.h>` - String Operations**
```c
// String length
size_t strlen(const char* str);

// String copying
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);

// String concatenation
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);

// String comparison
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t n);

// String searching
char* strchr(const char* str, int ch);
char* strrchr(const char* str, int ch);
char* strstr(const char* haystack, const char* needle);

// Memory operations
void* memcpy(void* dest, const void* src, size_t n);
void* memmove(void* dest, const void* src, size_t n);
void* memset(void* ptr, int value, size_t n);
int memcmp(const void* ptr1, const void* ptr2, size_t n);
```

#### **4. `<math.h>` - Mathematical Functions**
```c
// Trigonometric functions
double sin(double x);
double cos(double x);
double tan(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double atan2(double y, double x);

// Hyperbolic functions
double sinh(double x);
double cosh(double x);
double tanh(double x);

// Exponential and logarithmic
double exp(double x);
double log(double x);      // Natural log
double log10(double x);    // Base-10 log
double pow(double base, double exp);
double sqrt(double x);

// Rounding and absolute value
double ceil(double x);
double floor(double x);
double round(double x);
double fabs(double x);

// Constants
#define M_PI 3.14159265358979323846
#define M_E  2.71828182845904523536
```

#### **5. `<ctype.h>` - Character Classification**
```c
// Character classification
int isalnum(int ch);   // Alphanumeric
int isalpha(int ch);   // Alphabetic
int isdigit(int ch);   // Digit
int isxdigit(int ch);  // Hexadecimal digit
int isspace(int ch);   // White space
int isprint(int ch);   // Printable
int isgraph(int ch);   // Graphical
int iscntrl(int ch);   // Control character
int ispunct(int ch);   // Punctuation

// Character conversion
int tolower(int ch);
int toupper(int ch);
```

#### **6. `<time.h>` - Time and Date**
```c
// Time types
typedef long time_t;
typedef long clock_t;

// Time functions
time_t time(time_t* timer);
char* ctime(const time_t* timer);
struct tm* localtime(const time_t* timer);
struct tm* gmtime(const time_t* timer);
time_t mktime(struct tm* timeptr);

// Formatted time
size_t strftime(char* str, size_t maxsize, const char* format,
                const struct tm* timeptr);

// CPU time
clock_t clock(void);
```

### **Other Important Libraries**

#### **7. `<assert.h>` - Debugging**
```c
void assert(int expression);
```

#### **8. `<errno.h>` - Error Numbers**
```c
extern int errno;
// Various error constants like EINVAL, ENOENT, etc.
```

#### **9. `<limits.h>` - Implementation Limits**
```c
// Integer limits
CHAR_BIT    // Bits in a char
CHAR_MIN    // Minimum char value
CHAR_MAX    // Maximum char value
INT_MIN     // Minimum int value
INT_MAX     // Maximum int value
LONG_MIN    // Minimum long value
LONG_MAX    // Maximum long value
```

#### **10. `<float.h>` - Floating-Point Limits**
```c
FLT_MIN     // Minimum float value
FLT_MAX     // Maximum float value
FLT_DIG     // Decimal digits of precision
DBL_MIN     // Minimum double value
DBL_MAX     // Maximum double value
DBL_DIG     // Decimal digits of precision
```

---

## ❓ Common Interview Questions in C

### **Basic Questions**

#### **1. What is the difference between `malloc` and `calloc`?**
```c
// malloc: Allocates memory without initialization
int* ptr1 = (int*)malloc(5 * sizeof(int));
// Memory contains garbage values

// calloc: Allocates and initializes memory to zero
int* ptr2 = (int*)calloc(5, sizeof(int));
// Memory initialized to 0
```

#### **2. What is the difference between `struct` and `union`?**
```c
struct Person {
    char name[50];
    int age;
    float salary;
}; // Size: 50 + 4 + 4 = 58 bytes

union Data {
    char name[50];
    int age;
    float salary;
}; // Size: 50 bytes (largest member)
```

#### **3. Explain pointer arithmetic**
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;

printf("%d\n", *ptr);      // 10
printf("%d\n", *(ptr+1));  // 20
printf("%d\n", ptr[2]);    // 30

// Pointer arithmetic considers data type
ptr++;  // Moves by sizeof(int) bytes
```

#### **4. What is the `volatile` keyword?**
```c
volatile int sensor_value;

// Tells compiler that value can change unexpectedly
// Prevents certain optimizations
// Used for:
// - Hardware registers
// - Shared variables in multi-threaded programs
// - Signal handlers
```

### **Intermediate Questions**

#### **5. How does function call work?**
```c
// Stack frame creation
void func(int param) {
    int local = 10;
    // param and local stored on stack
}

// Calling convention
func(5);
// 1. Push parameters on stack
// 2. Push return address
// 3. Jump to function
// 4. Execute function
// 5. Pop stack frame
// 6. Return to caller
```

#### **6. Explain memory layout of C program**
```
+------------------+  High Address
| Command line args|
| Environment vars |
+------------------+
|       Stack      |  ← Grows downward
|        ↓         |
|        ↑         |
|       Heap       |  ← Grows upward
+------------------+
| Global variables |
|     Constants    |
|       Code       |
+------------------+  Low Address
```

#### **7. What are dangling pointers?**
```c
int* dangling_ptr() {
    int local_var = 42;
    return &local_var;  // Bad: returning address of local variable
}

int main() {
    int* ptr = dangling_ptr();
    // local_var no longer exists
    // *ptr is undefined behavior
}
```

### **Advanced Questions**

#### **8. Implement `strcpy` without using library functions**
```c
char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}
```

#### **9. Reverse a linked list**
```c
struct Node* reverse_list(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}
```

#### **10. Find loop in linked list (Floyd's Cycle Detection)**
```c
int has_loop(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1;  // Loop detected
        }
    }

    return 0;  // No loop
}
```

---

## ⚖️ C vs Other Programming Languages

### **C vs C++**

| Aspect | C | C++ |
|--------|---|-----|
| **Paradigm** | Procedural | Multi-paradigm (OOP + Procedural) |
| **Features** | Basic constructs | Classes, inheritance, polymorphism |
| **Memory Management** | Manual | Manual + RAII |
| **Standard Library** | Minimal | Rich STL |
| **Performance** | Excellent | Excellent (similar to C) |
| **Learning Curve** | Steep | Steeper |
| **Use Cases** | System programming, embedded | Application development, games |

### **C vs Java**

| Aspect | C | Java |
|--------|---|------|
| **Execution** | Compiled to native | Compiled to bytecode, JIT |
| **Memory Management** | Manual | Automatic (Garbage Collection) |
| **Platform Independence** | No (recompile needed) | Yes (JVM) |
| **Performance** | Very high | High (with optimizations) |
| **Safety** | Low (buffer overflows, etc.) | High (bounds checking, etc.) |
| **Development Speed** | Slow | Fast |
| **Use Cases** | System software, performance-critical | Enterprise applications, Android |

### **C vs Python**

| Aspect | C | Python |
|--------|---|--------|
| **Typing** | Static | Dynamic |
| **Syntax** | Complex | Simple, readable |
| **Performance** | Very high | Lower (interpreted) |
| **Development Speed** | Slow | Very fast |
| **Memory Management** | Manual | Automatic |
| **Learning Curve** | Steep | Gentle |
| **Use Cases** | System programming, games | Scripting, data science, web |

### **C vs Rust**

| Aspect | C | Rust |
|--------|---|------|
| **Memory Safety** | Manual (unsafe) | Automatic (ownership, borrowing) |
| **Concurrency** | Manual (error-prone) | Safe concurrency primitives |
| **Performance** | Excellent | Excellent (zero-cost abstractions) |
| **Learning Curve** | Moderate | Steep |
| **Ecosystem** | Mature | Growing |
| **Use Cases** | Legacy systems, embedded | New systems, safety-critical |

### **C vs Go**

| Aspect | C | Go |
|--------|---|-----|
| **Concurrency** | Manual (threads, pthreads) | Built-in goroutines |
| **Garbage Collection** | No | Yes |
| **Compilation Speed** | Fast | Very fast |
| **Syntax** | Complex | Simple |
| **Standard Library** | Minimal | Rich |
| **Use Cases** | System programming | Network services, cloud |

---

## 🎯 Best Practices for C Programming

### **1. Code Organization**
```c
// Header files (.h)
#ifndef MYHEADER_H
#define MYHEADER_H

// Function declarations
// Type definitions
// Macros

#endif

// Source files (.c)
// Include headers
// Implement functions
```

### **2. Error Handling**
```c
#define CHECK_NULL(ptr) \
    if (ptr == NULL) { \
        fprintf(stderr, "Null pointer error in %s:%d\n", __FILE__, __LINE__); \
        exit(1); \
    }

#define CHECK_ALLOC(ptr) \
    if (ptr == NULL) { \
        fprintf(stderr, "Memory allocation failed in %s:%d\n", __FILE__, __LINE__); \
        exit(1); \
    }
```

### **3. Memory Management**
```c
// Always check allocation
int* arr = (int*)malloc(n * sizeof(int));
if (arr == NULL) {
    // Handle error
}

// Always free memory
free(arr);
arr = NULL;  // Prevent dangling pointer
```

### **4. Input Validation**
```c
int safe_read_int(int min, int max) {
    int value;
    while (scanf("%d", &value) != 1 || value < min || value > max) {
        printf("Invalid input. Enter value between %d and %d: ", min, max);
        while (getchar() != '\n');  // Clear input buffer
    }
    return value;
}
```

---

## 🚀 Next Steps

**Congratulations!** You've completed the comprehensive C Language Reference.

### **What You've Learned:**
- ✅ C reserved keywords and their usage
- ✅ ASCII character encoding system
- ✅ All escape sequences in C
- ✅ Standard libraries and their functions
- ✅ Common interview questions and solutions
- ✅ Comparisons with other programming languages

### **Recommended Next Steps:**
1. **Practice coding problems** on platforms like LeetCode, HackerRank
2. **Contribute to open-source C projects** on GitHub
3. **Learn system programming** concepts (processes, threads, networking)
4. **Explore embedded systems** programming
5. **Study advanced topics** like compiler design, operating systems

**Remember**: C is the foundation of modern computing. Mastering C opens doors to understanding how computers work at the lowest level.

---

**🎓 Your C Programming Journey is Complete!**

[⬅️ Previous: Final Project](21_Final_Project.md) | [🏠 Back to Main README](../README.md)