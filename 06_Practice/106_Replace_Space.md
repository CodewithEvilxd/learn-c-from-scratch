# 🎯 Practical 106: Replace Space with Character

## 📋 Problem Statement

Write a C program to replace the string space with a given character.

## 🎯 Learning Objectives

- Understand string replacement
- Practice character substitution
- Learn in-place modification
- Understand space handling
- Practice string traversal

## 📝 Requirements

1. Accept a string and replacement character
2. Replace all spaces with the character
3. Modify string in-place
4. Display original and modified strings
5. Handle multiple spaces

## 💡 Hints

- Traverse string and find spaces
- Replace ' ' with given character
- Use loop for all occurrences
- Handle edge cases
- Clear output display

## 🔧 Solution

```c
// Practical 106: Replace Space with Character
// Replaces all spaces in a string with a given character

#include <stdio.h>
#include <string.h>

void replaceSpaces(char *str, char replacement) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main() {
    char str[1000], replacement;

    printf("Replace Space with Character\n");
    printf("=============================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Enter replacement character: ");
    scanf("%c", &replacement);

    printf("Original string: \"%s\"\n", str);

    replaceSpaces(str, replacement);

    printf("Modified string: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multiple Spaces
```
Input: String="Hello World", Character='_'
Expected Output:
Original string: "Hello World"
Modified string: "Hello_World"
```

### Test Case 2: Leading and Trailing Spaces
```
Input: String="  C Programming  ", Character='*'
Expected Output:
Original string: "  C Programming  "
Modified string: "**C*Programming**"
```

### Test Case 3: No Spaces
```
Input: String="Hello", Character='_'
Expected Output:
Original string: "Hello"
Modified string: "Hello"
```

### Test Case 4: All Spaces
```
Input: String="   ", Character='X'
Expected Output:
Original string: "   "
Modified string: "XXX"
```

## 🔍 Explanation

1. **String Input**: Accept string with spaces
2. **Character Input**: Get replacement character
3. **Space Replacement**: Loop and replace ' ' with character
4. **In-place Modification**: Modify original string
5. **Display Results**: Show before and after

## 🎯 Key Concepts Covered

- String modification
- Character replacement
- Loop implementation
- Space handling
- In-place operations

## 🚀 Extensions

1. Replace multiple characters
2. Replace specific words
3. Case-sensitive replacement
4. Replace with string instead of character