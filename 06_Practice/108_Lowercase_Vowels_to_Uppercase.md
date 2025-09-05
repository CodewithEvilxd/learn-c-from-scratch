# 🎯 Practical 108: Lowercase Vowels to Uppercase

## 📋 Problem Statement

Write a C program to convert lowercase vowel to uppercase in string.

## 🎯 Learning Objectives

- Understand selective case conversion
- Practice vowel identification
- Learn conditional character modification
- Understand string processing
- Practice character checking

## 📝 Requirements

1. Accept a string input
2. Identify lowercase vowels (a,e,i,o,u)
3. Convert only vowels to uppercase
4. Leave other characters unchanged
5. Display original and modified strings

## 💡 Hints

- Check for lowercase vowels
- Use toupper() for conversion
- Process each character
- Preserve consonants and uppercase
- Handle mixed case strings

## 🔧 Solution

```c
// Practical 108: Lowercase Vowels to Uppercase
// Converts only lowercase vowels to uppercase in a string

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convertVowelsToUppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        // Check if it's a lowercase vowel
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            str[i] = toupper(ch);
        }
    }
}

int main() {
    char str[1000];

    printf("Lowercase Vowels to Uppercase\n");
    printf("==============================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    convertVowelsToUppercase(str);

    printf("Modified string: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Vowels and Consonants
```
Input: hello world
Expected Output:
Original string: "hello world"
Modified string: "hEllO wOrld"
```

### Test Case 2: All Vowels
```
Input: aeiou
Expected Output:
Original string: "aeiou"
Modified string: "AEIOU"
```

### Test Case 3: No Vowels
```
Input: rhythm
Expected Output:
Original string: "rhythm"
Modified string: "rhythm"
```

### Test Case 4: Mixed Case
```
Input: Computer Programming
Expected Output:
Original string: "Computer Programming"
Modified string: "COmptEr PrOgrAmmIng"
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **Vowel Check**: Identify a,e,i,o,u
3. **Case Conversion**: Convert lowercase vowels only
4. **Preserve Others**: Leave consonants and uppercase unchanged
5. **In-place Modification**: Modify original string

## 🎯 Key Concepts Covered

- Selective character modification
- Vowel identification
- Case conversion
- Conditional processing
- String manipulation

## 🚀 Extensions

1. Convert uppercase vowels to lowercase
2. Convert only consonants
3. Toggle case of vowels
4. Convert specific vowels only