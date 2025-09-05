# 🎯 Practical 158: Read the Last Line From a File

## 📋 Problem Statement

C Program to Read the last Line From a File.

## 🎯 Learning Objectives

- Understand file reading to end
- Practice line-by-line reading
- Learn file positioning
- Understand end-of-file handling
- Practice string manipulation

## 📝 Requirements

1. Accept filename from user
2. Read entire file line by line
3. Extract and display last line
4. Handle file operations
5. Manage memory for lines

## 💡 Hints

- Read all lines using fgets
- Keep track of last line read
- Handle different line lengths
- Check for empty files
- Close file properly

## 🔧 Solution

```c
// Practical 158: Read the Last Line From a File
// Demonstrates reading the last line from a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *filePointer;
    char filename[100];
    char line[MAX_LINE_LENGTH];
    char lastLine[MAX_LINE_LENGTH] = "";
    int lineCount = 0;

    printf("Read the Last Line From a File\n");
    printf("===============================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file! File may not exist.\n");
        return 1;
    }

    // Read all lines and keep track of the last one
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        // Remove newline character if present
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Copy current line to lastLine
        strcpy(lastLine, line);
        lineCount++;
    }

    // Close file
    fclose(filePointer);

    if (lineCount == 0) {
        printf("File is empty!\n");
    } else {
        printf("Total lines in file: %d\n", lineCount);
        printf("Last line: %s\n", lastLine);
    }

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
Last line
Expected Output:
Total lines in file: 4
Last line: Last line
```

### Test Case 2: Single Line File
```
File content: Only one line
Expected Output:
Total lines in file: 1
Last line: Only one line
```

### Test Case 3: Empty File
```
File content: (empty)
Expected Output:
File is empty!
```

### Test Case 4: File Not Found
```
Input: nonexistent.txt
Expected Output:
Error opening file! File may not exist.
```

## 🔍 Explanation

1. **File Opening**: Open file in read mode
2. **Line Reading**: Read all lines using fgets loop
3. **Last Line Tracking**: Keep updating lastLine variable
4. **Line Counting**: Count total lines in file
5. **Result Display**: Show last line and statistics

## 🎯 Key Concepts Covered

- File reading operations
- Line-by-line processing
- String manipulation
- File error handling
- Memory management

## 🚀 Extensions

1. Read specific line numbers
2. Read last N lines
3. Handle very large files
4. Search for specific content