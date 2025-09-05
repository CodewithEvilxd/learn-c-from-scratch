# ⚡ Lesson 5: Operators in C
## Expressions and Operator Precedence

---

## 🎯 Learning Objectives

- Master all types of operators in C
- Understand operator precedence and associativity
- Learn bitwise operations and their applications
- Master the ternary operator
- Understand operator overloading concepts

---

## 📖 What are Operators?

**Operators** are symbols that perform operations on variables and values. C provides a rich set of operators for different types of operations.

### **Categories of Operators**
1. **Arithmetic Operators** - Mathematical operations
2. **Relational Operators** - Comparisons
3. **Logical Operators** - Boolean operations
4. **Bitwise Operators** - Bit-level operations
5. **Assignment Operators** - Value assignment
6. **Increment/Decrement** - Counter operations
7. **Conditional (Ternary)** - Conditional expressions
8. **Special Operators** - sizeof, comma, etc.

---

## ➕ Arithmetic Operators

Arithmetic operators perform mathematical operations.

### **Basic Arithmetic**
```c
#include <stdio.h>

int main() {
    int a = 10, b = 3;

    printf("Addition: %d + %d = %d\n", a, b, a + b);        // 13
    printf("Subtraction: %d - %d = %d\n", a, b, a - b);     // 7
    printf("Multiplication: %d * %d = %d\n", a, b, a * b);  // 30
    printf("Division: %d / %d = %d\n", a, b, a / b);        // 3 (integer division)
    printf("Modulus: %d %% %d = %d\n", a, b, a % b);        // 1 (remainder)

    return 0;
}
```

### **Floating-Point Arithmetic**
```c
#include <stdio.h>

int main() {
    float x = 10.5f, y = 3.2f;

    printf("Float Division: %.2f / %.2f = %.2f\n", x, y, x / y);
    printf("Mixed Division: %d / %.2f = %.2f\n", 10, y, 10 / y);

    return 0;
}
```

### **Common Mistakes**
```c
// Integer division
int result = 5 / 2;        // Result: 2 (not 2.5)

// Modulus with negative numbers
int mod1 = 7 % 3;          // Result: 1
int mod2 = (-7) % 3;       // Result: -1 (implementation defined)
int mod3 = 7 % (-3);       // Result: 1 (implementation defined)
```

---

## 🔍 Relational Operators

Relational operators compare two values and return boolean results (0 for false, 1 for true).

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20;

    printf("a == b: %d\n", a == b);    // Equal to: 0 (false)
    printf("a != b: %d\n", a != b);    // Not equal to: 1 (true)
    printf("a < b: %d\n", a < b);      // Less than: 1 (true)
    printf("a > b: %d\n", a > b);      // Greater than: 0 (false)
    printf("a <= b: %d\n", a <= b);    // Less than or equal: 1 (true)
    printf("a >= b: %d\n", a >= b);    // Greater than or equal: 0 (false)

    return 0;
}
```

### **Chaining Comparisons**
```c
// Valid in C
int x = 5;
if (0 < x < 10) {  // This works differently than expected!
    printf("x is between 0 and 10\n");
}

// Correct way
if (x > 0 && x < 10) {
    printf("x is between 0 and 10\n");
}
```

---

## 🤔 Logical Operators

Logical operators perform boolean operations.

```c
#include <stdio.h>

int main() {
    int a = 1, b = 0;  // 1 = true, 0 = false

    printf("a && b: %d\n", a && b);    // AND: 0 (false)
    printf("a || b: %d\n", a || b);    // OR: 1 (true)
    printf("!a: %d\n", !a);            // NOT: 0 (false)
    printf("!b: %d\n", !b);            // NOT: 1 (true)

    return 0;
}
```

### **Short-Circuit Evaluation**
```c
#include <stdio.h>

int test_function() {
    printf("Function called!\n");
    return 1;
}

int main() {
    int a = 0, b = 1;

    // Short-circuit AND: if first is false, second is not evaluated
    if (a && test_function()) {
        printf("Both true\n");
    }

    // Short-circuit OR: if first is true, second is not evaluated
    if (b || test_function()) {
        printf("At least one true\n");
    }

    return 0;
}
```

---

## 🔧 Bitwise Operators

Bitwise operators work on individual bits of data.

### **Basic Bitwise Operations**
```c
#include <stdio.h>

int main() {
    unsigned char a = 60;  // 0011 1100 in binary
    unsigned char b = 13;  // 0000 1101 in binary

    printf("a & b: %d\n", a & b);    // AND: 12 (0000 1100)
    printf("a | b: %d\n", a | b);    // OR: 61 (0011 1101)
    printf("a ^ b: %d\n", a ^ b);    // XOR: 49 (0011 0001)
    printf("~a: %d\n", ~a);          // NOT: 195 (1100 0011)
    printf("a << 2: %d\n", a << 2);  // Left shift: 240 (1111 0000)
    printf("a >> 2: %d\n", a >> 2);  // Right shift: 15 (0000 1111)

    return 0;
}
```

### **Bitwise Applications**

#### **1. Fast Multiplication/Division by Powers of 2**
```c
// Multiplication by 2^n
int multiply_by_8 = x << 3;    // Same as x * 8
int multiply_by_16 = x << 4;   // Same as x * 16

// Division by 2^n
int divide_by_4 = x >> 2;      // Same as x / 4
int divide_by_8 = x >> 3;      // Same as x / 8
```

#### **2. Checking if Number is Even/Odd**
```c
// Check if even (last bit is 0)
if ((num & 1) == 0) {
    printf("Even number\n");
}

// Check if odd (last bit is 1)
if (num & 1) {
    printf("Odd number\n");
}
```

#### **3. Setting/Clearing/Toggling Bits**
```c
// Set bit at position n
number |= (1 << n);

// Clear bit at position n
number &= ~(1 << n);

// Toggle bit at position n
number ^= (1 << n);

// Check if bit is set
if (number & (1 << n)) {
    printf("Bit %d is set\n", n);
}
```

#### **4. Swapping Two Numbers**
```c
// Using XOR (no temporary variable needed)
a = a ^ b;
b = a ^ b;
a = a ^ b;
```

#### **5. Finding Absolute Value**
```c
// Using bitwise operations
int abs_value = (num ^ (num >> 31)) - (num >> 31);

// Or using mask
int abs_value = (num + (num >> 31)) ^ (num >> 31);
```

#### **6. Checking if Power of 2**
```c
// Method 1: Using bitwise AND
int is_power_of_2 = (num > 0) && ((num & (num - 1)) == 0);

// Method 2: Using bitwise operations
int is_power_of_2 = num && !(num & (num - 1));
```

#### **7. Counting Set Bits (Population Count)**
```c
// Method 1: Brian Kernighan's algorithm
int count_bits(unsigned int num) {
    int count = 0;
    while (num) {
        num &= (num - 1);
        count++;
    }
    return count;
}

// Method 2: Lookup table (for 8-bit numbers)
int bit_count[256] = {0}; // Initialize with bit counts
int count = bit_count[num & 0xFF] + bit_count[(num >> 8) & 0xFF] +
           bit_count[(num >> 16) & 0xFF] + bit_count[num >> 24];
```

#### **8. Reversing Bits**
```c
unsigned int reverse_bits(unsigned int num) {
    unsigned int result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (num & 1);
        num >>= 1;
    }
    return result;
}
```

#### **9. Finding Rightmost Set Bit**
```c
// Method 1: Using two's complement
int rightmost_set_bit = num & -num;

// Method 2: Using bitwise operations
int rightmost_set_bit = num & ~(num - 1);
```

#### **10. Bit Manipulation Macros**
```c
#define SET_BIT(num, pos)    ((num) |= (1U << (pos)))
#define CLEAR_BIT(num, pos)  ((num) &= ~(1U << (pos)))
#define TOGGLE_BIT(num, pos) ((num) ^= (1U << (pos)))
#define CHECK_BIT(num, pos)  ((num) & (1U << (pos)))

// Usage
unsigned int flags = 0;
SET_BIT(flags, 3);     // Set bit 3
if (CHECK_BIT(flags, 3)) {
    printf("Bit 3 is set\n");
}
```

#### **11. Bit Masking**
```c
// Extracting fields from packed data
#define EXTRACT_FIELD(value, mask, shift) (((value) & (mask)) >> (shift))

// Example: Extract RGB components from 32-bit color
unsigned int color = 0xFF804020;  // ARGB format
unsigned char red   = EXTRACT_FIELD(color, 0x00FF0000, 16);
unsigned char green = EXTRACT_FIELD(color, 0x0000FF00, 8);
unsigned char blue  = EXTRACT_FIELD(color, 0x000000FF, 0);
```

#### **12. Endianness Detection**
```c
int is_little_endian() {
    unsigned int num = 1;
    return *(unsigned char*)&num == 1;
}

int is_big_endian() {
    return !is_little_endian();
}
```

#### **13. Fast Division and Multiplication**
```c
// Fast multiplication by constants
#define MUL_BY_7(x)  (((x) << 3) - (x))    // 8x - x = 7x
#define MUL_BY_9(x)  (((x) << 3) + (x))    // 8x + x = 9x
#define MUL_BY_15(x) (((x) << 4) - (x))    // 16x - x = 15x

// Fast division by constants (when x >= 0)
#define DIV_BY_2(x)   ((x) >> 1)
#define DIV_BY_4(x)   ((x) >> 2)
#define DIV_BY_8(x)   ((x) >> 3)
```

#### **14. Gray Code Conversion**
```c
// Binary to Gray code
unsigned int binary_to_gray(unsigned int num) {
    return num ^ (num >> 1);
}

// Gray code to Binary
unsigned int gray_to_binary(unsigned int num) {
    unsigned int mask = num;
    while (mask) {
        mask >>= 1;
        num ^= mask;
    }
    return num;
}
```

---

## 📈 Assignment Operators

Assignment operators assign values to variables.

### **Basic Assignment**
```c
int x = 10;    // Simple assignment
int y = x;     // Copy value
```

### **Compound Assignment**
```c
int a = 10;

a += 5;    // a = a + 5;  Result: 15
a -= 3;    // a = a - 3;  Result: 12
a *= 2;    // a = a * 2;  Result: 24
a /= 4;    // a = a / 4;  Result: 6
a %= 5;    // a = a % 5;  Result: 1

// Bitwise compound assignment
a &= 3;    // a = a & 3;
a |= 2;    // a = a | 2;
a ^= 1;    // a = a ^ 1;
a <<= 2;   // a = a << 2;
a >>= 1;   // a = a >> 1;
```

---

## 🔄 Increment/Decrement Operators

Increment and decrement operators modify variables by 1.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 5;

    // Post-increment: use then increment
    printf("Post-increment: %d\n", a++);  // Prints 5, then a becomes 6
    printf("After post-increment: %d\n", a);  // Prints 6

    // Pre-increment: increment then use
    printf("Pre-increment: %d\n", ++b);   // b becomes 6, then prints 6
    printf("After pre-increment: %d\n", b);   // Prints 6

    return 0;
}
```

### **Complex Expressions**
```c
int x = 5, y = 10, z;

z = x++ + ++y;  // z = 5 + 11 = 16, x=6, y=11
z = ++x + y++;  // z = 7 + 11 = 18, x=7, y=12
z = x-- + --y;  // z = 7 + 10 = 17, x=6, y=10
```

---

## ❓ Ternary (Conditional) Operator

The ternary operator is a shorthand for if-else statements.

### **Basic Syntax**
```c
condition ? expression1 : expression2
```

### **Examples**
```c
#include <stdio.h>

int main() {
    int age = 20;
    int voting_age = 18;

    // Simple ternary
    char *status = (age >= voting_age) ? "Eligible" : "Not eligible";
    printf("Voting status: %s\n", status);

    // Nested ternary
    int score = 85;
    char grade = (score >= 90) ? 'A' :
                 (score >= 80) ? 'B' :
                 (score >= 70) ? 'C' : 'F';
    printf("Grade: %c\n", grade);

    // In assignments
    int max = (a > b) ? a : b;
    int min = (a < b) ? a : b;

    return 0;
}
```

### **Advanced Usage**
```c
// In function calls
printf("Number is %s\n", (num % 2 == 0) ? "even" : "odd");

// In return statements
int absolute(int x) {
    return (x >= 0) ? x : -x;
}

// Multiple operations
(num > 0) ? printf("Positive\n") : printf("Non-positive\n");
```

---

## 📊 Special Operators

### **1. sizeof Operator**
```c
#include <stdio.h>

int main() {
    int arr[10];
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of array: %zu bytes\n", sizeof(arr));
    printf("Number of elements: %zu\n", sizeof(arr) / sizeof(int));

    // sizeof with expressions
    printf("Size of expression: %zu\n", sizeof(5 + 10));

    // sizeof with types
    printf("Size of long double: %zu\n", sizeof(long double));

    return 0;
}
```

### **2. Comma Operator**
```c
#include <stdio.h>

int main() {
    int a, b, c;

    // Multiple assignments
    a = (b = 5, c = 10, b + c);  // a = 15

    // In loops
    for (int i = 0, j = 10; i < j; i++, j--) {
        printf("i=%d, j=%d\n", i, j);
    }

    // In function calls
    printf("%d\n", (a = 5, b = 10, a + b));  // Prints 15

    return 0;
}
```

### **3. Address Operator (&)**
```c
int num = 42;
int *ptr = &num;  // Get address of num

// Address of array elements
int arr[5] = {1, 2, 3, 4, 5};
int *ptr2 = &arr[2];  // Address of third element
```

### **4. Dereference Operator (* )**
```c
int num = 42;
int *ptr = &num;
int value = *ptr;  // Get value at address stored in ptr

// Multiple indirection
int **ptr_to_ptr = &ptr;
int dereferenced = **ptr_to_ptr;  // Same as *ptr
```

### **5. Member Access Operators**
```c
struct Student {
    char name[50];
    int roll_number;
};

struct Student s1 = {"John", 101};

// Dot operator (direct member access)
printf("Name: %s\n", s1.name);
printf("Roll: %d\n", s1.roll_number);

// Arrow operator (pointer member access)
struct Student *ptr = &s1;
printf("Name: %s\n", ptr->name);
printf("Roll: %d\n", ptr->roll_number);
```

### **6. Array Subscript Operator**
```c
int arr[5] = {10, 20, 30, 40, 50};

// Equivalent expressions
arr[2] = 100;           // Direct array access
*(arr + 2) = 100;       // Pointer arithmetic
*(2 + arr) = 100;       // Commutative property
2[arr] = 100;           // Unusual but valid syntax
```

### **7. Function Call Operator**
```c
// Function declaration
int add(int a, int b);

// Function call
int result = add(5, 3);

// Function pointer call
int (*func_ptr)(int, int) = &add;
result = func_ptr(5, 3);
result = (*func_ptr)(5, 3);
```

### **8. Type Cast Operator**
```c
int num = 42;
double decimal = (double)num;  // Explicit cast

// Cast in expressions
float result = (float)num / 3;

// Cast for pointers
void *void_ptr = &num;
int *int_ptr = (int*)void_ptr;
```

### **9. Conditional Operator (Ternary)**
```c
// Basic usage
int max = (a > b) ? a : b;

// Nested ternary
char grade = (score >= 90) ? 'A' :
             (score >= 80) ? 'B' :
             (score >= 70) ? 'C' : 'F';

// In assignments
int abs_value = (num >= 0) ? num : -num;
```

### **10. Sequence Point Operators**
```c
// Comma operator creates sequence points
int a = 1, b = 2, c = 3;

// Logical operators have sequence points
if ((a = 5) && (b = 10)) {
    // Both assignments happen
}

// Assignment operators
a = b = c = 10;  // Right to left
```

---

## 📋 Operator Precedence Table

Operators are evaluated according to precedence (priority) and associativity.

### **Complete Precedence Table (Highest to Lowest)**

| Precedence | Operator | Description | Associativity |
|------------|----------|-------------|---------------|
| 1 | `()` `[]` `->` `.` `++` `--` | Function call, array access, member access | Left to Right |
| 2 | `!` `~` `++` `--` `+` `-` `*` `&` `sizeof` | Logical NOT, bitwise NOT, unary operators | Right to Left |
| 3 | `*` `/` `%` | Multiplication, division, modulus | Left to Right |
| 4 | `+` `-` | Addition, subtraction | Left to Right |
| 5 | `<<` `>>` | Bitwise shift | Left to Right |
| 6 | `<` `<=` `>` `>=` | Relational operators | Left to Right |
| 7 | `==` `!=` | Equality operators | Left to Right |
| 8 | `&` | Bitwise AND | Left to Right |
| 9 | `^` | Bitwise XOR | Left to Right |
| 10 | `\|` | Bitwise OR | Left to Right |
| 11 | `&&` | Logical AND | Left to Right |
| 12 | `\|\|` | Logical OR | Left to Right |
| 13 | `?:` | Ternary operator | Right to Left |
| 14 | `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `\|=` `<<=` `>>=` | Assignment operators | Right to Left |
| 15 | `,` | Comma operator | Left to Right |

### **Precedence Examples**
```c
// Example 1: Multiplication before addition
int result = 2 + 3 * 4;  // result = 2 + 12 = 14

// Example 2: Parentheses override precedence
int result = (2 + 3) * 4;  // result = 5 * 4 = 20

// Example 3: Unary operators before binary
int result = -5 + 10;  // result = (-5) + 10 = 5

// Example 4: Assignment is right-associative
int a, b, c;
a = b = c = 10;  // All variables get value 10
```

---

## 🎯 Best Practices

### **1. Use Parentheses for Clarity**
```c
// ✅ Clear precedence
int result = (a + b) * (c - d);

// ❌ Confusing without parentheses
int result = a + b * c - d;  // What does this mean?
```

### **2. Avoid Complex Expressions**
```c
// ✅ Simple and clear
int discriminant = b * b - 4 * a * c;
if (discriminant >= 0) {
    // calculate roots
}

// ❌ Complex and confusing
if ((x = a + b * c) && (y = d - e / f) || (z = g % h)) {
    // what is this doing?
}
```

### **3. Use Increment/Decrement Wisely**
```c
// ✅ Clear usage
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}

// ❌ Confusing usage
int x = 5;
int result = x++ + ++x;  // Undefined behavior!
```

### **4. Bitwise Operations on Unsigned Types**
```c
// ✅ Use unsigned for bitwise operations
unsigned int flags = 0;
flags |= (1 << 3);  // Set bit 3

// ❌ Avoid signed types for bitwise
int signed_flags = 0;
signed_flags |= (1 << 31);  // May cause issues
```

## 🔧 Operator Overloading Concepts (C++ Comparison)

Although C doesn't support operator overloading natively, understanding the concept helps when working with C++ or other languages.

### **What is Operator Overloading?**
```cpp
// C++ example (not valid in C)
class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Overload + operator
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overload << operator for output
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real << " + " << c.imag << "i";
        return out;
    }
};

// Usage
Complex c1(1, 2), c2(3, 4);
Complex c3 = c1 + c2;  // Uses overloaded +
cout << c3;            // Uses overloaded <<
```

### **Simulating Operator Overloading in C**
```c
// Function-based approach
typedef struct {
    double real, imag;
} Complex;

Complex complex_add(Complex a, Complex b) {
    return (Complex){a.real + b.real, a.imag + b.imag};
}

void complex_print(Complex c) {
    printf("%.2f + %.2fi\n", c.real, c.imag);
}

// Usage
Complex c1 = {1, 2}, c2 = {3, 4};
Complex c3 = complex_add(c1, c2);
complex_print(c3);
```

### **Macro-Based Operator Simulation**
```c
#define ADD(a, b) ((a) + (b))
#define MUL(a, b) ((a) * (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Usage
int result = ADD(5, MUL(3, 2));  // 5 + (3 * 2) = 11
int maximum = MAX(x, y);
```

## 🔄 Advanced Operator Techniques

### **1. Expression Templates (Advanced)**
```c
// Lazy evaluation concept
#define EVAL(expr) (expr)

// Complex expressions with lazy evaluation
#define COMPLEX_EXPR(a, b, c) \
    EVAL((a) * (b) + (c))

// Usage
int result = COMPLEX_EXPR(x + 1, y * 2, z - 3);
```

### **2. Operator Precedence Macros**
```c
// Force evaluation order
#define FORCE_ORDER(expr) expr

// Group operations clearly
#define ADD_THEN_MULTIPLY(a, b, c) \
    FORCE_ORDER((a) + (b)) * (c)

#define MULTIPLY_THEN_ADD(a, b, c) \
    FORCE_ORDER((a) * (b)) + (c)
```

### **3. Type-Safe Operations**
```c
// Type-checking macros
#define CHECK_TYPE(var, type) \
    _Generic((var), type: (var), default: (type){0})

#define SAFE_ADD(a, b) \
    _Generic((a) + (b), \
        int: (a) + (b), \
        float: (a) + (b), \
        double: (a) + (b), \
        default: 0 \
    )
```

### **4. Compile-Time Computations**
```c
// Constexpr-like behavior with macros
#define FIBONACCI(n) \
    ((n) == 0 ? 0 : (n) == 1 ? 1 : FIBONACCI((n)-1) + FIBONACCI((n)-2))

#define FACTORIAL(n) \
    ((n) <= 1 ? 1 : (n) * FACTORIAL((n)-1))

// Usage (computed at compile time)
int fib_5 = FIBONACCI(5);  // 5
int fact_4 = FACTORIAL(4); // 24
```

### **5. Advanced Bitwise Algorithms**
```c
// Bit reversal using lookup table
static const unsigned char bit_reverse_table[256] = {
    0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0,
    // ... more values
};

unsigned int reverse_bits_fast(unsigned int num) {
    return (bit_reverse_table[num & 0xFF] << 24) |
           (bit_reverse_table[(num >> 8) & 0xFF] << 16) |
           (bit_reverse_table[(num >> 16) & 0xFF] << 8) |
           bit_reverse_table[num >> 24];
}

// Parallel bit counting
int count_bits_parallel(unsigned int num) {
    num = num - ((num >> 1) & 0x55555555);
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
    num = (num + (num >> 4)) & 0x0F0F0F0F;
    num = num + (num >> 8);
    num = num + (num >> 16);
    return num & 0x3F;
}
```

---

## 🐛 Common Mistakes

### **1. Assignment vs Comparison**
```c
// Wrong: assignment in condition
if (x = 5) {  // Always true!
    printf("x is 5\n");
}

// Correct: comparison
if (x == 5) {
    printf("x is 5\n");
}
```

### **2. Operator Precedence Confusion**
```c
// Wrong interpretation
int result = a & b == c;  // Interpreted as a & (b == c)

// Correct
int result = (a & b) == c;
```

### **3. Integer Division**
```c
// Unexpected result
float average = (a + b) / 2;  // Integer division if a and b are int

// Correct
float average = (a + b) / 2.0f;
```

### **4. Bitwise Operations on Signed Types**
```c
// Problematic on signed types
int num = -1;
num = num >> 1;  // Implementation defined behavior
```

---

## 📝 Practice Exercises

### **Exercise 1: Operator Precedence**
Predict the output of these expressions:
```c
int a = 5, b = 10, c = 15;
printf("%d\n", a + b * c);           // ?
printf("%d\n", (a + b) * c);         // ?
printf("%d\n", a > b ? a : b);       // ?
printf("%d\n", a & b | c);           // ?
```

### **Exercise 2: Bitwise Operations**
Write functions for:
- Check if a number is power of 2
- Count set bits in a number
- Reverse bits of a number
- Find position of rightmost set bit

### **Exercise 3: Ternary Operator**
Rewrite these if-else statements using ternary operator:
```c
if (score >= 90) {
    grade = 'A';
} else if (score >= 80) {
    grade = 'B';
} else {
    grade = 'C';
}
```

### **Exercise 4: Complex Expressions**
Simplify these expressions using operators:
- Check if a year is leap year
- Calculate BMI category
- Determine quadrant of a point
- Check if three numbers can form a triangle

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the result of `5 & 3` in binary?
a) 1
b) 7
c) 2
d) 8

### **Question 2:**
Which operator has higher precedence: `*` or `+`?
a) `*`
b) `+`
c) Same precedence
d) Depends on context

### **Question 3:**
What does the expression `a++ + ++a` result in?
a) Defined behavior
b) Undefined behavior
c) Compilation error
d) Platform dependent

### **Question 4:**
Which of these is equivalent to `x *= 3`?
a) `x = x * 3`
b) `x = x + 3`
c) `x = x / 3`
d) `x = x % 3`

### **Question 5:**
What is the ternary operator syntax?
a) `condition ? true : false`
b) `condition : true ? false`
c) `condition ? true : false : else`
d) `if condition then true else false`

---

## 🔗 Additional Resources

### **Bitwise Calculator**
```c
// Online bitwise calculators:
// - https://bitwisecmd.com/
// - https://www.calculator.net/bitwise-calculator.html
```

### **Further Reading**
- [Operator Precedence](https://en.cppreference.com/w/c/language/operator_precedence)
- [Bitwise Operations](https://en.wikipedia.org/wiki/Bitwise_operation)
- [Ternary Operator](https://en.cppreference.com/w/c/language/operator_other)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ All types of operators in C
- ✅ Operator precedence and associativity
- ✅ Bitwise operations and applications
- ✅ Ternary operator techniques
- ✅ Common operator pitfalls

**Next Lesson Preview:**
- Control flow statements (if-else, switch)
- Loops (for, while, do-while)
- Jump statements (break, continue, goto)
- Flowcharts and decision making

---

**🚀 Ready to control program flow?**

[⬅️ Previous: Variables & Data Types](04_Variables_Data_Types.md) | [Next: Control Flow ➡️](06_Control_Flow.md)