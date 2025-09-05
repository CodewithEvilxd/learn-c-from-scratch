# 🎯 Practical 114: Separate Characters in String

## 📋 Problem Statement

Write a C program to separate characters in a given string.

## 🎯 Learning Objectives

- Understand string parsing
- Practice character extraction
- Learn string manipulation
- Understand character separation
- Practice formatted output

## 📝 Requirements

1. Accept a string input
2. Separate each character
3. Display characters individually
4. Show ASCII values
5. Provide clear formatting

## 💡 Hints

- Traverse string character by character
- Display each character separately
- Show position and ASCII value
- Handle spaces and special characters
- Format output clearly

## 🔧 Solution

```c
// Practical 114: Separate Characters in String
// Displays each character of the string separately

#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];

    printf("Separate Characters in String\n");
    printf("==============================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);
    printf("String length: %lu characters\n", strlen(str));

    printf("\nCharacter Separation:\n");
    printf("--------------------\n");

    // Display each character separately
    for (int i = 0; str[i] != '\0'; i++) {
        printf("Position %d: ", i + 1);
        
        if (str[i] == ' ') {
            printf("' ' (space)");
        } else if (str[i] == '\t') {
            printf("'\\t' (tab)");
        } else if (str[i] == '\n') {
            printf("'\\n' (newline)");
        } else if (str[i] >= 32 && str[i] <= 126) {
            printf("'%c'", str[i]);
        } else {
            printf("Non-printable character");
        }
        
        printf(" | ASCII: %d", str[i]);
        
        // Show hexadecimal representation
        printf(" | Hex: 0x%02X", (unsigned char)str[i]);
        
        printf("\n");
    }

    // Summary
    printf("\nSummary:\n");
    printf("--------\n");
    int alphabets = 0, digits = 0, spaces = 0, special = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) alphabets++;
        else if (isdigit(str[i])) digits++;
        else if (isspace(str[i])) spaces++;
        else special++;
    }
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);
    printf("Special Characters: %d\n", special);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal String
```
Input: Hello
Expected Output:
Position 1: 'H' | ASCII: 72 | Hex: 0x48
Position 2: 'e' | ASCII: 101 | Hex: 0x65
Position 3: 'l' | ASCII: 108 | Hex: 0x6C
Position 4: 'l' | ASCII: 108 | Hex: 0x6C
Position 5: 'o' | ASCII: 111 | Hex: 0x6F
```

### Test Case 2: String with Spaces
```
Input: C Programming
Expected Output:
Position 1: 'C' | ASCII: 67 | Hex: 0x43
Position 2: ' ' (space) | ASCII: 32 | Hex: 0x20
Position 3: 'P' | ASCII: 80 | Hex: 0x50
...
```

### Test Case 3: Mixed Characters
```
Input: A1@#
Expected Output:
Position 1: 'A' | ASCII: 65 | Hex: 0x41
Position 2: '1' | ASCII: 49 | Hex: 0x31
Position 3: '@' | ASCII: 64 | Hex: 0x40
Position 4: '#' | ASCII: 35 | Hex: 0x23
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **Character Separation**: Display each character individually
3. **Position Tracking**: Show position in string
4. **ASCII Display**: Show decimal ASCII value
5. **Hex Display**: Show hexadecimal representation
6. **Special Characters**: Handle spaces, tabs, etc.

## 🎯 Key Concepts Covered

- String traversal
- Character analysis
- ASCII representation
- Hexadecimal conversion
- Position tracking

## 🚀 Extensions

1. Separate by character type
2. Reverse character order
3. Group similar characters
4. Analyze character patterns