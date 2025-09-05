# 🎯 Practical 37: Alphabet Checker

## 📋 Problem Statement

Write a C program to check whether a character is an alphabet or not.

## 🎯 Learning Objectives

- Understand character classification
- Practice conditional statements
- Learn ASCII ranges
- Understand ctype functions
- Practice input validation

## 📝 Requirements

1. Accept character input
2. Check if alphabet
3. Handle case sensitivity
4. Display result
5. Clear output

## 💡 Hints

- Use isalpha() from ctype.h
- Check ranges A-Z, a-z
- Handle single character
- Clear messages
- Validate input

## 🔧 Solution

```c
// Practical 37: Alphabet Checker
// Checks if a character is an alphabet

#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;

    printf("Alphabet Checker\n");
    printf("================\n");

    printf("Enter a character: ");
    scanf("%c", &ch);

    if (isalpha(ch)) {
        printf("'%c' is an alphabet.\n", ch);
        if (isupper(ch)) {
            printf("It is an uppercase letter.\n");
        } else {
            printf("It is a lowercase letter.\n");
        }
    } else {
        printf("'%c' is not an alphabet.\n", ch);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Uppercase Letter
```
Input: A
Expected Output:
'A' is an alphabet.
It is an uppercase letter.
```

### Test Case 2: Lowercase Letter
```
Input: z
Expected Output:
'z' is an alphabet.
It is a lowercase letter.
```

### Test Case 3: Non-Alphabet
```
Input: 5
Expected Output:
'5' is not an alphabet.
```

## 🔍 Explanation

1. **isalpha()**: Checks if character is letter
2. **isupper()**: Checks uppercase
3. **islower()**: Checks lowercase
4. **Input**: Single character
5. **Output**: Classification result

## 🎯 Key Concepts Covered

- Character classification
- ctype functions
- Conditional statements
- Input handling
- ASCII ranges

## 🚀 Extensions

1. Check for vowels
2. Convert case
3. Check multiple characters
4. Add ASCII value display