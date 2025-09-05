# 🎯 Practical 186: Employee Database Management System

## 📋 Problem Statement

The following modules are included in this project. Add Employee Details, Edit Employee details, Modify Employee, Delete Employee, Create a Database using C file structure.

## 🎯 Learning Objectives

- Understand database concepts in C
- Practice file-based data storage
- Learn CRUD operations (Create, Read, Update, Delete)
- Understand data persistence
- Practice structured data management

## 📝 Requirements

1. **Add Employee Details**: Create new employee records
2. **Edit Employee Details**: Modify existing employee information
3. **Modify Employee**: Update employee data
4. **Delete Employee**: Remove employee records
5. **Database Creation**: Use C file structure for data storage

## 💡 Hints

- Use structures for employee data
- Implement file I/O for database operations
- Create functions for each CRUD operation
- Use binary files for data storage
- Implement proper error handling

## 🔧 Solution

```c
// Practical 186: Employee Database Management System
// Complete CRUD operations with file-based database

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMPLOYEES 1000
#define FILENAME "employee_database.dat"

// Employee structure
struct Employee {
    int id;
    char name[50];
    char department[30];
    char designation[30];
    float salary;
    char phone[15];
    char email[50];
    int active; // 1 for active, 0 for deleted
};

// Function prototypes
void displayMenu();
void addEmployee();
void editEmployee();
void modifyEmployee();
void deleteEmployee();
void displayAllEmployees();
void searchEmployee();
void loadDatabase(struct Employee employees[], int *count);
void saveDatabase(struct Employee employees[], int count);
int generateEmployeeID(struct Employee employees[], int count);
void clearInputBuffer();

int main() {
    struct Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    int choice;

    // Load existing database
    loadDatabase(employees, &employeeCount);

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addEmployee(employees, &employeeCount);
                break;
            case 2:
                editEmployee(employees, employeeCount);
                break;
            case 3:
                modifyEmployee(employees, employeeCount);
                break;
            case 4:
                deleteEmployee(employees, &employeeCount);
                break;
            case 5:
                displayAllEmployees(employees, employeeCount);
                break;
            case 6:
                searchEmployee(employees, employeeCount);
                break;
            case 7:
                saveDatabase(employees, employeeCount);
                printf("Database saved successfully!\n");
                break;
            case 8:
                saveDatabase(employees, employeeCount);
                printf("Thank you for using Employee Database Management System!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
    }

    return 0;
}

void displayMenu() {
    printf("\n=== EMPLOYEE DATABASE MANAGEMENT SYSTEM ===\n");
    printf("1. Add Employee Details\n");
    printf("2. Edit Employee Details\n");
    printf("3. Modify Employee\n");
    printf("4. Delete Employee\n");
    printf("5. Display All Employees\n");
    printf("6. Search Employee\n");
    printf("7. Save Database\n");
    printf("8. Exit\n");
    printf("===========================================\n");
}

void addEmployee(struct Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Database is full! Cannot add more employees.\n");
        return;
    }

    struct Employee emp;
    int newID = generateEmployeeID(employees, *count);

    printf("=== ADD NEW EMPLOYEE ===\n");
    printf("Employee ID will be: %d\n", newID);
    emp.id = newID;

    printf("Enter Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = 0;

    printf("Enter Department: ");
    fgets(emp.department, sizeof(emp.department), stdin);
    emp.department[strcspn(emp.department, "\n")] = 0;

    printf("Enter Designation: ");
    fgets(emp.designation, sizeof(emp.designation), stdin);
    emp.designation[strcspn(emp.designation, "\n")] = 0;

    printf("Enter Salary: ");
    scanf("%f", &emp.salary);
    clearInputBuffer();

    printf("Enter Phone: ");
    fgets(emp.phone, sizeof(emp.phone), stdin);
    emp.phone[strcspn(emp.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(emp.email, sizeof(emp.email), stdin);
    emp.email[strcspn(emp.email, "\n")] = 0;

    emp.active = 1;

    employees[*count] = emp;
    (*count)++;

    printf("Employee added successfully!\n");
}

void editEmployee(struct Employee employees[], int count) {
    int id, found = 0;

    printf("Enter Employee ID to edit: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id && employees[i].active) {
            printf("Current Employee Details:\n");
            printf("ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);
            printf("Designation: %s\n", employees[i].designation);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Phone: %s\n", employees[i].phone);
            printf("Email: %s\n", employees[i].email);

            printf("\nEnter New Details:\n");

            printf("Name: ");
            fgets(employees[i].name, sizeof(employees[i].name), stdin);
            employees[i].name[strcspn(employees[i].name, "\n")] = 0;

            printf("Department: ");
            fgets(employees[i].department, sizeof(employees[i].department), stdin);
            employees[i].department[strcspn(employees[i].department, "\n")] = 0;

            printf("Designation: ");
            fgets(employees[i].designation, sizeof(employees[i].designation), stdin);
            employees[i].designation[strcspn(employees[i].designation, "\n")] = 0;

            printf("Salary: ");
            scanf("%f", &employees[i].salary);
            clearInputBuffer();

            printf("Phone: ");
            fgets(employees[i].phone, sizeof(employees[i].phone), stdin);
            employees[i].phone[strcspn(employees[i].phone, "\n")] = 0;

            printf("Email: ");
            fgets(employees[i].email, sizeof(employees[i].email), stdin);
            employees[i].email[strcspn(employees[i].email, "\n")] = 0;

            printf("Employee details updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found!\n", id);
    }
}

void modifyEmployee(struct Employee employees[], int count) {
    // Modify is same as edit in this context
    editEmployee(employees, count);
}

void deleteEmployee(struct Employee employees[], int *count) {
    int id, found = 0;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < *count; i++) {
        if (employees[i].id == id && employees[i].active) {
            employees[i].active = 0; // Soft delete
            printf("Employee deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found!\n", id);
    }
}

void displayAllEmployees(struct Employee employees[], int count) {
    printf("=== EMPLOYEE DATABASE ===\n");
    printf("%-5s %-20s %-15s %-15s %-10s %-15s %-30s\n",
           "ID", "Name", "Department", "Designation", "Salary", "Phone", "Email");
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    int displayCount = 0;
    for (int i = 0; i < count; i++) {
        if (employees[i].active) {
            printf("%-" "5d %-" "20s %-" "15s %-" "15s %-" "10.2f %-" "15s %-" "30s\n",
                   employees[i].id,
                   employees[i].name,
                   employees[i].department,
                   employees[i].designation,
                   employees[i].salary,
                   employees[i].phone,
                   employees[i].email);
            displayCount++;
        }
    }

    if (displayCount == 0) {
        printf("No employees found in database!\n");
    } else {
        printf("\nTotal employees: %d\n", displayCount);
    }
}

void searchEmployee(struct Employee employees[], int count) {
    int id, found = 0;

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id && employees[i].active) {
            printf("Employee Found:\n");
            printf("ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);
            printf("Designation: %s\n", employees[i].designation);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Phone: %s\n", employees[i].phone);
            printf("Email: %s\n", employees[i].email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found!\n", id);
    }
}

void loadDatabase(struct Employee employees[], int *count) {
    FILE *file = fopen(FILENAME, "rb");
    if (file != NULL) {
        *count = fread(employees, sizeof(struct Employee), MAX_EMPLOYEES, file);
        fclose(file);
        printf("Database loaded successfully! %d employees found.\n", *count);
    } else {
        printf("No existing database found. Starting fresh.\n");
    }
}

void saveDatabase(struct Employee employees[], int count) {
    FILE *file = fopen(FILENAME, "wb");
    if (file != NULL) {
        fwrite(employees, sizeof(struct Employee), count, file);
        fclose(file);
    } else {
        printf("Error saving database!\n");
    }
}

int generateEmployeeID(struct Employee employees[], int count) {
    int maxID = 0;
    for (int i = 0; i < count; i++) {
        if (employees[i].id > maxID) {
            maxID = employees[i].id;
        }
    }
    return maxID + 1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

## 📊 Test Cases

### Test Case 1: Add Employee
```
Name: John Doe
Department: IT
Designation: Software Engineer
Salary: 50000
Phone: 1234567890
Email: john@example.com
Expected: Employee added with auto-generated ID
```

### Test Case 2: Edit Employee
```
ID: 1
New Name: John Smith
Expected: Employee details updated
```

### Test Case 3: Delete Employee
```
ID: 1
Expected: Employee marked as deleted
```

## 🔍 Explanation

1. **Database Structure**: Uses C structures for employee data
2. **File Operations**: Binary file I/O for data persistence
3. **CRUD Operations**: Complete Create, Read, Update, Delete functionality
4. **Auto ID Generation**: Automatic employee ID assignment
5. **Soft Delete**: Employees marked as inactive rather than removed

## 🎯 Key Concepts Covered

- File-based database management
- CRUD operations
- Data structures
- File I/O operations
- Input validation

## 🚀 Extensions

1. Add search by name/department
2. Implement sorting functionality
3. Add backup and restore features
4. Create reports and statistics
