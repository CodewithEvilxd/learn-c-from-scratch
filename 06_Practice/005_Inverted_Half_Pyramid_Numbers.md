# 🎯 Practical 5: Inverted Half Pyramid of Numbers

## 📋 Problem Statement

Write a C Program to implement an inverted half pyramid of numbers.

## 🎯 Learning Objectives

- Understand reverse number pattern printing
- Practice decreasing loop sequences
- Learn number pattern inversion
- Understand row-column relationships in reverse

## 📝 Requirements

1. Accept number of rows from user
2. Print numbers in inverted half pyramid pattern
3. Use nested loops with reverse logic
4. Display numbers with proper spacing
5. Handle input validation

## 💡 Hints

- Use outer loop from rows down to 1
- Use inner loop to print numbers 1 to current row
- Print numbers sequentially in each row
- Use proper spacing between numbers

## 🔧 Solution

```c
// Practical 5: Inverted Half Pyramid of Numbers
// This program prints an inverted half pyramid pattern using numbers

#include <stdio.h>

int main() {
    int rows;

    // Get number of rows from user
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    // Input validation
    if (rows <= 0) {
        printf("Please enter a positive number!\n");
        return 1;
    }

    printf("Inverted Half Pyramid of Numbers:\n");
    printf("=================================\n");

    // Outer loop for rows (decreasing)
    for (int i = rows; i >= 1; i--) {
        // Inner loop for numbers in each row
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Input
```
Input: 5
Expected Output:
Inverted Half Pyramid of Numbers:
=================================
1 2 3 4 5
1 2 3 4
1 2 3
1 2
1
```

### Test Case 2: Single Row
```
Input: 1
Expected Output:
Inverted Half Pyramid of Numbers:
=================================
1
```

### Test Case 3: Larger Pattern
```
Input: 7
Expected Output:
Inverted Half Pyramid of Numbers:
=================================
1 2 3 4 5 6 7
1 2 3 4 5 6
1 2 3 4 5
1 2 3 4
1 2 3
1 2
1
```

## 🔍 Explanation

1. **Outer Loop**: Starts from rows and decreases to 1
2. **Inner Loop**: Prints numbers 1 to i for each row
3. **Reverse Pattern**: Top row has most numbers, bottom has least
4. **Sequential Numbers**: Each row starts from 1
5. **Decreasing Length**: Row length decreases by 1 each time

## 🎯 Key Concepts Covered

- Reverse pattern printing
- Decreasing loop sequences
- Number pattern generation
- Nested loop control
- Pattern inversion logic

## 🚀 Extensions

1. Print numbers in reverse order per row
2. Print only even numbers in each row
3. Add sum calculation for each row
4. Print numbers in descending order