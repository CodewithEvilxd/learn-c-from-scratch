# 🎯 Practical 94: Remove Non-Alphabets from String

## 📋 Problem Statement

Write a C program to remove all characters in a string except alphabets.

## 🎯 Learning Objectives

- Understand string filtering
- Practice character validation
- Learn in-place string modification
- Understand isalpha() function
- Practice string manipulation

## 📝 Requirements

1. Accept a string input
2. Remove all non-alphabet characters
3. Keep only A-Z and a-z
4. Modify string in-place
5. Display original and filtered strings

## 💡 Hints

- Use isalpha() to check alphabets
- Use two-pointer approach
- Copy only alphabet characters
- Null terminate the result
- Preserve case of alphabets

## 🔧 Solution

```c
// Practical 94: Remove Non-Alphabets from String
// Filters string to keep only alphabet characters

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void removeNonAlphabets(char *str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null terminate
}

int main() {
    char str[1000];

    printf("Remove Non-Alphabets from String\n");
    printf("=================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    removeNonAlphabets(str);

    printf("Filtered string: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Characters
```
Input: Hello123 World!
Expected Output:
Original string: "Hello123 World!"
Filtered string: "HelloWorld"
```

### Test Case 2: Only Non-Alphabets
```
Input: 123@#$%
Expected Output:
Original string: "123@#$%"
Filtered string: ""
```

### Test Case 3: Only Alphabets
```
Input: Programming
Expected Output:
Original string: "Programming"
Filtered string: "Programming"
```

### Test Case 4: Mixed Case
```
Input: C Programming 2024!
Expected Output:
Original string: "C Programming 2024!"
Filtered string: "CProgramming"
```

## 🔍 Explanation

1. **Character Filtering**: Use isalpha() to identify alphabets
2. **In-place Modification**: Modify original string
3. **Two-pointer Approach**: i for reading, j for writing
4. **Case Preservation**: Keep original case of alphabets
5. **Null Termination**: Properly terminate filtered string

## 🎯 Key Concepts Covered

- String filtering
- Character validation functions
- In-place string modification
- Two-pointer technique
- String termination

## 🚀 Extensions

1. Remove only specific character types
2. Keep digits along with alphabets
3. Convert case while filtering
4. Count removed characters