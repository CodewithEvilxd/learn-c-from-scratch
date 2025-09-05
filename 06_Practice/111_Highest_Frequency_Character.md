# 🎯 Practical 111: Highest Frequency Character

## 📋 Problem Statement

Write a C program to print the highest frequency character in a String.

## 🎯 Learning Objectives

- Understand frequency analysis
- Practice maximum finding algorithms
- Learn character counting techniques
- Understand tie handling
- Practice array-based solutions

## 📝 Requirements

1. Accept a string input
2. Count frequency of each character
3. Find character with highest frequency
4. Handle ties (multiple characters with same frequency)
5. Display results clearly

## 💡 Hints

- Use frequency array for counting
- Track maximum frequency
- Store character with max frequency
- Handle case sensitivity
- Display all characters with max frequency

## 🔧 Solution

```c
// Practical 111: Highest Frequency Character
// Finds and displays the character with highest frequency

#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256

int main() {
    char str[1000];
    int frequency[ALPHABET_SIZE] = {0};
    int max_freq = 0;

    printf("Highest Frequency Character\n");
    printf("===========================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    // Count frequency of each character
    for (int i = 0; str[i] != '\0'; i++) {
        frequency[(unsigned char)str[i]]++;
        if (frequency[(unsigned char)str[i]] > max_freq) {
            max_freq = frequency[(unsigned char)str[i]];
        }
    }

    printf("String: \"%s\"\n", str);
    printf("Maximum frequency: %d\n", max_freq);
    printf("Characters with highest frequency:\n");

    // Display all characters with maximum frequency
    int found = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] == max_freq && frequency[i] > 0) {
            if (i >= 32 && i <= 126) { // Printable characters
                printf("'%c' : %d times\n", i, frequency[i]);
            } else { // Non-printable characters
                printf("ASCII %d : %d times\n", i, frequency[i]);
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

### Test Case 1: Single Highest Frequency
```
Input: programming
Expected Output:
String: "programming"
Maximum frequency: 2
Characters with highest frequency:
'g' : 2 times
'r' : 2 times
'm' : 2 times
```

### Test Case 2: All Same Character
```
Input: aaaa
Expected Output:
String: "aaaa"
Maximum frequency: 4
Characters with highest frequency:
'a' : 4 times
```

### Test Case 3: Spaces and Characters
```
Input: hello world
Expected Output:
String: "hello world"
Maximum frequency: 3
Characters with highest frequency:
'l' : 3 times
```

### Test Case 4: Special Characters
```
Input: a@b@c@d@
Expected Output:
String: "a@b@c@d@"
Maximum frequency: 4
Characters with highest frequency:
'@' : 4 times
```

## 🔍 Explanation

1. **Frequency Array**: Count occurrences of each character
2. **Maximum Tracking**: Keep track of highest frequency
3. **Multiple Characters**: Handle ties (multiple chars with same freq)
4. **Display Results**: Show all characters with max frequency
5. **Character Types**: Handle printable and non-printable chars

## 🎯 Key Concepts Covered

- Frequency analysis
- Maximum finding
- Character counting
- Array-based solutions
- Tie handling

## 🚀 Extensions

1. Find lowest frequency character
2. Sort characters by frequency
3. Find second highest frequency
4. Generate frequency histogram