# 🎯 Practical 162: Write Structure into File and Display Content

## 📋 Problem Statement

Program to write a structure into a file and display its content.

## 🎯 Learning Objectives

- Understand binary file I/O
- Practice structure serialization
- Learn fread and fwrite functions
- Understand data persistence
- Practice file operations with structs

## 📝 Requirements

1. Define a structure
2. Accept structure data
3. Write structure to binary file
4. Read structure from file
5. Display structure content

## 💡 Hints

- Use fwrite for binary writing
- Use fread for binary reading
- Open file in binary mode
- Handle structure padding
- Display formatted output

## 🔧 Solution

```c
// Practical 162: Write Structure into File and Display Content
// Demonstrates binary file I/O with structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
    char department[30];
};

int main() {
    FILE *filePointer;
    struct Employee emp, readEmp;
    char filename[100];

    printf("Write Structure to File and Display Content\n");
    printf("===========================================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Input employee data
    printf("\nEnter employee details:\n");
    printf("ID: ");
    scanf("%d", &emp.id);

    // Clear input buffer
    getchar();

    printf("Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    if (emp.name[strlen(emp.name) - 1] == '\n') {
        emp.name[strlen(emp.name) - 1] = '\0';
    }

    printf("Salary: ");
    scanf("%f", &emp.salary);

    // Clear input buffer
    getchar();

    printf("Department: ");
    fgets(emp.department, sizeof(emp.department), stdin);
    if (emp.department[strlen(emp.department) - 1] == '\n') {
        emp.department[strlen(emp.department) - 1] = '\0';
    }

    // Write structure to binary file
    filePointer = fopen(filename, "wb");

    if (filePointer == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }

    fwrite(&emp, sizeof(struct Employee), 1, filePointer);
    fclose(filePointer);

    printf("\nStructure written to file successfully!\n");

    // Read structure from binary file
    filePointer = fopen(filename, "rb");

    if (filePointer == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }

    fread(&readEmp, sizeof(struct Employee), 1, filePointer);
    fclose(filePointer);

    // Display read structure
    printf("\nEmployee Information from File:\n");
    printf("===============================\n");
    printf("ID: %d\n", readEmp.id);
    printf("Name: %s\n", readEmp.name);
    printf("Salary: %.2f\n", readEmp.salary);
    printf("Department: %s\n", readEmp.department);

    // Verify data integrity
    printf("\nData Integrity Check:\n");
    printf("ID Match: %s\n", emp.id == readEmp.id ? "Yes" : "No");
    printf("Name Match: %s\n", strcmp(emp.name, readEmp.name) == 0 ? "Yes" : "No");
    printf("Salary Match: %s\n", emp.salary == readEmp.salary ? "Yes" : "No");
    printf("Department Match: %s\n", strcmp(emp.department, readEmp.department) == 0 ? "Yes" : "No");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Operation
```
Input: ID: 101, Name: John Doe, Salary: 50000.50, Department: IT
Expected Output:
Structure written to file successfully!

Employee Information from File:
===============================
ID: 101
Name: John Doe
Salary: 50000.50
Department: IT

Data Integrity Check:
ID Match: Yes
Name Match: Yes
Salary Match: Yes
Department Match: Yes
```

## 🔍 Explanation

1. **Structure Definition**: Define Employee struct
2. **Data Input**: Read employee information
3. **Binary Writing**: Write structure to file using fwrite
4. **Binary Reading**: Read structure from file using fread
5. **Data Display**: Show read structure content
6. **Integrity Check**: Verify data matches original

## 🎯 Key Concepts Covered

- Binary file I/O
- Structure serialization
- fwrite and fread functions
- Data persistence
- Memory layout considerations

## 🚀 Extensions

1. Write multiple structures
2. Implement structure database
3. Handle structure arrays
4. Add error recovery