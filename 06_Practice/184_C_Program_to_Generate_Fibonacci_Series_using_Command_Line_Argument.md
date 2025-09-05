# 🎯 Practical 184: Generate Fibonacci Series using Command Line Argument

## 📋 Problem Statement

C Program to Generate Fibonacci Series using Command Line Argument.

## 🎯 Learning Objectives

- Understand command line argument processing
- Practice Fibonacci sequence generation
- Learn argument validation
- Understand series generation
- Practice iterative algorithms

## 📝 Requirements

1. Accept N from command line
2. Generate Fibonacci series up to N terms
3. Validate input arguments
4. Display series
5. Handle error cases

## 💡 Hints

- Use argc and argv
- Validate argument count
- Convert string to integer
- Implement Fibonacci algorithm
- Display series format

## 🔧 Solution

```c
// Practical 184: Generate Fibonacci Series using Command Line Argument
// Demonstrates command line argument processing and Fibonacci series generation

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n, i;
    long long first = 0, second = 1, next;

    printf("Fibonacci Series Generator\n");
    printf("==========================\n");

    // Check if correct number of arguments provided
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        printf("Example: %s 10\n", argv[0]);
        printf("\nGenerates first N Fibonacci numbers\n");
        return 1;
    }

    // Convert argument to integer
    n = atoi(argv[1]);

    // Validate input
    if (n < 1) {
        printf("Error: Number of terms must be positive and greater than 0\n");
        return 1;
    }

    if (n > 93) {
        printf("Warning: Large numbers may cause overflow\n");
        printf("Maximum recommended: 93 terms\n");
    }

    printf("Fibonacci Series (%d terms):\n", n);
    printf("==========================\n");

    // Generate and display Fibonacci series
    printf("0"); // First term

    for (i = 1; i < n; i++) {
        if (i == 1) {
            next = 1;
        } else {
            next = first + second;
            first = second;
            second = next;
        }

        printf(", %lld", next);
    }

    printf("\n\nSeries generation completed!\n");
    printf("Total terms generated: %d\n", n);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Input
```
Command: ./fibonacci 10
Expected Output:
Fibonacci Series (10 terms):
==========================
0, 1, 1, 2, 3, 5, 8, 13, 21, 34

Series generation completed!
Total terms generated: 10
```

### Test Case 2: Single Term
```
Command: ./fibonacci 1
Expected Output:
Fibonacci Series (1 terms):
==========================
0

Series generation completed!
Total terms generated: 1
```

### Test Case 3: Invalid Input
```
Command: ./fibonacci
Expected Output:
Usage: ./fibonacci <number_of_terms>
Example: ./fibonacci 10

Generates first N Fibonacci numbers
```

## 🔍 Explanation

1. **Argument Processing**: Use argc and argv for input
2. **Input Validation**: Check argument count and value
3. **Series Generation**: Implement iterative Fibonacci algorithm
4. **Output Formatting**: Display comma-separated series
5. **Error Handling**: Handle invalid inputs gracefully

## 🎯 Key Concepts Covered

- Command line arguments
- Input validation
- Fibonacci sequence
- Series generation
- Formatted output

## 🚀 Extensions

1. Add recursive option
2. Save series to file
3. Calculate sum of series
4. Find specific term position