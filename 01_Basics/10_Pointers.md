# 🎯 Lesson 10: Pointers in C
## Mastering Memory Addresses and Pointer Operations

---

## 🎯 Learning Objectives

- Understand pointer fundamentals and syntax
- Master pointer arithmetic and operations
- Learn different types of pointers
- Understand pointers to arrays, strings, and structures
- Master function pointers and callbacks
- Avoid common pointer pitfalls

---

## 📖 Pointers Kya Hain?

**Pointers** basically variables hain jo other variables ke memory addresses store karte hain. Ye C programming ke sabse powerful aur important features mein se ek hain.

### **Pointers Kyun Important Hain**
- **Direct memory access**: Memory level pe data manipulate karna
- **Dynamic memory allocation**: Flexible data structures banana
- **Function arguments**: Large data efficiently pass karna
- **System programming**: Hardware ke saath interface karna
- **Data structures**: Linked lists, trees, etc. implement karna

### **Pointer ke Advanced Concepts**
- **Memory layout understanding**
- **Pointer to functions (function tables)**
- **Complex pointer expressions**
- **Memory mapping aur virtual memory**
- **Pointer security aur best practices**

---

## 🔧 Pointer Basics

### **Pointer Declaration and Initialization**
```c
#include <stdio.h>

int main() {
    // Variable declaration
    int num = 42;
    int *ptr;        // Pointer declaration
    ptr = &num;      // Initialization with address

    // Combined declaration and initialization
    int value = 100;
    int *ptr2 = &value;

    // Multiple pointers
    int a = 10, b = 20;
    int *p1 = &a, *p2 = &b;

    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", &num);
    printf("Value of ptr: %p\n", ptr);
    printf("Value pointed by ptr: %d\n", *ptr);

    return 0;
}
```

### **Pointer Dereferencing**
```c
#include <stdio.h>

int main() {
    int num = 25;
    int *ptr = &num;

    printf("Direct access: %d\n", num);
    printf("Pointer access: %d\n", *ptr);

    // Modifying value through pointer
    *ptr = 50;
    printf("After modification: %d\n", num);

    return 0;
}
```

---

## 🔢 Pointer Arithmetic

### **Basic Pointer Arithmetic**
```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Points to first element

    printf("First element: %d\n", *ptr);
    printf("Address of first: %p\n", ptr);

    // Increment pointer
    ptr++;
    printf("Second element: %d\n", *ptr);
    printf("Address of second: %p\n", ptr);

    // Decrement pointer
    ptr--;
    printf("Back to first: %d\n", *ptr);

    return 0;
}
```

### **Pointer Arithmetic with Different Data Types**
```c
#include <stdio.h>

int main() {
    int int_arr[] = {1, 2, 3, 4, 5};
    char char_arr[] = {'A', 'B', 'C', 'D', 'E'};
    double double_arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};

    int *int_ptr = int_arr;
    char *char_ptr = char_arr;
    double *double_ptr = double_arr;

    printf("int pointer increment: %p -> ", int_ptr);
    int_ptr++;
    printf("%p (+%lu bytes)\n", int_ptr, sizeof(int));

    printf("char pointer increment: %p -> ", char_ptr);
    char_ptr++;
    printf("%p (+%lu bytes)\n", char_ptr, sizeof(char));

    printf("double pointer increment: %p -> ", double_ptr);
    double_ptr++;
    printf("%p (+%lu bytes)\n", double_ptr, sizeof(double));

    return 0;
}
```

### **Pointer Subtraction**
```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr1 = &arr[2];  // Points to 30
    int *ptr2 = &arr[4];  // Points to 50

    printf("ptr1 points to: %d\n", *ptr1);
    printf("ptr2 points to: %d\n", *ptr2);

    // Pointer subtraction gives number of elements between them
    int difference = ptr2 - ptr1;
    printf("Difference: %d elements\n", difference);

    return 0;
}
```

---

## 🎭 Types of Pointers

### **1. Null Pointer**
```c
#include <stdio.h>

int main() {
    int *null_ptr = NULL;

    // Always check for NULL before dereferencing
    if (null_ptr != NULL) {
        printf("Value: %d\n", *null_ptr);
    } else {
        printf("Pointer is NULL\n");
    }

    // Common use: Initialize pointers
    int *ptr = NULL;
    // Later assign valid address
    int num = 42;
    ptr = &num;

    return 0;
}
```

### **2. Void Pointer (Generic Pointer)**
```c
#include <stdio.h>

int main() {
    int num = 42;
    float pi = 3.14159;
    char ch = 'A';

    void *void_ptr;

    // Can point to any data type
    void_ptr = &num;
    printf("Integer: %d\n", *(int*)void_ptr);

    void_ptr = &pi;
    printf("Float: %.2f\n", *(float*)void_ptr);

    void_ptr = &ch;
    printf("Character: %c\n", *(char*)void_ptr);

    return 0;
}
```

### **3. Wild Pointer**
```c
#include <stdio.h>

int main() {
    int *wild_ptr;  // Uninitialized - points to random memory

    // Dangerous: May cause segmentation fault
    // printf("%d\n", *wild_ptr);  // DON'T DO THIS!

    // Always initialize pointers
    int *safe_ptr = NULL;  // Or assign valid address

    return 0;
}
```

### **4. Dangling Pointer**
```c
#include <stdio.h>

int* create_dangling() {
    int local_var = 42;
    return &local_var;  // Returns address of local variable
}

int main() {
    int *dangling = create_dangling();

    // local_var no longer exists, dangling points to invalid memory
    // printf("%d\n", *dangling);  // Dangerous!

    return 0;
}
```

---

## 📊 Pointers to Arrays

### **Array Name as Pointer**
```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // arr decays to pointer to first element

    printf("Array name: %p\n", arr);
    printf("Pointer: %p\n", ptr);
    printf("First element: %d\n", *ptr);

    // Accessing array elements using pointer
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d, *(ptr + %d) = %d\n",
               i, arr[i], i, *(ptr + i));
    }

    return 0;
}
```

### **Pointer to Array vs Array of Pointers**
```c
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // Pointer to array
    int (*ptr_to_arr)[5] = &arr;

    // Array of pointers
    int *arr_of_ptr[5];
    for (int i = 0; i < 5; i++) {
        arr_of_ptr[i] = &arr[i];
    }

    // Accessing elements
    printf("Using ptr_to_arr: %d\n", (*ptr_to_arr)[2]);
    printf("Using arr_of_ptr: %d\n", *arr_of_ptr[2]);

    return 0;
}
```

---

## 🔤 Pointers to Strings

### **String Pointers**
```c
#include <stdio.h>

int main() {
    // Method 1: Character array
    char str1[] = "Hello";
    char *ptr1 = str1;

    // Method 2: String literal
    char *ptr2 = "World";

    printf("String 1: %s\n", ptr1);
    printf("String 2: %s\n", ptr2);

    // Modifying character array
    ptr1[0] = 'h';
    printf("Modified: %s\n", ptr1);

    // Can't modify string literal
    // ptr2[0] = 'w';  // Runtime error!

    return 0;
}
```

### **String Operations with Pointers**
```c
#include <stdio.h>

int main() {
    char str[] = "Hello, World!";
    char *ptr = str;

    // Traverse string using pointer
    printf("String: ");
    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    printf("\n");

    // Reset pointer
    ptr = str;

    // Count characters
    int count = 0;
    while (*ptr != '\0') {
        count++;
        ptr++;
    }
    printf("Length: %d\n", count);

    return 0;
}
```

---

## 🏗️ Pointers to Structures

### **Basic Structure Pointer**
```c
#include <stdio.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    struct Student s1 = {"John", 101, 85.5};
    struct Student *ptr = &s1;

    // Accessing structure members
    printf("Name: %s\n", ptr->name);
    printf("Roll: %d\n", ptr->roll_number);
    printf("Marks: %.2f\n", ptr->marks);

    // Alternative syntax (less common)
    printf("Name: %s\n", (*ptr).name);

    return 0;
}
```

### **Dynamic Structure Allocation**
```c
#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    // Allocate memory for structure
    struct Student *ptr = (struct Student*)malloc(sizeof(struct Student));

    if (ptr != NULL) {
        // Initialize structure
        strcpy(ptr->name, "Alice");
        ptr->roll_number = 102;
        ptr->marks = 92.3;

        // Display
        printf("Name: %s\n", ptr->name);
        printf("Roll: %d\n", ptr->roll_number);
        printf("Marks: %.2f\n", ptr->marks);

        // Free memory
        free(ptr);
    }

    return 0;
}
```

---

## 🔧 Function Pointers

### **Basic Function Pointer**
```c
#include <stdio.h>

// Function to be pointed to
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    // Declare function pointer
    int (*operation)(int, int);

    // Point to add function
    operation = add;
    printf("Addition: %d\n", operation(10, 5));

    // Point to subtract function
    operation = subtract;
    printf("Subtraction: %d\n", operation(10, 5));

    return 0;
}
```

### **Function Pointer as Callback**
```c
#include <stdio.h>

// Callback function types
typedef int (*CompareFunc)(int, int);
typedef void (*PrintFunc)(int);

// Comparison functions
int ascending(int a, int b) {
    return a - b;
}

int descending(int a, int b) {
    return b - a;
}

// Print functions
void print_decimal(int num) {
    printf("%d ", num);
}

void print_hex(int num) {
    printf("0x%X ", num);
}

// Sort function with callback
void bubble_sort(int arr[], int size, CompareFunc compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(arr[j], arr[j + 1]) > 0) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    // Sort ascending
    bubble_sort(arr, size, ascending);
    printf("Ascending: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    // Sort descending
    bubble_sort(arr, size, descending);
    printf("Descending: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
```

### **Array of Function Pointers**
```c
#include <stdio.h>

// Calculator operations
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    // Array of function pointers
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};

    char *op_names[] = {"Add", "Subtract", "Multiply", "Divide"};

    int a = 20, b = 4;

    for (int i = 0; i < 4; i++) {
        printf("%s(%d, %d) = %d\n",
               op_names[i], a, b, operations[i](a, b));
    }

    return 0;
}
```

### **Advanced Function Pointers - Jump Tables**

#### **Function Table Implementation**
```c
#include <stdio.h>
#include <stdlib.h>

// Function table entry
typedef struct {
    char *name;
    int (*function)(int, int);
} FunctionEntry;

// Calculator functions
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }
int modulus(int a, int b) { return b != 0 ? a % b : 0; }

// Function table
FunctionEntry function_table[] = {
    {"add", add},
    {"subtract", subtract},
    {"multiply", multiply},
    {"divide", divide},
    {"modulus", modulus}
};

#define TABLE_SIZE (sizeof(function_table) / sizeof(FunctionEntry))

// Execute function by name
int execute_function(const char *name, int a, int b) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strcmp(function_table[i].name, name) == 0) {
            return function_table[i].function(a, b);
        }
    }
    printf("Function '%s' not found\n", name);
    return 0;
}

int main() {
    char operation[20];
    int a, b;

    printf("Available operations: ");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%s ", function_table[i].name);
    }
    printf("\n");

    printf("Enter operation: ");
    scanf("%s", operation);
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    int result = execute_function(operation, a, b);
    printf("Result: %d\n", result);

    return 0;
}
```

#### **State Machine with Function Pointers**
```c
#include <stdio.h>

// State machine states
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
} State;

// Event types
typedef enum {
    EVENT_START,
    EVENT_PAUSE,
    EVENT_RESUME,
    EVENT_STOP
} Event;

// State function signature
typedef void (*StateFunction)(Event);

// Forward declarations
void idle_state(Event event);
void running_state(Event event);
void paused_state(Event event);
void stopped_state(Event event);

// State table
StateFunction state_table[] = {
    idle_state,     // STATE_IDLE
    running_state,  // STATE_RUNNING
    paused_state,   // STATE_PAUSED
    stopped_state   // STATE_STOPPED
};

State current_state = STATE_IDLE;

// State functions
void idle_state(Event event) {
    switch (event) {
        case EVENT_START:
            printf("Starting...\n");
            current_state = STATE_RUNNING;
            break;
        default:
            printf("Invalid event for IDLE state\n");
    }
}

void running_state(Event event) {
    switch (event) {
        case EVENT_PAUSE:
            printf("Pausing...\n");
            current_state = STATE_PAUSED;
            break;
        case EVENT_STOP:
            printf("Stopping...\n");
            current_state = STATE_STOPPED;
            break;
        default:
            printf("Invalid event for RUNNING state\n");
    }
}

void paused_state(Event event) {
    switch (event) {
        case EVENT_RESUME:
            printf("Resuming...\n");
            current_state = STATE_RUNNING;
            break;
        case EVENT_STOP:
            printf("Stopping...\n");
            current_state = STATE_STOPPED;
            break;
        default:
            printf("Invalid event for PAUSED state\n");
    }
}

void stopped_state(Event event) {
    switch (event) {
        case EVENT_START:
            printf("Starting...\n");
            current_state = STATE_RUNNING;
            break;
        default:
            printf("Invalid event for STOPPED state\n");
    }
}

// Process event
void process_event(Event event) {
    state_table[current_state](event);
}

int main() {
    // Simulate state transitions
    process_event(EVENT_START);    // IDLE -> RUNNING
    process_event(EVENT_PAUSE);    // RUNNING -> PAUSED
    process_event(EVENT_RESUME);   // PAUSED -> RUNNING
    process_event(EVENT_STOP);     // RUNNING -> STOPPED

    return 0;
}
```

#### **Virtual Function Table (Simple OOP in C)**
```c
#include <stdio.h>
#include <stdlib.h>

// Base class equivalent
typedef struct {
    void (*speak)(void* self);
    void (*move)(void* self);
} AnimalVTable;

// Animal structure
typedef struct {
    AnimalVTable* vtable;
    char* name;
} Animal;

// Dog implementation
typedef struct {
    Animal base;
    char* breed;
} Dog;

void dog_speak(void* self) {
    Dog* dog = (Dog*)self;
    printf("%s the %s says: Woof!\n", dog->base.name, dog->breed);
}

void dog_move(void* self) {
    Dog* dog = (Dog*)self;
    printf("%s the %s runs around.\n", dog->base.name, dog->breed);
}

// Cat implementation
typedef struct {
    Animal base;
    int lives_remaining;
} Cat;

void cat_speak(void* self) {
    Cat* cat = (Cat*)self;
    printf("%s says: Meow! (%d lives remaining)\n",
           cat->base.name, cat->lives_remaining);
}

void cat_move(void* self) {
    Cat* cat = (Cat*)self;
    printf("%s gracefully walks.\n", cat->base.name);
}

// VTables
AnimalVTable dog_vtable = {dog_speak, dog_move};
AnimalVTable cat_vtable = {cat_speak, cat_move};

// Create dog
Dog* create_dog(char* name, char* breed) {
    Dog* dog = (Dog*)malloc(sizeof(Dog));
    dog->base.name = name;
    dog->base.vtable = &dog_vtable;
    dog->breed = breed;
    return dog;
}

// Create cat
Cat* create_cat(char* name, int lives) {
    Cat* cat = (Cat*)malloc(sizeof(Cat));
    cat->base.name = name;
    cat->base.vtable = &cat_vtable;
    cat->lives_remaining = lives;
    return cat;
}

int main() {
    // Create animals
    Dog* dog = create_dog("Buddy", "Golden Retriever");
    Cat* cat = create_cat("Whiskers", 9);

    // Polymorphic behavior
    Animal* animals[] = {(Animal*)dog, (Animal*)cat};

    for (int i = 0; i < 2; i++) {
        animals[i]->vtable->speak(animals[i]);
        animals[i]->vtable->move(animals[i]);
        printf("\n");
    }

    free(dog);
    free(cat);

    return 0;
}
```

#### **Callback System with Function Pointers**
```c
#include <stdio.h>
#include <stdlib.h>

// Event types
typedef enum {
    EVENT_CLICK,
    EVENT_HOVER,
    EVENT_KEYPRESS
} EventType;

// Callback function signature
typedef void (*EventCallback)(void* data);

// Event handler
typedef struct {
    EventType type;
    EventCallback callback;
    void* user_data;
} EventHandler;

// Button widget
typedef struct {
    char* label;
    EventHandler* handlers[10];
    int handler_count;
} Button;

// Register event handler
void add_event_handler(Button* button, EventType type, EventCallback callback, void* data) {
    if (button->handler_count < 10) {
        EventHandler* handler = (EventHandler*)malloc(sizeof(EventHandler));
        handler->type = type;
        handler->callback = callback;
        handler->user_data = data;
        button->handlers[button->handler_count++] = handler;
    }
}

// Trigger event
void trigger_event(Button* button, EventType type) {
    for (int i = 0; i < button->handler_count; i++) {
        if (button->handlers[i]->type == type) {
            button->handlers[i]->callback(button->handlers[i]->user_data);
        }
    }
}

// Callback functions
void on_click(void* data) {
    char* message = (char*)data;
    printf("Button clicked: %s\n", message);
}

void on_hover(void* data) {
    char* message = (char*)data;
    printf("Button hovered: %s\n", message);
}

int main() {
    Button button = {"Submit", {NULL}, 0};

    // Register callbacks
    add_event_handler(&button, EVENT_CLICK, on_click, "Submit button pressed");
    add_event_handler(&button, EVENT_HOVER, on_hover, "Mouse over submit button");

    // Simulate events
    trigger_event(&button, EVENT_CLICK);
    trigger_event(&button, EVENT_HOVER);

    // Cleanup
    for (int i = 0; i < button.handler_count; i++) {
        free(button.handlers[i]);
    }

    return 0;
}
```

---

## 📚 Double and Triple Pointers

### **Double Pointers**
```c
#include <stdio.h>

int main() {
    int num = 42;
    int *ptr = &num;      // Single pointer
    int **ptr2 = &ptr;    // Double pointer

    printf("Value: %d\n", num);
    printf("Single pointer: %d\n", *ptr);
    printf("Double pointer: %d\n", **ptr2);

    // Modifying through double pointer
    **ptr2 = 100;
    printf("Modified value: %d\n", num);

    return 0;
}
```

### **Common Use Cases for Double Pointers**
```c
#include <stdio.h>
#include <stdlib.h>

// Function that allocates memory and returns pointer
void allocate_memory(int **ptr, int size) {
    *ptr = (int*)malloc(size * sizeof(int));
    if (*ptr != NULL) {
        for (int i = 0; i < size; i++) {
            (*ptr)[i] = i + 1;
        }
    }
}

// Function to modify pointer itself
void reset_pointer(int **ptr) {
    free(*ptr);
    *ptr = NULL;
}

int main() {
    int *arr = NULL;
    int size = 5;

    // Allocate memory
    allocate_memory(&arr, size);

    if (arr != NULL) {
        printf("Allocated array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Reset pointer
        reset_pointer(&arr);
        printf("Pointer reset: %s\n", arr == NULL ? "Success" : "Failed");
    }

    return 0;
}
```

### **Triple Pointers**
```c
#include <stdio.h>

int main() {
    int num = 42;
    int *ptr1 = &num;
    int **ptr2 = &ptr1;
    int ***ptr3 = &ptr2;

    printf("Value using triple pointer: %d\n", ***ptr3);

    // Modifying through triple pointer
    ***ptr3 = 100;
    printf("Modified value: %d\n", num);

    return 0;
}
```

---

## 🤔 Pointer vs Array Confusion

### **Key Differences**
```c
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;

    // Both work for accessing elements
    printf("arr[2]: %d, *(ptr + 2): %d\n", arr[2], *(ptr + 2));

    // But arrays and pointers are different
    printf("Size of arr: %zu bytes\n", sizeof(arr));      // 20 bytes (5 * 4)
    printf("Size of ptr: %zu bytes\n", sizeof(ptr));      // 8 bytes (pointer size)

    // Array name cannot be reassigned
    // arr = &some_other_array;  // Error!

    // Pointer can be reassigned
    int arr2[5] = {6, 7, 8, 9, 10};
    ptr = arr2;  // OK

    return 0;
}
```

### **When Array Decays to Pointer**
```c
#include <stdio.h>

// Function parameter: array decays to pointer
void func1(int arr[]) {  // Same as int *arr
    printf("Size inside function: %zu\n", sizeof(arr));  // Pointer size
}

void func2(int *ptr) {   // Explicit pointer
    printf("Size with pointer: %zu\n", sizeof(ptr));    // Pointer size
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    printf("Size in main: %zu\n", sizeof(arr));  // Array size

    func1(arr);
    func2(arr);

    return 0;
}
```

---

## ⚠️ Common Pointer Mistakes

### **1. Uninitialized Pointers**
```c
int *ptr;      // Points to random memory
*ptr = 10;     // Dangerous!

// Fix
int *ptr = NULL;
int value = 10;
ptr = &value;
```

### **2. Memory Leaks**
```c
int *ptr = (int*)malloc(sizeof(int));
// Forgot to free
// free(ptr);  // Memory leak!

// Fix
free(ptr);
ptr = NULL;
```

### **3. Dangling Pointers**
```c
int *func() {
    int local = 42;
    return &local;  // Returns address of local variable
}

// Usage
int *ptr = func();
// *ptr is now invalid!
```

### **4. Double Free**
```c
int *ptr = (int*)malloc(sizeof(int));
free(ptr);
// free(ptr);  // Double free - undefined behavior
```

### **5. Invalid Pointer Arithmetic**
```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;

ptr += 10;    // Points outside array bounds
*ptr = 100;   // Undefined behavior
```

---

## 🎯 Best Practices

### **1. Always Initialize Pointers**
```c
// ✅ Good
int *ptr = NULL;
int value = 42;
ptr = &value;

// ❌ Bad
int *ptr;  // Uninitialized
```

### **2. Check for NULL**
```c
// ✅ Safe dereferencing
if (ptr != NULL) {
    *ptr = 10;
}

// ❌ Unsafe
*ptr = 10;  // May crash
```

### **3. Use const for Read-only Pointers**
```c
// ✅ Prevent modification
const int *ptr = &value;  // Cannot modify *ptr
int *const ptr2 = &value; // Cannot reassign ptr2
```

### **4. Free Dynamic Memory**
```c
// ✅ Proper cleanup
int *ptr = (int*)malloc(sizeof(int));
if (ptr != NULL) {
    *ptr = 42;
    // Use ptr
    free(ptr);
    ptr = NULL;
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Pointer Basics**
- Create pointers to different data types
- Demonstrate pointer dereferencing
- Show address-of operator usage

### **Exercise 2: Pointer Arithmetic**
- Implement array traversal using pointers
- Create pointer-based string operations
- Build a simple pointer-based calculator

### **Exercise 3: Function Pointers**
- Create a calculator using function pointers
- Implement callback functions for sorting
- Build a simple event system

### **Exercise 4: Complex Pointers**
- Work with double and triple pointers
- Create pointer to array of function pointers
- Implement a simple virtual function table

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What does the `&` operator do?
a) Dereferences a pointer
b) Gets address of a variable
c) Performs bitwise AND
d) Logical AND operation

### **Question 2:**
Which is the correct way to declare a pointer?
a) `int ptr;`
b) `int *ptr;`
c) `int &ptr;`
d) `pointer int ptr;`

### **Question 3:**
What happens when you increment a pointer?
a) Value increases by 1
b) Points to next memory location
c) Address increases by 1 byte
d) Address increases by data type size

### **Question 4:**
Which pointer type can point to any data type?
a) int*
b) char*
c) void*
d) float*

### **Question 5:**
What is a dangling pointer?
a) NULL pointer
b) Pointer to invalid memory
c) Wild pointer
d) Void pointer

---

## 🔗 Additional Resources

### **Pointer Concepts**
- [Pointers in C](https://en.cppreference.com/w/c/language/pointer)
- [Memory Management](https://en.wikipedia.org/wiki/Memory_management)
- [Function Pointers](https://en.cppreference.com/w/c/language/function_pointer)

### **Further Reading**
- [C Pointers](https://www.programiz.com/c-programming/c-pointers)
- [Pointer Arithmetic](https://www.geeksforgeeks.org/pointer-arithmetics-in-c-with-examples/)
- [Memory Layout](https://en.wikipedia.org/wiki/Memory_layout_of_C_program)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ Pointer declaration and initialization
- ✅ Pointer arithmetic and operations
- ✅ Different types of pointers
- ✅ Pointers to arrays, strings, and structures
- ✅ Function pointers and callbacks
- ✅ Double and triple pointers

**Next Lesson Preview:**
- Structures and unions
- Nested structures
- Pointers to structures
- Structure padding and alignment

---

**🚀 Ready to work with structures?**

[⬅️ Previous: Strings](09_Strings.md) | [Next: Structures & Unions ➡️](11_Structures_Unions.md)