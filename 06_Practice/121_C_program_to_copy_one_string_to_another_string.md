# 🎯 Practical 121: Copy One String to Another String

## 📋 Problem Statement

Write a C program to copy one string to another string.

## 🎯 Learning Objectives

- Understand string manipulation
- Practice string copying techniques
- Learn manual string copying
- Understand null termination
- Practice memory management

## 📝 Requirements

1. Accept a source string input
2. Create a destination string
3. Copy all characters from source to destination
4. Ensure null termination
5. Display both strings

## 💡 Hints

- Use character-by-character copying
- Include null terminator
- Use loop for copying
- Handle string length properly
- Test with different string lengths

## 🔧 Solution

```c
// Practical 121: Copy One String to Another String
// Demonstrates manual string copying

#include <stdio.h>
#include <string.h>

void copyString(char *dest, const char *src) {
    int i = 0;
    
    // Copy character by character
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    // Add null terminator
    dest[i] = '\0';
}

int main() {
    char source[1000];
    char destination[1000];

    printf("String Copy Program\n");
    printf("===================\n");

    printf("Enter a string: ");
    fgets(source, sizeof(source), stdin);

    // Remove newline character if present
    if (source[strlen(source) - 1] == '\n') {
        source[strlen(source) - 1] = '\0';
    }

    // Copy string
    copyString(destination, source);

    printf("Source string: \"%s\"\n", source);
    printf("Copied string: \"%s\"\n", destination);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Simple String
```
Input: Hello World
Expected Output:
Source string: "Hello World"
Copied string: "Hello World"
```

### Test Case 2: Empty String
```
Input: (empty)
Expected Output:
Source string: ""
Copied string: ""
```

### Test Case 3: Special Characters
```
Input: C@Programming#123
Expected Output:
Source string: "C@Programming#123"
Copied string: "C@Programming#123"
```

## 🔍 Explanation

1. **Input Reading**: Read source string from user
2. **Manual Copying**: Copy each character individually
3. **Null Termination**: Ensure destination is properly terminated
4. **Output Display**: Show both original and copied strings

## 🎯 Key Concepts Covered

- String manipulation
- Character arrays
- Loop-based copying
- Null termination
- Memory handling

## 🚀 Extensions

1. Use strcpy() function
2. Implement string concatenation
3. Handle memory allocation
4. Copy partial strings