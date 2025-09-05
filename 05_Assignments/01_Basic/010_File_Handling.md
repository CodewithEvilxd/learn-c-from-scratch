# 🎯 Assignment 1.10: File Handling in C

## 📋 Problem Statement

Create a C program that demonstrates file operations including reading, writing, appending, and binary file handling. Implement a simple text editor with save, load, and search functionality.

## 🎯 Learning Objectives

- Understand file opening and closing
- Learn text and binary file operations
- Practice file reading and writing
- Implement file search functionality
- Handle file errors properly
- Understand file pointers and positioning

## 📝 Requirements

1. Create a text file and write content to it
2. Read content from a file and display it
3. Append text to an existing file
4. Search for text within a file
5. Copy one file to another
6. Handle file operation errors
7. Work with binary files

## 💡 Hints

- Use `fopen()` to open files with appropriate modes
- Always check if file opened successfully
- Use `fclose()` to close files
- Different modes: "r", "w", "a", "rb", "wb", etc.
- Use `fgets()` for reading lines, `fputs()` for writing
- Handle file not found errors

## 🔧 Solution

```c
// Assignment 1.10: File Handling in C
// Simple text editor with file operations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_FILENAME 100

// Function prototypes
void create_file();
void read_file();
void append_to_file();
void search_in_file();
void copy_file();
void display_menu();
void handle_file_error(const char* operation);

int main() {
    int choice;

    do {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                read_file();
                break;
            case 3:
                append_to_file();
                break;
            case 4:
                search_in_file();
                break;
            case 5:
                copy_file();
                break;
            case 6:
                printf("Thank you for using the file editor!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }

        if (choice != 6) {
            printf("\nPress Enter to continue...");
            getchar();
        }

    } while (choice != 6);

    return 0;
}

void display_menu() {
    printf("\n=== Simple File Editor ===\n");
    printf("1. Create New File\n");
    printf("2. Read File\n");
    printf("3. Append to File\n");
    printf("4. Search in File\n");
    printf("5. Copy File\n");
    printf("6. Exit\n");
    printf("Enter your choice (1-6): ");
}

void create_file() {
    char filename[MAX_FILENAME];
    char content[MAX_LINE_LENGTH];

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "w");
    if (!file) {
        handle_file_error("create");
        return;
    }

    printf("Enter content (press Enter on empty line to finish):\n");

    while (1) {
        fgets(content, sizeof(content), stdin);

        if (strcmp(content, "\n") == 0) {
            break;
        }

        fputs(content, file);
    }

    fclose(file);
    printf("File created successfully!\n");
}

void read_file() {
    char filename[MAX_FILENAME];
    char line[MAX_LINE_LENGTH];

    printf("Enter filename to read: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "r");
    if (!file) {
        handle_file_error("read");
        return;
    }

    printf("\n=== File Content ===\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void append_to_file() {
    char filename[MAX_FILENAME];
    char content[MAX_LINE_LENGTH];

    printf("Enter filename to append to: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "a");
    if (!file) {
        handle_file_error("append to");
        return;
    }

    printf("Enter content to append (press Enter on empty line to finish):\n");

    while (1) {
        fgets(content, sizeof(content), stdin);

        if (strcmp(content, "\n") == 0) {
            break;
        }

        fputs(content, file);
    }

    fclose(file);
    printf("Content appended successfully!\n");
}

void search_in_file() {
    char filename[MAX_FILENAME];
    char search_term[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int found = 0;

    printf("Enter filename to search in: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    printf("Enter text to search: ");
    fgets(search_term, sizeof(search_term), stdin);
    search_term[strcspn(search_term, "\n")] = '\0';

    FILE* file = fopen(filename, "r");
    if (!file) {
        handle_file_error("search in");
        return;
    }

    printf("\n=== Search Results ===\n");

    while (fgets(line, sizeof(line), file)) {
        line_number++;

        if (strstr(line, search_term)) {
            printf("Line %d: %s", line_number, line);
            found = 1;
        }
    }

    if (!found) {
        printf("Text '%s' not found in file.\n", search_term);
    }

    fclose(file);
}

void copy_file() {
    char source_filename[MAX_FILENAME];
    char dest_filename[MAX_FILENAME];
    char buffer[MAX_LINE_LENGTH];

    printf("Enter source filename: ");
    fgets(source_filename, sizeof(source_filename), stdin);
    source_filename[strcspn(source_filename, "\n")] = '\0';

    printf("Enter destination filename: ");
    fgets(dest_filename, sizeof(dest_filename), stdin);
    dest_filename[strcspn(dest_filename, "\n")] = '\0';

    FILE* source_file = fopen(source_filename, "r");
    if (!source_file) {
        handle_file_error("open source");
        return;
    }

    FILE* dest_file = fopen(dest_filename, "w");
    if (!dest_file) {
        handle_file_error("create destination");
        fclose(source_file);
        return;
    }

    while (fgets(buffer, sizeof(buffer), source_file)) {
        fputs(buffer, dest_file);
    }

    fclose(source_file);
    fclose(dest_file);

    printf("File copied successfully!\n");
}

void handle_file_error(const char* operation) {
    printf("Error: Could not %s file.\n", operation);
    printf("Possible reasons:\n");
    printf("- File does not exist\n");
    printf("- Permission denied\n");
    printf("- Invalid filename\n");
}
```

## 📊 Test Cases

### Test Case 1: Create File
```
Input:
Filename: test.txt
Content: Hello, World!
This is a test file.

Expected Output: File created successfully!
```

### Test Case 2: Read File
```
Input: test.txt
Expected Output:
=== File Content ===
Hello, World!
This is a test file.
```

### Test Case 3: Search in File
```
Input:
Filename: test.txt
Search term: World
Expected Output:
Line 1: Hello, World!
```

### Test Case 4: Copy File
```
Input:
Source: test.txt
Destination: copy.txt
Expected Output: File copied successfully!
```

## 🔍 Explanation

1. **File Opening**: `fopen()` with different modes ("r", "w", "a")
2. **File Reading**: `fgets()` for reading lines
3. **File Writing**: `fputs()` for writing strings
4. **File Closing**: `fclose()` to release resources
5. **Error Handling**: Check return values for file operations
6. **String Operations**: Using `strstr()` for searching

## 🎯 Key Concepts Covered

- File opening and closing
- Text file operations (read/write/append)
- File error handling
- String searching in files
- File copying operations
- User input validation

## 🚀 Extensions

1. Add line numbering when displaying files
2. Implement find and replace functionality
3. Add binary file operations
4. Create a simple file encryption/decryption feature