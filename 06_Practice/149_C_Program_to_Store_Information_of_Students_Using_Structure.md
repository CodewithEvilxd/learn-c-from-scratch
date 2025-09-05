# 🎯 Practical 149: Store Information of Students Using Structure

## 📋 Problem Statement

C Program to Store Information of Students Using Structure.

## 🎯 Learning Objectives

- Understand array of structures
- Practice multiple struct instances
- Learn data organization
- Understand struct arrays
- Practice bulk data handling

## 📝 Requirements

1. Define a student structure
2. Accept number of students
3. Store information for each student
4. Display all student information
5. Handle multiple data entries

## 💡 Hints

- Define struct with student fields
- Create array of structs
- Use loop for multiple entries
- Access members with array indexing
- Display formatted output for all

## 🔧 Solution

```c
// Practical 149: Store Information of Students Using Structure
// Demonstrates using array of structures to store multiple students

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10

struct Student {
    char name[50];
    int rollNumber;
    float marks;
    char grade;
};

int main() {
    struct Student students[MAX_STUDENTS];
    int n;

    printf("Store Information of Students Using Structure\n");
    printf("=============================================\n");

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("Invalid number! Must be between 1 and %d.\n", MAX_STUDENTS);
        return 1;
    }

    // Clear input buffer
    getchar();

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Student %d:\n", i + 1);
        
        printf("Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        
        // Remove newline character
        if (students[i].name[strlen(students[i].name) - 1] == '\n') {
            students[i].name[strlen(students[i].name) - 1] = '\0';
        }

        printf("Roll Number: ");
        scanf("%d", &students[i].rollNumber);

        printf("Marks: ");
        scanf("%f", &students[i].marks);

        printf("Grade: ");
        scanf(" %c", &students[i].grade);

        // Clear input buffer
        getchar();
    }

    printf("\nStudent Information:\n");
    printf("===================\n");

    for (int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Marks: %.2f\n", students[i].marks);
        printf("Grade: %c\n", students[i].grade);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Two Students
```
Input: 2 students
Student 1: Name: John Doe, Roll: 101, Marks: 85.5, Grade: A
Student 2: Name: Jane Smith, Roll: 102, Marks: 92.0, Grade: A+
Expected Output:
Student Information:
===================
Student 1:
Name: John Doe
Roll Number: 101
Marks: 85.50
Grade: A

Student 2:
Name: Jane Smith
Roll Number: 102
Marks: 92.00
Grade: A+
```

## 🔍 Explanation

1. **Structure Definition**: Define Student struct
2. **Array Declaration**: Create array of Student structs
3. **Input Loop**: Read information for each student
4. **Data Storage**: Store in respective struct instances
5. **Display Loop**: Print information for all students

## 🎯 Key Concepts Covered

- Array of structures
- Multiple data entry
- Struct member access
- Loop-based input/output
- Data organization

## 🚀 Extensions

1. Sort students by marks
2. Find student with highest marks
3. Search for specific student
4. Save student data to file