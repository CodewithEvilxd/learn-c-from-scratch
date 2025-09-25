/*
 * Knowledge Base Header
 * Knowledge management and question answering system
 */

#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

// Maximum knowledge items
#define MAX_KNOWLEDGE_ITEMS 5000
#define MAX_QUESTION_LENGTH 200
#define MAX_ANSWER_LENGTH 1000
#define MAX_CATEGORY_LENGTH 50

// Knowledge item structure
typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char answer[MAX_ANSWER_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int confidence;
    int access_count;
    time_t last_accessed;
} KnowledgeItem;

// Knowledge base structure
typedef struct {
    KnowledgeItem items[MAX_KNOWLEDGE_ITEMS];
    int count;
    char filename[256];
} KnowledgeBase;

// Function declarations

// Knowledge base lifecycle
KnowledgeBase* knowledge_create(void);
void knowledge_destroy(KnowledgeBase* kb);

// Knowledge operations
int knowledge_add(KnowledgeBase* kb, const char* question, const char* answer, const char* category);
int knowledge_remove(KnowledgeBase* kb, const char* question);
const char* knowledge_find_answer(KnowledgeBase* kb, const char* question);
int knowledge_update_answer(KnowledgeBase* kb, const char* question, const char* new_answer);

// Search and query
int knowledge_search(KnowledgeBase* kb, const char* keyword, KnowledgeItem* results[], int max_results);
int knowledge_get_by_category(KnowledgeBase* kb, const char* category, KnowledgeItem* results[], int max_results);
KnowledgeItem* knowledge_get_random(KnowledgeBase* kb);

// Persistence
int knowledge_save(KnowledgeBase* kb, const char* filename);
int knowledge_load(KnowledgeBase* kb, const char* filename);

// Statistics and maintenance
void knowledge_get_stats(KnowledgeBase* kb, int* total_items, int* total_categories, time_t* last_updated);
void knowledge_cleanup(KnowledgeBase* kb);
int knowledge_optimize(KnowledgeBase* kb);

// Learning
int knowledge_learn_from_interaction(KnowledgeBase* kb, const char* user_input, const char* bot_response);

#endif // KNOWLEDGE_H