# 🎯 Assignment 1.7: String Operations in C

## 📋 Problem Statement

Create a C program that demonstrates various string operations including input, manipulation, searching, and comparison. Implement functions for string length, copy, concatenation, reversal, and palindrome checking.

## 🎯 Learning Objectives

- Understand string declaration and initialization
- Learn string input/output functions
- Implement string manipulation algorithms
- Practice character array operations
- Understand null termination
- Work with string library functions

## 📝 Requirements

1. Accept string input from user
2. Calculate string length manually and with library
3. Implement string copy and concatenation
4. Reverse a string
5. Check if string is palindrome
6. Search for substring
7. Compare strings
8. Convert case (upper/lower)

## 💡 Hints

- Strings are null-terminated character arrays
- Use `fgets()` for safe string input
- Implement manual algorithms before using library functions
- Check for buffer overflow
- Handle empty strings properly

## 🔧 Solution

```c
// Assignment 1.7: String Operations in C
// Comprehensive string manipulation program

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LENGTH 100

// Function prototypes
int string_length(const char* str);
void string_copy(char* dest, const char* src);
void string_concat(char* dest, const char* src);
void string_reverse(char* str);
bool is_palindrome(const char* str);
int string_compare(const char* str1, const char* str2);
void to_uppercase(char* str);
void to_lowercase(char* str);
int substring_search(const char* text, const char* pattern);

int main() {
    char str1[MAX_LENGTH], str2[MAX_LENGTH];
    char result[MAX_LENGTH * 2];

    // Get user input
    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';  // Remove newline

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';  // Remove newline

    printf("\n=== String Analysis ===\n");
    printf("String 1: \"%s\"\n", str1);
    printf("String 2: \"%s\"\n", str2);

    // String length
    printf("\nManual length of string 1: %d\n", string_length(str1));
    printf("Library length of string 1: %lu\n", strlen(str1));

    // String copy
    char copied[MAX_LENGTH];
    string_copy(copied, str1);
    printf("Copied string: \"%s\"\n", copied);

    // String concatenation
    string_copy(result, str1);
    string_concat(result, " ");
    string_concat(result, str2);
    printf("Concatenated: \"%s\"\n", result);

    // String reversal
    char reversed[MAX_LENGTH];
    string_copy(reversed, str1);
    string_reverse(reversed);
    printf("Reversed string 1: \"%s\"\n", reversed);

    // Palindrome check
    if (is_palindrome(str1)) {
        printf("String 1 is a palindrome\n");
    } else {
        printf("String 1 is not a palindrome\n");
    }

    // String comparison
    int cmp_result = string_compare(str1, str2);
    if (cmp_result == 0) {
        printf("Strings are equal\n");
    } else if (cmp_result < 0) {
        printf("String 1 comes before string 2\n");
    } else {
        printf("String 1 comes after string 2\n");
    }

    // Case conversion
    char upper[MAX_LENGTH], lower[MAX_LENGTH];
    string_copy(upper, str1);
    string_copy(lower, str1);
    to_uppercase(upper);
    to_lowercase(lower);
    printf("Uppercase: \"%s\"\n", upper);
    printf("Lowercase: \"%s\"\n", lower);

    // Substring search
    int position = substring_search(str1, str2);
    if (position != -1) {
        printf("Substring found at position %d\n", position);
    } else {
        printf("Substring not found\n");
    }

    return 0;
}

// Manual string length calculation
int string_length(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Manual string copy
void string_copy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Manual string concatenation
void string_concat(char* dest, const char* src) {
    int dest_len = string_length(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

// String reversal
void string_reverse(char* str) {
    int len = string_length(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Palindrome check
bool is_palindrome(const char* str) {
    int len = string_length(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

// String comparison
int string_compare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

// Convert to uppercase
void to_uppercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

// Convert to lowercase
void to_lowercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

// Substring search
int substring_search(const char* text, const char* pattern) {
    int text_len = string_length(text);
    int pattern_len = string_length(pattern);

    if (pattern_len == 0) return 0;
    if (pattern_len > text_len) return -1;

    for (int i = 0; i <= text_len - pattern_len; i++) {
        bool found = true;
        for (int j = 0; j < pattern_len; j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }

    return -1;
}
```

## 📊 Test Cases

### Test Case 1: Basic Operations
```
Input: "Hello", "World"
Expected Output:
Manual length: 5
Concatenated: "Hello World"
Reversed: "olleH"
```

### Test Case 2: Palindrome Check
```
Input: "radar"
Expected Output: String is a palindrome
```

### Test Case 3: Case Conversion
```
Input: "Hello World"
Expected Output:
Uppercase: "HELLO WORLD"
Lowercase: "hello world"
```

### Test Case 4: Substring Search
```
Text: "Hello World"
Pattern: "World"
Expected Output: Substring found at position 6
```

## 🔍 Explanation

1. **String Input**: Using `fgets()` for safe input with buffer size
2. **Null Termination**: All strings end with `\0` character
3. **Manual Implementation**: Writing functions without standard library
4. **Character Processing**: Using loops to process each character
5. **Buffer Management**: Careful handling to prevent overflow
6. **Return Values**: Functions return appropriate values

## 🎯 Key Concepts Covered

- String declaration and initialization
- Character array manipulation
- String termination with null character
- Manual string algorithms
- Safe string input handling
- String comparison and searching

## 🚀 Extensions

1. Implement string tokenization (split)
2. Add string compression algorithms
3. Create string formatting functions
4. Implement pattern matching with wildcards