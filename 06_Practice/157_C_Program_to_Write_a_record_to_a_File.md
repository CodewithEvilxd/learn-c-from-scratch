# 🎯 Practical 157: Write a Record to a File

## 📋 Problem Statement

C Program to Write a record to a File.

## 🎯 Learning Objectives

- Understand structured data writing
- Practice file I/O with records
- Learn fprintf with multiple fields
- Understand data persistence
- Practice record management

## 📝 Requirements

1. Define a record structure
2. Accept record data from user
3. Write record to file
4. Handle file operations
5. Display success message

## 💡 Hints

- Define struct for record
- Use fprintf for formatted writing
- Handle string and numeric data
- Check file operation success
- Close file properly

## 🔧 Solution

```c
// Practical 157: Write a Record to a File
// Demonstrates writing structured data to a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int id;
    char name[50];
    float salary;
    char department[30];
};

int main() {
    FILE *filePointer;
    struct Record record;
    char filename[100];

    printf("Write a Record to a File\n");
    printf("========================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    printf("Enter record details:\n");
    printf("ID: ");
    scanf("%d", &record.id);

    // Clear input buffer
    getchar();

    printf("Name: ");
    fgets(record.name, sizeof(record.name), stdin);
    if (record.name[strlen(record.name) - 1] == '\n') {
        record.name[strlen(record.name) - 1] = '\0';
    }

    printf("Salary: ");
    scanf("%f", &record.salary);

    // Clear input buffer
    getchar();

    printf("Department: ");
    fgets(record.department, sizeof(record.department), stdin);
    if (record.department[strlen(record.department) - 1] == '\n') {
        record.department[strlen(record.department) - 1] = '\0';
    }

    // Open file for writing
    filePointer = fopen(filename, "a");

    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write record to file
    fprintf(filePointer, "%d,%s,%.2f,%s\n",
            record.id, record.name, record.salary, record.department);

    // Close file
    fclose(filePointer);

    printf("Record written to file successfully!\n");
    printf("Record Details:\n");
    printf("ID: %d\n", record.id);
    printf("Name: %s\n", record.name);
    printf("Salary: %.2f\n", record.salary);
    printf("Department: %s\n", record.department);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Record
```
Input: ID: 101, Name: John Doe, Salary: 50000.50, Department: IT
Expected Output:
Record written to file successfully!
Record Details:
ID: 101
Name: John Doe
Salary: 50000.50
Department: IT
```

### Test Case 2: Different Data
```
Input: ID: 205, Name: Jane Smith, Salary: 45000.00, Department: HR
Expected Output:
Record written to file successfully!
Record Details:
ID: 205
Name: Jane Smith
Salary: 45000.00
Department: HR
```

## 🔍 Explanation

1. **Structure Definition**: Define Record struct with fields
2. **Data Input**: Read record data from user
3. **File Opening**: Open file in append mode
4. **Record Writing**: Use fprintf to write formatted record
5. **File Closing**: Close file and confirm operation

## 🎯 Key Concepts Covered

- Structured data writing
- File I/O operations
- fprintf with multiple fields
- Record management
- Data persistence

## 🚀 Extensions

1. Write multiple records
2. Read records from file
3. Update existing records
4. Search records in file