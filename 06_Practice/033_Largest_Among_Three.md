# 🎯 Practical 33: Largest Among Three Numbers

## 📋 Problem Statement

Write a C program to find the largest number among three numbers.

## 🎯 Learning Objectives

- Understand comparison operations
- Practice conditional statements
- Learn logical operators
- Understand input handling
- Practice decision making

## 📝 Requirements

1. Accept three numbers
2. Compare them
3. Find the largest
4. Display result
5. Handle equal numbers

## 💡 Hints

- Use if-else statements
- Compare pairwise
- Handle ties
- Use float for decimal numbers
- Clear output

## 🔧 Solution

```c
// Practical 33: Largest Among Three Numbers
// Finds the maximum of three numbers

#include <stdio.h>

int main() {
    float a, b, c, largest;

    printf("Find Largest Among Three Numbers\n");
    printf("=================================\n");

    printf("Enter first number: ");
    scanf("%f", &a);

    printf("Enter second number: ");
    scanf("%f", &b);

    printf("Enter third number: ");
    scanf("%f", &c);

    // Find largest using if-else
    if (a >= b && a >= c) {
        largest = a;
    } else if (b >= a && b >= c) {
        largest = b;
    } else {
        largest = c;
    }

    printf("The largest number is: %.2f\n", largest);

    // Check for equality
    if (a == b && b == c) {
        printf("All three numbers are equal.\n");
    } else if (a == b || a == c || b == c) {
        printf("Two numbers are equal.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Different Numbers
```
Input: 5, 8, 3
Expected Output:
The largest number is: 8.00
```

### Test Case 2: Two Equal
```
Input: 7, 7, 5
Expected Output:
The largest number is: 7.00
Two numbers are equal.
```

### Test Case 3: All Equal
```
Input: 4, 4, 4
Expected Output:
The largest number is: 4.00
All three numbers are equal.
```

## 🔍 Explanation

1. **Input**: Three floating point numbers
2. **Comparison**: Uses >= for largest
3. **Largest**: Stored in variable
4. **Equality Check**: Detects ties
5. **Output**: Clear result display

## 🎯 Key Concepts Covered

- Conditional statements
- Comparison operators
- Logical operators
- Input validation
- Decision making

## 🚀 Extensions

1. Find smallest number
2. Sort all three numbers
3. Handle n numbers
4. Add average calculation