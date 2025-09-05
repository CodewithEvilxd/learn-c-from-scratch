# 🔧 Lesson 16: Bitwise Programming in C
## Mastering Bit-Level Operations

---

## 🎯 Learning Objectives

- Understand bitwise operators and their applications
- Master bit manipulation techniques
- Learn bit fields in structures
- Implement efficient algorithms using bits
- Apply bitwise operations in real-world scenarios

---

## 📖 Bitwise Programming Kya Hai?

**Bitwise programming** data ke andar individual bits ko manipulate karna hai. Ye essential hai:
- **Memory optimization**: Multiple values ko pack karna
- **Performance**: Fast mathematical operations
- **Hardware control**: Device register manipulation
- **Cryptography**: Encryption algorithms
- **Embedded systems**: Resource-constrained environments

### **Advanced Bitwise Concepts**
- **Bit manipulation algorithms**
- **Cryptographic applications**
- **Embedded systems programming**
- **Performance optimization techniques**
- **Cross-platform bit operations**

---

## 🔧 Bitwise Operators

### **1. Bitwise AND (&)**
```c
#include <stdio.h>

int main() {
    unsigned char a = 60;  // 0011 1100
    unsigned char b = 13;  // 0000 1101
    unsigned char result = a & b;  // 0000 1100 (12)

    printf("a & b = %d\n", result);

    // Practical use: Check if a number is even
    int num = 10;
    if (num & 1) {
        printf("%d is odd\n", num);
    } else {
        printf("%d is even\n", num);
    }

    return 0;
}
```

### **2. Bitwise OR (|)**
```c
#include <stdio.h>

int main() {
    unsigned char a = 60;  // 0011 1100
    unsigned char b = 13;  // 0000 1101
    unsigned char result = a | b;  // 0011 1101 (61)

    printf("a | b = %d\n", result);

    // Practical use: Set multiple flags
    unsigned char flags = 0;
    flags |= (1 << 0);  // Set bit 0
    flags |= (1 << 2);  // Set bit 2
    flags |= (1 << 4);  // Set bit 4
    printf("Flags: %d\n", flags);

    return 0;
}
```

### **3. Bitwise XOR (^)**
```c
#include <stdio.h>

int main() {
    unsigned char a = 60;  // 0011 1100
    unsigned char b = 13;  // 0000 1101
    unsigned char result = a ^ b;  // 0011 0001 (49)

    printf("a ^ b = %d\n", result);

    // Practical use: Swap two numbers without temp variable
    int x = 10, y = 20;
    printf("Before: x=%d, y=%d\n", x, y);

    x = x ^ y;
    y = x ^ y;
    x = x ^ y;

    printf("After: x=%d, y=%d\n", x, y);

    return 0;
}
```

### **4. Bitwise NOT (~)**
```c
#include <stdio.h>

int main() {
    unsigned char a = 60;  // 0011 1100
    unsigned char result = ~a;  // 1100 0011 (195 in decimal)

    printf("~a = %d\n", result);

    // For signed char, be careful with sign extension
    signed char b = 60;
    signed char not_b = ~b;
    printf("~b = %d\n", not_b);

    return 0;
}
```

### **5. Left Shift (<<)**
```c
#include <stdio.h>

int main() {
    int a = 12;  // 0000 1100
    int result = a << 2;  // 0011 0000 (48)

    printf("a << 2 = %d\n", result);

    // Practical use: Fast multiplication by powers of 2
    int num = 5;
    printf("5 * 8 = %d (using shift)\n", num << 3);
    printf("5 * 16 = %d (using shift)\n", num << 4);

    return 0;
}
```

### **6. Right Shift (>>)**
```c
#include <stdio.h>

int main() {
    int a = 48;  // 0011 0000
    int result = a >> 2;  // 0000 1100 (12)

    printf("a >> 2 = %d\n", result);

    // Practical use: Fast division by powers of 2
    int num = 32;
    printf("32 / 4 = %d (using shift)\n", num >> 2);
    printf("32 / 8 = %d (using shift)\n", num >> 3);

    // For negative numbers (implementation defined)
    int negative = -16;
    printf("-16 >> 2 = %d\n", negative >> 2);

    return 0;
}
```

---

## 🔄 Bit Manipulation Techniques

### **1. Setting Bits**
```c
#include <stdio.h>

// Set a specific bit
int set_bit(int num, int position) {
    return num | (1 << position);
}

// Set multiple bits
int set_bits(int num, int mask) {
    return num | mask;
}

int main() {
    int num = 8;  // 0000 1000
    printf("Original: %d\n", num);

    // Set bit 0
    num = set_bit(num, 0);
    printf("After setting bit 0: %d\n", num);  // 0000 1001 (9)

    // Set bits 2 and 3
    num = set_bits(num, (1 << 2) | (1 << 3));
    printf("After setting bits 2,3: %d\n", num);  // 0000 1101 (13)

    return 0;
}
```

### **2. Clearing Bits**
```c
#include <stdio.h>

// Clear a specific bit
int clear_bit(int num, int position) {
    return num & ~(1 << position);
}

// Clear multiple bits
int clear_bits(int num, int mask) {
    return num & ~mask;
}

int main() {
    int num = 15;  // 0000 1111
    printf("Original: %d\n", num);

    // Clear bit 1
    num = clear_bit(num, 1);
    printf("After clearing bit 1: %d\n", num);  // 0000 1101 (13)

    // Clear bits 0 and 2
    num = clear_bits(num, (1 << 0) | (1 << 2));
    printf("After clearing bits 0,2: %d\n", num);  // 0000 1000 (8)

    return 0;
}
```

### **3. Toggling Bits**
```c
#include <stdio.h>

// Toggle a specific bit
int toggle_bit(int num, int position) {
    return num ^ (1 << position);
}

// Toggle multiple bits
int toggle_bits(int num, int mask) {
    return num ^ mask;
}

int main() {
    int num = 10;  // 0000 1010
    printf("Original: %d\n", num);

    // Toggle bit 0
    num = toggle_bit(num, 0);
    printf("After toggling bit 0: %d\n", num);  // 0000 1011 (11)

    // Toggle bits 1 and 3
    num = toggle_bits(num, (1 << 1) | (1 << 3));
    printf("After toggling bits 1,3: %d\n", num);  // 0000 1000 (8)

    return 0;
}
```

### **4. Checking Bits**
```c
#include <stdio.h>

// Check if a bit is set
int is_bit_set(int num, int position) {
    return (num & (1 << position)) != 0;
}

// Check if a bit is clear
int is_bit_clear(int num, int position) {
    return (num & (1 << position)) == 0;
}

// Get the value of a specific bit
int get_bit(int num, int position) {
    return (num >> position) & 1;
}

int main() {
    int num = 10;  // 0000 1010

    printf("Bit 0: %d\n", get_bit(num, 0));  // 0
    printf("Bit 1: %d\n", get_bit(num, 1));  // 1
    printf("Bit 2: %d\n", get_bit(num, 2));  // 0
    printf("Bit 3: %d\n", get_bit(num, 3));  // 1

    printf("Is bit 1 set? %s\n", is_bit_set(num, 1) ? "Yes" : "No");
    printf("Is bit 0 clear? %s\n", is_bit_clear(num, 0) ? "Yes" : "No");

    return 0;
}
```

---

## 📊 Bit Fields in Structures

### **1. Basic Bit Fields**
```c
#include <stdio.h>

struct Status {
    unsigned int ready : 1;    // 1 bit
    unsigned int error : 1;    // 1 bit
    unsigned int busy : 1;     // 1 bit
    unsigned int data : 4;     // 4 bits (0-15)
    unsigned int reserved : 9; // 9 bits
};

int main() {
    struct Status status;

    status.ready = 1;
    status.error = 0;
    status.busy = 1;
    status.data = 10;

    printf("Ready: %d\n", status.ready);
    printf("Error: %d\n", status.error);
    printf("Busy: %d\n", status.busy);
    printf("Data: %d\n", status.data);

    // Size comparison
    printf("Size of struct: %zu bytes\n", sizeof(status));
    printf("Size without bit fields: %zu bytes\n", sizeof(unsigned int) * 5);

    return 0;
}
```

### **2. Advanced Bit Field Usage**
```c
#include <stdio.h>

struct RGBColor {
    unsigned char red : 8;
    unsigned char green : 8;
    unsigned char blue : 8;
};

struct Date {
    unsigned int day : 5;    // 1-31 (5 bits)
    unsigned int month : 4;  // 1-12 (4 bits)
    unsigned int year : 12;  // 0-4095 (12 bits)
};

union Color {
    struct RGBColor rgb;
    unsigned int packed;  // 24-bit color value
};

int main() {
    struct Date today = {15, 8, 2023};
    printf("Date: %d/%d/%d\n", today.day, today.month, today.year);

    union Color color;
    color.rgb.red = 255;
    color.rgb.green = 128;
    color.rgb.blue = 0;

    printf("RGB: (%d, %d, %d)\n", color.rgb.red, color.rgb.green, color.rgb.blue);
    printf("Packed: 0x%06X\n", color.packed);

    return 0;
}
```

---

## 🎯 Practical Applications

### **1. Permission Systems**
```c
#include <stdio.h>

#define READ_PERMISSION    (1 << 0)  // 0001
#define WRITE_PERMISSION  (1 << 1)  // 0010
#define EXECUTE_PERMISSION (1 << 2) // 0100
#define DELETE_PERMISSION (1 << 3)  // 1000

typedef unsigned char Permission;

void set_permission(Permission *perm, int permission) {
    *perm |= permission;
}

void clear_permission(Permission *perm, int permission) {
    *perm &= ~permission;
}

int has_permission(Permission perm, int permission) {
    return (perm & permission) != 0;
}

void print_permissions(Permission perm) {
    printf("Permissions: ");
    if (has_permission(perm, READ_PERMISSION)) printf("R");
    if (has_permission(perm, WRITE_PERMISSION)) printf("W");
    if (has_permission(perm, EXECUTE_PERMISSION)) printf("X");
    if (has_permission(perm, DELETE_PERMISSION)) printf("D");
    printf("\n");
}

int main() {
    Permission user_perm = 0;

    set_permission(&user_perm, READ_PERMISSION);
    set_permission(&user_perm, WRITE_PERMISSION);

    print_permissions(user_perm);  // RW

    if (has_permission(user_perm, READ_PERMISSION)) {
        printf("User can read\n");
    }

    clear_permission(&user_perm, WRITE_PERMISSION);
    print_permissions(user_perm);  // R

    return 0;
}
```

### **2. Flag Management**
```c
#include <stdio.h>

#define FLAG_A (1 << 0)
#define FLAG_B (1 << 1)
#define FLAG_C (1 << 2)
#define FLAG_D (1 << 3)

typedef unsigned int Flags;

void set_flag(Flags *flags, Flags flag) {
    *flags |= flag;
}

void clear_flag(Flags *flags, Flags flag) {
    *flags &= ~flag;
}

int is_flag_set(Flags flags, Flags flag) {
    return (flags & flag) != 0;
}

void print_flags(Flags flags) {
    printf("Flags set: ");
    if (is_flag_set(flags, FLAG_A)) printf("A ");
    if (is_flag_set(flags, FLAG_B)) printf("B ");
    if (is_flag_set(flags, FLAG_C)) printf("C ");
    if (is_flag_set(flags, FLAG_D)) printf("D ");
    printf("\n");
}

int main() {
    Flags status = 0;

    set_flag(&status, FLAG_A);
    set_flag(&status, FLAG_C);

    print_flags(status);  // A C

    // Check multiple flags at once
    if ((status & (FLAG_A | FLAG_C)) == (FLAG_A | FLAG_C)) {
        printf("Both A and C are set\n");
    }

    return 0;
}
```

### **3. Bitwise Algorithms**

#### **Count Set Bits**
```c
#include <stdio.h>

// Method 1: Brian Kernighan's algorithm
int count_set_bits(unsigned int num) {
    int count = 0;
    while (num) {
        num &= (num - 1);  // Clear the least significant set bit
        count++;
    }
    return count;
}

// Method 2: Lookup table (for 8-bit numbers)
int bit_count[256] = {0};  // Initialize with lookup values

void initialize_lookup() {
    for (int i = 0; i < 256; i++) {
        bit_count[i] = (i & 1) + bit_count[i >> 1];
    }
}

int count_set_bits_fast(unsigned int num) {
    return bit_count[num & 0xFF] +
           bit_count[(num >> 8) & 0xFF] +
           bit_count[(num >> 16) & 0xFF] +
           bit_count[(num >> 24) & 0xFF];
}

int main() {
    unsigned int num = 29;  // 11101 in binary
    printf("Number: %u\n", num);
    printf("Set bits: %d\n", count_set_bits(num));

    initialize_lookup();
    printf("Set bits (fast): %d\n", count_set_bits_fast(num));

    return 0;
}
```

#### **Find Next Power of 2**
```c
#include <stdio.h>

unsigned int next_power_of_2(unsigned int num) {
    if (num == 0) return 1;

    // Subtract 1 to handle numbers that are already powers of 2
    num--;

    // Set all bits after the highest set bit
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;

    // Add 1 to get the next power of 2
    return num + 1;
}

int main() {
    unsigned int numbers[] = {1, 3, 7, 15, 16, 17, 31, 32};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < size; i++) {
        printf("Next power of 2 for %u: %u\n",
               numbers[i], next_power_of_2(numbers[i]));
    }

    return 0;
}
```

#### **Bit Reversal**
```c
#include <stdio.h>

// Reverse bits of a 32-bit integer
unsigned int reverse_bits(unsigned int num) {
    unsigned int result = 0;
    int bits = sizeof(num) * 8;

    for (int i = 0; i < bits; i++) {
        result <<= 1;  // Make space for next bit
        result |= (num & 1);  // Copy least significant bit
        num >>= 1;  // Shift original number
    }

    return result;
}

// Fast bit reversal using lookup table
unsigned char reverse_byte[256];

void initialize_reverse_lookup() {
    for (int i = 0; i < 256; i++) {
        reverse_byte[i] = (unsigned char)reverse_bits(i) >> 24;
    }
}

unsigned int reverse_bits_fast(unsigned int num) {
    return (reverse_byte[num & 0xFF] << 24) |
           (reverse_byte[(num >> 8) & 0xFF] << 16) |
           (reverse_byte[(num >> 16) & 0xFF] << 8) |
           reverse_byte[(num >> 24) & 0xFF];
}

int main() {
    unsigned int num = 19;  // 0001 0011
    printf("Original: %u\n", num);
    printf("Reversed: %u\n", reverse_bits(num));

    initialize_reverse_lookup();
    printf("Reversed (fast): %u\n", reverse_bits_fast(num));

    return 0;
}
```

#### **Gray Code Conversion**
```c
#include <stdio.h>

// Convert binary to Gray code
unsigned int binary_to_gray(unsigned int num) {
    return num ^ (num >> 1);
}

// Convert Gray code to binary
unsigned int gray_to_binary(unsigned int gray) {
    unsigned int binary = gray;
    while (gray >>= 1) {
        binary ^= gray;
    }
    return binary;
}

// Fast Gray code conversion using lookup table
unsigned char gray_to_binary_table[256];

void initialize_gray_table() {
    for (int i = 0; i < 256; i++) {
        gray_to_binary_table[i] = gray_to_binary(i);
    }
}

unsigned int gray_to_binary_fast(unsigned int gray) {
    return (gray_to_binary_table[gray & 0xFF]) |
           (gray_to_binary_table[(gray >> 8) & 0xFF] << 8) |
           (gray_to_binary_table[(gray >> 16) & 0xFF] << 16) |
           (gray_to_binary_table[(gray >> 24) & 0xFF] << 24);
}

int main() {
    unsigned int num = 15;  // 1111
    unsigned int gray = binary_to_gray(num);
    unsigned int back = gray_to_binary(gray);

    printf("Original: %u\n", num);
    printf("Gray code: %u\n", gray);
    printf("Converted back: %u\n", back);

    initialize_gray_table();
    printf("Fast conversion: %u\n", gray_to_binary_fast(gray));

    return 0;
}
```

#### **Hamming Distance**
```c
#include <stdio.h>

// Calculate Hamming distance between two numbers
int hamming_distance(unsigned int a, unsigned int b) {
    unsigned int xor_result = a ^ b;
    int distance = 0;

    while (xor_result) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }

    return distance;
}

// Fast Hamming distance using Brian Kernighan's algorithm
int hamming_distance_fast(unsigned int a, unsigned int b) {
    unsigned int xor_result = a ^ b;
    int distance = 0;

    while (xor_result) {
        xor_result &= (xor_result - 1);
        distance++;
    }

    return distance;
}

int main() {
    unsigned int a = 29;  // 11101
    unsigned int b = 15;  // 01111

    printf("Number A: %u (binary: ", a);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (a >> i) & 1);
    }
    printf(")\n");

    printf("Number B: %u (binary: ", b);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (b >> i) & 1);
    }
    printf(")\n");

    printf("Hamming distance: %d\n", hamming_distance(a, b));
    printf("Hamming distance (fast): %d\n", hamming_distance_fast(a, b));

    return 0;
}
```

### **4. Cryptography Applications**

#### **Simple XOR Encryption**
```c
#include <stdio.h>
#include <string.h>

// Simple XOR encryption/decryption
void xor_encrypt_decrypt(char *data, const char *key, size_t data_len, size_t key_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % key_len];
    }
}

// One-time pad (perfect secrecy if key is truly random and never reused)
void one_time_pad(char *data, const char *key, size_t len) {
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key[i];
    }
}

// Simple stream cipher
typedef struct {
    unsigned int state;
} StreamCipher;

void init_cipher(StreamCipher *cipher, unsigned int seed) {
    cipher->state = seed;
}

// Linear congruential generator for keystream
unsigned char next_byte(StreamCipher *cipher) {
    cipher->state = (cipher->state * 1103515245 + 12345) & 0x7FFFFFFF;
    return (unsigned char)(cipher->state >> 16);
}

void stream_encrypt_decrypt(char *data, size_t len, unsigned int seed) {
    StreamCipher cipher;
    init_cipher(&cipher, seed);

    for (size_t i = 0; i < len; i++) {
        data[i] ^= next_byte(&cipher);
    }
}

int main() {
    char message[] = "Hello, World!";
    const char *key = "secret";

    printf("Original: %s\n", message);

    // XOR encryption
    xor_encrypt_decrypt(message, key, strlen(message), strlen(key));
    printf("XOR encrypted: %s\n", message);

    // Decrypt
    xor_encrypt_decrypt(message, key, strlen(message), strlen(key));
    printf("XOR decrypted: %s\n", message);

    // Stream cipher
    stream_encrypt_decrypt(message, strlen(message), 12345);
    printf("Stream encrypted: %s\n", message);

    // Decrypt with same seed
    stream_encrypt_decrypt(message, strlen(message), 12345);
    printf("Stream decrypted: %s\n", message);

    return 0;
}
```

#### **CRC (Cyclic Redundancy Check)**
```c
#include <stdio.h>
#include <stdint.h>

// CRC-32 implementation
#define CRC32_POLYNOMIAL 0xEDB88320

uint32_t crc32_table[256];

void init_crc32_table() {
    for (int i = 0; i < 256; i++) {
        uint32_t crc = i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
            } else {
                crc >>= 1;
            }
        }
        crc32_table[i] = crc;
    }
}

uint32_t crc32(const unsigned char *data, size_t len) {
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < len; i++) {
        uint8_t index = (crc ^ data[i]) & 0xFF;
        crc = (crc >> 8) ^ crc32_table[index];
    }

    return crc ^ 0xFFFFFFFF;
}

int main() {
    const char *data = "Hello, World!";
    size_t len = strlen(data);

    init_crc32_table();
    uint32_t checksum = crc32((const unsigned char*)data, len);

    printf("Data: %s\n", data);
    printf("CRC-32: 0x%08X\n", checksum);

    // Test with modified data
    char modified_data[] = "Hello, world!";
    uint32_t modified_checksum = crc32((const unsigned char*)modified_data, len);

    printf("Modified data: %s\n", modified_data);
    printf("Modified CRC-32: 0x%08X\n", modified_checksum);

    if (checksum != modified_checksum) {
        printf("Checksums differ - data was modified!\n");
    }

    return 0;
}
```

### **5. Embedded Systems Applications**

#### **GPIO Register Manipulation**
```c
#include <stdio.h>

// Simulated GPIO registers (in real embedded systems, these would be memory-mapped)
#define GPIO_BASE 0x40000000
#define GPIO_DATA_OFFSET 0x00
#define GPIO_DIR_OFFSET 0x04
#define GPIO_SET_OFFSET 0x08
#define GPIO_CLEAR_OFFSET 0x0C

// GPIO pin definitions
#define PIN_0 (1 << 0)
#define PIN_1 (1 << 1)
#define PIN_2 (1 << 2)
#define PIN_3 (1 << 3)

// Simulated register access (in real systems, use volatile pointers)
typedef struct {
    volatile uint32_t data;
    volatile uint32_t direction;
    volatile uint32_t set;
    volatile uint32_t clear;
} GPIO_Registers;

GPIO_Registers gpio;

// GPIO functions
void gpio_set_direction(uint32_t pins, int output) {
    if (output) {
        gpio.direction |= pins;
    } else {
        gpio.direction &= ~pins;
    }
}

void gpio_write(uint32_t pins, int value) {
    if (value) {
        gpio.set = pins;
    } else {
        gpio.clear = pins;
    }
}

int gpio_read(uint32_t pin) {
    return (gpio.data & pin) ? 1 : 0;
}

void gpio_toggle(uint32_t pins) {
    gpio.data ^= pins;
}

int main() {
    // Initialize GPIO
    gpio.data = 0;
    gpio.direction = 0;

    // Set pins 0 and 1 as output
    gpio_set_direction(PIN_0 | PIN_1, 1);

    // Set pin 0 high, pin 1 low
    gpio_write(PIN_0, 1);
    gpio_write(PIN_1, 0);

    printf("GPIO Data: 0x%08X\n", gpio.data);
    printf("GPIO Direction: 0x%08X\n", gpio.direction);

    // Toggle pins
    gpio_toggle(PIN_0 | PIN_1);
    printf("After toggle: 0x%08X\n", gpio.data);

    return 0;
}
```

#### **Interrupt Flag Management**
```c
#include <stdio.h>

// Interrupt status register simulation
#define ISR_BASE 0x40001000
#define ISR_STATUS_OFFSET 0x00
#define ISR_ENABLE_OFFSET 0x04
#define ISR_CLEAR_OFFSET 0x08

typedef struct {
    volatile uint32_t status;
    volatile uint32_t enable;
    volatile uint32_t clear;
} InterruptController;

// Interrupt flags
#define INT_TIMER (1 << 0)
#define INT_UART_RX (1 << 1)
#define INT_UART_TX (1 << 2)
#define INT_GPIO (1 << 3)
#define INT_ADC (1 << 4)

InterruptController ic;

// Interrupt functions
void enable_interrupt(uint32_t interrupt) {
    ic.enable |= interrupt;
}

void disable_interrupt(uint32_t interrupt) {
    ic.enable &= ~interrupt;
}

int is_interrupt_pending(uint32_t interrupt) {
    return (ic.status & interrupt) ? 1 : 0;
}

void clear_interrupt(uint32_t interrupt) {
    ic.clear = interrupt;
}

void interrupt_handler() {
    uint32_t pending = ic.status & ic.enable;

    if (pending & INT_TIMER) {
        printf("Timer interrupt!\n");
        clear_interrupt(INT_TIMER);
    }

    if (pending & INT_UART_RX) {
        printf("UART RX interrupt!\n");
        clear_interrupt(INT_UART_RX);
    }

    if (pending & INT_GPIO) {
        printf("GPIO interrupt!\n");
        clear_interrupt(INT_GPIO);
    }
}

int main() {
    // Initialize interrupts
    ic.status = 0;
    ic.enable = 0;

    // Enable timer and UART interrupts
    enable_interrupt(INT_TIMER | INT_UART_RX | INT_GPIO);

    // Simulate interrupts
    ic.status |= INT_TIMER;
    ic.status |= INT_GPIO;

    printf("Enabled interrupts: 0x%08X\n", ic.enable);
    printf("Pending interrupts: 0x%08X\n", ic.status);

    // Handle interrupts
    interrupt_handler();

    printf("After handling: 0x%08X\n", ic.status);

    return 0;
}
```

#### **Bit-Banging Serial Communication**
```c
#include <stdio.h>
#include <unistd.h>

// Simulated serial pins
#define TX_PIN (1 << 0)
#define RX_PIN (1 << 1)

typedef struct {
    volatile uint32_t port;
} GPIO_Port;

GPIO_Port gpio;

// Simple UART simulation
void uart_putc(char c) {
    // Start bit
    gpio.port &= ~TX_PIN;
    usleep(104);  // 9600 baud delay

    // Data bits (LSB first)
    for (int i = 0; i < 8; i++) {
        if (c & (1 << i)) {
            gpio.port |= TX_PIN;
        } else {
            gpio.port &= ~TX_PIN;
        }
        usleep(104);
    }

    // Stop bit
    gpio.port |= TX_PIN;
    usleep(104);
}

void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

char uart_getc() {
    char c = 0;

    // Wait for start bit
    while (gpio.port & RX_PIN);

    usleep(52);  // Half bit delay for sampling

    // Read data bits
    for (int i = 0; i < 8; i++) {
        usleep(104);
        if (gpio.port & RX_PIN) {
            c |= (1 << i);
        }
    }

    // Wait for stop bit
    usleep(104);

    return c;
}

int main() {
    gpio.port = 0xFF;  // All pins high initially

    printf("Sending 'Hello' via bit-banging UART...\n");

    uart_puts("Hello");

    printf("Sent successfully!\n");

    // Simulate receiving
    gpio.port &= ~RX_PIN;  // Start bit
    usleep(104);

    // Send 'A' (65 = 01000001)
    char test_char = 'A';
    for (int i = 0; i < 8; i++) {
        if (test_char & (1 << i)) {
            gpio.port |= RX_PIN;
        } else {
            gpio.port &= ~RX_PIN;
        }
        usleep(104);
    }

    gpio.port |= RX_PIN;  // Stop bit

    char received = uart_getc();
    printf("Received: %c\n", received);

    return 0;
}
```

### **6. Performance Optimization Techniques**

#### **Fast Division by Constants**
```c
#include <stdio.h>

// Fast division by 7 using multiplication and shift
int divide_by_7(int num) {
    // Precomputed constant: (2^32 / 7) + 1
    const unsigned int divisor = 0x24924925;  // Approximately 2^32 / 7

    unsigned int quotient = ((unsigned int)num * divisor) >> 32;
    return quotient;
}

// Fast modulo 7
int modulo_7(int num) {
    int quotient = divide_by_7(num);
    return num - quotient * 7;
}

// General fast division by constant
#define FAST_DIVIDE_BY_CONST(divisor, num) \
    (((num) * ((0x100000000ULL / (divisor)) + 1)) >> 32)

int main() {
    int test_values[] = {0, 7, 14, 21, 35, 49, 100};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    printf("Testing fast division by 7:\n");
    for (int i = 0; i < num_tests; i++) {
        int num = test_values[i];
        int fast_result = divide_by_7(num);
        int exact_result = num / 7;
        int fast_mod = modulo_7(num);
        int exact_mod = num % 7;

        printf("%3d: fast_div=%d, exact_div=%d, fast_mod=%d, exact_mod=%d\n",
               num, fast_result, exact_result, fast_mod, exact_mod);
    }

    return 0;
}
```

#### **Memory Alignment and Bit Operations**
```c
#include <stdio.h>
#include <stdlib.h>

// Check if address is aligned to boundary
int is_aligned(void *ptr, size_t alignment) {
    return ((uintptr_t)ptr & (alignment - 1)) == 0;
}

// Align pointer to boundary
void* align_pointer(void *ptr, size_t alignment) {
    uintptr_t addr = (uintptr_t)ptr;
    uintptr_t aligned = (addr + alignment - 1) & ~(alignment - 1);
    return (void*)aligned;
}

// Fast memory copy using word operations
void fast_memcpy(void *dest, const void *src, size_t n) {
    uint32_t *d32 = (uint32_t*)dest;
    const uint32_t *s32 = (const uint32_t*)src;

    // Copy 32-bit words
    size_t words = n / 4;
    for (size_t i = 0; i < words; i++) {
        *d32++ = *s32++;
    }

    // Copy remaining bytes
    uint8_t *d8 = (uint8_t*)d32;
    const uint8_t *s8 = (const uint8_t*)s32;
    size_t remainder = n % 4;
    for (size_t i = 0; i < remainder; i++) {
        *d8++ = *s8++;
    }
}

// Bit scan forward (find first set bit)
int bit_scan_forward(uint32_t value) {
    if (value == 0) return -1;

    int position = 0;
    while ((value & 1) == 0) {
        value >>= 1;
        position++;
    }
    return position;
}

// Bit scan reverse (find last set bit)
int bit_scan_reverse(uint32_t value) {
    if (value == 0) return -1;

    int position = 31;
    while ((value & 0x80000000) == 0) {
        value <<= 1;
        position--;
    }
    return position;
}

int main() {
    // Test alignment
    char buffer[100];
    printf("Buffer address: %p\n", buffer);
    printf("Is 4-byte aligned: %s\n", is_aligned(buffer, 4) ? "Yes" : "No");

    void *aligned = align_pointer(buffer, 8);
    printf("8-byte aligned address: %p\n", aligned);

    // Test bit scanning
    uint32_t test_val = 0x00010000;  // Bit 16 set
    printf("Value: 0x%08X\n", test_val);
    printf("First set bit: %d\n", bit_scan_forward(test_val));
    printf("Last set bit: %d\n", bit_scan_reverse(test_val));

    // Test fast memcpy
    char src[] = "Hello, Fast Memory Copy!";
    char dest[sizeof(src)] = {0};

    fast_memcpy(dest, src, sizeof(src) - 1);
    printf("Copied string: %s\n", dest);

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Use Unsigned Types for Bit Operations**
```c
// ✅ Good
unsigned int flags = 0;
flags |= (1U << 5);

// ❌ Bad - undefined behavior with signed types
int flags = 0;
flags |= (1 << 31);  // May cause issues
```

### **2. Be Careful with Shift Operations**
```c
// ✅ Good
unsigned int value = 100;
value = value << 2;  // OK

// ❌ Bad - undefined behavior
int negative = -10;
negative = negative << 1;  // Implementation defined

// ❌ Bad - undefined behavior
unsigned int big = 1;
big = big << 40;  // Undefined for 32-bit int
```

### **3. Use Parentheses in Complex Expressions**
```c
// ✅ Good
result = (a & b) | (c ^ d);

// ❌ Bad - operator precedence may not be what you expect
result = a & b | c ^ d;
```

### **4. Document Bit Field Usage**
```c
struct ControlRegister {
    unsigned int enable : 1;      // Enable/disable device
    unsigned int mode : 2;        // 00=idle, 01=read, 10=write, 11=error
    unsigned int speed : 3;       // Speed setting (0-7)
    unsigned int reserved : 10;   // Reserved for future use
};
```

---

## 🐛 Common Mistakes

### **1. Signed Integer Overflow**
```c
// Wrong - undefined behavior
int a = INT_MAX;
a = a + 1;  // Overflow

// For bitwise operations, use unsigned
unsigned int flags = 0;
flags |= (1U << 31);  // OK
```

### **2. Incorrect Shift Amounts**
```c
// Wrong - undefined behavior
int x = 10;
x = x << -1;  // Invalid shift amount
x = x << 40;  // Too large for 32-bit int

// Correct
unsigned int y = 10;
y = y << 3;  // OK
```

### **3. Bit Field Portability**
```c
// Bit fields may not be portable across compilers
struct PortabilityIssue {
    int a : 3;  // May be signed or unsigned depending on compiler
    int b : 3;
};

// Better to be explicit
struct Better {
    unsigned int a : 3;
    unsigned int b : 3;
};
```

### **4. Assuming Bit Order**
```c
// Wrong - bit order may vary
unsigned int value = 1;
if (value & 0x01) {  // Assumes LSB is bit 0
    // This may not be true on all systems
}

// Better - use shifts
#define BIT_0 (1 << 0)
if (value & BIT_0) {
    // More portable
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Bit Manipulation**
- Implement functions to count set bits in a number
- Create a function to check if a number is a power of 2
- Build a function to find the position of the rightmost set bit

### **Exercise 2: Bitwise Algorithms**
- Implement bit reversal for 32-bit integers
- Create a function to find the next power of 2
- Build a bit manipulation library

### **Exercise 3: Bit Fields**
- Create a structure for RGB color using bit fields
- Implement a date structure using bit fields
- Build a permission system using bit fields

### **Exercise 4: Practical Applications**
- Create a file permission system
- Implement a simple compression algorithm
- Build a bit-based data structure

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What does the expression `n & (n - 1)` do?
a) Sets all bits to 1
b) Clears the least significant set bit
c) Sets the most significant bit
d) Reverses all bits

### **Question 2:**
Which operator is used for bitwise XOR?
a) `&`
b) `|`
c) `^`
d) `~`

### **Question 3:**
What is the result of `1 << 3`?
a) 1
b) 3
c) 4
d) 8

### **Question 4:**
Which of these is NOT a valid bit field declaration?
a) `unsigned int x : 3;`
b) `int y : 8;`
c) `signed int z : 5;`
d) `float w : 4;`

### **Question 5:**
What does `n & 1` check for?
a) If n is positive
b) If n is even
c) If n is odd
d) If n is a power of 2

---

## 🔗 Additional Resources

### **Bitwise Operations**
- [Bitwise Operators](https://en.cppreference.com/w/c/language/operator_arithmetic)
- [Bit Manipulation](https://graphics.stanford.edu/~seander/bithacks.html)
- [Bit Fields](https://en.cppreference.com/w/c/language/bit_field)

### **Further Reading**
- [Bit Twiddling Hacks](https://www.chessprogramming.org/Bit-Twiddling)
- [Efficient Bit Manipulation](https://www.geeksforgeeks.org/bits-manipulation-important-tactics/)
- [Embedded Systems Bit Operations](https://www.embedded.com/bit-manipulation-and-bit-fields/)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ Bitwise operators and their applications
- ✅ Bit manipulation techniques
- ✅ Bit fields in structures
- ✅ Efficient algorithms using bits
- ✅ Real-world bit operation applications

**Next Lesson Preview:**
- Command-line arguments
- Environment variables
- Program exit codes
- System calls basics

---

**🚀 Ready to interact with the system?**

[⬅️ Previous: Enumerations & Typedef](15_Enumerations_Typedef.md) | [Next: Command Line Arguments ➡️](17_Command_Line_Arguments.md)