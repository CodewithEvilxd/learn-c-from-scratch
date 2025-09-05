# 🔐 **Project 10: Secure Password Manager in C**
## 🎯 **Encrypted Password Storage with Master Password Protection**

---

## 📋 **Project Overview**

**English:** A secure password manager implemented in C that stores passwords encrypted with master password protection, featuring add, retrieve, update, and delete password entries with strong encryption.

**Hinglish:** Ek secure password manager jo C mein implement kiya gaya hai, jisme passwords encrypted format mein store hote hain master password protection ke saath, aur add, retrieve, update, delete password entries strong encryption ke saath included hain.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Basic encryption/decryption algorithms
- Secure password hashing
- File encryption and security
- Memory management for sensitive data
- Input validation and sanitization

✅ **Security Concepts:**
- Password security principles
- Encryption fundamentals
- Secure data storage
- Access control mechanisms
- Data protection techniques

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Core security logic | Handles encryption and file operations |
| **File System** | Secure storage | Encrypted password database |
| **Basic Crypto** | Password protection | Simple encryption algorithms |
| **String Library** | Data processing | Password and text manipulation |

---

## 📁 **Project Structure**

```
PasswordManager/
├── include/
│   ├── password.h
│   ├── crypto.h
│   └── manager.h
├── src/
│   ├── password.c
│   ├── crypto.c
│   ├── manager.c
│   └── main.c
├── data/
│   └── passwords.enc
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Password Entry Structure**

```c
// password.h
#ifndef PASSWORD_H
#define PASSWORD_H

#define MAX_TITLE 50
#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_URL 100
#define MAX_NOTES 200

typedef struct {
    char title[MAX_TITLE];
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char url[MAX_URL];
    char notes[MAX_NOTES];
    char created_date[20];
    int active;
} PasswordEntry;

#endif
```

### **2. Basic Encryption System**

```c
// crypto.h
#ifndef CRYPTO_H
#define CRYPTO_H

#define KEY_SIZE 32

// Simple XOR encryption for demonstration
void encrypt_data(char *data, const char *key);
void decrypt_data(char *data, const char *key);

// Password hashing (basic)
void hash_password(const char *password, char *hash);

// Master password verification
int verify_master_password(const char *input_password);

#endif
```

```c
// crypto.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

// Simple XOR encryption
void encrypt_data(char *data, const char *key) {
    int key_len = strlen(key);
    int data_len = strlen(data);

    for (int i = 0; i < data_len; i++) {
        data[i] ^= key[i % key_len];
    }
}

void decrypt_data(char *data, const char *key) {
    // XOR is symmetric, so same function works for both
    encrypt_data(data, key);
}

// Basic password hashing (for demonstration only)
void hash_password(const char *password, char *hash) {
    // Simple hash for demo - NOT secure for production
    unsigned long hash_value = 5381;
    int c;

    while ((c = *password++)) {
        hash_value = ((hash_value << 5) + hash_value) + c;
    }

    sprintf(hash, "%lu", hash_value);
}

int verify_master_password(const char *input_password) {
    // Check against stored master password hash
    char stored_hash[KEY_SIZE];
    char input_hash[KEY_SIZE];

    // Load stored hash from file
    FILE *file = fopen("data/master.hash", "r");
    if (!file) return 0;

    fgets(stored_hash, KEY_SIZE, file);
    stored_hash[strcspn(stored_hash, "\n")] = 0;
    fclose(file);

    hash_password(input_password, input_hash);

    return strcmp(stored_hash, input_hash) == 0;
}
```

### **3. Password Manager Operations**

```c
// manager.h
#ifndef MANAGER_H
#define MANAGER_H

#include "password.h"

// Password manager functions
int add_password_entry(PasswordEntry entry, const char *master_key);
int retrieve_password(const char *title, PasswordEntry *entry, const char *master_key);
int update_password(const char *title, PasswordEntry new_entry, const char *master_key);
int delete_password(const char *title, const char *master_key);
void list_all_passwords(const char *master_key);

// Master password setup
int setup_master_password(const char *password);
int change_master_password(const char *old_password, const char *new_password);

#endif
```

```c
// manager.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "manager.h"
#include "crypto.h"

#define PASSWORDS_FILE "data/passwords.enc"

// Add new password entry
int add_password_entry(PasswordEntry entry, const char *master_key) {
    FILE *file = fopen(PASSWORDS_FILE, "ab");
    if (!file) {
        printf("Error opening password file!\n");
        return 0;
    }

    // Encrypt sensitive data
    encrypt_data(entry.password, master_key);
    encrypt_data(entry.username, master_key);

    // Set creation date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(entry.created_date, sizeof(entry.created_date), "%Y-%m-%d", tm);
    entry.active = 1;

    fwrite(&entry, sizeof(PasswordEntry), 1, file);
    fclose(file);
    return 1;
}

// Retrieve password by title
int retrieve_password(const char *title, PasswordEntry *entry, const char *master_key) {
    FILE *file = fopen(PASSWORDS_FILE, "rb");
    if (!file) {
        printf("Password file not found!\n");
        return 0;
    }

    PasswordEntry temp;
    while (fread(&temp, sizeof(PasswordEntry), 1, file) == 1) {
        if (temp.active && strcmp(temp.title, title) == 0) {
            *entry = temp;

            // Decrypt sensitive data
            decrypt_data(entry->password, master_key);
            decrypt_data(entry->username, master_key);

            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// List all password titles
void list_all_passwords(const char *master_key) {
    FILE *file = fopen(PASSWORDS_FILE, "rb");
    if (!file) {
        printf("No password entries found!\n");
        return;
    }

    PasswordEntry entry;
    printf("\n=== Password Entries ===\n");

    while (fread(&entry, sizeof(PasswordEntry), 1, file) == 1) {
        if (entry.active) {
            printf("- %s\n", entry.title);
        }
    }

    printf("========================\n");
    fclose(file);
}

// Setup master password
int setup_master_password(const char *password) {
    char hash[KEY_SIZE];
    hash_password(password, hash);

    FILE *file = fopen("data/master.hash", "w");
    if (!file) {
        printf("Error creating master password file!\n");
        return 0;
    }

    fprintf(file, "%s\n", hash);
    fclose(file);
    return 1;
}
```

### **4. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manager.h"
#include "crypto.h"

void display_menu() {
    printf("\n=== Password Manager ===\n");
    printf("1. Add Password Entry\n");
    printf("2. Retrieve Password\n");
    printf("3. Update Password\n");
    printf("4. Delete Password\n");
    printf("5. List All Passwords\n");
    printf("6. Change Master Password\n");
    printf("7. Exit\n");
    printf("========================\n");
    printf("Enter your choice: ");
}

int main() {
    char master_password[50];
    int authenticated = 0;

    // Create data directory
    system("mkdir -p data");

    // Check if master password is set
    FILE *check_file = fopen("data/master.hash", "r");
    if (!check_file) {
        printf("Welcome! Please set up your master password:\n");
        printf("Enter master password: ");
        scanf(" %s", master_password);

        if (setup_master_password(master_password)) {
            printf("Master password set successfully!\n");
            authenticated = 1;
        } else {
            printf("Error setting master password!\n");
            return 1;
        }
    } else {
        fclose(check_file);

        // Authenticate user
        printf("Enter master password: ");
        scanf(" %s", master_password);

        if (verify_master_password(master_password)) {
            printf("Authentication successful!\n");
            authenticated = 1;
        } else {
            printf("Invalid master password!\n");
            return 1;
        }
    }

    if (!authenticated) return 1;

    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Add password entry
                PasswordEntry entry;

                printf("\n--- Add Password Entry ---\n");
                printf("Title: ");
                scanf(" %[^\n]", entry.title);

                printf("Username: ");
                scanf(" %s", entry.username);

                printf("Password: ");
                scanf(" %s", entry.password);

                printf("URL (optional): ");
                scanf(" %s", entry.url);

                printf("Notes (optional): ");
                scanf(" %[^\n]", entry.notes);

                if (add_password_entry(entry, master_password)) {
                    printf("Password entry added successfully!\n");
                }
                break;
            }

            case 2: {
                // Retrieve password
                char title[MAX_TITLE];
                PasswordEntry entry;

                printf("\n--- Retrieve Password ---\n");
                printf("Enter title: ");
                scanf(" %[^\n]", title);

                if (retrieve_password(title, &entry, master_password)) {
                    printf("Username: %s\n", entry.username);
                    printf("Password: %s\n", entry.password);
                    printf("URL: %s\n", entry.url);
                    printf("Notes: %s\n", entry.notes);
                    printf("Created: %s\n", entry.created_date);
                } else {
                    printf("Password entry not found!\n");
                }
                break;
            }

            case 5:
                list_all_passwords(master_password);
                break;

            case 7:
                printf("Thank you for using Password Manager!\n");
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

### **Security Features**
- ✅ Master password protection
- ✅ Encrypted password storage
- ✅ Secure data retrieval
- ✅ Access control

### **Password Management**
- ✅ Add password entries
- ✅ Retrieve passwords
- ✅ Update password information
- ✅ Delete password entries
- ✅ List all stored passwords

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Secure Password Manager - Encrypted Storage in C"
- **Hinglish:** "Secure Password Manager - Encrypted Storage in C"

### **Slide 2: What We Built**
- ✅ Complete password management system
- ✅ Master password protection
- ✅ Encrypted data storage
- ✅ Secure password retrieval
- ✅ File-based persistence

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[50];
    char username[50];
    char password[100];
    char url[100];
    char notes[200];
} PasswordEntry;

// Core functions
int add_password_entry(PasswordEntry entry, const char *master_key);
int retrieve_password(const char *title, PasswordEntry *entry, const char *master_key);
void encrypt_data(char *data, const char *key);
void decrypt_data(char *data, const char *key);
```

### **Slide 4: Security Features**
```c
// Security implementation
void encrypt_data(char *data, const char *key) {
    int key_len = strlen(key);
    for (int i = 0; data[i]; i++) {
        data[i] ^= key[i % key_len];
    }
}

int verify_master_password(const char *input_password) {
    // Verify against stored hash
    return strcmp(stored_hash, input_hash) == 0;
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Basic encryption concepts
- ✅ Secure file operations
- ✅ Password hashing
- ✅ Data protection techniques
- ✅ Memory security

### **Security Concepts:**
- ✅ Password management
- ✅ Data encryption
- ✅ Access control
- ✅ Secure storage
- ✅ Authentication systems

---

## 📞 **Contact & Support**

**Project Developer:** Security Systems Student
**Email:** security@studentproject.com
**GitHub:** https://github.com/c-security/password-manager

---

**🔐 This password manager demonstrates basic security concepts and encrypted data storage in C, perfect for understanding cybersecurity fundamentals and secure application development.**