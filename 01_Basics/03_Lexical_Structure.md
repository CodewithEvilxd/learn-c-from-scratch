# 📝 Lesson 3: Lexical Structure & Tokens
## Building Blocks of C Programs

---

## 🎯 Learning Objectives

- Understand lexical structure of C programs
- Learn about tokens and their types
- Master keywords, identifiers, and constants
- Understand escape sequences and comments
- Write well-structured C code

---

## 📖 What is Lexical Structure?

**Lexical structure** refers to the basic building blocks (tokens) that make up a C program. The C compiler breaks down the source code into these tokens during the lexical analysis phase (also called tokenization or scanning).

### **The Lexical Analysis Process**

1. **Input Reading**: Source code is read character by character
2. **Token Recognition**: Characters are grouped into meaningful tokens
3. **Whitespace Handling**: Spaces, tabs, and newlines are discarded (except in strings)
4. **Comment Processing**: Comments are identified and removed
5. **Error Detection**: Invalid tokens are flagged as lexical errors

### **Token Types in C**
1. **Keywords** - Reserved words with special meaning (32 total)
2. **Identifiers** - Names given to variables, functions, structures, etc.
3. **Constants** - Fixed numeric, character, or string values
4. **String Literals** - Sequences of characters enclosed in quotes
5. **Operators** - Symbols for arithmetic, logical, and other operations
6. **Punctuators** - Special characters like `{}`, `()`, `;`, `,`
7. **Header Names** - File names in `#include` directives

### **Lexical Grammar Rules**

#### **Token Separation**
```c
// Tokens are separated by whitespace or punctuators
int a=5;     // Valid: int, a, =, 5, ;
inta=5;      // Invalid: 'inta' is not a valid token

// Whitespace is required between certain tokens
intint a;    // Invalid: 'intint' is not a valid token
int int a;   // Invalid: two type specifiers
```

#### **Maximum Token Length**
```c
// C89/C90: Identifiers significant to 31 characters
// C99/C11: Identifiers significant to 63 characters
// Internal identifiers: No limit (implementation defined)

int very_long_identifier_name_that_might_cause_issues_in_older_compilers;
int very_long_identifier_name_that_might_cause_issues_in_older_compilers_different;  // Same as above in C89
```

#### **Case Sensitivity**
```c
// C is case-sensitive
int Variable;
int variable;  // Different from above
INT variable;  // Error: 'INT' is not a keyword
```

---

## 🔑 Keywords in C

C has **32 reserved keywords** that cannot be used as identifiers:

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

### **Example Usage**
```c
// Using various keywords
int main() {
    const int MAX_SIZE = 100;  // const keyword
    static int counter = 0;    // static keyword
    register int i;            // register keyword

    for (i = 0; i < MAX_SIZE; i++) {  // for, int keywords
        if (i % 2 == 0) {             // if keyword
            printf("%d ", i);
        }
    }

    return 0;  // return keyword
}
```

---

## 🏷️ Identifiers

**Identifiers** are names given to various program elements like variables, functions, arrays, etc.

### **Rules for Identifiers**
1. **First character** must be a letter (A-Z, a-z) or underscore (_)
2. **Subsequent characters** can be letters, digits (0-9), or underscore
3. **Case sensitive** - `name` and `Name` are different
4. **No keywords** allowed as identifiers
5. **No special characters** except underscore
6. **Length** - First 31 characters are significant (C89), more in C99/C11

### **Valid Identifiers**
```c
// Valid identifiers
int age;
float salary;
char name_1;
double _temp;
int student_id;
void display_info();
```

### **Invalid Identifiers**
```c
// Invalid identifiers
int 1name;      // Starts with digit
float sal ary;  // Space not allowed
char int;       // Keyword
double temp-var; // Special character (-)
```

### **Naming Conventions**
```c
// Good naming practices
int student_age;        // snake_case
int StudentAge;         // PascalCase
int studentAge;         // camelCase

// Constants (uppercase with underscores)
#define MAX_SIZE 100
const int PI_VALUE = 3.14;

// Functions (verbs or verb phrases)
void calculate_total();
int get_student_count();
void display_result();
```

---

## 🔢 Constants and Literals

**Constants** are fixed values that cannot be changed during program execution.

### **Integer Constants**
```c
// Decimal (base 10)
int decimal = 123;

// Octal (base 8) - starts with 0
int octal = 0123;    // 123 in octal = 83 in decimal

// Hexadecimal (base 16) - starts with 0x or 0X
int hex = 0x123;     // 123 in hex = 291 in decimal
int hex2 = 0XABC;    // ABC in hex = 2748 in decimal

// Long integers - end with L or l
long big_num = 123456L;

// Unsigned integers - end with U or u
unsigned int positive = 123U;
```

### **Floating-Point Constants**
```c
// Standard notation
float pi = 3.14159;
double gravity = 9.81;

// Scientific notation
double avogadro = 6.022e23;    // 6.022 × 10^23
float small_num = 1.23e-4;     // 1.23 × 10^-4

// Long double - end with L or l
long double precise = 3.141592653589793L;
```

### **Character Constants**
```c
// Single characters
char letter = 'A';
char digit = '5';
char symbol = '@';

// Escape sequences
char newline = '\n';
char tab = '\t';
char backslash = '\\';
char single_quote = '\'';
char double_quote = '\"';
```

### **String Literals**
```c
// String constants
char greeting[] = "Hello, World!";
char name[50] = "John Doe";

// Multi-line strings (concatenation)
char message[] = "This is a long message "
                 "that spans multiple lines";

// Empty string
char empty[] = "";
```

---

## 🎭 Escape Sequences

**Escape sequences** are special character combinations that represent characters that cannot be typed directly.

### **Common Escape Sequences**

| Escape Sequence | Character Represented | Description |
|----------------|------------------------|-------------|
| `\n` | Newline | Moves cursor to next line |
| `\t` | Horizontal Tab | Moves cursor to next tab stop |
| `\v` | Vertical Tab | Moves cursor vertically |
| `\b` | Backspace | Moves cursor one position left |
| `\r` | Carriage Return | Moves cursor to beginning of line |
| `\f` | Form Feed | Moves cursor to next page |
| `\a` | Alert (Bell) | Produces audible alert |
| `\\` | Backslash | Literal backslash character |
| `\'` | Single Quote | Literal single quote |
| `\"` | Double Quote | Literal double quote |
| `\?` | Question Mark | Literal question mark |
| `\0` | Null Character | String terminator |

### **Examples**
```c
#include <stdio.h>

int main() {
    // Using escape sequences
    printf("Name:\tJohn Doe\n");
    printf("Age:\t25\n");
    printf("City:\tNew York\n\n");

    printf("He said, \"Hello!\"\n");
    printf("Path: C:\\Program Files\\App\n");
    printf("Question: What\'s your name?\n");

    // Alert sound
    printf("Task completed!\a\n");

    return 0;
}
```

**Output:**
```
Name:   John Doe
Age:    25
City:   New York

He said, "Hello!"
Path: C:\Program Files\App
Question: What's your name?
Task completed! [beep]
```

---

## 💬 Comments in C

**Comments** are explanatory text ignored by the compiler. They help other programmers understand the code and are crucial for maintainable software.

### **Single-Line Comments**
```c
// This is a single-line comment
int age = 25;  // Variable declaration with inline comment

// Comments can be placed anywhere
printf("Hello");  // This prints Hello

// TODO: Implement error handling
// FIXME: This function has a bug
// NOTE: Remember to free memory
```

### **Multi-Line Comments**
```c
/*
 * This is a multi-line comment
 * It can span multiple lines
 * Used for detailed explanations
 */

/*
 * Function: calculate_average
 * Purpose: Calculates the average of an array of numbers
 * Parameters:
 *   - arr: Pointer to the array
 *   - size: Number of elements in the array
 * Returns: The average value as a double
 */
double calculate_average(int* arr, int size) {
    /* Multi-line comment
       inside function */
    return 0.0;
}
```

### **Advanced Comment Techniques**

#### **Conditional Comments**
```c
// Compile-time conditional comments
#ifdef DEBUG
    // Debug version comments
    printf("Debug: value = %d\n", value);
#endif

#ifndef PRODUCTION
    // Development-only comments
    log_debug_info();
#endif
```

#### **Doxygen Documentation Comments**
```c
/**
 * @brief Calculates the factorial of a number
 * @param n The number to calculate factorial for
 * @return The factorial of n
 * @note n should be non-negative
 * @warning This function may cause stack overflow for large n
 * @see fibonacci()
 */
int factorial(int n) {
    if (n < 0) return -1;  // Error case
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

#### **File Header Comments**
```c
/**
 * @file calculator.c
 * @brief Implementation of basic calculator functions
 * @author John Doe
 * @date 2024-01-15
 * @version 1.0
 * @copyright MIT License
 */

#include <stdio.h>
#include "calculator.h"
```

#### **Function Comments**
```c
/**
 * @brief Adds two integers
 * @param a First integer
 * @param b Second integer
 * @return Sum of a and b
 * @pre a and b are valid integers
 * @post Return value is a + b
 */
int add(int a, int b) {
    return a + b;
}
```

### **Comment Styles and Conventions**

#### **Block Comments**
```c
/******************************************************************************/
/* Function Name: main                                                       */
/* Purpose: Entry point of the program                                       */
/* Parameters: argc - number of command line arguments                      */
/*            argv - array of command line arguments                        */
/* Returns: 0 on success, non-zero on failure                               */
/******************************************************************************/
int main(int argc, char* argv[]) {
    // Implementation
    return 0;
}
```

#### **Inline Comments**
```c
int result = calculate(a, b);  // Calculate result using a and b
if (result > 0) {              // Check if result is positive
    process_positive(result);  // Process positive results
} else {                       // Handle negative or zero results
    handle_error();            // Error handling
}
```

#### **End-of-Line Comments**
```c
#define MAX_SIZE 100    /* Maximum array size */
#define PI 3.14159      /* Value of pi */
#define DEBUG 1         /* Enable debug mode */
```

### **Best Practices for Comments**

#### **When to Comment**
```c
// ✅ Comment complex logic
for (int i = 0; i < size; i += 2) {  // Process every other element
    // Complex algorithm here
}

// ✅ Comment workarounds
result *= 1.1;  // Workaround for floating-point precision issue

// ✅ Comment assumptions
if (ptr != NULL) {  // Assuming ptr was allocated earlier
    // Safe to use ptr
}
```

#### **What NOT to Comment**
```c
// ❌ Don't comment obvious code
int sum = a + b;  // Add a and b

// ❌ Don't comment bad code (fix the code instead)
temp = x; x = y; y = temp;  // Swap x and y

// ❌ Don't contradict the code
if (x > 0) return true;  // Return false if x is negative
```

#### **Comment Maintenance**
```c
// ✅ Keep comments synchronized with code
void old_function() { /* TODO: Remove this function */ }

// ❌ Outdated comments
void process_data(int data) {
    // This function used to validate data
    // Now it just processes it
    // TODO: Add validation back
}
```

### **Comment Extraction Tools**

#### **Using GCC to Extract Comments**
```bash
# Extract comments from source code
gcc -fpreprocessed -dD -E source.c | grep -A5 -B5 "comment"

# Generate documentation from comments
doxygen Doxyfile
```

#### **Comment Analysis**
```c
// Self-documenting code with good naming
void process_user_data(UserData* user_data, ProcessingOptions options) {
    validate_user_data(user_data);      // Clear intent
    apply_processing_options(user_data, options);
    save_processed_data(user_data);
}

// Less clear without comments
void proc_ud(ud* u, po opt) {  // What do these mean?
    val_ud(u);
    app_po(u, opt);
    sav_pd(u);
}
```

### **Comment Standards**

#### **Javadoc Style**
```c
/**
 * @brief Brief description
 * @details Detailed description
 * @param[in] input_param Description of input parameter
 * @param[out] output_param Description of output parameter
 * @return Description of return value
 * @note Special notes
 * @warning Warnings about usage
 * @see Related functions or files
 */
```

#### **Qt Style**
```c
/*!
 * \brief Brief description
 * \details Detailed description
 * \param input_param Description
 * \return Description
 * \sa Related functions
 */
```

#### **Microsoft Style**
```c
/// <summary>Brief description</summary>
/// <param name="param">Parameter description</param>
/// <returns>Return value description</returns>
```

---

## 🔤 Character Set

C uses the **ASCII character set** (American Standard Code for Information Interchange).

### **Character Categories**

#### **Letters (52 characters)**
- Uppercase: A-Z (65-90 in ASCII)
- Lowercase: a-z (97-122 in ASCII)

#### **Digits (10 characters)**
- 0-9 (48-57 in ASCII)

#### **Special Characters**
```c
! @ # $ % ^ & * ( ) _ - + = { } [ ] | \ : ; " ' < > , . ? / ~
```

#### **White Space Characters**
- Space (32)
- Horizontal Tab (\t, 9)
- Vertical Tab (\v, 11)
- Form Feed (\f, 12)
- Carriage Return (\r, 13)
- Newline (\n, 10)

---

## 📝 Complete Program Example

```c
// Program to demonstrate lexical elements
#include <stdio.h>

// Constants
#define PI 3.14159
#define MAX_SIZE 100

int main() {
    // Variable declarations (identifiers)
    int age, count;
    float salary, area;
    char grade, name[50];

    // Integer constants
    age = 25;
    count = 10;

    // Floating-point constants
    salary = 50000.50;
    area = PI * 5 * 5;  // Using defined constant

    // Character constants
    grade = 'A';

    // String literals
    strcpy(name, "John Doe");

    // Output with escape sequences
    printf("Employee Details:\n");
    printf("Name:\t%s\n", name);
    printf("Age:\t%d years\n", age);
    printf("Grade:\t%c\n", grade);
    printf("Salary:\t%.2f\n", salary);
    printf("Area:\t%.2f\n", area);

    return 0;
}
```

---

## 🐛 Common Lexical Errors

### **1. Invalid Identifiers**
```c
// Errors
int 1st_number;    // Cannot start with digit
int my-name;       // Hyphen not allowed
int int;           // Keyword cannot be used
int my name;       // Space not allowed
```

### **2. Unclosed Strings**
```c
// Error
printf("Hello, World!);  // Missing closing quote

// Correct
printf("Hello, World!");
```

### **3. Invalid Escape Sequences**
```c
// Error
printf("Path: C:\temp\file.txt");  // Invalid escape sequences

// Correct
printf("Path: C:\\temp\\file.txt");
```

### **4. Unclosed Comments**
```c
// Error - unclosed multi-line comment
/*
printf("This will not execute");

/* Correct */
printf("This will execute");
```

---

## 🎯 Practice Exercises

### **Exercise 1: Identifier Validation**
Identify which of the following are valid identifiers:
```c
int myVariable;
float 2ndNumber;
char _name;
double temp-var;
int for;
char my_name;
int MyName;
```

### **Exercise 2: Constants Practice**
Write a program that demonstrates:
- Integer constants in decimal, octal, and hexadecimal
- Floating-point constants in standard and scientific notation
- Character constants with escape sequences
- String literals

### **Exercise 3: Comments Exercise**
Add appropriate comments to the following code:
```c
#include <stdio.h>
int main() {
    int num1 = 10, num2 = 20;
    int sum = num1 + num2;
    printf("Sum: %d\n", sum);
    return 0;
}
```

### **Exercise 4: Escape Sequences**
Create a program that displays a formatted table using escape sequences for:
- Tabs for alignment
- Newlines for rows
- Proper spacing

---

## 🧠 Quiz: Test Your Understanding

### **Question 1:**
Which of the following is NOT a valid identifier?
a) `myVariable`
b) `_temp`
c) `2ndNumber`
d) `my_name`

### **Question 2:**
What does the escape sequence `\n` do?
a) Creates a new line
b) Creates a tab
c) Creates a backspace
d) Creates a form feed

### **Question 3:**
Which of the following is a keyword in C?
a) `name`
b) `age`
c) `int`
d) `sum`

### **Question 4:**
What is the correct way to write a single-line comment?
a) `/* comment */`
b) `// comment`
c) `# comment`
d) `<!-- comment -->`

### **Question 5:**
Which constant represents the hexadecimal number 255?
a) `255`
b) `0377`
c) `0xFF`
d) `0b11111111`

---

## 🔗 Additional Resources

### **ASCII Table Reference**
```c
// ASCII values for common characters
'A' = 65, 'a' = 97
'0' = 48, '9' = 57
' ' = 32 (space)
'\n' = 10 (newline)
'\t' = 9 (tab)
```

### **Further Reading**
- [C Keywords](https://en.cppreference.com/w/c/keyword)
- [Escape Sequences](https://en.cppreference.com/w/c/language/escape)
- [ASCII Table](https://www.asciitable.com/)

---

## 🎯 Next Steps

**Excellent work!** You've learned:
- ✅ Keywords and their usage
- ✅ Rules for identifiers
- ✅ Different types of constants
- ✅ Escape sequences
- ✅ Comment styles
- ✅ Character set

**Next Lesson Preview:**
- Variables and data types
- Type qualifiers and modifiers
- Type conversion
- Storage sizes and ranges

---

**🚀 Ready to explore variables and data types?**

[⬅️ Previous: Environment Setup](02_Environment_Setup.md) | [Next: Variables & Data Types ➡️](04_Variables_Data_Types.md)