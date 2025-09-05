# 🎯 Practical 177: Copy Contents of One File to Another File

## 📋 Problem Statement

C Program to copy contents of one file to another file.

## 🎯 Learning Objectives

- Understand file copying
- Practice file I/O operations
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
- Close both files

## 🔧 Solution

```c
// Practical 177: Copy Contents of One File to Another File
// Demonstrates file copying operations

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile, *destFile;
    char sourceFilename[100], destFilename[100];
    char ch;

    printf("Copy Contents of One File to Another File\n");
    printf("=========================================\n");

    printf("Enter source filename: ");
    scanf("%s", sourceFilename);

    printf("Enter destination filename: ");
    scanf("%s", destFilename);

    // Open source file for reading
    sourceFile = fopen(sourceFilename, "r");

    if (sourceFile == NULL) {
        printf("Error opening source file '%s'!\n", sourceFilename);
        return 1;
    }

    // Open destination file for writing
    destFile = fopen(destFilename, "w");

    if (destFile == NULL) {
        printf("Error opening destination file '%s'!\n", destFilename);
        fclose(sourceFile);
        return 1;
    }

    // Copy character by character
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destFile);

    printf("File copy completed successfully!\n");
    printf("Source: %s\n", sourceFilename);
    printf("Destination: %s\n", destFilename);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Copy
```
Source content: Hello World
Expected Output:
File copy completed successfully!
Source: source.txt
Destination: dest.txt
```

### Test Case 2: Empty Source
```
Source content: (empty)
Expected Output:
File copy completed successfully!
```

## 🔍 Explanation

1. **File Input**: Get source and destination filenames
2. **Source Opening**: Open source file for reading
3. **Destination Opening**: Open destination file for writing
4. **Copying Process**: Read and write character by character
5. **File Closing**: Close both files

## 🎯 Key Concepts Covered

- File I/O operations
- Character-based copying
- Error handling
- File permissions

## 🚀 Extensions

1. Copy in binary mode
2. Show progress for large files
3. Handle file overwrite confirmation
4. Copy multiple files