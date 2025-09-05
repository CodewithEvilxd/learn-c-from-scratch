# 🎯 Practical 100: Remove Character from String

## 📋 Problem Statement

Write a method in C which will remove any given character from a string.

## 🎯 Learning Objectives

- Understand string filtering
- Practice character removal
- Learn in-place string modification
- Understand string manipulation
- Practice conditional logic

## 📝 Requirements

1. Accept a string and character to remove
2. Remove all occurrences of the character
3. Modify string in-place
4. Display original and modified strings
5. Handle edge cases

## 💡 Hints

- Use two-pointer approach
- Skip characters that match
- Copy non-matching characters
- Null terminate result
- Handle multiple occurrences

## 🔧 Solution

```c
// Practical 100: Remove Character from String
// Removes all occurrences of a given character from a string

#include <stdio.h>
#include <string.h>

void removeCharacter(char *str, char ch) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ch) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null terminate
}

int main() {
    char str[1000], ch;

    printf("Remove Character from String\n");
    printf("=============================\n");

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
Input: String="Hello World", Character='l'
Expected Output:
Original string: "Hello World"
Modified string: "Heo Word"
```

### Test Case 2: Remove Space
```
Input: String="C Programming", Character=' '
Expected Output:
Original string: "C Programming"
Modified string: "CProgramming"
```

### Test Case 3: Character Not Found
```
Input: String="Hello", Character='z'
Expected Output:
Original string: "Hello"
Modified string: "Hello"
```

### Test Case 4: Remove All Occurrences
```
Input: String="banana", Character='a'
Expected Output:
Original string: "banana"
Modified string: "bnn"
```

## 🔍 Explanation

1. **Two-pointer Approach**: i for reading, j for writing
2. **Character Check**: Skip if matches character to remove
3. **Copy Operation**: Copy non-matching characters
4. **Null Termination**: Properly terminate modified string
5. **In-place Modification**: Modify original string

## 🎯 Key Concepts Covered

- String filtering
- In-place modification
- Two-pointer technique
- Character comparison
- String termination

## 🚀 Extensions

1. Remove multiple characters
2. Remove character at specific position
3. Remove all vowels
4. Remove all digits