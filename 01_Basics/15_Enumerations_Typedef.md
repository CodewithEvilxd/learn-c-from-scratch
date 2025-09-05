# 🔢 Lesson 15: Enumerations & Typedef in C
## Creating Custom Types and Named Constants

---

## 🎯 Learning Objectives

- Understand enumeration types and their usage
- Master typedef for type aliases
- Learn enum with switch-case combinations
- Create complex type definitions
- Understand best practices for custom types

---

## 📖 Enumerations Kya Hain?

**Enumerations** (enums) user-defined data types hain jo named integer constants se consist karte hain. Ye integral values ko names assign karne ka way provide karte hain, making code more readable and maintainable.

### **Enum Characteristics**
- **Named Constants**: Numbers ko meaningful names do
- **Type Safety**: Invalid values prevent karo
- **Readability**: Self-documenting code
- **Default Values**: Automatic numbering starting from 0

### **Advanced Enum Concepts**
- **Bit flags aur masking**
- **Enum classes (C++ style)**
- **Type-safe enums**
- **Enum reflection aur iteration**
- **Enum with custom underlying types**

---

## 🔧 Enumeration Basics

### **1. Basic Enum Declaration**
```c
#include <stdio.h>

// Method 1: Basic enum
enum Days {
    MONDAY,     // 0
    TUESDAY,    // 1
    WEDNESDAY,  // 2
    THURSDAY,   // 3
    FRIDAY,     // 4
    SATURDAY,   // 5
    SUNDAY      // 6
};

// Method 2: Enum with typedef
typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

int main() {
    // Using enum
    enum Days today = WEDNESDAY;
    Color favorite = BLUE;

    printf("Today is day %d\n", today);
    printf("Favorite color code: %d\n", favorite);

    return 0;
}
```

### **2. Custom Enum Values**
```c
#include <stdio.h>

enum Status {
    SUCCESS = 0,
    ERROR = -1,
    PENDING = 1,
    FAILED = -2
};

enum Months {
    JAN = 1,    // Start from 1
    FEB,        // 2
    MAR,        // 3
    APR,        // 4
    MAY,        // 5
    JUN,        // 6
    JUL,        // 7
    AUG,        // 8
    SEP,        // 9
    OCT,        // 10
    NOV,        // 11
    DEC         // 12
};

enum FilePermissions {
    READ = 4,
    WRITE = 2,
    EXECUTE = 1,
    RW = READ | WRITE,          // 6
    RX = READ | EXECUTE,        // 5
    WX = WRITE | EXECUTE,       // 3
    RWX = READ | WRITE | EXECUTE // 7
};

int main() {
    enum Status result = SUCCESS;
    enum Months birth_month = AUG;
    enum FilePermissions perm = RWX;

    printf("Result: %d\n", result);
    printf("Birth month: %d\n", birth_month);
    printf("Permissions: %d\n", perm);

    return 0;
}
```

---

## 🔄 Enum with Switch-Case

### **1. Basic Switch with Enum**
```c
#include <stdio.h>

typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULO
} Operation;

int calculate(Operation op, int a, int b) {
    switch (op) {
        case ADD:
            return a + b;
        case SUBTRACT:
            return a - b;
        case MULTIPLY:
            return a * b;
        case DIVIDE:
            return b != 0 ? a / b : 0;
        case MODULO:
            return b != 0 ? a % b : 0;
        default:
            printf("Invalid operation\n");
            return 0;
    }
}

int main() {
    Operation op = MULTIPLY;
    int result = calculate(op, 10, 5);
    printf("Result: %d\n", result);

    return 0;
}
```

### **2. State Machine with Enum**
```c
#include <stdio.h>

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED,
    STATE_ERROR
} ProgramState;

void handle_state(ProgramState state) {
    switch (state) {
        case STATE_IDLE:
            printf("Program is idle\n");
            break;
        case STATE_RUNNING:
            printf("Program is running\n");
            break;
        case STATE_PAUSED:
            printf("Program is paused\n");
            break;
        case STATE_STOPPED:
            printf("Program is stopped\n");
            break;
        case STATE_ERROR:
            printf("Program encountered an error\n");
            break;
        default:
            printf("Unknown state\n");
    }
}

int main() {
    ProgramState current_state = STATE_RUNNING;
    handle_state(current_state);

    // Change state
    current_state = STATE_PAUSED;
    handle_state(current_state);

    return 0;
}
```

### **3. Menu System with Enum**
```c
#include <stdio.h>

typedef enum {
    MENU_MAIN,
    MENU_FILE,
    MENU_EDIT,
    MENU_VIEW,
    MENU_HELP
} MenuOption;

typedef enum {
    FILE_NEW,
    FILE_OPEN,
    FILE_SAVE,
    FILE_EXIT
} FileOption;

void handle_menu(MenuOption menu, int submenu) {
    switch (menu) {
        case MENU_FILE:
            switch ((FileOption)submenu) {
                case FILE_NEW:
                    printf("Creating new file\n");
                    break;
                case FILE_OPEN:
                    printf("Opening file\n");
                    break;
                case FILE_SAVE:
                    printf("Saving file\n");
                    break;
                case FILE_EXIT:
                    printf("Exiting program\n");
                    break;
            }
            break;

        case MENU_EDIT:
            printf("Edit menu option: %d\n", submenu);
            break;

        default:
            printf("Menu option: %d, Submenu: %d\n", menu, submenu);
    }
}

int main() {
    handle_menu(MENU_FILE, FILE_NEW);
    handle_menu(MENU_EDIT, 1);

    return 0;
}
```

---

## 🔗 Typedef Basics

### **1. Basic Typedef Usage**
```c
#include <stdio.h>

// Basic typedef
typedef int Integer;
typedef float Real;
typedef char Character;

// Using typedef
Integer count = 10;
Real pi = 3.14159;
Character letter = 'A';

int main() {
    printf("Count: %d\n", count);
    printf("Pi: %.5f\n", pi);
    printf("Letter: %c\n", letter);

    return 0;
}
```

### **2. Typedef with Arrays**
```c
#include <stdio.h>

// Array typedef
typedef int IntArray[10];
typedef char String[50];

int main() {
    IntArray numbers = {1, 2, 3, 4, 5};
    String name = "John Doe";

    printf("First number: %d\n", numbers[0]);
    printf("Name: %s\n", name);

    return 0;
}
```

### **3. Typedef with Pointers**
```c
#include <stdio.h>

// Pointer typedef
typedef int* IntPtr;
typedef char* StringPtr;
typedef void* GenericPtr;

int main() {
    IntPtr ptr1;
    StringPtr ptr2;
    GenericPtr ptr3;

    int num = 42;
    char str[] = "Hello";

    ptr1 = &num;
    ptr2 = str;
    ptr3 = &num;

    printf("Value via IntPtr: %d\n", *ptr1);
    printf("String via StringPtr: %s\n", ptr2);
    printf("Value via GenericPtr: %d\n", *(int*)ptr3);

    return 0;
}
```

---

## 🏗️ Typedef with Structures

### **1. Basic Structure Typedef**
```c
#include <stdio.h>

// Method 1: typedef with struct
typedef struct {
    char name[50];
    int roll_number;
    float marks;
} Student;

// Method 2: typedef separate from struct
struct Employee {
    char name[50];
    int id;
    float salary;
};

typedef struct Employee Employee;

int main() {
    Student s1 = {"Alice", 101, 85.5};
    Employee e1 = {"Bob", 201, 50000.0};

    printf("Student: %s, Roll: %d, Marks: %.1f\n",
           s1.name, s1.roll_number, s1.marks);

    printf("Employee: %s, ID: %d, Salary: %.2f\n",
           e1.name, e1.id, e1.salary);

    return 0;
}
```

### **2. Self-Referential Structures**
```c
#include <stdio.h>
#include <stdlib.h>

// Self-referential structure for linked list
typedef struct Node {
    int data;
    struct Node* next;  // Can't use typedef alias here
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    print_list(head);

    // Free memory
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
```

### **3. Complex Structure Typedef**
```c
#include <stdio.h>

// Complex typedefs
typedef struct {
    int x, y;
} Point;

typedef struct {
    Point top_left;
    Point bottom_right;
} Rectangle;

typedef struct {
    char title[100];
    char author[50];
    int year;
    float price;
} Book;

typedef struct {
    Book* books;
    int count;
    int capacity;
} Library;

int main() {
    Point p1 = {10, 20};
    Rectangle rect = {{0, 0}, {100, 50}};
    Book book = {"C Programming", "Dennis Ritchie", 1978, 29.99};

    printf("Point: (%d, %d)\n", p1.x, p1.y);
    printf("Rectangle: (%d,%d) to (%d,%d)\n",
           rect.top_left.x, rect.top_left.y,
           rect.bottom_right.x, rect.bottom_right.y);
    printf("Book: %s by %s\n", book.title, book.author);

    return 0;
}
```

---

## 🔄 Typedef with Enums

### **1. Enum Typedef**
```c
#include <stdio.h>

// Method 1: typedef with enum
typedef enum {
    LOW = 1,
    MEDIUM = 5,
    HIGH = 10
} Priority;

// Method 2: typedef separate
enum Status {
    OK,
    WARNING,
    ERROR
};

typedef enum Status Status;

int main() {
    Priority task_priority = HIGH;
    Status system_status = OK;

    printf("Task priority: %d\n", task_priority);
    printf("System status: %d\n", system_status);

    return 0;
}
```

### **2. Enum in Switch-Case with Typedef**
```c
#include <stdio.h>

typedef enum {
    CMD_CREATE,
    CMD_READ,
    CMD_UPDATE,
    CMD_DELETE,
    CMD_EXIT
} Command;

void execute_command(Command cmd) {
    switch (cmd) {
        case CMD_CREATE:
            printf("Creating new item\n");
            break;
        case CMD_READ:
            printf("Reading item\n");
            break;
        case CMD_UPDATE:
            printf("Updating item\n");
            break;
        case CMD_DELETE:
            printf("Deleting item\n");
            break;
        case CMD_EXIT:
            printf("Exiting program\n");
            break;
        default:
            printf("Unknown command\n");
    }
}

int main() {
    Command user_cmd = CMD_CREATE;
    execute_command(user_cmd);

    user_cmd = CMD_EXIT;
    execute_command(user_cmd);

    return 0;
}
```

---

## 🔧 Advanced Typedef Techniques

### **1. Function Pointer Typedef**
```c
#include <stdio.h>

// Function pointer typedef
typedef int (*MathOperation)(int, int);

// Functions
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

int main() {
    MathOperation operation = add;
    printf("Add: %d\n", operation(5, 3));

    operation = multiply;
    printf("Multiply: %d\n", operation(5, 3));

    return 0;
}
```

### **2. Complex Type Definitions**
```c
#include <stdio.h>

// Array of function pointers
typedef int (*OperationArray[4])(int, int);

// Structure with function pointers
typedef struct {
    char name[20];
    int (*calculate)(int, int);
} Calculator;

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    Calculator calc = {"Adder", add};
    printf("%s: %d\n", calc.name, calc.calculate(10, 5));

    return 0;
}
```

### **3. Platform-Specific Types**
```c
#include <stdio.h>

// Platform-independent types
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

// Usage
int main() {
    int8_t small_num = -10;
    uint16_t medium_num = 50000;
    int32_t large_num = 1000000;

    printf("8-bit: %d\n", small_num);
    printf("16-bit: %u\n", medium_num);
    printf("32-bit: %d\n", large_num);

    return 0;
}
```

### **4. Bit Flags with Enums**
```c
#include <stdio.h>

// Bit flags using enum
typedef enum {
    FLAG_NONE = 0,
    FLAG_READ = 1 << 0,      // 0001
    FLAG_WRITE = 1 << 1,     // 0010
    FLAG_EXECUTE = 1 << 2,   // 0100
    FLAG_DELETE = 1 << 3,    // 1000

    // Combined flags
    FLAG_READ_WRITE = FLAG_READ | FLAG_WRITE,
    FLAG_ALL = FLAG_READ | FLAG_WRITE | FLAG_EXECUTE | FLAG_DELETE
} FilePermissions;

typedef enum {
    STYLE_BOLD = 1 << 0,
    STYLE_ITALIC = 1 << 1,
    STYLE_UNDERLINE = 1 << 2,
    STYLE_STRIKETHROUGH = 1 << 3
} TextStyle;

// Functions to manipulate flags
int has_flag(int flags, int flag) {
    return (flags & flag) != 0;
}

int add_flag(int flags, int flag) {
    return flags | flag;
}

int remove_flag(int flags, int flag) {
    return flags & ~flag;
}

int toggle_flag(int flags, int flag) {
    return flags ^ flag;
}

void print_permissions(int perms) {
    printf("Permissions: ");
    if (has_flag(perms, FLAG_READ)) printf("R");
    if (has_flag(perms, FLAG_WRITE)) printf("W");
    if (has_flag(perms, FLAG_EXECUTE)) printf("X");
    if (has_flag(perms, FLAG_DELETE)) printf("D");
    printf(" (%d)\n", perms);
}

int main() {
    int file_perms = FLAG_READ | FLAG_WRITE;
    int text_style = STYLE_BOLD | STYLE_ITALIC;

    printf("File permissions:\n");
    print_permissions(file_perms);

    // Add execute permission
    file_perms = add_flag(file_perms, FLAG_EXECUTE);
    print_permissions(file_perms);

    // Remove write permission
    file_perms = remove_flag(file_perms, FLAG_WRITE);
    print_permissions(file_perms);

    // Toggle delete permission
    file_perms = toggle_flag(file_perms, FLAG_DELETE);
    print_permissions(file_perms);

    printf("\nText style: %d\n", text_style);
    printf("Has bold: %s\n", has_flag(text_style, STYLE_BOLD) ? "Yes" : "No");
    printf("Has underline: %s\n", has_flag(text_style, STYLE_UNDERLINE) ? "Yes" : "No");

    return 0;
}
```

### **5. Generic Programming with Typedef**
```c
#include <stdio.h>
#include <stdlib.h>

// Generic stack using typedef
#define DEFINE_STACK_TYPE(type) \
    typedef struct { \
        type *data; \
        size_t size; \
        size_t capacity; \
    } CONCAT(type, Stack); \
    \
    CONCAT(type, Stack)* CONCAT(create_, CONCAT(type, _stack))(size_t capacity) { \
        CONCAT(type, Stack) *stack = (CONCAT(type, Stack)*)malloc(sizeof(CONCAT(type, Stack))); \
        if (stack == NULL) return NULL; \
        stack->data = (type*)malloc(capacity * sizeof(type)); \
        if (stack->data == NULL) { free(stack); return NULL; } \
        stack->size = 0; \
        stack->capacity = capacity; \
        return stack; \
    } \
    \
    void CONCAT(push_, CONCAT(type, _stack))(CONCAT(type, Stack) *stack, type value) { \
        if (stack->size >= stack->capacity) { \
            stack->capacity *= 2; \
            stack->data = (type*)realloc(stack->data, stack->capacity * sizeof(type)); \
        } \
        stack->data[stack->size++] = value; \
    } \
    \
    type CONCAT(pop_, CONCAT(type, _stack))(CONCAT(type, Stack) *stack) { \
        if (stack->size == 0) { \
            fprintf(stderr, "Stack underflow\n"); \
            exit(1); \
        } \
        return stack->data[--stack->size]; \
    } \
    \
    void CONCAT(free_, CONCAT(type, _stack))(CONCAT(type, Stack) *stack) { \
        free(stack->data); \
        free(stack); \
    }

// Generate stack types
DEFINE_STACK_TYPE(int)
DEFINE_STACK_TYPE(float)
DEFINE_STACK_TYPE(char)

int main() {
    // Use generated types
    intStack *int_stack = create_int_stack(10);
    floatStack *float_stack = create_float_stack(10);
    charStack *char_stack = create_char_stack(10);

    // Push elements
    push_int_stack(int_stack, 42);
    push_int_stack(int_stack, 100);

    push_float_stack(float_stack, 3.14f);
    push_float_stack(float_stack, 2.71f);

    push_char_stack(char_stack, 'A');
    push_char_stack(char_stack, 'B');

    // Pop elements
    printf("Int popped: %d\n", pop_int_stack(int_stack));
    printf("Float popped: %.2f\n", pop_float_stack(float_stack));
    printf("Char popped: %c\n", pop_char_stack(char_stack));

    // Cleanup
    free_int_stack(int_stack);
    free_float_stack(float_stack);
    free_char_stack(char_stack);

    return 0;
}
```

### **6. Advanced Enum Techniques**
```c
#include <stdio.h>

// Enum with custom underlying type (C++ style simulation)
typedef enum {
    COLOR_RED = 0xFF0000,
    COLOR_GREEN = 0x00FF00,
    COLOR_BLUE = 0x0000FF,
    COLOR_WHITE = 0xFFFFFF,
    COLOR_BLACK = 0x000000
} ColorRGB;

// Enum for state machine
typedef enum {
    STATE_INIT,
    STATE_READY,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED,
    STATE_ERROR,
    STATE_MAX  // Used for array sizing
} SystemState;

// State transition table
typedef struct {
    SystemState current;
    SystemState next;
    const char *description;
} StateTransition;

StateTransition transitions[] = {
    {STATE_INIT, STATE_READY, "Initializing to ready"},
    {STATE_READY, STATE_RUNNING, "Ready to running"},
    {STATE_RUNNING, STATE_PAUSED, "Running to paused"},
    {STATE_PAUSED, STATE_RUNNING, "Paused to running"},
    {STATE_RUNNING, STATE_STOPPED, "Running to stopped"},
    {STATE_STOPPED, STATE_READY, "Stopped to ready"}
};

const char* state_names[] = {
    "INIT",
    "READY",
    "RUNNING",
    "PAUSED",
    "STOPPED",
    "ERROR"
};

// Enum iteration helper
#define FOREACH_STATE(state_var) \
    for (SystemState state_var = STATE_INIT; state_var < STATE_MAX; state_var++)

// State machine functions
SystemState get_next_state(SystemState current, const char *action) {
    for (size_t i = 0; i < sizeof(transitions) / sizeof(transitions[0]); i++) {
        if (transitions[i].current == current) {
            // Simple action matching (in real code, use proper command parsing)
            if ((strcmp(action, "start") == 0 && transitions[i].next == STATE_RUNNING) ||
                (strcmp(action, "pause") == 0 && transitions[i].next == STATE_PAUSED) ||
                (strcmp(action, "resume") == 0 && transitions[i].next == STATE_RUNNING) ||
                (strcmp(action, "stop") == 0 && transitions[i].next == STATE_STOPPED)) {
                return transitions[i].next;
            }
        }
    }
    return STATE_ERROR;
}

int main() {
    SystemState current_state = STATE_INIT;
    printf("Initial state: %s\n", state_names[current_state]);

    // Simulate state transitions
    const char *actions[] = {"start", "pause", "resume", "stop"};
    for (int i = 0; i < 4; i++) {
        SystemState next_state = get_next_state(current_state, actions[i]);
        if (next_state != STATE_ERROR) {
            printf("Action '%s': %s -> %s\n",
                   actions[i], state_names[current_state], state_names[next_state]);
            current_state = next_state;
        } else {
            printf("Invalid action '%s' from state %s\n", actions[i], state_names[current_state]);
        }
    }

    // Demonstrate color enum
    ColorRGB color = COLOR_RED;
    printf("\nSelected color RGB: 0x%06X\n", color);

    // Iterate through all states
    printf("\nAll possible states:\n");
    FOREACH_STATE(state) {
        printf("  %s (%d)\n", state_names[state], state);
    }

    return 0;
}
```

### **7. Complex Type Definitions**
```c
#include <stdio.h>
#include <stdlib.h>

// Function pointer typedefs
typedef void (*Callback)(void);
typedef int (*Comparator)(const void*, const void*);

// Generic container typedef
typedef struct {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
    Comparator compare;
} GenericVector;

// Complex nested typedefs
typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
    size_t element_size;
} GenericList;

// Callback system
typedef struct {
    Callback on_init;
    Callback on_update;
    Callback on_cleanup;
} EventCallbacks;

// Usage examples
void init_callback(void) {
    printf("Initialization callback called\n");
}

void update_callback(void) {
    printf("Update callback called\n");
}

void cleanup_callback(void) {
    printf("Cleanup callback called\n");
}

int int_comparator(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    // Event callbacks
    EventCallbacks events = {
        .on_init = init_callback,
        .on_update = update_callback,
        .on_cleanup = cleanup_callback
    };

    events.on_init();
    events.on_update();
    events.on_cleanup();

    // Generic vector simulation
    GenericVector vec = {
        .data = NULL,
        .element_size = sizeof(int),
        .size = 0,
        .capacity = 0,
        .compare = int_comparator
    };

    printf("\nGeneric vector element size: %zu bytes\n", vec.element_size);

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Use Meaningful Names**
```c
// ✅ Good
typedef enum {
    TRAFFIC_LIGHT_RED,
    TRAFFIC_LIGHT_YELLOW,
    TRAFFIC_LIGHT_GREEN
} TrafficLight;

// ❌ Bad
typedef enum {
    R,
    Y,
    G
} TL;
```

### **2. Consistent Naming Conventions**
```c
// ✅ Good
typedef struct {
    char first_name[50];
    char last_name[50];
} Person;

typedef Person* PersonPtr;
typedef Person PersonArray[100];

// ❌ Bad
typedef struct {
    char fn[50];
    char ln[50];
} P;

typedef P* PP;
typedef P PA[100];
```

### **3. Use Typedef for Complex Types**
```c
// ✅ Good - simplifies complex declarations
typedef void (*CallbackFunction)(int, char*);

// ❌ Bad - hard to read
void (*callback)(int, char*) = NULL;
```

### **4. Avoid Overusing Typedef**
```c
// ✅ Good - use for structures and enums
typedef struct { int x, y; } Point;

// ❌ Bad - unnecessary for simple types
typedef int Integer;  // Unnecessary
```

---

## 🐛 Common Mistakes

### **1. Enum Value Conflicts**
```c
// Wrong - duplicate values
enum Colors {
    RED = 1,
    GREEN = 1,  // Same as RED
    BLUE = 1    // Same as RED and GREEN
};

// Correct - unique values
enum Colors {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};
```

### **2. Typedef Forward Declaration Issues**
```c
// Wrong - typedef can't be forward declared like this
typedef struct Node Node;  // Incomplete

struct Node {
    int data;
    Node* next;  // Error: Node not complete yet
};

// Correct
typedef struct Node {
    int data;
    struct Node* next;  // Use struct Node
} Node;
```

### **3. Enum in Switch Missing Cases**
```c
typedef enum {
    OPTION_A,
    OPTION_B,
    OPTION_C
} Option;

void process_option(Option opt) {
    switch (opt) {
        case OPTION_A:
            printf("A\n");
            break;
        case OPTION_B:
            printf("B\n");
            break;
        // Missing OPTION_C - may cause warnings
    }
}
```

### **4. Typedef Name Conflicts**
```c
// Wrong - conflicts with standard library
typedef int size_t;  // Conflicts with stdlib.h

// Correct - use unique names
typedef int my_size_t;
```

---

## 📝 Practice Exercises

### **Exercise 1: Enum Creation**
- Create enums for days of the week
- Build an enum for HTTP status codes
- Implement an enum for game states

### **Exercise 2: Typedef with Structures**
- Create typedefs for common data structures
- Build a linked list with typedef
- Implement a stack using typedef

### **Exercise 3: Enum with Switch-Case**
- Create a calculator using enum and switch
- Build a state machine for a traffic light
- Implement a menu system with enums

### **Exercise 4: Complex Types**
- Create function pointer typedefs
- Build an array of function pointers
- Implement platform-independent types

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the default value for the first enum constant?
a) 1
b) -1
c) 0
d) Random

### **Question 2:**
Which keyword is used to create type aliases?
a) `enum`
b) `struct`
c) `typedef`
d) `define`

### **Question 3:**
Can enum values be negative?
a) No, only positive
b) Yes, any integer value
c) Only zero and positive
d) Only -1, 0, 1

### **Question 4:**
What is the correct way to define an enum with typedef?
a) `typedef enum {A, B} MyEnum;`
b) `enum typedef {A, B} MyEnum;`
c) `typedef {A, B} enum MyEnum;`
d) `enum MyEnum typedef {A, B};`

### **Question 5:**
Which of these is a valid typedef?
a) `typedef int[10] Array;`
b) `typedef int Array[10];`
c) `typedef [10]int Array;`
d) `typedef Array int[10];`

---

## 🔗 Additional Resources

### **Enumerations**
- [C Enumerations](https://en.cppreference.com/w/c/language/enum)
- [Enum Best Practices](https://www.geeksforgeeks.org/enumeration-enum-c/)

### **Typedef**
- [C Typedef](https://en.cppreference.com/w/c/language/typedef)
- [Type Aliases](https://www.programiz.com/c-programming/c-typedef)

### **Further Reading**
- [Custom Types in C](https://www.tutorialspoint.com/cprogramming/c_typedef.htm)
- [Enum vs #define](https://stackoverflow.com/questions/106947/enum-vs-define)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ Enumeration types and usage
- ✅ Typedef for type aliases
- ✅ Enum with switch-case combinations
- ✅ Complex type definitions
- ✅ Best practices for custom types

**Next Lesson Preview:**
- Bit manipulation and bitwise operations
- Advanced bitwise techniques
- Practical bit operation applications
- Bit fields in structures

---

**🚀 Ready to manipulate bits?**

[⬅️ Previous: Preprocessor](14_Preprocessor.md) | [Next: Bitwise Programming ➡️](16_Bitwise_Programming.md)