# 🎯 Practical 120: Non-Repeating Characters in String

## 📋 Problem Statement

Write a C program to print all non-repeating character in string.

## 🎯 Learning Objectives

- Understand character frequency analysis
- Practice uniqueness detection
- Learn frequency counting techniques
- Understand character filtering
- Practice conditional output

## 📝 Requirements

1. Accept a string input
2. Find characters that appear only once
3. Display all non-repeating characters
4. Maintain original order
5. Handle case sensitivity

## 💡 Hints

- Use frequency array to count occurrences
- Traverse string to mark frequencies
- Second pass to find characters with count 1
- Preserve original character order
- Handle case sensitivity option

## 🔧 Solution

```c
// Practical 120: Non-Repeating Characters in String
// Finds and displays all characters that appear only once

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void printNonRepeatingChars(char *str, int case_sensitive) {
    int frequency[256] = {0};
    
    // Count frequency of each character
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = case_sensitive ? str[i] : tolower(str[i]);
        frequency[(unsigned char)ch]++;
    }
    
    printf("Non-repeating characters: ");
    
    // Find and print non-repeating characters
    int found = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = case_sensitive ? str[i] : tolower(str[i]);
        
        if (frequency[(unsigned char)ch] == 1) {
            printf("%c ", str[i]); // Print original case
            found = 1;
        }
    }
    
    if (!found) {
        printf("None");
    }
    printf("\n");
}

int main() {
    char str[1000];
    int case_sensitive = 1;

    printf("Non-Repeating Characters in String\n");
    printf("===================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Case sensitive? (1 for Yes, 0 for No): ");
    scanf("%d", &case_sensitive);

    printf("String: \"%s\"\n", str);

    printNonRepeatingChars(str, case_sensitive);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Case Sensitive
```
Input: Programming, Case=1
Expected Output:
String: "Programming"
Non-repeating characters: P o g a i n
```

### Test Case 2: Case Insensitive
```
Input: Programming, Case=0
Expected Output:
String: "Programming"
Non-repeating characters: P o g a i n
```

### Test Case 3: All Repeating
```
Input: aabbcc, Case=1
Expected Output:
String: "aabbcc"
Non-repeating characters: None
```

### Test Case 4: Mixed Characters
```
Input: Hello World, Case=1
Expected Output:
String: "Hello World"
Non-repeating characters: H e o W r d
```

## 🔍 Explanation

1. **Frequency Counting**: Count occurrences of each character
2. **Case Handling**: Option for case sensitivity
3. **Uniqueness Check**: Find characters with count = 1
4. **Order Preservation**: Maintain original string order
5. **Output Formatting**: Clear display of results

## 🎯 Key Concepts Covered

- Frequency analysis
- Character uniqueness
- Case sensitivity handling
- Array-based counting
- Conditional output

## 🚀 Extensions

1. Print positions of non-repeating characters
2. Find first non-repeating character
3. Count total non-repeating characters
4. Handle Unicode characters