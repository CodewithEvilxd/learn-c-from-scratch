# 🎯 Practical 72: Binary Decimal Conversion

## 📋 Problem Statement

Write a C program to convert binary number to decimal and vice-versa.

## 🎯 Learning Objectives

- Understand number system conversion
- Practice binary to decimal conversion
- Learn decimal to binary conversion
- Understand positional notation
- Practice string manipulation

## 📝 Requirements

1. Accept binary or decimal number
2. Convert between systems
3. Display both conversions
4. Validate input
5. Handle different bases

## 💡 Hints

- Binary to decimal: sum of digits * 2^position
- Decimal to binary: divide by 2, keep remainders
- Use strings for binary input
- Validate binary digits (0,1)
- Handle large numbers

## 🔧 Solution

```c
// Practical 72: Binary Decimal Conversion
// Converts between binary and decimal systems

#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to convert binary to decimal
long long binaryToDecimal(char *binary) {
    long long decimal = 0;
    int length = strlen(binary);

    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') {
            decimal += pow(2, length - 1 - i);
        } else if (binary[i] != '0') {
            return -1; // Invalid binary
        }
    }
    return decimal;
}

// Function to convert decimal to binary
void decimalToBinary(long long decimal, char *binary) {
    if (decimal == 0) {
        strcpy(binary, "0");
        return;
    }

    int index = 0;
    long long temp = decimal;

    while (temp > 0) {
        binary[index++] = (temp % 2) + '0';
        temp /= 2;
    }
    binary[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp_char = binary[i];
        binary[i] = binary[index - 1 - i];
        binary[index - 1 - i] = temp_char;
    }
}

int main() {
    int choice;
    char binary[65];
    long long decimal;
    char binary_result[65];

    printf("Number System Converter\n");
    printf("=======================\n");
    printf("1. Binary to Decimal\n");
    printf("2. Decimal to Binary\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter a binary number: ");
        scanf("%s", binary);

        decimal = binaryToDecimal(binary);
        if (decimal == -1) {
            printf("Invalid binary number! Only 0s and 1s allowed.\n");
        } else {
            printf("Binary %s = Decimal %lld\n", binary, decimal);
        }
    } else if (choice == 2) {
        printf("Enter a decimal number: ");
        scanf("%lld", &decimal);

        if (decimal < 0) {
            printf("Negative numbers not supported for binary conversion.\n");
        } else {
            decimalToBinary(decimal, binary_result);
            printf("Decimal %lld = Binary %s\n", decimal, binary_result);
        }
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Binary to Decimal
```
Choice: 1
Input: 1010
Expected Output:
Binary 1010 = Decimal 10
```

### Test Case 2: Decimal to Binary
```
Choice: 2
Input: 10
Expected Output:
Decimal 10 = Binary 1010
```

### Test Case 3: Invalid Binary
```
Choice: 1
Input: 1020
Expected Output:
Invalid binary number! Only 0s and 1s allowed.
```

## 🔍 Explanation

1. **Binary to Decimal**: Sum of binary digits * 2^position
2. **Decimal to Binary**: Repeated division by 2, collect remainders
3. **String Handling**: Binary input as string
4. **Validation**: Check for valid binary digits
5. **Reversal**: Binary result needs string reversal

## 🎯 Key Concepts Covered

- Number system conversion
- Positional notation
- String manipulation
- Mathematical operations
- Input validation

## 🚀 Extensions

1. Add octal and hexadecimal conversion
2. Handle fractional binary numbers
3. Convert between any two bases
4. Add conversion history