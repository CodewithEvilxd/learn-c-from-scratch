# 🎯 Practical 148: Store Information of a Student Using Structure

## 📋 Problem Statement

C Program to Store Information of a Student Using Structure.

## 🎯 Learning Objectives

- Understand structure definition
- Practice struct usage
- Learn data organization
- Understand member access
- Practice structured data handling

## 📝 Requirements

1. Define a student structure
2. Accept student information
3. Store data in structure
4. Display student information
5. Handle multiple data types

## 💡 Hints

- Define struct with name, roll, marks
- Use struct keyword
- Access members with dot operator
- Handle string and numeric data
- Display formatted output

## 🔧 Solution

```c
// Practical 148: Store Information of a Student Using Structure
// Demonstrates using structures to store student data

#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int rollNumber;
    float marks;
    char grade;
};

int main() {
    struct Student student;

    printf("Store Student Information Using Structure\n");
    printf("=========================================\n");

    printf("Enter student name: ");
    fgets(student.name, sizeof(student.name), stdin);
    
    // Remove newline character if present
    if (student.name[strlen(student.name) - 1] == '\n') {
        student.name[strlen(student.name) - 1] = '\0';
    }

    printf("Enter roll number: ");
    scanf("%d", &student.rollNumber);

    printf("Enter marks: ");
    scanf("%f", &student.marks);

    printf("Enter grade: ");
    scanf(" %c", &student.grade);

    printf("\nStudent Information:\n");
    printf("===================\n");
    printf("Name: %s\n", student.name);
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Marks: %.2f\n", student.marks);
    printf("Grade: %c\n", student.grade);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Input
```
Input: Name: John Doe, Roll: 101, Marks: 85.5, Grade: A
Expected Output:
Student Information:
===================
Name: John Doe
Roll Number: 101
Marks: 85.50
Grade: A
```

### Test Case 2: Different Data
```
Input: Name: Alice Smith, Roll: 205, Marks: 92.0, Grade: A+
Expected Output:
Student Information:
===================
Name: Alice Smith
Roll Number: 205
Marks: 92.00
Grade: A+
```

## 🔍 Explanation

1. **Structure Definition**: Define Student struct with members
2. **Data Input**: Read student information from user
3. **Data Storage**: Store in struct instance
4. **Data Display**: Print formatted student information
5. **Type Handling**: Handle strings, integers, floats, characters

## 🎯 Key Concepts Covered

- Structure definition
- Member access
- Data types in structs
- Input handling
- Formatted output

## 🚀 Extensions

1. Add more fields to student structure
2. Store multiple students
3. Calculate grade from marks
4. Save to file