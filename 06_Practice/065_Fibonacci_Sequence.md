# 🎯 Practical 65: Fibonacci Sequence

## 📋 Problem Statement

Write a C program to display Fibonacci sequence.

## 🎯 Learning Objectives

- Understand Fibonacci sequence
- Practice iterative sequence generation
- Learn variable swapping
- Understand sequence patterns
- Practice input validation

## 📝 Requirements

1. Accept number of terms
2. Generate Fibonacci sequence
3. Display the sequence
4. Handle edge cases
5. Show sequence properties

## 💡 Hints

- Start with 0, 1
- Each term is sum of previous two
- Use loop for generation
- Handle small n values
- Display clearly

## 🔧 Solution

```c
// Practical 65: Fibonacci Sequence
// Generates and displays Fibonacci sequence

#include <stdio.h>

int main() {
    int n, first = 0, second = 1, next;

    printf("Fibonacci Sequence Generator\n");
    printf("=============================\n");

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of terms must be positive!\n");
        return 1;
    }

    printf("Fibonacci Sequence:\n");

    for (int i = 0; i < n; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = first + second;
            first = second;
            second = next;
        }
        printf("%d", next);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("\n");

    // Reset for additional information
    first = 0;
    second = 1;

    if (n >= 1) {
        printf("First term (F₁): %d\n", first);
    }
    if (n >= 2) {
        printf("Second term (F₂): %d\n", second);
    }
    if (n >= 3) {
        printf("Ratio approximation: %.4f\n", (double)second / first);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Standard Sequence
```
Input: 8
Expected Output:
Fibonacci Sequence:
0, 1, 1, 2, 3, 5, 8, 13
First term (F₁): 0
Second term (F₂): 1
Ratio approximation: inf
```

### Test Case 2: Larger Sequence
```
Input: 10
Expected Output:
Fibonacci Sequence:
0, 1, 1, 2, 3, 5, 8, 13, 21, 34
First term (F₁): 0
Second term (F₂): 1
Ratio approximation: inf
```

### Test Case 3: Single Term
```
Input: 1
Expected Output:
Fibonacci Sequence:
0
First term (F₁): 0
```

## 🔍 Explanation

1. **Initialization**: first = 0, second = 1
2. **Loop**: Generate each term as sum of previous two
3. **Variable Swap**: Update first and second
4. **Display**: Comma-separated sequence
5. **Additional Info**: Show first terms and ratio

## 🎯 Key Concepts Covered

- Fibonacci sequence generation
- Variable swapping
- Loop implementation
- Sequence patterns
- Input validation

## 🚀 Extensions

1. Generate Fibonacci recursively
2. Check if number is Fibonacci
3. Find nth Fibonacci number
4. Calculate golden ratio