# 🎯 Practical 92: Character Frequency in String

## 📋 Problem Statement

Write a C program to find the frequency of characters in a string.

## 🎯 Learning Objectives

- Understand character counting
- Practice string traversal
- Learn frequency analysis
- Understand ASCII character handling
- Practice array usage for counting

## 📝 Requirements

1. Accept a string input
2. Count frequency of each character
3. Display character frequencies
4. Handle all ASCII characters
5. Show clear output format

## 💡 Hints

- Use array of size 256 for ASCII characters
- Traverse string and increment counters
- Display only characters that appear
- Handle spaces and special characters
- Use proper formatting

## 🔧 Solution

```c
// Practical 92: Character Frequency in String
// Counts frequency of each character in a string

#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];
    int frequency[256] = {0}; // Array for ASCII characters

    printf("Character Frequency in String\n");
    printf("==============================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    // Count frequency of each character
    for (int i = 0; str[i] != '\0'; i++) {
        frequency[(unsigned char)str[i]]++;
    }

    printf("\nCharacter frequencies:\n");
    printf("----------------------\n");

    // Display frequencies
    int found = 0;
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            if (i >= 32 && i <= 126) { // Printable characters
                printf("'%c' : %d\n", i, frequency[i]);
            } else { // Non-printable characters
                printf("ASCII %d : %d\n", i, frequency[i]);
            }
            found = 1;
        }
    }

    if (!found) {
        printf("No characters found in the string.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal String
```
Input: Hello World
Expected Output:
'H' : 1
'e' : 1
'l' : 3
'o' : 2
' ' : 1
'W' : 1
'r' : 1
'd' : 1
```

### Test Case 2: Repeated Characters
```
Input: Programming
Expected Output:
'P' : 1
'r' : 2
'o' : 1
'g' : 2
'a' : 1
'm' : 2
'i' : 1
'n' : 1
```

### Test Case 3: Numbers and Special Characters
```
Input: Hello123!
Expected Output:
'H' : 1
'e' : 1
'l' : 2
'o' : 1
'1' : 1
'2' : 1
'3' : 1
'!' : 1
```

## 🔍 Explanation

1. **Frequency Array**: Size 256 for all ASCII characters
2. **Character Counting**: Increment counter for each character
3. **ASCII Handling**: Cast to unsigned char to handle negative values
4. **Display Logic**: Show printable characters with quotes, others with ASCII codes
5. **Edge Cases**: Handle empty strings and non-printable characters

## 🎯 Key Concepts Covered

- String traversal
- ASCII character handling
- Array-based counting
- Character classification
- Frequency analysis

## 🚀 Extensions

1. Sort characters by frequency
2. Find most/least frequent character
3. Case-insensitive counting
4. Handle Unicode characters