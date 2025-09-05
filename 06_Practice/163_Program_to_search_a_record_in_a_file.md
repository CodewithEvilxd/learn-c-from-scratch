# 🎯 Practical 163: Search a Record in a File

## 📋 Problem Statement

Program to search a record in a file.

## 🎯 Learning Objectives

- Understand file searching
- Practice record parsing
- Learn search algorithms
- Understand data retrieval
- Practice file navigation

## 📝 Requirements

1. Accept search criteria
2. Open file for reading
3. Search for matching records
4. Display found records
5. Handle search failures

## 💡 Hints

- Read file line by line
- Parse record fields
- Compare with search criteria
- Handle multiple matches
- Display formatted results

## 🔧 Solution

```c
// Practical 163: Search a Record in a File
// Demonstrates searching for records in a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200

struct Record {
    int id;
    char name[50];
    float salary;
    char department[30];
};

int parseRecord(char *line, struct Record *record) {
    // Parse CSV format: id,name,salary,department
    char *token;
    
    // Get ID
    token = strtok(line, ",");
    if (token == NULL) return 0;
    record->id = atoi(token);
    
    // Get name
    token = strtok(NULL, ",");
    if (token == NULL) return 0;
    strcpy(record->name, token);
    
    // Get salary
    token = strtok(NULL, ",");
    if (token == NULL) return 0;
    record->salary = atof(token);
    
    // Get department
    token = strtok(NULL, ",");
    if (token == NULL) return 0;
    strcpy(record->department, token);
    
    return 1;
}

void displayRecord(struct Record *record) {
    printf("ID: %d\n", record->id);
    printf("Name: %s\n", record->name);
    printf("Salary: %.2f\n", record->salary);
    printf("Department: %s\n", record->department);
    printf("------------------------\n");
}

int main() {
    FILE *filePointer;
    char filename[100];
    char line[MAX_LINE_LENGTH];
    struct Record record;
    int searchId;
    int found = 0;

    printf("Search a Record in a File\n");
    printf("=========================\n");

    printf("Enter filename: ");
    scanf("%s", filename);

    printf("Enter ID to search: ");
    scanf("%d", &searchId);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file! Make sure the file exists.\n");
        return 1;
    }

    printf("\nSearching for records with ID: %d\n", searchId);
    printf("================================\n");

    // Read file line by line
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        // Remove newline character
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Parse record
        if (parseRecord(line, &record)) {
            // Check if ID matches
            if (record.id == searchId) {
                printf("Record found:\n");
                displayRecord(&record);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No record found with ID: %d\n", searchId);
    }

    fclose(filePointer);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Record Found
```
File content:
101,John Doe,50000.50,IT
102,Jane Smith,45000.00,HR
103,Bob Johnson,55000.75,Finance

Search ID: 102
Expected Output:
Record found:
ID: 102
Name: Jane Smith
Salary: 45000.00
Department: HR
```

### Test Case 2: Record Not Found
```
Search ID: 999
Expected Output:
No record found with ID: 999
```

## 🔍 Explanation

1. **File Opening**: Open file for reading
2. **Search Input**: Get search criteria from user
3. **Line Reading**: Read file line by line
4. **Record Parsing**: Parse CSV format records
5. **Search Comparison**: Compare record ID with search ID
6. **Result Display**: Show matching records

## 🎯 Key Concepts Covered

- File searching
- Record parsing
- CSV format handling
- String tokenization
- Search algorithms

## 🚀 Extensions

1. Search by name instead of ID
2. Implement multiple search criteria
3. Add wildcard search
4. Search in binary files