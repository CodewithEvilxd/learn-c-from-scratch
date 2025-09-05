# 🎯 Practical 168: Read an Existing File

## 📋 Problem Statement

Write a program in C to read an existing file.

## 🎯 Learning Objectives

- Understand file reading operations
- Practice file opening in read mode
- Learn character-by-character reading
- Understand file existence checking
- Practice error handling

## 📝 Requirements

1. Accept filename from user
2. Open existing file for reading
3. Read and display file contents
4. Handle file not found errors
5. Close file properly

## 💡 Hints

- Use fopen with "r" mode
- Use fgetc or fgets for reading
- Check if file exists
- Handle end-of-file condition
- Display contents to console

## 🔧 Solution

```c
// Practical 168: Read an Existing File
// Demonstrates reading contents from an existing file

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char ch;

    printf("Read an Existing File\n");
    printf("=====================\n");

    printf("Enter filename to read: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        printf("Possible reasons:\n");
        printf("- File does not exist\n");
        printf("- No read permissions\n");
        printf("- Invalid filename\n");
        return 1;
    }

    printf("Reading file '%s':\n", filename);
    printf("===================\n");

    // Read and display file contents character by character
    while ((ch = fgetc(filePointer)) != EOF) {
        putchar(ch);
    }

    // Check for read errors
    if (ferror(filePointer)) {
        printf("\nError reading file!\n");
        fclose(filePointer);
        return 1;
    }

    // Close file
    fclose(filePointer);

    printf("\n\nFile read successfully!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal File Reading
```
File content: Hello World
This is a test file.
Expected Output:
Reading file 'test.txt':
===================
Hello World
This is a test file.

File read successfully!
```

### Test Case 2: Empty File
```
File content: (empty)
Expected Output:
Reading file 'empty.txt':
===================

File read successfully!
```

### Test Case 3: File Not Found
```
Input: nonexistent.txt
Expected Output:
Error opening file 'nonexistent.txt'!
Possible reasons:
- File does not exist
- No read permissions
- Invalid filename
```

## 🔍 Explanation

1. **File Input**: Get filename from user
2. **File Opening**: Open file in read mode
3. **Error Checking**: Verify file opened successfully
4. **Content Reading**: Read and display file contents
5. **File Closing**: Close file and confirm operation

## 🎯 Key Concepts Covered

- File reading operations
- Error handling
- Character I/O
- File existence checking
- Resource management

## 🚀 Extensions

1. Read line by line
2. Count characters/words/lines
3. Search for specific content
4. Handle binary files