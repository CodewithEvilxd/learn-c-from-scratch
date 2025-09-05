# 🎯 Practical 95: String Length

## 📋 Problem Statement

Write a C program to find the length of a string.

## 🎯 Learning Objectives

- Understand string termination
- Practice string traversal
- Learn null character handling
- Understand string length concept
- Practice loop implementation

## 📝 Requirements

1. Accept a string input
2. Count characters until null terminator
3. Display the length
4. Handle empty strings
5. Compare with strlen() function

## 💡 Hints

- Traverse string until '\0'
- Use counter variable
- Handle empty string case
- Compare manual vs library function
- Clear output display

## 🔧 Solution

```c
// Practical 95: String Length
// Calculates length of a string manually and using library function

#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];
    int manual_length = 0;

    printf("String Length Calculator\n");
    printf("========================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    // Manual length calculation
    for (int i = 0; str[i] != '\0'; i++) {
        manual_length++;
    }

    printf("String: \"%s\"\n", str);
    printf("Manual length: %d\n", manual_length);
    printf("Library function strlen(): %lu\n", strlen(str));

    // Additional information
    if (manual_length == 0) {
        printf("The string is empty.\n");
    } else {
        printf("First character: '%c' (ASCII: %d)\n", str[0], str[0]);
        printf("Last character: '%c' (ASCII: %d)\n", str[manual_length - 1], str[manual_length - 1]);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal String
```
Input: Hello World
Expected Output:
String: "Hello World"
Manual length: 11
Library function strlen(): 11
```

### Test Case 2: Empty String
```
Input: (just press enter)
Expected Output:
String: ""
Manual length: 0
Library function strlen(): 0
The string is empty.
```

### Test Case 3: Single Character
```
Input: A
Expected Output:
String: "A"
Manual length: 1
Library function strlen(): 1
```

### Test Case 4: String with Spaces
```
Input: C Programming
Expected Output:
String: "C Programming"
Manual length: 13
Library function strlen(): 13
```

## 🔍 Explanation

1. **Manual Calculation**: Loop until null terminator
2. **Counter Increment**: Count each character
3. **Library Function**: Use strlen() for comparison
4. **Edge Cases**: Handle empty strings
5. **Additional Info**: Show first and last characters

## 🎯 Key Concepts Covered

- String termination with null character
- Loop-based counting
- Library function usage
- Character indexing
- String validation

## 🚀 Extensions

1. Find length without counting null terminator
2. Compare different length calculation methods
3. Handle very long strings
4. Count specific character types