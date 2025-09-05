# 🎯 Practical 160: Copy One File Into Another

## 📋 Problem Statement

Program to copy one file into another.

## 🎯 Learning Objectives

- Understand file copying operations
- Practice reading and writing files
- Learn character-by-character copying
- Understand file handling
- Practice error management

## 📝 Requirements

1. Accept source and destination filenames
2. Open both files
3. Copy content from source to destination
4. Handle file operation errors
5. Display copy status

## 💡 Hints

- Open source file for reading
- Open destination file for writing
- Use fgetc and fputc for copying
- Handle end-of-file condition
- Close both files properly

## 🔧 Solution

```c
// Practical 160: Copy One File Into Another
// Demonstrates file copying operations

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile, *destFile;
    char sourceFilename[100], destFilename[100];
    char ch;
    int charCount = 0;

    printf("Copy One File Into Another\n");
    printf("==========================\n");

    printf("Enter source filename: ");
    scanf("%s", sourceFilename);

    printf("Enter destination filename: ");
    scanf("%s", destFilename);

    // Open source file for reading
    sourceFile = fopen(sourceFilename, "r");

    if (sourceFile == NULL) {
        printf("Error opening source file '%s'!\n", sourceFilename);
        printf("Make sure the file exists and you have read permissions.\n");
        return 1;
    }

    // Open destination file for writing
    destFile = fopen(destFilename, "w");

    if (destFile == NULL) {
        printf("Error opening destination file '%s'!\n", destFilename);
        printf("Check write permissions and available disk space.\n");
        fclose(sourceFile);
        return 1;
    }

    printf("Copying from '%s' to '%s'...\n", sourceFilename, destFilename);

    // Copy character by character
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destFile);
        charCount++;
    }

    // Close both files
    fclose(sourceFile);
    fclose(destFile);

    printf("File copy completed successfully!\n");
    printf("Total characters copied: %d\n", charCount);
    printf("Source file: %s\n", sourceFilename);
    printf("Destination file: %s\n", destFilename);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Copy
```
Source file content: Hello World
This is a test file.
Expected Output:
Copying from 'source.txt' to 'dest.txt'...
File copy completed successfully!
Total characters copied: 28
Source file: source.txt
Destination file: dest.txt
```

### Test Case 2: Empty Source File
```
Source file content: (empty)
Expected Output:
Copying from 'empty.txt' to 'copy.txt'...
File copy completed successfully!
Total characters copied: 0
```

### Test Case 3: Source File Not Found
```
Input: nonexistent.txt to dest.txt
Expected Output:
Error opening source file 'nonexistent.txt'!
Make sure the file exists and you have read permissions.
```

## 🔍 Explanation

1. **File Input**: Get source and destination filenames
2. **Source Opening**: Open source file for reading
3. **Destination Opening**: Open destination file for writing
4. **Copying Process**: Read and write character by character
5. **Statistics**: Count total characters copied

## 🎯 Key Concepts Covered

- File I/O operations
- Character-based copying
- Error handling
- File permissions
- Resource management

## 🚀 Extensions

1. Copy in binary mode
2. Show progress for large files
3. Handle file overwrite confirmation
4. Copy multiple files