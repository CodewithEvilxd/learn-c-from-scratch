/*
 * AI Chatbot Core Implementation
 * Main chatbot logic and processing functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "../headers/chatbot.h"
#include "../headers/nlp.h"
#include "../headers/memory.h"
#include "../headers/knowledge.h"
#include "../headers/personality.h"
#include "../headers/utils.h"

// Static response arrays for different intents
static const char* greeting_responses[] = {
    "Hello! How can I help you today?",
    "Hi there! What can I do for you?",
    "Greetings! How may I assist you?",
    "Hello! I'm here to help. What do you need?",
    "Hi! Nice to meet you. How can I help?"
};

static const char* goodbye_responses[] = {
    "Goodbye! Have a great day!",
    "See you later! Take care!",
    "Farewell! It was nice chatting with you!",
    "Bye! Come back anytime!",
    "Take care! Goodbye!"
};

static const char* unknown_responses[] = {
    "I'm not sure I understand. Could you rephrase that?",
    "I didn't quite catch that. Can you say it differently?",
    "I'm still learning! Could you explain that another way?",
    "Hmm, I'm not sure about that. Can you help me understand?",
    "I need a bit more context. Could you elaborate?"
};

static const char* joke_responses[] = {
    "Why don't scientists trust atoms? Because they make up everything! 😄",
    "Why did the computer go to the doctor? Because it had a virus! 💻",
    "What do you call a computer that sings? A Dell! 🎵",
    "Why was the JavaScript developer sad? Because he didn't know how to 'null' his feelings! 😢",
    "Why do programmers prefer dark mode? Because light attracts bugs! 🐛"
};

// Chatbot creation and destruction
Chatbot* chatbot_create(void) {
    Chatbot* chatbot = (Chatbot*)safe_malloc(sizeof(Chatbot));

    if (!chatbot) {
        return NULL;
    }

    // Initialize basic properties
    strcpy(chatbot->name, "AI_Assistant");
    chatbot->personality = PERSONALITY_FRIENDLY;
    chatbot->start_time = time(NULL);
    chatbot->total_interactions = 0;

    // Initialize context
    memset(&chatbot->context, 0, sizeof(ConversationContext));
    chatbot->context.conversation_start = time(NULL);
    chatbot->context.sentiment_score = 0.5f;

    // Initialize subsystems
    chatbot->nlp_processor = nlp_create();
    chatbot->memory = memory_create();
    chatbot->knowledge_base = knowledge_create();
    chatbot->personality_system = personality_create();

    if (!chatbot->nlp_processor || !chatbot->memory ||
        !chatbot->knowledge_base || !chatbot->personality_system) {
        chatbot_destroy(chatbot);
        return NULL;
    }

    // Initialize NLP patterns
    nlp_add_pattern(chatbot->nlp_processor, "hello|hi|hey|greetings", "greeting", 1.0f);
    nlp_add_pattern(chatbot->nlp_processor, "bye|goodbye|see you|farewell", "goodbye", 1.0f);
    nlp_add_pattern(chatbot->nlp_processor, "calculate|compute|math|solve", "calculation", 1.0f);
    nlp_add_pattern(chatbot->nlp_processor, "remember|recall|store", "memory", 0.8f);
    nlp_add_pattern(chatbot->nlp_processor, "play game|game|fun", "game", 1.0f);
    nlp_add_pattern(chatbot->nlp_processor, "joke|funny|laugh", "joke", 1.0f);
    nlp_add_pattern(chatbot->nlp_processor, "help|commands|what can you do", "help", 1.0f);

    log_message(LOG_INFO, "Chatbot initialized successfully");
    return chatbot;
}

void chatbot_destroy(Chatbot* chatbot) {
    if (!chatbot) return;

    if (chatbot->nlp_processor) {
        nlp_destroy(chatbot->nlp_processor);
    }
    if (chatbot->memory) {
        memory_destroy(chatbot->memory);
    }
    if (chatbot->knowledge_base) {
        knowledge_destroy(chatbot->knowledge_base);
    }
    if (chatbot->personality_system) {
        personality_destroy(chatbot->personality_system);
    }

    safe_free(chatbot);
    log_message(LOG_INFO, "Chatbot destroyed");
}

// Main processing function
int chatbot_process_input(Chatbot* chatbot, const char* input, char* response, size_t response_size) {
    if (!chatbot || !input || !response || response_size == 0) {
        return CHATBOT_ERROR_INVALID_INPUT;
    }

    chatbot->total_interactions++;

    // Recognize intent
    IntentType intent = chatbot_recognize_intent(chatbot, input);

    // Update context
    chatbot_update_context(chatbot, intent, input);

    // Process intent and generate response
    int result = chatbot_process_intent(chatbot, intent, input, response, response_size);

    if (result != CHATBOT_SUCCESS) {
        // Fallback response
        const char* fallback = "I'm having trouble processing that. Could you try rephrasing?";
        str_copy(fallback, response, response_size);
    }

    return CHATBOT_SUCCESS;
}

// Intent recognition
IntentType chatbot_recognize_intent(Chatbot* chatbot, const char* input) {
    char intent_str[50];
    float confidence;

    if (nlp_recognize_intent(chatbot->nlp_processor, input, intent_str, sizeof(intent_str), &confidence) == 0) {
        // Map string intent to enum
        if (strcmp(intent_str, "greeting") == 0) return INTENT_GREETING;
        if (strcmp(intent_str, "goodbye") == 0) return INTENT_GOODBYE;
        if (strcmp(intent_str, "calculation") == 0) return INTENT_CALCULATION;
        if (strcmp(intent_str, "memory") == 0) return INTENT_MEMORY_RECALL;
        if (strcmp(intent_str, "game") == 0) return INTENT_GAME_START;
        if (strcmp(intent_str, "joke") == 0) return INTENT_JOKE;
        if (strcmp(intent_str, "help") == 0) return INTENT_HELP;
    }

    // Pattern-based recognition
    char lower_input[1024];
    str_copy(input, lower_input, sizeof(lower_input));
    str_to_lower(lower_input);

    if (strstr(lower_input, "weather")) return INTENT_WEATHER;
    if (strstr(lower_input, "time") || strstr(lower_input, "date")) return INTENT_TIME_DATE;
    if (strstr(lower_input, "news")) return INTENT_NEWS;
    if (strstr(lower_input, "convert") || strstr(lower_input, "exchange")) return INTENT_CURRENCY_CONVERT;
    if (strstr(lower_input, "status")) return INTENT_STATUS;
    if (strstr(lower_input, "personality")) return INTENT_PERSONALITY_SWITCH;

    return INTENT_UNKNOWN;
}

// Intent processing
int chatbot_process_intent(Chatbot* chatbot, IntentType intent, const char* input, char* response, size_t response_size) {
    switch (intent) {
        case INTENT_GREETING:
            return chatbot_handle_greeting(chatbot, response, response_size);
        case INTENT_GOODBYE:
            return chatbot_handle_goodbye(chatbot, response, response_size);
        case INTENT_CALCULATION:
            return chatbot_handle_calculation(chatbot, input, response, response_size);
        case INTENT_MEMORY_RECALL:
            return chatbot_handle_memory(chatbot, input, response, response_size);
        case INTENT_GAME_START:
            return chatbot_handle_game(chatbot, input, response, response_size);
        case INTENT_JOKE:
            return chatbot_handle_joke(chatbot, response, response_size);
        case INTENT_WEATHER:
            return chatbot_handle_weather(chatbot, response, response_size);
        case INTENT_TIME_DATE:
            return chatbot_handle_time_date(chatbot, response, response_size);
        case INTENT_NEWS:
            return chatbot_handle_news(chatbot, response, response_size);
        case INTENT_CURRENCY_CONVERT:
            return chatbot_handle_currency(chatbot, input, response, response_size);
        case INTENT_STATUS:
            return chatbot_handle_status(chatbot, response, response_size);
        case INTENT_PERSONALITY_SWITCH:
            return chatbot_handle_personality_switch(chatbot, input, response, response_size);
        case INTENT_HELP:
            return chatbot_handle_help(chatbot, response, response_size);
        default:
            return chatbot_handle_unknown(chatbot, response, response_size);
    }
}

// Intent handlers
int chatbot_handle_greeting(Chatbot* chatbot, char* response, size_t response_size) {
    int index = random_int(0, sizeof(greeting_responses) / sizeof(greeting_responses[0]) - 1);
    str_copy(greeting_responses[index], response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_goodbye(Chatbot* chatbot, char* response, size_t response_size) {
    int index = random_int(0, sizeof(goodbye_responses) / sizeof(goodbye_responses[0]) - 1);
    str_copy(goodbye_responses[index], response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_calculation(Chatbot* chatbot, const char* input, char* response, size_t response_size) {
    // Simple expression evaluation
    double result = calculate_expression(input);
    if (!isnan(result)) {
        snprintf(response, response_size, "The result is: %.6f", result);
    } else {
        str_copy("I couldn't calculate that. Please check your expression.", response, response_size);
    }
    return CHATBOT_SUCCESS;
}

int chatbot_handle_memory(Chatbot* chatbot, const char* input, char* response, size_t response_size) {
    // Simple memory operations
    if (strstr(input, "remember")) {
        str_copy("I'll remember that for our future conversations!", response, response_size);
    } else if (strstr(input, "recall")) {
        str_copy("Let me think... I remember we talked about various topics!", response, response_size);
    } else {
        str_copy("Memory functions are still being developed!", response, response_size);
    }
    return CHATBOT_SUCCESS;
}

int chatbot_handle_game(Chatbot* chatbot, const char* input, char* response, size_t response_size) {
    str_copy("Let's play a game! Try 'guess number' or 'rock paper scissors'. What would you like to play?", response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_joke(Chatbot* chatbot, char* response, size_t response_size) {
    int index = random_int(0, sizeof(joke_responses) / sizeof(joke_responses[0]) - 1);
    str_copy(joke_responses[index], response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_weather(Chatbot* chatbot, char* response, size_t response_size) {
    str_copy("I'd love to help with weather information, but I don't have access to current weather data. However, I can tell you about general weather patterns!", response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_time_date(Chatbot* chatbot, char* response, size_t response_size) {
    char time_str[100];
    char date_str[100];

    get_current_time(time_str, sizeof(time_str));
    get_current_date(date_str, sizeof(date_str));

    snprintf(response, response_size, "Current time: %s, Date: %s", time_str, date_str);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_news(Chatbot* chatbot, char* response, size_t response_size) {
    str_copy("For the latest news, I recommend checking reputable news websites. I don't have real-time news access, but I can help you find information on various topics!", response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_currency(Chatbot* chatbot, const char* input, char* response, size_t response_size) {
    str_copy("Currency conversion requires real-time exchange rates. I can help you understand the concept, but for accurate conversions, please use a financial service!", response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_status(Chatbot* chatbot, char* response, size_t response_size) {
    time_t uptime = chatbot_get_uptime(chatbot);
    int hours = uptime / 3600;
    int minutes = (uptime % 3600) / 60;

    snprintf(response, response_size,
             "Status: Active\nUptime: %d hours, %d minutes\nInteractions: %d\nPersonality: %s",
             hours, minutes, chatbot->total_interactions,
             chatbot->personality == PERSONALITY_FRIENDLY ? "Friendly" : "Other");
    return CHATBOT_SUCCESS;
}

int chatbot_handle_personality_switch(Chatbot* chatbot, const char* input, char* response, size_t response_size) {
    if (strstr(input, "friendly")) {
        chatbot_set_personality(chatbot, PERSONALITY_FRIENDLY);
        str_copy("Switched to friendly personality! 😊", response, response_size);
    } else if (strstr(input, "professional")) {
        chatbot_set_personality(chatbot, PERSONALITY_PROFESSIONAL);
        str_copy("Switched to professional personality. How may I assist you?", response, response_size);
    } else {
        str_copy("Available personalities: friendly, professional. Which would you like?", response, response_size);
    }
    return CHATBOT_SUCCESS;
}

int chatbot_handle_help(Chatbot* chatbot, char* response, size_t response_size) {
    str_copy("I can help with calculations, tell jokes, play games, check time/date, and have conversations. Try asking me to 'calculate 2+3' or 'tell me a joke'!", response, response_size);
    return CHATBOT_SUCCESS;
}

int chatbot_handle_unknown(Chatbot* chatbot, char* response, size_t response_size) {
    int index = random_int(0, sizeof(unknown_responses) / sizeof(unknown_responses[0]) - 1);
    str_copy(unknown_responses[index], response, response_size);
    return CHATBOT_SUCCESS;
}

// Context updates
void chatbot_update_context(Chatbot* chatbot, IntentType intent, const char* input) {
    chatbot->context.last_intent = intent;
    chatbot->context.message_count++;

    // Simple sentiment analysis
    if (strstr(input, "great") || strstr(input, "awesome") || strstr(input, "love")) {
        chatbot->context.sentiment_score += 0.1f;
    } else if (strstr(input, "bad") || strstr(input, "hate") || strstr(input, "terrible")) {
        chatbot->context.sentiment_score -= 0.1f;
    }

    // Clamp sentiment between 0 and 1
    if (chatbot->context.sentiment_score < 0) chatbot->context.sentiment_score = 0;
    if (chatbot->context.sentiment_score > 1) chatbot->context.sentiment_score = 1;
}

// Utility functions
const char* chatbot_get_name(Chatbot* chatbot) {
    return chatbot ? chatbot->name : "";
}

PersonalityType chatbot_get_personality(Chatbot* chatbot) {
    return chatbot ? chatbot->personality : PERSONALITY_FRIENDLY;
}

void chatbot_set_personality(Chatbot* chatbot, PersonalityType personality) {
    if (chatbot) {
        chatbot->personality = personality;
    }
}

time_t chatbot_get_uptime(Chatbot* chatbot) {
    return chatbot ? (time(NULL) - chatbot->start_time) : 0;
}

const char* chatbot_error_message(ChatbotError error) {
    switch (error) {
        case CHATBOT_SUCCESS: return "Success";
        case CHATBOT_ERROR_MEMORY: return "Memory allocation failed";
        case CHATBOT_ERROR_INVALID_INPUT: return "Invalid input provided";
        case CHATBOT_ERROR_PROCESSING: return "Processing error occurred";
        case CHATBOT_ERROR_IO: return "Input/Output error";
        default: return "Unknown error";
    }
}