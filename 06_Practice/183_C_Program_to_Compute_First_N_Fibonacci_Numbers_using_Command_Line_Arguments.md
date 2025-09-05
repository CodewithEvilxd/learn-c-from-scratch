# 🎯 Practical 183: Compute First N Fibonacci Numbers using Command Line Arguments

## 📋 Problem Statement

C Program to Compute First N Fibonacci Numbers using Command Line Arguments.

## 🎯 Learning Objectives

- Understand command line argument processing
- Practice Fibonacci sequence generation
- Learn argument validation
- Understand main function parameters
- Practice iterative algorithms

## 📝 Requirements

1. Accept N from command line
2. Generate first N Fibonacci numbers
3. Validate input arguments
4. Display results
5. Handle error cases

## 💡 Hints

- Use argc and argv
- Validate argument count
- Convert string to integer
- Implement Fibonacci algorithm
- Handle invalid inputs

## 🔧 Solution

```c
// Practical 183: Compute First N Fibonacci Numbers using Command Line Arguments
// Demonstrates command line argument processing and Fibonacci generation

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n, i;
    long long first = 0, second = 1, next;

    printf("Fibonacci Series Generator\n");
    printf("==========================\n");

    // Check if correct number of arguments provided
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        printf("Example: %s 10\n", argv[0]);
        return 1;
    }

    // Convert argument to integer
    n = atoi(argv[1]);

    // Validate input
    if (n < 1) {
        printf("Error: Number must be positive and greater than 0\n");
        return 1;
    }

    if (n > 93) {
        printf("Warning: Large numbers may cause overflow\n");
        printf("Maximum recommended: 93\n");
    }

    printf("First %d Fibonacci numbers:\n", n);
    printf("==========================\n");

    // Generate and display Fibonacci series
    for (i = 0; i < n; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = first + second;
            first = second;
            second = next;
        }

        printf("F(%2d) = %lld\n", i, next);
    }

    printf("\nSeries generation completed!\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Input
```
Command: ./fibonacci 10
Expected Output:
First 10 Fibonacci numbers:
==========================
F( 0) = 0
F( 1) = 1
F( 2) = 1
F( 3) = 2
F( 4) = 3
F( 5) = 5
F( 6) = 8
F( 7) = 13
F( 8) = 21
F( 9) = 34
```

### Test Case 2: Invalid Input
```
Command: ./fibonacci
Expected Output:
Usage: ./fibonacci <number>
Example: ./fibonacci 10
```

### Test Case 3: Edge Case
```
Command: ./fibonacci 1
Expected Output:
First 1 Fibonacci numbers:
==========================
F( 0) = 0
```

## 🔍 Explanation

1. **Argument Processing**: Use argc and argv for input
2. **Input Validation**: Check argument count and value
3. **Fibonacci Generation**: Implement iterative algorithm
4. **Output Formatting**: Display with proper indexing
5. **Error Handling**: Handle invalid inputs gracefully

## 🎯 Key Concepts Covered

- Command line arguments
- Input validation
- Fibonacci sequence
- Iterative algorithms
- Error handling

## 🚀 Extensions

1. Add recursive Fibonacci option
2. Save results to file
3. Calculate golden ratio
4. Handle very large numbers