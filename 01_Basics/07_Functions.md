# 🔧 Lesson 7: Functions & Modular Programming
## Building Reusable Code Components

---

## 🎯 Learning Objectives

- Understand function declaration, definition, and calls
- Master parameter passing techniques
- Learn recursion and recursive functions
- Understand storage classes and scope rules
- Implement modular programming principles

---

## 📖 Functions Kya Hain?

**Functions** basically code ke self-contained blocks hain jo specific tasks perform karte hain. Ye help karte hain:
- **Modularity**: Complex programs ko chhote parts mein break karna
- **Reusability**: Same code ko multiple times use karna
- **Maintainability**: Debug aur modify karna easy
- **Abstraction**: Implementation details ko hide karna

### **Function ke Components**
1. **Function Declaration** (Prototype)
2. **Function Definition** (Implementation)
3. **Function Call** (Usage)

### **Function ki Types**
- **Library Functions**: Pre-built functions (printf, scanf, etc.)
- **User-defined Functions**: Programmer dwara banaye gaye functions
- **Recursive Functions**: Khud ko call karne wale functions
- **Inline Functions**: Compiler ko suggest karte hain direct code insert karne ke liye

---

## 🔧 Function Declaration and Definition

### **Function Declaration (Prototype)**
```c
// Syntax: return_type function_name(parameter_list);

// Examples
int add(int a, int b);                    // Two parameters
void print_message();                     // No parameters
float calculate_area(float radius);       // One parameter
char* get_name(int id);                   // Returns pointer
```

### **Function Definition**
```c
// Complete function with body
return_type function_name(parameter_list) {
    // Function body
    // Local variables
    // Statements
    return value;  // Optional
}

// Example
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
```

### **Complete Example**
```c
#include <stdio.h>

// Function declarations (prototypes)
int add(int, int);
void display_result(int);
int get_number();

int main() {
    int num1 = get_number();
    int num2 = get_number();

    int result = add(num1, num2);
    display_result(result);

    return 0;
}

// Function definitions
int add(int a, int b) {
    return a + b;
}

void display_result(int result) {
    printf("Result: %d\n", result);
}

int get_number() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    return num;
}
```

---

## 📝 Parameter Passing

### **Pass by Value**
```c
#include <stdio.h>

void modify_value(int x) {
    x = x * 2;  // Changes local copy only
    printf("Inside function: %d\n", x);
}

int main() {
    int num = 5;
    printf("Before function: %d\n", num);

    modify_value(num);

    printf("After function: %d\n", num);  // Original unchanged
    return 0;
}
```

### **Pass by Reference (Using Pointers)**
```c
#include <stdio.h>

void modify_value(int *ptr) {
    *ptr = *ptr * 2;  // Changes original value
    printf("Inside function: %d\n", *ptr);
}

int main() {
    int num = 5;
    printf("Before function: %d\n", num);

    modify_value(&num);  // Pass address

    printf("After function: %d\n", num);  // Original changed
    return 0;
}
```

### **Array Parameters**
```c
#include <stdio.h>

// Array as parameter (decays to pointer)
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Modifying array elements
void double_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Changes original array
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};

    print_array(numbers, 5);
    double_array(numbers, 5);
    print_array(numbers, 5);

    return 0;
}
```

---

## 🔄 Recursion

**Recursion** is when a function calls itself to solve a problem.

### **Basic Recursion: Factorial**
```c
#include <stdio.h>

// Recursive factorial
int factorial(int n) {
    if (n <= 1) {
        return 1;  // Base case
    }
    return n * factorial(n - 1);  // Recursive case
}

int main() {
    int num = 5;
    printf("Factorial of %d is %d\n", num, factorial(num));
    return 0;
}
```

### **Fibonacci Series**
```c
#include <stdio.h>

// Recursive Fibonacci
int fibonacci(int n) {
    if (n <= 1) {
        return n;  // Base case
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int terms = 10;
    printf("Fibonacci series: ");
    for (int i = 0; i < terms; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    return 0;
}
```

### **Tower of Hanoi**
```c
#include <stdio.h>

// Tower of Hanoi recursive solution
void tower_of_hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from_rod, to_rod);
        return;
    }

    tower_of_hanoi(n - 1, from_rod, aux_rod, to_rod);
    printf("Move disk %d from %c to %c\n", n, from_rod, to_rod);
    tower_of_hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n = 3;  // Number of disks
    tower_of_hanoi(n, 'A', 'C', 'B');  // A, B, C are rods
    return 0;
}
```

### **Advanced Recursion Examples**

#### **Binary Search (Recursive)**
```c
#include <stdio.h>

// Recursive binary search
int binary_search_recursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;  // Element not found
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;  // Element found
    } else if (arr[mid] > target) {
        return binary_search_recursive(arr, left, mid - 1, target);
    } else {
        return binary_search_recursive(arr, mid + 1, right, target);
    }
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;

    int result = binary_search_recursive(arr, 0, size - 1, target);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
```

#### **String Reversal (Recursive)**
```c
#include <stdio.h>
#include <string.h>

// Recursive string reversal
void reverse_string(char str[], int start, int end) {
    if (start >= end) {
        return;  // Base case
    }

    // Swap characters
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    // Recursive call
    reverse_string(str, start + 1, end - 1);
}

int main() {
    char str[] = "Hello, World!";
    printf("Original: %s\n", str);

    reverse_string(str, 0, strlen(str) - 1);
    printf("Reversed: %s\n", str);

    return 0;
}
```

#### **Directory Traversal (Simulated)**
```c
#include <stdio.h>

// Simulated directory structure
typedef struct Node {
    char name[50];
    struct Node* children[10];
    int child_count;
} Directory;

// Recursive directory size calculation
int calculate_directory_size(Directory* dir) {
    int total_size = 100;  // Base size for directory

    for (int i = 0; i < dir->child_count; i++) {
        if (dir->children[i] != NULL) {
            total_size += calculate_directory_size(dir->children[i]);
        }
    }

    return total_size;
}

// Recursive directory listing
void list_directory(Directory* dir, int depth) {
    // Print indentation
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("%s/\n", dir->name);

    // List children
    for (int i = 0; i < dir->child_count; i++) {
        if (dir->children[i] != NULL) {
            list_directory(dir->children[i], depth + 1);
        }
    }
}
```

#### **Permutations Generation**
```c
#include <stdio.h>
#include <string.h>

// Function to swap two characters
void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Recursive function to generate permutations
void generate_permutations(char str[], int start, int end) {
    if (start == end) {
        printf("%s\n", str);
        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&str[start], &str[i]);
        generate_permutations(str, start + 1, end);
        swap(&str[start], &str[i]);  // Backtrack
    }
}

int main() {
    char str[] = "ABC";
    int n = strlen(str);

    printf("Permutations of %s:\n", str);
    generate_permutations(str, 0, n - 1);

    return 0;
}
```

#### **Maze Solving (Backtracking)**
```c
#define MAZE_SIZE 5

int maze[MAZE_SIZE][MAZE_SIZE] = {
    {1, 0, 1, 1, 1},
    {1, 1, 1, 0, 1},
    {0, 0, 0, 1, 1},
    {1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1}
};

int solution[MAZE_SIZE][MAZE_SIZE] = {0};

// Check if position is valid
int is_valid(int x, int y) {
    return (x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE &&
            maze[x][y] == 1 && solution[x][y] == 0);
}

// Recursive maze solver
int solve_maze(int x, int y) {
    // Base case: reached destination
    if (x == MAZE_SIZE - 1 && y == MAZE_SIZE - 1) {
        solution[x][y] = 1;
        return 1;
    }

    // Check if current position is valid
    if (is_valid(x, y)) {
        solution[x][y] = 1;

        // Try moving right
        if (solve_maze(x, y + 1)) return 1;

        // Try moving down
        if (solve_maze(x + 1, y)) return 1;

        // Try moving left
        if (solve_maze(x, y - 1)) return 1;

        // Try moving up
        if (solve_maze(x - 1, y)) return 1;

        // Backtrack
        solution[x][y] = 0;
        return 0;
    }

    return 0;
}

int main() {
    if (solve_maze(0, 0)) {
        printf("Solution found!\n");
        for (int i = 0; i < MAZE_SIZE; i++) {
            for (int j = 0; j < MAZE_SIZE; j++) {
                printf("%d ", solution[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No solution exists\n");
    }

    return 0;
}
```

### **Tail Recursion Optimization**
```c
#include <stdio.h>

// Non-tail recursive factorial
int factorial_non_tail(int n) {
    if (n <= 1) return 1;
    return n * factorial_non_tail(n - 1);  // Multiplication after recursion
}

// Tail recursive factorial (optimized)
int factorial_tail(int n, int accumulator) {
    if (n <= 1) return accumulator;
    return factorial_tail(n - 1, n * accumulator);  // No operation after recursion
}

// Wrapper function
int factorial(int n) {
    return factorial_tail(n, 1);
}

int main() {
    printf("Factorial: %d\n", factorial(5));
    return 0;
}
```

---

## 💾 Storage Classes

Storage classes determine the lifetime and scope of variables.

### **1. Automatic Variables (`auto`)**
```c
#include <stdio.h>

void function() {
    auto int local_var = 10;  // Explicit auto (default)
    int another_var = 20;     // Implicit auto

    printf("Local variables: %d, %d\n", local_var, another_var);
    // Variables destroyed when function ends
}

int main() {
    function();
    // local_var and another_var no longer exist
    return 0;
}
```

### **2. Static Variables (`static`)**
```c
#include <stdio.h>

void counter() {
    static int count = 0;  // Initialized only once
    count++;
    printf("Count: %d\n", count);
}

int main() {
    counter();  // Count: 1
    counter();  // Count: 2
    counter();  // Count: 3

    return 0;
}
```

### **3. External Variables (`extern`)**
```c
// File: main.c
#include <stdio.h>

extern int global_var;  // Declaration

int main() {
    printf("Global variable: %d\n", global_var);
    return 0;
}

// File: data.c
int global_var = 42;  // Definition
```

### **4. Register Variables (`register`)**
```c
#include <stdio.h>

int main() {
    register int fast_counter = 0;  // Suggest compiler to use register

    for (register int i = 0; i < 1000000; i++) {
        fast_counter += i;
    }

    printf("Sum: %d\n", fast_counter);
    return 0;
}
```

---

## 🎯 Scope Rules

### **Block Scope**
```c
#include <stdio.h>

int main() {
    int outer = 10;

    {
        int inner = 20;  // Block scope
        printf("Inner: %d, Outer: %d\n", inner, outer);
    }

    // inner is not accessible here
    // printf("%d", inner);  // Error!

    return 0;
}
```

### **Function Scope**
```c
#include <stdio.h>

void function1() {
    int func_var = 100;
    printf("Function 1: %d\n", func_var);
}

void function2() {
    // func_var is not accessible here
    // printf("%d", func_var);  // Error!
}

int main() {
    function1();
    function2();
    return 0;
}
```

### **File Scope (Global Variables)**
```c
#include <stdio.h>

int global_var = 50;  // File scope

void function() {
    printf("Global in function: %d\n", global_var);
    global_var = 100;  // Can modify
}

int main() {
    printf("Global in main: %d\n", global_var);
    function();
    printf("Global after function: %d\n", global_var);

    return 0;
}
```

### **Scope Resolution**
```c
#include <stdio.h>

int var = 10;  // Global variable

int main() {
    int var = 20;  // Local variable (hides global)

    printf("Local var: %d\n", var);

    // Access global variable using scope resolution
    {
        extern int var;  // Refers to global var
        printf("Global var: %d\n", var);
    }

    return 0;
}
```

---

## 🔧 Inline Functions aur Advanced Features

### **Inline Functions (C99)**
**Inline functions** compiler ko suggest karte hain ki function code ko directly call site pe insert kar de for better performance.

```c
#include <stdio.h>

// Inline function definition
inline int square(int x) {
    return x * x;
}

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int num = 5;
    printf("Square of %d: %d\n", num, square(num));
    printf("Max of 10, 20: %d\n", max(10, 20));

    return 0;
}
```

### **When to Use Inline Functions**
- Small functions (few lines)
- Frequently called functions
- Performance-critical code
- Jab function call overhead significant ho

### **Function Pointers aur Callbacks**
```c
#include <stdio.h>

// Function pointer typedef
typedef int (*Operation)(int, int);

// Basic operations
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

// Calculator using function pointers
int calculate(Operation op, int a, int b) {
    return op(a, b);
}

// Callback example
void process_array(int arr[], int size, int (*callback)(int)) {
    for (int i = 0; i < size; i++) {
        arr[i] = callback(arr[i]);
    }
}

int square_callback(int x) {
    return x * x;
}

int main() {
    // Function pointer usage
    Operation ops[] = {add, subtract, multiply};
    int result = calculate(ops[0], 10, 5);  // Addition
    printf("Result: %d\n", result);

    // Callback usage
    int arr[] = {1, 2, 3, 4, 5};
    process_array(arr, 5, square_callback);

    printf("Squared array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

### **Variable Arguments (Varargs)**
```c
#include <stdio.h>
#include <stdarg.h>

// Function with variable arguments
int sum(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }

    va_end(args);
    return total;
}

// Printf-style function
void print_info(const char* format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);  // Use vprintf for variable args

    va_end(args);
}

int main() {
    printf("Sum of 1,2,3,4,5: %d\n", sum(5, 1, 2, 3, 4, 5));
    print_info("Name: %s, Age: %d, Score: %.2f\n", "John", 25, 85.5);

    return 0;
}
```

### **Function Design Patterns**

#### **1. Factory Pattern**
```c
#include <stdio.h>
#include <stdlib.h>

// Shape interface
typedef struct {
    void (*draw)(void* self);
    void (*area)(void* self);
} Shape;

// Circle implementation
typedef struct {
    Shape base;
    double radius;
} Circle;

void circle_draw(void* self) {
    Circle* circle = (Circle*)self;
    printf("Drawing circle with radius %.2f\n", circle->radius);
}

void circle_area(void* self) {
    Circle* circle = (Circle*)self;
    printf("Circle area: %.2f\n", 3.14159 * circle->radius * circle->radius);
}

// Shape factory
Shape* create_circle(double radius) {
    Circle* circle = (Circle*)malloc(sizeof(Circle));
    circle->radius = radius;
    circle->base.draw = circle_draw;
    circle->base.area = circle_area;
    return (Shape*)circle;
}

int main() {
    Shape* shape = create_circle(5.0);
    shape->draw(shape);
    shape->area(shape);

    free(shape);
    return 0;
}
```

#### **2. Strategy Pattern**
```c
#include <stdio.h>

// Sorting strategy
typedef int (*CompareFunc)(const void*, const void*);

// Bubble sort with strategy
void bubble_sort(void* arr, size_t n, size_t size, CompareFunc compare) {
    char* array = (char*)arr;

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            void* elem1 = array + j * size;
            void* elem2 = array + (j + 1) * size;

            if (compare(elem1, elem2) > 0) {
                // Swap elements
                for (size_t k = 0; k < size; k++) {
                    char temp = array[j * size + k];
                    array[j * size + k] = array[(j + 1) * size + k];
                    array[(j + 1) * size + k] = temp;
                }
            }
        }
    }
}

// Comparison functions
int compare_int_asc(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int compare_int_desc(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Sort ascending
    bubble_sort(arr, n, sizeof(int), compare_int_asc);
    printf("Ascending: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Sort descending
    bubble_sort(arr, n, sizeof(int), compare_int_desc);
    printf("Descending: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
```

#### **3. Command Pattern**
```c
#include <stdio.h>
#include <stdlib.h>

// Command interface
typedef struct {
    void (*execute)(void* self);
    void (*undo)(void* self);
} Command;

// Calculator commands
typedef struct {
    Command base;
    int* target;
    int value;
    int previous_value;
} AddCommand;

void add_execute(void* self) {
    AddCommand* cmd = (AddCommand*)self;
    cmd->previous_value = *(cmd->target);
    *(cmd->target) += cmd->value;
}

void add_undo(void* self) {
    AddCommand* cmd = (AddCommand*)self;
    *(cmd->target) = cmd->previous_value;
}

Command* create_add_command(int* target, int value) {
    AddCommand* cmd = (AddCommand*)malloc(sizeof(AddCommand));
    cmd->target = target;
    cmd->value = value;
    cmd->base.execute = add_execute;
    cmd->base.undo = add_undo;
    return (Command*)cmd;
}

int main() {
    int calculator = 0;
    Command* cmd = create_add_command(&calculator, 10);

    printf("Initial value: %d\n", calculator);
    cmd->execute(cmd);
    printf("After add 10: %d\n", calculator);
    cmd->undo(cmd);
    printf("After undo: %d\n", calculator);

    free(cmd);
    return 0;
}
```

### **Function Attributes (GCC Extensions)**
```c
#include <stdio.h>

// Function attributes
__attribute__((noreturn)) void fatal_error(const char* message) {
    fprintf(stderr, "Fatal error: %s\n", message);
    exit(1);
}

__attribute__((deprecated("Use new_function instead")))
void old_function() {
    printf("This function is deprecated\n");
}

__attribute__((constructor))
void init_function() {
    printf("Program initializing...\n");
}

__attribute__((destructor))
void cleanup_function() {
    printf("Program cleaning up...\n");
}

int main() {
    printf("Main function\n");
    // old_function();  // Compiler warning
    return 0;
}
```

---

## 📚 Function Categories

### **1. Library Functions**
```c
#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    // Math functions
    printf("Square root of 16: %.2f\n", sqrt(16.0));
    printf("Power 2^3: %.2f\n", pow(2, 3));

    // String functions
    char str1[] = "Hello";
    char str2[] = "World";
    printf("String length: %zu\n", strlen(str1));
    printf("String compare: %d\n", strcmp(str1, str2));

    return 0;
}
```

### **2. User-Defined Functions**
```c
#include <stdio.h>

// Function to check if number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }

    return 1;
}

// Function to calculate factorial
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int num = 17;
    printf("%d is %s\n", num, is_prime(num) ? "prime" : "not prime");

    int fact_num = 5;
    printf("Factorial of %d: %lld\n", fact_num, factorial(fact_num));

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Function Naming**
```c
// ✅ Good naming
int calculate_total_amount();
void display_user_profile();
int validate_email_address();

// ❌ Bad naming
int calc();
void disp();
int check();
```

### **2. Function Length**
```c
// ✅ Keep functions focused and small
int is_valid_age(int age) {
    return age >= 0 && age <= 150;
}

void process_user_data(User *user) {
    if (!is_valid_age(user->age)) {
        printf("Invalid age\n");
        return;
    }
    // Process data
}

// ❌ Avoid long functions
void process_everything() {
    // 100+ lines of code
    // Hard to understand and maintain
}
```

### **3. Parameter Validation**
```c
// ✅ Validate parameters
int divide(int dividend, int divisor) {
    if (divisor == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return dividend / divisor;
}

// ✅ Use assertions for debugging
#include <assert.h>
int factorial(int n) {
    assert(n >= 0 && "Factorial of negative number not defined");
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

### **4. Return Value Consistency**
```c
// ✅ Consistent return values
int find_max(int a, int b) {
    return (a > b) ? a : b;
}

// ✅ Use enums for status codes
typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_INPUT = -1,
    ERROR_MEMORY_ALLOCATION = -2
} Status;

Status process_data(int *data) {
    if (data == NULL) return ERROR_INVALID_INPUT;
    // Process data
    return SUCCESS;
}
```

---

## 🐛 Common Mistakes

### **1. Missing Function Prototype**
```c
// Error: function called before definition
int main() {
    int result = add(5, 3);  // Error if add() not declared
    return 0;
}

int add(int a, int b) {
    return a + b;
}

// Fix: Add prototype
int add(int, int);

int main() {
    int result = add(5, 3);
    return 0;
}
```

### **2. Wrong Parameter Types**
```c
// Error: type mismatch
void print_number(int num);

int main() {
    print_number(3.14);  // Passing float to int parameter
    return 0;
}

// Fix: Correct parameter type
void print_number(float num) {
    printf("%.2f\n", num);
}
```

### **3. Missing Return Statement**
```c
// Error: non-void function without return
int add(int a, int b) {
    int sum = a + b;
    // Missing return statement
}

// Fix
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
```

### **4. Stack Overflow in Recursion**
```c
// Error: infinite recursion
int infinite_loop(int n) {
    return infinite_loop(n);  // Never reaches base case
}

// Fix: proper base case
int factorial(int n) {
    if (n <= 1) return 1;  // Base case
    return n * factorial(n - 1);
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic Functions**
Create functions for:
- Calculate area of circle
- Check if number is even/odd
- Convert temperature (Celsius to Fahrenheit)
- Find maximum of three numbers

### **Exercise 2: Recursion Practice**
Implement recursive functions for:
- Calculate power (x^n)
- Reverse a string
- Check if string is palindrome
- Solve Tower of Hanoi for n disks

### **Exercise 3: Function Parameters**
Create functions that demonstrate:
- Pass by value vs pass by reference
- Array parameters
- String parameters
- Structure parameters

### **Exercise 4: Modular Calculator**
Build a calculator with separate functions for:
- Addition, subtraction, multiplication, division
- Input validation
- Error handling
- Result display

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the correct way to declare a function prototype?
a) `int add(a, b)`
b) `int add(int a, int b)`
c) `int add(int, int)`
d) Both b and c

### **Question 2:**
What happens when a function is called with pass by value?
a) Original value is modified
b) A copy is created and modified
c) Function cannot modify the value
d) Both b and c

### **Question 3:**
Which storage class keeps the variable value between function calls?
a) auto
b) static
c) extern
d) register

### **Question 4:**
What is tail recursion?
a) Recursion at the end of function
b) Recursion at the beginning
c) Multiple recursive calls
d) No base case

### **Question 5:**
When should you use inline functions?
a) For large functions
b) For small, frequently called functions
c) For recursive functions
d) For all functions

---

## 🔗 Additional Resources

### **Function Design**
- [Function Prototypes](https://en.cppreference.com/w/c/language/function_declaration)
- [Storage Classes](https://en.cppreference.com/w/c/language/storage_duration)
- [Recursion](https://en.wikipedia.org/wiki/Recursion_(computer_science))

### **Further Reading**
- [C Functions](https://www.programiz.com/c-programming/c-functions)
- [Inline Functions](https://en.cppreference.com/w/c/language/inline)
- [Scope Rules](https://en.cppreference.com/w/c/language/scope)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ Function declaration, definition, and calls
- ✅ Parameter passing techniques
- ✅ Recursion and recursive algorithms
- ✅ Storage classes and scope rules
- ✅ Inline functions and optimization

**Next Lesson Preview:**
- Arrays and their operations
- Multi-dimensional arrays
- Array manipulation techniques
- Common array algorithms

---

**🚀 Ready to work with arrays?**

[⬅️ Previous: Control Flow](06_Control_Flow.md) | [Next: Arrays ➡️](08_Arrays.md)