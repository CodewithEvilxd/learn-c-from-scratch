# 🎯 Practical 82: Search Element in Array

## 📋 Problem Statement

Write a C program to search an element in an array.

## 🎯 Learning Objectives

- Understand array searching
- Practice linear search algorithm
- Learn array traversal
- Understand search results
- Practice input validation

## 📝 Requirements

1. Accept array elements
2. Accept search element
3. Search using linear search
4. Display search result
5. Show element position

## 💡 Hints

- Use loop to traverse array
- Compare each element with search key
- Return position if found
- Handle not found case
- Show array contents

## 🔧 Solution

```c
// Practical 82: Search Element in Array
// Searches for an element in an array using linear search

#include <stdio.h>

int main() {
    int n, search_element, found = 0, position = -1;

    printf("Array Element Search\n");
    printf("====================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array must have at least one element!\n");
        return 1;
    }

    int array[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &search_element);

    // Linear search
    for (int i = 0; i < n; i++) {
        if (array[i] == search_element) {
            found = 1;
            position = i;
            break; // Stop at first occurrence
        }
    }

    // Display array
    printf("\nArray elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("\n");

    // Display search result
    if (found) {
        printf("Element %d found at position %d (index %d)\n",
               search_element, position + 1, position);
    } else {
        printf("Element %d not found in the array.\n", search_element);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Element Found
```
Input: n=5, elements=[10, 20, 30, 40, 50], search=30
Expected Output:
Array elements: 10, 20, 30, 40, 50
Element 30 found at position 3 (index 2)
```

### Test Case 2: Element Not Found
```
Input: n=4, elements=[1, 3, 5, 7], search=4
Expected Output:
Array elements: 1, 3, 5, 7
Element 4 not found in the array.
```

### Test Case 3: First Element
```
Input: n=3, elements=[100, 200, 300], search=100
Expected Output:
Array elements: 100, 200, 300
Element 100 found at position 1 (index 0)
```

## 🔍 Explanation

1. **Input**: Array size, elements, and search key
2. **Linear Search**: Traverse array sequentially
3. **Comparison**: Check each element with search key
4. **Position Tracking**: Store index when found
5. **Result Display**: Show position or not found message

## 🎯 Key Concepts Covered

- Array traversal
- Linear search algorithm
- Position tracking
- Input validation
- Result formatting

## 🚀 Extensions

1. Implement binary search for sorted arrays
2. Find all occurrences of element
3. Search in 2D arrays
4. Add search statistics