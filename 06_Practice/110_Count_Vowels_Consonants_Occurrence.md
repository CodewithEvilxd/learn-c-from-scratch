# 🎯 Practical 110: Count Vowels & Consonants Occurrence

## 📋 Problem Statement

Write a C program to count Occurrence Of Vowels & Consonants in a String.

## 🎯 Learning Objectives

- Understand vowel and consonant counting
- Practice character classification
- Learn detailed counting
- Understand case handling
- Practice statistical analysis

## 📝 Requirements

1. Accept a string input
2. Count vowels and consonants separately
3. Display individual counts
4. Handle both uppercase and lowercase
5. Show total alphabets

## 💡 Hints

- Use separate counters for vowels and consonants
- Check isalpha() for alphabets
- Identify vowels: a,e,i,o,u,A,E,I,O,U
- Consonants = alphabets - vowels
- Display detailed breakdown

## 🔧 Solution

```c
// Practical 110: Count Vowels & Consonants Occurrence
// Counts and displays occurrence of vowels and consonants

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[1000];
    int vowels = 0, consonants = 0, alphabets = 0;

    printf("Count Vowels & Consonants Occurrence\n");
    printf("=====================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    // Count vowels and consonants
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);
        
        if (isalpha(str[i])) {
            alphabets++;
            
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    // Display results
    printf("\nString Analysis:\n");
    printf("----------------\n");
    printf("Original String: \"%s\"\n", str);
    printf("String Length: %lu characters\n", strlen(str));
    printf("\nAlphabet Count: %d\n", alphabets);
    printf("Vowel Count: %d\n", vowels);
    printf("Consonant Count: %d\n", consonants);

    // Percentage calculation
    if (alphabets > 0) {
        printf("\nPercentages:\n");
        printf("Vowels: %.2f%%\n", (float)vowels / alphabets * 100);
        printf("Consonants: %.2f%%\n", (float)consonants / alphabets * 100);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal String
```
Input: Hello World
Expected Output:
Alphabet Count: 10
Vowel Count: 3
Consonant Count: 7
Vowels: 30.00%
Consonants: 70.00%
```

### Test Case 2: All Vowels
```
Input: AEIOUaeiou
Expected Output:
Alphabet Count: 10
Vowel Count: 10
Consonant Count: 0
Vowels: 100.00%
Consonants: 0.00%
```

### Test Case 3: All Consonants
```
Input: BCDFG
Expected Output:
Alphabet Count: 5
Vowel Count: 0
Consonant Count: 5
Vowels: 0.00%
Consonants: 100.00%
```

### Test Case 4: Mixed Characters
```
Input: C Programming 123!
Expected Output:
Alphabet Count: 12
Vowel Count: 3
Consonant Count: 9
Vowels: 25.00%
Consonants: 75.00%
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **Alphabet Check**: Use isalpha() for letters
3. **Vowel Identification**: Check a,e,i,o,u (both cases)
4. **Consonant Calculation**: Alphabets minus vowels
5. **Percentage Calculation**: Show proportions

## 🎯 Key Concepts Covered

- Character classification
- Statistical counting
- Percentage calculation
- Case handling
- Detailed analysis

## 🚀 Extensions

1. Count individual vowel occurrences
2. Count uppercase vs lowercase separately
3. Generate vowel/consonant ratio
4. Compare multiple strings