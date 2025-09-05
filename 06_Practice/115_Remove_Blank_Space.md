# 🎯 Practical 115: Remove Blank Space from String

## 📋 Problem Statement

Write a C program to remove blank space from string.

## 🎯 Learning Objectives

- Understand space removal
- Practice string filtering
- Learn in-place modification
- Understand space handling
- Practice character skipping

## 📝 Requirements

1. Accept a string input
2. Remove all blank spaces
3. Modify string in-place
4. Display original and modified strings
5. Handle multiple consecutive spaces

## 💡 Hints

- Use two-pointer approach
- Skip space characters
- Copy non-space characters
- Null terminate result
- Handle leading/trailing spaces

## 🔧 Solution

```c
// Practical 115: Remove Blank Space from String
// Removes all blank spaces from a string

#include <stdio.h>
#include <string.h>

void removeBlankSpaces(char *str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null terminate
}

int main() {
    char str[1000];

    printf("Remove Blank Space from String\n");
    printf("===============================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    removeBlankSpaces(str);

    printf("String without spaces: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multiple Spaces
```
Input: Hello   World   Programming
Expected Output:
Original string: "Hello   World   Programming"
String without spaces: "HelloWorldProgramming"
```

### Test Case 2: Leading and Trailing Spaces
```
Input:   C Programming   
Expected Output:
Original string: "   C Programming   "
String without spaces: "CProgramming"
```

### Test Case 3: Only Spaces
```
Input:       
Expected Output:
Original string: "       "
String without spaces: ""
```

### Test Case 4: No Spaces
```
Input: HelloWorld
Expected Output:
Original string: "HelloWorld"
String without spaces: "HelloWorld"
```

## 🔍 Explanation

1. **String Input**: Accept any string with spaces
2. **Space Removal**: Use two-pointer technique
3. **Character Copying**: Copy only non-space characters
4. **In-place Modification**: Modify original string
5. **Null Termination**: Properly terminate result

## 🎯 Key Concepts Covered

- String filtering
- Space handling
- Two-pointer technique
- In-place modification
- Character skipping

## 🚀 Extensions

1. Remove all whitespace (tabs, newlines)
2. Remove only leading/trailing spaces
3. Replace multiple spaces with single space
4. Count removed spaces