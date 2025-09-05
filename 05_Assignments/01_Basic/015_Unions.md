# 🎯 Assignment 1.15: Unions in C

## 📋 Problem Statement

Create a C program that demonstrates union usage for memory optimization and type punning. Implement a variant data type system and demonstrate memory layout differences between structures and unions.

## 🎯 Learning Objectives

- Understand union declaration and usage
- Learn memory sharing in unions
- Practice type punning techniques
- Compare unions vs structures
- Implement variant data types
- Understand union memory layout

## 📝 Requirements

1. Demonstrate basic union operations
2. Show memory sharing between union members
3. Implement type punning examples
4. Compare structure vs union memory usage
5. Create a variant data type system
6. Handle union member access safely
7. Demonstrate endianness and byte ordering

## 💡 Hints

- All union members share same memory location
- Union size equals largest member size
- Only one member can be active at a time
- Use unions for memory optimization
- Be careful with type punning and strict aliasing

## 🔧 Solution

```c
// Assignment 1.15: Unions in C
// Memory optimization and type punning

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Basic union demonstration
typedef union {
    int integer;
    float floating;
    char string[20];
} DataUnion;

// Memory layout comparison
typedef struct {
    int a;
    float b;
    char c[20];
} DataStruct;

typedef union {
    int a;
    float b;
    char c[20];
} DataUnionCompare;

// Variant data type system
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_DOUBLE
} DataType;

typedef union {
    int int_value;
    float float_value;
    char string_value[50];
    double double_value;
} VariantData;

typedef struct {
    DataType type;
    VariantData data;
} Variant;

// IP address representation
typedef union {
    uint32_t address;
    uint8_t bytes[4];
    struct {
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
        uint8_t byte4;
    } octets;
} IPv4Address;

// Type punning examples
typedef union {
    uint32_t integer;
    float floating;
} IntFloatUnion;

typedef union {
    uint64_t bits;
    double value;
} DoubleBits;

// Function prototypes
void demonstrate_basic_union();
void demonstrate_memory_layout();
void demonstrate_variant_system();
void demonstrate_type_punning();
void demonstrate_ip_address();
void print_binary(uint32_t num);

int main() {
    printf("=== Unions in C Demonstration ===\n\n");

    demonstrate_basic_union();
    demonstrate_memory_layout();
    demonstrate_variant_system();
    demonstrate_type_punning();
    demonstrate_ip_address();

    return 0;
}

void demonstrate_basic_union() {
    printf("1. Basic Union Operations\n");

    DataUnion data;

    // Store integer
    data.integer = 42;
    printf("Integer: %d\n", data.integer);

    // Store float (overwrites integer)
    data.floating = 3.14159f;
    printf("Float: %f\n", data.floating);
    printf("Integer after float: %d (garbage)\n", data.integer);

    // Store string (overwrites float)
    strcpy(data.string, "Hello");
    printf("String: %s\n", data.string);
    printf("Float after string: %f (garbage)\n", data.floating);

    printf("Union size: %lu bytes\n", sizeof(DataUnion));
    printf("Largest member size: %lu bytes\n", sizeof(data.string));

    printf("\n");
}

void demonstrate_memory_layout() {
    printf("2. Memory Layout Comparison\n");

    DataStruct struct_data = {42, 3.14159f, "Hello"};
    DataUnionCompare union_data;

    printf("Structure size: %lu bytes\n", sizeof(DataStruct));
    printf("Union size: %lu bytes\n", sizeof(DataUnionCompare));
    printf("Memory savings: %lu bytes\n",
           sizeof(DataStruct) - sizeof(DataUnionCompare));

    // Demonstrate memory sharing
    union_data.a = 100;
    printf("Union int: %d\n", union_data.a);

    union_data.b = 2.718f;
    printf("Union float: %f\n", union_data.b);
    printf("Union int after float: %d (overwritten)\n", union_data.a);

    printf("\n");
}

void demonstrate_variant_system() {
    printf("3. Variant Data Type System\n");

    Variant variants[4];

    // Integer variant
    variants[0].type = TYPE_INT;
    variants[0].data.int_value = 42;

    // Float variant
    variants[1].type = TYPE_FLOAT;
    variants[1].data.float_value = 3.14159f;

    // String variant
    variants[2].type = TYPE_STRING;
    strcpy(variants[2].data.string_value, "Hello World");

    // Double variant
    variants[3].type = TYPE_DOUBLE;
    variants[3].data.double_value = 2.718281828;

    // Display variants
    for (int i = 0; i < 4; i++) {
        printf("Variant %d: ", i);
        switch (variants[i].type) {
            case TYPE_INT:
                printf("Integer = %d\n", variants[i].data.int_value);
                break;
            case TYPE_FLOAT:
                printf("Float = %f\n", variants[i].data.float_value);
                break;
            case TYPE_STRING:
                printf("String = %s\n", variants[i].data.string_value);
                break;
            case TYPE_DOUBLE:
                printf("Double = %lf\n", variants[i].data.double_value);
                break;
        }
    }

    printf("\n");
}

void demonstrate_type_punning() {
    printf("4. Type Punning\n");

    IntFloatUnion int_float;
    DoubleBits double_bits;

    // Integer to float conversion
    int_float.integer = 0x40490FDB;  // IEEE 754 representation of 3.14159
    printf("Integer: %u\n", int_float.integer);
    printf("As float: %f\n", int_float.floating);

    // Double precision analysis
    double_bits.value = 3.141592653589793;
    printf("Double value: %lf\n", double_bits.value);
    printf("Binary representation: ");
    print_binary((uint32_t)(double_bits.bits >> 32));
    print_binary((uint32_t)double_bits.bits);

    printf("\n");
}

void demonstrate_ip_address() {
    printf("5. IP Address Representation\n");

    IPv4Address ip;

    // Set IP address as integer
    ip.address = 0xC0A80101;  // 192.168.1.1
    printf("IP as integer: %u\n", ip.address);

    // Access as bytes
    printf("IP as bytes: %d.%d.%d.%d\n",
           ip.bytes[3], ip.bytes[2], ip.bytes[1], ip.bytes[0]);

    // Access as octets
    printf("IP as octets: %d.%d.%d.%d\n",
           ip.octets.byte4, ip.octets.byte3,
           ip.octets.byte2, ip.octets.byte1);

    // Modify individual bytes
    ip.bytes[0] = 100;  // Change last octet
    printf("Modified IP: %d.%d.%d.%d\n",
           ip.bytes[3], ip.bytes[2], ip.bytes[1], ip.bytes[0]);

    printf("\n");
}

void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}
```

## 📊 Test Cases

### Test Case 1: Basic Union
```
Expected Output:
Integer: 42
Float: 3.141590
Integer after float: (garbage value)
String: Hello
Float after string: (garbage value)
Union size: 20 bytes
```

### Test Case 2: Memory Layout
```
Expected Output:
Structure size: 28 bytes
Union size: 20 bytes
Memory savings: 8 bytes
Union int: 100
Union float: 2.718000
Union int after float: (overwritten)
```

### Test Case 3: Variant System
```
Expected Output:
Variant 0: Integer = 42
Variant 1: Float = 3.141590
Variant 2: String = Hello World
Variant 3: Double = 2.718282
```

### Test Case 4: IP Address
```
Expected Output:
IP as integer: 3232235777
IP as bytes: 192.168.1.1
IP as octets: 192.168.1.1
Modified IP: 192.168.1.100
```

## 🔍 Explanation

1. **Union Declaration**: `union { int x; float y; } data;`
2. **Memory Sharing**: All members occupy same memory location
3. **Size Calculation**: Union size = size of largest member
4. **Type Punning**: Accessing same memory as different types
5. **Variant Types**: Unions for implementing dynamic typing
6. **Memory Layout**: Unions vs structures comparison

## 🎯 Key Concepts Covered

- Union declaration and usage
- Memory sharing and optimization
- Type punning techniques
- Variant data type systems
- Memory layout differences
- Safe union member access

## 🚀 Extensions

1. Implement a more complex variant type system
2. Add union serialization/deserialization
3. Create unions for different data representations
4. Implement union-based polymorphism