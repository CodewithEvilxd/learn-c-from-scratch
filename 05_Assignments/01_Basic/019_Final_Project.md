# 🎯 Assignment 1.19: Basic Final Project

## 📋 Problem Statement

Create a comprehensive C program that integrates multiple concepts learned so far. Build a simple student grade management system that uses files for data persistence, implements data structures, and provides a menu-driven interface.

## 🎯 Learning Objectives

- Integrate multiple C programming concepts
- Implement file-based data persistence
- Create menu-driven user interface
- Use data structures for data management
- Handle errors and edge cases
- Practice modular programming

## 📝 Requirements

1. Create student structure with grades
2. Implement file I/O for data persistence
3. Provide menu-driven interface
4. Calculate GPA and statistics
5. Search and sort students
6. Handle errors gracefully
7. Use functions for modularity

## 💡 Hints

- Use structures for student data
- Implement file save/load operations
- Create separate functions for each operation
- Use arrays or linked lists for data storage
- Validate user input
- Provide clear menu options

## 🔧 Solution

```c
// Assignment 1.19: Basic Final Project
// Student Grade Management System

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_SUBJECTS 5
#define DATA_FILE "students.dat"

// Student structure
typedef struct {
    int id;
    char name[MAX_NAME];
    float grades[MAX_SUBJECTS];
    int num_grades;
    float gpa;
} Student;

// Student database
typedef struct {
    Student students[MAX_STUDENTS];
    int count;
} StudentDB;

// Function prototypes
void initialize_database(StudentDB* db);
void display_menu();
void add_student(StudentDB* db);
void display_students(const StudentDB* db);
void search_student(const StudentDB* db);
void calculate_gpa(Student* student);
void save_to_file(const StudentDB* db);
void load_from_file(StudentDB* db);
void generate_report(const StudentDB* db);
float calculate_class_average(const StudentDB* db);

int main() {
    StudentDB db;
    initialize_database(&db);
    load_from_file(&db);

    int choice;

    do {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                add_student(&db);
                break;
            case 2:
                display_students(&db);
                break;
            case 3:
                search_student(&db);
                break;
            case 4:
                generate_report(&db);
                break;
            case 5:
                save_to_file(&db);
                printf("Data saved successfully!\n");
                break;
            case 6:
                printf("Thank you for using the Student Grade Management System!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }

        if (choice != 6) {
            printf("\nPress Enter to continue...");
            getchar();
        }

    } while (choice != 6);

    return 0;
}

void initialize_database(StudentDB* db) {
    db->count = 0;
}

void display_menu() {
    printf("\n=== Student Grade Management System ===\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student\n");
    printf("4. Generate Report\n");
    printf("5. Save Data\n");
    printf("6. Exit\n");
    printf("Enter your choice (1-6): ");
}

void add_student(StudentDB* db) {
    if (db->count >= MAX_STUDENTS) {
        printf("Database is full! Cannot add more students.\n");
        return;
    }

    Student* student = &db->students[db->count];

    printf("Enter student details:\n");

    // Get student ID
    printf("ID: ");
    scanf("%d", &student->id);
    getchar(); // Consume newline

    // Check for duplicate ID
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == student->id) {
            printf("Error: Student ID already exists!\n");
            return;
        }
    }

    // Get student name
    printf("Name: ");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = '\0';

    // Get grades
    printf("Enter grades for %d subjects (0-100):\n", MAX_SUBJECTS);
    student->num_grades = 0;

    for (int i = 0; i < MAX_SUBJECTS; i++) {
        float grade;
        printf("Subject %d: ", i + 1);
        scanf("%f", &grade);

        if (grade >= 0 && grade <= 100) {
            student->grades[i] = grade;
            student->num_grades++;
        } else {
            printf("Invalid grade! Skipping subject %d.\n", i + 1);
            student->grades[i] = 0;
        }
    }

    // Calculate GPA
    calculate_gpa(student);

    db->count++;
    printf("Student added successfully!\n");
}

void display_students(const StudentDB* db) {
    if (db->count == 0) {
        printf("No students in the database!\n");
        return;
    }

    printf("\n=== Student Records ===\n");
    printf("%-5s %-20s %-10s %-15s\n", "ID", "Name", "GPA", "Subjects");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < db->count; i++) {
        const Student* student = &db->students[i];

        printf("%-5d %-20s %-10.2f ",
               student->id, student->name, student->gpa);

        for (int j = 0; j < student->num_grades; j++) {
            printf("%.1f", student->grades[j]);
            if (j < student->num_grades - 1) printf(",");
        }
        printf("\n");
    }

    printf("\nClass Average GPA: %.2f\n", calculate_class_average(db));
}

void search_student(const StudentDB* db) {
    if (db->count == 0) {
        printf("No students in the database!\n");
        return;
    }

    int search_id;
    printf("Enter student ID to search: ");
    scanf("%d", &search_id);

    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == search_id) {
            const Student* student = &db->students[i];

            printf("\nStudent Found:\n");
            printf("ID: %d\n", student->id);
            printf("Name: %s\n", student->name);
            printf("GPA: %.2f\n", student->gpa);
            printf("Grades: ");

            for (int j = 0; j < student->num_grades; j++) {
                printf("%.1f", student->grades[j]);
                if (j < student->num_grades - 1) printf(", ");
            }
            printf("\n");
            return;
        }
    }

    printf("Student with ID %d not found!\n", search_id);
}

void calculate_gpa(Student* student) {
    if (student->num_grades == 0) {
        student->gpa = 0.0;
        return;
    }

    float sum = 0;
    for (int i = 0; i < student->num_grades; i++) {
        sum += student->grades[i];
    }

    student->gpa = sum / student->num_grades;
}

void save_to_file(const StudentDB* db) {
    FILE* file = fopen(DATA_FILE, "wb");
    if (!file) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    fwrite(&db->count, sizeof(int), 1, file);

    for (int i = 0; i < db->count; i++) {
        fwrite(&db->students[i], sizeof(Student), 1, file);
    }

    fclose(file);
}

void load_from_file(StudentDB* db) {
    FILE* file = fopen(DATA_FILE, "rb");
    if (!file) {
        printf("No existing data file found. Starting with empty database.\n");
        return;
    }

    fread(&db->count, sizeof(int), 1, file);

    for (int i = 0; i < db->count; i++) {
        fread(&db->students[i], sizeof(Student), 1, file);
    }

    fclose(file);
    printf("Data loaded successfully from file!\n");
}

void generate_report(const StudentDB* db) {
    if (db->count == 0) {
        printf("No students in the database!\n");
        return;
    }

    printf("\n=== Class Report ===\n");
    printf("Total Students: %d\n", db->count);
    printf("Class Average GPA: %.2f\n", calculate_class_average(db));

    // Grade distribution
    int grade_counts[5] = {0}; // A, B, C, D, F

    for (int i = 0; i < db->count; i++) {
        float gpa = db->students[i].gpa;
        if (gpa >= 90) grade_counts[0]++;
        else if (gpa >= 80) grade_counts[1]++;
        else if (gpa >= 70) grade_counts[2]++;
        else if (gpa >= 60) grade_counts[3]++;
        else grade_counts[4]++;
    }

    printf("\nGrade Distribution:\n");
    printf("A (90-100): %d students\n", grade_counts[0]);
    printf("B (80-89): %d students\n", grade_counts[1]);
    printf("C (70-79): %d students\n", grade_counts[2]);
    printf("D (60-69): %d students\n", grade_counts[3]);
    printf("F (0-59): %d students\n", grade_counts[4]);
}

float calculate_class_average(const StudentDB* db) {
    if (db->count == 0) return 0.0;

    float sum = 0;
    for (int i = 0; i < db->count; i++) {
        sum += db->students[i].gpa;
    }

    return sum / db->count;
}
```

## 📊 Test Cases

### Test Case 1: Add Student
```
Input:
ID: 101
Name: John Doe
Grades: 85, 90, 88, 92, 87
Expected Output: Student added successfully!
```

### Test Case 2: Display Students
```
Expected Output:
ID    Name                 GPA        Subjects
--------------------------------------------------
101  John Doe            88.40      85.0,90.0,88.0,92.0,87.0
```

### Test Case 3: Search Student
```
Input: 101
Expected Output: Student details displayed
```

### Test Case 4: Generate Report
```
Expected Output:
Total Students: 1
Class Average GPA: 88.40
Grade Distribution:
A (90-100): 0 students
B (80-89): 1 students
...
```

## 🔍 Explanation

1. **Student Structure**: Contains ID, name, grades, and GPA
2. **File I/O**: Binary file operations for data persistence
3. **Menu System**: User-friendly interface with options
4. **Data Validation**: Check for duplicate IDs and valid grades
5. **Statistics**: GPA calculation and class reports
6. **Modular Design**: Separate functions for each operation

## 🎯 Key Concepts Covered

- Structures and data organization
- File I/O operations
- Menu-driven interfaces
- Data validation and error handling
- Modular programming
- Array manipulation
- Statistical calculations

## 🚀 Extensions

1. Add student deletion and modification
2. Implement sorting by GPA or name
3. Add subject-wise analysis
4. Create graphical reports
5. Add password protection