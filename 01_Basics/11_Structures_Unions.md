# 🏗️ Lesson 11: Structures & Unions in C
## Building Complex Data Types

---

## 🎯 Learning Objectives

- Understand structure declaration and usage
- Master union concepts and memory layout
- Learn nested structures and arrays of structures
- Work with pointers to structures
- Understand structure padding and alignment

---

## 📖 Structures Kya Hain?

**Structures** user-defined data types hain jo different types ke related data items ko ek single name ke under group karne dete hain. Ye C mein complex data models banana ke liye fundamental hain.

### **Structures Kyun Use Karein?**
- **Logical grouping**: Related data ek saath
- **Custom data types**: Application-specific types banana
- **Data abstraction**: Implementation details hide karna
- **Modularity**: Complex programs organize karna

### **Advanced Structure Concepts**
- **Self-referential structures**: Linked lists ke liye
- **Bit fields**: Memory optimization ke liye
- **Flexible array members**: Dynamic sizing
- **Structure packing**: Memory layout control

---

## 🔧 Structure Declaration and Definition

### **Basic Structure Declaration**
```c
#include <stdio.h>

// Structure declaration
struct Student {
    char name[50];
    int roll_number;
    float marks;
    char grade;
};

// Structure definition and usage
int main() {
    // Declare structure variable
    struct Student s1;

    // Initialize structure members
    strcpy(s1.name, "John Doe");
    s1.roll_number = 101;
    s1.marks = 85.5;
    s1.grade = 'A';

    // Display structure members
    printf("Name: %s\n", s1.name);
    printf("Roll Number: %d\n", s1.roll_number);
    printf("Marks: %.2f\n", s1.marks);
    printf("Grade: %c\n", s1.grade);

    return 0;
}
```

### **Structure Initialization**
```c
#include <stdio.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
    char grade;
};

int main() {
    // Method 1: Initialize during declaration
    struct Student s1 = {"Alice", 102, 92.3, 'A'};

    // Method 2: Designated initialization (C99)
    struct Student s2 = {
        .name = "Bob",
        .roll_number = 103,
        .marks = 78.9,
        .grade = 'B'
    };

    // Method 3: Partial initialization
    struct Student s3 = {"Charlie", 104};  // marks and grade = 0

    // Display
    printf("Student 1: %s, Roll: %d, Marks: %.1f\n",
           s1.name, s1.roll_number, s1.marks);

    return 0;
}
```

---

## 📊 Arrays of Structures

### **Basic Array of Structures**
```c
#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    // Array of structures
    struct Student students[3];

    // Initialize array elements
    strcpy(students[0].name, "Alice");
    students[0].roll_number = 101;
    students[0].marks = 85.5;

    strcpy(students[1].name, "Bob");
    students[1].roll_number = 102;
    students[1].marks = 92.3;

    strcpy(students[2].name, "Charlie");
    students[2].roll_number = 103;
    students[2].marks = 78.9;

    // Display all students
    for (int i = 0; i < 3; i++) {
        printf("Student %d:\n", i + 1);
        printf("  Name: %s\n", students[i].name);
        printf("  Roll: %d\n", students[i].roll_number);
        printf("  Marks: %.1f\n", students[i].marks);
        printf("\n");
    }

    return 0;
}
```

### **Initializing Array of Structures**
```c
#include <stdio.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    // Initialize array of structures
    struct Student students[3] = {
        {"Alice", 101, 85.5},
        {"Bob", 102, 92.3},
        {"Charlie", 103, 78.9}
    };

    // Calculate average marks
    float total = 0;
    for (int i = 0; i < 3; i++) {
        total += students[i].marks;
    }
    printf("Average marks: %.2f\n", total / 3);

    return 0;
}
```

---

## 🏗️ Nested Structures

### **Basic Nested Structure**
```c
#include <stdio.h>
#include <string.h>

struct Address {
    char street[100];
    char city[50];
    char state[50];
    int pincode;
};

struct Employee {
    char name[50];
    int id;
    float salary;
    struct Address address;  // Nested structure
};

int main() {
    struct Employee emp;

    // Initialize employee data
    strcpy(emp.name, "John Doe");
    emp.id = 1001;
    emp.salary = 50000.0;

    // Initialize nested address
    strcpy(emp.address.street, "123 Main St");
    strcpy(emp.address.city, "Mumbai");
    strcpy(emp.address.state, "Maharashtra");
    emp.address.pincode = 400001;

    // Display information
    printf("Employee Details:\n");
    printf("Name: %s\n", emp.name);
    printf("ID: %d\n", emp.id);
    printf("Salary: %.2f\n", emp.salary);
    printf("Address: %s, %s, %s - %d\n",
           emp.address.street,
           emp.address.city,
           emp.address.state,
           emp.address.pincode);

    return 0;
}
```

### **Complex Nested Structures**
```c
#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Subject {
    char name[50];
    int marks;
};

struct Student {
    char name[50];
    int roll_number;
    struct Date birth_date;
    struct Subject subjects[3];
};

int main() {
    struct Student student;

    strcpy(student.name, "Alice");
    student.roll_number = 101;

    // Initialize birth date
    student.birth_date.day = 15;
    student.birth_date.month = 8;
    student.birth_date.year = 2000;

    // Initialize subjects
    strcpy(student.subjects[0].name, "Math");
    student.subjects[0].marks = 85;

    strcpy(student.subjects[1].name, "Physics");
    student.subjects[1].marks = 92;

    strcpy(student.subjects[2].name, "Chemistry");
    student.subjects[2].marks = 88;

    // Display
    printf("Student: %s (Roll: %d)\n", student.name, student.roll_number);
    printf("Birth Date: %d/%d/%d\n",
           student.birth_date.day,
           student.birth_date.month,
           student.birth_date.year);

    printf("Subjects:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %s: %d\n",
               student.subjects[i].name,
               student.subjects[i].marks);
    }

    return 0;
}
```

### **Self-Referential Structures (Linked List Nodes)**
```c
#include <stdio.h>
#include <stdlib.h>

// Self-referential structure for linked list
struct Node {
    int data;
    struct Node* next;  // Points to another Node
};

typedef struct Node Node;

// Create a new node
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Insert at beginning
void insert_beginning(Node** head, int data) {
    Node* new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Display linked list
void display_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Free linked list
void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    // Create linked list
    insert_beginning(&head, 10);
    insert_beginning(&head, 20);
    insert_beginning(&head, 30);

    printf("Linked List: ");
    display_list(head);

    // Cleanup
    free_list(head);

    return 0;
}
```

### **Bit Fields in Structures**
```c
#include <stdio.h>

// Structure with bit fields for memory optimization
struct StatusFlags {
    unsigned int is_active : 1;    // 1 bit
    unsigned int is_admin : 1;     // 1 bit
    unsigned int permission : 2;   // 2 bits (0-3)
    unsigned int priority : 4;     // 4 bits (0-15)
    unsigned int reserved : 8;     // 8 bits
};

struct NetworkPacket {
    unsigned int version : 4;      // IP version
    unsigned int header_len : 4;   // Header length
    unsigned int type_of_service : 8; // TOS
    unsigned int total_length : 16;   // Total length
};

int main() {
    struct StatusFlags flags = {0};

    // Set flags
    flags.is_active = 1;
    flags.is_admin = 0;
    flags.permission = 3;  // Full permissions
    flags.priority = 10;

    printf("Active: %d\n", flags.is_active);
    printf("Admin: %d\n", flags.is_admin);
    printf("Permission: %d\n", flags.permission);
    printf("Priority: %d\n", flags.priority);

    printf("Size of StatusFlags: %zu bytes\n", sizeof(flags));
    printf("Size without bit fields would be: %zu bytes\n",
           sizeof(unsigned int) * 4);

    // Network packet example
    struct NetworkPacket packet;
    packet.version = 4;        // IPv4
    packet.header_len = 5;     // 20 bytes
    packet.type_of_service = 0;
    packet.total_length = 1500;

    printf("\nNetwork Packet:\n");
    printf("Version: %d\n", packet.version);
    printf("Header Length: %d\n", packet.header_len);
    printf("Total Length: %d\n", packet.total_length);

    return 0;
}
```

### **Flexible Array Members (C99)**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure with flexible array member
struct StringBuffer {
    size_t length;
    char data[];  // Flexible array member
};

// Create string buffer with dynamic size
struct StringBuffer* create_buffer(size_t size) {
    // Allocate memory for structure + array
    struct StringBuffer* buffer =
        (struct StringBuffer*)malloc(sizeof(struct StringBuffer) + size);

    if (buffer == NULL) {
        return NULL;
    }

    buffer->length = size;
    memset(buffer->data, 0, size);

    return buffer;
}

// Structure with multiple flexible members (not allowed)
// struct BadExample {
//     int count;
//     int data[];     // Only one flexible member allowed
//     char names[];   // Error!
// };

int main() {
    size_t buffer_size = 100;
    struct StringBuffer* buffer = create_buffer(buffer_size);

    if (buffer != NULL) {
        strcpy(buffer->data, "Hello, Flexible Arrays!");
        printf("Buffer content: %s\n", buffer->data);
        printf("Buffer size: %zu\n", buffer->length);

        free(buffer);
    }

    return 0;
}
```

### **Structure Packing and Alignment Control**
```c
#include <stdio.h>

// Default alignment
struct NormalStruct {
    char c;      // 1 byte
    int i;       // 4 bytes
    short s;     // 2 bytes
};

// Packed structure (no padding)
#pragma pack(1)
struct PackedStruct {
    char c;      // 1 byte
    int i;       // 4 bytes
    short s;     // 2 bytes
};
#pragma pack()  // Reset to default

// Aligned structure
struct AlignedStruct {
    char c;      // 1 byte
    int i __attribute__((aligned(8)));  // Force 8-byte alignment
    short s;     // 2 bytes
};

int main() {
    printf("Normal struct size: %zu bytes\n", sizeof(struct NormalStruct));
    printf("Packed struct size: %zu bytes\n", sizeof(struct PackedStruct));
    printf("Aligned struct size: %zu bytes\n", sizeof(struct AlignedStruct));

    // Show memory layout
    struct NormalStruct normal = {'A', 42, 100};
    unsigned char* bytes = (unsigned char*)&normal;

    printf("\nMemory layout of normal struct:\n");
    for (size_t i = 0; i < sizeof(struct NormalStruct); i++) {
        printf("Byte %zu: 0x%02X", i, bytes[i]);
        if (i == 0) printf(" (char)");
        else if (i >= 1 && i <= 4) printf(" (int)");
        else if (i >= 5 && i <= 6) printf(" (short)");
        else printf(" (padding)");
        printf("\n");
    }

    return 0;
}
```

### **Advanced Union Usage**
```c
#include <stdio.h>
#include <string.h>

// Union for different data interpretations
union DataInterpreter {
    unsigned int as_int;
    float as_float;
    unsigned char as_bytes[4];
};

union NetworkMessage {
    struct {
        unsigned int type : 4;
        unsigned int length : 12;
        unsigned int flags : 16;
    } header;
    unsigned int raw_header;
};

int main() {
    // Data interpretation
    union DataInterpreter data;
    data.as_float = 3.14159f;

    printf("Float: %.6f\n", data.as_float);
    printf("As int: %u\n", data.as_int);
    printf("Bytes: ");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", data.as_bytes[i]);
    }
    printf("\n");

    // Network message
    union NetworkMessage msg;
    msg.header.type = 1;
    msg.header.length = 256;
    msg.header.flags = 0xABCD;

    printf("\nNetwork Message:\n");
    printf("Type: %u\n", msg.header.type);
    printf("Length: %u\n", msg.header.length);
    printf("Flags: 0x%04X\n", msg.header.flags);
    printf("Raw header: 0x%08X\n", msg.raw_header);

    return 0;
}
```

---

## 🎯 Pointers to Structures

### **Basic Structure Pointer**
```c
#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    struct Student s1 = {"John", 101, 85.5};
    struct Student *ptr = &s1;

    // Accessing members using arrow operator
    printf("Name: %s\n", ptr->name);
    printf("Roll: %d\n", ptr->roll_number);
    printf("Marks: %.2f\n", ptr->marks);

    // Alternative syntax (dereference then access)
    printf("Name: %s\n", (*ptr).name);

    // Modifying through pointer
    ptr->marks = 90.0;
    printf("Updated marks: %.2f\n", s1.marks);

    return 0;
}
```

### **Dynamic Structure Allocation**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    // Allocate memory for structure
    struct Student *ptr = (struct Student*)malloc(sizeof(struct Student));

    if (ptr != NULL) {
        // Initialize using pointer
        strcpy(ptr->name, "Alice");
        ptr->roll_number = 102;
        ptr->marks = 92.5;

        // Display
        printf("Name: %s\n", ptr->name);
        printf("Roll: %d\n", ptr->roll_number);
        printf("Marks: %.2f\n", ptr->marks);

        // Free memory
        free(ptr);
        ptr = NULL;
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}
```

### **Array of Structure Pointers**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    int n = 3;
    struct Student *students[n];

    // Allocate memory for each student
    for (int i = 0; i < n; i++) {
        students[i] = (struct Student*)malloc(sizeof(struct Student));
        if (students[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    // Initialize students
    strcpy(students[0]->name, "Alice");
    students[0]->roll_number = 101;
    students[0]->marks = 85.5;

    strcpy(students[1]->name, "Bob");
    students[1]->roll_number = 102;
    students[1]->marks = 92.3;

    strcpy(students[2]->name, "Charlie");
    students[2]->roll_number = 103;
    students[2]->marks = 78.9;

    // Display
    for (int i = 0; i < n; i++) {
        printf("Student %d: %s (Roll: %d, Marks: %.1f)\n",
               i + 1, students[i]->name,
               students[i]->roll_number,
               students[i]->marks);
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(students[i]);
    }

    return 0;
}
```

---

## 🔄 Structures with Functions

### **Structure Containing Function Pointers**
```c
#include <stdio.h>

struct Calculator {
    int (*add)(int, int);
    int (*subtract)(int, int);
    int (*multiply)(int, int);
    int (*divide)(int, int);
};

// Function implementations
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    struct Calculator calc = {add, subtract, multiply, divide};

    int a = 20, b = 4;

    printf("Addition: %d\n", calc.add(a, b));
    printf("Subtraction: %d\n", calc.subtract(a, b));
    printf("Multiplication: %d\n", calc.multiply(a, b));
    printf("Division: %d\n", calc.divide(a, b));

    return 0;
}
```

### **Structure Methods (Simulated)**
```c
#include <stdio.h>
#include <string.h>

struct BankAccount {
    char account_number[20];
    char owner_name[50];
    double balance;
};

// Structure methods (functions that work with structures)
void deposit(struct BankAccount *account, double amount) {
    if (amount > 0) {
        account->balance += amount;
        printf("Deposited: %.2f\n", amount);
    }
}

void withdraw(struct BankAccount *account, double amount) {
    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        printf("Withdrawn: %.2f\n", amount);
    } else {
        printf("Insufficient funds or invalid amount\n");
    }
}

void display_balance(struct BankAccount *account) {
    printf("Account: %s\n", account->account_number);
    printf("Owner: %s\n", account->owner_name);
    printf("Balance: %.2f\n", account->balance);
}

int main() {
    struct BankAccount account;

    strcpy(account.account_number, "1234567890");
    strcpy(account.owner_name, "John Doe");
    account.balance = 1000.0;

    display_balance(&account);
    deposit(&account, 500.0);
    withdraw(&account, 200.0);
    display_balance(&account);

    return 0;
}
```

---

## 🔀 Unions

### **Basic Union Declaration**
```c
#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;

    // Store integer
    data.i = 10;
    printf("Integer: %d\n", data.i);

    // Store float (overwrites integer)
    data.f = 3.14;
    printf("Float: %.2f\n", data.f);

    // Store string (overwrites float)
    strcpy(data.str, "Hello");
    printf("String: %s\n", data.str);

    // Integer value is lost
    printf("Integer (corrupted): %d\n", data.i);

    return 0;
}
```

### **Union Size and Memory Layout**
```c
#include <stdio.h>

union Data {
    int i;        // 4 bytes
    float f;      // 4 bytes
    char str[20]; // 20 bytes
};

int main() {
    union Data data;

    printf("Size of union: %zu bytes\n", sizeof(data));
    printf("Size of int: %zu bytes\n", sizeof(data.i));
    printf("Size of float: %zu bytes\n", sizeof(data.f));
    printf("Size of string: %zu bytes\n", sizeof(data.str));

    return 0;
}
```

---

## ⚖️ Structure vs Union Comparison

### **Memory Layout Comparison**

| Aspect | Structure | Union |
|--------|-----------|-------|
| **Memory** | Sum of all members | Size of largest member |
| **Access** | All members accessible | Only one member at a time |
| **Initialization** | All members can be initialized | Only first member initialized |
| **Use Case** | Related data together | Multiple data types in same memory |
| **Size** | Larger | Smaller |

### **Visual Memory Layout**

**Structure Memory Layout:**
```
struct Example {
    char c;    // 1 byte
    int i;     // 4 bytes
    float f;   // 4 bytes
};
// Total: 9 bytes + padding = 12 bytes (typically)
```

**Union Memory Layout:**
```
union Example {
    char c;    // 1 byte
    int i;     // 4 bytes
    float f;   // 4 bytes
};
// Total: 4 bytes (size of largest member)
```

### **Practical Example**
```c
#include <stdio.h>

struct Employee {
    char name[50];
    int id;
    float salary;
};

union Variant {
    int int_value;
    float float_value;
    char string_value[20];
};

int main() {
    struct Employee emp = {"John", 101, 50000.0};
    union Variant var;

    printf("Structure size: %zu bytes\n", sizeof(emp));
    printf("Union size: %zu bytes\n", sizeof(var));

    // Structure: all members accessible
    printf("Employee: %s, ID: %d, Salary: %.2f\n",
           emp.name, emp.id, emp.salary);

    // Union: only one member at a time
    var.int_value = 42;
    printf("Integer: %d\n", var.int_value);

    var.float_value = 3.14;
    printf("Float: %.2f\n", var.float_value);

    return 0;
}
```

---

## 📏 Structure Padding and Alignment

### **Understanding Padding**
```c
#include <stdio.h>

struct Example {
    char c;    // 1 byte
    int i;     // 4 bytes
    char c2;   // 1 byte
};

int main() {
    struct Example ex;

    printf("Size of struct: %zu bytes\n", sizeof(ex));
    printf("Expected size: %zu bytes\n", sizeof(char) + sizeof(int) + sizeof(char));

    // Memory layout (with padding):
    // Byte 0: c
    // Bytes 1-3: padding
    // Bytes 4-7: i
    // Byte 8: c2
    // Bytes 9-11: padding

    return 0;
}
```

### **Controlling Alignment**
```c
#include <stdio.h>

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

int main() {
    printf("Packed size: %zu bytes\n", sizeof(struct PackedExample));
    printf("Aligned size: %zu bytes\n", sizeof(struct AlignedExample));

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Use Meaningful Structure Names**
```c
// ✅ Good
struct EmployeeDetails {
    char name[50];
    int employee_id;
    float salary;
};

// ❌ Bad
struct Data {
    char n[50];
    int id;
    float s;
};
```

### **2. Initialize Structures Properly**
```c
// ✅ Complete initialization
struct Student s1 = {"John", 101, 85.5};

// ✅ Designated initialization
struct Student s2 = {
    .name = "Alice",
    .roll_number = 102,
    .marks = 92.3
};
```

### **3. Use Pointers for Large Structures**
```c
// ✅ Pass by reference for large structures
void update_student(struct Student *student) {
    student->marks += 5;
}

// ❌ Avoid pass by value for large structures
void update_student(struct Student student) {  // Inefficient
    student.marks += 5;
}
```

### **4. Choose Between struct and union Wisely**
```c
// Use struct when you need all members
struct Person {
    char name[50];
    int age;
    float height;
};

// Use union when only one member is active
union DataType {
    int int_value;
    float float_value;
    char string_value[20];
};
```

---

## 🐛 Common Mistakes

### **1. Missing Semicolon After Structure Definition**
```c
// Error
struct Student {
    char name[50];
    int roll;
}
// Missing semicolon!

// Correct
struct Student {
    char name[50];
    int roll;
};
```

### **2. Accessing Wrong Union Member**
```c
union Data {
    int i;
    float f;
};

int main() {
    union Data data;
    data.i = 10;

    // Wrong: accessing float when int was stored
    printf("%f\n", data.f);  // Garbage value

    // Correct: access the member that was stored
    printf("%d\n", data.i);
}
```

### **3. Structure Copy Issues**
```c
struct LargeStruct {
    char data[1000];
};

int main() {
    struct LargeStruct s1;
    // Initialize s1...

    // Wrong: expensive copy
    struct LargeStruct s2 = s1;

    // Better: use pointers
    struct LargeStruct *s2 = &s1;
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic Structures**
Create a structure for:
- Book (title, author, price, pages)
- Car (make, model, year, mileage)
- Product (id, name, price, quantity)

### **Exercise 2: Arrays of Structures**
Implement:
- Student database with search functionality
- Employee management system
- Library book catalog

### **Exercise 3: Nested Structures**
Build:
- Company with multiple departments
- University with multiple colleges
- Shopping cart with multiple items

### **Exercise 4: Unions**
Create unions for:
- Different data types storage
- Network packet handling
- Configuration settings

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the main difference between struct and union?
a) Struct uses more memory
b) Union allows multiple members
c) Struct members share memory
d) Union members are independent

### **Question 2:**
How do you access structure members through a pointer?
a) `ptr.member`
b) `ptr->member`
c) `*ptr.member`
d) `&ptr.member`

### **Question 3:**
What is structure padding?
a) Adding extra memory for alignment
b) Removing unused memory
c) Compressing structure size
d) Encrypting structure data

### **Question 4:**
Which operator is used to access structure members?
a) `.` (dot)
b) `->` (arrow)
c) Both a and b
d) Neither

### **Question 5:**
When should you use a union?
a) When all members are needed simultaneously
b) When only one member is active at a time
c) When memory is not a concern
d) When structures are too complex

---

## 🔗 Additional Resources

### **Structure Concepts**
- [Structures in C](https://en.cppreference.com/w/c/language/struct)
- [Unions in C](https://en.cppreference.com/w/c/language/union)
- [Memory Alignment](https://en.wikipedia.org/wiki/Data_structure_alignment)

### **Further Reading**
- [C Structures](https://www.programiz.com/c-programming/c-structures)
- [Structure Padding](https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/)
- [Unions vs Structures](https://www.tutorialspoint.com/cprogramming/c_unions.htm)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ Structure declaration and initialization
- ✅ Arrays of structures
- ✅ Nested structures
- ✅ Pointers to structures
- ✅ Union concepts and usage
- ✅ Memory layout differences

**Next Lesson Preview:**
- Dynamic memory allocation
- malloc(), calloc(), realloc(), free()
- Memory leaks and prevention
- Debugging memory errors

---

**🚀 Ready to manage dynamic memory?**

[⬅️ Previous: Pointers](10_Pointers.md) | [Next: Dynamic Memory Allocation ➡️](12_Dynamic_Memory.md)