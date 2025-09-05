# 🎯 Practical 147: Find Highest Frequency Element in Array

## 📋 Problem Statement

C Program to find highest frequency element in array.

## 🎯 Learning Objectives

- Understand frequency analysis
- Practice counting techniques
- Learn maximum frequency finding
- Understand element tracking
- Practice array processing

## 📝 Requirements

1. Accept array of integers
2. Count frequency of each element
3. Find element with highest frequency
4. Display element and its frequency
5. Handle ties appropriately

## 💡 Hints

- Use frequency array or map
- Track maximum frequency
- Keep track of element with max frequency
- Handle negative numbers
- Display clear results

## 🔧 Solution

```c
// Practical 147: Find Highest Frequency Element in Array
// Demonstrates finding the most frequent element

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 100
#define FREQ_SIZE 201 // For numbers -100 to 100

void findHighestFrequency(int arr[], int n) {
    int frequency[FREQ_SIZE] = {0};
    int maxFreq = 0;
    int mostFrequent = INT_MIN;
    
    // Count frequencies
    for (int i = 0; i < n; i++) {
        if (arr[i] >= -100 && arr[i] <= 100) {
            int index = arr[i] + 100; // Shift to positive indices
            frequency[index]++;
            
            if (frequency[index] > maxFreq) {
                maxFreq = frequency[index];
                mostFrequent = arr[i];
            }
        }
    }
    
    if (mostFrequent == INT_MIN) {
        printf("No valid elements found!\n");
    } else {
        printf("Element with highest frequency: %d\n", mostFrequent);
        printf("Frequency: %d\n", maxFreq);
    }
}

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Find Highest Frequency Element\n");
    printf("==============================\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid array size! Must be between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    findHighestFrequency(arr, n);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Clear Winner
```
Input: 8 elements: 1 2 2 3 2 4 2 5
Expected Output:
Array: 1 2 2 3 2 4 2 5
Element with highest frequency: 2
Frequency: 4
```

### Test Case 2: Tie
```
Input: 6 elements: 1 1 2 2 3 3
Expected Output:
Array: 1 1 2 2 3 3
Element with highest frequency: 1
Frequency: 2
```

### Test Case 3: All Unique
```
Input: 4 elements: 1 2 3 4
Expected Output:
Array: 1 2 3 4
Element with highest frequency: 1
Frequency: 1
```

### Test Case 4: Single Element
```
Input: 1 element: 5
Expected Output:
Array: 5
Element with highest frequency: 5
Frequency: 1
```

## 🔍 Explanation

1. **Input Reading**: Read array size and elements
2. **Frequency Counting**: Count occurrences using frequency array
3. **Maximum Tracking**: Track element with highest frequency
4. **Result Display**: Show most frequent element and count
5. **Edge Cases**: Handle arrays with all unique elements

## 🎯 Key Concepts Covered

- Frequency analysis
- Array processing
- Maximum finding
- Element tracking
- Boundary handling

## 🚀 Extensions

1. Find all elements with maximum frequency
2. Find k most frequent elements
3. Handle larger number ranges
4. Sort by frequency