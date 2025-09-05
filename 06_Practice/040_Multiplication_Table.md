# 🎯 Practical 40: Multiplication Table

## 📋 Problem Statement

Write a C program to generate multiplication table.

## 🎯 Learning Objectives

- Understand multiplication tables
- Practice nested loops
- Learn formatted output
- Understand table generation
- Practice input handling

## 📝 Requirements

1. Accept number and range
2. Generate multiplication table
3. Format output properly
4. Handle validation
5. Clear display

## 💡 Hints

- Use nested loops
- Format with proper spacing
- Accept range for table
- Validate inputs
- Clear headers

## 🔧 Solution

```c
// Practical 40: Multiplication Table
// Generates multiplication table for a number

#include <stdio.h>

int main() {
    int number, range;

    printf("Multiplication Table Generator\n");
    printf("===============================\n");

    printf("Enter the number: ");
    scanf("%d", &number);

    printf("Enter the range: ");
    scanf("%d", &range);

    if (range <= 0) {
        printf("Range must be positive!\n");
        return 1;
    }

    printf("\nMultiplication Table for %d:\n", number);
    printf("-----------------------------\n");

    for (int i = 1; i <= range; i++) {
        printf("%d x %2d = %3d\n", number, i, number * i);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Table
```
Input: 5, 10
Expected Output:
5 x  1 =   5
5 x  2 =  10
...
5 x 10 =  50
```

### Test Case 2: Larger Number
```
Input: 12, 12
Expected Output:
12 x  1 =  12
12 x  2 =  24
...
12 x 12 = 144
```

## 🔍 Explanation

1. **Input**: Number and range
2. **Loop**: From 1 to range
3. **Formatting**: Proper spacing with %2d, %3d
4. **Validation**: Positive range
5. **Output**: Clear table format

## 🎯 Key Concepts Covered

- Multiplication tables
- Formatted output
- Loop control
- Input validation
- Table generation

## 🚀 Extensions

1. Generate table for range of numbers
2. Add headers and borders
3. Save table to file
4. Interactive table navigation