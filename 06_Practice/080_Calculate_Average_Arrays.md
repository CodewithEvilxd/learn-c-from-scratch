# 🎯 Practical 80: Calculate Average Using Arrays

## 📋 Problem Statement

Write a C program to calculate average using arrays.

## 🎯 Learning Objectives

- Understand array operations
- Practice average calculation
- Learn array input/output
- Understand data processing
- Practice loop implementation

## 📝 Requirements

1. Accept array of numbers
2. Calculate sum of elements
3. Compute average
4. Display results
5. Handle different array sizes

## 💡 Hints

- Use array to store numbers
- Loop to calculate sum
- Divide sum by count for average
- Use float for decimal results
- Validate array size

## 🔧 Solution

```c
// Practical 80: Calculate Average Using Arrays
// Calculates average of numbers stored in an array

#include <stdio.h>

int main() {
    int n;
    float sum = 0, average;
    
    printf("Calculate Average Using Arrays\n");
    printf("===============================\n");
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Number of elements must be positive!\n");
        return 1;
    }
    
    float numbers[n];
    
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Number %d: ", i + 1);
        scanf("%f", &numbers[i]);
        sum += numbers[i];
    }
    
    average = sum / n;
    
    printf("\nNumbers entered: ");
    for (int i = 0; i < n; i++) {
        printf("%.2f", numbers[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    
    printf("\nSum: %.2f\n", sum);
    printf("Average: %.2f\n", average);
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Integer Numbers
```
Input: n=5, numbers=[10, 20, 30, 40, 50]
Expected Output:
Sum: 150.00
Average: 30.00
```

### Test Case 2: Decimal Numbers
```
Input: n=3, numbers=[1.5, 2.5, 3.0]
Expected Output:
Sum: 7.00
Average: 2.33
```

### Test Case 3: Single Element
```
Input: n=1, numbers=[42]
Expected Output:
Sum: 42.00
Average: 42.00
```

## 🔍 Explanation

1. **Array Declaration**: Variable size array
2. **Input Loop**: Read numbers into array
3. **Sum Calculation**: Accumulate in loop
4. **Average**: sum / n
5. **Display**: Show all numbers and results

## 🎯 Key Concepts Covered

- Array declaration and usage
- Loop implementation
- Sum and average calculation
- Input validation
- Float precision

## 🚀 Extensions

1. Find minimum and maximum values
2. Calculate median
3. Sort the array
4. Handle dynamic array size