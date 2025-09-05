# 🎯 Assignment 1.1: Hello World Program

## 📋 Problem Statement

Write a C program that displays "Hello, World!" on the screen.

## 🎯 Learning Objectives

- Understand basic C program structure
- Learn how to use `printf()` function
- Master compilation and execution process
- Understand main function syntax

## 📝 Requirements

1. Use `printf()` function to display text
2. Include proper header files
3. Use correct main function syntax
4. Return 0 from main function
5. Add proper comments

## 💡 Hints

- Include `<stdio.h>` header for `printf()`
- Main function should return `int`
- Use `\n` for newline character
- Don't forget semicolon after statements

## 🔧 Solution

```c
// Assignment 1.1: Hello World Program
// This program displays "Hello, World!" on the screen

#include <stdio.h>  // Include standard input/output header

int main() {  // Main function - program entry point
    // Display message using printf function
    printf("Hello, World!\n");

    // Return 0 to indicate successful execution
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Execution
```
Input: (none)
Expected Output:
Hello, World!
```

### Test Case 2: Compilation Check
```
Command: gcc hello.c -o hello
Expected: No compilation errors
```

### Test Case 3: Execution Check
```
Command: ./hello
Expected Output:
Hello, World!
```

## 🔍 Explanation

1. **Header Inclusion**: `#include <stdio.h>` includes the standard I/O library needed for `printf()`
2. **Main Function**: `int main()` is the entry point of every C program
3. **Print Statement**: `printf("Hello, World!\n");` outputs the text to console
4. **Return Statement**: `return 0;` indicates successful program execution
5. **Newline Character**: `\n` moves cursor to next line

## 🎯 Key Concepts Covered

- Basic program structure
- Function declarations
- String literals
- Escape sequences
- Return values
- Header files

## 🚀 Extensions

1. Modify the program to display your name
2. Add multiple printf statements
3. Include current date/time
4. Add ASCII art