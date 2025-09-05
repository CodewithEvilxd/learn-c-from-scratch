# 🎯 Practical 150: Store Data in Structures Dynamically

## 📋 Problem Statement

C Program to Store Data in Structures Dynamically.

## 🎯 Learning Objectives

- Understand dynamic memory allocation
- Practice malloc and free
- Learn pointer to structures
- Understand memory management
- Practice dynamic data structures

## 📝 Requirements

1. Define a student structure
2. Accept number of students
3. Allocate memory dynamically
4. Store student information
5. Display and free memory

## 💡 Hints

- Use malloc to allocate struct array
- Use pointers to access struct members
- Handle memory allocation failure
- Free memory after use
- Use arrow operator for pointers

## 🔧 Solution

```c
// Practical 150: Store Data in Structures Dynamically
// Demonstrates dynamic memory allocation for structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int rollNumber;
    float marks;
    char grade;
};

int main() {
    int n;
    struct Student *students;

    printf("Store Data in Structures Dynamically\n");
    printf("=====================================\n");

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students!\n");
        return 1;
    }

    // Allocate memory dynamically
    students = (struct Student *)malloc(n * sizeof(struct Student));

    if (students == NULL) {
        printf("Memory allocation failed!\n");
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

    // Free allocated memory
    free(students);
    printf("\nMemory freed successfully!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Allocation
```
Input: 2 students
Student 1: Name: John, Roll: 101, Marks: 85.5, Grade: A
Student 2: Name: Jane, Roll: 102, Marks: 90.0, Grade: A
Expected Output:
Student Information:
===================
Student 1:
Name: John
Roll Number: 101
Marks: 85.50
Grade: A

Student 2:
Name: Jane
Roll Number: 102
Marks: 90.00
Grade: A

Memory freed successfully!
```

## 🔍 Explanation

1. **Structure Definition**: Define Student struct
2. **Dynamic Allocation**: Use malloc to allocate memory
3. **Memory Check**: Verify allocation success
4. **Data Input**: Read and store student information
5. **Data Display**: Print all student information
6. **Memory Cleanup**: Free allocated memory

## 🎯 Key Concepts Covered

- Dynamic memory allocation
- Pointer usage with structures
- Memory management
- malloc and free functions
- Error handling

## 🚀 Extensions

1. Resize allocated memory
2. Handle memory reallocation
3. Implement linked list of students
4. Add file I/O capabilities