# 🎯 Practical 154: Write a Sentence to a File

## 📋 Problem Statement

C Program to Write a Sentence to a File.

## 🎯 Learning Objectives

- Understand file I/O operations
- Practice file opening and closing
- Learn fprintf function usage
- Understand file modes
- Practice error handling

## 📝 Requirements

1. Accept a sentence from user
2. Open/create a file for writing
3. Write the sentence to file
4. Close the file properly
5. Display success message

## 💡 Hints

- Use fopen with "w" mode
- Use fprintf to write to file
- Check if file opened successfully
- Close file with fclose
- Handle file operation errors

## 🔧 Solution

```c
// Practical 154: Write a Sentence to a File
// Demonstrates basic file writing operations

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *filePointer;
    char sentence[1000];
    char filename[100];

    printf("Write a Sentence to a File\n");
    printf("==========================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Clear input buffer
    getchar();

    printf("Enter a sentence to write: ");
    fgets(sentence, sizeof(sentence), stdin);

    // Remove newline character if present
    if (sentence[strlen(sentence) - 1] == '\n') {
        sentence[strlen(sentence) - 1] = '\0';
    }

    // Open file for writing
    filePointer = fopen(filename, "w");

    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write sentence to file
    fprintf(filePointer, "%s", sentence);

    // Close file
    fclose(filePointer);

    printf("Sentence written to file successfully!\n");
    printf("File: %s\n", filename);
    printf("Content: %s\n", sentence);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Writing
```
Input: Filename: test.txt, Sentence: Hello World!
Expected Output:
Sentence written to file successfully!
File: test.txt
Content: Hello World!
```

### Test Case 2: Long Sentence
```
Input: Filename: story.txt, Sentence: This is a long sentence with many words.
Expected Output:
Sentence written to file successfully!
File: story.txt
Content: This is a long sentence with many words.
```

### Test Case 3: Special Characters
```
Input: Filename: special.txt, Sentence: Hello @ World # 123!
Expected Output:
Sentence written to file successfully!
File: special.txt
Content: Hello @ World # 123!
```

## 🔍 Explanation

1. **Input Reading**: Get filename and sentence from user
2. **File Opening**: Open file in write mode
3. **Error Checking**: Verify file opened successfully
4. **Writing**: Use fprintf to write sentence to file
5. **File Closing**: Close file and free resources

## 🎯 Key Concepts Covered

- File I/O operations
- fopen and fclose functions
- fprintf function
- Error handling
- File modes

## 🚀 Extensions

1. Append to existing file
2. Write multiple lines
3. Write formatted data
4. Handle file overwrite confirmation