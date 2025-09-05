# 🎯 Practical 126: Find First Duplicate Number in Array

## 📋 Problem Statement

Write a program in C to find first duplicate number in a given array.

## 🎯 Learning Objectives

- Understand duplicate detection
- Practice early termination
- Learn hash set simulation
- Understand first occurrence tracking
- Practice efficient searching

## 📝 Requirements

1. Accept array of integers
2. Find first number that appears more than once
3. Return the first duplicate found
4. Handle no duplicates case
5. Display clear result

## 💡 Hints

- Use hash set or frequency array
- Track seen numbers
- Return immediately when duplicate found
- Handle negative numbers if needed
- Consider array size limits

## 🔧 Solution

```c
// Practical 126: Find First Duplicate Number in Array
// Finds the first number that appears more than once

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int findFirstDuplicate(int arr[], int n) {
    int *seen = (int *)calloc(MAX_SIZE * 2, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        int index = num + MAX_SIZE; // Handle negative numbers
        
        if (seen[index] == 1) {
            free(seen);
            return num;
        }
        
        seen[index] = 1;
    }
    
    free(seen);
    return -1; // No duplicate found
}

int main() {
    int n;
    int arr[1000];

    printf("Find First Duplicate Number\n");
    printf("===========================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int firstDuplicate = findFirstDuplicate(arr, n);

    if (firstDuplicate != -1) {
        printf("First duplicate number: %d\n", firstDuplicate);
    } else {
        printf("No duplicate numbers found!\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: First Duplicate at Beginning
```
Input: 1 2 2 3 4
Expected Output:
First duplicate number: 2
```

### Test Case 2: First Duplicate in Middle
```
Input: 1 2 3 4 2 5
Expected Output:
First duplicate number: 2
```

### Test Case 3: No Duplicates
```
Input: 1 2 3 4 5
Expected Output:
No duplicate numbers found!
```

### Test Case 4: Multiple Duplicates
```
Input: 1 2 3 2 3 4
Expected Output:
First duplicate number: 2
```

## 🔍 Explanation

1. **Input Reading**: Read array elements from user
2. **Hash Set Simulation**: Use array to track seen numbers
3. **Duplicate Detection**: Check if number already seen
4. **Early Return**: Return immediately when first duplicate found
5. **Memory Management**: Free allocated memory

## 🎯 Key Concepts Covered

- Duplicate detection
- Hash set simulation
- Early termination
- Memory allocation
- Array indexing

## 🚀 Extensions

1. Find all duplicates
2. Find last duplicate
3. Find most frequent number
4. Handle large number ranges