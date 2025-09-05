# 🔐 Basic Encryption & Decryption System
## Implement Caesar cipher and Vigenère cipher algorithms

---

## 📋 Project Overview

This project implements basic encryption and decryption algorithms in C, including Caesar cipher and Vigenère cipher. It demonstrates fundamental cryptography concepts, file I/O for encrypted data, and command-line interface for encryption operations.

## 🎯 Learning Objectives

- Understand basic encryption algorithms
- Learn character manipulation techniques
- Practice file I/O with binary/text data
- Implement command-line interfaces
- Learn cryptography fundamentals

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries
- **Platform**: Cross-platform
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
encryption_system/
├── src/
│   ├── main.c           # Main program with CLI
│   ├── caesar.c         # Caesar cipher implementation
│   ├── vigenere.c       # Vigenère cipher implementation
│   ├── file_io.c        # File encryption/decryption
│   └── utils.c          # Utility functions
├── include/
│   ├── caesar.h
│   ├── vigenere.h
│   ├── file_io.h
│   └── utils.h
├── test_files/
│   ├── sample.txt
│   └── encrypted.dat
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Caesar Cipher**

```c
// caesar.h
#ifndef CAESAR_H
#define CAESAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function prototypes
void caesar_encrypt(char* text, int shift);
void caesar_decrypt(char* text, int shift);
char caesar_encrypt_char(char ch, int shift);
char caesar_decrypt_char(char ch, int shift);

#endif
```

```c
// caesar.c
#include "caesar.h"

char caesar_encrypt_char(char ch, int shift) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return (ch - base + shift) % ALPHABET_SIZE + base;
    }
    return ch;
}

char caesar_decrypt_char(char ch, int shift) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return (ch - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
    }
    return ch;
}

void caesar_encrypt(char* text, int shift) {
    for (size_t i = 0; text[i] != '\0'; i++) {
        text[i] = caesar_encrypt_char(text[i], shift);
    }
}

void caesar_decrypt(char* text, int shift) {
    for (size_t i = 0; text[i] != '\0'; i++) {
        text[i] = caesar_decrypt_char(text[i], shift);
    }
}
```

### **Step 2: Vigenère Cipher**

```c
// vigenere.h
#ifndef VIGENERE_H
#define VIGENERE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY_LENGTH 100

// Function prototypes
void vigenere_encrypt(char* text, const char* key);
void vigenere_decrypt(char* text, const char* key);
void generate_key(const char* text, const char* key, char* extended_key);
char vigenere_encrypt_char(char text_char, char key_char);
char vigenere_decrypt_char(char text_char, char key_char);

#endif
```

```c
// vigenere.c
#include "vigenere.h"

void generate_key(const char* text, const char* key, char* extended_key) {
    size_t text_len = strlen(text);
    size_t key_len = strlen(key);
    size_t key_index = 0;

    for (size_t i = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            extended_key[i] = toupper(key[key_index % key_len]);
            key_index++;
        } else {
            extended_key[i] = text[i];
        }
    }
    extended_key[text_len] = '\0';
}

char vigenere_encrypt_char(char text_char, char key_char) {
    if (isalpha(text_char)) {
        char base = isupper(text_char) ? 'A' : 'a';
        int text_val = text_char - base;
        int key_val = toupper(key_char) - 'A';
        return (text_val + key_val) % ALPHABET_SIZE + base;
    }
    return text_char;
}

char vigenere_decrypt_char(char text_char, char key_char) {
    if (isalpha(text_char)) {
        char base = isupper(text_char) ? 'A' : 'a';
        int text_val = text_char - base;
        int key_val = toupper(key_char) - 'A';
        return (text_val - key_val + ALPHABET_SIZE) % ALPHABET_SIZE + base;
    }
    return text_char;
}

void vigenere_encrypt(char* text, const char* key) {
    char extended_key[strlen(text) + 1];
    generate_key(text, key, extended_key);

    for (size_t i = 0; text[i] != '\0'; i++) {
        text[i] = vigenere_encrypt_char(text[i], extended_key[i]);
    }
}

void vigenere_decrypt(char* text, const char* key) {
    char extended_key[strlen(text) + 1];
    generate_key(text, key, extended_key);

    for (size_t i = 0; text[i] != '\0'; i++) {
        text[i] = vigenere_decrypt_char(text[i], extended_key[i]);
    }
}
```

### **Step 3: File I/O Operations**

```c
// file_io.h
#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int encrypt_file(const char* input_file, const char* output_file,
                void (*encrypt_func)(char*, int), int shift);
int decrypt_file(const char* input_file, const char* output_file,
                void (*decrypt_func)(char*, int), int shift);
int encrypt_file_vigenere(const char* input_file, const char* output_file,
                         void (*encrypt_func)(char*, const char*), const char* key);
int decrypt_file_vigenere(const char* input_file, const char* output_file,
                         void (*decrypt_func)(char*, const char*), const char* key);

#endif
```

```c
// file_io.c
#include "file_io.h"

int encrypt_file(const char* input_file, const char* output_file,
                void (*encrypt_func)(char*, int), int shift) {
    FILE* input = fopen(input_file, "r");
    if (!input) {
        perror("Error opening input file");
        return -1;
    }

    FILE* output = fopen(output_file, "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        buffer[bytes_read] = '\0';
        encrypt_func(buffer, shift);
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}

int decrypt_file(const char* input_file, const char* output_file,
                void (*decrypt_func)(char*, int), int shift) {
    FILE* input = fopen(input_file, "r");
    if (!input) {
        perror("Error opening input file");
        return -1;
    }

    FILE* output = fopen(output_file, "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        buffer[bytes_read] = '\0';
        decrypt_func(buffer, shift);
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}

int encrypt_file_vigenere(const char* input_file, const char* output_file,
                         void (*encrypt_func)(char*, const char*), const char* key) {
    FILE* input = fopen(input_file, "r");
    if (!input) {
        perror("Error opening input file");
        return -1;
    }

    FILE* output = fopen(output_file, "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        buffer[bytes_read] = '\0';
        encrypt_func(buffer, key);
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}

int decrypt_file_vigenere(const char* input_file, const char* output_file,
                         void (*decrypt_func)(char*, const char*), const char* key) {
    FILE* input = fopen(input_file, "r");
    if (!input) {
        perror("Error opening input file");
        return -1;
    }

    FILE* output = fopen(output_file, "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        buffer[bytes_read] = '\0';
        decrypt_func(buffer, key);
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}
```

### **Step 4: Main Program**

```c
// main.c
#include "caesar.h"
#include "vigenere.h"
#include "file_io.h"
#include <string.h>

void display_menu() {
    printf("\n=== Encryption/Decryption System ===\n");
    printf("1. Caesar Cipher Encrypt Text\n");
    printf("2. Caesar Cipher Decrypt Text\n");
    printf("3. Vigenère Cipher Encrypt Text\n");
    printf("4. Vigenère Cipher Decrypt Text\n");
    printf("5. Encrypt File (Caesar)\n");
    printf("6. Decrypt File (Caesar)\n");
    printf("7. Encrypt File (Vigenère)\n");
    printf("8. Decrypt File (Vigenère)\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char text[1024];
    char key[MAX_KEY_LENGTH];
    int shift;
    char input_file[256];
    char output_file[256];

    printf("Encryption & Decryption System\n");
    printf("===============================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: // Caesar Encrypt Text
                printf("Enter text to encrypt: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';

                printf("Enter shift value (1-25): ");
                scanf("%d", &shift);

                caesar_encrypt(text, shift);
                printf("Encrypted text: %s\n", text);
                break;

            case 2: // Caesar Decrypt Text
                printf("Enter text to decrypt: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';

                printf("Enter shift value (1-25): ");
                scanf("%d", &shift);

                caesar_decrypt(text, shift);
                printf("Decrypted text: %s\n", text);
                break;

            case 3: // Vigenère Encrypt Text
                printf("Enter text to encrypt: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';

                printf("Enter key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';

                vigenere_encrypt(text, key);
                printf("Encrypted text: %s\n", text);
                break;

            case 4: // Vigenère Decrypt Text
                printf("Enter text to decrypt: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';

                printf("Enter key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';

                vigenere_decrypt(text, key);
                printf("Decrypted text: %s\n", text);
                break;

            case 5: // Encrypt File (Caesar)
                printf("Enter input file: ");
                scanf("%s", input_file);
                printf("Enter output file: ");
                scanf("%s", output_file);
                printf("Enter shift value: ");
                scanf("%d", &shift);

                if (encrypt_file(input_file, output_file, caesar_encrypt, shift) == 0) {
                    printf("File encrypted successfully!\n");
                }
                break;

            case 6: // Decrypt File (Caesar)
                printf("Enter input file: ");
                scanf("%s", input_file);
                printf("Enter output file: ");
                scanf("%s", output_file);
                printf("Enter shift value: ");
                scanf("%d", &shift);

                if (decrypt_file(input_file, output_file, caesar_decrypt, shift) == 0) {
                    printf("File decrypted successfully!\n");
                }
                break;

            case 7: // Encrypt File (Vigenère)
                printf("Enter input file: ");
                scanf("%s", input_file);
                printf("Enter output file: ");
                scanf("%s", output_file);
                printf("Enter key: ");
                scanf("%s", key);

                if (encrypt_file_vigenere(input_file, output_file, vigenere_encrypt, key) == 0) {
                    printf("File encrypted successfully!\n");
                }
                break;

            case 8: // Decrypt File (Vigenère)
                printf("Enter input file: ");
                scanf("%s", input_file);
                printf("Enter output file: ");
                scanf("%s", output_file);
                printf("Enter key: ");
                scanf("%s", key);

                if (decrypt_file_vigenere(input_file, output_file, vigenere_decrypt, key) == 0) {
                    printf("File decrypted successfully!\n");
                }
                break;

            case 0:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Cryptography**
- [x] Caesar cipher implementation
- [x] Vigenère cipher implementation
- [x] Character encryption/decryption
- [x] File encryption/decryption
- [x] Command-line interface

### **✅ Advanced Features**
- [x] Case preservation
- [x] Non-alphabetic character handling
- [x] File I/O operations
- [x] Error handling
- [x] User-friendly interface

### **🚀 Extensions**
- [ ] AES encryption
- [ ] RSA encryption
- [ ] Hash functions
- [ ] Digital signatures
- [ ] Key management
- [ ] Secure file transfer

## 🧪 Testing and Usage

### **Basic Text Encryption**
```c
// Caesar cipher example
char text[] = "Hello, World!";
caesar_encrypt(text, 3);
printf("Encrypted: %s\n", text);  // "Khoor, Zruog!"

caesar_decrypt(text, 3);
printf("Decrypted: %s\n", text);  // "Hello, World!"
```

### **Vigenère Cipher Example**
```c
char text[] = "Attack at dawn";
char key[] = "LEMON";
vigenere_encrypt(text, key);
printf("Encrypted: %s\n", text);  // "Lxfopv ef rnhr"

vigenere_decrypt(text, key);
printf("Decrypted: %s\n", text);  // "Attack at dawn"
```

### **File Encryption**
```bash
# Encrypt a file
./encryption_system
# Choose option 5
# Input: sample.txt
# Output: encrypted.txt
# Shift: 5

# Decrypt the file
# Choose option 6
# Input: encrypted.txt
# Output: decrypted.txt
# Shift: 5
```

## 📊 Technical Learning Outcomes

### **Cryptography Concepts**
- Symmetric encryption algorithms
- Key management
- Character manipulation
- File I/O security
- Basic cryptanalysis

### **C Programming Skills**
- String manipulation
- File operations
- Command-line interfaces
- Error handling
- Modular programming

## 🚀 Advanced Extensions

### **Brute Force Attack**
```c
void brute_force_caesar(const char* ciphertext) {
    printf("Brute force Caesar cipher:\n");
    for (int shift = 1; shift < ALPHABET_SIZE; shift++) {
        char test_text[1024];
        strcpy(test_text, ciphertext);
        caesar_decrypt(test_text, shift);
        printf("Shift %d: %s\n", shift, test_text);
    }
}
```

### **Frequency Analysis**
```c
void frequency_analysis(const char* text) {
    int frequency[ALPHABET_SIZE] = {0};
    int total_letters = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        char ch = toupper(text[i]);
        if (isalpha(ch)) {
            frequency[ch - 'A']++;
            total_letters++;
        }
    }

    printf("Letter frequencies:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("%c: %.2f%%\n", 'A' + i,
                   (float)frequency[i] / total_letters * 100);
        }
    }
}
```

## 📖 References

- **"The Code Book"** by Simon Singh
- **"Applied Cryptography"** by Bruce Schneier
- **"Cryptography and Network Security"** by William Stallings
- **Historical Ciphers** - NIST publications

## 🎯 Real-World Applications

- **File Encryption**: Protecting sensitive documents
- **Secure Communication**: Basic message encryption
- **Password Storage**: Hash-based security
- **Digital Rights Management**: Content protection
- **Network Security**: VPN and secure protocols

---

**🔐 This project demonstrates fundamental cryptography concepts and secure data handling in C!**