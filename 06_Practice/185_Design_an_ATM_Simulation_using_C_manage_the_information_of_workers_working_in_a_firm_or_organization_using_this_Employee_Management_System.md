# 🎯 Practical 185: ATM Simulation & Employee Management System

## 📋 Problem Statement

Design an ATM Simulation using C manage the information of workers working in a firm or organization using this Employee Management System. The file handling technique is used here to save the data in a particular file, and you get the notion of this project as soon as you hear the name. This project uses the Insert, Edit, and Delete file actions, but the sole constraint is that you can only display the data, not search for any data item in particular. If you have more experience with C, you may alter this program by using the searching strategies.

## 🎯 Learning Objectives

- Understand complex system design
- Practice file handling for data persistence
- Learn menu-driven programming
- Understand ATM transaction logic
- Practice employee data management
- Learn structured programming

## 📝 Requirements

1. **ATM Simulation:**
   - Account creation and management
   - Balance inquiry
   - Deposit and withdrawal
   - PIN validation
   - Transaction history

2. **Employee Management System:**
   - Add new employees
   - Edit employee information
   - Delete employees
   - Display all employees
   - File-based data storage

## 💡 Hints

- Use structures for ATM accounts and employees
- Implement file I/O for data persistence
- Create separate menus for ATM and EMS
- Use proper validation and error handling
- Implement data security measures

## 🔧 Solution

```c
// Practical 185: ATM Simulation & Employee Management System
// Comprehensive system with file handling for data persistence

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EMPLOYEES 100
#define MAX_ACCOUNTS 50
#define MAX_TRANSACTIONS 100

// Employee Structure
struct Employee {
    int id;
    char name[50];
    char department[30];
    float salary;
    char designation[30];
    int active;
};

// ATM Account Structure
struct Account {
    int accountNumber;
    char holderName[50];
    int pin;
    float balance;
    int active;
};

// Transaction Structure
struct Transaction {
    int accountNumber;
    char type[20];
    float amount;
    char date[20];
    float balance;
};

// Global variables
struct Employee employees[MAX_EMPLOYEES];
struct Account accounts[MAX_ACCOUNTS];
struct Transaction transactions[MAX_TRANSACTIONS];
int employeeCount = 0;
int accountCount = 0;
int transactionCount = 0;

// File names
#define EMPLOYEE_FILE "employees.dat"
#define ACCOUNT_FILE "accounts.dat"
#define TRANSACTION_FILE "transactions.dat"

// Function prototypes
void loadEmployees();
void saveEmployees();
void loadAccounts();
void saveAccounts();
void loadTransactions();
void saveTransactions();

// Employee Management Functions
void addEmployee();
void editEmployee();
void deleteEmployee();
void displayEmployees();
void employeeMenu();

// ATM Functions
void createAccount();
void loginAccount();
void depositMoney(int accNum);
void withdrawMoney(int accNum);
void checkBalance(int accNum);
void transactionHistory(int accNum);
void atmMenu();

// Utility Functions
void getCurrentDate(char *date);
int generateAccountNumber();
int validatePIN(int pin);
void clearScreen();

int main() {
    int choice;
    
    // Load data from files
    loadEmployees();
    loadAccounts();
    loadTransactions();
    
    while (1) {
        clearScreen();
        printf("=== MAIN MENU ===\n");
        printf("1. Employee Management System\n");
        printf("2. ATM Simulation\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                atmMenu();
                break;
            case 3:
                // Save data before exit
                saveEmployees();
                saveAccounts();
                saveTransactions();
                printf("Data saved successfully!\n");
                printf("Thank you for using the system!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    
    return 0;
}

// Employee Management Functions
void employeeMenu() {
    int choice;
    
    while (1) {
        clearScreen();
        printf("=== EMPLOYEE MANAGEMENT SYSTEM ===\n");
        printf("1. Add Employee\n");
        printf("2. Edit Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display All Employees\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                editEmployee();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4:
                displayEmployees();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Maximum employee limit reached!\n");
        return;
    }
    
    struct Employee emp;
    
    printf("Enter Employee Details:\n");
    printf("ID: ");
    scanf("%d", &emp.id);
    getchar(); // Clear buffer
    
    printf("Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = 0;
    
    printf("Department: ");
    fgets(emp.department, sizeof(emp.department), stdin);
    emp.department[strcspn(emp.department, "\n")] = 0;
    
    printf("Salary: ");
    scanf("%f", &emp.salary);
    getchar();
    
    printf("Designation: ");
    fgets(emp.designation, sizeof(emp.designation), stdin);
    emp.designation[strcspn(emp.designation, "\n")] = 0;
    
    emp.active = 1;
    
    employees[employeeCount++] = emp;
    printf("Employee added successfully!\n");
}

void editEmployee() {
    int id, found = 0;
    
    printf("Enter Employee ID to edit: ");
    scanf("%d", &id);
    
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id && employees[i].active) {
            printf("Current Details:\n");
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Designation: %s\n", employees[i].designation);
            
            printf("\nEnter New Details:\n");
            printf("Name: ");
            getchar();
            fgets(employees[i].name, sizeof(employees[i].name), stdin);
            employees[i].name[strcspn(employees[i].name, "\n")] = 0;
            
            printf("Department: ");
            fgets(employees[i].department, sizeof(employees[i].department), stdin);
            employees[i].department[strcspn(employees[i].department, "\n")] = 0;
            
            printf("Salary: ");
            scanf("%f", &employees[i].salary);
            getchar();
            
            printf("Designation: ");
            fgets(employees[i].designation, sizeof(employees[i].designation), stdin);
            employees[i].designation[strcspn(employees[i].designation, "\n")] = 0;
            
            printf("Employee updated successfully!\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Employee not found!\n");
    }
}

void deleteEmployee() {
    int id, found = 0;
    
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id && employees[i].active) {
            employees[i].active = 0;
            printf("Employee deleted successfully!\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Employee not found!\n");
    }
}

void displayEmployees() {
    printf("=== EMPLOYEE LIST ===\n");
    printf("%-5s %-20s %-15s %-10s %-15s\n", "ID", "Name", "Department", "Salary", "Designation");
    printf("------------------------------------------------------------\n");
    
    int count = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].active) {
            printf("%-5d %-20s %-15s %-10.2f %-15s\n",
                   employees[i].id,
                   employees[i].name,
                   employees[i].department,
                   employees[i].salary,
                   employees[i].designation);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No employees found!\n");
    } else {
        printf("\nTotal employees: %d\n", count);
    }
}

// ATM Functions
void atmMenu() {
    int choice;
    
    while (1) {
        clearScreen();
        printf("=== ATM SIMULATION ===\n");
        printf("1. Create Account\n");
        printf("2. Login to Account\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                loginAccount();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum account limit reached!\n");
        return;
    }
    
    struct Account acc;
    
    acc.accountNumber = generateAccountNumber();
    
    printf("Enter Account Details:\n");
    printf("Account Number: %d\n", acc.accountNumber);
    
    printf("Holder Name: ");
    getchar();
    fgets(acc.holderName, sizeof(acc.holderName), stdin);
    acc.holderName[strcspn(acc.holderName, "\n")] = 0;
    
    printf("Initial PIN (4 digits): ");
    scanf("%d", &acc.pin);
    
    if (!validatePIN(acc.pin)) {
        printf("Invalid PIN! Must be 4 digits.\n");
        return;
    }
    
    printf("Initial Balance: ");
    scanf("%f", &acc.balance);
    
    if (acc.balance < 0) {
        printf("Invalid balance amount!\n");
        return;
    }
    
    acc.active = 1;
    accounts[accountCount++] = acc;
    
    printf("Account created successfully!\n");
    printf("Account Number: %d\n", acc.accountNumber);
    printf("Remember your PIN: %d\n", acc.pin);
}

void loginAccount() {
    int accNum, pin, found = 0;
    
    printf("Enter Account Number: ");
    scanf("%d", &accNum);
    
    printf("Enter PIN: ");
    scanf("%d", &pin);
    
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum && 
            accounts[i].pin == pin && 
            accounts[i].active) {
            
            printf("Login successful! Welcome %s\n", accounts[i].holderName);
            accountMenu(i);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Invalid account number or PIN!\n");
    }
}

void accountMenu(int accIndex) {
    int choice;
    
    while (1) {
        clearScreen();
        printf("=== ACCOUNT MENU ===\n");
        printf("Account: %d\n", accounts[accIndex].accountNumber);
        printf("Holder: %s\n", accounts[accIndex].holderName);
        printf("Balance: $%.2f\n\n", accounts[accIndex].balance);
        
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Check Balance\n");
        printf("4. Transaction History\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                depositMoney(accIndex);
                break;
            case 2:
                withdrawMoney(accIndex);
                break;
            case 3:
                checkBalance(accIndex);
                break;
            case 4:
                transactionHistory(accounts[accIndex].accountNumber);
                break;
            case 5:
                printf("Logged out successfully!\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

void depositMoney(int accIndex) {
    float amount;
    
    printf("Enter deposit amount: $");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    
    accounts[accIndex].balance += amount;
    
    // Record transaction
    if (transactionCount < MAX_TRANSACTIONS) {
        transactions[transactionCount].accountNumber = accounts[accIndex].accountNumber;
        strcpy(transactions[transactionCount].type, "Deposit");
        transactions[transactionCount].amount = amount;
        getCurrentDate(transactions[transactionCount].date);
        transactions[transactionCount].balance = accounts[accIndex].balance;
        transactionCount++;
    }
    
    printf("Deposit successful!\n");
    printf("New balance: $%.2f\n", accounts[accIndex].balance);
}

void withdrawMoney(int accIndex) {
    float amount;
    
    printf("Enter withdrawal amount: $");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    
    if (amount > accounts[accIndex].balance) {
        printf("Insufficient balance!\n");
        return;
    }
    
    accounts[accIndex].balance -= amount;
    
    // Record transaction
    if (transactionCount < MAX_TRANSACTIONS) {
        transactions[transactionCount].accountNumber = accounts[accIndex].accountNumber;
        strcpy(transactions[transactionCount].type, "Withdrawal");
        transactions[transactionCount].amount = amount;
        getCurrentDate(transactions[transactionCount].date);
        transactions[transactionCount].balance = accounts[accIndex].balance;
        transactionCount++;
    }
    
    printf("Withdrawal successful!\n");
    printf("New balance: $%.2f\n", accounts[accIndex].balance);
}

void checkBalance(int accIndex) {
    printf("Current Balance: $%.2f\n", accounts[accIndex].balance);
}

void transactionHistory(int accNum) {
    printf("=== TRANSACTION HISTORY ===\n");
    printf("Account: %d\n\n", accNum);
    
    int count = 0;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].accountNumber == accNum) {
            printf("%s - %s: $%.2f (Balance: $%.2f)\n",
                   transactions[i].date,
                   transactions[i].type,
                   transactions[i].amount,
                   transactions[i].balance);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No transactions found!\n");
    } else {
        printf("\nTotal transactions: %d\n", count);
    }
}

// Utility Functions
void getCurrentDate(char *date) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(date, 20, "%Y-%m-%d %H:%M:%S", tm_info);
}

int generateAccountNumber() {
    return 100000 + accountCount + 1;
}

int validatePIN(int pin) {
    return (pin >= 1000 && pin <= 9999);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// File handling functions (simplified for demonstration)
void loadEmployees() {
    FILE *file = fopen(EMPLOYEE_FILE, "rb");
    if (file != NULL) {
        employeeCount = fread(employees, sizeof(struct Employee), MAX_EMPLOYEES, file);
        fclose(file);
    }
}

void saveEmployees() {
    FILE *file = fopen(EMPLOYEE_FILE, "wb");
    if (file != NULL) {
        fwrite(employees, sizeof(struct Employee), employeeCount, file);
        fclose(file);
    }
}

void loadAccounts() {
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file != NULL) {
        accountCount = fread(accounts, sizeof(struct Account), MAX_ACCOUNTS, file);
        fclose(file);
    }
}

void saveAccounts() {
    FILE *file = fopen(ACCOUNT_FILE, "wb");
    if (file != NULL) {
        fwrite(accounts, sizeof(struct Account), accountCount, file);
        fclose(file);
    }
}

void loadTransactions() {
    FILE *file = fopen(TRANSACTION_FILE, "rb");
    if (file != NULL) {
        transactionCount = fread(transactions, sizeof(struct Transaction), MAX_TRANSACTIONS, file);
        fclose(file);
    }
}

void saveTransactions() {
    FILE *file = fopen(TRANSACTION_FILE, "wb");
    if (file != NULL) {
        fwrite(transactions, sizeof(struct Transaction), transactionCount, file);
        fclose(file);
    }
}
```

## 📊 Test Cases

### Test Case 1: Employee Management
```
Add Employee:
ID: 101
Name: John Doe
Department: IT
Salary: 50000
Designation: Software Engineer
Expected: Employee added successfully
```

### Test Case 2: ATM Account Creation
```
Holder Name: Jane Smith
PIN: 1234
Initial Balance: 1000
Expected: Account created with number generated
```

### Test Case 3: ATM Transaction
```
Login with account number and PIN
Deposit: $500
Expected: Balance updated to $1500
```

## 🔍 Explanation

1. **Dual System**: Combines Employee Management and ATM Simulation
2. **File Persistence**: Data saved to files for persistence
3. **Menu-Driven**: User-friendly interface with multiple menus
4. **Data Structures**: Uses structures for organized data storage
5. **Validation**: Input validation and error handling
6. **Transaction Logging**: Records all ATM transactions

## 🎯 Key Concepts Covered

- Complex system design
- File I/O operations
- Data structures and management
- Menu-driven programming
- Input validation and security
- Transaction processing

## 🚀 Extensions

1. Add search functionality for employees
2. Implement account transfer between users
3. Add interest calculation for accounts
4. Implement employee salary calculations
5. Add user authentication for EMS