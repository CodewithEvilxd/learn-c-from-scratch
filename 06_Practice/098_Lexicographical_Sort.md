# 🎯 Practical 98: Lexicographical Sort

## 📋 Problem Statement

Write a C program to sort elements in lexicographical order (dictionary order).

## 🎯 Learning Objectives

- Understand lexicographical sorting
- Practice string comparison
- Learn sorting algorithms
- Understand dictionary order
- Practice array of strings

## 📝 Requirements

1. Accept array of strings
2. Sort in dictionary order
3. Display original and sorted arrays
4. Handle case sensitivity
5. Use proper sorting algorithm

## 💡 Hints

- Use strcmp() for string comparison
- Implement bubble sort or selection sort
- Handle variable number of strings
- Preserve original order display
- Clear output formatting

## 🔧 Solution

```c
// Practical 98: Lexicographical Sort
// Sorts strings in dictionary order

#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 10
#define MAX_LENGTH 100

void sortStrings(char strings[][MAX_LENGTH], int n) {
    char temp[MAX_LENGTH];
    
    // Bubble sort for strings
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                // Swap strings
                strcpy(temp, strings[j]);
                strcpy(strings[j], strings[j + 1]);
                strcpy(strings[j + 1], temp);
            }
        }
    }
}

int main() {
    char strings[MAX_STRINGS][MAX_LENGTH];
    int n;

    printf("Lexicographical Sort\n");
    printf("====================\n");

    printf("Enter number of strings: ");
    scanf("%d", &n);
    getchar(); // Consume newline

    if (n <= 0 || n > MAX_STRINGS) {
        printf("Invalid number of strings!\n");
        return 1;
    }

    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        printf("String %d: ", i + 1);
        fgets(strings[i], MAX_LENGTH, stdin);
        
        // Remove newline character
        if (strings[i][strlen(strings[i]) - 1] == '\n') {
            strings[i][strlen(strings[i]) - 1] = '\0';
        }
    }

    printf("\nOriginal strings:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, strings[i]);
    }

    // Sort the strings
    sortStrings(strings, n);

    printf("\nSorted strings (lexicographical order):\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, strings[i]);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Strings
```
Input: 4 strings - "zebra", "apple", "mango", "banana"
Expected Output:
Original: zebra, apple, mango, banana
Sorted: apple, banana, mango, zebra
```

### Test Case 2: Case Sensitivity
```
Input: 3 strings - "Apple", "apple", "APPLE"
Expected Output:
Sorted: APPLE, Apple, apple
```

### Test Case 3: Single String
```
Input: 1 string - "hello"
Expected Output:
Original: hello
Sorted: hello
```

## 🔍 Explanation

1. **String Input**: Accept multiple strings
2. **Bubble Sort**: Compare adjacent strings
3. **strcmp()**: Dictionary comparison
4. **String Swap**: Exchange positions
5. **Display**: Show original and sorted

## 🎯 Key Concepts Covered

- Lexicographical ordering
- String comparison functions
- Sorting algorithms
- Array of strings
- Case sensitivity

## 🚀 Extensions

1. Implement different sorting algorithms
2. Add case-insensitive sorting
3. Sort by string length
4. Handle very long strings