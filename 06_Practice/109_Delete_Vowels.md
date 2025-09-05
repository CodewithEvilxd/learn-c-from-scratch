# 🎯 Practical 109: Delete Vowels from String

## 📋 Problem Statement

Write a C program to delete vowels in a given string.

## 🎯 Learning Objectives

- Understand vowel removal
- Practice selective character deletion
- Learn two-pointer technique
- Understand string compression
- Practice character identification

## 📝 Requirements

1. Accept a string input
2. Remove all vowels (a,e,i,o,u,A,E,I,O,U)
3. Modify string in-place
4. Display original and modified strings
5. Handle case insensitivity

## 💡 Hints

- Use two-pointer approach
- Check for both cases of vowels
- Copy non-vowel characters
- Null terminate result
- Handle empty strings

## 🔧 Solution

```c
// Practical 109: Delete Vowels from String
// Removes all vowels from a string

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void deleteVowels(char *str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);
        // Check if character is not a vowel
        if (ch != 'a' && ch != 'e' && ch != 'i' && ch != 'o' && ch != 'u') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null terminate
}

int main() {
    char str[1000];

    printf("Delete Vowels from String\n");
    printf("=========================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    deleteVowels(str);

    printf("String without vowels: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Vowels and Consonants
```
Input: Hello World
Expected Output:
Original string: "Hello World"
String without vowels: "Hll Wrld"
```

### Test Case 2: All Vowels
```
Input: AEIOUaeiou
Expected Output:
Original string: "AEIOUaeiou"
String without vowels: ""
```

### Test Case 3: No Vowels
```
Input: Rhythm
Expected Output:
Original string: "Rhythm"
String without vowels: "Rhythm"
```

### Test Case 4: Numbers and Special Characters
```
Input: C Programming 123!
Expected Output:
Original string: "C Programming 123!"
String without vowels: "C Prgrmmng 123!"
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **Vowel Check**: Identify a,e,i,o,u (both cases)
3. **Two-pointer Method**: Copy non-vowel characters
4. **Case Insensitive**: Convert to lowercase for checking
5. **Null Termination**: Properly terminate result

## 🎯 Key Concepts Covered

- Selective character removal
- Two-pointer technique
- Vowel identification
- Case handling
- String compression

## 🚀 Extensions

1. Delete consonants instead
2. Delete specific vowels only
3. Delete vowels at specific positions
4. Count deleted vowels