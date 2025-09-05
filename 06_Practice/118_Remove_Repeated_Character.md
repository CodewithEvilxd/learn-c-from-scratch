# 🎯 Practical 118: Remove Repeated Character from String

## 📋 Problem Statement

Write a C program to remove repeated character from string.

## 🎯 Learning Objectives

- Understand duplicate removal
- Practice character tracking
- Learn frequency-based filtering
- Understand string compression
- Practice array usage for tracking

## 📝 Requirements

1. Accept a string input
2. Remove repeated characters
3. Keep only first occurrence
4. Display original and modified strings
5. Handle case sensitivity

## 💡 Hints

- Use frequency array or boolean array
- Track seen characters
- Copy only first occurrences
- Maintain original order
- Handle case sensitivity option

## 🔧 Solution

```c
// Practical 118: Remove Repeated Character from String
// Removes repeated characters, keeping only first occurrence

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeRepeatedChars(char *str, int case_sensitive) {
    int seen[256] = {0}; // Track seen characters
    int j = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = case_sensitive ? str[i] : tolower(str[i]);
        
        if (!seen[(unsigned char)ch]) {
            seen[(unsigned char)ch] = 1;
            str[j++] = str[i]; // Keep original case
        }
    }
    
    str[j] = '\0'; // Null terminate
}

int main() {
    char str[1000];
    int case_sensitive = 1;

    printf("Remove Repeated Character from String\n");
    printf("======================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Case sensitive? (1 for Yes, 0 for No): ");
    scanf("%d", &case_sensitive);

    printf("Original string: \"%s\"\n", str);

    removeRepeatedChars(str, case_sensitive);

    printf("String without repeated characters: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Case Sensitive
```
Input: Programming, Case=1
Expected Output:
Original string: "Programming"
String without repeated characters: "Progamin"
```

### Test Case 2: Case Insensitive
```
Input: Programming, Case=0
Expected Output:
Original string: "Programming"
String without repeated characters: "Progamin"
```

### Test Case 3: All Same Characters
```
Input: aaaa, Case=1
Expected Output:
Original string: "aaaa"
String without repeated characters: "a"
```

### Test Case 4: Mixed Case
```
Input: Hello World, Case=0
Expected Output:
Original string: "Hello World"
String without repeated characters: "Helo Wrd"
```

## 🔍 Explanation

1. **Character Tracking**: Use array to track seen characters
2. **Case Handling**: Option for case sensitivity
3. **First Occurrence**: Keep only first instance
4. **Order Preservation**: Maintain original character order
5. **In-place Modification**: Modify original string

## 🎯 Key Concepts Covered

- Duplicate removal
- Character tracking
- Case sensitivity handling
- Array-based solutions
- String compression

## 🚀 Extensions

1. Remove all duplicates (keep none)
2. Remove only specific character duplicates
3. Count removed duplicates
4. Handle Unicode characters