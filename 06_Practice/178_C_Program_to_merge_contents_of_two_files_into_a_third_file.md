# 🎯 Practical 178: Merge Contents of Two Files into a Third File

## 📋 Problem Statement

C Program to merge contents of two files into a third file.

## 🎯 Learning Objectives

- Understand file merging operations
- Practice multiple file handling
- Learn sequential file operations
- Understand file concatenation
- Practice error management

## 📝 Requirements

1. Accept two source filenames and one destination
2. Open all three files
3. Copy first file content to destination
4. Append second file content to destination
5. Handle file operation errors

## 💡 Hints

- Open first source file for reading
- Open destination file for writing
- Copy first file content
- Open second source file for reading
- Append second file content
- Close all files properly

## 🔧 Solution

```c
// Practical 178: Merge Contents of Two Files into a Third File
// Demonstrates merging two files into one

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file1, *file2, *destFile;
    char filename1[100], filename2[100], destFilename[100];
    char ch;

    printf("Merge Contents of Two Files into a Third File\n");
    printf("=============================================\n");

    printf("Enter first source filename: ");
    scanf("%s", filename1);

    printf("Enter second source filename: ");
    scanf("%s", filename2);

    printf("Enter destination filename: ");
    scanf("%s", destFilename);

    // Open first source file
    file1 = fopen(filename1, "r");
    if (file1 == NULL) {
        printf("Error opening first source file '%s'!\n", filename1);
        return 1;
    }

    // Open destination file
    destFile = fopen(destFilename, "w");
    if (destFile == NULL) {
        printf("Error opening destination file '%s'!\n", destFilename);
        fclose(file1);
        return 1;
    }

    // Copy first file to destination
    printf("Copying '%s' to '%s'...\n", filename1, destFilename);
    while ((ch = fgetc(file1)) != EOF) {
        fputc(ch, destFile);
    }
    fclose(file1);

    // Open second source file
    file2 = fopen(filename2, "r");
    if (file2 == NULL) {
        printf("Error opening second source file '%s'!\n", filename2);
        fclose(destFile);
        return 1;
    }

    // Append second file to destination
    printf("Appending '%s' to '%s'...\n", filename2, destFilename);
    while ((ch = fgetc(file2)) != EOF) {
        fputc(ch, destFile);
    }
    fclose(file2);
    fclose(destFile);

    printf("File merge completed successfully!\n");
    printf("Merged files: %s + %s\n", filename1, filename2);
    printf("Result file: %s\n", destFilename);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Merge
```
File1: Hello
File2: World
Expected Output:
File merge completed successfully!
Merged files: file1.txt + file2.txt
Result file: merged.txt
```

### Test Case 2: One Empty File
```
File1: Content
File2: (empty)
Expected Output:
File merge completed successfully!
```

## 🔍 Explanation

1. **File Input**: Get source and destination filenames
2. **First File**: Open and copy first source to destination
3. **Second File**: Open and append second source to destination
4. **File Management**: Close all files properly
5. **Status Display**: Show merge completion

## 🎯 Key Concepts Covered

- Multiple file operations
- File concatenation
- Sequential file processing
- Error handling
- File management

## 🚀 Extensions

1. Merge more than two files
2. Add separator between files
3. Handle binary files
4. Show merge progress