# 🎯 Practical 159: Create a File Using Command Line Argument

## 📋 Problem Statement

Program to create a file using command line argument.

## 🎯 Learning Objectives

- Understand command line arguments
- Practice main function parameters
- Learn file creation via command line
- Understand argument validation
- Practice error handling

## 📝 Requirements

1. Accept filename via command line
2. Create file with given name
3. Handle invalid arguments
4. Display success message
5. Show usage instructions

## 💡 Hints

- Use main(int argc, char *argv[])
- Check argc for argument count
- Use argv[1] for filename
- Create file using fopen
- Handle file creation errors

## 🔧 Solution

```c
// Practical 159: Create a File Using Command Line Argument
// Demonstrates file creation using command line arguments

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *filePointer;

    printf("Create a File Using Command Line Argument\n");
    printf("==========================================\n");

    // Check if filename is provided
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        printf("Example: %s myfile.txt\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    printf("Creating file: %s\n", filename);

    // Create file for writing
    filePointer = fopen(filename, "w");

    if (filePointer == NULL) {
        printf("Error creating file!\n");
        printf("Possible reasons:\n");
        printf("- Invalid filename\n");
        printf("- No write permissions\n");
        printf("- Disk full\n");
        return 1;
    }

    // Write some initial content
    fprintf(filePointer, "File created using command line argument.\n");
    fprintf(filePointer, "Filename: %s\n", filename);

    // Close file
    fclose(filePointer);

    printf("File '%s' created successfully!\n", filename);
    printf("Initial content has been written to the file.\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Creation
```
Command: ./program myfile.txt
Expected Output:
Creating file: myfile.txt
File 'myfile.txt' created successfully!
Initial content has been written to the file.
```

### Test Case 2: No Arguments
```
Command: ./program
Expected Output:
Usage: ./program <filename>
Example: ./program myfile.txt
```

### Test Case 3: Multiple Arguments
```
Command: ./program file1.txt file2.txt
Expected Output:
Usage: ./program <filename>
Example: ./program myfile.txt
```

## 🔍 Explanation

1. **Argument Check**: Validate command line arguments
2. **Usage Display**: Show proper usage if arguments invalid
3. **File Creation**: Create file using fopen
4. **Error Handling**: Handle file creation failures
5. **Content Writing**: Write initial content to file

## 🎯 Key Concepts Covered

- Command line arguments
- main function parameters
- File creation
- Error handling
- Argument validation

## 🚀 Extensions

1. Accept multiple filenames
2. Create files with specific content
3. Handle file overwrite confirmation
4. Create files in specific directories