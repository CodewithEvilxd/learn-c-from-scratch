# 🎯 Practical 105: Check Digit

## 📋 Problem Statement

Write a C program to check given character is digit or not.

## 🎯 Learning Objectives

- Understand digit classification
- Practice character checking
- Learn ASCII range for digits
- Understand isdigit() function
- Practice input validation

## 📝 Requirements

1. Accept a character input
2. Check if it's a digit (0-9)
3. Display appropriate message
4. Show ASCII value
5. Handle non-digit characters

## 💡 Hints

- Use isdigit() function
- Check ASCII range 48-57
- Manual comparison with '0'-'9'
- Display character information
- Clear output messages

## 🔧 Solution

```c
// Practical 105: Check Digit
// Determines if a character is a digit

#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;

    printf("Check Digit\n");
    printf("===========\n");

    printf("Enter a character: ");
    scanf("%c", &ch);

    printf("Character: '%c'\n", ch);
    printf("ASCII value: %d\n", ch);

    // Method 1: Using isdigit() function
    if (isdigit(ch)) {
        printf("✓ Using isdigit(): '%c' is a digit.\n", ch);
    } else {
        printf("✗ Using isdigit(): '%c' is not a digit.\n", ch);
    }

    // Method 2: Manual check using ASCII values
    if (ch >= '0' && ch <= '9') {
        printf("✓ Using ASCII: '%c' is a digit.\n", ch);
        printf("Digit value: %d\n", ch - '0');
    } else {
        printf("✗ Using ASCII: '%c' is not a digit.\n", ch);
    }

    // Additional classification
    if (isalpha(ch)) {
        printf("Character type: Alphabet\n");
    } else if (ispunct(ch)) {
        printf("Character type: Punctuation/Special\n");
    } else if (isspace(ch)) {
        printf("Character type: Whitespace\n");
    } else if (isdigit(ch)) {
        printf("Character type: Digit\n");
    } else {
        printf("Character type: Other\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Digit
```
Input: 5
Expected Output:
Character: '5'
ASCII value: 53
✓ Using isdigit(): '5' is a digit.
✓ Using ASCII: '5' is a digit.
Digit value: 5
Character type: Digit
```

### Test Case 2: Alphabet
```
Input: A
Expected Output:
Character: 'A'
ASCII value: 65
✗ Using isdigit(): 'A' is not a digit.
✗ Using ASCII: 'A' is not a digit.
Character type: Alphabet
```

### Test Case 3: Special Character
```
Input: @
Expected Output:
Character: '@'
ASCII value: 64
✗ Using isdigit(): '@' is not a digit.
✗ Using ASCII: '@' is not a digit.
Character type: Punctuation/Special
```

### Test Case 4: Zero
```
Input: 0
Expected Output:
Character: '0'
ASCII value: 48
✓ Using isdigit(): '0' is a digit.
✓ Using ASCII: '0' is a digit.
Digit value: 0
Character type: Digit
```

## 🔍 Explanation

1. **isdigit() Function**: Library function for digit check
2. **ASCII Range**: Check between '0' and '9'
3. **Digit Value**: Convert character to integer
4. **Character Classification**: Additional type information
5. **Multiple Methods**: Show both approaches

## 🎯 Key Concepts Covered

- Digit classification
- ASCII values
- Character functions
- Type checking
- Multiple validation methods

## 🚀 Extensions

1. Check for hexadecimal digits
2. Validate numeric strings
3. Convert digit to word
4. Check for negative digits