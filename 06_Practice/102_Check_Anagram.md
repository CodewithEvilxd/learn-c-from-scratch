# 🎯 Practical 102: Check Anagram

## 📋 Problem Statement

Write a program in C to check if two strings are anagram.

## 🎯 Learning Objectives

- Understand anagram concept
- Practice character frequency counting
- Learn string comparison techniques
- Understand sorting for anagram check
- Practice multiple approaches

## 📝 Requirements

1. Accept two strings
2. Check if they are anagrams
3. Display result clearly
4. Handle case sensitivity
5. Show character frequencies

## 💡 Hints

- Anagrams have same character frequencies
- Use frequency arrays or sorting
- Ignore spaces and punctuation
- Handle case sensitivity
- Compare sorted strings

## 🔧 Solution

```c
// Practical 102: Check Anagram
// Checks if two strings are anagrams

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 256

// Function to check if two strings are anagrams using frequency count
int areAnagrams(char *str1, char *str2) {
    int count[ALPHABET_SIZE] = {0};
    
    // If lengths are different, not anagrams
    if (strlen(str1) != strlen(str2)) {
        return 0;
    }
    
    // Count frequency of each character in first string
    for (int i = 0; str1[i] != '\0'; i++) {
        count[(unsigned char)tolower(str1[i])]++;
    }
    
    // Decrease frequency for each character in second string
    for (int i = 0; str2[i] != '\0'; i++) {
        count[(unsigned char)tolower(str2[i])]--;
    }
    
    // Check if all frequencies are zero
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (count[i] != 0) {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    char str1[1000], str2[1000];

    printf("Check Anagram\n");
    printf("=============\n");

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    
    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);

    // Remove newline characters
    if (str1[strlen(str1) - 1] == '\n') {
        str1[strlen(str1) - 1] = '\0';
    }
    if (str2[strlen(str2) - 1] == '\n') {
        str2[strlen(str2) - 1] = '\0';
    }

    printf("\nString 1: \"%s\"\n", str1);
    printf("String 2: \"%s\"\n", str2);

    if (areAnagrams(str1, str2)) {
        printf("✓ The strings are anagrams!\n");
    } else {
        printf("✗ The strings are not anagrams.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Valid Anagrams
```
Input: String1="listen", String2="silent"
Expected Output:
String 1: "listen"
String 2: "silent"
✓ The strings are anagrams!
```

### Test Case 2: Different Lengths
```
Input: String1="hello", String2="world"
Expected Output:
String 1: "hello"
String 2: "world"
✗ The strings are not anagrams.
```

### Test Case 3: Same Characters Different Order
```
Input: String1="triangle", String2="integral"
Expected Output:
String 1: "triangle"
String 2: "integral"
✓ The strings are anagrams!
```

### Test Case 4: Case Insensitive
```
Input: String1="Listen", String2="Silent"
Expected Output:
String 1: "Listen"
String 2: "Silent"
✓ The strings are anagrams!
```

## 🔍 Explanation

1. **Length Check**: Different lengths can't be anagrams
2. **Frequency Count**: Count characters in first string
3. **Frequency Decrease**: Decrease for second string
4. **Zero Check**: All frequencies should be zero
5. **Case Insensitive**: Convert to lowercase

## 🎯 Key Concepts Covered

- Anagram definition
- Frequency counting
- Character comparison
- Case conversion
- Array-based counting

## 🚀 Extensions

1. Check anagrams ignoring spaces
2. Find all anagrams in a list
3. Check for partial anagrams
4. Sort strings for comparison