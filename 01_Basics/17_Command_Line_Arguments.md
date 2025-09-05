# 💻 Lesson 17: Command Line Arguments in C
## Interacting with the Operating System

---

## 🎯 Learning Objectives

- Understand command line arguments in C programs
- Master argument parsing techniques
- Learn environment variable handling
- Implement proper program exit codes
- Build command-line utilities

---

## 📖 Command Line Arguments Kya Hain?

**Command line arguments** users ko programs start karte time information pass karne dete hain. Ye programs ko flexible aur configurable banate hain bina recompilation ke.

### **Command Line Structure**
```bash
program_name argument1 argument2 argument3
```

### **Example Usage**
```bash
# Calculator program
./calculator add 10 5

# File processor
./processor -i input.txt -o output.txt -v

# Custom greeting
./greet John 25
```

### **Advanced CLI Concepts**
- **Subcommands aur nested commands**
- **Configuration files integration**
- **Auto-completion aur shell integration**
- **Internationalization (i18n) support**
- **Interactive mode aur REPL**

---

## 🔧 Basic Command Line Arguments

### **1. main() with Arguments**
```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc - 1);

    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}
```

**Compilation and Execution:**
```bash
gcc program.c -o program
./program hello world 123
```

**Output:**
```
Program name: ./program
Number of arguments: 3
Argument 1: hello
Argument 2: world
Argument 3: 123
```

### **2. Argument Processing**
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <operation> <numbers...>\n", argv[0]);
        return 1;
    }

    char *operation = argv[1];

    if (strcmp(operation, "add") == 0) {
        if (argc < 4) {
            printf("Usage: %s add <num1> <num2>\n", argv[0]);
            return 1;
        }

        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        printf("Sum: %d\n", a + b);

    } else if (strcmp(operation, "multiply") == 0) {
        if (argc < 4) {
            printf("Usage: %s multiply <num1> <num2>\n", argv[0]);
            return 1;
        }

        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        printf("Product: %d\n", a * b);

    } else {
        printf("Unknown operation: %s\n", operation);
        printf("Supported operations: add, multiply\n");
        return 1;
    }

    return 0;
}
```

---

## 🔍 Advanced Argument Parsing

### **1. Manual Parsing with Loops**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 10

typedef struct {
    char *input_file;
    char *output_file;
    int verbose;
    int help;
} ProgramOptions;

void print_usage(char *program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -i, --input <file>    Input file\n");
    printf("  -o, --output <file>   Output file\n");
    printf("  -v, --verbose         Verbose output\n");
    printf("  -h, --help           Show this help\n");
}

ProgramOptions parse_arguments(int argc, char *argv[]) {
    ProgramOptions options = {NULL, NULL, 0, 0};

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc) {
                options.input_file = argv[i + 1];
                i++;  // Skip next argument
            } else {
                printf("Error: -i requires a filename\n");
                options.help = 1;
            }
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                options.output_file = argv[i + 1];
                i++;  // Skip next argument
            } else {
                printf("Error: -o requires a filename\n");
                options.help = 1;
            }
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            options.verbose = 1;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            options.help = 1;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            options.help = 1;
        }
    }

    return options;
}

int main(int argc, char *argv[]) {
    ProgramOptions options = parse_arguments(argc, argv);

    if (options.help) {
        print_usage(argv[0]);
        return 0;
    }

    if (options.verbose) {
        printf("Verbose mode enabled\n");
    }

    if (options.input_file) {
        printf("Input file: %s\n", options.input_file);
    }

    if (options.output_file) {
        printf("Output file: %s\n", options.output_file);
    }

    return 0;
}
```

### **2. Using getopt() Function**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For getopt
#include <string.h>

void print_usage(char *program_name) {
    printf("Usage: %s [-i input_file] [-o output_file] [-v] [-h]\n", program_name);
    printf("Options:\n");
    printf("  -i input_file    Specify input file\n");
    printf("  -o output_file   Specify output file\n");
    printf("  -v               Verbose mode\n");
    printf("  -h               Show help\n");
}

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_file = NULL;
    int verbose = 0;
    int opt;

    // getopt format: "i:o:vh"
    // Colon after option means it requires an argument
    while ((opt = getopt(argc, argv, "i:o:vh")) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
            case '?':
                // Invalid option or missing argument
                return 1;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    // Process remaining arguments (not options)
    if (optind < argc) {
        printf("Non-option arguments: ");
        for (int i = optind; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }

    if (verbose) {
        printf("Verbose mode enabled\n");
    }

    if (input_file) {
        printf("Input file: %s\n", input_file);
    }

    if (output_file) {
        printf("Output file: %s\n", output_file);
    }

    return 0;
}
```

### **3. Long Options with getopt_long()**
```c
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct option long_options[] = {
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},
    {"verbose", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

void print_usage(char *program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -i, --input <file>    Input file\n");
    printf("  -o, --output <file>   Output file\n");
    printf("  -v, --verbose         Verbose output\n");
    printf("  -h, --help           Show help\n");
}

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_file = NULL;
    int verbose = 0;
    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "i:o:vh", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
            case '?':
                return 1;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (verbose) {
        printf("Verbose mode enabled\n");
    }

    if (input_file) {
        printf("Input file: %s\n", input_file);
    }

    if (output_file) {
        printf("Output file: %s\n", output_file);
    }

    return 0;
}
```

---

## 🌍 Environment Variables

### **1. Accessing Environment Variables**
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    // Method 1: Using getenv()
    char *home_dir = getenv("HOME");
    if (home_dir != NULL) {
        printf("Home directory: %s\n", home_dir);
    }

    char *path = getenv("PATH");
    if (path != NULL) {
        printf("PATH: %s\n", path);
    }

    char *user = getenv("USER");
    if (user != NULL) {
        printf("Current user: %s\n", user);
    }

    // Method 2: Using envp parameter (if supported)
    if (envp != NULL) {
        printf("\nAll environment variables:\n");
        for (int i = 0; envp[i] != NULL; i++) {
            printf("%s\n", envp[i]);
        }
    }

    return 0;
}
```

### **2. Setting Environment Variables**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Set environment variable
    if (setenv("MY_VARIABLE", "Hello World", 1) == 0) {
        printf("Environment variable set successfully\n");
    } else {
        printf("Failed to set environment variable\n");
    }

    // Get the variable we just set
    char *value = getenv("MY_VARIABLE");
    if (value != NULL) {
        printf("MY_VARIABLE = %s\n", value);
    }

    // Modify existing variable
    setenv("PATH", "/usr/local/bin:/usr/bin:/bin", 1);
    printf("Modified PATH: %s\n", getenv("PATH"));

    return 0;
}
```

### **3. Environment Variable Utilities**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_environment() {
    extern char **environ;  // Global environment variable array

    printf("Environment Variables:\n");
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

char* get_env_value(const char *name) {
    extern char **environ;

    for (char **env = environ; *env != NULL; env++) {
        char *equals = strchr(*env, '=');
        if (equals != NULL) {
            size_t name_len = equals - *env;
            if (strncmp(*env, name, name_len) == 0 && name[name_len] == '\0') {
                return equals + 1;
            }
        }
    }
    return NULL;
}

int main() {
    // Print specific environment variables
    printf("HOME: %s\n", getenv("HOME"));
    printf("USER: %s\n", getenv("USER"));
    printf("SHELL: %s\n", getenv("SHELL"));

    // Custom function to get environment value
    char *custom_value = get_env_value("HOME");
    if (custom_value != NULL) {
        printf("Custom HOME: %s\n", custom_value);
    }

    // Print all environment variables (commented out to avoid spam)
    // print_environment();

    return 0;
}
```

---

## 🚪 Program Exit Codes

### **1. Standard Exit Codes**
```c
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR_INVALID_ARGS 1
#define ERROR_FILE_NOT_FOUND 2
#define ERROR_PERMISSION_DENIED 3
#define ERROR_OUT_OF_MEMORY 4

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: Insufficient arguments\n");
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return ERROR_INVALID_ARGS;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return ERROR_FILE_NOT_FOUND;
    }

    // Process file...
    printf("File processed successfully\n");
    fclose(file);

    return SUCCESS;
}
```

### **2. Exit Code Handling in Scripts**
```bash
#!/bin/bash

# Run the program
./myprogram input.txt

# Check exit code
if [ $? -eq 0 ]; then
    echo "Program executed successfully"
elif [ $? -eq 1 ]; then
    echo "Invalid arguments"
elif [ $? -eq 2 ]; then
    echo "File not found"
else
    echo "Unknown error"
fi
```

### **3. Using exit() Function**
```c
#include <stdio.h>
#include <stdlib.h>

void check_memory(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int *arr = (int*)malloc(10 * sizeof(int));
    check_memory(arr);

    // Normal program execution
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 2;
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}
```

### **4. Advanced Exit Code Patterns**
```c
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>  // BSD exit codes

// Custom exit codes
#define EXIT_USAGE 64       // Command line usage error
#define EXIT_DATAERR 65     // Data format error
#define EXIT_NOINPUT 66     // Cannot open input
#define EXIT_NOUSER 67      // Addressee unknown
#define EXIT_NOHOST 68      // Host name unknown
#define EXIT_UNAVAILABLE 69 // Service unavailable
#define EXIT_SOFTWARE 70    // Internal software error
#define EXIT_OSERR 71       // System error
#define EXIT_OSFILE 72      // Critical OS file missing
#define EXIT_CANTCREAT 73   // Can't create user output file
#define EXIT_IOERR 74       // Input/output error
#define EXIT_TEMPFAIL 75    // Temp failure
#define EXIT_PROTOCOL 76    // Remote error in protocol
#define EXIT_NOPERM 77      // Permission denied
#define EXIT_CONFIG 78      // Configuration error

void validate_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Cannot open input file");
        exit(EXIT_NOINPUT);
    }
    fclose(file);
}

void validate_output(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Cannot create output file");
        exit(EXIT_CANTCREAT);
    }
    fclose(file);
    remove(filename);  // Clean up test file
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_USAGE);
    }

    validate_file(argv[1]);
    validate_output(argv[2]);

    printf("Files validated successfully\n");
    return EXIT_SUCCESS;
}
```

### **5. Signal Handling for Clean Exits**
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t exit_requested = 0;

void signal_handler(int signum) {
    exit_requested = 1;
    printf("\nReceived signal %d, cleaning up...\n", signum);
}

void cleanup_resources() {
    printf("Cleaning up resources...\n");
    // Close files, free memory, etc.
}

int main() {
    // Register signal handlers
    signal(SIGINT, signal_handler);   // Ctrl+C
    signal(SIGTERM, signal_handler);  // Termination request
    signal(SIGHUP, signal_handler);   // Hangup

    printf("Program running. Press Ctrl+C to exit.\n");

    while (!exit_requested) {
        printf("Working...\n");
        sleep(1);
    }

    cleanup_resources();
    printf("Program exited cleanly\n");

    return EXIT_SUCCESS;
}
```

---

## 🛠️ Practical Applications

### **1. File Processor with Options**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char *input_file;
    char *output_file;
    int line_numbers;
    int word_count;
    int char_count;
    int verbose;
} Options;

void print_usage(char *program_name) {
    printf("Usage: %s [options] input_file [output_file]\n", program_name);
    printf("Options:\n");
    printf("  -l    Add line numbers\n");
    printf("  -w    Show word count\n");
    printf("  -c    Show character count\n");
    printf("  -v    Verbose output\n");
    printf("  -h    Show this help\n");
}

Options parse_options(int argc, char *argv[]) {
    Options opts = {NULL, NULL, 0, 0, 0, 0};
    int opt;

    while ((opt = getopt(argc, argv, "lwcvho:")) != -1) {
        switch (opt) {
            case 'l':
                opts.line_numbers = 1;
                break;
            case 'w':
                opts.word_count = 1;
                break;
            case 'c':
                opts.char_count = 1;
                break;
            case 'v':
                opts.verbose = 1;
                break;
            case 'o':
                opts.output_file = optarg;
                break;
            case 'h':
            default:
                print_usage(argv[0]);
                exit(0);
        }
    }

    // Get input file
    if (optind < argc) {
        opts.input_file = argv[optind];
    } else {
        fprintf(stderr, "Error: Input file required\n");
        print_usage(argv[0]);
        exit(1);
    }

    return opts;
}

void process_file(Options opts) {
    FILE *input = fopen(opts.input_file, "r");
    if (input == NULL) {
        perror("Error opening input file");
        exit(1);
    }

    FILE *output = stdout;
    if (opts.output_file != NULL) {
        output = fopen(opts.output_file, "w");
        if (output == NULL) {
            perror("Error opening output file");
            fclose(input);
            exit(1);
        }
    }

    char line[1024];
    int line_num = 1;
    int total_words = 0;
    int total_chars = 0;

    while (fgets(line, sizeof(line), input) != NULL) {
        if (opts.line_numbers) {
            fprintf(output, "%d: ", line_num);
        }

        fprintf(output, "%s", line);

        if (opts.word_count || opts.char_count) {
            int words = 0;
            int chars = strlen(line);
            int in_word = 0;

            for (int i = 0; line[i] != '\0'; i++) {
                if (isspace(line[i])) {
                    in_word = 0;
                } else if (!in_word) {
                    in_word = 1;
                    words++;
                }
            }

            total_words += words;
            total_chars += chars;
        }

        line_num++;
    }

    if (opts.verbose) {
        fprintf(stderr, "Processed %d lines\n", line_num - 1);
        if (opts.word_count) {
            fprintf(stderr, "Total words: %d\n", total_words);
        }
        if (opts.char_count) {
            fprintf(stderr, "Total characters: %d\n", total_chars);
        }
    }

    fclose(input);
    if (output != stdout) {
        fclose(output);
    }
}

int main(int argc, char *argv[]) {
    Options opts = parse_options(argc, argv);
    process_file(opts);

    return 0;
}
```

### **2. Configuration Manager**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILE "app.config"
#define MAX_CONFIG_LINE 256

typedef struct {
    char database_host[64];
    int database_port;
    char log_level[16];
    int max_connections;
} Config;

Config load_config() {
    Config config = {"localhost", 5432, "INFO", 100};

    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        printf("Config file not found, using defaults\n");
        return config;
    }

    char line[MAX_CONFIG_LINE];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;

        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\0') continue;

        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key && value) {
            if (strcmp(key, "database_host") == 0) {
                strncpy(config.database_host, value, sizeof(config.database_host) - 1);
            } else if (strcmp(key, "database_port") == 0) {
                config.database_port = atoi(value);
            } else if (strcmp(key, "log_level") == 0) {
                strncpy(config.log_level, value, sizeof(config.log_level) - 1);
            } else if (strcmp(key, "max_connections") == 0) {
                config.max_connections = atoi(value);
            }
        }
    }

    fclose(file);
    return config;
}

void print_config(Config config) {
    printf("Configuration:\n");
    printf("  Database Host: %s\n", config.database_host);
    printf("  Database Port: %d\n", config.database_port);
    printf("  Log Level: %s\n", config.log_level);
    printf("  Max Connections: %d\n", config.max_connections);
}

int main() {
    Config config = load_config();
    print_config(config);

    return 0;
}
```

### **3. Subcommands and Command Dispatch**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*CommandHandler)(int argc, char *argv[]);

// Command handlers
int handle_create(int argc, char *argv[]) {
    printf("Creating new item\n");
    if (argc > 2) {
        printf("Name: %s\n", argv[2]);
    }
    return 0;
}

int handle_delete(int argc, char *argv[]) {
    printf("Deleting item\n");
    if (argc > 2) {
        printf("ID: %s\n", argv[2]);
    }
    return 0;
}

int handle_list(int argc, char *argv[]) {
    printf("Listing items\n");
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--filter") == 0 && i + 1 < argc) {
            printf("Filter: %s\n", argv[i + 1]);
            i++;  // Skip next argument
        }
    }
    return 0;
}

int handle_help(int argc, char *argv[]) {
    printf("Available commands:\n");
    printf("  create <name>    Create new item\n");
    printf("  delete <id>      Delete item by ID\n");
    printf("  list [--filter]  List items with optional filter\n");
    printf("  help             Show this help\n");
    return 0;
}

struct {
    const char *name;
    CommandHandler handler;
    const char *description;
} commands[] = {
    {"create", handle_create, "Create new item"},
    {"delete", handle_delete, "Delete item by ID"},
    {"list", handle_list, "List items"},
    {"help", handle_help, "Show help"},
    {NULL, NULL, NULL}  // Sentinel
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        fprintf(stderr, "Use '%s help' for available commands\n", argv[0]);
        return 1;
    }

    const char *command_name = argv[1];

    // Find and execute command
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(command_name, commands[i].name) == 0) {
            return commands[i].handler(argc, argv);
        }
    }

    fprintf(stderr, "Unknown command: %s\n", command_name);
    fprintf(stderr, "Use '%s help' for available commands\n", argv[0]);
    return 1;
}
```

### **4. Configuration File with Command Line Override**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char server_host[64];
    int server_port;
    char log_file[256];
    int debug_mode;
    int max_clients;
} AppConfig;

// Default configuration
AppConfig default_config() {
    AppConfig config;
    strcpy(config.server_host, "localhost");
    config.server_port = 8080;
    strcpy(config.log_file, "app.log");
    config.debug_mode = 0;
    config.max_clients = 100;
    return config;
}

// Load configuration from file
AppConfig load_config_file(const char *filename) {
    AppConfig config = default_config();

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return config;  // Return defaults if file not found
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (key && value) {
            if (strcmp(key, "server_host") == 0) {
                strncpy(config.server_host, value, sizeof(config.server_host) - 1);
            } else if (strcmp(key, "server_port") == 0) {
                config.server_port = atoi(value);
            } else if (strcmp(key, "log_file") == 0) {
                strncpy(config.log_file, value, sizeof(config.log_file) - 1);
            } else if (strcmp(key, "debug_mode") == 0) {
                config.debug_mode = atoi(value);
            } else if (strcmp(key, "max_clients") == 0) {
                config.max_clients = atoi(value);
            }
        }
    }

    fclose(file);
    return config;
}

// Override configuration with command line arguments
AppConfig parse_command_line(int argc, char *argv[], AppConfig config) {
    int opt;
    while ((opt = getopt(argc, argv, "h:p:l:dm:c:")) != -1) {
        switch (opt) {
            case 'h':
                strncpy(config.server_host, optarg, sizeof(config.server_host) - 1);
                break;
            case 'p':
                config.server_port = atoi(optarg);
                break;
            case 'l':
                strncpy(config.log_file, optarg, sizeof(config.log_file) - 1);
                break;
            case 'd':
                config.debug_mode = 1;
                break;
            case 'm':
                config.max_clients = atoi(optarg);
                break;
            case 'c':
                // Load config file specified on command line
                config = load_config_file(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-h host] [-p port] [-l log] [-d] [-m max] [-c config]\n", argv[0]);
                exit(1);
        }
    }

    return config;
}

void print_config(const AppConfig *config) {
    printf("Application Configuration:\n");
    printf("  Server Host: %s\n", config->server_host);
    printf("  Server Port: %d\n", config->server_port);
    printf("  Log File: %s\n", config->log_file);
    printf("  Debug Mode: %s\n", config->debug_mode ? "Enabled" : "Disabled");
    printf("  Max Clients: %d\n", config->max_clients);
}

int main(int argc, char *argv[]) {
    // Load default configuration
    AppConfig config = default_config();

    // Try to load from default config file
    config = load_config_file("app.conf");

    // Override with command line arguments
    config = parse_command_line(argc, argv, config);

    print_config(&config);

    return 0;
}
```

### **5. Internationalization (i18n) Support**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Message catalog
typedef struct {
    const char *key;
    const char *english;
    const char *hindi;
    const char *spanish;
} Message;

Message messages[] = {
    {"welcome", "Welcome to the application", "एप्लिकेशन में आपका स्वागत है", "Bienvenido a la aplicación"},
    {"error_file", "Error opening file", "फ़ाइल खोलने में त्रुटि", "Error al abrir archivo"},
    {"success", "Operation successful", "ऑपरेशन सफल", "Operación exitosa"},
    {"invalid_input", "Invalid input provided", "अमान्य इनपुट प्रदान किया गया", "Entrada inválida proporcionada"},
    {NULL, NULL, NULL, NULL}
};

typedef enum {
    LANG_ENGLISH,
    LANG_HINDI,
    LANG_SPANISH
} Language;

Language current_language = LANG_ENGLISH;

// Set language from command line or environment
void set_language(const char *lang_code) {
    if (strcmp(lang_code, "hi") == 0 || strcmp(lang_code, "hindi") == 0) {
        current_language = LANG_HINDI;
    } else if (strcmp(lang_code, "es") == 0 || strcmp(lang_code, "spanish") == 0) {
        current_language = LANG_SPANISH;
    } else {
        current_language = LANG_ENGLISH;
    }
}

// Get localized message
const char* get_message(const char *key) {
    for (int i = 0; messages[i].key != NULL; i++) {
        if (strcmp(messages[i].key, key) == 0) {
            switch (current_language) {
                case LANG_HINDI:
                    return messages[i].hindi;
                case LANG_SPANISH:
                    return messages[i].spanish;
                default:
                    return messages[i].english;
            }
        }
    }
    return key;  // Return key if message not found
}

int main(int argc, char *argv[]) {
    // Set locale
    setlocale(LC_ALL, "");

    // Check for language option
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--lang") == 0 && i + 1 < argc) {
            set_language(argv[i + 1]);
            break;
        }
    }

    // Check environment variable
    char *env_lang = getenv("APP_LANG");
    if (env_lang != NULL) {
        set_language(env_lang);
    }

    printf("%s\n", get_message("welcome"));

    // Simulate some operations
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("%s\n", get_message("error_file"));
    } else {
        printf("%s\n", get_message("success"));
        fclose(file);
    }

    return 0;
}
```

### **6. Interactive Mode and REPL**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 256

void print_prompt() {
    printf("cli> ");
    fflush(stdout);
}

void process_command(char *command) {
    // Remove trailing newline
    command[strcspn(command, "\n")] = 0;

    if (strlen(command) == 0) {
        return;
    }

    if (strcmp(command, "help") == 0) {
        printf("Available commands:\n");
        printf("  help     - Show this help\n");
        printf("  version  - Show version\n");
        printf("  quit     - Exit the program\n");
        printf("  echo     - Echo the arguments\n");
    } else if (strcmp(command, "version") == 0) {
        printf("CLI Tool v1.0.0\n");
    } else if (strcmp(command, "quit") == 0) {
        printf("Goodbye!\n");
        exit(0);
    } else if (strncmp(command, "echo ", 5) == 0) {
        printf("%s\n", command + 5);
    } else {
        printf("Unknown command: %s\n", command);
        printf("Type 'help' for available commands\n");
    }
}

int is_interactive() {
    return isatty(STDIN_FILENO);
}

int main(int argc, char *argv[]) {
    // Check for batch mode (commands from arguments)
    if (argc > 1) {
        // Batch mode - execute command from arguments
        char command[MAX_INPUT] = "";
        for (int i = 1; i < argc; i++) {
            if (i > 1) strcat(command, " ");
            strcat(command, argv[i]);
        }
        process_command(command);
        return 0;
    }

    // Interactive mode
    if (is_interactive()) {
        printf("Welcome to CLI Tool\n");
        printf("Type 'help' for available commands or 'quit' to exit\n\n");

        char input[MAX_INPUT];
        while (1) {
            print_prompt();
            if (fgets(input, sizeof(input), stdin) == NULL) {
                break;  // EOF or error
            }
            process_command(input);
        }
        printf("\n");
    } else {
        // Non-interactive mode (pipe input)
        char input[MAX_INPUT];
        while (fgets(input, sizeof(input), stdin) != NULL) {
            process_command(input);
        }
    }

    return 0;
}
```

### **7. Auto-completion and Shell Integration**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Generate bash completion script
void generate_completion_script(const char *program_name) {
    printf("# Bash completion for %s\n", program_name);
    printf("_%s_completions()\n", program_name);
    printf("{\n");
    printf("    local cur prev opts\n");
    printf("    COMPREPLY=()\n");
    printf("    cur=\"${COMP_WORDS[COMP_CWORD]}\"\n");
    printf("    prev=\"${COMP_WORDS[COMP_CWORD-1]}\"\n");
    printf("    opts=\"--help --version --verbose -h -v\"\n");
    printf("\n");
    printf("    case \"$prev\" in\n");
    printf("        -i|--input)\n");
    printf("            COMPREPLY=( $(compgen -f -- \"$cur\") )\n");
    printf("            return 0\n");
    printf("            ;;\n");
    printf("        -o|--output)\n");
    printf("            COMPREPLY=( $(compgen -f -- \"$cur\") )\n");
    printf("            return 0\n");
    printf("            ;;\n");
    printf("    esac\n");
    printf("\n");
    printf("    COMPREPLY=( $(compgen -W \"$opts\" -- \"$cur\") )\n");
    printf("    return 0\n");
    printf("}\n");
    printf("\n");
    printf("complete -F _%s_completions %s\n", program_name, program_name);
}

// Command history (simple implementation)
#define MAX_HISTORY 100
char *command_history[MAX_HISTORY];
int history_count = 0;

void add_to_history(const char *command) {
    if (history_count < MAX_HISTORY) {
        command_history[history_count] = strdup(command);
        history_count++;
    }
}

void show_history() {
    printf("Command History:\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, command_history[i]);
    }
}

// Enhanced interactive shell
int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--generate-completion") == 0) {
        generate_completion_script(argv[0]);
        return 0;
    }

    printf("Enhanced CLI Tool\n");
    printf("Type 'help' for commands, 'history' for command history\n");
    printf("Use --generate-completion to create bash completion script\n\n");

    char input[256];
    while (1) {
        printf("cli> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Add to history
        add_to_history(input);

        if (strcmp(input, "quit") == 0) {
            break;
        } else if (strcmp(input, "help") == 0) {
            printf("Commands:\n");
            printf("  help     - Show this help\n");
            printf("  history  - Show command history\n");
            printf("  quit     - Exit\n");
        } else if (strcmp(input, "history") == 0) {
            show_history();
        } else if (strlen(input) > 0) {
            printf("Executing: %s\n", input);
            // Execute command here
        }
    }

    // Cleanup history
    for (int i = 0; i < history_count; i++) {
        free(command_history[i]);
    }

    printf("Goodbye!\n");
    return 0;
}
```

---

## 🎯 Best Practices

### **1. Validate Arguments**
```c
// ✅ Good
if (argc < 3) {
    fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
    return 1;
}

// ❌ Bad
// No validation - program may crash
```

### **2. Use Descriptive Option Names**
```c
// ✅ Good
#define VERBOSE_FLAG 'v'
#define INPUT_FILE 'i'

// ❌ Bad
#define A 'a'
#define B 'b'
```

### **3. Handle Errors Gracefully**
```c
// ✅ Good
FILE *file = fopen(argv[1], "r");
if (file == NULL) {
    perror("Error opening file");
    return 1;
}

// ❌ Bad
FILE *file = fopen(argv[1], "r");
// No error checking
```

### **4. Document Usage**
```c
// ✅ Good
void print_usage(char *program_name) {
    printf("Usage: %s [options] file\n", program_name);
    printf("Options:\n");
    printf("  -v    Verbose output\n");
    printf("  -h    Show help\n");
}

// ❌ Bad
// No usage information
```

---

## 🐛 Common Mistakes

### **1. Off-by-One with argc**
```c
// Wrong
for (int i = 0; i <= argc; i++) {  // Includes argv[argc] which is NULL
    printf("%s\n", argv[i]);
}

// Correct
for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
}
```

### **2. Not Checking optind**
```c
// Wrong - may access invalid memory
while ((opt = getopt(argc, argv, "i:o:")) != -1) {
    // Process options
}
// argv[optind] may be out of bounds

// Correct
while ((opt = getopt(argc, argv, "i:o:")) != -1) {
    // Process options
}
if (optind < argc) {
    // Process remaining arguments
}
```

### **3. atoi() Without Validation**
```c
// Wrong
int num = atoi(argv[1]);  // No error checking

// Correct
char *endptr;
int num = strtol(argv[1], &endptr, 10);
if (*endptr != '\0') {
    printf("Invalid number: %s\n", argv[1]);
    return 1;
}
```

### **4. Buffer Overflow with strcpy**
```c
// Wrong
char buffer[10];
strcpy(buffer, argv[1]);  // May overflow

// Correct
char buffer[100];
strncpy(buffer, argv[1], sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic Argument Processing**
- Create a program that accepts numbers as arguments and calculates their sum
- Build a program that reverses the order of command line arguments
- Implement a simple calculator that takes operation and operands as arguments

### **Exercise 2: Option Parsing**
- Create a file copy utility with options for verbose output and force overwrite
- Build a text processing tool with options for case conversion and word counting
- Implement a program that accepts multiple input files and processes them

### **Exercise 3: Environment Variables**
- Create a program that displays all environment variables
- Build a configuration system that reads from environment variables
- Implement a program that modifies environment variables

### **Exercise 4: Advanced Applications**
- Create a command-line task manager
- Build a file analysis tool with multiple options
- Implement a program that uses both command line arguments and environment variables

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What does `argc` represent in main function?
a) Array of command line arguments
b) Number of command line arguments
c) First command line argument
d) Program name

### **Question 2:**
Which function is used to get environment variables?
a) `getenv()`
b) `setenv()`
c) `putenv()`
d) `env()`

### **Question 3:**
What does `argv[0]` contain?
a) First command line argument
b) Program name
c) Number of arguments
d) NULL

### **Question 4:**
Which library function helps parse command line options?
a) `scanf()`
b) `getopt()`
c) `atoi()`
d) `strcpy()`

### **Question 5:**
What is the conventional exit code for successful program execution?
a) -1
b) 0
c) 1
d) 255

---

## 🔗 Additional Resources

### **Command Line Arguments**
- [Program Arguments](https://en.cppreference.com/w/c/language/main_function)
- [getopt Function](https://www.gnu.org/software/libc/manual/html_node/Getopt.html)
- [Environment Variables](https://en.cppreference.com/w/c/program/getenv)

### **Further Reading**
- [Command Line Interfaces](https://en.wikipedia.org/wiki/Command-line_interface)
- [POSIX Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)
- [Shell Scripting](https://www.gnu.org/software/bash/manual/bash.html)

---

## 🎯 Next Steps

**Great job!** You've mastered:
- ✅ Command line argument processing
- ✅ Advanced option parsing with getopt
- ✅ Environment variable handling
- ✅ Program exit codes
- ✅ Building command-line utilities

**Next Lesson Preview:**
- Error handling techniques
- Assertions and debugging
- Signal handling
- Exception-like mechanisms in C

---

**🚀 Ready to handle errors gracefully?**

[⬅️ Previous: Bitwise Programming](16_Bitwise_Programming.md) | [Next: Error Handling ➡️](18_Error_Handling.md)