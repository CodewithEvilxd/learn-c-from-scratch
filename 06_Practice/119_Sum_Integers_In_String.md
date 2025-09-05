# 🎯 Practical 119: Sum of Integers in String

## 📋 Problem Statement

Write a C program to calculate sum of integers in string.

## 🎯 Learning Objectives

- Understand string parsing
- Practice number extraction
- Learn atoi() function
- Understand digit sequence handling
- Practice summation algorithms

## 📝 Requirements

1. Accept a string with numbers
2. Extract all integers
3. Calculate their sum
4. Handle multiple numbers
5. Display results clearly

## 💡 Hints

- Traverse string character by character
- Identify digit sequences
- Convert to integers using atoi()
- Accumulate sum
- Handle negative numbers

## 🔧 Solution

```c
// Practical 119: Sum of Integers in String
// Extracts and sums all integers found in a string

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int sumOfIntegersInString(char *str) {
    int sum = 0;
    char temp[20]; // Temporary buffer for number
    int tempIndex = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) || (str[i] == '-' && isdigit(str[i + 1]))) {
            // Start of a number
            temp[tempIndex++] = str[i];
            
            // Continue reading digits
            while (isdigit(str[i + 1]) && tempIndex < 19) {
                i++;
                temp[tempIndex++] = str[i];
            }
            
            temp[tempIndex] = '\0';
            
            // Convert to integer and add to sum
            sum += atoi(temp);
            tempIndex = 0;
        }
    }
    
    return sum;
}

int main() {
    char str[1000];
    int sum;

    printf("Sum of Integers in String\n");
    printf("=========================\n");

    printf("Enter a string with numbers: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    sum = sumOfIntegersInString(str);

    printf("String: \"%s\"\n", str);
    printf("Sum of integers: %d\n", sum);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Multiple Numbers
```
Input: The price is 100 and tax is 20
Expected Output:
String: "The price is 100 and tax is 20"
Sum of integers: 120
```

### Test Case 2: Negative Numbers
```
Input: Profit: 500, Loss: -200
Expected Output:
String: "Profit: 500, Loss: -200"
Sum of integers: 300
```

### Test Case 3: No Numbers
```
Input: Hello World
Expected Output:
String: "Hello World"
Sum of integers: 0
```

### Test Case 4: Mixed Characters
```
Input: Order 123 items for $456
Expected Output:
String: "Order 123 items for $456"
Sum of integers: 579
```

## 🔍 Explanation

1. **String Parsing**: Traverse character by character
2. **Number Detection**: Identify digit sequences
3. **Number Extraction**: Build temporary number strings
4. **Conversion**: Use atoi() to convert to integers
5. **Summation**: Accumulate all extracted numbers

## 🎯 Key Concepts Covered

- String parsing
- Number extraction
- atoi() function usage
- Character sequence handling
- Summation algorithms

## 🚀 Extensions

1. Handle decimal numbers
2. Extract and sum specific number ranges
3. Handle hexadecimal numbers
4. Calculate product instead of sum