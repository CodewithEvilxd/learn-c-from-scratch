# 🎯 Practical 104: Check Vowel or Consonant

## 📋 Problem Statement

Write a C program to check given character is vowel or consonant.

## 🎯 Learning Objectives

- Understand vowel and consonant classification
- Practice character checking
- Learn conditional logic
- Understand case sensitivity
- Practice input validation

## 📝 Requirements

1. Accept a character input
2. Check if it's a vowel or consonant
3. Handle both cases (upper and lower)
4. Display appropriate message
5. Handle invalid inputs

## 💡 Hints

- Check for vowels: a,e,i,o,u,A,E,I,O,U
- Use isalpha() to validate alphabet
- Handle case insensitivity
- Check for non-alphabet characters
- Clear output messages

## 🔧 Solution

```c
// Practical 104: Check Vowel or Consonant
// Determines if a character is a vowel or consonant

#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;

    printf("Check Vowel or Consonant\n");
    printf("=========================\n");

    printf("Enter a character: ");
    scanf("%c", &ch);

    // Check if it's an alphabet
    if (!isalpha(ch)) {
        printf("'%c' is not an alphabet character.\n", ch);
        printf("Please enter an alphabet character (A-Z or a-z).\n");
        return 1;
    }

    // Convert to lowercase for easy checking
    char lower_ch = tolower(ch);

    // Check if it's a vowel
    if (lower_ch == 'a' || lower_ch == 'e' || lower_ch == 'i' || 
        lower_ch == 'o' || lower_ch == 'u') {
        printf("'%c' is a vowel.\n", ch);
    } else {
        printf("'%c' is a consonant.\n", ch);
    }

    // Additional information
    printf("Character: '%c'\n", ch);
    printf("ASCII value: %d\n", ch);
    printf("Case: %s\n", isupper(ch) ? "Uppercase" : "Lowercase");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Vowel (Lowercase)
```
Input: a
Expected Output:
'a' is a vowel.
Character: 'a'
ASCII value: 97
Case: Lowercase
```

### Test Case 2: Vowel (Uppercase)
```
Input: E
Expected Output:
'E' is a vowel.
Character: 'E'
ASCII value: 69
Case: Uppercase
```

### Test Case 3: Consonant
```
Input: b
Expected Output:
'b' is a consonant.
Character: 'b'
ASCII value: 98
Case: Lowercase
```

### Test Case 4: Non-Alphabet
```
Input: 5
Expected Output:
'5' is not an alphabet character.
Please enter an alphabet character (A-Z or a-z).
```

### Test Case 5: Special Character
```
Input: @
Expected Output:
'@' is not an alphabet character.
Please enter an alphabet character (A-Z or a-z).
```

## 🔍 Explanation

1. **Input Validation**: Check if character is alphabet
2. **Case Conversion**: Convert to lowercase for checking
3. **Vowel Check**: Compare with a,e,i,o,u
4. **Classification**: Vowel or consonant
5. **Additional Info**: ASCII value and case

## 🎯 Key Concepts Covered

- Character classification
- Case conversion
- Input validation
- Conditional logic
- ASCII values

## 🚀 Extensions

1. Check for digits
2. Classify special characters
3. Check for uppercase/lowercase vowels separately
4. Handle multiple characters