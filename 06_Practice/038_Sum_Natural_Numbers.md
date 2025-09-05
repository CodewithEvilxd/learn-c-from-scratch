# 🎯 Practical 38: Sum of Natural Numbers

## 📋 Problem Statement

Write a C program to calculate the sum of natural numbers.

## 🎯 Learning Objectives

- Understand natural numbers
- Practice mathematical formulas
- Learn iterative summation
- Understand formula vs loop
- Practice input validation

## 📝 Requirements

1. Accept number n
2. Calculate sum 1 to n
3. Use formula method
4. Use loop method
5. Display results

## 💡 Hints

- Formula: n*(n+1)/2
- Loop: for(i=1; i<=n; i++) sum+=i
- Use long long for large sums
- Validate positive n
- Compare methods

## 🔧 Solution

```c
// Practical 38: Sum of Natural Numbers
// Calculates sum of first n natural numbers

#include <stdio.h>

// Formula method
long long sumFormula(int n) {
    return (long long)n * (n + 1) / 2;
}

// Iterative method
long long sumIterative(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    int n;
    long long sum_form, sum_iter;

    printf("Sum of Natural Numbers\n");
    printf("======================\n");

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer!\n");
        return 1;
    }

    sum_form = sumFormula(n);
    sum_iter = sumIterative(n);

    printf("Sum of first %d natural numbers:\n", n);
    printf("Using formula: %lld\n", sum_form);
    printf("Using iteration: %lld\n", sum_iter);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Small Number
```
Input: 5
Expected Output:
Sum: 15
```

### Test Case 2: Larger Number
```
Input: 10
Expected Output:
Sum: 55
```

### Test Case 3: Large Number
```
Input: 100
Expected Output:
Sum: 5050
```

## 🔍 Explanation

1. **Formula**: n*(n+1)/2
2. **Iterative**: Loop from 1 to n
3. **Data Type**: long long for large sums
4. **Validation**: Positive integer check
5. **Comparison**: Both methods give same result

## 🎯 Key Concepts Covered

- Natural number summation
- Mathematical formulas
- Iterative calculation
- Large number handling
- Input validation

## 🚀 Extensions

1. Sum of squares
2. Sum of cubes
3. Sum of even numbers
4. Performance comparison