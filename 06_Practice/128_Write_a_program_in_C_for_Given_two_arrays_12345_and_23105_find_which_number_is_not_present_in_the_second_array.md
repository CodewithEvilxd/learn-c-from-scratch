# 🎯 Practical 128: Find Numbers Not Present in Second Array

## 📋 Problem Statement

Write a program in C for, Given two arrays 1,2,3,4,5 and 2,3,1,0,5 find which number is not present in the second array.

## 🎯 Learning Objectives

- Understand set difference
- Practice array comparison
- Learn frequency-based approach
- Understand element presence checking
- Practice multiple array handling

## 📝 Requirements

1. Accept two arrays
2. Find elements in first array not in second
3. Display missing elements
4. Handle duplicates appropriately
5. Show clear output

## 💡 Hints

- Use frequency array for second array
- Check each element of first array
- Mark presence in second array
- Display elements not found
- Handle array sizes

## 🔧 Solution

```c
// Practical 128: Find Numbers Not Present in Second Array
// Finds elements from first array that are not in second array

#include <stdio.h>

#define MAX_NUM 100

void findMissingElements(int arr1[], int n1, int arr2[], int n2) {
    int present[MAX_NUM + 1] = {0};
    
    // Mark elements present in second array
    for (int i = 0; i < n2; i++) {
        if (arr2[i] >= 0 && arr2[i] <= MAX_NUM) {
            present[arr2[i]] = 1;
        }
    }
    
    printf("Numbers from first array not present in second array: ");
    
    int found = 0;
    for (int i = 0; i < n1; i++) {
        if (arr1[i] >= 0 && arr1[i] <= MAX_NUM && present[arr1[i]] == 0) {
            printf("%d ", arr1[i]);
            found = 1;
            present[arr1[i]] = 1; // Mark as displayed to handle duplicates
        }
    }
    
    if (!found) {
        printf("None");
    }
    printf("\n");
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 3, 1, 0, 5};
    int n1 = 5;
    int n2 = 5;

    printf("Find Missing Elements Between Arrays\n");
    printf("=====================================\n");

    printf("First array: ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("Second array: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    findMissingElements(arr1, n1, arr2, n2);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Given Example
```
First array: 1 2 3 4 5
Second array: 2 3 1 0 5
Expected Output:
Numbers from first array not present in second array: 4
```

### Test Case 2: No Missing Elements
```
First array: 1 2 3
Second array: 1 2 3 4 5
Expected Output:
Numbers from first array not present in second array: None
```

### Test Case 3: Multiple Missing
```
First array: 1 2 3 4 5 6
Second array: 2 4 6
Expected Output:
Numbers from first array not present in second array: 1 3 5
```

## 🔍 Explanation

1. **Array Setup**: Use given arrays or accept input
2. **Presence Marking**: Mark elements present in second array
3. **Missing Detection**: Check first array against presence markers
4. **Output Display**: Show elements not found in second array
5. **Duplicate Handling**: Avoid displaying same missing number multiple times

## 🎯 Key Concepts Covered

- Set difference
- Frequency arrays
- Array comparison
- Presence checking
- Duplicate handling

## 🚀 Extensions

1. Find elements in second array not in first
2. Find common elements
3. Handle unsorted arrays
4. Support negative numbers