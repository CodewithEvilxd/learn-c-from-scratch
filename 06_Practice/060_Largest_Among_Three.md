# 🎯 Practical 60: Largest Among Three Numbers

## 📋 Problem Statement

Write a C program to find the largest number among three numbers.

## 🎯 Learning Objectives

- Understand comparison operations
- Practice conditional statements
- Learn logical operators
- Understand input validation
- Practice decision making

## 📝 Requirements

1. Accept three numbers
2. Compare them to find largest
3. Display the result
4. Handle equal numbers
5. Use proper logic

## 💡 Hints

- Use if-else statements
- Compare pairwise
- Handle ties properly
- Use clear variable names
- Display all numbers and result

## 🔧 Solution

```c
// Practical 60: Largest Among Three Numbers
// Finds the maximum of three input numbers

#include <stdio.h>

int main() {
    double num1, num2, num3, largest;

    printf("Find Largest Among Three Numbers\n");
    printf("=================================\n");

    printf("Enter first number: ");
    scanf("%lf", &num1);

    printf("Enter second number: ");
    scanf("%lf", &num2);

    printf("Enter third number: ");
    scanf("%lf", &num3);

    // Find largest using if-else
    if (num1 >= num2 && num1 >= num3) {
        largest = num1;
    } else if (num2 >= num1 && num2 >= num3) {
        largest = num2;
    } else {
        largest = num3;
    }

    printf("\nNumbers entered: %.2f, %.2f, %.2f\n", num1, num2, num3);
    printf("Largest number: %.2f\n", largest);

    // Check for equality
    if (num1 == num2 && num2 == num3) {
        printf("All three numbers are equal.\n");
    } else if (num1 == num2 || num1 == num3 || num2 == num3) {
        printf("Two numbers are equal.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Different Numbers
```
Input: 15.5, 23.8, 12.3
Expected Output:
Numbers entered: 15.50, 23.80, 12.30
Largest number: 23.80
```

### Test Case 2: Two Equal
```
Input: 10, 10, 5
Expected Output:
Numbers entered: 10.00, 10.00, 5.00
Largest number: 10.00
Two numbers are equal.
```

### Test Case 3: All Equal
```
Input: 7, 7, 7
Expected Output:
Numbers entered: 7.00, 7.00, 7.00
Largest number: 7.00
All three numbers are equal.
```

## 🔍 Explanation

1. **Input**: Accept three double precision numbers
2. **Comparison**: Use >= to handle equal values
3. **Largest**: Store in variable and display
4. **Equality Check**: Detect ties between numbers
5. **Output**: Clear display of results

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