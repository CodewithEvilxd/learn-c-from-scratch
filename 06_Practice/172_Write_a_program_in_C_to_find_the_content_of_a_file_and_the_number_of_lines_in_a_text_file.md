# 🎯 Practical 172: Find Content and Line Count in Text File

## 📋 Problem Statement

Write a program in C to find the content of a file and the number of lines in a text file.

## 🎯 Learning Objectives

- Understand comprehensive file analysis
- Practice content reading and counting
- Learn file statistics generation
- Understand combined operations
- Practice structured output

## 📝 Requirements

1. Accept filename from user
2. Read and display file contents
3. Count lines in file
4. Show both content and statistics
5. Handle file operations

## 💡 Hints

- Read file line by line
- Display each line with numbers
- Count lines during reading
- Show content and statistics
- Handle large files

## 🔧 Solution

```c
// Practical 172: Find Content and Line Count in Text File
// Demonstrates reading file content and counting lines

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *filePointer;
    char filename[100];
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    printf("Find Content and Line Count in Text File\n");
    printf("=========================================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        printf("Make sure the file exists and you have read permissions.\n");
        return 1;
    }

    printf("\nFile Contents:\n");
    printf("==============\n");

    // Read and display file contents with line numbers
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        lineCount++;
        printf("%3d: %s", lineCount, line);
    }

    // Check for read errors
    if (ferror(filePointer)) {
        printf("Error reading file!\n");
        fclose(filePointer);
        return 1;
    }

    // Close file
    fclose(filePointer);

    // Display statistics
    printf("\nFile Statistics:\n");
    printf("================\n");
    printf("Filename: %s\n", filename);
    printf("Total lines: %d\n", lineCount);

    if (lineCount == 0) {
        printf("Status: Empty file\n");
    } else if (lineCount == 1) {
        printf("Status: Single line file\n");
    } else {
        printf("Status: Multi-line file\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multi-line File
```
File content:
First line of text
Second line here
Third and final line
Expected Output:
File Contents:
==============
  1: First line of text
  2: Second line here
  3: Third and final line

File Statistics:
================
Filename: test.txt
Total lines: 3
Status: Multi-line file
```

### Test Case 2: Single Line File
```
File content: Only one line
Expected Output:
  1: Only one line
Total lines: 1
Status: Single line file
```

### Test Case 3: Empty File
```
File content: (empty)
Expected Output:
File Contents:
==============

File Statistics:
================
Total lines: 0
Status: Empty file
```

## 🔍 Explanation

1. **File Reading**: Open and read file line by line
2. **Content Display**: Show lines with line numbers
3. **Line Counting**: Count lines during reading
4. **Statistics**: Display filename and line count
5. **Status**: Show file type based on line count

## 🎯 Key Concepts Covered

- File content reading
- Line numbering
- File statistics
- Combined operations
- Formatted output

## 🚀 Extensions

1. Count words and characters too
2. Find longest/shortest line
3. Add search functionality
4. Handle binary files