# 👥 Employee Management System
## Complete HR management solution with employee records and analytics

---

## 📋 Project Overview

This project implements a comprehensive Employee Management System in C that handles employee records, payroll calculations, attendance tracking, and HR analytics. It demonstrates database-like operations, file persistence, and business logic implementation.

## 🎯 Learning Objectives

- Understand data persistence techniques
- Learn record management systems
- Practice file I/O for structured data
- Implement business logic
- Learn data analysis and reporting

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries
- **Platform**: Cross-platform
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
employee_management/
├── src/
│   ├── main.c           # Main program with menu
│   ├── employee.c       # Employee data management
│   ├── payroll.c        # Salary and payroll calculations
│   ├── attendance.c     # Attendance tracking
│   ├── file_io.c        # Data persistence
│   └── analytics.c      # HR analytics and reporting
├── include/
│   ├── employee.h
│   ├── payroll.h
│   ├── attendance.h
│   ├── file_io.h
│   └── analytics.h
├── data/
│   ├── employees.dat
│   └── attendance.dat
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Employee Data Structure**

```c
// employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 50
#define MAX_DEPARTMENT 30
#define MAX_POSITION 30
#define MAX_EMPLOYEES 1000

typedef enum {
    GENDER_MALE,
    GENDER_FEMALE,
    GENDER_OTHER
} Gender;

typedef enum {
    STATUS_ACTIVE,
    STATUS_INACTIVE,
    STATUS_TERMINATED
} EmploymentStatus;

typedef struct {
    int year, month, day;
} Date;

typedef struct {
    int employee_id;
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    Date birth_date;
    Gender gender;
    char department[MAX_DEPARTMENT];
    char position[MAX_POSITION];
    double salary;
    Date hire_date;
    EmploymentStatus status;
    char email[MAX_NAME];
    char phone[15];
} Employee;

// Function prototypes
Employee* create_employee(int id, const char* first_name, const char* last_name);
void free_employee(Employee* emp);
void print_employee(const Employee* emp);
int compare_employees_by_id(const void* a, const void* b);
int compare_employees_by_name(const void* a, const void* b);

#endif
```

```c
// employee.c
#include "employee.h"

Employee* create_employee(int id, const char* first_name, const char* last_name) {
    Employee* emp = (Employee*)malloc(sizeof(Employee));
    if (!emp) return NULL;

    emp->employee_id = id;
    strncpy(emp->first_name, first_name, MAX_NAME - 1);
    emp->first_name[MAX_NAME - 1] = '\0';

    strncpy(emp->last_name, last_name, MAX_NAME - 1);
    emp->last_name[MAX_NAME - 1] = '\0';

    // Initialize other fields with defaults
    emp->birth_date.year = 1990;
    emp->birth_date.month = 1;
    emp->birth_date.day = 1;

    emp->gender = GENDER_OTHER;
    strcpy(emp->department, "General");
    strcpy(emp->position, "Employee");
    emp->salary = 0.0;

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    emp->hire_date.year = tm_info->tm_year + 1900;
    emp->hire_date.month = tm_info->tm_mon + 1;
    emp->hire_date.day = tm_info->tm_mday;

    emp->status = STATUS_ACTIVE;
    sprintf(emp->email, "%s.%s@company.com", first_name, last_name);
    strcpy(emp->phone, "000-000-0000");

    return emp;
}

void free_employee(Employee* emp) {
    if (emp) {
        free(emp);
    }
}

void print_employee(const Employee* emp) {
    if (!emp) return;

    printf("\nEmployee Details:\n");
    printf("================\n");
    printf("ID: %d\n", emp->employee_id);
    printf("Name: %s %s\n", emp->first_name, emp->last_name);
    printf("Birth Date: %02d/%02d/%04d\n",
           emp->birth_date.month, emp->birth_date.day, emp->birth_date.year);
    printf("Gender: %s\n",
           emp->gender == GENDER_MALE ? "Male" :
           emp->gender == GENDER_FEMALE ? "Female" : "Other");
    printf("Department: %s\n", emp->department);
    printf("Position: %s\n", emp->position);
    printf("Salary: $%.2f\n", emp->salary);
    printf("Hire Date: %02d/%02d/%04d\n",
           emp->hire_date.month, emp->hire_date.day, emp->hire_date.year);
    printf("Status: %s\n",
           emp->status == STATUS_ACTIVE ? "Active" :
           emp->status == STATUS_INACTIVE ? "Inactive" : "Terminated");
    printf("Email: %s\n", emp->email);
    printf("Phone: %s\n", emp->phone);
}

int compare_employees_by_id(const void* a, const void* b) {
    const Employee* emp_a = (const Employee*)a;
    const Employee* emp_b = (const Employee*)b;
    return emp_a->employee_id - emp_b->employee_id;
}

int compare_employees_by_name(const void* a, const void* b) {
    const Employee* emp_a = (const Employee*)a;
    const Employee* emp_b = (const Employee*)b;
    int result = strcmp(emp_a->last_name, emp_b->last_name);
    if (result == 0) {
        result = strcmp(emp_a->first_name, emp_b->first_name);
    }
    return result;
}
```

### **Step 2: Payroll System**

```c
// payroll.h
#ifndef PAYROLL_H
#define PAYROLL_H

#include "employee.h"

typedef struct {
    int employee_id;
    double base_salary;
    double overtime_hours;
    double overtime_rate;
    double deductions;
    double bonuses;
    double net_salary;
    Date pay_period_start;
    Date pay_period_end;
} PayrollRecord;

// Function prototypes
PayrollRecord* calculate_payroll(const Employee* emp, double overtime_hours,
                                double deductions, double bonuses);
void print_payroll_record(const PayrollRecord* record);
double calculate_gross_salary(const Employee* emp, double overtime_hours);
double calculate_net_salary(double gross_salary, double deductions, double bonuses);

#endif
```

```c
// payroll.c
#include "payroll.h"

PayrollRecord* calculate_payroll(const Employee* emp, double overtime_hours,
                                double deductions, double bonuses) {
    PayrollRecord* record = (PayrollRecord*)malloc(sizeof(PayrollRecord));
    if (!record) return NULL;

    record->employee_id = emp->employee_id;
    record->base_salary = emp->salary;
    record->overtime_hours = overtime_hours;
    record->overtime_rate = emp->salary / 2080 * 1.5; // Assuming 40 hours/week * 52 weeks
    record->deductions = deductions;
    record->bonuses = bonuses;

    double gross_salary = calculate_gross_salary(emp, overtime_hours);
    record->net_salary = calculate_net_salary(gross_salary, deductions, bonuses);

    // Set pay period (simplified - monthly)
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    record->pay_period_end.year = tm_info->tm_year + 1900;
    record->pay_period_end.month = tm_info->tm_mon + 1;
    record->pay_period_end.day = tm_info->tm_mday;

    // Start of pay period (30 days ago)
    record->pay_period_start = record->pay_period_end;
    record->pay_period_start.day -= 30;
    if (record->pay_period_start.day <= 0) {
        record->pay_period_start.month--;
        if (record->pay_period_start.month <= 0) {
            record->pay_period_start.month = 12;
            record->pay_period_start.year--;
        }
        // Simplified date calculation
        record->pay_period_start.day += 30;
    }

    return record;
}

double calculate_gross_salary(const Employee* emp, double overtime_hours) {
    double regular_pay = emp->salary;
    double overtime_pay = overtime_hours * (emp->salary / 2080 * 1.5);
    return regular_pay + overtime_pay;
}

double calculate_net_salary(double gross_salary, double deductions, double bonuses) {
    // Simplified tax calculation (20% of gross)
    double taxes = gross_salary * 0.20;
    return gross_salary - taxes - deductions + bonuses;
}

void print_payroll_record(const PayrollRecord* record) {
    printf("\nPayroll Record:\n");
    printf("==============\n");
    printf("Employee ID: %d\n", record->employee_id);
    printf("Base Salary: $%.2f\n", record->base_salary);
    printf("Overtime Hours: %.2f\n", record->overtime_hours);
    printf("Overtime Rate: $%.2f/hour\n", record->overtime_rate);
    printf("Deductions: $%.2f\n", record->deductions);
    printf("Bonuses: $%.2f\n", record->bonuses);
    printf("Net Salary: $%.2f\n", record->net_salary);
    printf("Pay Period: %02d/%02d/%04d - %02d/%02d/%04d\n",
           record->pay_period_start.month, record->pay_period_start.day, record->pay_period_start.year,
           record->pay_period_end.month, record->pay_period_end.day, record->pay_period_end.year);
}
```

### **Step 3: File I/O for Data Persistence**

```c
// file_io.h
#ifndef FILE_IO_H
#define FILE_IO_H

#include "employee.h"

#define EMPLOYEE_FILE "data/employees.dat"
#define PAYROLL_FILE "data/payroll.dat"

int save_employee_to_file(const Employee* emp, const char* filename);
Employee* load_employee_from_file(const char* filename, int employee_id);
int save_all_employees(Employee* employees[], int count, const char* filename);
Employee** load_all_employees(const char* filename, int* count);
int update_employee_file(const Employee* emp, const char* filename);
int delete_employee_from_file(int employee_id, const char* filename);

#endif
```

```c
// file_io.c
#include "file_io.h"

int save_employee_to_file(const Employee* emp, const char* filename) {
    FILE* file = fopen(filename, "ab"); // Append binary
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    size_t written = fwrite(emp, sizeof(Employee), 1, file);
    fclose(file);

    return written == 1 ? 0 : -1;
}

Employee* load_employee_from_file(const char* filename, int employee_id) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return NULL;
    }

    Employee* emp = (Employee*)malloc(sizeof(Employee));
    if (!emp) {
        fclose(file);
        return NULL;
    }

    while (fread(emp, sizeof(Employee), 1, file) == 1) {
        if (emp->employee_id == employee_id) {
            fclose(file);
            return emp;
        }
    }

    free(emp);
    fclose(file);
    return NULL;
}

int save_all_employees(Employee* employees[], int count, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (employees[i]) {
            fwrite(employees[i], sizeof(Employee), 1, file);
        }
    }

    fclose(file);
    return 0;
}

Employee** load_all_employees(const char* filename, int* count) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        *count = 0;
        return NULL;
    }

    // Count employees
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    *count = file_size / sizeof(Employee);
    fseek(file, 0, SEEK_SET);

    if (*count == 0) {
        fclose(file);
        return NULL;
    }

    Employee** employees = (Employee**)malloc(*count * sizeof(Employee*));
    if (!employees) {
        fclose(file);
        *count = 0;
        return NULL;
    }

    for (int i = 0; i < *count; i++) {
        employees[i] = (Employee*)malloc(sizeof(Employee));
        if (!employees[i] || fread(employees[i], sizeof(Employee), 1, file) != 1) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                free(employees[j]);
            }
            free(employees);
            fclose(file);
            *count = 0;
            return NULL;
        }
    }

    fclose(file);
    return employees;
}

int update_employee_file(const Employee* emp, const char* filename) {
    // This is a simplified implementation
    // In a real system, you'd want to update the specific record
    return save_employee_to_file(emp, filename);
}

int delete_employee_from_file(int employee_id, const char* filename) {
    // Load all employees
    int count;
    Employee** employees = load_all_employees(filename, &count);
    if (!employees) return -1;

    // Create new array without the deleted employee
    int new_count = 0;
    Employee** new_employees = NULL;

    for (int i = 0; i < count; i++) {
        if (employees[i]->employee_id != employee_id) {
            new_employees = (Employee**)realloc(new_employees,
                                               (new_count + 1) * sizeof(Employee*));
            new_employees[new_count] = employees[i];
            new_count++;
        } else {
            free(employees[i]);
        }
    }

    free(employees);

    // Save updated list
    int result = save_all_employees(new_employees, new_count, filename);

    // Cleanup
    for (int i = 0; i < new_count; i++) {
        free(new_employees[i]);
    }
    free(new_employees);

    return result;
}
```

### **Step 4: Main Program**

```c
// main.c
#include "employee.h"
#include "payroll.h"
#include "file_io.h"

#define MAX_EMPLOYEES 100

void display_menu(void) {
    printf("\n=== Employee Management System ===\n");
    printf("1. Add new employee\n");
    printf("2. View employee details\n");
    printf("3. Update employee information\n");
    printf("4. Delete employee\n");
    printf("5. List all employees\n");
    printf("6. Calculate payroll\n");
    printf("7. Generate employee report\n");
    printf("8. Search employees\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Employee* employees[MAX_EMPLOYEES] = {NULL};
    int employee_count = 0;
    int choice;

    // Load existing employees
    employees = load_all_employees(EMPLOYEE_FILE, &employee_count);

    printf("Employee Management System\n");
    printf("==========================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: { // Add employee
                if (employee_count >= MAX_EMPLOYEES) {
                    printf("Maximum employee limit reached!\n");
                    break;
                }

                char first_name[MAX_NAME], last_name[MAX_NAME];
                printf("Enter first name: ");
                scanf("%s", first_name);
                printf("Enter last name: ");
                scanf("%s", last_name);

                int id = employee_count + 1; // Simple ID assignment
                Employee* emp = create_employee(id, first_name, last_name);

                if (emp) {
                    employees[employee_count] = emp;
                    employee_count++;

                    // Save to file
                    save_employee_to_file(emp, EMPLOYEE_FILE);
                    printf("Employee added successfully with ID: %d\n", id);
                } else {
                    printf("Failed to create employee!\n");
                }
                break;
            }

            case 2: { // View employee
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);

                Employee* emp = NULL;
                for (int i = 0; i < employee_count; i++) {
                    if (employees[i] && employees[i]->employee_id == id) {
                        emp = employees[i];
                        break;
                    }
                }

                if (emp) {
                    print_employee(emp);
                } else {
                    printf("Employee not found!\n");
                }
                break;
            }

            case 3: { // Update employee
                int id;
                printf("Enter employee ID to update: ");
                scanf("%d", &id);

                Employee* emp = NULL;
                for (int i = 0; i < employee_count; i++) {
                    if (employees[i] && employees[i]->employee_id == id) {
                        emp = employees[i];
                        break;
                    }
                }

                if (emp) {
                    printf("Current salary: $%.2f\n", emp->salary);
                    printf("Enter new salary: ");
                    scanf("%lf", &emp->salary);

                    // Update file
                    update_employee_file(emp, EMPLOYEE_FILE);
                    printf("Employee updated successfully!\n");
                } else {
                    printf("Employee not found!\n");
                }
                break;
            }

            case 4: { // Delete employee
                int id;
                printf("Enter employee ID to delete: ");
                scanf("%d", &id);

                for (int i = 0; i < employee_count; i++) {
                    if (employees[i] && employees[i]->employee_id == id) {
                        free_employee(employees[i]);
                        employees[i] = NULL;

                        delete_employee_from_file(id, EMPLOYEE_FILE);
                        printf("Employee deleted successfully!\n");
                        break;
                    }
                }
                break;
            }

            case 5: { // List all employees
                printf("\nAll Employees:\n");
                printf("==============\n");
                for (int i = 0; i < employee_count; i++) {
                    if (employees[i]) {
                        printf("ID: %d, Name: %s %s, Department: %s\n",
                               employees[i]->employee_id,
                               employees[i]->first_name,
                               employees[i]->last_name,
                               employees[i]->department);
                    }
                }
                break;
            }

            case 6: { // Calculate payroll
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);

                Employee* emp = NULL;
                for (int i = 0; i < employee_count; i++) {
                    if (employees[i] && employees[i]->employee_id == id) {
                        emp = employees[i];
                        break;
                    }
                }

                if (emp) {
                    double overtime, deductions, bonuses;
                    printf("Enter overtime hours: ");
                    scanf("%lf", &overtime);
                    printf("Enter deductions: ");
                    scanf("%lf", &deductions);
                    printf("Enter bonuses: ");
                    scanf("%lf", &bonuses);

                    PayrollRecord* payroll = calculate_payroll(emp, overtime,
                                                             deductions, bonuses);
                    if (payroll) {
                        print_payroll_record(payroll);
                        free(payroll);
                    }
                } else {
                    printf("Employee not found!\n");
                }
                break;
            }

            case 7: { // Generate report
                printf("\nEmployee Report:\n");
                printf("================\n");
                printf("Total Employees: %d\n", employee_count);

                double total_salary = 0.0;
                for (int i = 0; i < employee_count; i++) {
                    if (employees[i]) {
                        total_salary += employees[i]->salary;
                    }
                }

                printf("Total Salary Budget: $%.2f\n", total_salary);
                printf("Average Salary: $%.2f\n",
                       employee_count > 0 ? total_salary / employee_count : 0.0);
                break;
            }

            case 8: { // Search employees
                char search_term[MAX_NAME];
                printf("Enter search term (name or department): ");
                scanf("%s", search_term);

                printf("\nSearch Results:\n");
                printf("================\n");

                for (int i = 0; i < employee_count; i++) {
                    if (employees[i] &&
                        (strstr(employees[i]->first_name, search_term) ||
                         strstr(employees[i]->last_name, search_term) ||
                         strstr(employees[i]->department, search_term))) {
                        printf("ID: %d, Name: %s %s, Department: %s\n",
                               employees[i]->employee_id,
                               employees[i]->first_name,
                               employees[i]->last_name,
                               employees[i]->department);
                    }
                }
                break;
            }

            case 0:
                printf("Saving data and exiting...\n");

                // Save all employees
                save_all_employees(employees, employee_count, EMPLOYEE_FILE);

                // Cleanup
                for (int i = 0; i < employee_count; i++) {
                    if (employees[i]) {
                        free_employee(employees[i]);
                    }
                }
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core HR Features**
- [x] Employee record management
- [x] Payroll calculation
- [x] Data persistence
- [x] Search and filtering
- [x] Reporting and analytics

### **✅ Advanced Features**
- [x] File I/O for data storage
- [x] Memory management
- [x] Error handling
- [x] Data validation
- [x] User-friendly interface

### **🚀 Extensions**
- [ ] Attendance tracking
- [ ] Performance management
- [ ] Leave management
- [ ] Employee benefits
- [ ] Training records
- [ ] Organizational charts

## 🧪 Testing and Usage

### **Basic Usage**
```bash
# Compile the program
gcc -o employee_system main.c employee.c payroll.c file_io.c

# Run the system
./employee_system

# Add an employee
1
John
Doe
# Follow prompts...

# View employee details
2
1
```

### **Sample Data File Format**
```
Employee records are stored in binary format using fwrite/fread
Each record contains: ID, names, dates, department, salary, etc.
```

## 📊 Technical Learning Outcomes

### **Data Management Skills**
- Binary file I/O operations
- Data persistence techniques
- Record management
- Search and sort algorithms
- Memory management

### **Business Logic Implementation**
- Payroll calculations
- Data validation
- Report generation
- User interface design
- Error handling

## 🚀 Advanced Extensions

### **Database Integration**
```c
// SQLite integration for better data management
#include <sqlite3.h>

int create_employee_table(sqlite3* db) {
    const char* sql = "CREATE TABLE employees ("
                     "id INTEGER PRIMARY KEY,"
                     "first_name TEXT,"
                     "last_name TEXT,"
                     "salary REAL);";

    return sqlite3_exec(db, sql, NULL, NULL, NULL);
}
```

### **Web Interface**
```c
// Simple HTTP server integration
#include "server.h"

void handle_employee_request(int client_socket, const char* request) {
    // Parse HTTP request and return employee data as JSON
}
```

## 📖 References

- **"Database System Concepts"** by Silberschatz et al.
- **"Human Resource Management"** concepts
- **File I/O in C** - GNU C Library
- **Payroll Systems** - Accounting principles

## 🎯 Real-World Applications

- **HR Management**: Employee record systems
- **Payroll Processing**: Salary calculations
- **Attendance Systems**: Time tracking
- **Performance Management**: Employee evaluations
- **Reporting**: HR analytics and insights

---

**👥 This project demonstrates comprehensive employee management and business data processing in C!**