# 🎯 Practical 174: List Files and Sub-directories in Directory

## 📋 Problem Statement

C Program to list all files and sub-directories in a directory.

## 🎯 Learning Objectives

- Understand directory operations
- Practice file system navigation
- Learn directory entry reading
- Understand file attributes
- Practice system-level programming

## 📝 Requirements

1. Accept directory path from user
2. Open directory for reading
3. List all files and subdirectories
4. Display file information
5. Handle directory access errors

## 💡 Hints

- Use opendir and readdir functions
- Check entry types (file/directory)
- Display file names and types
- Handle permission errors
- Close directory properly

## 🔧 Solution

```c
// Practical 174: List Files and Sub-directories in Directory
// Demonstrates directory reading and file system navigation

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void listDirectory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char fullPath[1024];
    int fileCount = 0, dirCount = 0;

    // Open directory
    dir = opendir(path);

    if (dir == NULL) {
        printf("Error opening directory '%s'!\n", path);
        printf("Make sure the directory exists and you have read permissions.\n");
        return;
    }

    printf("Contents of directory: %s\n", path);
    printf("================================\n");

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Create full path for stat
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        if (stat(fullPath, &fileStat) == 0) {
            if (S_ISDIR(fileStat.st_mode)) {
                printf("[DIR]  %s/\n", entry->d_name);
                dirCount++;
            } else if (S_ISREG(fileStat.st_mode)) {
                printf("[FILE] %s\n", entry->d_name);
                fileCount++;
            } else {
                printf("[OTHER] %s\n", entry->d_name);
            }
        } else {
            printf("[ERROR] %s (cannot access)\n", entry->d_name);
        }
    }

    // Close directory
    closedir(dir);

    // Display summary
    printf("\nSummary:\n");
    printf("========\n");
    printf("Files: %d\n", fileCount);
    printf("Directories: %d\n", dirCount);
    printf("Total items: %d\n", fileCount + dirCount);
}

int main() {
    char path[512];

    printf("List Files and Sub-directories in Directory\n");
    printf("===========================================\n");

    printf("Enter directory path: ");
    fgets(path, sizeof(path), stdin);

    // Remove newline character
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }

    // Use current directory if empty
    if (strlen(path) == 0) {
        strcpy(path, ".");
    }

    listDirectory(path);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Current Directory
```
Input: .
Expected Output:
Contents of directory: .
================================
[DIR]  src/
[DIR]  include/
[FILE] main.c
[FILE] README.md

Summary:
========
Files: 2
Directories: 2
Total items: 4
```

### Test Case 2: Specific Directory
```
Input: /home/user
Expected Output:
Contents of directory: /home/user
================================
[DIR]  Documents/
[DIR]  Downloads/
[FILE] .bashrc
```

## 🔍 Explanation

1. **Directory Opening**: Use opendir to access directory
2. **Entry Reading**: Use readdir to read directory entries
3. **Type Checking**: Use stat to determine file types
4. **Display**: Show files and directories with types
5. **Summary**: Count and display totals

## 🎯 Key Concepts Covered

- Directory operations
- File system navigation
- File attribute checking
- System calls
- Directory entry handling

## 🚀 Extensions

1. Recursive directory listing
2. Filter by file type
3. Sort directory contents
4. Show file sizes and permissions