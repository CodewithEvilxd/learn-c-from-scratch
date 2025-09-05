# 🎯 Practical 130: Student Records Management with File Handling

## 📋 Problem Statement

Write a C program to create and manage student records using file handling operations (create, read, update, delete records in binary/text files).

## 🎯 Learning Objectives

- Understand file handling in C
- Practice binary file operations
- Learn structured data persistence
- Implement CRUD operations with files
- Understand file pointers and operations

## 📝 Requirements

1. Implement student record management system with:
   - Add new student record
   - Display all student records
   - Search student by ID
   - Update student information
   - Delete student record
   - Save records to file
   - Load records from file

2. Use binary file for data storage
3. Handle file operations errors
4. Implement data validation
5. Provide user-friendly interface

## 💡 Hints

- Define Student structure
- Use fopen(), fread(), fwrite(), fclose()
- Implement file-based CRUD operations
- Handle file not found scenarios
- Use proper file modes (rb, wb, ab, rb+)

## 🔧 Solution

```c
// Practical 130: Student Records Management with File Handling
// Implements CRUD operations on student records using binary files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define FILENAME "students.dat"

// Student structure
typedef struct {
    int id;
    char name[MAX_NAME];
    char email[MAX_NAME];
    int age;
    float gpa;
} Student;

// Function prototypes
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveToFile(Student* students, int count);
Student* loadFromFile(int* count);
void displayStudent(Student* student);
int findStudentIndex(Student* students, int count, int id);

int main() {
    int choice;

    printf("Student Records Management System\n");
    printf("=================================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Save Records to File\n");
        printf("7. Load Records from File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6: {
                // Load current records and save
                int count;
                Student* students = loadFromFile(&count);
                if (students != NULL) {
                    saveToFile(students, count);
                    free(students);
                    printf("Records saved to file successfully!\n");
                }
                break;
            }
            case 7: {
                int count;
                Student* students = loadFromFile(&count);
                if (students != NULL) {
                    printf("Records loaded from file successfully!\n");
                    printf("Total records: %d\n", count);
                    free(students);
                }
                break;
            }
            case 0:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void addStudent() {
    Student student;

    printf("\n=== Add New Student ===\n");

    printf("Enter student ID: ");
    scanf("%d", &student.id);
    getchar();

    printf("Enter student name: ");
    fgets(student.name, MAX_NAME, stdin);
    student.name[strcspn(student.name, "\n")] = '\0'; // Remove newline

    printf("Enter student email: ");
    fgets(student.email, MAX_NAME, stdin);
    student.email[strcspn(student.email, "\n")] = '\0';

    printf("Enter student age: ");
    scanf("%d", &student.age);

    printf("Enter student GPA: ");
    scanf("%f", &student.gpa);

    // Load existing records
    int count;
    Student* students = loadFromFile(&count);

    if (students == NULL) {
        students = (Student*)malloc(sizeof(Student));
        count = 0;
    } else {
        students = (Student*)realloc(students, (count + 1) * sizeof(Student));
    }

    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Check for duplicate ID
    for (int i = 0; i < count; i++) {
        if (students[i].id == student.id) {
            printf("Student with ID %d already exists!\n", student.id);
            free(students);
            return;
        }
    }

    students[count] = student;
    count++;

    saveToFile(students, count);
    free(students);

    printf("Student added successfully!\n");
}

void displayAllStudents() {
    int count;
    Student* students = loadFromFile(&count);

    if (students == NULL || count == 0) {
        printf("No student records found!\n");
        return;
    }

    printf("\n=== All Student Records ===\n");
    printf("%-5s %-20s %-25s %-5s %-5s\n", "ID", "Name", "Email", "Age", "GPA");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-25s %-5d %-5.2f\n",
               students[i].id, students[i].name,
               students[i].email, students[i].age, students[i].gpa);
    }

    free(students);
}

void searchStudent() {
    int searchId;
    printf("Enter student ID to search: ");
    scanf("%d", &searchId);

    int count;
    Student* students = loadFromFile(&count);

    if (students == NULL || count == 0) {
        printf("No student records found!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].id == searchId) {
            printf("\nStudent found:\n");
            displayStudent(&students[i]);
            free(students);
            return;
        }
    }

    printf("Student with ID %d not found!\n", searchId);
    free(students);
}

void updateStudent() {
    int updateId;
    printf("Enter student ID to update: ");
    scanf("%d", &updateId);
    getchar();

    int count;
    Student* students = loadFromFile(&count);

    if (students == NULL || count == 0) {
        printf("No student records found!\n");
        return;
    }

    int index = findStudentIndex(students, count, updateId);
    if (index == -1) {
        printf("Student with ID %d not found!\n", updateId);
        free(students);
        return;
    }

    printf("Current information:\n");
    displayStudent(&students[index]);

    printf("\nEnter new information:\n");

    printf("Enter new name (press Enter to keep current): ");
    char newName[MAX_NAME];
    fgets(newName, MAX_NAME, stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(students[index].name, newName);
    }

    printf("Enter new email (press Enter to keep current): ");
    char newEmail[MAX_NAME];
    fgets(newEmail, MAX_NAME, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';
    if (strlen(newEmail) > 0) {
        strcpy(students[index].email, newEmail);
    }

    printf("Enter new age (0 to keep current): ");
    int newAge;
    scanf("%d", &newAge);
    if (newAge > 0) {
        students[index].age = newAge;
    }

    printf("Enter new GPA (-1 to keep current): ");
    float newGpa;
    scanf("%f", &newGpa);
    if (newGpa >= 0) {
        students[index].gpa = newGpa;
    }

    saveToFile(students, count);
    free(students);

    printf("Student information updated successfully!\n");
}

void deleteStudent() {
    int deleteId;
    printf("Enter student ID to delete: ");
    scanf("%d", &deleteId);

    int count;
    Student* students = loadFromFile(&count);

    if (students == NULL || count == 0) {
        printf("No student records found!\n");
        return;
    }

    int index = findStudentIndex(students, count, deleteId);
    if (index == -1) {
        printf("Student with ID %d not found!\n", deleteId);
        free(students);
        return;
    }

    // Shift elements to fill the gap
    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    count--;
    saveToFile(students, count);
    free(students);

    printf("Student with ID %d deleted successfully!\n", deleteId);
}

void saveToFile(Student* students, int count) {
    FILE* file = fopen(FILENAME, "wb");

    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);

    fclose(file);
}

Student* loadFromFile(int* count) {
    FILE* file = fopen(FILENAME, "rb");

    if (file == NULL) {
        *count = 0;
        return NULL;
    }

    fread(count, sizeof(int), 1, file);

    if (*count == 0) {
        fclose(file);
        return NULL;
    }

    Student* students = (Student*)malloc(*count * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return NULL;
    }

    fread(students, sizeof(Student), *count, file);

    fclose(file);
    return students;
}

void displayStudent(Student* student) {
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Email: %s\n", student->email);
    printf("Age: %d\n", student->age);
    printf("GPA: %.2f\n", student->gpa);
}

int findStudentIndex(Student* students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}
```

## 📊 Test Cases

### Test Case 1: Basic CRUD Operations
```
Operations:
1. Add student: ID=101, Name="John Doe", Email="john@example.com", Age=20, GPA=3.5
2. Add student: ID=102, Name="Jane Smith", Email="jane@example.com", Age=19, GPA=3.8
3. Display all students
4. Search student with ID=101
5. Update student ID=101 (change GPA to 3.7)
6. Delete student ID=102
```

### Test Case 2: File Persistence
```
Operations:
1. Add multiple students
2. Save to file
3. Exit program
4. Restart program
5. Load from file
6. Verify data persistence
```

## 🔍 Explanation

1. **File Operations**:
   - `fopen()`: Open file in binary mode
   - `fwrite()`: Write data to file
   - `fread()`: Read data from file
   - `fclose()`: Close file

2. **Data Structure**:
   - Student struct with fixed-size fields
   - Binary storage for efficiency
   - Count stored at beginning of file

3. **CRUD Operations**:
   - Create: Add new student record
   - Read: Display/search existing records
   - Update: Modify existing records
   - Delete: Remove records from storage

## 🎯 Key Concepts Covered

- Binary file handling
- Structured data persistence
- Dynamic memory management
- Error handling for file operations
- Data validation and integrity

## 🚀 Extensions

1. Implement text file storage
2. Add backup and restore functionality
3. Implement search by name/email
4. Add sorting and filtering options
5. Implement concurrent access handling