# 🔗 **Project 16: Hash Table Implementation in C**
## 🎯 **Complete Hash Table with Collision Resolution**

---

## 📋 **Project Overview**

**English:** A complete hash table implementation in C featuring collision resolution using chaining, dynamic resizing, and comprehensive operations for key-value data storage and retrieval.

**Hinglish:** Ek complete hash table implementation jo C mein hai, jisme collision resolution using chaining, dynamic resizing, aur comprehensive operations for key-value data storage aur retrieval included hai.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Hash function design
- Collision resolution strategies
- Dynamic memory management
- Data structure implementation
- Performance optimization

✅ **Algorithm Concepts:**
- Hash table operations
- Load factor management
- Rehashing algorithms
- Time complexity analysis
- Memory efficiency

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Core data structure | Handles memory and algorithms |
| **Dynamic Memory** | Flexible storage | Linked list nodes and table resizing |
| **Hash Functions** | Key distribution | DJB2 hash algorithm implementation |
| **Standard Library** | String operations | Key comparison and manipulation |

---

## 📁 **Project Structure**

```
HashTable/
├── include/
│   ├── hashtable.h
│   ├── hashnode.h
│   ├── hashfunctions.h
├── src/
│   ├── hashtable.c
│   ├── hashnode.c
│   ├── hashfunctions.c
│   └── main.c
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Hash Node Structure**

```c
// hashnode.h
#ifndef HASHNODE_H
#define HASHNODE_H

#define MAX_KEY_LENGTH 100
#define MAX_VALUE_LENGTH 500

typedef struct HashNode {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
    struct HashNode *next;
} HashNode;

// Node functions
HashNode* create_node(const char *key, const char *value);
void free_node(HashNode *node);
void print_node(HashNode *node);

#endif
```

```c
// hashnode.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashnode.h"

// Create new hash node
HashNode* create_node(const char *key, const char *value) {
    HashNode *node = (HashNode*)malloc(sizeof(HashNode));
    if (!node) return NULL;

    strcpy(node->key, key);
    strcpy(node->value, value);
    node->next = NULL;

    return node;
}

// Free node memory
void free_node(HashNode *node) {
    if (node) {
        free(node);
    }
}

// Print node information
void print_node(HashNode *node) {
    if (node) {
        printf("Key: %s, Value: %s\n", node->key, node->value);
    }
}
```

### **2. Hash Functions**

```c
// hashfunctions.h
#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H

// Hash function declarations
unsigned long djb2_hash(const char *str);
unsigned long sdbm_hash(const char *str);
unsigned long hash_function(const char *key, int table_size);

#endif
```

```c
// hashfunctions.c
#include <stdio.h>
#include <stdlib.h>
#include "hashfunctions.h"

// DJB2 hash function
unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

// SDBM hash function
unsigned long sdbm_hash(const char *str) {
    unsigned long hash = 0;
    int c;

    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

// Main hash function with table size
unsigned long hash_function(const char *key, int table_size) {
    unsigned long hash = djb2_hash(key);
    return hash % table_size;
}
```

### **3. Hash Table Implementation**

```c
// hashtable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "hashnode.h"

#define INITIAL_SIZE 16
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct {
    HashNode **table;
    int size;
    int count;
    double load_factor;
} HashTable;

// Hash table functions
HashTable* create_hashtable(int initial_size);
void free_hashtable(HashTable *ht);
int insert(HashTable *ht, const char *key, const char *value);
char* search(HashTable *ht, const char *key);
int delete(HashTable *ht, const char *key);
void resize_table(HashTable *ht);
void print_table(HashTable *ht);
double get_load_factor(HashTable *ht);

#endif
```

```c
// hashtable.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hashfunctions.h"

// Create hash table
HashTable* create_hashtable(int initial_size) {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->size = initial_size;
    ht->count = 0;
    ht->load_factor = 0.0;

    ht->table = (HashNode**)malloc(sizeof(HashNode*) * initial_size);
    if (!ht->table) {
        free(ht);
        return NULL;
    }

    // Initialize all buckets to NULL
    for (int i = 0; i < initial_size; i++) {
        ht->table[i] = NULL;
    }

    return ht;
}

// Free hash table
void free_hashtable(HashTable *ht) {
    if (!ht) return;

    for (int i = 0; i < ht->size; i++) {
        HashNode *current = ht->table[i];
        while (current) {
            HashNode *temp = current;
            current = current->next;
            free_node(temp);
        }
    }

    free(ht->table);
    free(ht);
}

// Insert key-value pair
int insert(HashTable *ht, const char *key, const char *value) {
    if (!ht || !key || !value) return 0;

    // Check load factor and resize if needed
    if (get_load_factor(ht) >= LOAD_FACTOR_THRESHOLD) {
        resize_table(ht);
    }

    unsigned long index = hash_function(key, ht->size);

    // Check if key already exists
    HashNode *current = ht->table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            // Update existing value
            strcpy(current->value, value);
            return 1;
        }
        current = current->next;
    }

    // Create new node
    HashNode *new_node = create_node(key, value);
    if (!new_node) return 0;

    // Insert at beginning of chain
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
    ht->count++;

    return 1;
}

// Search for value by key
char* search(HashTable *ht, const char *key) {
    if (!ht || !key) return NULL;

    unsigned long index = hash_function(key, ht->size);
    HashNode *current = ht->table[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

// Delete key-value pair
int delete(HashTable *ht, const char *key) {
    if (!ht || !key) return 0;

    unsigned long index = hash_function(key, ht->size);
    HashNode *current = ht->table[index];
    HashNode *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht->table[index] = current->next;
            }

            free_node(current);
            ht->count--;
            return 1;
        }

        prev = current;
        current = current->next;
    }

    return 0;
}

// Resize hash table
void resize_table(HashTable *ht) {
    int new_size = ht->size * 2;
    HashNode **new_table = (HashNode**)malloc(sizeof(HashNode*) * new_size);

    if (!new_table) return;

    // Initialize new table
    for (int i = 0; i < new_size; i++) {
        new_table[i] = NULL;
    }

    // Rehash all existing entries
    for (int i = 0; i < ht->size; i++) {
        HashNode *current = ht->table[i];
        while (current) {
            HashNode *next = current->next;

            // Calculate new index
            unsigned long new_index = hash_function(current->key, new_size);

            // Insert into new table
            current->next = new_table[new_index];
            new_table[new_index] = current;

            current = next;
        }
    }

    // Free old table and update
    free(ht->table);
    ht->table = new_table;
    ht->size = new_size;
}

// Print hash table
void print_table(HashTable *ht) {
    if (!ht) return;

    printf("\n=== Hash Table Contents ===\n");
    printf("Size: %d, Count: %d, Load Factor: %.2f\n\n", ht->size, ht->count, get_load_factor(ht));

    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i]) {
            printf("Bucket %d: ", i);
            HashNode *current = ht->table[i];
            while (current) {
                printf("[%s: %s] ", current->key, current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

// Get load factor
double get_load_factor(HashTable *ht) {
    if (!ht || ht->size == 0) return 0.0;
    return (double)ht->count / ht->size;
}
```

### **4. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

void display_menu() {
    printf("\n=== Hash Table Operations ===\n");
    printf("1. Insert Key-Value Pair\n");
    printf("2. Search Value by Key\n");
    printf("3. Delete Key-Value Pair\n");
    printf("4. Display Hash Table\n");
    printf("5. Show Statistics\n");
    printf("6. Exit\n");
    printf("===========================\n");
    printf("Enter your choice: ");
}

int main() {
    HashTable *ht = create_hashtable(INITIAL_SIZE);
    if (!ht) {
        printf("Failed to create hash table!\n");
        return 1;
    }

    printf("Hash Table Implementation\n");
    printf("=========================\n");

    int choice;
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Insert
                printf("Enter key: ");
                scanf(" %[^\n]", key);
                printf("Enter value: ");
                scanf(" %[^\n]", value);

                if (insert(ht, key, value)) {
                    printf("Successfully inserted!\n");
                } else {
                    printf("Failed to insert!\n");
                }
                break;
            }

            case 2: {
                // Search
                printf("Enter key to search: ");
                scanf(" %[^\n]", key);

                char *result = search(ht, key);
                if (result) {
                    printf("Found: %s\n", result);
                } else {
                    printf("Key not found!\n");
                }
                break;
            }

            case 3: {
                // Delete
                printf("Enter key to delete: ");
                scanf(" %[^\n]", key);

                if (delete(ht, key)) {
                    printf("Successfully deleted!\n");
                } else {
                    printf("Key not found!\n");
                }
                break;
            }

            case 4:
                // Display
                print_table(ht);
                break;

            case 5: {
                // Statistics
                printf("\n=== Hash Table Statistics ===\n");
                printf("Table Size: %d\n", ht->size);
                printf("Number of Entries: %d\n", ht->count);
                printf("Load Factor: %.2f\n", get_load_factor(ht));

                // Calculate collisions
                int total_collisions = 0;
                int max_chain_length = 0;

                for (int i = 0; i < ht->size; i++) {
                    int chain_length = 0;
                    HashNode *current = ht->table[i];
                    while (current) {
                        chain_length++;
                        current = current->next;
                    }

                    if (chain_length > 1) {
                        total_collisions += (chain_length - 1);
                    }

                    if (chain_length > max_chain_length) {
                        max_chain_length = chain_length;
                    }
                }

                printf("Total Collisions: %d\n", total_collisions);
                printf("Max Chain Length: %d\n", max_chain_length);
                break;
            }

            case 6:
                free_hashtable(ht);
                printf("Thank you for using Hash Table!\n");
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

### **Core Operations**
- ✅ Insert key-value pairs
- ✅ Search by key
- ✅ Delete entries
- ✅ Dynamic resizing
- ✅ Collision resolution using chaining

### **Advanced Features**
- ✅ Load factor monitoring
- ✅ Performance statistics
- ✅ Memory management
- ✅ Hash function optimization

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Hash Table Implementation - Efficient Key-Value Storage"
- **Hinglish:** "Hash Table Implementation - Efficient Key-Value Storage"

### **Slide 2: What We Built**
- ✅ Complete hash table with chaining
- ✅ Dynamic resizing capabilities
- ✅ Collision resolution
- ✅ Performance monitoring
- ✅ Memory-efficient implementation

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode {
    char key[100];
    char value[500];
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **table;
    int size;
    int count;
} HashTable;

// Core functions
HashTable* create_hashtable(int initial_size);
int insert(HashTable *ht, const char *key, const char *value);
char* search(HashTable *ht, const char *key);
int delete(HashTable *ht, const char *key);
void resize_table(HashTable *ht);
```

### **Slide 4: Hash Function**
```c
// DJB2 hash algorithm
unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

// Hash table index calculation
unsigned long hash_function(const char *key, int table_size) {
    unsigned long hash = djb2_hash(key);
    return hash % table_size;
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Data structure implementation
- ✅ Hash function design
- ✅ Dynamic memory management
- ✅ Algorithm optimization
- ✅ Performance analysis

### **Algorithm Concepts:**
- ✅ Hash table operations
- ✅ Collision resolution
- ✅ Load factor management
- ✅ Time complexity analysis
- ✅ Memory efficiency

---

## 📞 **Contact & Support**

**Project Developer:** Data Structures Student
**Email:** hashtable@studentproject.com
**GitHub:** https://github.com/c-hashtable/hash-table

---

**🔗 This hash table implementation demonstrates advanced data structure concepts and efficient key-value storage in C, perfect for understanding database indexing and caching systems.**