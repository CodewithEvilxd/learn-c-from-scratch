# 🎯 Practical 3: Half Pyramid of Alphabets

## 📋 Problem Statement

Write a C Program to implement a half pyramid of alphabets.

## 🎯 Learning Objectives

- Understand character pattern printing
- Practice ASCII value manipulation
- Learn character loop control
- Understand alphabet sequences

## 📝 Requirements

1. Accept number of rows from user
2. Print alphabets in half pyramid pattern
3. Use uppercase or lowercase alphabets
4. Display with proper spacing
5. Handle input validation

## 💡 Hints

- Use ASCII values (A=65, a=97)
- Cast int to char for printing
- Use loop variables for alphabet generation
- Start from 'A' or 'a'

## 🔧 Solution

```c
// Practical 3: Half Pyramid of Alphabets
// This program prints a half pyramid pattern using alphabets

#include <stdio.h>

int main() {
    int rows;
    char choice;

    // Get user preferences
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Choose case (U for Uppercase, L for Lowercase): ");
    scanf(" %c", &choice);

    // Input validation
    if (rows <= 0) {
        printf("Please enter a positive number!\n");
        return 1;
    }

    if (choice != 'U' && choice != 'u' && choice != 'L' && choice != 'l') {
        printf("Invalid choice! Please enter U or L.\n");
        return 1;
    }

    // Determine starting character
    char start_char = (choice == 'U' || choice == 'u') ? 'A' : 'a';

    printf("Half Pyramid of Alphabets:\n");
    printf("==========================\n");

    // Outer loop for rows
    for (int i = 1; i <= rows; i++) {
        // Inner loop for alphabets in each row
        for (int j = 0; j < i; j++) {
            printf("%c ", start_char + j);
        }
        printf("\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Uppercase
```
Input: 5, U
Expected Output:
Half Pyramid of Alphabets:
==========================
A
A B
A B C
A B C D
A B C D E
```

### Test Case 2: Lowercase
```
Input: 4, L
Expected Output:
Half Pyramid of Alphabets:
==========================
a
a b
a b c
a b c d
```

### Test Case 3: Single Row
```
Input: 1, U
Expected Output:
Half Pyramid of Alphabets:
==========================
A
```

## 🔍 Explanation

1. **Character Generation**: Uses ASCII values to generate alphabets
2. **Loop Control**: Inner loop runs i times for row i
3. **ASCII Arithmetic**: start_char + j gives next alphabet
4. **Case Selection**: User chooses uppercase or lowercase
5. **Pattern Logic**: Row i contains first i alphabets

## 🎯 Key Concepts Covered

- Character manipulation
- ASCII value operations
- User choice handling
- Pattern printing with characters
- Input validation

## 🚀 Extensions

1. Print alphabets in reverse order per row
2. Start from a specific alphabet
3. Print only vowels or consonants
4. Add numbering to each row