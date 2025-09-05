# 🗄️ Advanced C: Database Integration & Data Persistence

## Building Data-Driven Applications with SQLite

---

## 🎯 Learning Objectives

- Master SQLite database integration in C
- Understand SQL query execution and result processing
- Learn database schema design and migration
- Implement ORM-like patterns in C
- Master transaction management and error handling
- Build data persistence layers for applications

---

## 📖 Database Integration Fundamentals

**Database integration** involves connecting C applications to databases for persistent data storage and retrieval. SQLite is an excellent choice for C applications due to its simplicity, zero-configuration nature, and self-contained design.

### **Key Concepts:**
- SQLite C API usage
- SQL query preparation and execution
- Result set processing
- Transaction management
- Database schema design
- Data migration strategies

---

## 🗃️ SQLite Integration

### **1. Basic SQLite Operations**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DB_NAME "example.db"

// Callback function for SELECT queries
static int callback(void* data, int argc, char** argv, char** col_names) {
    (void)data;  // Suppress unused parameter warning

    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", col_names[i], argv[i] ? argv[i] : "NULL");
    }
    printf("---\n");

    return 0;
}

int main() {
    sqlite3* db;
    char* err_msg = NULL;
    int rc;

    // Open database
    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Database opened successfully\n");

    // Create table
    const char* create_table_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "email TEXT UNIQUE,"
        "age INTEGER,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    printf("Table created successfully\n");

    // Insert data
    const char* insert_sql =
        "INSERT INTO users (name, email, age) VALUES "
        "('John Doe', 'john@example.com', 25),"
        "('Jane Smith', 'jane@example.com', 30),"
        "('Bob Johnson', 'bob@example.com', 35);";

    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    printf("Data inserted successfully\n");

    // Query data
    const char* select_sql = "SELECT * FROM users;";

    rc = sqlite3_exec(db, select_sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Close database
    sqlite3_close(db);
    printf("Database closed\n");

    return 0;
}
```

### **2. Prepared Statements**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DB_NAME "prepared.db"

typedef struct {
    int id;
    char name[100];
    char email[100];
    int age;
} User;

int main() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    // Open database
    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table
    const char* create_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "email TEXT UNIQUE,"
        "age INTEGER"
        ");";

    rc = sqlite3_exec(db, create_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Create table error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Prepare INSERT statement
    const char* insert_sql = "INSERT INTO users (name, email, age) VALUES (?, ?, ?);";

    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Prepare error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Sample data
    User users[] = {
        {0, "Alice Johnson", "alice@example.com", 28},
        {0, "Charlie Brown", "charlie@example.com", 32},
        {0, "Diana Prince", "diana@example.com", 26}
    };

    // Insert data using prepared statement
    for (int i = 0; i < 3; i++) {
        sqlite3_bind_text(stmt, 1, users[i].name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, users[i].email, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, users[i].age);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Insert error: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Inserted user: %s\n", users[i].name);
        }

        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);
    }

    sqlite3_finalize(stmt);

    // Prepare SELECT statement
    const char* select_sql = "SELECT id, name, email, age FROM users WHERE age > ?;";

    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Prepare select error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Bind parameter
    sqlite3_bind_int(stmt, 1, 25);

    // Execute query
    printf("\nUsers older than 25:\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = (const char*)sqlite3_column_text(stmt, 1);
        const char* email = (const char*)sqlite3_column_text(stmt, 2);
        int age = sqlite3_column_int(stmt, 3);

        printf("ID: %d, Name: %s, Email: %s, Age: %d\n", id, name, email, age);
    }

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Query error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
```

### **3. Transaction Management**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DB_NAME "transactions.db"

int execute_transaction(sqlite3* db, const char* sql) {
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Prepare error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc;
}

int begin_transaction(sqlite3* db) {
    return execute_transaction(db, "BEGIN TRANSACTION;");
}

int commit_transaction(sqlite3* db) {
    return execute_transaction(db, "COMMIT;");
}

int rollback_transaction(sqlite3* db) {
    return execute_transaction(db, "ROLLBACK;");
}

int main() {
    sqlite3* db;
    int rc;

    // Open database
    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create accounts table
    const char* create_sql =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "id INTEGER PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "balance REAL DEFAULT 0.0"
        ");";

    rc = sqlite3_exec(db, create_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Create table error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Insert initial data
    sqlite3_exec(db, "INSERT OR REPLACE INTO accounts VALUES (1, 'Alice', 1000.0);", 0, 0, 0);
    sqlite3_exec(db, "INSERT OR REPLACE INTO accounts VALUES (2, 'Bob', 500.0);", 0, 0, 0);

    printf("Initial balances:\n");
    sqlite3_exec(db, "SELECT * FROM accounts;", 0, 0, 0);

    // Perform transaction: Transfer money from Alice to Bob
    printf("\nPerforming transaction: Alice -> Bob ($200)\n");

    if (begin_transaction(db) != SQLITE_OK) {
        fprintf(stderr, "Failed to begin transaction\n");
        sqlite3_close(db);
        return 1;
    }

    // Check Alice's balance
    sqlite3_stmt* stmt;
    const char* check_sql = "SELECT balance FROM accounts WHERE id = 1;";

    rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Prepare error: %s\n", sqlite3_errmsg(db));
        rollback_transaction(db);
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "No data found\n");
        sqlite3_finalize(stmt);
        rollback_transaction(db);
        sqlite3_close(db);
        return 1;
    }

    double alice_balance = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);

    if (alice_balance < 200.0) {
        printf("Insufficient funds! Rolling back transaction.\n");
        rollback_transaction(db);
    } else {
        // Perform transfer
        const char* debit_sql = "UPDATE accounts SET balance = balance - 200.0 WHERE id = 1;";
        const char* credit_sql = "UPDATE accounts SET balance = balance + 200.0 WHERE id = 2;";

        if (execute_transaction(db, debit_sql) == SQLITE_OK &&
            execute_transaction(db, credit_sql) == SQLITE_OK) {

            if (commit_transaction(db) == SQLITE_OK) {
                printf("Transaction completed successfully!\n");
            } else {
                fprintf(stderr, "Commit failed\n");
            }
        } else {
            fprintf(stderr, "Transaction failed, rolling back\n");
            rollback_transaction(db);
        }
    }

    printf("\nFinal balances:\n");
    sqlite3_exec(db, "SELECT * FROM accounts;", 0, 0, 0);

    sqlite3_close(db);
    return 0;
}
```

---

## 🏗️ ORM-like Patterns in C

### **1. Simple ORM Implementation**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_SIZE 1024

typedef struct {
    int id;
    char name[100];
    char email[100];
    int age;
} User;

typedef struct {
    sqlite3* db;
    char table_name[50];
} Database;

// Database operations
Database* db_open(const char* db_name) {
    Database* db = calloc(1, sizeof(Database));
    if (!db) return NULL;

    if (sqlite3_open(db_name, &db->db) != SQLITE_OK) {
        free(db);
        return NULL;
    }

    strcpy(db->table_name, "users");
    return db;
}

void db_close(Database* db) {
    if (db) {
        sqlite3_close(db->db);
        free(db);
    }
}

// CRUD Operations
int user_create(Database* db, User* user) {
    char sql[MAX_QUERY_SIZE];
    sqlite3_stmt* stmt;

    snprintf(sql, sizeof(sql),
             "INSERT INTO %s (name, email, age) VALUES (?, ?, ?);",
             db->table_name);

    if (sqlite3_prepare_v2(db->db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, user->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user->email, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, user->age);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result == SQLITE_DONE) {
        user->id = sqlite3_last_insert_rowid(db->db);
        return 0;
    }

    return -1;
}

int user_read(Database* db, int id, User* user) {
    char sql[MAX_QUERY_SIZE];
    sqlite3_stmt* stmt;

    snprintf(sql, sizeof(sql),
             "SELECT id, name, email, age FROM %s WHERE id = ?;",
             db->table_name);

    if (sqlite3_prepare_v2(db->db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_int(stmt, 1, id);

    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        user->id = sqlite3_column_int(stmt, 0);
        strcpy(user->name, (const char*)sqlite3_column_text(stmt, 1));
        strcpy(user->email, (const char*)sqlite3_column_text(stmt, 2));
        user->age = sqlite3_column_int(stmt, 3);

        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    return -1;
}

int user_update(Database* db, User* user) {
    char sql[MAX_QUERY_SIZE];
    sqlite3_stmt* stmt;

    snprintf(sql, sizeof(sql),
             "UPDATE %s SET name = ?, email = ?, age = ? WHERE id = ?;",
             db->table_name);

    if (sqlite3_prepare_v2(db->db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, user->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user->email, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, user->age);
    sqlite3_bind_int(stmt, 4, user->id);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (result == SQLITE_DONE) ? 0 : -1;
}

int user_delete(Database* db, int id) {
    char sql[MAX_QUERY_SIZE];
    sqlite3_stmt* stmt;

    snprintf(sql, sizeof(sql), "DELETE FROM %s WHERE id = ?;", db->table_name);

    if (sqlite3_prepare_v2(db->db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_int(stmt, 1, id);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (result == SQLITE_DONE) ? 0 : -1;
}

// Collection operations
typedef struct {
    User* users;
    int count;
    int capacity;
} UserCollection;

UserCollection* user_find_all(Database* db) {
    char sql[MAX_QUERY_SIZE];
    sqlite3_stmt* stmt;

    snprintf(sql, sizeof(sql), "SELECT id, name, email, age FROM %s;", db->table_name);

    if (sqlite3_prepare_v2(db->db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return NULL;
    }

    UserCollection* collection = calloc(1, sizeof(UserCollection));
    if (!collection) {
        sqlite3_finalize(stmt);
        return NULL;
    }

    collection->capacity = 10;
    collection->users = malloc(sizeof(User) * collection->capacity);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (collection->count >= collection->capacity) {
            collection->capacity *= 2;
            collection->users = realloc(collection->users,
                                      sizeof(User) * collection->capacity);
        }

        User* user = &collection->users[collection->count++];
        user->id = sqlite3_column_int(stmt, 0);
        strcpy(user->name, (const char*)sqlite3_column_text(stmt, 1));
        strcpy(user->email, (const char*)sqlite3_column_text(stmt, 2));
        user->age = sqlite3_column_int(stmt, 3);
    }

    sqlite3_finalize(stmt);
    return collection;
}

void user_collection_free(UserCollection* collection) {
    if (collection) {
        free(collection->users);
        free(collection);
    }
}

int main() {
    // Initialize database
    Database* db = db_open("orm_example.db");
    if (!db) {
        fprintf(stderr, "Failed to open database\n");
        return 1;
    }

    // Create table
    const char* create_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "email TEXT UNIQUE,"
        "age INTEGER"
        ");";

    if (sqlite3_exec(db->db, create_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Create table error: %s\n", sqlite3_errmsg(db->db));
        db_close(db);
        return 1;
    }

    // Create user
    User new_user = {0, "John Doe", "john@example.com", 30};
    if (user_create(db, &new_user) == 0) {
        printf("Created user with ID: %d\n", new_user.id);
    }

    // Read user
    User read_user;
    if (user_read(db, new_user.id, &read_user) == 0) {
        printf("Read user: %s (%s, %d years old)\n",
               read_user.name, read_user.email, read_user.age);
    }

    // Update user
    strcpy(read_user.name, "John Smith");
    if (user_update(db, &read_user) == 0) {
        printf("Updated user name to: %s\n", read_user.name);
    }

    // Find all users
    UserCollection* users = user_find_all(db);
    if (users) {
        printf("Found %d users:\n", users->count);
        for (int i = 0; i < users->count; i++) {
            printf("  %d: %s\n", users->users[i].id, users->users[i].name);
        }
        user_collection_free(users);
    }

    // Delete user
    if (user_delete(db, new_user.id) == 0) {
        printf("Deleted user with ID: %d\n", new_user.id);
    }

    db_close(db);
    return 0;
}
```

---

## 🔄 Database Schema and Migrations

### **1. Schema Management**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DB_VERSION 2

typedef struct {
    int version;
    const char* description;
    const char* sql;
} Migration;

Migration migrations[] = {
    {1, "Create users table",
     "CREATE TABLE users ("
     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
     "name TEXT NOT NULL,"
     "email TEXT UNIQUE,"
     "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
     ");"},

    {2, "Add age column",
     "ALTER TABLE users ADD COLUMN age INTEGER DEFAULT 0;"}
};

int get_current_version(sqlite3* db) {
    sqlite3_stmt* stmt;
    int version = 0;

    const char* sql = "SELECT version FROM schema_version LIMIT 1;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            version = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return version;
}

int set_current_version(sqlite3* db, int version) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "INSERT OR REPLACE INTO schema_version (id, version) VALUES (1, %d);",
             version);

    return sqlite3_exec(db, sql, 0, 0, 0);
}

int run_migration(sqlite3* db, Migration* migration) {
    char* err_msg = NULL;
    int rc;

    printf("Running migration %d: %s\n", migration->version, migration->description);

    rc = sqlite3_exec(db, migration->sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Migration failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        return rc;
    }

    return set_current_version(db, migration->version);
}

int migrate_database(sqlite3* db) {
    int current_version = get_current_version(db);

    printf("Current database version: %d\n", current_version);
    printf("Target version: %d\n", DB_VERSION);

    // Create schema_version table if it doesn't exist
    const char* create_version_sql =
        "CREATE TABLE IF NOT EXISTS schema_version ("
        "id INTEGER PRIMARY KEY,"
        "version INTEGER NOT NULL"
        ");";

    if (sqlite3_exec(db, create_version_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to create schema_version table\n");
        return SQLITE_ERROR;
    }

    // Run migrations
    for (size_t i = 0; i < sizeof(migrations) / sizeof(migrations[0]); i++) {
        if (migrations[i].version > current_version) {
            if (run_migration(db, &migrations[i]) != SQLITE_OK) {
                fprintf(stderr, "Migration %d failed\n", migrations[i].version);
                return SQLITE_ERROR;
            }
        }
    }

    printf("Database migration completed successfully\n");
    return SQLITE_OK;
}

int main() {
    sqlite3* db;
    int rc;

    rc = sqlite3_open("migrated.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (migrate_database(db) != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }

    // Test the migrated schema
    const char* test_sql = "INSERT INTO users (name, email, age) VALUES ('Test User', 'test@example.com', 25);";

    rc = sqlite3_exec(db, test_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert test failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Insert test successful\n");
    }

    sqlite3_close(db);
    return 0;
}
```

---

## 🔒 Database Security and Best Practices

### **1. SQL Injection Prevention**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

// UNSAFE: Vulnerable to SQL injection
void unsafe_query(sqlite3* db, const char* user_input) {
    char sql[256];
    sprintf(sql, "SELECT * FROM users WHERE name = '%s';", user_input);

    // This is dangerous if user_input contains SQL
    sqlite3_exec(db, sql, 0, 0, 0);
}

// SAFE: Using prepared statements
void safe_query(sqlite3* db, const char* user_input) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM users WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, user_input, -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Process results safely
            printf("User: %s\n", sqlite3_column_text(stmt, 1));
        }

        sqlite3_finalize(stmt);
    }
}

// Input validation
int validate_user_input(const char* input) {
    if (!input || strlen(input) == 0 || strlen(input) > 100) {
        return 0;  // Invalid
    }

    // Check for potentially dangerous characters
    const char* dangerous_chars = ";'\"\\";
    for (const char* p = input; *p; p++) {
        if (strchr(dangerous_chars, *p)) {
            return 0;  // Potentially dangerous
        }
    }

    return 1;  // Valid
}
```

### **2. Connection Pooling**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <pthread.h>

#define MAX_CONNECTIONS 5

typedef struct {
    sqlite3* db;
    int in_use;
} DBConnection;

typedef struct {
    DBConnection connections[MAX_CONNECTIONS];
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    const char* db_name;
} ConnectionPool;

ConnectionPool* create_connection_pool(const char* db_name) {
    ConnectionPool* pool = calloc(1, sizeof(ConnectionPool));
    if (!pool) return NULL;

    pool->db_name = db_name;
    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);

    return pool;
}

sqlite3* get_connection(ConnectionPool* pool) {
    pthread_mutex_lock(&pool->mutex);

    // Find available connection
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (!pool->connections[i].in_use) {
            if (pool->connections[i].db == NULL) {
                // Create new connection
                if (sqlite3_open(pool->db_name, &pool->connections[i].db) != SQLITE_OK) {
                    pthread_mutex_unlock(&pool->mutex);
                    return NULL;
                }
            }

            pool->connections[i].in_use = 1;
            pthread_mutex_unlock(&pool->mutex);
            return pool->connections[i].db;
        }
    }

    // No available connections, wait
    while (1) {
        pthread_cond_wait(&pool->cond, &pool->mutex);

        for (int i = 0; i < MAX_CONNECTIONS; i++) {
            if (!pool->connections[i].in_use) {
                pool->connections[i].in_use = 1;
                pthread_mutex_unlock(&pool->mutex);
                return pool->connections[i].db;
            }
        }
    }
}

void release_connection(ConnectionPool* pool, sqlite3* db) {
    pthread_mutex_lock(&pool->mutex);

    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (pool->connections[i].db == db) {
            pool->connections[i].in_use = 0;
            pthread_cond_signal(&pool->cond);
            break;
        }
    }

    pthread_mutex_unlock(&pool->mutex);
}

void destroy_connection_pool(ConnectionPool* pool) {
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (pool->connections[i].db) {
            sqlite3_close(pool->connections[i].db);
        }
    }

    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);
    free(pool);
}
```

---

## 🎯 Best Practices for Database Integration

### **1. Error Handling**
```c
typedef enum {
    DB_SUCCESS = 0,
    DB_ERROR_CONNECTION = 1,
    DB_ERROR_QUERY = 2,
    DB_ERROR_NO_DATA = 3,
    DB_ERROR_CONSTRAINT = 4
} DBError;

typedef struct {
    DBError code;
    char message[256];
} DBResult;

DBResult db_execute_query(sqlite3* db, const char* sql) {
    DBResult result = {DB_SUCCESS, ""};

    char* err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        result.code = DB_ERROR_QUERY;
        strncpy(result.message, err_msg, sizeof(result.message) - 1);
        sqlite3_free(err_msg);
    }

    return result;
}
```

### **2. Resource Management**
```c
// RAII-like database connection
typedef struct {
    sqlite3* db;
    int valid;
} DBConnection;

DBConnection* db_connect(const char* db_name) {
    DBConnection* conn = calloc(1, sizeof(DBConnection));
    if (!conn) return NULL;

    if (sqlite3_open(db_name, &conn->db) == SQLITE_OK) {
        conn->valid = 1;
    } else {
        free(conn);
        return NULL;
    }

    return conn;
}

void db_disconnect(DBConnection* conn) {
    if (conn) {
        if (conn->db) {
            sqlite3_close(conn->db);
        }
        free(conn);
    }
}

// Smart pointer-like prepared statement
typedef struct {
    sqlite3_stmt* stmt;
} PreparedStatement;

PreparedStatement* prepare_statement(sqlite3* db, const char* sql) {
    PreparedStatement* ps = calloc(1, sizeof(PreparedStatement));
    if (!ps) return NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &ps->stmt, 0) != SQLITE_OK) {
        free(ps);
        return NULL;
    }

    return ps;
}

void finalize_statement(PreparedStatement* ps) {
    if (ps) {
        if (ps->stmt) {
            sqlite3_finalize(ps->stmt);
        }
        free(ps);
    }
}
```

### **3. Performance Optimization**
```c
// Optimize database for performance
void optimize_database(sqlite3* db) {
    const char* pragmas[] = {
        "PRAGMA synchronous = NORMAL;",
        "PRAGMA journal_mode = WAL;",
        "PRAGMA cache_size = 10000;",
        "PRAGMA temp_store = memory;",
        "PRAGMA mmap_size = 268435456;",  // 256MB
        NULL
    };

    for (int i = 0; pragmas[i]; i++) {
        sqlite3_exec(db, pragmas[i], 0, 0, 0);
    }
}

// Batch operations
void batch_insert(sqlite3* db, User* users, int count) {
    sqlite3_exec(db, "BEGIN TRANSACTION;", 0, 0, 0);

    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO users (name, email, age) VALUES (?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    for (int i = 0; i < count; i++) {
        sqlite3_bind_text(stmt, 1, users[i].name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, users[i].email, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, users[i].age);

        sqlite3_step(stmt);
        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", 0, 0, 0);
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic Database Operations**
- Create a library management system with books and borrowers
- Implement CRUD operations for a product catalog
- Build a simple blog system with posts and comments

### **Exercise 2: Advanced Queries**
- Implement complex joins and aggregations
- Create database views and triggers
- Build a reporting system with analytics

### **Exercise 3: Performance Optimization**
- Optimize database queries and indexes
- Implement database connection pooling
- Create a caching layer for frequently accessed data

### **Exercise 4: Security and Best Practices**
- Implement user authentication and authorization
- Add input validation and SQL injection prevention
- Create database backup and recovery procedures

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What does SQLite stand for?
a) Structured Query Language Interface for Tables
b) Simple Query Language for Tables
c) No official expansion, it's just SQLite
d) Structured Query Language Lite

### **Question 2:**
Which function is used to prepare SQL statements in SQLite?
a) sqlite3_exec()
b) sqlite3_prepare_v2()
c) sqlite3_step()
d) sqlite3_bind()

### **Question 3:**
What is the purpose of transactions in databases?
a) To speed up queries
b) To ensure data consistency
c) To compress data
d) To create backups

### **Question 4:**
Which pragma is used to enable WAL mode in SQLite?
a) PRAGMA wal_mode = ON;
b) PRAGMA journal_mode = WAL;
c) PRAGMA synchronous = WAL;
d) PRAGMA cache_mode = WAL;

### **Question 5:**
What is SQL injection?
a) A type of database index
b) A security vulnerability
c) A database optimization technique
d) A transaction isolation level

---

## 🔗 Additional Resources

### **Database Integration**
- [SQLite Documentation](https://www.sqlite.org/docs.html)
- [SQLite C API Reference](https://www.sqlite.org/capi3ref.html)
- [Using SQLite in C](https://www.sqlite.org/cintro.html)

### **Further Reading**
- [Database System Concepts](https://www.amazon.com/Database-System-Concepts-Abraham-Silberschatz/dp/0073523321)
- [SQL Performance Explained](https://www.amazon.com/SQL-Performance-Explained-Markus-Winand/dp/3950307826)
- [Designing Data-Intensive Applications](https://www.amazon.com/Designing-Data-Intensive-Applications-Reliable-Maintainable/dp/1449373321)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ SQLite database integration
- ✅ Prepared statements and transactions
- ✅ ORM-like patterns in C
- ✅ Database schema management
- ✅ Security and performance optimization
- ✅ Connection pooling and resource management

**Next Lesson Preview:**
- Web API development with CGI/FastCGI
- RESTful service implementation
- JSON handling and serialization
- HTTP request/response processing
- API authentication and security

---

**🚀 Ready to build web APIs?**

[⬅️ Previous: Multi-threading](03_Multi_threading.md) | [Next: Web API Development](05_Web_API_Development.md)