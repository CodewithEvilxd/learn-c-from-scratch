# 🎯 Practical 18: Number System Converter

## 📋 Problem Statement

Design a calculator that performs number system conversion.

## 🎯 Learning Objectives

- Understand number system conversions
- Practice string manipulation
- Learn mathematical algorithms
- Understand different bases
- Practice menu-driven programs

## 📝 Requirements

1. Convert between binary, decimal, octal, hexadecimal
2. Menu-driven interface
3. Handle input validation
4. Display results clearly
5. Support large numbers

## 💡 Hints

- Use functions for each conversion
- Handle string inputs for hex
- Use pow() for calculations
- Validate input formats
- Clear menu display

## 🔧 Solution

```c
// Practical 18: Number System Converter
// Converts between binary, decimal, octal, and hexadecimal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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
    while (decimal > 0) {
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = binary[i];
        binary[i] = binary[index - 1 - i];
        binary[index - 1 - i] = temp;
    }
}

// Function to convert octal to decimal
long long octalToDecimal(char *octal) {
    long long decimal = 0;
    int length = strlen(octal);

    for (int i = 0; i < length; i++) {
        if (octal[i] >= '0' && octal[i] <= '7') {
            decimal += (octal[i] - '0') * pow(8, length - 1 - i);
        } else {
            return -1; // Invalid octal
        }
    }
    return decimal;
}

// Function to convert decimal to octal
void decimalToOctal(long long decimal, char *octal) {
    if (decimal == 0) {
        strcpy(octal, "0");
        return;
    }

    int index = 0;
    while (decimal > 0) {
        octal[index++] = (decimal % 8) + '0';
        decimal /= 8;
    }
    octal[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = octal[i];
        octal[i] = octal[index - 1 - i];
        octal[index - 1 - i] = temp;
    }
}

// Function to convert hex to decimal
long long hexToDecimal(char *hex) {
    long long decimal = 0;
    int length = strlen(hex);

    for (int i = 0; i < length; i++) {
        int value;
        if (isdigit(hex[i])) {
            value = hex[i] - '0';
        } else if (isupper(hex[i])) {
            value = hex[i] - 'A' + 10;
        } else if (islower(hex[i])) {
            value = hex[i] - 'a' + 10;
        } else {
            return -1; // Invalid hex
        }
        decimal += value * pow(16, length - 1 - i);
    }
    return decimal;
}

// Function to convert decimal to hex
void decimalToHex(long long decimal, char *hex) {
    if (decimal == 0) {
        strcpy(hex, "0");
        return;
    }

    int index = 0;
    while (decimal > 0) {
        int remainder = decimal % 16;
        if (remainder < 10) {
            hex[index++] = remainder + '0';
        } else {
            hex[index++] = remainder - 10 + 'A';
        }
        decimal /= 16;
    }
    hex[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = hex[i];
        hex[i] = hex[index - 1 - i];
        hex[index - 1 - i] = temp;
    }
}

int main() {
    int choice;
    char input[100], output[100];
    long long decimal;

    while (1) {
        printf("\nNumber System Converter\n");
        printf("=======================\n");
        printf("1. Binary to Decimal\n");
        printf("2. Decimal to Binary\n");
        printf("3. Octal to Decimal\n");
        printf("4. Decimal to Octal\n");
        printf("5. Hexadecimal to Decimal\n");
        printf("6. Decimal to Hexadecimal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 7) {
            printf("Exiting converter...\n");
            break;
        }

        printf("Enter the number: ");
        scanf("%s", input);

        switch (choice) {
            case 1:
                decimal = binaryToDecimal(input);
                if (decimal == -1) {
                    printf("Invalid binary number!\n");
                } else {
                    printf("Binary %s = Decimal %lld\n", input, decimal);
                }
                break;
            case 2:
                decimal = atoll(input);
                decimalToBinary(decimal, output);
                printf("Decimal %lld = Binary %s\n", decimal, output);
                break;
            case 3:
                decimal = octalToDecimal(input);
                if (decimal == -1) {
                    printf("Invalid octal number!\n");
                } else {
                    printf("Octal %s = Decimal %lld\n", input, decimal);
                }
                break;
            case 4:
                decimal = atoll(input);
                decimalToOctal(decimal, output);
                printf("Decimal %lld = Octal %s\n", decimal, output);
                break;
            case 5:
                decimal = hexToDecimal(input);
                if (decimal == -1) {
                    printf("Invalid hexadecimal number!\n");
                } else {
                    printf("Hexadecimal %s = Decimal %lld\n", input, decimal);
                }
                break;
            case 6:
                decimal = atoll(input);
                decimalToHex(decimal, output);
                printf("Decimal %lld = Hexadecimal %s\n", decimal, output);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Binary to Decimal
```
Input: 1010
Expected Output:
Binary 1010 = Decimal 10
```

### Test Case 2: Decimal to Hex
```
Input: 255
Expected Output:
Decimal 255 = Hexadecimal FF
```

### Test Case 3: Hex to Decimal
```
Input: 1A
Expected Output:
Hexadecimal 1A = Decimal 26
```

## 🔍 Explanation

1. **Binary Conversion**: Uses pow(2, position)
2. **Octal Conversion**: Uses pow(8, position)
3. **Hex Conversion**: Handles A-F characters
4. **Decimal Output**: Uses string reversal
5. **Input Validation**: Checks for valid digits

## 🎯 Key Concepts Covered

- Number system mathematics
- String manipulation
- Power calculations
- Character validation
- Menu-driven interface

## 🚀 Extensions

1. Add direct conversions (binary to hex)
2. Support negative numbers
3. Add more number systems
4. Save conversion history