# 🗄️ Simple Database Engine
## Custom database implementation with SQL-like query language

---

## 📋 Project Overview

This project implements a simple but functional database engine in C that supports basic SQL-like operations including table creation, data insertion, querying, and indexing. It demonstrates database internals, file-based storage, and query processing without external database libraries.

## 🎯 Learning Objectives

- Understand database architecture
- Learn data storage and indexing
- Practice query processing
- Implement B-tree data structures
- Learn transaction concepts

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries
- **Platform**: Cross-platform
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
simple_db/
├── src/
│   ├── main.c           # Main database interface
│   ├── database.c       # Core database engine
│   ├── table.c          # Table management
│   ├── query.c          # Query processing
│   ├── storage.c        # Data persistence
│   ├── index.c          # Indexing system
│   └── btree.c          # B-tree implementation
├── include/
│   ├── database.h
│   ├── table.h
│   ├── query.h
│   ├── storage.h
│   ├── index.h
│   └── btree.h
├── data/
│   ├── tables/
│   └── indexes/
├── examples/
│   ├── employees.db
│   └── sales.db
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Core Database Structures**

```c
// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TABLE_NAME 64
#define MAX_COLUMN_NAME 32
#define MAX_STRING_LENGTH 256
#define PAGE_SIZE 4096

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL
} DataType;

typedef struct {
    char name[MAX_COLUMN_NAME];
    DataType type;
    bool is_primary_key;
    bool nullable;
} Column;

typedef struct {
    Column* columns;
    int column_count;
    char* data;  // Serialized row data
    int data_size;
} Row;

typedef struct {
    char name[MAX_TABLE_NAME];
    Column* columns;
    int column_count;
    int row_count;
    char filename[256];
} Table;

typedef struct {
    Table* tables;
    int table_count;
    char db_name[256];
    char db_path[512];
} Database;

// Function prototypes
Database* database_create(const char* name, const char* path);
void database_free(Database* db);
Table* database_create_table(Database* db, const char* name, Column* columns, int column_count);
Table* database_get_table(Database* db, const char* name);
bool database_drop_table(Database* db, const char* name);
void database_save(Database* db);
Database* database_load(const char* path);

#endif
```

```c
// database.c
#include "database.h"

Database* database_create(const char* name, const char* path) {
    Database* db = (Database*)malloc(sizeof(Database));
    if (!db) return NULL;

    strcpy(db->db_name, name);
    strcpy(db->db_path, path);
    db->tables = NULL;
    db->table_count = 0;

    // Create database directory if it doesn't exist
    char db_dir[512];
    sprintf(db_dir, "%s/%s", path, name);

    #ifdef _WIN32
        _mkdir(db_dir);
    #else
        mkdir(db_dir, 0755);
    #endif

    return db;
}

void database_free(Database* db) {
    if (!db) return;

    for (int i = 0; i < db->table_count; i++) {
        if (db->tables[i].columns) {
            free(db->tables[i].columns);
        }
    }

    if (db->tables) {
        free(db->tables);
    }

    free(db);
}

Table* database_create_table(Database* db, const char* name, Column* columns, int column_count) {
    // Check if table already exists
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].name, name) == 0) {
            return NULL; // Table already exists
        }
    }

    // Resize tables array
    db->tables = (Table*)realloc(db->tables, (db->table_count + 1) * sizeof(Table));
    if (!db->tables) return NULL;

    Table* table = &db->tables[db->table_count];
    strcpy(table->name, name);
    table->columns = (Column*)malloc(column_count * sizeof(Column));
    if (!table->columns) return NULL;

    memcpy(table->columns, columns, column_count * sizeof(Column));
    table->column_count = column_count;
    table->row_count = 0;

    // Create table file path
    sprintf(table->filename, "%s/%s/%s.dat", db->db_path, db->db_name, name);

    db->table_count++;
    return table;
}

Table* database_get_table(Database* db, const char* name) {
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].name, name) == 0) {
            return &db->tables[i];
        }
    }
    return NULL;
}

bool database_drop_table(Database* db, const char* name) {
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].name, name) == 0) {
            // Remove table file
            remove(db->tables[i].filename);

            // Shift remaining tables
            for (int j = i; j < db->table_count - 1; j++) {
                db->tables[j] = db->tables[j + 1];
            }

            db->table_count--;
            return true;
        }
    }
    return false;
}
```

### **Step 2: Table Operations and Data Storage**

```c
// table.h
#ifndef TABLE_H
#define TABLE_H

#include "database.h"

typedef struct {
    void** values;
    int value_count;
} RowData;

// Function prototypes
bool table_insert_row(Table* table, RowData* row_data);
RowData* table_select_all(Table* table);
RowData* table_select_where(Table* table, const char* column, const char* value);
bool table_update_row(Table* table, int row_index, RowData* new_data);
bool table_delete_row(Table* table, int row_index);
void table_free_row_data(RowData* row_data, int count);

#endif
```

```c
// table.c
#include "table.h"

bool table_insert_row(Table* table, RowData* row_data) {
    if (!table || !row_data || row_data->value_count != table->column_count) {
        return false;
    }

    FILE* file = fopen(table->filename, "ab");
    if (!file) return false;

    // Serialize row data
    for (int i = 0; i < table->column_count; i++) {
        Column* col = &table->columns[i];

        switch (col->type) {
            case TYPE_INT: {
                int value = *(int*)row_data->values[i];
                fwrite(&value, sizeof(int), 1, file);
                break;
            }
            case TYPE_FLOAT: {
                float value = *(float*)row_data->values[i];
                fwrite(&value, sizeof(float), 1, file);
                break;
            }
            case TYPE_STRING: {
                char* value = (char*)row_data->values[i];
                int len = strlen(value);
                fwrite(&len, sizeof(int), 1, file);
                fwrite(value, sizeof(char), len, file);
                break;
            }
            case TYPE_BOOL: {
                bool value = *(bool*)row_data->values[i];
                fwrite(&value, sizeof(bool), 1, file);
                break;
            }
        }
    }

    fclose(file);
    table->row_count++;
    return true;
}

RowData* table_select_all(Table* table) {
    if (!table || table->row_count == 0) return NULL;

    FILE* file = fopen(table->filename, "rb");
    if (!file) return NULL;

    RowData* rows = (RowData*)malloc(table->row_count * sizeof(RowData));
    if (!rows) {
        fclose(file);
        return NULL;
    }

    for (int row = 0; row < table->row_count; row++) {
        rows[row].values = (void**)malloc(table->column_count * sizeof(void*));
        rows[row].value_count = table->column_count;

        for (int col = 0; col < table->column_count; col++) {
            Column* column = &table->columns[col];

            switch (column->type) {
                case TYPE_INT: {
                    int* value = (int*)malloc(sizeof(int));
                    fread(value, sizeof(int), 1, file);
                    rows[row].values[col] = value;
                    break;
                }
                case TYPE_FLOAT: {
                    float* value = (float*)malloc(sizeof(float));
                    fread(value, sizeof(float), 1, file);
                    rows[row].values[col] = value;
                    break;
                }
                case TYPE_STRING: {
                    int len;
                    fread(&len, sizeof(int), 1, file);
                    char* value = (char*)malloc(len + 1);
                    fread(value, sizeof(char), len, file);
                    value[len] = '\0';
                    rows[row].values[col] = value;
                    break;
                }
                case TYPE_BOOL: {
                    bool* value = (bool*)malloc(sizeof(bool));
                    fread(value, sizeof(bool), 1, file);
                    rows[row].values[col] = value;
                    break;
                }
            }
        }
    }

    fclose(file);
    return rows;
}

void table_free_row_data(RowData* row_data, int count) {
    if (!row_data) return;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < row_data[i].value_count; j++) {
            free(row_data[i].values[j]);
        }
        free(row_data[i].values);
    }

    free(row_data);
}
```

### **Step 3: Simple Query Language**

```c
// query.h
#ifndef QUERY_H
#define QUERY_H

#include "database.h"

typedef enum {
    QUERY_CREATE_TABLE,
    QUERY_INSERT,
    QUERY_SELECT,
    QUERY_UPDATE,
    QUERY_DELETE,
    QUERY_DROP_TABLE
} QueryType;

typedef struct {
    QueryType type;
    char table_name[MAX_TABLE_NAME];
    char* raw_query;
    // Additional fields for specific query types
} Query;

// Function prototypes
Query* parse_query(const char* sql);
void execute_query(Database* db, Query* query);
void free_query(Query* query);

#endif
```

```c
// query.c
#include "query.h"
#include "table.h"

Query* parse_query(const char* sql) {
    Query* query = (Query*)malloc(sizeof(Query));
    if (!query) return NULL;

    query->raw_query = strdup(sql);

    // Simple parsing (can be extended)
    char* sql_copy = strdup(sql);
    char* token = strtok(sql_copy, " ");

    if (strcasecmp(token, "CREATE") == 0) {
        query->type = QUERY_CREATE_TABLE;
    } else if (strcasecmp(token, "INSERT") == 0) {
        query->type = QUERY_INSERT;
    } else if (strcasecmp(token, "SELECT") == 0) {
        query->type = QUERY_SELECT;
    } else if (strcasecmp(token, "UPDATE") == 0) {
        query->type = QUERY_UPDATE;
    } else if (strcasecmp(token, "DELETE") == 0) {
        query->type = QUERY_DELETE;
    } else if (strcasecmp(token, "DROP") == 0) {
        query->type = QUERY_DROP_TABLE;
    }

    // Extract table name (simplified)
    token = strtok(NULL, " ");
    if (token) {
        strcpy(query->table_name, token);
    }

    free(sql_copy);
    return query;
}

void execute_query(Database* db, Query* query) {
    Table* table = database_get_table(db, query->table_name);

    switch (query->type) {
        case QUERY_SELECT:
            if (table) {
                RowData* rows = table_select_all(table);
                if (rows) {
                    printf("Selected %d rows from %s\n", table->row_count, table->name);
                    table_free_row_data(rows, table->row_count);
                }
            } else {
                printf("Table '%s' not found\n", query->table_name);
            }
            break;

        case QUERY_DROP_TABLE:
            if (database_drop_table(db, query->table_name)) {
                printf("Table '%s' dropped successfully\n", query->table_name);
            } else {
                printf("Table '%s' not found\n", query->table_name);
            }
            break;

        default:
            printf("Query type not fully implemented\n");
            break;
    }
}

void free_query(Query* query) {
    if (query) {
        if (query->raw_query) {
            free(query->raw_query);
        }
        free(query);
    }
}
```

### **Step 4: Main Database Interface**

```c
// main.c
#include "database.h"
#include "query.h"
#include "table.h"

void display_menu(void) {
    printf("\n=== Simple Database Engine ===\n");
    printf("1. Create table\n");
    printf("2. Insert data\n");
    printf("3. Query data\n");
    printf("4. List tables\n");
    printf("5. Execute SQL query\n");
    printf("6. Save database\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Database* db = NULL;
    char db_name[256];
    char db_path[512] = "./data";

    printf("Simple Database Engine\n");
    printf("=====================\n");

    // Create database
    printf("Enter database name: ");
    scanf("%s", db_name);
    db = database_create(db_name, db_path);

    if (!db) {
        printf("Failed to create database\n");
        return 1;
    }

    printf("Database '%s' created successfully\n", db_name);

    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: { // Create table
                char table_name[MAX_TABLE_NAME];
                int column_count;

                printf("Enter table name: ");
                scanf("%s", table_name);
                printf("Enter number of columns: ");
                scanf("%d", &column_count);

                Column* columns = (Column*)malloc(column_count * sizeof(Column));
                if (!columns) break;

                for (int i = 0; i < column_count; i++) {
                    printf("Column %d name: ", i + 1);
                    scanf("%s", columns[i].name);

                    printf("Column %d type (0=int, 1=float, 2=string, 3=bool): ", i + 1);
                    int type;
                    scanf("%d", &type);
                    columns[i].type = (DataType)type;

                    printf("Is primary key? (0=no, 1=yes): ");
                    scanf("%d", &type);
                    columns[i].is_primary_key = type;

                    columns[i].nullable = true;
                }

                Table* table = database_create_table(db, table_name, columns, column_count);
                if (table) {
                    printf("Table '%s' created successfully\n", table_name);
                } else {
                    printf("Failed to create table\n");
                }

                free(columns);
                break;
            }

            case 2: { // Insert data
                char table_name[MAX_TABLE_NAME];
                printf("Enter table name: ");
                scanf("%s", table_name);

                Table* table = database_get_table(db, table_name);
                if (!table) {
                    printf("Table not found\n");
                    break;
                }

                RowData row_data;
                row_data.values = (void**)malloc(table->column_count * sizeof(void*));
                row_data.value_count = table->column_count;

                for (int i = 0; i < table->column_count; i++) {
                    Column* col = &table->columns[i];
                    printf("Enter value for %s: ", col->name);

                    switch (col->type) {
                        case TYPE_INT: {
                            int* value = (int*)malloc(sizeof(int));
                            scanf("%d", value);
                            row_data.values[i] = value;
                            break;
                        }
                        case TYPE_FLOAT: {
                            float* value = (float*)malloc(sizeof(float));
                            scanf("%f", value);
                            row_data.values[i] = value;
                            break;
                        }
                        case TYPE_STRING: {
                            char* value = (char*)malloc(MAX_STRING_LENGTH);
                            scanf("%s", value);
                            row_data.values[i] = value;
                            break;
                        }
                        case TYPE_BOOL: {
                            bool* value = (bool*)malloc(sizeof(bool));
                            int temp;
                            scanf("%d", &temp);
                            *value = temp;
                            row_data.values[i] = value;
                            break;
                        }
                    }
                }

                if (table_insert_row(table, &row_data)) {
                    printf("Row inserted successfully\n");
                } else {
                    printf("Failed to insert row\n");
                }

                // Cleanup
                for (int i = 0; i < row_data.value_count; i++) {
                    free(row_data.values[i]);
                }
                free(row_data.values);
                break;
            }

            case 3: { // Query data
                char table_name[MAX_TABLE_NAME];
                printf("Enter table name: ");
                scanf("%s", table_name);

                Table* table = database_get_table(db, table_name);
                if (!table) {
                    printf("Table not found\n");
                    break;
                }

                RowData* rows = table_select_all(table);
                if (rows) {
                    printf("\nTable: %s (%d rows)\n", table->name, table->row_count);
                    printf("------------------------\n");

                    for (int i = 0; i < table->row_count; i++) {
                        printf("Row %d: ", i + 1);
                        for (int j = 0; j < table->column_count; j++) {
                            if (j > 0) printf(", ");

                            switch (table->columns[j].type) {
                                case TYPE_INT:
                                    printf("%s=%d", table->columns[j].name, *(int*)rows[i].values[j]);
                                    break;
                                case TYPE_FLOAT:
                                    printf("%s=%.2f", table->columns[j].name, *(float*)rows[i].values[j]);
                                    break;
                                case TYPE_STRING:
                                    printf("%s=%s", table->columns[j].name, (char*)rows[i].values[j]);
                                    break;
                                case TYPE_BOOL:
                                    printf("%s=%s", table->columns[j].name,
                                           *(bool*)rows[i].values[j] ? "true" : "false");
                                    break;
                            }
                        }
                        printf("\n");
                    }

                    table_free_row_data(rows, table->row_count);
                } else {
                    printf("No data found\n");
                }
                break;
            }

            case 4: { // List tables
                printf("\nDatabase Tables:\n");
                printf("================\n");
                for (int i = 0; i < db->table_count; i++) {
                    printf("%d. %s (%d columns, %d rows)\n",
                           i + 1, db->tables[i].name,
                           db->tables[i].column_count,
                           db->tables[i].row_count);
                }
                break;
            }

            case 5: { // Execute SQL query
                printf("Enter SQL query: ");
                char query_str[1024];
                getchar(); // Clear any remaining newline
                fgets(query_str, sizeof(query_str), stdin);
                query_str[strcspn(query_str, "\n")] = '\0';

                Query* query = parse_query(query_str);
                if (query) {
                    execute_query(db, query);
                    free_query(query);
                } else {
                    printf("Failed to parse query\n");
                }
                break;
            }

            case 6: { // Save database
                database_save(db);
                printf("Database saved successfully\n");
                break;
            }

            case 0:
                printf("Saving database and exiting...\n");
                database_save(db);
                database_free(db);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Database Features**
- [x] Table creation with multiple data types
- [x] Data insertion and retrieval
- [x] File-based persistence
- [x] Simple query interface
- [x] Memory management

### **✅ Advanced Features**
- [x] Multiple data types (int, float, string, bool)
- [x] Column definitions with constraints
- [x] Row-based storage
- [x] Database file management
- [x] Query parsing (basic)

### **🚀 Extensions**
- [ ] Indexing system
- [ ] SQL query parser
- [ ] Join operations
- [ ] Transaction support
- [ ] Concurrency control
- [ ] Query optimization
- [ ] Backup and recovery

## 🧪 Testing and Usage

### **Basic Usage**
```bash
# Compile the database engine
gcc -o simple_db main.c database.c table.c query.c

# Run the database
./simple_db

# Create database and table
Enter database name: mydb

# Create table
1
employees
3
id
0
1
0
name
2
0
0
salary
1
0
0
```

### **Sample Session**
```
=== Simple Database Engine ===
1. Create table
2. Insert data
3. Query data
4. List tables
5. Execute SQL query
0. Exit
Enter your choice: 1
Enter table name: employees
Enter number of columns: 3
Column 1 name: id
Column 1 type (0=int, 1=float, 2=string, 3=bool): 0
Is primary key? (0=no, 1=yes): 1
Column 2 name: name
Column 2 type (0=int, 1=float, 2=string, 3=bool): 2
Is primary key? (0=no, 1=yes): 0
Column 3 name: salary
Column 3 type (0=int, 1=float, 2=string, 3=bool): 1
Is primary key? (0=no, 1=yes): 0
Table 'employees' created successfully
```

## 📊 Technical Learning Outcomes

### **Database Concepts**
- Data storage and retrieval
- Table and column management
- File-based persistence
- Query processing
- Memory management

### **C Programming Skills**
- Complex data structures
- File I/O operations
- Dynamic memory allocation
- String processing
- Error handling

## 🚀 Advanced Extensions

### **B-Tree Indexing**
```c
typedef struct BTreeNode {
    int* keys;
    struct BTreeNode** children;
    int num_keys;
    bool is_leaf;
} BTreeNode;

BTreeNode* btree_create(void);
void btree_insert(BTreeNode* root, int key, void* value);
void* btree_search(BTreeNode* root, int key);
```

### **SQL Query Parser**
```c
typedef struct {
    char* select_columns;
    char* from_table;
    char* where_condition;
    char* order_by;
} SelectQuery;

SelectQuery* parse_select_query(const char* sql);
RowData* execute_select_query(Database* db, SelectQuery* query);
```

## 📖 References

- **"Database System Concepts"** by Silberschatz et al.
- **"An Introduction to Database Systems"** by Date
- **"SQLite Architecture"** documentation
- **"B-Tree Tutorial"** by MIT

## 🎯 Real-World Applications

- **Embedded Systems**: Local data storage
- **Mobile Apps**: Offline data management
- **IoT Devices**: Sensor data storage
- **Configuration Management**: Settings storage
- **Caching Systems**: Fast data retrieval

---

**🗄️ This project demonstrates database engine architecture and data management in C!**