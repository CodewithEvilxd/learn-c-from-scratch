# 🎯 Practical 171: Find Number of Lines in Text File

## 📋 Problem Statement

Write a program in C to find the number of lines in a text file.

## 🎯 Learning Objectives

- Understand line counting in files
- Practice file reading operations
- Learn line detection techniques
- Understand file statistics
- Practice counter implementation

## 📝 Requirements

1. Accept filename from user
2. Open file for reading
3. Count lines in file
4. Display line count
5. Handle edge cases

## 💡 Hints

- Use fgets to read lines
- Increment counter for each line
- Handle empty files
- Check for file existence
- Display clear results

## 🔧 Solution

```c
// Practical 171: Find Number of Lines in Text File
// Demonstrates counting lines in a text file

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *filePointer;
    char filename[100];
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    printf("Find Number of Lines in Text File\n");
    printf("==================================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        printf("Make sure the file exists and you have read permissions.\n");
        return 1;
    }

    // Count lines
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        lineCount++;
    }

    // Check for read errors
    if (ferror(filePointer)) {
        printf("Error reading file!\n");
        fclose(filePointer);
        return 1;
    }

    // Close file
    fclose(filePointer);

    // Display results
    printf("\nFile Analysis Results:\n");
    printf("=====================\n");
    printf("Filename: %s\n", filename);
    printf("Number of lines: %d\n", lineCount);

    if (lineCount == 0) {
        printf("Note: File is empty or contains no lines.\n");
    } else if (lineCount == 1) {
        printf("Note: File contains 1 line.\n");
    } else {
        printf("Note: File contains %d lines.\n", lineCount);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multi-line File
```
File content:
Line 1
Line 2
Line 3
Line 4
Expected Output:
Filename: test.txt
Number of lines: 4
Note: File contains 4 lines.
```

### Test Case 2: Single Line File
```
File content: Single line only
Expected Output:
Number of lines: 1
Note: File contains 1 line.
```

### Test Case 3: Empty File
```
File content: (empty)
Expected Output:
Number of lines: 0
Note: File is empty or contains no lines.
```

### Test Case 4: File Not Found
```
Input: nonexistent.txt
Expected Output:
Error opening file 'nonexistent.txt'!
Make sure the file exists and you have read permissions.
```

## 🔍 Explanation

1. **File Opening**: Open file in read mode
2. **Line Counting**: Read lines and increment counter
3. **Error Handling**: Check for file and read errors
4. **Result Display**: Show filename and line count
5. **Edge Cases**: Handle empty files and single lines

## 🎯 Key Concepts Covered

- File reading operations
- Line counting algorithms
- Error handling
- File statistics
- User feedback

## 🚀 Extensions

1. Count words and characters too
2. Find longest/shortest line
3. Display line numbers
4. Handle binary files