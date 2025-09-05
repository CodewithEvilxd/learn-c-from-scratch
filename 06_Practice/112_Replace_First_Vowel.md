# 🎯 Practical 112: Replace First Vowel with '-'

## 📋 Problem Statement

Write a C program to Replace First Occurrence Of Vowel With '-'.

## 🎯 Learning Objectives

- Understand vowel identification
- Practice string modification
- Learn first occurrence replacement
- Understand loop control with break
- Practice character replacement

## 📝 Requirements

1. Accept a string input
2. Find first vowel (a,e,i,o,u,A,E,I,O,U)
3. Replace it with '-'
4. Display original and modified strings
5. Handle strings without vowels

## 💡 Hints

- Traverse string from left to right
- Check each character for vowel
- Replace first vowel found
- Use break to stop after first replacement
- Handle case insensitivity

## 🔧 Solution

```c
// Practical 112: Replace First Vowel with '-'
// Replaces the first occurrence of a vowel with '-'

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void replaceFirstVowel(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            str[i] = '-';
            break; // Stop after first replacement
        }
    }
}

int main() {
    char str[1000];

    printf("Replace First Vowel with '-'\n");
    printf("=============================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    replaceFirstVowel(str);

    printf("Modified string: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Vowel at Beginning
```
Input: apple
Expected Output:
Original string: "apple"
Modified string: "-pple"
```

### Test Case 2: Vowel in Middle
```
Input: computer
Expected Output:
Original string: "computer"
Modified string: "c-mputer"
```

### Test Case 3: No Vowels
```
Input: rhythm
Expected Output:
Original string: "rhythm"
Modified string: "rhythm"
```

### Test Case 4: Uppercase Vowel
```
Input: Apple
Expected Output:
Original string: "Apple"
Modified string: "-pple"
```

### Test Case 5: Multiple Vowels
```
Input: education
Expected Output:
Original string: "education"
Modified string: "-ducation"
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **Vowel Search**: Traverse from left to right
3. **First Occurrence**: Replace first vowel found
4. **Case Handling**: Check both uppercase and lowercase
5. **Break Statement**: Stop after first replacement

## 🎯 Key Concepts Covered

- String modification
- Vowel identification
- Loop control with break
- First occurrence replacement
- Case insensitivity

## 🚀 Extensions

1. Replace all vowels with '-'
2. Replace first consonant with '-'
3. Replace nth occurrence of vowel
4. Replace with different characters