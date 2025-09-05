# 🎯 Assignment 1.13: Bitwise Operators

## 📋 Problem Statement

Create a C program that demonstrates all bitwise operators and their practical applications. Implement functions for bit manipulation, flag management, and data compression techniques.

## 🎯 Learning Objectives

- Understand bitwise operators (&, |, ^, ~, <<, >>)
- Learn bit manipulation techniques
- Practice flag management with bits
- Implement data compression algorithms
- Understand bit-level operations
- Work with binary representation

## 📝 Requirements

1. Demonstrate all bitwise operators
2. Show binary representation of numbers
3. Implement bit manipulation functions
4. Create a flag system using bits
5. Implement simple data compression
6. Show practical applications (permissions, etc.)
7. Handle edge cases and overflow

## 💡 Hints

- Use bitwise operators for efficient operations
- Left shift multiplies by powers of 2
- Right shift divides by powers of 2
- XOR can swap values without temporary variable
- Use masks for bit manipulation
- Be careful with signed vs unsigned types

## 🔧 Solution

```c
// Assignment 1.13: Bitwise Operators
// Bit manipulation and practical applications

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Function prototypes
void print_binary(uint32_t num);
void demonstrate_bitwise_operators();
void demonstrate_bit_manipulation();
void demonstrate_flag_system();
void demonstrate_data_compression();

// Bit manipulation functions
bool get_bit(uint32_t num, int position);
uint32_t set_bit(uint32_t num, int position);
uint32_t clear_bit(uint32_t num, int position);
uint32_t toggle_bit(uint32_t num, int position);
int count_bits(uint32_t num);
uint32_t reverse_bits(uint32_t num);

// Flag system
#define FLAG_READ 0x01
#define FLAG_WRITE 0x02
#define FLAG_EXECUTE 0x04
#define FLAG_ADMIN 0x08

void set_permission(uint8_t* permissions, uint8_t flag);
void clear_permission(uint8_t* permissions, uint8_t flag);
bool has_permission(uint8_t permissions, uint8_t flag);
void print_permissions(uint8_t permissions);

// Simple run-length encoding
typedef struct {
    uint8_t value;
    uint8_t count;
} RLEPair;

void compress_rle(const uint8_t* data, int size, RLEPair* compressed, int* compressed_size);
void decompress_rle(const RLEPair* compressed, int compressed_size, uint8_t* decompressed, int* decompressed_size);

int main() {
    printf("=== Bitwise Operators Demonstration ===\n\n");

    demonstrate_bitwise_operators();
    demonstrate_bit_manipulation();
    demonstrate_flag_system();
    demonstrate_data_compression();

    return 0;
}

void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}

void demonstrate_bitwise_operators() {
    printf("1. Bitwise Operators\n");

    uint32_t a = 60;  // 0011 1100
    uint32_t b = 13;  // 0000 1101

    printf("a = %u (", a);
    print_binary(a);
    printf("b = %u (", b);
    print_binary(b);

    printf("\nBitwise Operations:\n");
    printf("a & b = %u (", a & b);
    print_binary(a & b);
    printf("a | b = %u (", a | b);
    print_binary(a | b);
    printf("a ^ b = %u (", a ^ b);
    print_binary(a ^ b);
    printf("~a = %u (", ~a);
    print_binary(~a);
    printf("a << 2 = %u (", a << 2);
    print_binary(a << 2);
    printf("a >> 2 = %u (", a >> 2);
    print_binary(a >> 2);

    printf("\n");
}

void demonstrate_bit_manipulation() {
    printf("2. Bit Manipulation Functions\n");

    uint32_t num = 42;  // 101010
    printf("Original number: %u\n", num);
    print_binary(num);

    // Test bit manipulation
    printf("\nBit at position 3: %s\n", get_bit(num, 3) ? "SET" : "CLEAR");

    num = set_bit(num, 5);
    printf("After setting bit 5: %u\n", num);
    print_binary(num);

    num = clear_bit(num, 1);
    printf("After clearing bit 1: %u\n", num);
    print_binary(num);

    num = toggle_bit(num, 0);
    printf("After toggling bit 0: %u\n", num);
    print_binary(num);

    printf("Number of set bits: %d\n", count_bits(num));
    printf("Reversed bits: %u\n", reverse_bits(num));
    print_binary(reverse_bits(num));

    printf("\n");
}

void demonstrate_flag_system() {
    printf("3. Flag System (File Permissions)\n");

    uint8_t permissions = 0;

    printf("Initial permissions: ");
    print_permissions(permissions);

    set_permission(&permissions, FLAG_READ);
    set_permission(&permissions, FLAG_WRITE);
    printf("After setting read and write: ");
    print_permissions(permissions);

    if (has_permission(permissions, FLAG_READ)) {
        printf("Read permission granted\n");
    }

    clear_permission(&permissions, FLAG_WRITE);
    printf("After clearing write permission: ");
    print_permissions(permissions);

    printf("\n");
}

void demonstrate_data_compression() {
    printf("4. Data Compression (Run-Length Encoding)\n");

    uint8_t data[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 5, 5};
    int data_size = sizeof(data) / sizeof(data[0]);

    printf("Original data: ");
    for (int i = 0; i < data_size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    RLEPair compressed[20];
    int compressed_size = 0;

    compress_rle(data, data_size, compressed, &compressed_size);

    printf("Compressed data (%d pairs):\n", compressed_size);
    for (int i = 0; i < compressed_size; i++) {
        printf("(%d, %d) ", compressed[i].value, compressed[i].count);
    }
    printf("\n");

    uint8_t decompressed[50];
    int decompressed_size = 0;

    decompress_rle(compressed, compressed_size, decompressed, &decompressed_size);

    printf("Decompressed data: ");
    for (int i = 0; i < decompressed_size; i++) {
        printf("%d ", decompressed[i]);
    }
    printf("\n");

    printf("Compression ratio: %.2f%%\n",
           (1.0 - (double)compressed_size * 2 / data_size) * 100);

    printf("\n");
}

// Bit manipulation functions
bool get_bit(uint32_t num, int position) {
    return (num >> position) & 1;
}

uint32_t set_bit(uint32_t num, int position) {
    return num | (1U << position);
}

uint32_t clear_bit(uint32_t num, int position) {
    return num & ~(1U << position);
}

uint32_t toggle_bit(uint32_t num, int position) {
    return num ^ (1U << position);
}

int count_bits(uint32_t num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

uint32_t reverse_bits(uint32_t num) {
    uint32_t reversed = 0;
    for (int i = 0; i < 32; i++) {
        reversed |= ((num >> i) & 1) << (31 - i);
    }
    return reversed;
}

// Flag system functions
void set_permission(uint8_t* permissions, uint8_t flag) {
    *permissions |= flag;
}

void clear_permission(uint8_t* permissions, uint8_t flag) {
    *permissions &= ~flag;
}

bool has_permission(uint8_t permissions, uint8_t flag) {
    return (permissions & flag) != 0;
}

void print_permissions(uint8_t permissions) {
    printf("Permissions: ");
    if (permissions & FLAG_READ) printf("R");
    if (permissions & FLAG_WRITE) printf("W");
    if (permissions & FLAG_EXECUTE) printf("X");
    if (permissions & FLAG_ADMIN) printf("A");
    if (permissions == 0) printf("None");
    printf("\n");
}

// RLE functions
void compress_rle(const uint8_t* data, int size, RLEPair* compressed, int* compressed_size) {
    if (size == 0) return;

    int comp_idx = 0;
    uint8_t current_value = data[0];
    uint8_t current_count = 1;

    for (int i = 1; i < size; i++) {
        if (data[i] == current_value && current_count < 255) {
            current_count++;
        } else {
            compressed[comp_idx].value = current_value;
            compressed[comp_idx].count = current_count;
            comp_idx++;

            current_value = data[i];
            current_count = 1;
        }
    }

    // Add last run
    compressed[comp_idx].value = current_value;
    compressed[comp_idx].count = current_count;
    comp_idx++;

    *compressed_size = comp_idx;
}

void decompress_rle(const RLEPair* compressed, int compressed_size, uint8_t* decompressed, int* decompressed_size) {
    int decomp_idx = 0;

    for (int i = 0; i < compressed_size; i++) {
        for (int j = 0; j < compressed[i].count; j++) {
            decompressed[decomp_idx++] = compressed[i].value;
        }
    }

    *decompressed_size = decomp_idx;
}
```

## 📊 Test Cases

### Test Case 1: Bitwise Operators
```
Input: a=60, b=13
Expected Output:
a & b = 12 (AND)
a | b = 61 (OR)
a ^ b = 49 (XOR)
```

### Test Case 2: Bit Manipulation
```
Input: num=42
Expected Output:
Bit at position 3: SET
After setting bit 5: 74
After clearing bit 1: 72
Number of set bits: 3
```

### Test Case 3: Flag System
```
Expected Output:
Initial permissions: None
After setting read and write: RW
Read permission granted
After clearing write permission: R
```

### Test Case 4: Data Compression
```
Input: [1,1,1,2,2,3,3,3,3,4,5,5]
Expected Output:
Compressed: (1,3) (2,2) (3,4) (4,1) (5,2)
Compression ratio: 58.33%
```

## 🔍 Explanation

1. **Bitwise AND (&)**: Sets bit to 1 only if both bits are 1
2. **Bitwise OR (|)**: Sets bit to 1 if either bit is 1
3. **Bitwise XOR (^)**: Sets bit to 1 if bits are different
4. **Bitwise NOT (~)**: Flips all bits
5. **Left Shift (<<)**: Shifts bits left, multiplies by 2^n
6. **Right Shift (>>)**: Shifts bits right, divides by 2^n

## 🎯 Key Concepts Covered

- Bitwise operators and their applications
- Bit manipulation techniques
- Flag systems using bits
- Data compression algorithms
- Binary representation
- Bit-level operations

## 🚀 Extensions

1. Implement more compression algorithms (Huffman coding)
2. Create a bit vector class
3. Add CRC calculation for data integrity
4. Implement bit-level file operations