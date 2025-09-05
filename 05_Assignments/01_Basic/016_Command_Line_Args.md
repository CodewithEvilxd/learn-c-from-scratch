# 🎯 Assignment 1.16: Command Line Arguments

## 📋 Problem Statement

Create a C program that processes command line arguments for a file processing utility. Implement options for file operations, text processing, and data manipulation with proper argument validation.

## 🎯 Learning Objectives

- Understand command line argument processing
- Learn main function with parameters
- Practice argument parsing and validation
- Implement command-line options and flags
- Handle different argument types
- Create user-friendly help system

## 📝 Requirements

1. Accept command line arguments in main function
2. Parse options and flags (-h, -v, etc.)
3. Process file names and paths
4. Validate argument count and types
5. Implement help and usage information
6. Handle errors gracefully
7. Support multiple operation modes

## 💡 Hints

- Use `int main(int argc, char *argv[])`
- `argc` is argument count, `argv` is argument array
- First argument is program name
- Use string comparison for option parsing
- Provide clear error messages

## 🔧 Solution

```c
// Assignment 1.16: Command Line Arguments
// File processing utility with command line options

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_FILENAME 256
#define MAX_LINE_LENGTH 1024

// Function prototypes
void print_usage(const char* program_name);
void print_help();
bool parse_arguments(int argc, char* argv[], char** input_file,
                    char** output_file, bool* verbose, bool* uppercase,
                    bool* lowercase, bool* count_lines, bool* count_words);
void process_file(const char* input_file, const char* output_file,
                 bool verbose, bool uppercase, bool lowercase,
                 bool count_lines, bool count_words);
int count_file_lines(const char* filename);
int count_file_words(const char* filename);
void convert_case(char* line, bool uppercase, bool lowercase);

int main(int argc, char* argv[]) {
    char* input_file = NULL;
    char* output_file = NULL;
    bool verbose = false;
    bool uppercase = false;
    bool lowercase = false;
    bool count_lines = false;
    bool count_words = false;

    // Parse command line arguments
    if (!parse_arguments(argc, argv, &input_file, &output_file,
                        &verbose, &uppercase, &lowercase,
                        &count_lines, &count_words)) {
        print_usage(argv[0]);
        return 1;
    }

    // Process the file
    process_file(input_file, output_file, verbose, uppercase, lowercase,
                count_lines, count_words);

    return 0;
}

bool parse_arguments(int argc, char* argv[], char** input_file,
                    char** output_file, bool* verbose, bool* uppercase,
                    bool* lowercase, bool* count_lines, bool* count_words) {

    // Check minimum arguments
    if (argc < 2) {
        fprintf(stderr, "Error: No arguments provided\n");
        return false;
    }

    // Parse options
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // Option
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                print_help();
                exit(0);
            } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
                *verbose = true;
            } else if (strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--uppercase") == 0) {
                *uppercase = true;
            } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lowercase") == 0) {
                *lowercase = true;
            } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--count-lines") == 0) {
                *count_lines = true;
            } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--count-words") == 0) {
                *count_words = true;
            } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                if (i + 1 < argc) {
                    *output_file = argv[i + 1];
                    i++;  // Skip next argument
                } else {
                    fprintf(stderr, "Error: -o requires output filename\n");
                    return false;
                }
            } else {
                fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
                return false;
            }
        } else {
            // File name
            if (*input_file == NULL) {
                *input_file = argv[i];
            } else if (*output_file == NULL) {
                *output_file = argv[i];
            } else {
                fprintf(stderr, "Error: Too many file arguments\n");
                return false;
            }
        }
    }

    // Validate required arguments
    if (*input_file == NULL) {
        fprintf(stderr, "Error: Input file not specified\n");
        return false;
    }

    return true;
}

void print_usage(const char* program_name) {
    printf("Usage: %s [OPTIONS] INPUT_FILE [OUTPUT_FILE]\n", program_name);
    printf("Try '%s --help' for more information.\n", program_name);
}

void print_help() {
    printf("File Processing Utility\n\n");
    printf("USAGE:\n");
    printf("  program [OPTIONS] INPUT_FILE [OUTPUT_FILE]\n\n");
    printf("OPTIONS:\n");
    printf("  -h, --help           Show this help message\n");
    printf("  -v, --verbose        Enable verbose output\n");
    printf("  -u, --uppercase      Convert text to uppercase\n");
    printf("  -l, --lowercase      Convert text to lowercase\n");
    printf("  -c, --count-lines    Count and display line count\n");
    printf("  -w, --count-words    Count and display word count\n");
    printf("  -o, --output FILE    Specify output file\n\n");
    printf("EXAMPLES:\n");
    printf("  program input.txt\n");
    printf("  program -v -u input.txt output.txt\n");
    printf("  program -c -w input.txt\n");
}

void process_file(const char* input_file, const char* output_file,
                 bool verbose, bool uppercase, bool lowercase,
                 bool count_lines, bool count_words) {

    FILE* input = fopen(input_file, "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", input_file);
        return;
    }

    FILE* output = NULL;
    if (output_file) {
        output = fopen(output_file, "w");
        if (!output) {
            fprintf(stderr, "Error: Cannot create output file '%s'\n", output_file);
            fclose(input);
            return;
        }
    }

    if (verbose) {
        printf("Processing file: %s\n", input_file);
        if (output_file) {
            printf("Output file: %s\n", output_file);
        }
    }

    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    int word_count = 0;

    // Process file line by line
    while (fgets(line, sizeof(line), input)) {
        line_count++;

        // Count words in current line
        char* token = strtok(line, " \t\n");
        while (token) {
            word_count++;
            token = strtok(NULL, " \t\n");
        }

        // Apply case conversion
        if (uppercase || lowercase) {
            convert_case(line, uppercase, lowercase);
        }

        // Write to output file or stdout
        if (output) {
            fputs(line, output);
        } else if (uppercase || lowercase) {
            printf("%s", line);
        }
    }

    if (verbose) {
        printf("Processing complete\n");
    }

    // Display statistics
    if (count_lines) {
        printf("Lines: %d\n", line_count);
    }

    if (count_words) {
        printf("Words: %d\n", word_count);
    }

    fclose(input);
    if (output) {
        fclose(output);
    }
}

void convert_case(char* line, bool uppercase, bool lowercase) {
    for (int i = 0; line[i]; i++) {
        if (uppercase) {
            line[i] = toupper(line[i]);
        } else if (lowercase) {
            line[i] = tolower(line[i]);
        }
    }
}
```

## 📊 Test Cases

### Test Case 1: Basic Usage
```
Command: ./program input.txt
Expected: Process input.txt and display if case conversion specified
```

### Test Case 2: With Options
```
Command: ./program -v -u input.txt output.txt
Expected Output:
Processing file: input.txt
Output file: output.txt
Processing complete
```

### Test Case 3: Statistics
```
Command: ./program -c -w input.txt
Expected Output:
Lines: 10
Words: 50
```

### Test Case 4: Help
```
Command: ./program --help
Expected: Display help information
```

### Test Case 5: Error Handling
```
Command: ./program nonexistent.txt
Expected Output: Error: Cannot open input file 'nonexistent.txt'
```

## 🔍 Explanation

1. **Main Function**: `int main(int argc, char* argv[])`
2. **Argument Count**: `argc` - number of arguments
3. **Argument Array**: `argv` - array of argument strings
4. **Option Parsing**: Check for `-` prefix for options
5. **File Handling**: Open and process input/output files
6. **Error Handling**: Validate arguments and file operations

## 🎯 Key Concepts Covered

- Command line argument processing
- Option parsing and validation
- File I/O with command line arguments
- Error handling for invalid arguments
- Help system implementation
- Program configuration via command line

## 🚀 Extensions

1. Add more file processing options (sorting, filtering)
2. Implement long options with `--`
3. Add argument validation for file types
4. Create subcommands for different operations