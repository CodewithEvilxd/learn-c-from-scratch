# 🎯 Practical 107: Lowercase to Uppercase

## 📋 Problem Statement

Write a C program to convert lowercase char to uppercase of string.

## 🎯 Learning Objectives

- Understand case conversion
- Practice ASCII manipulation
- Learn toupper() function
- Understand character arithmetic
- Practice string modification

## 📝 Requirements

1. Accept a string input
2. Convert lowercase to uppercase
3. Modify string in-place
4. Display original and converted strings
5. Handle mixed case strings

## 💡 Hints

- Use toupper() function
- Manual conversion: ch - 32
- Check if character is lowercase
- Traverse entire string
- Handle non-alphabet characters

## 🔧 Solution

```c
// Practical 107: Lowercase to Uppercase
// Converts all lowercase characters to uppercase in a string

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convertToUppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    char str[1000];

    printf("Lowercase to Uppercase Converter\n");
    printf("=================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    convertToUppercase(str);

    printf("Uppercase string: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Case
```
Input: Hello World
Expected Output:
Original string: "Hello World"
Uppercase string: "HELLO WORLD"
```

### Test Case 2: All Lowercase
```
Input: programming
Expected Output:
Original string: "programming"
Uppercase string: "PROGRAMMING"
```

### Test Case 3: All Uppercase
```
Input: COMPUTER
Expected Output:
Original string: "COMPUTER"
Uppercase string: "COMPUTER"
```

### Test Case 4: Mixed Characters
```
Input: C Programming 123!
Expected Output:
Original string: "C Programming 123!"
Uppercase string: "C PROGRAMMING 123!"
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **toupper() Function**: Convert each character
3. **In-place Modification**: Modify original string
4. **All Characters**: Process entire string
5. **Preserve Non-letters**: Numbers and symbols unchanged

## 🎯 Key Concepts Covered

- Case conversion
- Character functions
- String modification
- ASCII manipulation
- Library functions

## 🚀 Extensions

1. Convert uppercase to lowercase
2. Toggle case of each character
3. Convert only vowels
4. Handle specific character ranges