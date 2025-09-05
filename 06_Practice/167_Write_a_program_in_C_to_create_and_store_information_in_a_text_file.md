# 🎯 Practical 167: Create and Store Information in Text File

## 📋 Problem Statement

Write a program in C to create and store information in a text file.

## 🎯 Learning Objectives

- Understand file creation
- Practice text file operations
- Learn information storage
- Understand data persistence
- Practice file I/O

## 📝 Requirements

1. Create a text file
2. Accept user information
3. Store information in file
4. Handle file operations
5. Display success message

## 💡 Hints

- Use fopen with "w" mode
- Accept multiple data fields
- Use fprintf for formatted writing
- Handle file creation errors
- Close file properly

## 🔧 Solution

```c
// Practical 167: Create and Store Information in Text File
// Demonstrates creating a file and storing user information

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char name[50];
    int age;
    char address[100];
    char phone[15];

    printf("Create and Store Information in Text File\n");
    printf("=========================================\n");

    printf("Enter filename to create: ");
    scanf("%s", filename);

    // Clear input buffer
    getchar();

    printf("\nEnter personal information:\n");
    printf("Name: ");
    fgets(name, sizeof(name), stdin);
    if (name[strlen(name) - 1] == '\n') {
        name[strlen(name) - 1] = '\0';
    }

    printf("Age: ");
    scanf("%d", &age);

    // Clear input buffer
    getchar();

    printf("Address: ");
    fgets(address, sizeof(address), stdin);
    if (address[strlen(address) - 1] == '\n') {
        address[strlen(address) - 1] = '\0';
    }

    printf("Phone: ");
    fgets(phone, sizeof(phone), stdin);
    if (phone[strlen(phone) - 1] == '\n') {
        phone[strlen(phone) - 1] = '\0';
    }

    // Create and open file for writing
    filePointer = fopen(filename, "w");

    if (filePointer == NULL) {
        printf("Error creating file!\n");
        return 1;
    }

    // Write information to file
    fprintf(filePointer, "Personal Information\n");
    fprintf(filePointer, "===================\n");
    fprintf(filePointer, "Name: %s\n", name);
    fprintf(filePointer, "Age: %d\n", age);
    fprintf(filePointer, "Address: %s\n", address);
    fprintf(filePointer, "Phone: %s\n", phone);

    // Close file
    fclose(filePointer);

    printf("\nInformation stored successfully in '%s'!\n", filename);
    printf("File contains:\n");
    printf("- Name: %s\n", name);
    printf("- Age: %d\n", age);
    printf("- Address: %s\n", address);
    printf("- Phone: %s\n", phone);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Information Storage
```
Input: filename: info.txt, Name: John Doe, Age: 25, Address: 123 Main St, Phone: 555-0123
Expected Output:
Information stored successfully in 'info.txt'!
File contains:
- Name: John Doe
- Age: 25
- Address: 123 Main St
- Phone: 555-0123
```

## 🔍 Explanation

1. **File Creation**: Create new text file
2. **Data Input**: Collect user information
3. **File Writing**: Store formatted information
4. **Error Handling**: Handle file creation failures
5. **Confirmation**: Display stored information

## 🎯 Key Concepts Covered

- File creation
- Text file operations
- Formatted output
- Data storage
- File management

## 🚀 Extensions

1. Store multiple records
2. Add data validation
3. Append to existing file
4. Read and display stored information