# 🎯 Practical 169: Write Multiple Lines to Text File

## 📋 Problem Statement

Write a program in C to write multiple lines to a text file.

## 🎯 Learning Objectives

- Understand multi-line file writing
- Practice loop-based input
- Learn line termination handling
- Understand file append operations
- Practice user interaction

## 📝 Requirements

1. Accept filename from user
2. Accept multiple lines of text
3. Write each line to file
4. Handle line termination
5. Display success message

## 💡 Hints

- Use loop for multiple inputs
- Use fgets for line input
- Handle newline characters
- Use fprintf for writing
- Allow user to stop input

## 🔧 Solution

```c
// Practical 169: Write Multiple Lines to Text File
// Demonstrates writing multiple lines to a text file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *filePointer;
    char filename[100];
    char line[MAX_LINE_LENGTH];
    char choice;

    printf("Write Multiple Lines to Text File\n");
    printf("=================================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Clear input buffer
    getchar();

    // Open file for writing
    filePointer = fopen(filename, "w");

    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter text lines (press Enter after each line):\n");
    printf("Enter 'END' on a new line to finish.\n\n");

    while (1) {
        printf("Line: ");
        fgets(line, sizeof(line), stdin);

        // Remove newline character
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Check for end marker
        if (strcmp(line, "END") == 0) {
            break;
        }

        // Write line to file
        fprintf(filePointer, "%s\n", line);
    }

    // Close file
    fclose(filePointer);

    printf("\nMultiple lines written to '%s' successfully!\n", filename);

    // Optional: Display file contents
    printf("\nDo you want to view the file contents? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        filePointer = fopen(filename, "r");
        if (filePointer != NULL) {
            printf("\nFile contents:\n");
            printf("==============\n");
            while (fgets(line, sizeof(line), filePointer) != NULL) {
                printf("%s", line);
            }
            fclose(filePointer);
        }
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multiple Lines Input
```
Input: filename: multiline.txt
Lines: Hello World
This is line 2
Third line here
END
Expected Output:
Multiple lines written to 'multiline.txt' successfully!
```

### Test Case 2: Single Line
```
Input: filename: single.txt
Lines: Only one line
END
Expected Output:
Multiple lines written to 'single.txt' successfully!
```

## 🔍 Explanation

1. **File Setup**: Get filename and open file
2. **Input Loop**: Accept multiple lines from user
3. **End Detection**: Check for END marker to stop
4. **Line Writing**: Write each line to file with newline
5. **File Display**: Optional content verification

## 🎯 Key Concepts Covered

- Multi-line file writing
- Loop-based input handling
- String comparison
- File operations
- User interaction

## 🚀 Extensions

1. Append to existing file
2. Number lines automatically
3. Handle empty lines
4. Add line editing features