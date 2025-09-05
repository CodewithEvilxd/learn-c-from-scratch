# 🎯 Practical 64: Multiplication Table

## 📋 Problem Statement

Write a C program to generate multiplication table.

## 🎯 Learning Objectives

- Understand multiplication tables
- Practice nested loops
- Learn formatted output
- Understand table generation
- Practice input validation

## 📝 Requirements

1. Accept a number
2. Generate multiplication table
3. Display up to 10 or custom range
4. Format output clearly
5. Handle edge cases

## 💡 Hints

- Use loop from 1 to 10
- Format: num × i = result
- Accept table size
- Clear table layout
- Handle zero and negative

## 🔧 Solution

```c
// Practical 64: Multiplication Table
// Generates multiplication table for a number

#include <stdio.h>

int main() {
    int number, range;

    printf("Multiplication Table Generator\n");
    printf("===============================\n");

    printf("Enter the number: ");
    scanf("%d", &number);

    printf("Enter the range (up to which multiple): ");
    scanf("%d", &range);

    if (range <= 0) {
        printf("Range must be positive!\n");
        return 1;
    }

    printf("\nMultiplication Table for %d:\n", number);
    printf("----------------------------\n");

    for (int i = 1; i <= range; i++) {
        printf("%d × %2d = %3d\n", number, i, number * i);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Standard Table
```
Input: Number=5, Range=10
Expected Output:
Multiplication Table for 5:
----------------------------
5 ×  1 =   5
5 ×  2 =  10
5 ×  3 =  15
5 ×  4 =  20
5 ×  5 =  25
5 ×  6 =  30
5 ×  7 =  35
5 ×  8 =  40
5 ×  9 =  45
5 × 10 =  50
```

### Test Case 2: Custom Range
```
Input: Number=7, Range=5
Expected Output:
Multiplication Table for 7:
----------------------------
7 × 1 =  7
7 × 2 = 14
7 × 3 = 21
7 × 4 = 28
7 × 5 = 35
```

### Test Case 3: Zero
```
Input: Number=0, Range=3
Expected Output:
Multiplication Table for 0:
----------------------------
0 × 1 = 0
0 × 2 = 0
0 × 3 = 0
```

## 🔍 Explanation

1. **Input**: Number and range
2. **Loop**: Generate table from 1 to range
3. **Formatting**: Aligned columns
4. **Display**: Clear table layout
5. **Validation**: Handle invalid range

## 🎯 Key Concepts Covered

- Loop implementation
- Formatted output
- Multiplication operations
- Input validation
- Table generation

## 🚀 Extensions

1. Generate table for range of numbers
2. Add horizontal table format
3. Include negative numbers
4. Save table to file