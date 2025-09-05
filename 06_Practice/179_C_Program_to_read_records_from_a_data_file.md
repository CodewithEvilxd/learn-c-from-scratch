# 🎯 Practical 179: Read Records from a Data File

## 📋 Problem Statement

C Program to read records from a data file.

## 🎯 Learning Objectives

- Understand record-based file reading
- Practice structured data handling
- Learn data parsing from files
- Understand file formats
- Practice data validation

## 📝 Requirements

1. Accept data filename
2. Define record structure
3. Read records from file
4. Parse and display record data
5. Handle file format errors

## 💡 Hints

- Define structure for records
- Use fscanf for formatted reading
- Handle different data types
- Validate record format
- Display records in table format

## 🔧 Solution

```c
// Practical 179: Read Records from a Data File
// Demonstrates reading structured records from a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

struct Record {
    int id;
    char name[50];
    int age;
    float salary;
};

int main() {
    FILE *filePointer;
    char filename[100];
    struct Record records[MAX_RECORDS];
    int recordCount = 0;

    printf("Read Records from a Data File\n");
    printf("==============================\n");

    printf("Enter data filename: ");
    scanf("%s", filename);

    // Open file for reading
    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Error opening file '%s'!\n", filename);
        printf("Make sure the file exists and contains records in format:\n");
        printf("id,name,age,salary\n");
        return 1;
    }

    // Read records from file
    printf("Reading records from '%s'...\n\n", filename);

    while (recordCount < MAX_RECORDS &&
           fscanf(filePointer, "%d,%[^,],%d,%f",
                  &records[recordCount].id,
                  records[recordCount].name,
                  &records[recordCount].age,
                  &records[recordCount].salary) == 4) {
        recordCount++;
    }

    // Close file
    fclose(filePointer);

    // Display records
    if (recordCount == 0) {
        printf("No valid records found in the file!\n");
        printf("Expected format: id,name,age,salary\n");
        return 1;
    }

    printf("Records read successfully!\n\n");
    printf("Employee Records:\n");
    printf("================\n");
    printf("%-5s %-20s %-5s %-10s\n", "ID", "Name", "Age", "Salary");
    printf("----------------------------------------\n");

    for (int i = 0; i < recordCount; i++) {
        printf("%-5d %-20s %-5d $%-10.2f\n",
               records[i].id,
               records[i].name,
               records[i].age,
               records[i].salary);
    }

    printf("\nTotal records: %d\n", recordCount);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Valid Records
```
File content:
101,John Doe,25,50000.50
102,Jane Smith,30,60000.75
Expected Output:
Employee Records:
================
ID    Name                 Age   Salary
----------------------------------------
101   John Doe             25    $50000.50
102   Jane Smith           30    $60000.75

Total records: 2
```

## 🔍 Explanation

1. **File Opening**: Open data file for reading
2. **Record Reading**: Use fscanf to parse structured data
3. **Data Storage**: Store records in structure array
4. **Display**: Format and display records in table
5. **Validation**: Check for valid record format

## 🎯 Key Concepts Covered

- Structured data reading
- File parsing
- Data validation
- Formatted output
- Record handling

## 🚀 Extensions

1. Write records to file
2. Search specific records
3. Sort records
4. Handle variable record formats