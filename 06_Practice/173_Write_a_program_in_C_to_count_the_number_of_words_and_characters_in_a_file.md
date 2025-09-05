# 🎯 Practical 173: Count Words and Characters in File

## 📋 Problem Statement

Write a program in C to count the number of words and characters in a file.

## 🎯 Learning Objectives

- Understand text analysis in files
- Practice character and word counting
- Learn text processing techniques
- Understand file statistics
- Practice parsing algorithms

## 📝 Requirements

1. Accept filename from user
2. Read file contents
3. Count characters and words
4. Display statistics
5. Handle different text formats

## 💡 Hints

- Read file character by character
- Count all characters including spaces
- Use word boundary detection
- Handle punctuation and formatting
- Display comprehensive statistics

## 🔧 Solution

```c
// Practical 173: Count Words and Characters in File
// Demonstrates text analysis and counting in files

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char ch;
    int charCount = 0;
    int wordCount = 0;
    int inWord = 0;

    printf("Count Words and Characters in File\n");
    printf("===================================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        printf("Make sure the file exists and you have read permissions.\n");
        return 1;
    }

    // Read file character by character
    while ((ch = fgetc(filePointer)) != EOF) {
        charCount++;

        // Word counting logic
        if (isspace(ch) || ispunct(ch)) {
            if (inWord) {
                wordCount++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
    }

    // Handle case where file ends with a word
    if (inWord) {
        wordCount++;
    }

    // Check for read errors
    if (ferror(filePointer)) {
        printf("Error reading file!\n");
        fclose(filePointer);
        return 1;
    }

    // Close file
    fclose(filePointer);

    // Display results
    printf("\nFile Analysis Results:\n");
    printf("=====================\n");
    printf("Filename: %s\n", filename);
    printf("Total characters: %d\n", charCount);
    printf("Total words: %d\n", wordCount);

    if (charCount > 0) {
        printf("Average word length: %.1f characters\n", (float)charCount / wordCount);
    }

    if (wordCount == 0 && charCount == 0) {
        printf("Status: Empty file\n");
    } else if (wordCount == 0) {
        printf("Status: File contains no words (possibly only whitespace/punctuation)\n");
    } else {
        printf("Status: Analysis completed successfully\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Text File
```
File content: Hello world! This is a test file with multiple words.
Expected Output:
Filename: test.txt
Total characters: 52
Total words: 9
Average word length: 5.8 characters
Status: Analysis completed successfully
```

### Test Case 2: Single Word
```
File content: Hello
Expected Output:
Total characters: 5
Total words: 1
Average word length: 5.0 characters
```

### Test Case 3: Empty File
```
File content: (empty)
Expected Output:
Total characters: 0
Total words: 0
Status: Empty file
```

## 🔍 Explanation

1. **File Reading**: Open and read file character by character
2. **Character Counting**: Count all characters including spaces
3. **Word Detection**: Use whitespace and punctuation as word boundaries
4. **Statistics**: Calculate totals and averages
5. **Edge Cases**: Handle empty files and special characters

## 🎯 Key Concepts Covered

- File character reading
- Word boundary detection
- Text analysis algorithms
- Statistical calculations
- Error handling

## 🚀 Extensions

1. Count sentences and paragraphs
2. Find most frequent words
3. Analyze reading level
4. Handle different encodings