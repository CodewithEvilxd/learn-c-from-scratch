# 🎯 Practical 59: Vowel Consonant Check

## 📋 Problem Statement

Write a C program to check whether a character is a vowel or consonant.

## 🎯 Learning Objectives

- Understand vowel and consonant classification
- Practice character checking
- Learn conditional logic
- Understand ASCII values
- Practice input validation

## 📝 Requirements

1. Accept a character from user
2. Check if it's a vowel or consonant
3. Handle both uppercase and lowercase
4. Display appropriate message
5. Handle non-alphabet characters

## 💡 Hints

- Vowels: A, E, I, O, U (both cases)
- Use logical OR conditions
- Check if alphabet first
- Handle case sensitivity
- Clear output messages

## 🔧 Solution

```c
// Practical 59: Vowel Consonant Check
// Checks if a character is vowel or consonant

#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;

    printf("Vowel or Consonant Checker\n");
    printf("==========================\n");

    printf("Enter a character: ");
    scanf("%c", &ch);

    // Convert to lowercase for easier checking
    char lower_ch = tolower(ch);

    if (!isalpha(ch)) {
        printf("'%c' is not an alphabet character.\n", ch);
        printf("Please enter an alphabet character.\n");
    } else if (lower_ch == 'a' || lower_ch == 'e' || lower_ch == 'i' ||
               lower_ch == 'o' || lower_ch == 'u') {
        printf("'%c' is a vowel.\n", ch);
    } else {
        printf("'%c' is a consonant.\n", ch);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Vowel (Lowercase)
```
Input: a
Expected Output:
'a' is a vowel.
```

### Test Case 2: Vowel (Uppercase)
```
Input: E
Expected Output:
'E' is a vowel.
```

### Test Case 3: Consonant
```
Input: b
Expected Output:
'b' is a consonant.
```

### Test Case 4: Non-Alphabet
```
Input: 5
Expected Output:
'5' is not an alphabet character.
Please enter an alphabet character.
```

## 🔍 Explanation

1. **Input**: Accept single character
2. **Validation**: Check if alphabet using isalpha()
3. **Case Conversion**: Use tolower() for case-insensitive check
4. **Vowel Check**: Check against a, e, i, o, u
5. **Classification**: Vowel or consonant

## 🎯 Key Concepts Covered

- Character classification
- Case conversion
- Logical operators
- Input validation
- Conditional statements

## 🚀 Extensions

1. Check for specific vowel types
2. Count vowels in a string
3. Remove vowels from string
4. Check diphthongs