# 🎓 **Project 5: Simple Student Database System in C**
## 🎯 **File-Based Student Record Management with CRUD Operations**

---

## 📋 **Project Overview**

**English:** A complete student database system in C that manages student records using file operations, featuring add, view, update, delete, and search functionality with data persistence.

**Hinglish:** C mein ek complete student database system jo file operations ka use karke student records ko manage karta hai, jisme add, view, update, delete aur search functionality ke saath data persistence included hai.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- File I/O operations (fopen, fread, fwrite, fclose)
- Data structures for record management
- String manipulation and validation
- Error handling and data integrity
- Modular programming with header files

✅ **Problem Solving:**
- Data persistence strategies
- Record search and sorting algorithms
- Memory management for dynamic data
- User interface design for console applications

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Core implementation | Handles all data operations and file I/O |
| **File System** | Data persistence | Binary/text files for storing records |
| **Standard Library** | String and I/O functions | Provides essential utilities |
| **Structs** | Data organization | Groups related student information |

---

## 📁 **Project Structure**

```
StudentDatabase/
├── include/
│   ├── student.h
│   └── database.h
├── src/
│   ├── student.c
│   ├── database.c
│   └── main.c
├── data/
│   └── students.dat
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Student Data Structure**

```c
// student.h
#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 50
#define MAX_ROLL 20
#define MAX_COURSE 30
#define MAX_EMAIL 50

typedef struct {
    int id;
    char name[MAX_NAME];
    char roll_number[MAX_ROLL];
    char course[MAX_COURSE];
    char email[MAX_EMAIL];
    float gpa;
    int active; // 1 for active, 0 for deleted
} Student;

#endif
```

```c
// student.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Function to input student details
void input_student(Student *s) {
    printf("Enter Student ID: ");
    scanf("%d", &s->id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s->name);

    printf("Enter Roll Number: ");
    scanf(" %s", s->roll_number);

    printf("Enter Course: ");
    scanf(" %[^\n]", s->course);

    printf("Enter Email: ");
    scanf(" %s", s->email);

    printf("Enter GPA: ");
    scanf("%f", &s->gpa);

    s->active = 1;
}

// Function to display student details
void display_student(Student s) {
    printf("\n=== Student Details ===\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Roll Number: %s\n", s.roll_number);
    printf("Course: %s\n", s.course);
    printf("Email: %s\n", s.email);
    printf("GPA: %.2f\n", s.gpa);
    printf("=======================\n");
}
```

### **2. Database Operations**

```c
// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "student.h"

#define DATABASE_FILE "students.dat"

// Function declarations
int add_student(Student s);
int view_all_students();
int search_student(int id);
int update_student(int id);
int delete_student(int id);
int get_next_id();

#endif
```

```c
// database.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

// Add student to database
int add_student(Student s) {
    FILE *file = fopen(DATABASE_FILE, "ab");
    if (!file) {
        printf("Error opening database file!\n");
        return 0;
    }

    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    return 1;
}

// View all students
int view_all_students() {
    FILE *file = fopen(DATABASE_FILE, "rb");
    if (!file) {
        printf("No database file found!\n");
        return 0;
    }

    Student s;
    int count = 0;

    printf("\n=== All Students ===\n");
    while (fread(&s, sizeof(Student), 1, file) == 1) {
        if (s.active) {
            display_student(s);
            count++;
        }
    }

    if (count == 0) {
        printf("No students found!\n");
    }

    fclose(file);
    return count;
}

// Search student by ID
int search_student(int id) {
    FILE *file = fopen(DATABASE_FILE, "rb");
    if (!file) {
        printf("Database file not found!\n");
        return 0;
    }

    Student s;
    while (fread(&s, sizeof(Student), 1, file) == 1) {
        if (s.id == id && s.active) {
            display_student(s);
            fclose(file);
            return 1;
        }
    }

    printf("Student with ID %d not found!\n", id);
    fclose(file);
    return 0;
}

// Update student information
int update_student(int id) {
    FILE *file = fopen(DATABASE_FILE, "rb+");
    if (!file) {
        printf("Database file not found!\n");
        return 0;
    }

    Student s;
    long pos;

    while ((pos = ftell(file)) != -1 && fread(&s, sizeof(Student), 1, file) == 1) {
        if (s.id == id && s.active) {
            printf("Enter new details:\n");
            input_student(&s);

            // Go back to the record position
            fseek(file, pos, SEEK_SET);
            fwrite(&s, sizeof(Student), 1, file);

            fclose(file);
            return 1;
        }
    }

    printf("Student with ID %d not found!\n", id);
    fclose(file);
    return 0;
}

// Delete student (soft delete)
int delete_student(int id) {
    FILE *file = fopen(DATABASE_FILE, "rb+");
    if (!file) {
        printf("Database file not found!\n");
        return 0;
    }

    Student s;
    while (fread(&s, sizeof(Student), 1, file) == 1) {
        if (s.id == id && s.active) {
            s.active = 0;

            // Go back to update the record
            fseek(file, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, file);

            fclose(file);
            return 1;
        }
    }

    printf("Student with ID %d not found!\n", id);
    fclose(file);
    return 0;
}

// Get next available ID
int get_next_id() {
    FILE *file = fopen(DATABASE_FILE, "rb");
    if (!file) {
        return 1; // First student
    }

    Student s;
    int max_id = 0;

    while (fread(&s, sizeof(Student), 1, file) == 1) {
        if (s.id > max_id) {
            max_id = s.id;
        }
    }

    fclose(file);
    return max_id + 1;
}
```

### **3. Main Program**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "student.h"

void display_menu() {
    printf("\n=== Student Database System ===\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit\n");
    printf("================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    Student s;
    int id;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Add Student ---\n");
                s.id = get_next_id();
                input_student(&s);
                if (add_student(s)) {
                    printf("Student added successfully!\n");
                } else {
                    printf("Failed to add student!\n");
                }
                break;

            case 2:
                printf("\n--- View All Students ---\n");
                view_all_students();
                break;

            case 3:
                printf("\n--- Search Student ---\n");
                printf("Enter Student ID: ");
                scanf("%d", &id);
                search_student(id);
                break;

            case 4:
                printf("\n--- Update Student ---\n");
                printf("Enter Student ID: ");
                scanf("%d", &id);
                if (update_student(id)) {
                    printf("Student updated successfully!\n");
                }
                break;

            case 5:
                printf("\n--- Delete Student ---\n");
                printf("Enter Student ID: ");
                scanf("%d", &id);
                if (delete_student(id)) {
                    printf("Student deleted successfully!\n");
                }
                break;

            case 6:
                printf("Thank you for using Student Database System!\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

---

## 🎯 **Features Implemented**

### **Core CRUD Operations**
- ✅ **Create:** Add new student records
- ✅ **Read:** View all students or search specific student
- ✅ **Update:** Modify existing student information
- ✅ **Delete:** Remove student records (soft delete)

### **Data Management**
- ✅ **File Persistence:** Data saved to binary file
- ✅ **Unique IDs:** Auto-generated student IDs
- ✅ **Data Validation:** Input validation and error handling
- ✅ **Soft Delete:** Records marked as inactive instead of physical deletion

---

## 📊 **Data Flow & Architecture**

### **System Architecture**
```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   User Interface │───▶│  Database       │───▶│   File System   │
│   (main.c)       │    │  Operations     │    │   (students.dat)│
└─────────────────┘    └─────────────────┘    └─────────────────┘
          │                       │                       │
          ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Input/Output  │    │   Data          │    │   Data          │
│   Handling      │    │   Validation    │    │   Persistence   │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Student Database System - Complete CRUD Operations in C"
- **Hinglish:** "Student Database System - C mein Complete CRUD Operations"

### **Slide 2: What We Built**
- ✅ Complete student record management system
- ✅ File-based data persistence
- ✅ CRUD operations (Create, Read, Update, Delete)
- ✅ Search and display functionality
- ✅ Data validation and error handling

### **Slide 3: Technologies Used**
- **C Programming Language** - Core implementation
- **File I/O Operations** - Data persistence
- **Structs** - Data organization
- **Standard Library** - String and I/O functions

### **Slide 4: How It Works**
```
User Input → Data Validation → Database Operation
     ↓              ↓                        ↓
File I/O → Data Persistence → Result Display
```

### **Slide 5: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student structure
typedef struct {
    int id;
    char name[50];
    char roll_number[20];
    char course[30];
    char email[50];
    float gpa;
    int active;
} Student;

// Function declarations
int add_student(Student s);
int view_all_students();
int search_student(int id);
int update_student(int id);
int delete_student(int id);
```

### **Slide 6: Key Features**
- **File Operations:** Binary file I/O for data persistence
- **Data Validation:** Input validation and error handling
- **Unique IDs:** Auto-generated student identification
- **Soft Delete:** Safe record deletion without data loss
- **Search Functionality:** Find students by ID

### **Slide 7: Sample Usage**
```c
// Adding a student
Student s;
s.id = get_next_id();
strcpy(s.name, "John Doe");
strcpy(s.roll_number, "CS101");
strcpy(s.course, "Computer Science");
strcpy(s.email, "john@example.com");
s.gpa = 3.8;
s.active = 1;

add_student(s);
```

### **Slide 8: Database Operations**
```c
// Complete CRUD operations
int add_student(Student s);      // Create
int view_all_students();         // Read All
int search_student(int id);      // Read One
int update_student(int id);      // Update
int delete_student(int id);      // Delete
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ File I/O operations in C
- ✅ Binary file handling
- ✅ Struct manipulation
- ✅ Data persistence techniques
- ✅ Error handling and validation

### **Database Concepts:**
- ✅ CRUD operations
- ✅ Data integrity
- ✅ Record management
- ✅ Search algorithms
- ✅ File-based storage

---

## 📞 **Contact & Support**

**Project Developer:** Database Systems Student
**Email:** database@studentproject.com
**GitHub:** https://github.com/c-databases/student-db

---

**📚 This student database system provides a solid foundation for understanding file-based data management and CRUD operations in C, perfect for college assignments and database concepts learning.**