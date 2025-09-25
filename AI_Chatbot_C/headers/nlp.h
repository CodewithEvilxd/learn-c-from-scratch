/*
 * Natural Language Processing Header
 * Text processing and intent recognition functions
 */

#ifndef NLP_H
#define NLP_H

#include <stdbool.h>

// Maximum sizes for NLP processing
#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 50
#define MAX_PATTERNS 50
#define MAX_PATTERN_LENGTH 200

// Token structure for text processing
typedef struct {
    char text[MAX_TOKEN_LENGTH];
    char type[20];  // noun, verb, adjective, etc.
    float confidence;
} Token;

// Pattern matching structure
typedef struct {
    char pattern[MAX_PATTERN_LENGTH];
    char intent[50];
    float weight;
} Pattern;

// NLP Processor structure
typedef struct {
    Pattern patterns[MAX_PATTERNS];
    int pattern_count;
    char language[10];
    bool case_sensitive;
} NLPProcessor;

// Function declarations

// NLP Processor lifecycle
NLPProcessor* nlp_create(void);
void nlp_destroy(NLPProcessor* nlp);

// Text processing
int nlp_tokenize(const char* text, Token* tokens, int max_tokens);
int nlp_normalize_text(char* text);
int nlp_remove_punctuation(char* text);
int nlp_to_lowercase(char* text);

// Intent recognition
int nlp_recognize_intent(NLPProcessor* nlp, const char* text, char* intent, size_t intent_size, float* confidence);
int nlp_add_pattern(NLPProcessor* nlp, const char* pattern, const char* intent, float weight);
int nlp_load_patterns(NLPProcessor* nlp, const char* filename);
int nlp_save_patterns(NLPProcessor* nlp, const char* filename);

// Entity extraction
int nlp_extract_entities(const char* text, char* entities[][2], int max_entities);
int nlp_find_numbers(const char* text, double* numbers, int max_numbers);
int nlp_find_dates(const char* text, char* dates[], int max_dates);

// Sentiment analysis
float nlp_analyze_sentiment(const char* text);

// Language detection
int nlp_detect_language(const char* text, char* language, size_t language_size);

// Text similarity
float nlp_calculate_similarity(const char* text1, const char* text2);

// Utility functions
bool nlp_contains_word(const char* text, const char* word);
int nlp_word_count(const char* text);
int nlp_sentence_count(const char* text);

#endif // NLP_H