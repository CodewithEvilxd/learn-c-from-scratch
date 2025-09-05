# 🎯 Practical 96: String Concatenation

## 📋 Problem Statement

Write a C program to concatenate two strings.

## 🎯 Learning Objectives

- Understand string concatenation
- Practice string manipulation
- Learn manual concatenation
- Understand string termination
- Practice array bounds checking

## 📝 Requirements

1. Accept two strings
2. Concatenate them manually
3. Compare with library function
4. Handle buffer overflow
5. Display results clearly

## 💡 Hints

- Find end of first string
- Copy second string after first
- Ensure proper null termination
- Check buffer size
- Use strcat() for comparison

## 🔧 Solution

```c
// Practical 96: String Concatenation
// Concatenates two strings manually and using library function

#include <stdio.h>
#include <string.h>

void concatenateStrings(char *dest, const char *src, size_t dest_size) {
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    
    // Check if concatenation would overflow
    if (dest_len + src_len >= dest_size) {
        printf("Warning: Concatenation would overflow buffer!\n");
        return;
    }
    
    // Find end of destination string
    size_t i = dest_len;
    
    // Copy source string
    for (size_t j = 0; src[j] != '\0'; j++) {
        dest[i++] = src[j];
    }
    
    // Null terminate
    dest[i] = '\0';
}

int main() {
    char str1[100], str2[100], result[200];

    printf("String Concatenation\n");
    printf("====================\n");

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    
    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);

    // Remove newline characters
    if (str1[strlen(str1) - 1] == '\n') {
        str1[strlen(str1) - 1] = '\0';
    }
    if (str2[strlen(str2) - 1] == '\n') {
        str2[strlen(str2) - 1] = '\0';
    }

    printf("\nOriginal strings:\n");
    printf("String 1: \"%s\"\n", str1);
    printf("String 2: \"%s\"\n", str2);

    // Manual concatenation
    strcpy(result, str1); // Copy first string
    concatenateStrings(result, str2, sizeof(result));

    printf("\nManual concatenation: \"%s\"\n", result);

    // Using library function
    char lib_result[200];
    strcpy(lib_result, str1);
    strcat(lib_result, str2);

    printf("Library function: \"%s\"\n", lib_result);

    // Verify results match
    if (strcmp(result, lib_result) == 0) {
        printf("✓ Results match!\n");
    } else {
        printf("✗ Results differ!\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Strings
```
Input: Hello, World
Expected Output:
Manual concatenation: "HelloWorld"
Library function: "HelloWorld"
✓ Results match!
```

### Test Case 2: Empty First String
```
Input: (empty), Programming
Expected Output:
Manual concatenation: "Programming"
Library function: "Programming"
✓ Results match!
```

### Test Case 3: Empty Second String
```
Input: Hello, (empty)
Expected Output:
Manual concatenation: "Hello"
Library function: "Hello"
✓ Results match!
```

## 🔍 Explanation

1. **Manual Method**: Find end of first string, copy second string
2. **Buffer Check**: Prevent overflow
3. **Null Termination**: Properly terminate result
4. **Library Comparison**: Use strcat() for verification
5. **Result Validation**: Ensure both methods produce same result

## 🎯 Key Concepts Covered

- String concatenation
- Buffer management
- Null termination
- Library function usage
- Manual string operations

## 🚀 Extensions

1. Concatenate multiple strings
2. Add separator between strings
3. Handle very long strings
4. Concatenate with formatting