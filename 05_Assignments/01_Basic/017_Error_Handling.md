# 🎯 Assignment 1.17: Error Handling in C

## 📋 Problem Statement

Create a C program that demonstrates various error handling techniques including return codes, errno, perror, strerror, and custom error handling. Implement a robust file processing system with comprehensive error checking.

## 🎯 Learning Objectives

- Understand error handling mechanisms in C
- Learn errno and system error codes
- Practice perror and strerror functions
- Implement custom error handling
- Handle file operation errors
- Create robust error recovery

## 📝 Requirements

1. Demonstrate different error handling methods
2. Use errno for system call errors
3. Implement perror and strerror
4. Create custom error codes and messages
5. Handle file operation errors
6. Implement error recovery mechanisms
7. Log errors appropriately

## 💡 Hints

- Check return values of system calls
- Use errno with perror/strerror
- Define custom error codes as enums
- Implement error logging functions
- Handle errors gracefully without crashing
- Provide meaningful error messages

## 🔧 Solution

```c
// Assignment 1.17: Error Handling in C
// Comprehensive error handling techniques

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

// Custom error codes
typedef enum {
    SUCCESS = 0,
    ERR_FILE_NOT_FOUND = 1,
    ERR_PERMISSION_DENIED = 2,
    ERR_INVALID_INPUT = 3,
    ERR_MEMORY_ALLOCATION = 4,
    ERR_FILE_OPERATION = 5,
    ERR_UNKNOWN = 99
} ErrorCode;

// Error message structure
typedef struct {
    ErrorCode code;
    const char* message;
} ErrorInfo;

// Error lookup table
static const ErrorInfo error_table[] = {
    {SUCCESS, "Operation completed successfully"},
    {ERR_FILE_NOT_FOUND, "File not found"},
    {ERR_PERMISSION_DENIED, "Permission denied"},
    {ERR_INVALID_INPUT, "Invalid input provided"},
    {ERR_MEMORY_ALLOCATION, "Memory allocation failed"},
    {ERR_FILE_OPERATION, "File operation failed"},
    {ERR_UNKNOWN, "Unknown error occurred"}
};

#define ERROR_TABLE_SIZE (sizeof(error_table) / sizeof(error_table[0]))

// Function prototypes
const char* get_error_message(ErrorCode code);
void log_error(const char* function, ErrorCode code, const char* details);
ErrorCode process_file(const char* filename);
ErrorCode validate_input(const char* input);
ErrorCode allocate_memory(size_t size, void** ptr);
void demonstrate_system_errors();
void demonstrate_custom_errors();
void demonstrate_file_errors();

// Error logging function
void log_error(const char* function, ErrorCode code, const char* details) {
    fprintf(stderr, "[ERROR] %s: %s", function, get_error_message(code));
    if (details) {
        fprintf(stderr, " (%s)", details);
    }

    // Add errno information for system errors
    if (errno != 0) {
        fprintf(stderr, " - System error: %s", strerror(errno));
    }

    fprintf(stderr, "\n");
}

const char* get_error_message(ErrorCode code) {
    for (size_t i = 0; i < ERROR_TABLE_SIZE; i++) {
        if (error_table[i].code == code) {
            return error_table[i].message;
        }
    }
    return "Unknown error";
}

ErrorCode process_file(const char* filename) {
    if (!filename) {
        return ERR_INVALID_INPUT;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        if (errno == ENOENT) {
            return ERR_FILE_NOT_FOUND;
        } else if (errno == EACCES) {
            return ERR_PERMISSION_DENIED;
        } else {
            return ERR_FILE_OPERATION;
        }
    }

    // Simulate file processing
    char buffer[1024];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);

    if (ferror(file)) {
        fclose(file);
        return ERR_FILE_OPERATION;
    }

    printf("Successfully read %zu bytes from %s\n", bytes_read, filename);
    fclose(file);

    return SUCCESS;
}

ErrorCode validate_input(const char* input) {
    if (!input) {
        return ERR_INVALID_INPUT;
    }

    if (strlen(input) == 0) {
        return ERR_INVALID_INPUT;
    }

    // Check for invalid characters
    for (size_t i = 0; input[i]; i++) {
        if (!isalnum(input[i]) && input[i] != '_' && input[i] != '-') {
            return ERR_INVALID_INPUT;
        }
    }

    return SUCCESS;
}

ErrorCode allocate_memory(size_t size, void** ptr) {
    *ptr = malloc(size);
    if (!*ptr) {
        return ERR_MEMORY_ALLOCATION;
    }
    return SUCCESS;
}

void demonstrate_system_errors() {
    printf("1. System Error Handling\n");

    // Try to open non-existent file
    FILE* file = fopen("nonexistent_file.txt", "r");
    if (!file) {
        printf("System error demonstration:\n");
        printf("errno: %d\n", errno);
        perror("fopen failed");
        printf("Error message: %s\n", strerror(errno));
    }

    // Try invalid memory allocation
    void* ptr = malloc(SIZE_MAX);
    if (!ptr) {
        printf("Memory allocation error:\n");
        printf("errno: %d\n", errno);
        perror("malloc failed");
    }

    printf("\n");
}

void demonstrate_custom_errors() {
    printf("2. Custom Error Handling\n");

    // Test input validation
    const char* test_inputs[] = {NULL, "", "valid_name", "invalid@name"};
    const char* test_names[] = {"NULL input", "Empty string", "Valid name", "Invalid characters"};

    for (int i = 0; i < 4; i++) {
        ErrorCode result = validate_input(test_inputs[i]);
        if (result != SUCCESS) {
            log_error("validate_input", result, test_names[i]);
        } else {
            printf("Input validation passed: %s\n", test_names[i]);
        }
    }

    // Test memory allocation
    void* ptr;
    ErrorCode mem_result = allocate_memory(1024 * 1024 * 1024, &ptr);  // Try to allocate 1GB
    if (mem_result != SUCCESS) {
        log_error("allocate_memory", mem_result, "1GB allocation");
    } else {
        printf("Memory allocation successful\n");
        free(ptr);
    }

    printf("\n");
}

void demonstrate_file_errors() {
    printf("3. File Operation Error Handling\n");

    const char* test_files[] = {
        "existing_file.txt",
        "nonexistent_file.txt",
        "/root/protected_file.txt"  // May require permissions
    };

    // Create a test file first
    FILE* test_file = fopen("existing_file.txt", "w");
    if (test_file) {
        fprintf(test_file, "This is a test file for error handling demonstration.\n");
        fclose(test_file);
    }

    for (int i = 0; i < 3; i++) {
        ErrorCode result = process_file(test_files[i]);
        if (result != SUCCESS) {
            log_error("process_file", result, test_files[i]);
        }
    }

    // Clean up
    remove("existing_file.txt");

    printf("\n");
}

int main() {
    printf("=== Error Handling in C Demonstration ===\n\n");

    demonstrate_system_errors();
    demonstrate_custom_errors();
    demonstrate_file_errors();

    printf("Error handling demonstration complete!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: System Errors
```
Expected Output:
System error demonstration:
errno: 2
fopen failed: No such file or directory
Error message: No such file or directory
```

### Test Case 2: Custom Errors
```
Expected Output:
[ERROR] validate_input: Invalid input provided (NULL input)
[ERROR] validate_input: Invalid input provided (Empty string)
Input validation passed: Valid name
[ERROR] validate_input: Invalid input provided (Invalid characters)
```

### Test Case 3: File Errors
```
Expected Output:
Successfully read 58 bytes from existing_file.txt
[ERROR] process_file: File not found (nonexistent_file.txt)
[ERROR] process_file: Permission denied (/root/protected_file.txt)
```

## 🔍 Explanation

1. **errno**: Global variable set by system calls
2. **perror()**: Prints error message with system error
3. **strerror()**: Converts errno to readable string
4. **Custom Error Codes**: Enum for application-specific errors
5. **Error Lookup Table**: Maps error codes to messages
6. **Error Logging**: Centralized error reporting function

## 🎯 Key Concepts Covered

- System error handling with errno
- perror and strerror functions
- Custom error codes and messages
- Error logging and reporting
- File operation error handling
- Memory allocation error handling

## 🚀 Extensions

1. Add error recovery mechanisms
2. Implement error callback functions
3. Create error context information
4. Add error statistics and reporting