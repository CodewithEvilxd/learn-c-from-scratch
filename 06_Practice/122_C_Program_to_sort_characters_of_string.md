# 🎯 Practical 122: Sort Characters of String

## 📋 Problem Statement

Write a C program to sort characters of string in ascending order.

## 🎯 Learning Objectives

- Understand string sorting
- Practice character comparison
- Learn bubble sort for strings
- Understand ASCII ordering
- Practice string manipulation

## 📝 Requirements

1. Accept a string input
2. Sort characters in ascending order
3. Display original and sorted strings
4. Handle case sensitivity
5. Maintain string integrity

## 💡 Hints

- Use bubble sort algorithm
- Compare ASCII values
- Swap characters in place
- Handle string length
- Consider case sensitivity

## 🔧 Solution

```c
// Practical 122: Sort Characters of String
// Sorts characters in ascending order

#include <stdio.h>
#include <string.h>

void sortString(char *str) {
    int n = strlen(str);
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                // Swap characters
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

int main() {
    char str[1000];

    printf("String Character Sorting\n");
    printf("========================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    sortString(str);

    printf("Sorted string: \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Characters
```
Input: dcba
Expected Output:
Original string: "dcba"
Sorted string: "abcd"
```

### Test Case 2: With Spaces
```
Input: hello world
Expected Output:
Original string: "hello world"
Sorted string: " dehllloorw"
```

### Test Case 3: Numbers and Letters
```
Input: a1b2c3
Expected Output:
Original string: "a1b2c3"
Sorted string: "123abc"
```

## 🔍 Explanation

1. **Input Reading**: Read string from user
2. **Bubble Sort**: Compare and swap adjacent characters
3. **ASCII Ordering**: Sort based on ASCII values
4. **In-place Sorting**: Modify original string
5. **Output Display**: Show before and after

## 🎯 Key Concepts Covered

- String sorting
- Bubble sort algorithm
- Character comparison
- ASCII values
- In-place modification

## 🚀 Extensions

1. Implement different sorting algorithms
2. Sort in descending order
3. Handle case-insensitive sorting
4. Sort words instead of characters