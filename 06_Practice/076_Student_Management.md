# 🎯 Practical 76: Student Management System

## 📋 Problem Statement

Design a Menu Driven program which performs the functions as per the menu
Add Details of students
Search the student data
a. Display the records Name must not be blank, and first letter should be alphabet
Student details should contain Name. Age, Class, Roll-No
Exit
Enter the Choice:
Note: Choice must be between 1-4 Only. Other than that, an error message must be displayed and entry should be done again

## 🎯 Learning Objectives

- Understand menu-driven programs
- Practice structure usage
- Learn data validation
- Understand array of structures
- Practice input handling

## 📝 Requirements

1. Menu with Add, Search, Display, Exit options
2. Add student with validation
3. Search student by name
4. Display all records
5. Validate name (not blank, starts with alphabet)

## 💡 Hints

- Use struct for student data
- Array of structures for storage
- Validate name format
- Implement search function
- Clear menu display

## 🔧 Solution

```c
// Practical 76: Student Management System
// Manages student records with validation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int age;
    char class[20];
    int roll_no;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// Function to validate name
int isValidName(char *name) {
    if (strlen(name) == 0) {
        return 0; // Empty name
    }
    if (!isalpha(name[0])) {
        return 0; // First character not alphabet
    }
    return 1;
}

// Function to add student
void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Maximum student limit reached!\n");
        return;
    }

    Student s;
    
    printf("Enter student name: ");
    scanf(" %[^\n]", s.name);
    
    if (!isValidName(s.name)) {
        printf("Invalid name! Name must not be blank and first letter should be alphabet.\n");
        return;
    }
    
    printf("Enter age: ");
    scanf("%d", &s.age);
    
    printf("Enter class: ");
    scanf("%s", s.class);
    
    printf("Enter roll number: ");
    scanf("%d", &s.roll_no);
    
    students[student_count] = s;
    student_count++;
    
    printf("Student added successfully!\n");
}

// Function to search student
void searchStudent() {
    char search_name[50];
    int found = 0;
    
    printf("Enter student name to search: ");
    scanf(" %[^\n]", search_name);
    
    for (int i = 0; i < student_count; i++) {
        if (strcasecmp(students[i].name, search_name) == 0) {
            printf("Student found:\n");
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Class: %s\n", students[i].class);
            printf("Roll No: %d\n", students[i].roll_no);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Student not found!\n");
    }
}

// Function to display all records
void displayRecords() {
    if (student_count == 0) {
        printf("No student records found!\n");
        return;
    }
    
    printf("Student Records:\n");
    printf("================\n");
    
    for (int i = 0; i < student_count; i++) {
        printf("Student %d:\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Class: %s\n", students[i].class);
        printf("Roll No: %d\n", students[i].roll_no);
        printf("----------------\n");
    }
}

int main() {
    int choice;
    
    while (1) {
        printf("\nStudent Management System\n");
        printf("=========================\n");
        printf("1. Add Details of students\n");
        printf("2. Search the student data\n");
        printf("3. Display the records\n");
        printf("4. Exit\n");
        printf("Enter the Choice: ");
        scanf("%d", &choice);
        
        if (choice < 1 || choice > 4) {
            printf("Invalid choice! Choice must be between 1-4 only.\n");
            continue;
        }
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                displayRecords();
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
        }
    }
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Add Valid Student
```
Choice: 1
Name: John Doe
Age: 16
Class: 10A
Roll No: 101
Expected Output: Student added successfully!
```

### Test Case 2: Invalid Name
```
Choice: 1
Name: 123John
Expected Output: Invalid name! Name must not be blank and first letter should be alphabet.
```

### Test Case 3: Search Student
```
Choice: 2
Search Name: John Doe
Expected Output: Student details displayed
```

## 🔍 Explanation

1. **Structure**: Student with name, age, class, roll_no
2. **Validation**: Name not blank, starts with alphabet
3. **Array**: Store up to 100 students
4. **Search**: Case-insensitive name search
5. **Display**: Show all student records

## 🎯 Key Concepts Covered

- Structures and arrays
- String validation
- Menu-driven interface
- Data management
- Input validation

## 🚀 Extensions

1. Delete student records
2. Update student information
3. Save data to file
4. Sort students by name/roll number