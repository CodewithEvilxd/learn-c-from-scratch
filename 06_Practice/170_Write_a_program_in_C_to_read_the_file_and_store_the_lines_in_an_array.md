# 🎯 Practical 170: Read File and Store Lines in Array

## 📋 Problem Statement

Write a program in C to read the file and store the lines in an array.

## 🎯 Learning Objectives

- Understand file reading with arrays
- Practice dynamic line storage
- Learn array of strings
- Understand memory allocation for strings
- Practice file parsing

## 📝 Requirements

1. Accept filename from user
2. Read file line by line
3. Store each line in array
4. Display stored lines
5. Handle memory management

## 💡 Hints

- Use array of char pointers
- Allocate memory for each line
- Use fgets for line reading
- Handle variable line lengths
- Free allocated memory

## 🔧 Solution

```c
// Practical 170: Read File and Store Lines in Array
// Demonstrates reading file lines into an array

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1000

int main() {
    FILE *filePointer;
    char filename[100];
    char *lines[MAX_LINES];
    char buffer[MAX_LINE_LENGTH];
    int lineCount = 0;

    printf("Read File and Store Lines in Array\n");
    printf("===================================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        return 1;
    }

    // Read lines and store in array
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL && lineCount < MAX_LINES) {
        // Remove newline character
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Allocate memory for this line
        lines[lineCount] = (char *)malloc(strlen(buffer) + 1);

        if (lines[lineCount] == NULL) {
            printf("Memory allocation failed!\n");
            // Free previously allocated memory
            for (int i = 0; i < lineCount; i++) {
                free(lines[i]);
            }
            fclose(filePointer);
            return 1;
        }

        // Copy line to allocated memory
        strcpy(lines[lineCount], buffer);
        lineCount++;
    }

    // Close file
    fclose(filePointer);

    // Display stored lines
    printf("\nFile contents stored in array:\n");
    printf("===============================\n");
    printf("Total lines read: %d\n\n", lineCount);

    for (int i = 0; i < lineCount; i++) {
        printf("Line %d: %s\n", i + 1, lines[i]);
    }

    // Free allocated memory
    printf("\nFreeing allocated memory...\n");
    for (int i = 0; i < lineCount; i++) {
        free(lines[i]);
    }
    printf("Memory freed successfully!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multi-line File
```
File content:
First line
Second line
Third line
Expected Output:
File contents stored in array:
===============================
Total lines read: 3

Line 1: First line
Line 2: Second line
Line 3: Third line

Freeing allocated memory...
Memory freed successfully!
```

### Test Case 2: Single Line File
```
File content: Only one line
Expected Output:
Total lines read: 1
Line 1: Only one line
```

## 🔍 Explanation

1. **File Reading**: Open and read file line by line
2. **Memory Allocation**: Allocate memory for each line
3. **Line Storage**: Store lines in array of pointers
4. **Display**: Show stored lines with line numbers
5. **Memory Cleanup**: Free all allocated memory

## 🎯 Key Concepts Covered

- Dynamic memory allocation
- Array of strings
- File reading
- Memory management
- String operations

## 🚀 Extensions

1. Handle files with more lines than array size
2. Sort lines in array
3. Search for specific content
4. Write array back to file