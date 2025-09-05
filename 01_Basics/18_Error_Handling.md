# 🚨 Lesson 18: Error Handling in C
## Building Robust and Reliable Programs

---

## 🎯 Learning Objectives

- Master error handling techniques in C
- Understand errno and error reporting
- Learn assertion and debugging methods
- Handle signals and exceptions
- Implement custom error handling systems

---

## 📖 Error Handling Kya Hai?

**Error handling** in C runtime errors ko detect, report, aur recover karna hai. Built-in exception handling wale languages ke unlike, C mein explicit error checking aur handling required hai.

### **Types of Errors**
1. **Compile-time Errors**: Syntax errors, type mismatches
2. **Link-time Errors**: Missing functions, libraries
3. **Runtime Errors**: Division by zero, null pointer access
4. **Logical Errors**: Incorrect algorithm implementation
5. **Resource Errors**: Memory leaks, file handle leaks
6. **Concurrency Errors**: Race conditions, deadlocks
7. **Security Errors**: Buffer overflows, injection attacks

---

## 🔧 errno and perror()

### **1. errno Global Variable**
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        printf("errno value: %d\n", errno);
        printf("Error message: %s\n", strerror(errno));
    } else {
        fclose(file);
    }

    return 0;
}
```

### **2. perror() Function**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        // Equivalent to: fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    } else {
        fclose(file);
    }

    return 0;
}
```

### **3. Common errno Values**
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void demonstrate_errno_values() {
    // ENOENT - No such file or directory
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL && errno == ENOENT) {
        perror("File not found");
    }

    // EINVAL - Invalid argument
    int *ptr = (int*)malloc(-1);  // Invalid size
    if (ptr == NULL) {
        perror("Memory allocation failed");
    }

    // ERANGE - Result too large
    // Demonstrated in mathematical operations
}

int main() {
    demonstrate_errno_values();
    return 0;
}
```

---

## 🐛 Assertions and Debugging

### **1. assert() Macro**
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int divide(int a, int b) {
    assert(b != 0 && "Division by zero!");
    return a / b;
}

void process_array(int arr[], int size) {
    assert(arr != NULL && "Array cannot be NULL");
    assert(size > 0 && "Array size must be positive");

    for (int i = 0; i < size; i++) {
        assert(arr[i] >= 0 && "Array elements must be non-negative");
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Normal operation
    printf("Division result: %d\n", divide(10, 2));

    // This will trigger assertion
    // printf("Division result: %d\n", divide(10, 0));

    int arr[] = {1, 2, 3, 4, 5};
    process_array(arr, 5);

    return 0;
}
```

### **2. Custom Assertion Function**
```c
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

void custom_assert(int condition, const char *message, const char *file, int line) {
    if (!condition) {
        fprintf(stderr, "Assertion failed: %s\n", message);
        fprintf(stderr, "File: %s, Line: %d\n", file, line);
        exit(1);
    }
}

#define ASSERT(condition, message) \
    custom_assert(condition, message, __FILE__, __LINE__)

int divide(int a, int b) {
    ASSERT(b != 0, "Division by zero");
    return a / b;
}

int main() {
    printf("Result: %d\n", divide(10, 2));
    // printf("Result: %d\n", divide(10, 0));  // Will trigger custom assertion

    return 0;
}
```

### **3. NDEBUG Macro**
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// When NDEBUG is defined, assertions are disabled
// #define NDEBUG

int main() {
    int x = 5;
    assert(x > 0);  // Enabled in debug mode, disabled in release

    printf("Program continues...\n");

    return 0;
}
```

### **4. Static Assertions (C11)**
```c
#include <stdio.h>
#include <assert.h>

// Compile-time assertions
#define STATIC_ASSERT(condition, message) _Static_assert(condition, message)

int main() {
    // Check array size at compile time
    STATIC_ASSERT(sizeof(int) == 4, "int must be 4 bytes");

    // Check structure size
    struct Test {
        int a;
        char b;
    };
    STATIC_ASSERT(sizeof(struct Test) <= 8, "Structure too large");

    printf("All static assertions passed!\n");
    return 0;
}
```

### **5. Defensive Programming Techniques**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Safe string copy with bounds checking
char* safe_strncpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return NULL;
    }

    size_t src_len = strlen(src);
    size_t copy_len = (src_len < dest_size - 1) ? src_len : dest_size - 1;

    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';

    return dest;
}

// Safe arithmetic operations
int safe_add(int a, int b) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        // Overflow would occur
        errno = ERANGE;
        return 0;
    }
    return a + b;
}

int safe_multiply(int a, int b) {
    if (a != 0 && b != 0) {
        if (a > INT_MAX / b || a < INT_MIN / b) {
            errno = ERANGE;
            return 0;
        }
    }
    return a * b;
}

// Bounds checking for array access
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int safe_array_access(int *arr, size_t size, size_t index) {
    if (arr == NULL) {
        errno = EINVAL;
        return 0;
    }

    if (index >= size) {
        errno = ERANGE;
        return 0;
    }

    return arr[index];
}

// Input validation
int validate_user_input(const char *input, size_t max_len) {
    if (input == NULL) {
        return 0;
    }

    size_t len = strlen(input);
    if (len == 0 || len > max_len) {
        return 0;
    }

    // Check for potentially dangerous characters
    for (size_t i = 0; i < len; i++) {
        if (!isalnum(input[i]) && input[i] != '_' && input[i] != '-') {
            return 0;
        }
    }

    return 1;
}

int main() {
    // Safe string operations
    char buffer[10];
    const char *source = "Hello World!";
    safe_strncpy(buffer, source, sizeof(buffer));
    printf("Safe copy: %s\n", buffer);

    // Safe arithmetic
    int result = safe_add(1000000000, 1000000000);
    if (errno == ERANGE) {
        printf("Addition overflow detected!\n");
    }

    // Array bounds checking
    int arr[] = {1, 2, 3, 4, 5};
    size_t arr_size = ARRAY_SIZE(arr);

    int value = safe_array_access(arr, arr_size, 10);  // Out of bounds
    if (errno == ERANGE) {
        printf("Array access out of bounds!\n");
    }

    // Input validation
    const char *user_input = "valid_input_123";
    if (validate_user_input(user_input, 20)) {
        printf("Input is valid: %s\n", user_input);
    }

    return 0;
}
```

---

## 📡 Signal Handling

### **1. Basic Signal Handling**
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signal_number) {
    printf("\nReceived signal: %d\n", signal_number);

    switch (signal_number) {
        case SIGINT:
            printf("Interrupt signal (Ctrl+C) received\n");
            break;
        case SIGTERM:
            printf("Termination signal received\n");
            break;
        case SIGSEGV:
            printf("Segmentation fault occurred\n");
            break;
        default:
            printf("Unknown signal received\n");
    }

    exit(0);
}

int main() {
    // Register signal handlers
    signal(SIGINT, signal_handler);   // Ctrl+C
    signal(SIGTERM, signal_handler);  // Termination
    signal(SIGSEGV, signal_handler);  // Segmentation fault

    printf("Program running... Press Ctrl+C to exit\n");

    // Infinite loop to keep program running
    while (1) {
        // Do some work
    }

    return 0;
}
```

### **2. Advanced Signal Handling**
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t signal_received = 0;

void signal_handler(int signal_number) {
    signal_received = signal_number;
}

void cleanup_resources() {
    printf("Cleaning up resources...\n");
    // Close files, free memory, etc.
}

int main() {
    // Ignore SIGPIPE (useful for network programs)
    signal(SIGPIPE, SIG_IGN);

    // Handle SIGINT gracefully
    signal(SIGINT, signal_handler);

    printf("Program running... Press Ctrl+C to exit gracefully\n");

    while (!signal_received) {
        printf("Working...\n");
        sleep(1);
    }

    printf("Signal %d received, exiting gracefully\n", signal_received);
    cleanup_resources();

    return 0;
}
```

### **3. Signal Masking**
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    sigset_t mask;

    // Initialize signal set
    sigemptyset(&mask);

    // Add signals to mask
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);

    // Block signals
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("sigprocmask");
        return 1;
    }

    printf("Signals blocked for 10 seconds...\n");

    // Do critical work here
    sleep(10);

    // Unblock signals
    if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1) {
        perror("sigprocmask");
        return 1;
    }

    printf("Signals unblocked\n");

    return 0;
}
```

---

## 🛑 setjmp/longjmp (Non-local Jumps)

### **1. Basic setjmp/longjmp**
```c
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf jump_buffer;

void function_that_might_fail() {
    static int attempt = 0;
    attempt++;

    if (attempt < 3) {
        printf("Attempt %d failed, trying again...\n", attempt);
        longjmp(jump_buffer, attempt);  // Jump back to setjmp
    } else {
        printf("All attempts failed\n");
        longjmp(jump_buffer, -1);  // Error condition
    }
}

int main() {
    int result = setjmp(jump_buffer);

    if (result == 0) {
        printf("Starting operation...\n");
        function_that_might_fail();
    } else if (result > 0) {
        printf("Recovered from attempt %d\n", result);
        // Try alternative approach
        printf("Using alternative method...\n");
    } else {
        printf("Operation completely failed\n");
        return 1;
    }

    printf("Operation completed successfully\n");
    return 0;
}
```

### **2. Exception-like Error Handling**
```c
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define TRY do { jmp_buf exception_buffer; if (setjmp(exception_buffer) == 0) {
#define CATCH } else {
#define END_TRY } } while(0)
#define THROW longjmp(exception_buffer, 1)

jmp_buf exception_buffer;

void risky_operation() {
    printf("Performing risky operation...\n");

    // Simulate an error condition
    if (rand() % 2 == 0) {
        printf("Error occurred!\n");
        THROW;
    }

    printf("Operation completed successfully\n");
}

int main() {
    TRY {
        risky_operation();
        printf("No errors occurred\n");
    } CATCH {
        printf("Exception caught! Cleaning up...\n");
        // Error recovery code
    } END_TRY;

    return 0;
}
```

---

## 🛠️ Custom Error Handling Systems

### **1. Error Code System**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SUCCESS = 0,
    ERROR_FILE_NOT_FOUND = 1,
    ERROR_PERMISSION_DENIED = 2,
    ERROR_OUT_OF_MEMORY = 3,
    ERROR_INVALID_ARGUMENT = 4,
    ERROR_IO_ERROR = 5
} ErrorCode;

const char* error_messages[] = {
    "Success",
    "File not found",
    "Permission denied",
    "Out of memory",
    "Invalid argument",
    "I/O error"
};

typedef struct {
    ErrorCode code;
    char message[256];
} Error;

Error create_error(ErrorCode code, const char *message) {
    Error error;
    error.code = code;
    strncpy(error.message, message, sizeof(error.message) - 1);
    error.message[sizeof(error.message) - 1] = '\0';
    return error;
}

void print_error(Error error) {
    fprintf(stderr, "Error %d: %s\n", error.code, error.message);
    if (error.code > 0 && error.code < sizeof(error_messages) / sizeof(error_messages[0])) {
        fprintf(stderr, "Description: %s\n", error_messages[error.code]);
    }
}

Error read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        if (errno == ENOENT) {
            return create_error(ERROR_FILE_NOT_FOUND, "File does not exist");
        } else if (errno == EACCES) {
            return create_error(ERROR_PERMISSION_DENIED, "Permission denied");
        } else {
            return create_error(ERROR_IO_ERROR, strerror(errno));
        }
    }

    // Read file contents
    char buffer[1024];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    if (bytes_read == 0 && !feof(file)) {
        return create_error(ERROR_IO_ERROR, "Failed to read file");
    }

    return create_error(SUCCESS, "File read successfully");
}

int main() {
    Error result = read_file("nonexistent.txt");
    if (result.code != SUCCESS) {
        print_error(result);
        return 1;
    }

    printf("File processed successfully\n");
    return 0;
}
```

### **2. Error Context System**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ErrorContext {
    int code;
    char message[256];
    char file[64];
    int line;
    struct ErrorContext *next;
} ErrorContext;

ErrorContext* error_stack = NULL;

void push_error(int code, const char *message, const char *file, int line) {
    ErrorContext *error = (ErrorContext*)malloc(sizeof(ErrorContext));
    if (error == NULL) return;

    error->code = code;
    strncpy(error->message, message, sizeof(error->message) - 1);
    strncpy(error->file, file, sizeof(error->file) - 1);
    error->line = line;
    error->next = error_stack;
    error_stack = error;
}

void print_error_stack() {
    ErrorContext *current = error_stack;
    while (current != NULL) {
        fprintf(stderr, "Error %d at %s:%d: %s\n",
                current->code, current->file, current->line, current->message);
        current = current->next;
    }
}

void clear_error_stack() {
    while (error_stack != NULL) {
        ErrorContext *temp = error_stack;
        error_stack = error_stack->next;
        free(temp);
    }
}

#define LOG_ERROR(code, message) push_error(code, message, __FILE__, __LINE__)

int divide(int a, int b) {
    if (b == 0) {
        LOG_ERROR(1, "Division by zero");
        return 0;
    }
    return a / b;
}

FILE* safe_fopen(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Failed to open file: %s", filename);
        LOG_ERROR(2, error_msg);
    }
    return file;
}

int main() {
    int result = divide(10, 0);
    if (error_stack != NULL) {
        printf("Errors occurred:\n");
        print_error_stack();
    }

    FILE *file = safe_fopen("nonexistent.txt", "r");
    if (error_stack != NULL) {
        printf("\nAll errors:\n");
        print_error_stack();
    }

    clear_error_stack();
    return 0;
}
```

### **3. Advanced Logging System**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
} LogLevel;

typedef struct {
    FILE *file;
    LogLevel level;
    int include_timestamp;
    int include_level;
    char filename[256];
} Logger;

const char* level_names[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "CRITICAL"
};

Logger* create_logger(const char *filename, LogLevel level) {
    Logger *logger = (Logger*)malloc(sizeof(Logger));
    if (logger == NULL) return NULL;

    if (filename != NULL) {
        logger->file = fopen(filename, "a");
        if (logger->file == NULL) {
            free(logger);
            return NULL;
        }
        strncpy(logger->filename, filename, sizeof(logger->filename) - 1);
    } else {
        logger->file = stderr;
        strcpy(logger->filename, "stderr");
    }

    logger->level = level;
    logger->include_timestamp = 1;
    logger->include_level = 1;

    return logger;
}

void destroy_logger(Logger *logger) {
    if (logger == NULL) return;

    if (logger->file != stderr && logger->file != stdout) {
        fclose(logger->file);
    }
    free(logger);
}

void log_message(Logger *logger, LogLevel level, const char *format, ...) {
    if (logger == NULL || level < logger->level) return;

    // Timestamp
    if (logger->include_timestamp) {
        time_t now = time(NULL);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
        fprintf(logger->file, "[%s] ", timestamp);
    }

    // Level
    if (logger->include_level) {
        fprintf(logger->file, "[%s] ", level_names[level]);
    }

    // Message
    va_list args;
    va_start(args, format);
    vfprintf(logger->file, format, args);
    va_end(args);

    fprintf(logger->file, "\n");
    fflush(logger->file);
}

#define LOG_DEBUG(logger, ...) log_message(logger, LOG_DEBUG, __VA_ARGS__)
#define LOG_INFO(logger, ...) log_message(logger, LOG_INFO, __VA_ARGS__)
#define LOG_WARNING(logger, ...) log_message(logger, LOG_WARNING, __VA_ARGS__)
#define LOG_ERROR(logger, ...) log_message(logger, LOG_ERROR, __VA_ARGS__)
#define LOG_CRITICAL(logger, ...) log_message(logger, LOG_CRITICAL, __VA_ARGS__)

// Error recovery patterns
typedef enum {
    RECOVERY_NONE,
    RECOVERY_RETRY,
    RECOVERY_FALLBACK,
    RECOVERY_ABORT
} RecoveryStrategy;

typedef struct {
    int max_retries;
    int current_retry;
    RecoveryStrategy strategy;
} ErrorRecovery;

int execute_with_recovery(int (*operation)(void*), void *data, ErrorRecovery *recovery) {
    int result;

    do {
        result = operation(data);
        if (result == 0) {
            return 0;  // Success
        }

        recovery->current_retry++;

        switch (recovery->strategy) {
            case RECOVERY_RETRY:
                if (recovery->current_retry < recovery->max_retries) {
                    printf("Operation failed, retrying (%d/%d)...\n",
                           recovery->current_retry, recovery->max_retries);
                    sleep(1);  // Wait before retry
                    continue;
                }
                break;

            case RECOVERY_FALLBACK:
                printf("Operation failed, trying fallback...\n");
                // Implement fallback logic here
                return 1;  // Fallback result

            case RECOVERY_ABORT:
                printf("Operation failed, aborting...\n");
                return -1;

            default:
                return result;
        }
    } while (recovery->current_retry < recovery->max_retries);

    return result;
}

// Example operation that may fail
int unreliable_operation(void *data) {
    int *attempt = (int*)data;
    (*attempt)++;

    // Simulate random failure
    if (rand() % 3 == 0) {  // 33% failure rate
        return -1;
    }

    printf("Operation succeeded on attempt %d\n", *attempt);
    return 0;
}

int main() {
    // Create logger
    Logger *logger = create_logger("app.log", LOG_DEBUG);
    if (logger == NULL) {
        fprintf(stderr, "Failed to create logger\n");
        return 1;
    }

    LOG_INFO(logger, "Application started");

    // Test error recovery
    ErrorRecovery recovery = {3, 0, RECOVERY_RETRY};
    int attempt_count = 0;

    int result = execute_with_recovery(unreliable_operation, &attempt_count, &recovery);

    if (result == 0) {
        LOG_INFO(logger, "Operation completed successfully after %d attempts", attempt_count);
    } else {
        LOG_ERROR(logger, "Operation failed after %d attempts", attempt_count);
    }

    LOG_INFO(logger, "Application finished");
    destroy_logger(logger);

    return 0;
}
```

### **4. Security Error Handling**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Secure memory operations
void* secure_malloc(size_t size) {
    if (size == 0 || size > 1024 * 1024) {  // Reasonable limit
        errno = EINVAL;
        return NULL;
    }

    void *ptr = malloc(size);
    if (ptr == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    // Clear memory for security
    memset(ptr, 0, size);
    return ptr;
}

void secure_free(void **ptr) {
    if (ptr == NULL || *ptr == NULL) return;

    // Clear memory before freeing
    size_t size = malloc_usable_size(*ptr);
    memset(*ptr, 0, size);

    free(*ptr);
    *ptr = NULL;
}

// Input sanitization
int sanitize_input(char *input, size_t max_len) {
    if (input == NULL) return -1;

    size_t len = strlen(input);

    // Check length
    if (len == 0 || len > max_len) {
        return -1;
    }

    // Remove potentially dangerous characters
    char *src = input, *dst = input;
    while (*src) {
        if (isalnum(*src) || *src == '_' || *src == '-' || *src == '.') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';

    return 0;
}

// Buffer overflow protection
#define SAFE_STRCPY(dst, src, dst_size) \
    do { \
        if (dst == NULL || src == NULL || dst_size == 0) { \
            errno = EINVAL; \
            break; \
        } \
        size_t src_len = strlen(src); \
        size_t copy_len = (src_len < dst_size - 1) ? src_len : dst_size - 1; \
        memcpy(dst, src, copy_len); \
        dst[copy_len] = '\0'; \
    } while(0)

// SQL injection protection (basic)
int validate_sql_input(const char *input) {
    if (input == NULL) return -1;

    const char *dangerous[] = {
        "SELECT", "INSERT", "UPDATE", "DELETE", "DROP",
        "UNION", "SCRIPT", "EXEC", "SYSTEM", NULL
    };

    char upper_input[256];
    SAFE_STRCPY(upper_input, input, sizeof(upper_input));

    // Convert to uppercase for checking
    for (char *p = upper_input; *p; p++) {
        *p = toupper(*p);
    }

    for (int i = 0; dangerous[i] != NULL; i++) {
        if (strstr(upper_input, dangerous[i]) != NULL) {
            return -1;  // Dangerous content detected
        }
    }

    return 0;
}

// Resource limit enforcement
#define MAX_FILE_SIZE (10 * 1024 * 1024)  // 10MB
#define MAX_MEMORY_USAGE (100 * 1024 * 1024)  // 100MB

typedef struct {
    size_t memory_used;
    size_t file_size_limit;
} ResourceLimits;

ResourceLimits global_limits = {0, MAX_FILE_SIZE};

int check_resource_limits(size_t requested_size, ResourceLimits *limits) {
    if (limits == NULL) limits = &global_limits;

    if (limits->memory_used + requested_size > MAX_MEMORY_USAGE) {
        errno = ENOMEM;
        return -1;
    }

    if (requested_size > limits->file_size_limit) {
        errno = EFBIG;
        return -1;
    }

    limits->memory_used += requested_size;
    return 0;
}

void* secure_resource_malloc(size_t size, ResourceLimits *limits) {
    if (check_resource_limits(size, limits) != 0) {
        return NULL;
    }

    void *ptr = secure_malloc(size);
    if (ptr == NULL) {
        limits->memory_used -= size;  // Rollback
    }

    return ptr;
}

int main() {
    // Test secure memory operations
    char *secure_data = (char*)secure_malloc(100);
    if (secure_data != NULL) {
        strcpy(secure_data, "Sensitive data");
        printf("Secure data: %s\n", secure_data);
        secure_free((void**)&secure_data);
    }

    // Test input sanitization
    char user_input[] = "user_name<script>alert('xss')</script>";
    if (sanitize_input(user_input, 50) == 0) {
        printf("Sanitized input: %s\n", user_input);
    }

    // Test SQL injection protection
    const char *safe_query = "SELECT * FROM users WHERE id = 123";
    const char *dangerous_query = "SELECT * FROM users; DROP TABLE users;";

    printf("Safe query validation: %s\n",
           validate_sql_input(safe_query) == 0 ? "PASS" : "FAIL");
    printf("Dangerous query validation: %s\n",
           validate_sql_input(dangerous_query) == 0 ? "PASS" : "FAIL");

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Check Return Values**
```c
// ✅ Good
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    perror("Failed to open file");
    return 1;
}

// ❌ Bad
FILE *file = fopen("data.txt", "r");
// No error checking
```

### **2. Use errno Appropriately**
```c
// ✅ Good
if (fopen("file.txt", "r") == NULL) {
    if (errno == ENOENT) {
        fprintf(stderr, "File not found\n");
    } else {
        perror("Error opening file");
    }
}

// ❌ Bad
errno = 0;  // Don't manually set errno
```

### **3. Handle Signals Carefully**
```c
// ✅ Good
void signal_handler(int sig) {
    // Use async-safe functions only
    write(STDERR_FILENO, "Signal received\n", 16);
    _exit(1);
}

// ❌ Bad
void bad_signal_handler(int sig) {
    printf("Signal received\n");  // Not async-safe
    malloc(100);  // Not async-safe
}
```

### **4. Clean Up Resources**
```c
// ✅ Good
int process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    // Process file
    int result = process_data(file);

    fclose(file);  // Always close
    return result;
}

// ❌ Bad
int bad_process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    // File not closed on error paths
}
```

---

## 🐛 Common Mistakes

### **1. Ignoring errno**
```c
// Wrong
FILE *file = fopen("file.txt", "r");
if (file == NULL) {
    printf("Error opening file\n");  // No details
}

// Correct
FILE *file = fopen("file.txt", "r");
if (file == NULL) {
    perror("Error opening file");
}
```

### **2. Using printf in Signal Handlers**
```c
// Wrong
void signal_handler(int sig) {
    printf("Signal %d received\n", sig);  // Not async-safe
}

// Correct
void signal_handler(int sig) {
    const char *msg = "Signal received\n";
    write(STDERR_FILENO, msg, strlen(msg));
}
```

### **3. Not Restoring Signal Handlers**
```c
// Wrong
signal(SIGINT, handler);
// Handler may be reset after first signal

// Correct
void handler(int sig) {
    // Handle signal
    signal(SIGINT, handler);  // Reinstall handler
}
```

### **4. Race Conditions with Signals**
```c
// Wrong
int flag = 0;
void handler(int sig) { flag = 1; }
int main() {
    signal(SIGINT, handler);
    while (!flag) { /* work */ }  // Race condition
}

// Better
volatile sig_atomic_t flag = 0;
void handler(int sig) { flag = 1; }
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic Error Handling**
- Create a program that handles file opening errors gracefully
- Implement memory allocation error checking
- Build a calculator with proper error handling

### **Exercise 2: Signal Handling**
- Create a program that handles SIGINT gracefully
- Implement a signal-based timer
- Build a program that ignores SIGPIPE

### **Exercise 3: Custom Error System**
- Design an error code system for a library
- Implement error context tracking
- Create a logging system with error levels

### **Exercise 4: Advanced Error Handling**
- Implement setjmp/longjmp for error recovery
- Create a signal-safe error reporting system
- Build a comprehensive error handling framework

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What does errno contain?
a) Error message string
b) Error code number
c) Error function name
d) Error file location

### **Question 2:**
Which function is used to print error messages with errno?
a) `printf()`
b) `fprintf()`
c) `perror()`
d) `strerror()`

### **Question 3:**
What is the purpose of assert()?
a) Handle runtime errors
b) Check conditions during debugging
c) Print error messages
d) Terminate program

### **Question 4:**
Which signals can be handled by user programs?
a) SIGKILL and SIGSTOP
b) SIGINT and SIGTERM
c) All signals
d) No signals

### **Question 5:**
What does setjmp() return on the first call?
a) -1
b) 0
c) 1
d) Random value

---

## 🔗 Additional Resources

### **Error Handling**
- [errno](https://en.cppreference.com/w/c/error/errno)
- [Signal Handling](https://en.cppreference.com/w/c/program/signal)
- [setjmp/longjmp](https://en.cppreference.com/w/c/program/setjmp)

### **Further Reading**
- [C Error Handling](https://www.gnu.org/software/libc/manual/html_node/Error-Reporting.html)
- [Signals](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Debugging C Programs](https://www.gnu.org/software/gdb/)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ errno and perror for error reporting
- ✅ Assertions and debugging techniques
- ✅ Signal handling and interruption management
- ✅ setjmp/longjmp for non-local jumps
- ✅ Custom error handling systems

**Next Lesson Preview:**
- Data structures fundamentals
- Linked lists implementation
- Stacks and queues
- Trees and graphs basics

---

**🚀 Ready to build data structures?**

[⬅️ Previous: Command Line Arguments](17_Command_Line_Arguments.md) | [Next: Data Structures ➡️](19_Data_Structures.md)