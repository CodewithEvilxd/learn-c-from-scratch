# 🎯 Assignment 1.2: Variables and Data Types

## 📋 Problem Statement

Create a C program that demonstrates the use of different data types and variables. The program should declare variables of different types, assign values to them, and display their values.

## 🎯 Learning Objectives

- Understand different data types in C
- Learn variable declaration and initialization
- Practice formatted output with `printf()`
- Understand memory usage of different types

## 📝 Requirements

1. Declare variables of all primitive data types
2. Initialize variables with appropriate values
3. Display values using `printf()` with correct format specifiers
4. Show the size of each data type using `sizeof()`
5. Include comments explaining each data type

## 💡 Hints

- Use `%d` for integers, `%f` for floats, `%c` for characters
- Use `%lu` for `sizeof()` results
- Initialize variables at declaration time
- Use meaningful variable names

## 🔧 Solution

```c
// Assignment 1.2: Variables and Data Types
// This program demonstrates different data types in C

#include <stdio.h>

int main() {
    // Integer types
    int integer_var = 42;                    // Basic integer
    short short_var = 32767;                 // Short integer
    long long_var = 2147483647L;             // Long integer
    long long long_long_var = 9223372036854775807LL;  // Long long integer

    // Unsigned integer types
    unsigned int unsigned_int = 4294967295U;
    unsigned short unsigned_short = 65535;
    unsigned long unsigned_long = 4294967295UL;

    // Floating point types
    float float_var = 3.14159f;
    double double_var = 3.141592653589793;
    long double long_double_var = 3.141592653589793238L;

    // Character type
    char char_var = 'A';
    unsigned char unsigned_char = 255;

    // Display integer values
    printf("=== Integer Types ===\n");
    printf("int: %d (size: %lu bytes)\n", integer_var, sizeof(int));
    printf("short: %d (size: %lu bytes)\n", short_var, sizeof(short));
    printf("long: %ld (size: %lu bytes)\n", long_var, sizeof(long));
    printf("long long: %lld (size: %lu bytes)\n", long_long_var, sizeof(long long));

    // Display unsigned integer values
    printf("\n=== Unsigned Integer Types ===\n");
    printf("unsigned int: %u (size: %lu bytes)\n", unsigned_int, sizeof(unsigned int));
    printf("unsigned short: %u (size: %lu bytes)\n", unsigned_short, sizeof(unsigned short));
    printf("unsigned long: %lu (size: %lu bytes)\n", unsigned_long, sizeof(unsigned long));

    // Display floating point values
    printf("\n=== Floating Point Types ===\n");
    printf("float: %f (size: %lu bytes)\n", float_var, sizeof(float));
    printf("double: %lf (size: %lu bytes)\n", double_var, sizeof(double));
    printf("long double: %Lf (size: %lu bytes)\n", long_double_var, sizeof(long double));

    // Display character values
    printf("\n=== Character Types ===\n");
    printf("char: %c (ASCII: %d, size: %lu bytes)\n", char_var, char_var, sizeof(char));
    printf("unsigned char: %c (ASCII: %d, size: %lu bytes)\n", unsigned_char, unsigned_char, sizeof(unsigned char));

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Execution
```
Expected Output:
=== Integer Types ===
int: 42 (size: 4 bytes)
short: 32767 (size: 2 bytes)
long: 2147483647 (size: 4 bytes)
long long: 9223372036854775807 (size: 8 bytes)

=== Unsigned Integer Types ===
unsigned int: 4294967295 (size: 4 bytes)
unsigned short: 65535 (size: 2 bytes)
unsigned long: 4294967295 (size: 4 bytes)

=== Floating Point Types ===
float: 3.141590 (size: 4 bytes)
double: 3.141593 (size: 8 bytes)
long double: 3.141593 (size: 12 bytes)

=== Character Types ===
char: A (ASCII: 65, size: 1 bytes)
unsigned char: ÿ (ASCII: 255, size: 1 bytes)
```

### Test Case 2: Size Verification
```
Command: gcc data_types.c -o data_types && ./data_types
Expected: Program runs without errors and displays correct sizes
```

## 🔍 Explanation

1. **Integer Types**: `int`, `short`, `long`, `long long` for whole numbers
2. **Unsigned Types**: Same as signed but only non-negative values
3. **Floating Point**: `float`, `double`, `long double` for decimal numbers
4. **Character Types**: `char` for single characters, stores ASCII values
5. **sizeof() Operator**: Returns size in bytes of data types
6. **Format Specifiers**: Different format codes for different data types

## 🎯 Key Concepts Covered

- Primitive data types
- Variable declaration and initialization
- Memory sizes of data types
- Format specifiers in printf
- Signed vs unsigned types
- Floating point precision

## 🚀 Extensions

1. Add boolean values using `<stdbool.h>`
2. Demonstrate type casting between different types
3. Show overflow behavior with large values
4. Add user input for variable values