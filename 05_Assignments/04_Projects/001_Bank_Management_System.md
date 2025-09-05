# 🎯 Project 1.1: Bank Management System

## 📋 Project Statement

Create a comprehensive bank management system in C that handles customer accounts, transactions, and banking operations. The system should include account creation, deposits, withdrawals, transfers, and transaction history.

## 🎯 Learning Objectives

- Integrate multiple C programming concepts
- Implement file-based data persistence
- Create modular, maintainable code
- Handle complex data structures
- Implement security features
- Create user-friendly interfaces

## 📝 Requirements

1. Customer account management
2. Transaction processing (deposit/withdrawal/transfer)
3. Transaction history and statements
4. File-based data storage
5. Input validation and error handling
6. Security features (PIN/password)
7. Admin and customer interfaces
8. Report generation

## 💡 Implementation Hints

- Use structures for accounts and transactions
- Implement file I/O for data persistence
- Create separate modules for different functionalities
- Use enums for account types and transaction types
- Implement proper error handling
- Add data validation

## 🏗️ Project Structure

```
bank_system/
├── main.c              # Main program entry
├── account.h           # Account structure definitions
├── account.c           # Account management functions
├── transaction.h       # Transaction structure definitions
├── transaction.c       # Transaction processing functions
├── file_io.h          # File I/O operations
├── file_io.c          # File operations implementation
├── security.h         # Security functions
├── security.c         # Authentication and security
├── ui.h               # User interface
├── ui.c               # Menu and display functions
└── data/              # Data storage directory
    ├── accounts.dat
    └── transactions.dat
```

## 🔧 Core Implementation

```c
// main.c - Main program entry point
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "transaction.h"
#include "file_io.h"
#include "ui.h"
#include "security.h"

int main() {
    printf("=== Bank Management System ===\n");

    // Initialize system
    if (!initialize_system()) {
        printf("Failed to initialize system!\n");
        return 1;
    }

    // Main menu loop
    int choice;
    do {
        display_main_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                admin_menu();
                break;
            case 2:
                customer_menu();
                break;
            case 3:
                printf("Thank you for using Bank Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    // Cleanup
    cleanup_system();

    return 0;
}
```

```c
// account.h - Account structure definitions
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdbool.h>

#define MAX_NAME 50
#define MAX_PIN 5
#define MIN_BALANCE 500

typedef enum {
    SAVINGS,
    CURRENT,
    FIXED_DEPOSIT
} AccountType;

typedef struct {
    int account_number;
    char name[MAX_NAME];
    char pin[MAX_PIN];
    AccountType type;
    double balance;
    bool is_active;
    char created_date[11];  // YYYY-MM-DD
} Account;

// Function prototypes
Account* create_account(const char* name, AccountType type, const char* pin);
bool validate_account(Account* account);
void display_account(const Account* account);
bool authenticate_account(int account_number, const char* pin);

#endif
```

```c
// transaction.h - Transaction structure definitions
#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef enum {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
} TransactionType;

typedef struct {
    int transaction_id;
    int account_number;
    TransactionType type;
    double amount;
    char date[11];          // YYYY-MM-DD
    char time[9];           // HH:MM:SS
    int target_account;     // For transfers
    char description[100];
} Transaction;

// Function prototypes
Transaction* create_transaction(int account_number, TransactionType type,
                               double amount, const char* description);
bool process_deposit(int account_number, double amount);
bool process_withdrawal(int account_number, double amount);
bool process_transfer(int from_account, int to_account, double amount);
void display_transaction(const Transaction* transaction);

#endif
```

## 📊 Key Features

### 1. Account Management
- Create new accounts with validation
- Account type selection (Savings/Current/FD)
- PIN-based authentication
- Account status management

### 2. Transaction Processing
- Deposit funds with validation
- Withdrawal with balance checks
- Inter-account transfers
- Transaction logging and history

### 3. Security Features
- PIN-based authentication
- Input validation
- Secure data storage
- Access control

### 4. Reporting
- Account statements
- Transaction history
- Balance reports
- Admin reports

## 🧪 Test Cases

### Test Case 1: Account Creation
```
Input:
Name: John Doe
Type: Savings
PIN: 1234
Initial Deposit: 1000

Expected Output: Account created successfully with number 1001
```

### Test Case 2: Deposit Transaction
```
Input:
Account: 1001
Amount: 500
PIN: 1234

Expected Output: Deposit successful. New balance: 1500
```

### Test Case 3: Transfer Transaction
```
Input:
From Account: 1001
To Account: 1002
Amount: 200
PIN: 1234

Expected Output: Transfer successful
```

### Test Case 4: Insufficient Balance
```
Input:
Account: 1001
Withdrawal: 2000
PIN: 1234

Expected Output: Insufficient balance error
```

## 🎯 Advanced Features

1. **Multi-threading**: Handle concurrent transactions
2. **Database Integration**: Use SQLite for data storage
3. **Network Support**: Client-server architecture
4. **Encryption**: Secure PIN storage
5. **Audit Trail**: Complete transaction logging
6. **Interest Calculation**: Automatic interest computation

## 📈 Project Milestones

### Phase 1: Core Functionality
- [ ] Account creation and management
- [ ] Basic transaction processing
- [ ] File-based storage
- [ ] Simple authentication

### Phase 2: Advanced Features
- [ ] Transaction history
- [ ] Report generation
- [ ] Enhanced security
- [ ] Input validation

### Phase 3: Optimization
- [ ] Performance optimization
- [ ] Error handling improvement
- [ ] Code refactoring
- [ ] Documentation

## 🔧 Build Instructions

```bash
# Compile the project
gcc -o bank_system main.c account.c transaction.c file_io.c ui.c security.c

# Run the program
./bank_system
```

## 🎯 Learning Outcomes

- **Data Structures**: Complex structure usage
- **File I/O**: Binary file operations
- **Modular Programming**: Code organization
- **Error Handling**: Robust error management
- **Security**: Basic security implementation
- **User Interface**: Menu-driven systems

## 🚀 Extensions

1. Add loan management system
2. Implement ATM interface
3. Add online banking features
4. Create mobile app interface
5. Add blockchain-based security
6. Implement AI-powered fraud detection