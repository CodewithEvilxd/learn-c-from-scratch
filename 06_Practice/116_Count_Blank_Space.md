# 🎯 Practical 116: Count Blank Space from String

## 📋 Problem Statement

Write a C program to count blank space from string.

## 🎯 Learning Objectives

- Understand space counting
- Practice string traversal
- Learn character comparison
- Understand space types
- Practice counter variables

## 📝 Requirements

1. Accept a string input
2. Count all blank spaces
3. Display the count
4. Show original string
5. Handle different space types

## 💡 Hints

- Traverse string character by character
- Check for space character ' '
- Increment counter on match
- Handle multiple spaces
- Display clear results

## 🔧 Solution

```c
// Practical 116: Count Blank Space from String
// Counts the number of blank spaces in a string

#include <stdio.h>
#include <string.h>

int countBlankSpaces(char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[1000];
    int spaceCount;

    printf("Count Blank Space from String\n");
    printf("==============================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    spaceCount = countBlankSpaces(str);

    printf("String: \"%s\"\n", str);
    printf("Number of blank spaces: %d\n", spaceCount);

    // Additional information
    printf("String length: %lu characters\n", strlen(str));
    if (strlen(str) > 0) {
        printf("Percentage of spaces: %.2f%%\n", (float)spaceCount / strlen(str) * 100);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multiple Spaces
```
Input: Hello   World   Programming
Expected Output:
String: "Hello   World   Programming"
Number of blank spaces: 5
String length: 27 characters
Percentage of spaces: 18.52%
```

### Test Case 2: No Spaces
```
Input: HelloWorld
Expected Output:
String: "HelloWorld"
Number of blank spaces: 0
String length: 10 characters
Percentage of spaces: 0.00%
```

### Test Case 3: Only Spaces
```
Input:       
Expected Output:
String: "       "
Number of blank spaces: 7
String length: 7 characters
Percentage of spaces: 100.00%
```

### Test Case 4: Leading and Trailing Spaces
```
Input:   C Programming   
Expected Output:
String: "   C Programming   "
Number of blank spaces: 5
String length: 18 characters
Percentage of spaces: 27.78%
```

## 🔍 Explanation

1. **String Input**: Accept any string
2. **Space Counting**: Traverse and count spaces
3. **Counter Variable**: Increment on space detection
4. **Statistics**: Show percentage and length
5. **Edge Cases**: Handle no spaces, all spaces

## 🎯 Key Concepts Covered

- String traversal
- Character comparison
- Counter variables
- Statistical calculation
- Percentage computation

## 🚀 Extensions

1. Count different whitespace types (tab, newline)
2. Count consecutive spaces
3. Find positions of spaces
4. Remove spaces while counting