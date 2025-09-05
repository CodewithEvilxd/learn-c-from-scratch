# 🎯 Practical 188: Student Result Management System

## 📋 Problem Statement

Design a Simple Result System in the C programming language. You can keep track of the pupils' grades and update them at any time. Students might be given marks based on their performance in each subject.

## 🎯 Learning Objectives

- Understand student data management
- Practice grade calculation and reporting
- Learn result processing
- Understand academic record keeping
- Practice file-based data storage

## 📝 Requirements

1. **Student Management**:
   - Add new students
   - Edit student information
   - Delete students
   - Display all students

2. **Grade Management**:
   - Add/update marks for subjects
   - Calculate total and percentage
   - Assign grades (A, B, C, D, F)
   - Generate result reports

3. **Subject Management**:
   - Define subjects and maximum marks
   - Track subject-wise performance

## 💡 Hints

- Use structures for Student and Subject data
- Implement grade calculation logic
- Create result reports
- Use file I/O for data persistence
- Handle multiple subjects per student

## 🔧 Solution

```c
// Practical 188: Student Result Management System
// Complete solution for managing student grades and results

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10
#define MAX_NAME_LENGTH 50

// Subject structure
struct Subject {
    char name[30];
    int maxMarks;
};

// Student structure
struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    char class[20];
    int marks[MAX_SUBJECTS];
    int numSubjects;
    int active;
};

// Global variables
struct Student students[MAX_STUDENTS];
struct Subject subjects[MAX_SUBJECTS];
int studentCount = 0;
int subjectCount = 0;

// File names
#define STUDENT_FILE "students.dat"
#define SUBJECT_FILE "subjects.dat"

// Function prototypes
void displayMainMenu();
void studentMenu();
void subjectMenu();
void resultMenu();

void addStudent();
void editStudent();
void deleteStudent();
void displayStudents();
void searchStudent();

void addSubject();
void displaySubjects();

void addMarks();
void viewResult();
void generateReport();
void calculateGrade(int marks, int maxMarks, char *grade);

void loadData();
void saveData();
int generateRollNumber();

int main() {
    loadData();

    int choice;
    while (1) {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                studentMenu();
                break;
            case 2:
                subjectMenu();
                break;
            case 3:
                resultMenu();
                break;
            case 4:
                saveData();
                printf("Data saved successfully!\n");
                break;
            case 5:
                saveData();
                printf("Thank you for using Student Result Management System!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }

    return 0;
}

void displayMainMenu() {
    printf("\n=== STUDENT RESULT MANAGEMENT SYSTEM ===\n");
    printf("1. Student Management\n");
    printf("2. Subject Management\n");
    printf("3. Result Management\n");
    printf("4. Save Data\n");
    printf("5. Exit\n");
    printf("=======================================\n");
}

void studentMenu() {
    int choice;
    while (1) {
        printf("\n=== STUDENT MANAGEMENT ===\n");
        printf("1. Add Student\n");
        printf("2. Edit Student\n");
        printf("3. Delete Student\n");
        printf("4. Display All Students\n");
        printf("5. Search Student\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                editStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                displayStudents();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice!\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student database is full!\n");
        return;
    }

    struct Student student;
    student.rollNumber = generateRollNumber();

    printf("=== ADD NEW STUDENT ===\n");
    printf("Roll Number: %d\n", student.rollNumber);

    printf("Name: ");
    getchar();
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = 0;

    printf("Class: ");
    fgets(student.class, sizeof(student.class), stdin);
    student.class[strcspn(student.class, "\n")] = 0;

    student.numSubjects = subjectCount;
    memset(student.marks, 0, sizeof(student.marks));
    student.active = 1;

    students[studentCount++] = student;
    printf("Student added successfully!\n");
}

void editStudent() {
    int roll, found = 0;

    printf("Enter Roll Number to edit: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll && students[i].active) {
            printf("Current Student Details:\n");
            printf("Name: %s\n", students[i].name);
            printf("Class: %s\n", students[i].class);

            printf("\nEnter New Details:\n");

            printf("Name: ");
            getchar();
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("Class: ");
            fgets(students[i].class, sizeof(students[i].class), stdin);
            students[i].class[strcspn(students[i].class, "\n")] = 0;

            printf("Student updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found!\n", roll);
    }
}

void deleteStudent() {
    int roll, found = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll && students[i].active) {
            students[i].active = 0;
            printf("Student deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found!\n", roll);
    }
}

void displayStudents() {
    printf("=== STUDENT DATABASE ===\n");
    printf("%-10s %-20s %-15s\n", "Roll No", "Name", "Class");
    printf("----------------------------------------\n");

    int count = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].active) {
            printf("%-10d %-20s %-15s\n",
                   students[i].rollNumber,
                   students[i].name,
                   students[i].class);
            count++;
        }
    }

    if (count == 0) {
        printf("No students found!\n");
    } else {
        printf("\nTotal students: %d\n", count);
    }
}

void searchStudent() {
    int roll, found = 0;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll && students[i].active) {
            printf("Student Found:\n");
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s\n", students[i].name);
            printf("Class: %s\n", students[i].class);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found!\n", roll);
    }
}

void subjectMenu() {
    int choice;
    while (1) {
        printf("\n=== SUBJECT MANAGEMENT ===\n");
        printf("1. Add Subject\n");
        printf("2. Display All Subjects\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addSubject();
                break;
            case 2:
                displaySubjects();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice!\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

void addSubject() {
    if (subjectCount >= MAX_SUBJECTS) {
        printf("Maximum subjects reached!\n");
        return;
    }

    struct Subject subject;

    printf("=== ADD NEW SUBJECT ===\n");

    printf("Subject Name: ");
    getchar();
    fgets(subject.name, sizeof(subject.name), stdin);
    subject.name[strcspn(subject.name, "\n")] = 0;

    printf("Maximum Marks: ");
    scanf("%d", &subject.maxMarks);

    subjects[subjectCount++] = subject;
    printf("Subject added successfully!\n");
}

void displaySubjects() {
    printf("=== SUBJECT LIST ===\n");
    printf("%-5s %-20s %-10s\n", "S.No", "Subject", "Max Marks");
    printf("--------------------------------\n");

    for (int i = 0; i < subjectCount; i++) {
        printf("%-5d %-20s %-10d\n", i + 1, subjects[i].name, subjects[i].maxMarks);
    }

    if (subjectCount == 0) {
        printf("No subjects found!\n");
    }
}

void resultMenu() {
    int choice;
    while (1) {
        printf("\n=== RESULT MANAGEMENT ===\n");
        printf("1. Add/Update Marks\n");
        printf("2. View Student Result\n");
        printf("3. Generate Class Report\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMarks();
                break;
            case 2:
                viewResult();
                break;
            case 3:
                generateReport();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

void addMarks() {
    int roll, found = 0;

    printf("Enter Student Roll Number: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll && students[i].active) {
            printf("Student: %s\n", students[i].name);
            printf("Enter marks for each subject:\n");

            for (int j = 0; j < subjectCount; j++) {
                printf("%s (Max: %d): ", subjects[j].name, subjects[j].maxMarks);
                scanf("%d", &students[i].marks[j]);

                // Validate marks
                if (students[i].marks[j] < 0) {
                    students[i].marks[j] = 0;
                } else if (students[i].marks[j] > subjects[j].maxMarks) {
                    students[i].marks[j] = subjects[j].maxMarks;
                }
            }

            printf("Marks updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found!\n", roll);
    }
}

void viewResult() {
    int roll, found = 0;

    printf("Enter Student Roll Number: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll && students[i].active) {
            printf("\n=== STUDENT RESULT ===\n");
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s\n", students[i].name);
            printf("Class: %s\n", students[i].class);
            printf("------------------------\n");

            int totalMarks = 0;
            int totalMaxMarks = 0;

            printf("%-20s %-8s %-8s %-6s\n", "Subject", "Marks", "Max", "Grade");
            printf("----------------------------------------\n");

            for (int j = 0; j < subjectCount; j++) {
                char grade[3];
                calculateGrade(students[i].marks[j], subjects[j].maxMarks, grade);

                printf("%-20s %-8d %-8d %-6s\n",
                       subjects[j].name,
                       students[i].marks[j],
                       subjects[j].maxMarks,
                       grade);

                totalMarks += students[i].marks[j];
                totalMaxMarks += subjects[j].maxMarks;
            }

            printf("----------------------------------------\n");
            printf("Total: %d/%d\n", totalMarks, totalMaxMarks);

            float percentage = (float)totalMarks / totalMaxMarks * 100;
            printf("Percentage: %.2f%%\n", percentage);

            char overallGrade[3];
            calculateGrade(totalMarks, totalMaxMarks, overallGrade);
            printf("Overall Grade: %s\n", overallGrade);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found!\n", roll);
    }
}

void generateReport() {
    printf("=== CLASS RESULT REPORT ===\n");
    printf("%-10s %-20s %-8s %-10s %-6s\n",
           "Roll No", "Name", "Total", "Percentage", "Grade");
    printf("----------------------------------------------------\n");

    int count = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].active) {
            int totalMarks = 0;
            int totalMaxMarks = 0;

            for (int j = 0; j < subjectCount; j++) {
                totalMarks += students[i].marks[j];
                totalMaxMarks += subjects[j].maxMarks;
            }

            float percentage = (float)totalMarks / totalMaxMarks * 100;
            char grade[3];
            calculateGrade(totalMarks, totalMaxMarks, grade);

            printf("%-10d %-20s %-8d %-10.2f %-6s\n",
                   students[i].rollNumber,
                   students[i].name,
                   totalMarks,
                   percentage,
                   grade);

            count++;
        }
    }

    if (count == 0) {
        printf("No students found!\n");
    } else {
        printf("\nTotal students: %d\n", count);
    }
}

void calculateGrade(int marks, int maxMarks, char *grade) {
    float percentage = (float)marks / maxMarks * 100;

    if (percentage >= 90) {
        strcpy(grade, "A");
    } else if (percentage >= 80) {
        strcpy(grade, "B");
    } else if (percentage >= 70) {
        strcpy(grade, "C");
    } else if (percentage >= 60) {
        strcpy(grade, "D");
    } else {
        strcpy(grade, "F");
    }
}

// Utility functions
void loadData() {
    FILE *file;

    // Load subjects
    file = fopen(SUBJECT_FILE, "rb");
    if (file != NULL) {
        subjectCount = fread(subjects, sizeof(struct Subject), MAX_SUBJECTS, file);
        fclose(file);
    }

    // Load students
    file = fopen(STUDENT_FILE, "rb");
    if (file != NULL) {
        studentCount = fread(students, sizeof(struct Student), MAX_STUDENTS, file);
        fclose(file);
    }
}

void saveData() {
    FILE *file;

    // Save subjects
    file = fopen(SUBJECT_FILE, "wb");
    if (file != NULL) {
        fwrite(subjects, sizeof(struct Subject), subjectCount, file);
        fclose(file);
    }

    // Save students
    file = fopen(STUDENT_FILE, "wb");
    if (file != NULL) {
        fwrite(students, sizeof(struct Student), studentCount, file);
        fclose(file);
    }
}

int generateRollNumber() {
    int maxRoll = 1000;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber > maxRoll) {
            maxRoll = students[i].rollNumber;
        }
    }
    return maxRoll + 1;
}
```

## 📊 Test Cases

### Test Case 1: Add Student
```
Name: John Doe
Class: 10th Grade
Expected: Student added with auto-generated roll number
```

### Test Case 2: Add Subject
```
Subject: Mathematics
Max Marks: 100
Expected: Subject added to system
```

### Test Case 3: Add Marks and View Result
```
Roll Number: 1001
Marks: Math: 85, Science: 92, English: 78
Expected: Result displayed with grades and percentage
```

## 🔍 Explanation

1. **Student Management**: Complete CRUD operations for students
2. **Subject Management**: Define subjects with maximum marks
3. **Grade Management**: Add/update marks and calculate results
4. **Result Generation**: Automatic grade calculation and reporting
5. **File Persistence**: Data saved to binary files

## 🎯 Key Concepts Covered

- Academic data management
- Grade calculation algorithms
- Result processing
- Report generation
- File-based storage

## 🚀 Extensions

1. Add attendance tracking
2. Generate transcripts
3. Implement ranking system
4. Add parent notification system
5. Create graphical reports