/*
 * Conversation Memory Header
 * Memory management for conversation history and user preferences
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <time.h>
#include <stdbool.h>

// Maximum memory items
#define MAX_MEMORY_ITEMS 1000
#define MAX_KEY_LENGTH 100
#define MAX_VALUE_LENGTH 500

// Memory item structure
typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
    time_t timestamp;
    int access_count;
    float importance;
} MemoryItem;

// Conversation memory structure
typedef struct {
    MemoryItem items[MAX_MEMORY_ITEMS];
    int count;
    char filename[256];
    time_t last_save;
    bool auto_save;
} ConversationMemory;

// Function declarations

// Memory lifecycle
ConversationMemory* memory_create(void);
void memory_destroy(ConversationMemory* memory);

// Memory operations
int memory_store(ConversationMemory* memory, const char* key, const char* value);
const char* memory_recall(ConversationMemory* memory, const char* key);
int memory_forget(ConversationMemory* memory, const char* key);
int memory_update(ConversationMemory* memory, const char* key, const char* new_value);

// Memory management
void memory_cleanup_old(ConversationMemory* memory, time_t max_age);
void memory_optimize(ConversationMemory* memory);
int memory_get_count(ConversationMemory* memory);

// Persistence
int memory_save(ConversationMemory* memory, const char* filename);
int memory_load(ConversationMemory* memory, const char* filename);

// Search and query
int memory_search(ConversationMemory* memory, const char* pattern, MemoryItem* results[], int max_results);
MemoryItem* memory_get_recent(ConversationMemory* memory, int count);
MemoryItem* memory_get_important(ConversationMemory* memory, int count);

// Statistics
void memory_get_stats(ConversationMemory* memory, int* total_items, int* total_accesses, time_t* oldest_item);

#endif // MEMORY_H