# 🎯 Practical 101: Count Character Occurrence

## 📋 Problem Statement

Write a program in C to count occurrence of a given character in a string.

## 🎯 Learning Objectives

- Understand character counting
- Practice string traversal
- Learn character comparison
- Understand case sensitivity
- Practice input validation

## 📝 Requirements

1. Accept a string and character
2. Count occurrences of the character
3. Display the count
4. Handle case sensitivity
5. Show clear results

## 💡 Hints

- Traverse string with loop
- Compare each character
- Increment counter on match
- Handle case sensitivity option
- Display original string and count

## 🔧 Solution

```c
// Practical 101: Count Character Occurrence
// Counts how many times a character appears in a string

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[1000], ch;
    int count = 0, case_sensitive = 1;

    printf("Count Character Occurrence\n");
    printf("==========================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Enter character to count: ");
    scanf("%c", &ch);

    printf("Case sensitive? (1 for Yes, 0 for No): ");
    scanf("%d", &case_sensitive);

    // Count occurrences
    for (int i = 0; str[i] != '\0'; i++) {
        if (case_sensitive) {
            if (str[i] == ch) {
                count++;
            }
        } else {
            if (tolower(str[i]) == tolower(ch)) {
                count++;
            }
        }
    }

    printf("\nString: \"%s\"\n", str);
    printf("Character to count: '%c'\n", ch);
    printf("Case sensitive: %s\n", case_sensitive ? "Yes" : "No");
    printf("Occurrences: %d\n", count);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Case Sensitive
```
Input: String="Hello World", Character='l', Case=1
Expected Output:
String: "Hello World"
Character to count: 'l'
Case sensitive: Yes
Occurrences: 3
```

### Test Case 2: Case Insensitive
```
Input: String="Hello World", Character='L', Case=0
Expected Output:
String: "Hello World"
Character to count: 'L'
Case sensitive: No
Occurrences: 3
```

### Test Case 3: Character Not Found
```
Input: String="Hello", Character='z', Case=1
Expected Output:
String: "Hello"
Character to count: 'z'
Case sensitive: Yes
Occurrences: 0
```

### Test Case 4: Multiple Same Characters
```
Input: String="aaa", Character='a', Case=1
Expected Output:
String: "aaa"
Character to count: 'a'
Case sensitive: Yes
Occurrences: 3
```

## 🔍 Explanation

1. **String Input**: Accept string and character
2. **Case Option**: Choose case sensitivity
3. **Traversal**: Loop through each character
4. **Comparison**: Check for matches
5. **Counting**: Increment counter on match

## 🎯 Key Concepts Covered

- String traversal
- Character comparison
- Case conversion
- Counter variables
- Input validation

## 🚀 Extensions

1. Count multiple characters
2. Find positions of occurrences
3. Count words in string
4. Count specific patterns