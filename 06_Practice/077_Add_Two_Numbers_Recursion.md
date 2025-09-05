# 🎯 Practical 77: Add Two Numbers Using Recursion

## 📋 Problem Statement

Write a C program to add two numbers using recursion.

## 🎯 Learning Objectives

- Understand recursive addition
- Practice recursive functions
- Learn base cases for addition
- Understand recursive decrement
- Practice mathematical recursion

## 📝 Requirements

1. Accept two numbers
2. Add them using recursive function
3. Display the result
4. Handle negative numbers
5. Show recursive steps

## 💡 Hints

- Base case: add(a, 0) = a
- Recursive case: add(a, b) = add(a + 1, b - 1)
- Handle negative numbers
- Show addition steps
- Use proper base cases

## 🔧 Solution

```c
// Practical 77: Add Two Numbers Using Recursion
// Adds two numbers using recursive function

#include <stdio.h>

// Recursive function to add two numbers
int addRecursive(int a, int b) {
    // Base case: if second number is 0, return first number
    if (b == 0) {
        return a;
    }

    // Base case: if second number is negative, handle differently
    if (b < 0) {
        return addRecursive(a - 1, b + 1);
    }

    // Recursive case: increment first number, decrement second number
    return addRecursive(a + 1, b - 1);
}

int main() {
    int num1, num2, result;

    printf("Recursive Addition Calculator\n");
    printf("=============================\n");

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    result = addRecursive(num1, num2);

    printf("Result: %d + %d = %d\n", num1, num2, result);

    // Show the recursive process for small numbers
    if (abs(num1) <= 5 && abs(num2) <= 5) {
        printf("\nRecursive steps:\n");
        int x = num1, y = num2;
        while (y != 0) {
            if (y > 0) {
                printf("add(%d, %d) = add(%d, %d)\n", x, y, x + 1, y - 1);
                x = x + 1;
                y = y - 1;
            } else {
                printf("add(%d, %d) = add(%d, %d)\n", x, y, x - 1, y + 1);
                x = x - 1;
                y = y + 1;
            }
        }
        printf("Final result: %d\n", x);
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Positive Numbers
```
Input: 5, 3
Expected Output:
Result: 5 + 3 = 8
Recursive steps:
add(5, 3) = add(6, 2)
add(6, 2) = add(7, 1)
add(7, 1) = add(8, 0)
Final result: 8
```

### Test Case 2: One Zero
```
Input: 10, 0
Expected Output:
Result: 10 + 0 = 10
```

### Test Case 3: Negative Numbers
```
Input: 7, -2
Expected Output:
Result: 7 + (-2) = 5
```

## 🔍 Explanation

1. **Base Case**: When second number is 0, return first number
2. **Positive Addition**: Increment first, decrement second
3. **Negative Addition**: Decrement first, increment second
4. **Recursive Calls**: Continue until second number is 0
5. **Steps Display**: Show recursive process for small numbers

## 🎯 Key Concepts Covered

- Recursive functions
- Base cases
- Recursive addition
- Negative number handling
- Mathematical recursion

## 🚀 Extensions

1. Implement recursive subtraction
2. Add multiplication recursively
3. Handle very large numbers
4. Compare with iterative addition