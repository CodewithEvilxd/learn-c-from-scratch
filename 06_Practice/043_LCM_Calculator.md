# 🎯 Practical 43: LCM Calculator

## 📋 Problem Statement

Write a C program to find LCM of two numbers.

## 🎯 Learning Objectives

- Understand LCM concept
- Practice GCD-LCM relationship
- Learn mathematical calculations
- Understand least common multiple
- Practice function reuse

## 📝 Requirements

1. Accept two numbers
2. Calculate LCM
3. Use GCD method
4. Handle validation
5. Display result

## 💡 Hints

- LCM = (a*b)/gcd(a,b)
- Reuse GCD function
- Handle large numbers
- Validate inputs
- Clear output

## 🔧 Solution

```c
// Practical 43: LCM Calculator
// Calculates LCM using GCD

#include <stdio.h>

// GCD function
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM function
long long lcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0; // LCM with 0 is undefined, but we'll return 0
    }

    a = abs(a);
    b = abs(b);

    return (long long)a * b / gcd(a, b);
}

int main() {
    int num1, num2;
    long long lcm_result;

    printf("LCM Calculator\n");
    printf("==============\n");

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    lcm_result = lcm(num1, num2);

    printf("LCM of %d and %d is: %lld\n", num1, num2, lcm_result);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Different Numbers
```
Input: 4, 6
Expected Output:
LCM: 12
```

### Test Case 2: Same Numbers
```
Input: 5, 5
Expected Output:
LCM: 5
```

### Test Case 3: Prime Numbers
```
Input: 7, 11
Expected Output:
LCM: 77
```

## 🔍 Explanation

1. **Formula**: LCM = (a*b)/gcd(a,b)
2. **GCD Function**: Reused from previous
3. **Data Type**: long long for large products
4. **Absolute Values**: Handle negatives
5. **Edge Cases**: Handle zeros

## 🎯 Key Concepts Covered

- LCM calculation
- GCD-LCM relationship
- Mathematical formulas
- Function reuse
- Large number handling

## 🚀 Extensions

1. Calculate LCM of multiple numbers
2. Add GCD calculation
3. Handle fractions
4. Performance optimization