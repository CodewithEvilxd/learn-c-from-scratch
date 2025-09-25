/*
 * Utilities Header
 * Common utility functions for the chatbot
 */

#ifndef UTILS_H
#define UTILS_H

#include <time.h>

// String utilities
int str_trim(char* str);
int str_to_lower(char* str);
int str_to_upper(char* str);
int str_starts_with(const char* str, const char* prefix);
int str_ends_with(const char* str, const char* suffix);
int str_contains(const char* str, const char* substring);
char* str_copy(const char* src, char* dest, size_t dest_size);
char* str_concat(char* dest, const char* src, size_t dest_size);

// Mathematical utilities
double calculate_expression(const char* expression);
double evaluate_function(const char* func_name, double arg);

// Time and date utilities
char* get_current_time(char* buffer, size_t size);
char* get_current_date(char* buffer, size_t size);
time_t parse_date(const char* date_str);
int format_time(time_t timestamp, char* buffer, size_t size);

// File utilities
int file_exists(const char* filename);
long get_file_size(const char* filename);
int create_directory(const char* path);

// Random utilities
int random_int(int min, int max);
double random_double(double min, double max);
void shuffle_array(int* array, int size);

// Memory utilities
void* safe_malloc(size_t size);
void* safe_calloc(size_t num, size_t size);
void safe_free(void* ptr);

// Validation utilities
int is_valid_email(const char* email);
int is_valid_phone(const char* phone);
int is_valid_date(const char* date);
int is_numeric(const char* str);
int is_alphabetic(const char* str);

// Encoding utilities
char* url_encode(const char* str, char* buffer, size_t size);
char* url_decode(const char* str, char* buffer, size_t size);

// Hash utilities
unsigned long hash_string(const char* str);
unsigned long hash_file(const char* filename);

// Logging utilities
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

void log_message(LogLevel level, const char* message, ...);
void set_log_level(LogLevel level);
void set_log_file(const char* filename);

#endif // UTILS_H