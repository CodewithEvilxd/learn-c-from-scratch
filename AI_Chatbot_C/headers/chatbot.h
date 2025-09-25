/*
 * AI Chatbot in C - Main Header File
 * Core chatbot data structures and function declarations
 */

#ifndef CHATBOT_H
#define CHATBOT_H

#include <time.h>
#include "nlp.h"
#include "memory.h"
#include "knowledge.h"
#include "personality.h"

// Maximum sizes for strings
#define MAX_MESSAGE 1024
#define MAX_RESPONSE 2048
#define MAX_NAME 100
#define MAX_KEY 100
#define MAX_VALUE 500

// Intent and personality types are defined in personality.h

// Conversation context
typedef struct {
    char last_topic[MAX_KEY];
    char user_name[MAX_NAME];
    time_t conversation_start;
    int message_count;
    float sentiment_score;
    IntentType last_intent;
} ConversationContext;

// Main chatbot structure
typedef struct {
    char name[MAX_NAME];
    PersonalityType personality;
    ConversationContext context;
    NLPProcessor* nlp_processor;
    ConversationMemory* memory;
    KnowledgeBase* knowledge_base;
    PersonalitySystem* personality_system;
    time_t start_time;
    int total_interactions;
} Chatbot;

// Function declarations

// Chatbot lifecycle
Chatbot* chatbot_create(void);
void chatbot_destroy(Chatbot* chatbot);

// Main processing
int chatbot_process_input(Chatbot* chatbot, const char* input, char* response, size_t response_size);

// Intent recognition and processing
IntentType chatbot_recognize_intent(Chatbot* chatbot, const char* input);
int chatbot_process_intent(Chatbot* chatbot, IntentType intent, const char* input, char* response, size_t response_size);

// Response generation
int chatbot_generate_response(Chatbot* chatbot, IntentType intent, const char* input, char* response, size_t response_size);

// Utility functions
void chatbot_update_context(Chatbot* chatbot, IntentType intent, const char* input);
const char* chatbot_get_name(Chatbot* chatbot);
PersonalityType chatbot_get_personality(Chatbot* chatbot);
void chatbot_set_personality(Chatbot* chatbot, PersonalityType personality);
time_t chatbot_get_uptime(Chatbot* chatbot);

// Learning and adaptation
void chatbot_learn_from_interaction(Chatbot* chatbot, const char* input, const char* response);
void chatbot_adapt_personality(Chatbot* chatbot, const char* feedback);

// Status and information
void chatbot_get_status(Chatbot* chatbot, char* status, size_t status_size);
void chatbot_get_statistics(Chatbot* chatbot, char* stats, size_t stats_size);

// Error handling
typedef enum {
    CHATBOT_SUCCESS = 0,
    CHATBOT_ERROR_MEMORY = -1,
    CHATBOT_ERROR_INVALID_INPUT = -2,
    CHATBOT_ERROR_PROCESSING = -3,
    CHATBOT_ERROR_IO = -4,
    CHATBOT_ERROR_UNKNOWN = -99
} ChatbotError;

const char* chatbot_error_message(ChatbotError error);

// Intent handler functions
int chatbot_handle_greeting(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_goodbye(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_calculation(Chatbot* chatbot, const char* input, char* response, size_t response_size);
int chatbot_handle_memory(Chatbot* chatbot, const char* input, char* response, size_t response_size);
int chatbot_handle_game(Chatbot* chatbot, const char* input, char* response, size_t response_size);
int chatbot_handle_joke(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_weather(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_time_date(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_news(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_currency(Chatbot* chatbot, const char* input, char* response, size_t response_size);
int chatbot_handle_status(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_personality_switch(Chatbot* chatbot, const char* input, char* response, size_t response_size);
int chatbot_handle_help(Chatbot* chatbot, char* response, size_t response_size);
int chatbot_handle_unknown(Chatbot* chatbot, char* response, size_t response_size);

#endif // CHATBOT_H