# 🎯 Practical 123: Sort Characters of String in Descending Order

## 📋 Problem Statement

Write a C program to sort characters of string in descending order.

## 🎯 Learning Objectives

- Understand string sorting
- Practice character comparison
- Learn bubble sort for strings
- Understand ASCII ordering
- Practice string manipulation

## 📝 Requirements

1. Accept a string input
2. Sort characters in descending order
3. Display original and sorted strings
4. Handle case sensitivity
5. Maintain string integrity

## 💡 Hints

- Use bubble sort algorithm
- Compare ASCII values in reverse
- Swap characters in place
- Handle string length
- Consider case sensitivity

## 🔧 Solution

```c
// Practical 123: Sort Characters of String in Descending Order
// Sorts characters in descending order

#include <stdio.h>
#include <string.h>

void sortStringDescending(char *str) {
    int n = strlen(str);
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (str[j] < str[j + 1]) {
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

    printf("String Character Sorting (Descending)\n");
    printf("=====================================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", str);

    sortStringDescending(str);

    printf("Sorted string (descending): \"%s\"\n", str);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Mixed Characters
```
Input: abcd
Expected Output:
Original string: "abcd"
Sorted string (descending): "dcba"
```

### Test Case 2: With Spaces
```
Input: hello world
Expected Output:
Original string: "hello world"
Sorted string (descending): "wroolllhed "
```

### Test Case 3: Numbers and Letters
```
Input: a1b2c3
Expected Output:
Original string: "a1b2c3"
Sorted string (descending): "cba321"
```

## 🔍 Explanation

1. **Input Reading**: Read string from user
2. **Bubble Sort**: Compare and swap adjacent characters
3. **Reverse ASCII Ordering**: Sort based on descending ASCII values
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
2. Sort in ascending order
3. Handle case-insensitive sorting
4. Sort words instead of characters