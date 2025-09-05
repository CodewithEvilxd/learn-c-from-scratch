# 🎯 Practical 175: Count Number of Lines in a File

## 📋 Problem Statement

C Program to count number of lines in a file.

## 🎯 Learning Objectives

- Understand basic file reading
- Practice line counting
- Learn file handling
- Understand end-of-file detection
- Practice counter implementation

## 📝 Requirements

1. Accept filename from user
2. Open file for reading
3. Count lines in file
4. Display line count
5. Handle file errors

## 💡 Hints

- Use fgets to read lines
- Increment counter for each line
- Handle file opening errors
- Close file properly
- Display clear results

## 🔧 Solution

```c
// Practical 175: Count Number of Lines in a File
// Demonstrates basic line counting in files

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *filePointer;
    char filename[100];
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    printf("Count Number of Lines in a File\n");
    printf("================================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        return 1;
    }

    // Count lines
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        lineCount++;
    }

    // Close file
    fclose(filePointer);

    // Display result
    printf("Number of lines in '%s': %d\n", filename, lineCount);

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
Expected Output:
Number of lines in 'test.txt': 3
```

### Test Case 2: Single Line
```
File content: Single line
Expected Output:
Number of lines in 'test.txt': 1
```

### Test Case 3: Empty File
```
File content: (empty)
Expected Output:
Number of lines in 'test.txt': 0
```

## 🔍 Explanation

1. **File Opening**: Open file in read mode
2. **Line Counting**: Read lines and increment counter
3. **File Closing**: Close file after reading
4. **Result Display**: Show filename and line count

## 🎯 Key Concepts Covered

- File reading operations
- Line counting
- Error handling
- File management

## 🚀 Extensions

1. Count words and characters too
2. Find longest line
3. Display line numbers
4. Handle large files