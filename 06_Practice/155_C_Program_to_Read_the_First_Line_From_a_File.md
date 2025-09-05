# 🎯 Practical 155: Read the First Line From a File

## 📋 Problem Statement

C Program to Read the First Line From a File.

## 🎯 Learning Objectives

- Understand file reading operations
- Practice fgets function usage
- Learn file opening in read mode
- Understand line-based reading
- Practice error handling

## 📝 Requirements

1. Accept filename from user
2. Open file for reading
3. Read first line from file
4. Display the line
5. Close file properly

## 💡 Hints

- Use fopen with "r" mode
- Use fgets to read line
- Check if file exists
- Handle empty files
- Close file after reading

## 🔧 Solution

```c
// Practical 155: Read the First Line From a File
// Demonstrates reading the first line from a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char line[1000];

    printf("Read the First Line From a File\n");
    printf("===============================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file! File may not exist.\n");
        return 1;
    }

    // Read first line
    if (fgets(line, sizeof(line), filePointer) != NULL) {
        // Remove newline character if present
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        printf("First line: %s\n", line);
    } else {
        printf("File is empty or error reading file!\n");
    }

    // Close file
    fclose(filePointer);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal File
```
File content: Hello World
This is second line
Expected Output:
First line: Hello World
```

### Test Case 2: Empty File
```
File content: (empty)
Expected Output:
File is empty or error reading file!
```

### Test Case 3: Single Line File
```
File content: Single line only
Expected Output:
First line: Single line only
```

### Test Case 4: File Not Found
```
Input: nonexistent.txt
Expected Output:
Error opening file! File may not exist.
```

## 🔍 Explanation

1. **Input Reading**: Get filename from user
2. **File Opening**: Open file in read mode
3. **Error Checking**: Verify file opened successfully
4. **Line Reading**: Use fgets to read first line
5. **Display**: Show the first line content

## 🎯 Key Concepts Covered

- File reading operations
- fgets function usage
- File error handling
- Line-based reading
- String manipulation

## 🚀 Extensions

1. Read specific line numbers
2. Read all lines from file
3. Count total lines in file
4. Search for specific content