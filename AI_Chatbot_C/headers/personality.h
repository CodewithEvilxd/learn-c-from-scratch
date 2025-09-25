/*
 * Personality System Header
 * Dynamic personality adaptation and response generation
 */

#ifndef PERSONALITY_H
#define PERSONALITY_H

#include <time.h>

// Forward declarations to avoid circular dependencies
typedef enum {
    INTENT_GREETING,
    INTENT_GOODBYE,
    INTENT_QUESTION,
    INTENT_COMMAND,
    INTENT_CALCULATION,
    INTENT_MEMORY_RECALL,
    INTENT_MEMORY_STORE,
    INTENT_GAME_START,
    INTENT_LEARN,
    INTENT_WEATHER,
    INTENT_NEWS,
    INTENT_TIME_DATE,
    INTENT_JOKE,
    INTENT_PERSONALITY_SWITCH,
    INTENT_CURRENCY_CONVERT,
    INTENT_HELP,
    INTENT_STATUS,
    INTENT_UNKNOWN
} IntentType;

typedef enum {
    PERSONALITY_FRIENDLY,
    PERSONALITY_PROFESSIONAL,
    PERSONALITY_WITTY,
    PERSONALITY_CREATIVE,
    PERSONALITY_HELPFUL
} PersonalityType;

// Personality parameters
#define MAX_GREETING_LENGTH 200
#define MAX_RESPONSE_STYLE_LENGTH 100

// Personality structure
typedef struct {
    PersonalityType type;
    char greeting[MAX_GREETING_LENGTH];
    char response_style[MAX_RESPONSE_STYLE_LENGTH];
    float humor_level;      // 0.0 to 1.0
    float formality_level;  // 0.0 to 1.0
    float creativity_level; // 0.0 to 1.0
    float empathy_level;    // 0.0 to 1.0
    int adaptation_count;
} Personality;

// Personality system structure
typedef struct {
    Personality personalities[5];  // One for each personality type
    PersonalityType current_type;
    float user_satisfaction;  // Based on feedback
    int interaction_count;
} PersonalitySystem;

// Function declarations

// Personality system lifecycle
PersonalitySystem* personality_create(void);
void personality_destroy(PersonalitySystem* ps);

// Personality management
int personality_set_type(PersonalitySystem* ps, PersonalityType type);
PersonalityType personality_get_current(PersonalitySystem* ps);
const char* personality_get_greeting(PersonalitySystem* ps);

// Response generation
int personality_generate_response(PersonalitySystem* ps, IntentType intent, const char* input, char* response, size_t response_size);

// Adaptation and learning
int personality_adapt_from_feedback(PersonalitySystem* ps, float satisfaction_score);
int personality_learn_from_interaction(PersonalitySystem* ps, IntentType intent, const char* user_input, const char* bot_response);

// Utility functions
void personality_get_stats(PersonalitySystem* ps, char* stats, size_t stats_size);
int personality_save_settings(PersonalitySystem* ps, const char* filename);
int personality_load_settings(PersonalitySystem* ps, const char* filename);

#endif // PERSONALITY_H