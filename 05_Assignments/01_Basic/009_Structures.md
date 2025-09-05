# 🎯 Assignment 1.9: Structures in C

## 📋 Problem Statement

Create a C program that demonstrates structure operations including declaration, initialization, nested structures, and arrays of structures. Implement a student management system with functions for adding, displaying, searching, and sorting student records.

## 🎯 Learning Objectives

- Understand structure declaration and definition
- Learn structure initialization and access
- Practice nested structures
- Work with arrays of structures
- Implement structure-based data management
- Understand structure padding and alignment

## 📝 Requirements

1. Define a Student structure with multiple fields
2. Create functions to manage student records
3. Implement add, display, search, and sort operations
4. Use nested structures for address information
5. Handle arrays of structures
6. Demonstrate structure padding

## 💡 Hints

- Use `struct` keyword for structure definition
- Access members with dot operator (.)
- Use arrow operator (->) for pointer to structure
- Structures can contain other structures
- Arrays of structures work like regular arrays

## 🔧 Solution

```c
// Assignment 1.9: Structures in C
// Student management system using structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_CITY 30

// Nested structure for address
typedef struct {
    char street[MAX_NAME];
    char city[MAX_CITY];
    char state[3];
    int zip_code;
} Address;

// Main Student structure
typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    float gpa;
    Address address;
} Student;

// Structure for managing students
typedef struct {
    Student students[MAX_STUDENTS];
    int count;
} StudentManager;

// Function prototypes
void initialize_manager(StudentManager* manager);
void add_student(StudentManager* manager);
void display_students(const StudentManager* manager);
void search_student(const StudentManager* manager);
void sort_students_by_gpa(StudentManager* manager);
void display_structure_padding();

int main() {
    StudentManager manager;
    initialize_manager(&manager);

    int choice;

    do {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Sort by GPA\n");
        printf("5. Show Structure Padding\n");
        printf("6. Exit\n");
        printf("Enter choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student(&manager);
                break;
            case 2:
                display_students(&manager);
                break;
            case 3:
                search_student(&manager);
                break;
            case 4:
                sort_students_by_gpa(&manager);
                printf("Students sorted by GPA!\n");
                break;
            case 5:
                display_structure_padding();
                break;
            case 6:
                printf("Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}

void initialize_manager(StudentManager* manager) {
    manager->count = 0;
}

void add_student(StudentManager* manager) {
    if (manager->count >= MAX_STUDENTS) {
        printf("Maximum students reached!\n");
        return;
    }

    Student* student = &manager->students[manager->count];

    printf("Enter student details:\n");

    printf("ID: ");
    scanf("%d", &student->id);

    printf("Name: ");
    scanf(" %[^\n]", student->name);

    printf("Age: ");
    scanf("%d", &student->age);

    printf("GPA: ");
    scanf("%f", &student->gpa);

    printf("Street: ");
    scanf(" %[^\n]", student->address.street);

    printf("City: ");
    scanf(" %[^\n]", student->address.city);

    printf("State (2 letters): ");
    scanf(" %s", student->address.state);

    printf("ZIP Code: ");
    scanf("%d", &student->address.zip_code);

    manager->count++;
    printf("Student added successfully!\n");
}

void display_students(const StudentManager* manager) {
    if (manager->count == 0) {
        printf("No students to display!\n");
        return;
    }

    printf("\n=== Student Records ===\n");
    for (int i = 0; i < manager->count; i++) {
        const Student* student = &manager->students[i];

        printf("\nStudent %d:\n", i + 1);
        printf("ID: %d\n", student->id);
        printf("Name: %s\n", student->name);
        printf("Age: %d\n", student->age);
        printf("GPA: %.2f\n", student->gpa);
        printf("Address: %s, %s, %s %d\n",
               student->address.street,
               student->address.city,
               student->address.state,
               student->address.zip_code);
    }
}

void search_student(const StudentManager* manager) {
    if (manager->count == 0) {
        printf("No students to search!\n");
        return;
    }

    int search_id;
    printf("Enter student ID to search: ");
    scanf("%d", &search_id);

    for (int i = 0; i < manager->count; i++) {
        if (manager->students[i].id == search_id) {
            const Student* student = &manager->students[i];

            printf("Student found!\n");
            printf("Name: %s\n", student->name);
            printf("Age: %d\n", student->age);
            printf("GPA: %.2f\n", student->gpa);
            printf("Address: %s, %s, %s %d\n",
                   student->address.street,
                   student->address.city,
                   student->address.state,
                   student->address.zip_code);
            return;
        }
    }

    printf("Student with ID %d not found!\n", search_id);
}

void sort_students_by_gpa(StudentManager* manager) {
    for (int i = 0; i < manager->count - 1; i++) {
        for (int j = 0; j < manager->count - i - 1; j++) {
            if (manager->students[j].gpa < manager->students[j + 1].gpa) {
                // Swap students
                Student temp = manager->students[j];
                manager->students[j] = manager->students[j + 1];
                manager->students[j + 1] = temp;
            }
        }
    }
}

void display_structure_padding() {
    printf("\n=== Structure Padding Analysis ===\n");

    printf("Size of Student structure: %lu bytes\n", sizeof(Student));
    printf("Size of Address structure: %lu bytes\n", sizeof(Address));

    // Individual member sizes
    printf("\nIndividual member sizes:\n");
    printf("int id: %lu bytes\n", sizeof(int));
    printf("char name[%d]: %lu bytes\n", MAX_NAME, sizeof(char) * MAX_NAME);
    printf("int age: %lu bytes\n", sizeof(int));
    printf("float gpa: %lu bytes\n", sizeof(float));
    printf("Address: %lu bytes\n", sizeof(Address));

    // Calculate expected size without padding
    size_t expected_size = sizeof(int) + (sizeof(char) * MAX_NAME) +
                          sizeof(int) + sizeof(float) + sizeof(Address);

    printf("\nExpected size (no padding): %lu bytes\n", expected_size);
    printf("Actual size: %lu bytes\n", sizeof(Student));
    printf("Padding: %lu bytes\n", sizeof(Student) - expected_size);
}
```

## 📊 Test Cases

### Test Case 1: Add Student
```
Input:
ID: 101
Name: John Doe
Age: 20
GPA: 3.8
Street: 123 Main St
City: Anytown
State: CA
ZIP: 12345
Expected Output: Student added successfully!
```

### Test Case 2: Display Students
```
Expected Output:
Student 1:
ID: 101
Name: John Doe
Age: 20
GPA: 3.80
Address: 123 Main St, Anytown, CA 12345
```

### Test Case 3: Search Student
```
Input: 101
Expected Output: Student found! (with details)
```

### Test Case 4: Structure Padding
```
Expected Output:
Size of Student structure: 168 bytes
Padding: 8 bytes (approximately)
```

## 🔍 Explanation

1. **Structure Definition**: `struct Student { ... };` defines the structure
2. **Nested Structures**: Address structure inside Student structure
3. **Structure Arrays**: Array of Student structures for multiple records
4. **Member Access**: Using dot operator (.) for direct access
5. **Structure Padding**: Compiler adds padding for memory alignment
6. **Function Parameters**: Passing structures by reference for efficiency

## 🎯 Key Concepts Covered

- Structure declaration and definition
- Nested structures
- Arrays of structures
- Structure padding and alignment
- Pointers to structures
- Structure-based data management

## 🚀 Extensions

1. Add file I/O to save/load student records
2. Implement more sorting options (by name, age)
3. Add data validation for input
4. Create functions for updating and deleting records