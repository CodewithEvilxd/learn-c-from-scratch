# 🔐 **Project 20: Basic Encryption Tool in C**
## 🎯 **Caesar Cipher and Vigenère Cipher Implementation**

---

## 📋 **Project Overview**

**English:** A basic encryption tool in C that implements Caesar cipher and Vigenère cipher algorithms with encryption and decryption capabilities, key management, and security analysis.

**Hinglish:** Ek basic encryption tool jo C mein hai, jisme Caesar cipher aur Vigenère cipher algorithms implement kiye gaye hain with encryption aur decryption capabilities, key management, aur security analysis ke saath.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Cryptographic algorithm implementation
- String manipulation for encryption
- Key management and validation
- File encryption/decryption
- Security best practices

✅ **Cryptography Concepts:**
- Symmetric encryption
- Caesar cipher mechanics
- Vigenère cipher implementation
- Key scheduling
- Basic cryptanalysis

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Encryption algorithms | Handles cryptographic operations |
| **String Library** | Text processing | Character manipulation for encryption |
| **File System** | Secure file operations | Encrypted file reading/writing |
| **Math Library** | Modular arithmetic | Cipher calculations |

---

## 📁 **Project Structure**

```
EncryptionTool/
├── include/
│   ├── caesar.h
│   ├── vigenere.h
│   ├── crypto.h
├── src/
│   ├── caesar.c
│   ├── vigenere.c
│   ├── crypto.c
│   └── main.c
├── data/
│   └── sample.txt
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Caesar Cipher**

```c
// caesar.h
#ifndef CAESAR_H
#define CAESAR_H

// Caesar cipher functions
void caesar_encrypt(char *text, int shift);
void caesar_decrypt(char *text, int shift);
int caesar_encrypt_file(const char *input_file, const char *output_file, int shift);
int caesar_decrypt_file(const char *input_file, const char *output_file, int shift);
void caesar_brute_force(const char *encrypted_text);

#endif
```

```c
// caesar.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "caesar.h"

// Encrypt using Caesar cipher
void caesar_encrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = ((text[i] - base + shift) % 26) + base;
        }
    }
}

// Decrypt using Caesar cipher
void caesar_decrypt(char *text, int shift) {
    caesar_encrypt(text, 26 - shift); // Decrypt is encrypt with negative shift
}

// Encrypt file using Caesar cipher
int caesar_encrypt_file(const char *input_file, const char *output_file, int shift) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return 0;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        caesar_encrypt(buffer, shift);
        fputs(buffer, output);
    }

    fclose(input);
    fclose(output);
    return 1;
}

// Decrypt file using Caesar cipher
int caesar_decrypt_file(const char *input_file, const char *output_file, int shift) {
    return caesar_encrypt_file(input_file, output_file, 26 - shift);
}

// Brute force attack on Caesar cipher
void caesar_brute_force(const char *encrypted_text) {
    printf("Brute force attack results:\n");
    printf("==========================\n");

    for (int shift = 1; shift < 26; shift++) {
        char *decrypted = (char*)malloc(strlen(encrypted_text) + 1);
        strcpy(decrypted, encrypted_text);
        caesar_decrypt(decrypted, shift);

        printf("Shift %2d: %s\n", shift, decrypted);
        free(decrypted);
    }
}
```

### **2. Vigenère Cipher**

```c
// vigenere.h
#ifndef VIGENERE_H
#define VIGENERE_H

// Vigenère cipher functions
void vigenere_encrypt(char *text, const char *key);
void vigenere_decrypt(char *text, const char *key);
int vigenere_encrypt_file(const char *input_file, const char *output_file, const char *key);
int vigenere_decrypt_file(const char *input_file, const char *output_file, const char *key);
void vigenere_frequency_analysis(const char *encrypted_text);

#endif
```

```c
// vigenere.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vigenere.h"

// Encrypt using Vigenère cipher
void vigenere_encrypt(char *text, const char *key) {
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_char = toupper(key[key_index % key_len]) - 'A';

            text[i] = ((text[i] - base + key_char) % 26) + base;
            key_index++;
        }
    }
}

// Decrypt using Vigenère cipher
void vigenere_decrypt(char *text, const char *key) {
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_char = toupper(key[key_index % key_len]) - 'A';

            text[i] = ((text[i] - base - key_char + 26) % 26) + base;
            key_index++;
        }
    }
}

// Encrypt file using Vigenère cipher
int vigenere_encrypt_file(const char *input_file, const char *output_file, const char *key) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return 0;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        vigenere_encrypt(buffer, key);
        fputs(buffer, output);
    }

    fclose(input);
    fclose(output);
    return 1;
}

// Decrypt file using Vigenère cipher
int vigenere_decrypt_file(const char *input_file, const char *output_file, const char *key) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return 0;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        vigenere_decrypt(buffer, key);
        fputs(buffer, output);
    }

    fclose(input);
    fclose(output);
    return 1;
}

// Basic frequency analysis for Vigenère
void vigenere_frequency_analysis(const char *encrypted_text) {
    int freq[26] = {0};
    int total_letters = 0;

    for (int i = 0; encrypted_text[i] != '\0'; i++) {
        if (isalpha(encrypted_text[i])) {
            freq[toupper(encrypted_text[i]) - 'A']++;
            total_letters++;
        }
    }

    printf("Letter Frequency Analysis:\n");
    printf("=========================\n");

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            printf("%c: %d (%.1f%%)\n", 'A' + i, freq[i],
                   (double)freq[i] / total_letters * 100);
        }
    }
}
```

### **3. Cryptography Utilities**

```c
// crypto.h
#ifndef CRYPTO_H
#define CRYPTO_H

// Cryptography utilities
int is_valid_key(const char *key);
void generate_random_key(char *key, int length);
double calculate_entropy(const char *text);
void print_cipher_info();

#endif
```

```c
// crypto.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "crypto.h"

// Validate encryption key
int is_valid_key(const char *key) {
    if (!key || strlen(key) == 0) return 0;

    for (int i = 0; key[i] != '\0'; i++) {
        if (!isalpha(key[i])) return 0;
    }

    return 1;
}

// Generate random key
void generate_random_key(char *key, int length) {
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabet_len = strlen(alphabet);

    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        key[i] = alphabet[rand() % alphabet_len];
    }
    key[length] = '\0';
}

// Calculate text entropy
double calculate_entropy(const char *text) {
    int freq[256] = {0};
    int total_chars = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        freq[(unsigned char)text[i]]++;
        total_chars++;
    }

    double entropy = 0.0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            double p = (double)freq[i] / total_chars;
            entropy -= p * log2(p);
        }
    }

    return entropy;
}

// Print cipher information
void print_cipher_info() {
    printf("Supported Ciphers:\n");
    printf("==================\n");
    printf("1. Caesar Cipher\n");
    printf("   - Shift-based substitution\n");
    printf("   - Key: 1-25 (shift amount)\n");
    printf("   - Security: Very weak\n\n");

    printf("2. Vigenère Cipher\n");
    printf("   - Poly-alphabetic substitution\n");
    printf("   - Key: Alphabetic string\n");
    printf("   - Security: Moderate\n\n");
}
```

### **4. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caesar.h"
#include "vigenere.h"
#include "crypto.h"

void display_menu() {
    printf("\n=== Encryption Tool ===\n");
    printf("1. Caesar Cipher Encrypt\n");
    printf("2. Caesar Cipher Decrypt\n");
    printf("3. Caesar Brute Force Attack\n");
    printf("4. Vigenère Cipher Encrypt\n");
    printf("5. Vigenère Cipher Decrypt\n");
    printf("6. Vigenère Frequency Analysis\n");
    printf("7. Generate Random Key\n");
    printf("8. Calculate Text Entropy\n");
    printf("9. Cipher Information\n");
    printf("10. Exit\n");
    printf("=======================\n");
    printf("Enter your choice: ");
}

int main() {
    char text[1000], key[100];
    int choice, shift;

    printf("Encryption Tool\n");
    printf("===============\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Caesar Encrypt
                printf("Enter text to encrypt: ");
                scanf(" %[^\n]", text);
                printf("Enter shift (1-25): ");
                scanf("%d", &shift);

                caesar_encrypt(text, shift);
                printf("Encrypted: %s\n", text);
                break;
            }

            case 2: {
                // Caesar Decrypt
                printf("Enter text to decrypt: ");
                scanf(" %[^\n]", text);
                printf("Enter shift (1-25): ");
                scanf("%d", &shift);

                caesar_decrypt(text, shift);
                printf("Decrypted: %s\n", text);
                break;
            }

            case 3: {
                // Caesar Brute Force
                printf("Enter encrypted text: ");
                scanf(" %[^\n]", text);
                caesar_brute_force(text);
                break;
            }

            case 4: {
                // Vigenère Encrypt
                printf("Enter text to encrypt: ");
                scanf(" %[^\n]", text);
                printf("Enter key: ");
                scanf(" %s", key);

                if (is_valid_key(key)) {
                    vigenere_encrypt(text, key);
                    printf("Encrypted: %s\n", text);
                } else {
                    printf("Invalid key! Use only alphabetic characters.\n");
                }
                break;
            }

            case 5: {
                // Vigenère Decrypt
                printf("Enter text to decrypt: ");
                scanf(" %[^\n]", text);
                printf("Enter key: ");
                scanf(" %s", key);

                if (is_valid_key(key)) {
                    vigenere_decrypt(text, key);
                    printf("Decrypted: %s\n", text);
                } else {
                    printf("Invalid key! Use only alphabetic characters.\n");
                }
                break;
            }

            case 6: {
                // Vigenère Frequency Analysis
                printf("Enter encrypted text: ");
                scanf(" %[^\n]", text);
                vigenere_frequency_analysis(text);
                break;
            }

            case 7: {
                // Generate Random Key
                printf("Enter key length: ");
                scanf("%d", &shift);
                generate_random_key(key, shift);
                printf("Generated key: %s\n", key);
                break;
            }

            case 8: {
                // Calculate Entropy
                printf("Enter text: ");
                scanf(" %[^\n]", text);
                double entropy = calculate_entropy(text);
                printf("Text entropy: %.2f bits per character\n", entropy);
                break;
            }

            case 9:
                print_cipher_info();
                break;

            case 10:
                printf("Thank you for using Encryption Tool!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
```

---

## 🎯 **Features Implemented**

### **Encryption Algorithms**
- ✅ Caesar cipher (encrypt/decrypt)
- ✅ Vigenère cipher (encrypt/decrypt)
- ✅ Brute force attack on Caesar
- ✅ Frequency analysis for Vigenère
- ✅ Key generation and validation

### **Security Analysis**
- ✅ Text entropy calculation
- ✅ Cipher information display
- ✅ Basic cryptanalysis tools
- ✅ Security strength assessment

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Basic Encryption Tool - Caesar and Vigenère Ciphers in C"
- **Hinglish:** "Basic Encryption Tool - Caesar and Vigenère Ciphers in C"

### **Slide 2: What We Built**
- ✅ Complete encryption tool with multiple ciphers
- ✅ Caesar cipher with brute force attack
- ✅ Vigenère cipher with frequency analysis
- ✅ Key management and validation
- ✅ Security analysis tools

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char algorithm_name[50];
    int key_size;
    char security_level[20];
} CipherInfo;

// Core functions
void caesar_encrypt(char *text, int shift);
void caesar_decrypt(char *text, int shift);
void vigenere_encrypt(char *text, const char *key);
void vigenere_decrypt(char *text, const char *key);
void caesar_brute_force(const char *encrypted_text);
double calculate_entropy(const char *text);
```

### **Slide 4: Encryption Algorithms**
```c
// Caesar cipher implementation
void caesar_encrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = ((text[i] - base + shift) % 26) + base;
        }
    }
}

// Vigenère cipher implementation
void vigenere_encrypt(char *text, const char *key) {
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_char = toupper(key[key_index % key_len]) - 'A';
            text[i] = ((text[i] - base + key_char) % 26) + base;
            key_index++;
        }
    }
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Cryptographic algorithm implementation
- ✅ String manipulation
- ✅ File I/O for encrypted data
- ✅ Security analysis
- ✅ Algorithm optimization

### **Cryptography Concepts:**
- ✅ Symmetric encryption
- ✅ Cipher implementation
- ✅ Key management
- ✅ Cryptanalysis techniques
- ✅ Security evaluation

---

## 📞 **Contact & Support**

**Project Developer:** Cryptography Student
**Email:** crypto@studentproject.com
**GitHub:** https://github.com/c-crypto/encryption-tool

---

**🔐 This encryption tool demonstrates basic cryptographic concepts and cipher implementation in C, perfect for understanding encryption algorithms and security fundamentals.**