# 🔗 Hash Table Implementation
## Efficient key-value data structure with collision handling

---

## 📋 Project Overview

This project implements a complete hash table data structure in C with collision resolution using separate chaining. Hash tables provide average O(1) time complexity for insertions, deletions, and lookups, making them essential for efficient data storage and retrieval.

## 🎯 Learning Objectives

- Understand hash table data structure
- Learn hash function design
- Practice collision resolution techniques
- Implement dynamic memory management
- Learn load factor and rehashing

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries
- **Platform**: Cross-platform
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
hash_table/
├── src/
│   ├── main.c           # Main program with test cases
│   ├── hash_table.c     # Core hash table implementation
│   ├── hash_functions.c # Hash function implementations
│   └── linked_list.c    # Linked list for collision resolution
├── include/
│   ├── hash_table.h
│   ├── hash_functions.h
│   └── linked_list.h
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Hash Table Structure**

```c
// hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct HashNode {
    char* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** buckets;
    int capacity;
    int size;
    float load_factor;
} HashTable;

// Function prototypes
HashTable* create_hash_table(int capacity);
void free_hash_table(HashTable* table);
unsigned int hash_function(const char* key, int capacity);
void insert(HashTable* table, const char* key, void* value);
void* get(HashTable* table, const char* key);
bool remove_key(HashTable* table, const char* key);
bool contains_key(HashTable* table, const char* key);
void resize_table(HashTable* table);
void print_table(HashTable* table);

#endif
```

```c
// hash_table.c
#include "hash_table.h"

HashTable* create_hash_table(int capacity) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->capacity = capacity;
    table->size = 0;
    table->load_factor = 0.0f;

    table->buckets = (HashNode**)calloc(capacity, sizeof(HashNode*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    return table;
}

void free_hash_table(HashTable* table) {
    if (!table) return;

    for (int i = 0; i < table->capacity; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }

    free(table->buckets);
    free(table);
}

unsigned int hash_function(const char* key, int capacity) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31) + key[i];
    }
    return hash % capacity;
}

void insert(HashTable* table, const char* key, void* value) {
    // Check load factor and resize if necessary
    if ((float)(table->size + 1) / table->capacity > LOAD_FACTOR_THRESHOLD) {
        resize_table(table);
    }

    unsigned int index = hash_function(key, table->capacity);
    HashNode* current = table->buckets[index];

    // Check if key already exists
    while (current) {
        if (strcmp(current->key, key) == 0) {
            // Update existing value
            current->value = value;
            return;
        }
        current = current->next;
    }

    // Create new node
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (!new_node) return;

    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return;
    }

    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->size++;

    table->load_factor = (float)table->size / table->capacity;
}

void* get(HashTable* table, const char* key) {
    unsigned int index = hash_function(key, table->capacity);
    HashNode* current = table->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

bool remove_key(HashTable* table, const char* key) {
    unsigned int index = hash_function(key, table->capacity);
    HashNode* current = table->buckets[index];
    HashNode* prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }

            free(current->key);
            free(current);
            table->size--;
            table->load_factor = (float)table->size / table->capacity;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false;
}

bool contains_key(HashTable* table, const char* key) {
    return get(table, key) != NULL;
}

void resize_table(HashTable* table) {
    int new_capacity = table->capacity * 2;
    HashNode** new_buckets = (HashNode**)calloc(new_capacity, sizeof(HashNode*));

    if (!new_buckets) return;

    // Rehash all existing entries
    for (int i = 0; i < table->capacity; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;

            // Recompute hash for new capacity
            unsigned int new_index = hash_function(temp->key, new_capacity);

            // Insert into new bucket
            temp->next = new_buckets[new_index];
            new_buckets[new_index] = temp;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
    table->load_factor = (float)table->size / table->capacity;
}

void print_table(HashTable* table) {
    printf("Hash Table Contents (Capacity: %d, Size: %d, Load Factor: %.2f):\n",
           table->capacity, table->size, table->load_factor);

    for (int i = 0; i < table->capacity; i++) {
        if (table->buckets[i]) {
            printf("Bucket %d: ", i);
            HashNode* current = table->buckets[i];
            while (current) {
                printf("(%s, %p) -> ", current->key, current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}
```

### **Step 2: Main Program with Test Cases**

```c
// main.c
#include "hash_table.h"
#include <time.h>

void test_basic_operations() {
    printf("=== Basic Operations Test ===\n");

    HashTable* table = create_hash_table(INITIAL_CAPACITY);

    // Insert some key-value pairs
    insert(table, "apple", (void*)1);
    insert(table, "banana", (void*)2);
    insert(table, "cherry", (void*)3);

    printf("Inserted 3 items\n");
    print_table(table);

    // Test retrieval
    void* value = get(table, "banana");
    if (value) {
        printf("Retrieved banana: %ld\n", (long)value);
    }

    // Test update
    insert(table, "banana", (void*)20);
    value = get(table, "banana");
    printf("Updated banana: %ld\n", (long)value);

    // Test deletion
    remove_key(table, "cherry");
    printf("Deleted cherry\n");
    print_table(table);

    free_hash_table(table);
}

void test_collision_handling() {
    printf("\n=== Collision Handling Test ===\n");

    HashTable* table = create_hash_table(4); // Small capacity to force collisions

    // Insert items that will collide
    insert(table, "abc", (void*)1);
    insert(table, "def", (void*)2);
    insert(table, "ghi", (void*)3);
    insert(table, "jkl", (void*)4);

    print_table(table);
    free_hash_table(table);
}

void test_resize() {
    printf("\n=== Resize Test ===\n");

    HashTable* table = create_hash_table(4);

    // Insert many items to trigger resize
    for (int i = 0; i < 20; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        insert(table, key, (void*)(long)i);
    }

    printf("After inserting 20 items:\n");
    print_table(table);
    free_hash_table(table);
}

void performance_test() {
    printf("\n=== Performance Test ===\n");

    HashTable* table = create_hash_table(INITIAL_CAPACITY);
    const int num_operations = 10000;

    // Insert performance
    clock_t start = clock();
    for (int i = 0; i < num_operations; i++) {
        char key[20];
        sprintf(key, "perf_key_%d", i);
        insert(table, key, (void*)(long)i);
    }
    clock_t end = clock();

    printf("Inserted %d items in %.2f seconds\n",
           num_operations, (double)(end - start) / CLOCKS_PER_SEC);

    // Lookup performance
    start = clock();
    for (int i = 0; i < num_operations; i++) {
        char key[20];
        sprintf(key, "perf_key_%d", i);
        get(table, key);
    }
    end = clock();

    printf("Looked up %d items in %.2f seconds\n",
           num_operations, (double)(end - start) / CLOCKS_PER_SEC);

    free_hash_table(table);
}

int main() {
    printf("Hash Table Implementation in C\n");
    printf("==============================\n");

    test_basic_operations();
    test_collision_handling();
    test_resize();
    performance_test();

    printf("\nAll tests completed!\n");
    return 0;
}
```

## 🎯 Key Features

### **✅ Core Hash Table Operations**
- [x] Insert key-value pairs
- [x] Retrieve values by key
- [x] Delete key-value pairs
- [x] Check key existence
- [x] Dynamic resizing

### **✅ Advanced Features**
- [x] Collision resolution (separate chaining)
- [x] Load factor monitoring
- [x] Automatic rehashing
- [x] Memory management
- [x] Performance testing

### **🚀 Extensions**
- [ ] Linear probing collision resolution
- [ ] Quadratic probing
- [ ] Double hashing
- [ ] Concurrent hash table
- [ ] Persistent storage
- [ ] Generic value types

## 🧪 Testing and Usage

### **Basic Usage Example**
```c
HashTable* table = create_hash_table(16);

// Insert values
insert(table, "name", "John");
insert(table, "age", (void*)25);
insert(table, "salary", (void*)50000);

// Retrieve values
char* name = (char*)get(table, "name");
int age = (int)(long)get(table, "age");

// Check existence
if (contains_key(table, "name")) {
    printf("Name exists in table\n");
}

// Remove entry
remove_key(table, "age");

free_hash_table(table);
```

### **Performance Characteristics**
- **Average Case**: O(1) for insert, delete, lookup
- **Worst Case**: O(n) when many collisions occur
- **Space Complexity**: O(n) for storage
- **Load Factor**: Automatically managed with resizing

## 📊 Technical Learning Outcomes

### **Algorithm Concepts**
- Hash function design
- Collision resolution strategies
- Load factor management
- Dynamic array resizing
- Time complexity analysis

### **C Programming Skills**
- Pointer manipulation
- Dynamic memory allocation
- String handling
- Struct usage
- Function pointers

## 🚀 Advanced Extensions

### **Different Hash Functions**
```c
// djb2 hash function
unsigned long djb2_hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// FNV-1a hash function
unsigned long fnv1a_hash(const char* str) {
    unsigned long hash = 14695981039346656037UL;
    for (char c = *str; c != '\0'; c = *++str) {
        hash ^= c;
        hash *= 1099511628211UL;
    }
    return hash;
}
```

### **Linear Probing Implementation**
```c
typedef struct {
    char** keys;
    void** values;
    bool* occupied;
    int capacity;
    int size;
} LinearProbingHashTable;

void insert_linear_probing(LinearProbingHashTable* table, const char* key, void* value) {
    unsigned int index = hash_function(key, table->capacity);

    while (table->occupied[index]) {
        if (strcmp(table->keys[index], key) == 0) {
            // Update existing
            table->values[index] = value;
            return;
        }
        index = (index + 1) % table->capacity;
    }

    // Insert new
    table->keys[index] = strdup(key);
    table->values[index] = value;
    table->occupied[index] = true;
    table->size++;
}
```

## 📖 References

- **Introduction to Algorithms** by Cormen et al.
- **Hash Table Performance** - MIT OpenCourseWare
- **Collision Resolution Techniques** - Stanford CS Library
- **Hash Function Design** - NIST Guidelines

## 🎯 Real-World Applications

- **Database Indexing**: Fast data retrieval
- **Caching Systems**: LRU cache implementation
- **Symbol Tables**: Compiler design
- **Associative Arrays**: Programming language implementations
- **Network Routing**: IP routing tables

---

**🔗 This project demonstrates efficient data storage and retrieval using hash table data structures in C!**