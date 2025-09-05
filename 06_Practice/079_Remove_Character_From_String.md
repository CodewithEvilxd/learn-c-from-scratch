# 🎯 Practical 79: Remove Character From String

## 📋 Problem Statement

Write a method in C that will remove any given character from a string.

## 🎯 Learning Objectives

- Understand string manipulation
- Practice character removal
- Learn string traversal
- Understand in-place modification
- Practice pointer usage

## 📝 Requirements

1. Accept a string and character to remove
2. Remove all occurrences of the character
3. Modify string in-place
4. Display original and modified strings
5. Handle edge cases

## 💡 Hints

- Use two pointers or index variables
- Traverse string and copy non-matching characters
- Null terminate the result
- Handle empty string
- Case-sensitive removal

## 🔧 Solution

```c
// Practical 79: Remove Character From String
// Removes all occurrences of a character from a string

#include <stdio.h>
#include <string.h>

// Function to remove character from string
void removeCharacter(char *str, char ch) {
    int i, j = 0;
    int length = strlen(str);
    
    for (i = 0; i < length; i++) {
        if (str[i] != ch) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null terminate
}

int main() {
    char str[100], ch;
    
    printf("Remove Character From String\n");
    printf("============================\n");
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    
    printf("Enter character to remove: ");
    scanf("%c", &ch);
    
    printf("Original string: \"%s\"\n", str);
    
    removeCharacter(str, ch);
    
    printf("Modified string: \"%s\"\n", str);
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Remove Single Character
```
Input String: Hello World
Character: l
Expected Output:
Original: "Hello World"
Modified: "Heo Word"
```

### Test Case 2: Remove Multiple Characters
```
Input String: Programming
Character: m
Expected Output:
Original: "Programming"
Modified: "Prograing"
```

### Test Case 3: Character Not Found
```
Input String: Hello
Character: z
Expected Output:
Original: "Hello"
Modified: "Hello"
```

## 🔍 Explanation

1. **Two Pointer Approach**: i for reading, j for writing
2. **Character Check**: Only copy non-matching characters
3. **In-place Modification**: Modify original string
4. **Null Termination**: Properly terminate result string
5. **Edge Cases**: Handle empty strings, character not found

## 🎯 Key Concepts Covered

- String manipulation
- Character removal
- In-place modification
- Pointer usage
- String termination

## 🚀 Extensions

1. Remove all occurrences of multiple characters
2. Remove character at specific position
3. Remove substring from string
4. Case-insensitive removal