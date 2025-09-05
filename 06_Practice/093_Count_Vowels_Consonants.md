# 🎯 Practical 93: Count Vowels, Consonants, and Characters

## 📋 Problem Statement

Write a C program to count the number of vowels, consonants and so on.

## 🎯 Learning Objectives

- Understand character classification
- Practice string analysis
- Learn vowel and consonant identification
- Understand character counting
- Practice conditional logic

## 📝 Requirements

1. Accept a string input
2. Count vowels (a,e,i,o,u,A,E,I,O,U)
3. Count consonants
4. Count digits, spaces, and special characters
5. Display all counts clearly

## 💡 Hints

- Use isalpha() to check alphabets
- Check for vowels using conditional
- Count consonants as alphabets minus vowels
- Use counters for different categories
- Handle case sensitivity

## 🔧 Solution

```c
// Practical 93: Count Vowels, Consonants, and Characters
// Analyzes string and counts different character types

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char str[1000];
    int vowels = 0, consonants = 0, digits = 0, spaces = 0, special = 0;

    printf("Count Vowels, Consonants, and Characters\n");
    printf("=========================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    // Analyze each character
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]); // Convert to lowercase for easy checking

        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowels++;
        } else if (isalpha(str[i])) { // Check original character for consonants
            consonants++;
        } else if (isdigit(str[i])) {
            digits++;
        } else if (isspace(str[i])) {
            spaces++;
        } else {
            special++;
        }
    }

    // Display results
    printf("\nString Analysis:\n");
    printf("----------------\n");
    printf("Original String: \"%s\"\n", str);
    printf("String Length: %lu characters\n", strlen(str));
    printf("\nCharacter Counts:\n");
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);
    printf("Special Characters: %d\n", special);

    // Additional statistics
    int alphabets = vowels + consonants;
    int total = alphabets + digits + spaces + special;

    printf("\nSummary:\n");
    printf("Total Alphabets: %d\n", alphabets);
    printf("Total Characters (excluding null): %d\n", total);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal String
```
Input: Hello World 123!
Expected Output:
Vowels: 3
Consonants: 7
Digits: 3
Spaces: 1
Special Characters: 1
```

### Test Case 2: Only Vowels
```
Input: AEIOUaeiou
Expected Output:
Vowels: 10
Consonants: 0
Digits: 0
Spaces: 0
Special Characters: 0
```

### Test Case 3: Mixed Characters
```
Input: C Programming 2024 @#$%
Expected Output:
Vowels: 3
Consonants: 10
Digits: 4
Spaces: 2
Special Characters: 4
```

## 🔍 Explanation

1. **Character Analysis**: Check each character in the string
2. **Vowel Check**: a,e,i,o,u (both cases)
3. **Consonant Check**: Alphabets that are not vowels
4. **Category Counting**: Digits, spaces, special characters
5. **Summary**: Total counts and statistics

## 🎯 Key Concepts Covered

- Character classification functions
- String traversal
- Conditional logic
- Case conversion
- Statistical analysis

## 🚀 Extensions

1. Count uppercase and lowercase separately
2. Find most frequent character type
3. Analyze multiple strings
4. Generate character type report