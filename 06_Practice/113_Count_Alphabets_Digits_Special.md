# 🎯 Practical 113: Count Alphabets, Digits, Special Characters

## 📋 Problem Statement

Write a C program to count alphabets, digits and special characters.

## 🎯 Learning Objectives

- Understand character classification
- Practice comprehensive counting
- Learn character type identification
- Understand statistical analysis
- Practice detailed reporting

## 📝 Requirements

1. Accept a string input
2. Count alphabets (A-Z, a-z)
3. Count digits (0-9)
4. Count special characters
5. Display detailed breakdown

## 💡 Hints

- Use isalpha() for alphabets
- Use isdigit() for digits
- Special characters = total - alphabets - digits - spaces
- Include spaces in analysis
- Provide percentage breakdown

## 🔧 Solution

```c
// Practical 113: Count Alphabets, Digits, Special Characters
// Comprehensive character type counting

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[1000];
    int alphabets = 0, digits = 0, spaces = 0, special = 0;

    printf("Count Alphabets, Digits, Special Characters\n");
    printf("=============================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    // Count different character types
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            alphabets++;
        } else if (isdigit(str[i])) {
            digits++;
        } else if (isspace(str[i])) {
            spaces++;
        } else {
            special++;
        }
    }

    int total = alphabets + digits + spaces + special;

    // Display results
    printf("\nString Analysis:\n");
    printf("----------------\n");
    printf("Original String: \"%s\"\n", str);
    printf("String Length: %lu characters\n", strlen(str));
    printf("\nCharacter Counts:\n");
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);
    printf("Special Characters: %d\n", special);
    printf("Total Characters: %d\n", total);

    // Percentage calculation
    if (total > 0) {
        printf("\nPercentages:\n");
        printf("Alphabets: %.2f%%\n", (float)alphabets / total * 100);
        printf("Digits: %.2f%%\n", (float)digits / total * 100);
        printf("Spaces: %.2f%%\n", (float)spaces / total * 100);
        printf("Special Characters: %.2f%%\n", (float)special / total * 100);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Characters
```
Input: Hello World 123 @#$!
Expected Output:
Alphabets: 10
Digits: 3
Spaces: 2
Special Characters: 4
Total Characters: 19
```

### Test Case 2: Only Alphabets
```
Input: Programming
Expected Output:
Alphabets: 11
Digits: 0
Spaces: 0
Special Characters: 0
Total Characters: 11
```

### Test Case 3: Only Digits
```
Input: 123456789
Expected Output:
Alphabets: 0
Digits: 9
Spaces: 0
Special Characters: 0
Total Characters: 9
```

### Test Case 4: Special Characters Only
```
Input: @#$%^&*()
Expected Output:
Alphabets: 0
Digits: 0
Spaces: 0
Special Characters: 9
Total Characters: 9
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **Character Classification**: Use isalpha(), isdigit(), isspace()
3. **Special Characters**: Everything else
4. **Total Count**: Sum of all categories
5. **Percentage Calculation**: Proportions of each type

## 🎯 Key Concepts Covered

- Character type identification
- Comprehensive counting
- Statistical analysis
- Percentage calculations
- Detailed reporting

## 🚀 Extensions

1. Count uppercase vs lowercase separately
2. Count vowels and consonants within alphabets
3. Generate character type histogram
4. Analyze multiple strings