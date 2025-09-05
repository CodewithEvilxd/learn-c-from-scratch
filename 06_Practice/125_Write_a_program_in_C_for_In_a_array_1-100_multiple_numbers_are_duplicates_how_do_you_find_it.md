# 🎯 Practical 125: Find Duplicate Numbers in Array 1-100

## 📋 Problem Statement

Write a program in C for, In a array 1-100 multiple numbers are duplicates, how do you find it.

## 🎯 Learning Objectives

- Understand duplicate detection
- Practice frequency counting
- Learn array-based duplicate finding
- Understand hash-like techniques
- Practice conditional output

## 📝 Requirements

1. Accept array with numbers 1-100 (with duplicates)
2. Find all duplicate numbers
3. Display duplicate numbers and their frequencies
4. Handle multiple duplicates
5. Show clear output

## 💡 Hints

- Use frequency array of size 101
- Count occurrences of each number
- Numbers appearing more than once are duplicates
- Display number and count
- Handle edge cases

## 🔧 Solution

```c
// Practical 125: Find Duplicate Numbers in Array 1-100
// Finds and displays all duplicate numbers with their frequencies

#include <stdio.h>

#define MAX_NUM 100

void findDuplicates(int arr[], int n) {
    int frequency[MAX_NUM + 1] = {0};
    
    // Count frequency of each number
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 1 && arr[i] <= MAX_NUM) {
            frequency[arr[i]]++;
        }
    }
    
    printf("Duplicate numbers found:\n");
    int found = 0;
    
    // Find and display duplicates
    for (int i = 1; i <= MAX_NUM; i++) {
        if (frequency[i] > 1) {
            printf("Number %d appears %d times\n", i, frequency[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No duplicates found!\n");
    }
}

int main() {
    int n;
    int arr[200]; // Allow for duplicates

    printf("Find Duplicate Numbers (1-100)\n");
    printf("================================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d numbers (1-100, may contain duplicates): ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findDuplicates(arr, n);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multiple Duplicates
```
Input: 1 2 2 3 3 3 4 5
Expected Output:
Duplicate numbers found:
Number 2 appears 2 times
Number 3 appears 3 times
```

### Test Case 2: No Duplicates
```
Input: 1 2 3 4 5
Expected Output:
No duplicates found!
```

### Test Case 3: Single Number Multiple Times
```
Input: 1 1 1 1 1
Expected Output:
Duplicate numbers found:
Number 1 appears 5 times
```

## 🔍 Explanation

1. **Input Reading**: Read array elements from user
2. **Frequency Counting**: Count occurrences using frequency array
3. **Duplicate Detection**: Find numbers with count > 1
4. **Output Display**: Show duplicates with their frequencies
5. **Edge Case Handling**: Handle no duplicates scenario

## 🎯 Key Concepts Covered

- Frequency analysis
- Array indexing
- Duplicate detection
- Conditional output
- Boundary checking

## 🚀 Extensions

1. Find first duplicate only
2. Remove duplicates from array
3. Find most frequent number
4. Handle numbers outside 1-100 range