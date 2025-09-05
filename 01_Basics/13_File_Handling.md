# 📁 Lesson 13: File Handling in C
## Reading and Writing Files

---

## 🎯 Learning Objectives

- Master file opening and closing operations
- Understand different file modes and formats
- Learn sequential and random file access
- Handle file errors and exceptions
- Build practical file-based applications

---

## 📖 File Handling Kya Hai?

**File handling** C mein programs ko disk pe files se read aur write karne deta hai. Files data ka persistent storage provide karta hai jo program termination ke baad bhi survive karta hai.

### **Files ke Types**
1. **Text Files**: Human-readable characters
2. **Binary Files**: Raw data bytes
3. **Sequential Files**: Data order mein access
4. **Random Access Files**: Kisi bhi position pe direct access

### **Advanced File Concepts**
- **File locking aur concurrency**
- **Memory-mapped files**
- **File compression aur encryption**
- **Directory operations**
- **File permissions aur security**

---

## 🔧 Basic File Operations

### **1. Opening and Closing Files**
```c
#include <stdio.h>

int main() {
    FILE *file_ptr;

    // Open file for writing
    file_ptr = fopen("example.txt", "w");

    if (file_ptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // File operations here...

    // Close file
    fclose(file_ptr);

    return 0;
}
```

### **2. File Opening Modes**

| Mode | Description | File Created | Position |
|------|-------------|--------------|----------|
| `"r"` | Read only | No | Beginning |
| `"w"` | Write only | Yes | Beginning (overwrite) |
| `"a"` | Append | Yes | End |
| `"r+"` | Read + Write | No | Beginning |
| `"w+"` | Read + Write | Yes | Beginning (overwrite) |
| `"a+"` | Read + Append | Yes | End |

**Binary Modes:**
- `"rb"`, `"wb"`, `"ab"`, `"rb+"`, `"wb+"`, `"ab+"`

### **3. Writing to Files**
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write strings
    fprintf(file, "Hello, World!\n");
    fprintf(file, "Number: %d\n", 42);

    // Write characters
    fputc('A', file);
    fputc('\n', file);

    // Write formatted data
    int age = 25;
    float height = 5.9;
    fprintf(file, "Age: %d, Height: %.1f\n", age, height);

    fclose(file);
    printf("Data written to file successfully!\n");

    return 0;
}
```

### **4. Reading from Files**
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char buffer[100];

    // Read line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Read: %s", buffer);
    }

    // Read character by character
    rewind(file);  // Go back to beginning
    int ch;
    printf("\nCharacters: ");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}
```

---

## 📝 Text vs Binary Files

### **Text File Operations**
```c
#include <stdio.h>

int main() {
    // Writing text
    FILE *text_file = fopen("text_data.txt", "w");
    fprintf(text_file, "Name: John\nAge: 25\nCity: Mumbai\n");
    fclose(text_file);

    // Reading text
    text_file = fopen("text_data.txt", "r");
    char line[100];
    while (fgets(line, sizeof(line), text_file)) {
        printf("%s", line);
    }
    fclose(text_file);

    return 0;
}
```

### **Binary File Operations**
```c
#include <stdio.h>

struct Student {
    char name[50];
    int roll;
    float marks;
};

int main() {
    struct Student s1 = {"Alice", 101, 95.5};

    // Writing binary
    FILE *bin_file = fopen("student.dat", "wb");
    fwrite(&s1, sizeof(struct Student), 1, bin_file);
    fclose(bin_file);

    // Reading binary
    struct Student s2;
    bin_file = fopen("student.dat", "rb");
    fread(&s2, sizeof(struct Student), 1, bin_file);
    fclose(bin_file);

    printf("Name: %s\nRoll: %d\nMarks: %.2f\n", s2.name, s2.roll, s2.marks);

    return 0;
}
```

---

## 🔍 Random Access Files

### **1. fseek() - Positioning File Pointer**
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("random.txt", "w+");

    // Write some data
    fprintf(file, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    // Move to position 5
    fseek(file, 5, SEEK_SET);
    fprintf(file, "HELLO");

    // Move 10 bytes from current position
    fseek(file, 10, SEEK_CUR);
    fprintf(file, "WORLD");

    // Move to end
    fseek(file, 0, SEEK_END);
    fprintf(file, "END");

    fclose(file);

    return 0;
}
```

### **2. ftell() - Get Current Position**
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("position.txt", "r");

    if (file == NULL) {
        printf("File not found!\n");
        return 1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    printf("File size: %ld bytes\n", file_size);

    // Go back to beginning
    rewind(file);
    printf("Position after rewind: %ld\n", ftell(file));

    fclose(file);
    return 0;
}
```

### **3. rewind() - Reset File Pointer**
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "r");

    // Read some data
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    printf("Position after reading: %ld\n", ftell(file));

    // Reset to beginning
    rewind(file);
    printf("Position after rewind: %ld\n", ftell(file));

    fclose(file);
    return 0;
}
```

### **4. Advanced File Positioning**
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("large_file.txt", "r");
    if (file == NULL) return 1;

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    printf("File size: %ld bytes\n", file_size);

    // Read last 100 bytes
    long read_pos = file_size - 100;
    if (read_pos < 0) read_pos = 0;

    fseek(file, read_pos, SEEK_SET);
    char buffer[101];
    size_t bytes_read = fread(buffer, 1, 100, file);
    buffer[bytes_read] = '\0';

    printf("Last 100 bytes: %s\n", buffer);

    // Read middle section
    fseek(file, file_size / 2, SEEK_SET);
    fread(buffer, 1, 50, file);
    buffer[50] = '\0';
    printf("Middle section: %s\n", buffer);

    fclose(file);
    return 0;
}
```

---

## 🚨 Error Handling

### **1. perror() and errno**
```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");

    if (file == NULL) {
        // Print error message
        perror("Error opening file");

        // Print error number
        printf("Error number: %d\n", errno);

        // Print error description
        printf("Error description: %s\n", strerror(errno));
    } else {
        fclose(file);
    }

    return 0;
}
```

### **2. Comprehensive Error Handling**
```c
#include <stdio.h>
#include <stdlib.h>

FILE* safe_fopen(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file '%s': ", filename);
        perror("");
        return NULL;
    }
    return file;
}

size_t safe_fread(void *ptr, size_t size, size_t count, FILE *stream) {
    size_t result = fread(ptr, size, count, stream);
    if (result != count && !feof(stream)) {
        fprintf(stderr, "Read error occurred\n");
    }
    return result;
}

size_t safe_fwrite(const void *ptr, size_t size, size_t count, FILE *stream) {
    size_t result = fwrite(ptr, size, count, stream);
    if (result != count) {
        fprintf(stderr, "Write error occurred\n");
    }
    return result;
}
```

---

## 📊 Practical Projects

### **Project 1: Student Record System**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_RECORDS 100

typedef struct {
    int roll_number;
    char name[MAX_NAME];
    float marks;
    char grade;
} Student;

void add_student(FILE *file) {
    Student s;

    printf("Enter roll number: ");
    scanf("%d", &s.roll_number);

    printf("Enter name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter marks: ");
    scanf("%f", &s.marks);

    // Calculate grade
    if (s.marks >= 90) s.grade = 'A';
    else if (s.marks >= 80) s.grade = 'B';
    else if (s.marks >= 70) s.grade = 'C';
    else if (s.marks >= 60) s.grade = 'D';
    else s.grade = 'F';

    // Write to file
    fprintf(file, "%d,%s,%.2f,%c\n", s.roll_number, s.name, s.marks, s.grade);
    printf("Student record added successfully!\n");
}

void display_students(FILE *file) {
    char line[200];
    rewind(file);

    printf("\n%-10s %-20s %-10s %-5s\n", "Roll", "Name", "Marks", "Grade");
    printf("--------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        int roll;
        char name[MAX_NAME];
        float marks;
        char grade;

        sscanf(line, "%d,%[^,],%f,%c", &roll, name, &marks, &grade);
        printf("%-10d %-20s %-10.2f %-5c\n", roll, name, marks, grade);
    }
}

int main() {
    FILE *file = fopen("students.txt", "a+");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int choice;
    do {
        printf("\nStudent Record System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student(file);
                break;
            case 2:
                display_students(file);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    fclose(file);
    return 0;
}
```

### **Project 2: Log File Writer**
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LOG_FILE "application.log"
#define MAX_LOG_MESSAGE 500

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_DEBUG
} LogLevel;

const char* log_level_strings[] = {
    "INFO",
    "WARNING",
    "ERROR",
    "DEBUG"
};

void write_log(LogLevel level, const char *message) {
    FILE *log_file = fopen(LOG_FILE, "a");

    if (log_file == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    // Write log entry
    fprintf(log_file, "[%s] [%s] %s\n", time_str, log_level_strings[level], message);

    fclose(log_file);
}

void log_info(const char *message) {
    write_log(LOG_INFO, message);
}

void log_warning(const char *message) {
    write_log(LOG_WARNING, message);
}

void log_error(const char *message) {
    write_log(LOG_ERROR, message);
}

void log_debug(const char *message) {
    write_log(LOG_DEBUG, message);
}

int main() {
    // Clear log file
    FILE *file = fopen(LOG_FILE, "w");
    if (file) fclose(file);

    // Write some log entries
    log_info("Application started");
    log_info("Initializing components");

    log_warning("Configuration file not found, using defaults");

    log_debug("Processing user input");
    log_debug("Input validation passed");

    log_error("Database connection failed");
    log_error("Unable to save user data");

    log_info("Application shutting down");

    printf("Log entries written to %s\n", LOG_FILE);

    return 0;
}
```

---

## 🔄 Advanced File Operations

### **1. Reading/Writing Binary Data**
```c
#include <stdio.h>

struct Employee {
    int id;
    char name[50];
    double salary;
};

void write_employee_binary(const char *filename) {
    FILE *file = fopen(filename, "wb");

    struct Employee emp = {101, "John Doe", 75000.50};
    fwrite(&emp, sizeof(struct Employee), 1, file);

    fclose(file);
}

void read_employee_binary(const char *filename) {
    FILE *file = fopen(filename, "rb");

    struct Employee emp;
    fread(&emp, sizeof(struct Employee), 1, file);

    printf("ID: %d\n", emp.id);
    printf("Name: %s\n", emp.name);
    printf("Salary: %.2f\n", emp.salary);

    fclose(file);
}
```

### **2. File Copy Utility**
```c
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int copy_file(const char *source, const char *destination) {
    FILE *src_file = fopen(source, "rb");
    if (src_file == NULL) {
        perror("Error opening source file");
        return 0;
    }

    FILE *dest_file = fopen(destination, "wb");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        fclose(src_file);
        return 0;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    return 1;
}

int main() {
    if (copy_file("source.txt", "destination.txt")) {
        printf("File copied successfully!\n");
    } else {
        printf("File copy failed!\n");
    }

    return 0;
}
```

### **3. File Statistics**
```c
#include <stdio.h>
#include <ctype.h>

void analyze_file(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int lines = 0, words = 0, characters = 0;
    int in_word = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    // Count the last line if file doesn't end with newline
    if (characters > 0 && ch != '\n') {
        lines++;
    }

    printf("File: %s\n", filename);
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);

    fclose(file);
}

int main() {
    analyze_file("sample.txt");
    return 0;
}
```

### **4. File Locking (Unix/Linux)**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("shared_file.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Try to acquire write lock
    struct flock lock;
    lock.l_type = F_WRLCK;    // Write lock
    lock.l_whence = SEEK_SET; // From beginning
    lock.l_start = 0;         // Start at byte 0
    lock.l_len = 0;           // Lock entire file

    printf("Attempting to acquire lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {  // F_SETLKW waits for lock
        perror("Error acquiring lock");
        close(fd);
        return 1;
    }

    printf("Lock acquired! Writing to file...\n");

    // Write to file
    write(fd, "Process ", 8);
    write(fd, getpid(), sizeof(pid_t));
    write(fd, " was here\n", 10);

    sleep(5);  // Hold lock for 5 seconds

    // Release lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error releasing lock");
    }

    printf("Lock released\n");
    close(fd);
    return 0;
}
```

### **5. Memory-Mapped Files**
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "mmap_example.txt";
    const char *message = "Hello, Memory-Mapped Files!";

    // Create and write to file
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write some data
    write(fd, message, strlen(message));

    // Get file size
    off_t file_size = lseek(fd, 0, SEEK_END);

    // Memory map the file
    char *mapped = mmap(NULL, file_size, PROT_READ | PROT_WRITE,
                       MAP_SHARED, fd, 0);

    if (mapped == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return 1;
    }

    printf("Original content: %s\n", mapped);

    // Modify content through memory mapping
    strcpy(mapped + 7, "Memory-Mapped");  // Replace "World" with "Memory-Mapped"

    printf("Modified content: %s\n", mapped);

    // Unmap and close
    if (munmap(mapped, file_size) == -1) {
        perror("Error unmapping");
    }

    close(fd);

    // Read file to verify changes
    FILE *file = fopen(filename, "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    printf("File content after mmap: %s", buffer);
    fclose(file);

    return 0;
}
```

### **6. Directory Operations**
```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    printf("Contents of %s:\n", path);

    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("  %s", entry->d_name);

        // Check if it's a directory
        struct stat statbuf;
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                printf(" (directory)");
            } else if (S_ISREG(statbuf.st_mode)) {
                printf(" (file, %ld bytes)", statbuf.st_size);
            }
        }
        printf("\n");
    }

    closedir(dir);
}

int create_directory(const char *path) {
    #ifdef _WIN32
        return mkdir(path);
    #else
        return mkdir(path, 0755);
    #endif
}

int main() {
    const char *dirname = "test_dir";

    // Create directory
    if (create_directory(dirname) == 0) {
        printf("Directory '%s' created\n", dirname);
    } else {
        perror("Error creating directory");
    }

    // List current directory
    list_directory(".");

    // List the new directory
    list_directory(dirname);

    return 0;
}
```

### **7. File Compression/Decompression (Simple RLE)**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");

    if (in == NULL || out == NULL) {
        perror("Error opening files");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    int current_byte, prev_byte = -1;
    int count = 1;

    while ((current_byte = fgetc(in)) != EOF) {
        if (current_byte == prev_byte && count < 255) {
            count++;
        } else {
            if (prev_byte != -1) {
                fputc(count, out);
                fputc(prev_byte, out);
            }
            prev_byte = current_byte;
            count = 1;
        }
    }

    // Write last sequence
    if (prev_byte != -1) {
        fputc(count, out);
        fputc(prev_byte, out);
    }

    fclose(in);
    fclose(out);
    printf("File compressed successfully\n");
}

void decompress_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");

    if (in == NULL || out == NULL) {
        perror("Error opening files");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    int count, byte;

    while ((count = fgetc(in)) != EOF) {
        byte = fgetc(in);
        for (int i = 0; i < count; i++) {
            fputc(byte, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("File decompressed successfully\n");
}

int main() {
    const char *original = "test.txt";
    const char *compressed = "test.rle";
    const char *decompressed = "test_decompressed.txt";

    // Create a test file
    FILE *test = fopen(original, "w");
    fprintf(test, "AAAAAABBBBBBCCCCCCDDDDDD");
    fclose(test);

    compress_file(original, compressed);
    decompress_file(compressed, decompressed);

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Always Check File Operations**
```c
// ✅ Good
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    perror("Error opening file");
    return 1;
}

// ❌ Bad
FILE *file = fopen("data.txt", "r");
// No error checking
```

### **2. Close Files Properly**
```c
// ✅ Good
FILE *file = fopen("data.txt", "r");
if (file != NULL) {
    // Use file
    fclose(file);
}

// ❌ Bad
FILE *file = fopen("data.txt", "r");
// Forgot to close - resource leak
```

### **3. Use Appropriate Buffer Sizes**
```c
// ✅ Good
char buffer[1024];
while (fgets(buffer, sizeof(buffer), file)) {
    // Process line
}

// ❌ Bad
char buffer[10];
while (fgets(buffer, sizeof(buffer), file)) {
    // May truncate long lines
}
```

### **4. Handle Binary vs Text Files Correctly**
```c
// ✅ Good
FILE *text_file = fopen("data.txt", "r");     // Text mode
FILE *bin_file = fopen("data.bin", "rb");     // Binary mode

// ❌ Bad
FILE *file = fopen("data.bin", "r");          // Wrong mode for binary
```

---

## 🐛 Common Mistakes

### **1. Forgetting File Mode**
```c
// Wrong
FILE *file = fopen("data.txt");  // No mode specified

// Correct
FILE *file = fopen("data.txt", "r");
```

### **2. Not Checking EOF Correctly**
```c
// Wrong
char ch;
while (ch = fgetc(file) != EOF) {
    // ch gets 0 or 1, not the character
}

// Correct
char ch;
while ((ch = fgetc(file)) != EOF) {
    // ch gets the actual character
}
```

### **3. Buffer Overflow**
```c
// Wrong
char buffer[10];
fgets(buffer, 100, file);  // May overflow buffer

// Correct
char buffer[100];
fgets(buffer, sizeof(buffer), file);
```

### **4. Not Handling fgets Return Value**
```c
// Wrong
char buffer[100];
fgets(buffer, sizeof(buffer), file);
// No check if read was successful

// Correct
char buffer[100];
if (fgets(buffer, sizeof(buffer), file) != NULL) {
    // Process buffer
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic File Operations**
- Create a program to count lines, words, and characters in a file
- Build a simple text file viewer
- Implement a file copy utility

### **Exercise 2: Data Persistence**
- Create a phonebook application with file storage
- Build a simple database for student records
- Implement a configuration file parser

### **Exercise 3: Binary Files**
- Create a program to store and retrieve structures
- Build an inventory management system
- Implement a simple database with indexing

### **Exercise 4: Advanced File Handling**
- Create a log rotation system
- Build a file compression utility
- Implement a simple text editor

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
Which mode opens a file for both reading and writing?
a) `"r"`
b) `"w"`
c) `"r+"`
d) `"a"`

### **Question 2:**
What does `fseek(file, 0, SEEK_END)` do?
a) Goes to file beginning
b) Goes to file end
c) Moves 0 bytes from current position
d) Closes the file

### **Question 3:**
Which function is used to read a line from a file?
a) `fread()`
b) `fgets()`
c) `fscanf()`
d) `fgetc()`

### **Question 4:**
What does `perror()` function do?
a) Prints error message
b) Closes file
c) Opens file
d) Reads file

### **Question 5:**
Which mode should be used for binary files?
a) `"r"`, `"w"`, `"a"`
b) `"rb"`, `"wb"`, `"ab"`
c) `"rt"`, `"wt"`, `"at"`
d) `"r+"`, `"w+"`, `"a+"`

---

## 🔗 Additional Resources

### **File Handling**
- [C File I/O](https://en.cppreference.com/w/c/io)
- [File Positioning](https://en.cppreference.com/w/c/io/fseek)
- [Error Handling](https://en.cppreference.com/w/c/error)

### **Further Reading**
- [File Operations in C](https://www.programiz.com/c-programming/c-file-input-output)
- [Binary Files](https://www.geeksforgeeks.org/basics-file-handling-c/)
- [File Management](https://www.tutorialspoint.com/cprogramming/c_file_io.htm)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ File opening and closing operations
- ✅ Different file modes and formats
- ✅ Sequential and random file access
- ✅ File error handling
- ✅ Practical file-based applications

**Next Lesson Preview:**
- Preprocessor directives
- Macros and conditional compilation
- Header files and multi-file programs
- Compilation process details

---

**🚀 Ready to explore the preprocessor?**

[⬅️ Previous: Dynamic Memory](12_Dynamic_Memory.md) | [Next: Preprocessor ➡️](14_Preprocessor.md)