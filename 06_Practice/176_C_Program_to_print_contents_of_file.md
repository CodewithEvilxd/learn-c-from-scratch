# 🎯 Practical 176: Print Contents of File

## 📋 Problem Statement

C Program to print contents of file.

## 🎯 Learning Objectives

- Understand file reading
- Practice content display
- Learn file handling
- Understand character I/O
- Practice error handling

## 📝 Requirements

1. Accept filename from user
2. Open file for reading
3. Display file contents
4. Handle file errors
5. Close file properly

## 💡 Hints

- Use fopen with "r" mode
- Use fgetc or fgets for reading
- Display characters to console
- Handle end-of-file
- Check for read errors

## 🔧 Solution

```c
// Practical 176: Print Contents of File
// Demonstrates reading and displaying file contents

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char ch;

    printf("Print Contents of File\n");
    printf("======================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        return 1;
    }

    printf("Contents of '%s':\n", filename);
    printf("===================\n");

    // Read and display file contents
    while ((ch = fgetc(filePointer)) != EOF) {
        putchar(ch);
    }

    // Check for read errors
    if (ferror(filePointer)) {
        printf("Error reading file!\n");
        fclose(filePointer);
        return 1;
    }

    // Close file
    fclose(filePointer);

    printf("\n\nFile contents displayed successfully!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Text File
```
File content: Hello World
This is a test file.
Expected Output:
Contents of 'test.txt':
===================
Hello World
This is a test file.

File contents displayed successfully!
```

### Test Case 2: Empty File
```
File content: (empty)
Expected Output:
Contents of 'empty.txt':
===================

File contents displayed successfully!
```

## 🔍 Explanation

1. **File Opening**: Open file in read mode
2. **Content Reading**: Read characters one by one
3. **Display**: Output characters to console
4. **Error Handling**: Check for file and read errors
5. **File Closing**: Close file after reading

## 🎯 Key Concepts Covered

- File reading operations
- Character I/O
- Error handling
- File management

## 🚀 Extensions

1. Display with line numbers
2. Handle binary files
3. Add search functionality
4. Format output