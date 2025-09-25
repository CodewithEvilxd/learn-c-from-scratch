/*
 * Utilities Implementation
 * Common utility functions for the chatbot
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include "../headers/utils.h"

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// String utilities
int str_trim(char* str) {
    if (!str) return -1;

    // Trim leading whitespace
    char* start = str;
    while (*start && isspace(*start)) start++;

    // Trim trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) end--;

    // Shift the string
    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';

    return 0;
}

int str_to_lower(char* str) {
    if (!str) return -1;

    for (char* p = str; *p; ++p) {
        *p = tolower(*p);
    }
    return 0;
}

int str_to_upper(char* str) {
    if (!str) return -1;

    for (char* p = str; *p; ++p) {
        *p = toupper(*p);
    }
    return 0;
}

int str_starts_with(const char* str, const char* prefix) {
    if (!str || !prefix) return 0;
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

int str_ends_with(const char* str, const char* suffix) {
    if (!str || !suffix) return 0;

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len) return 0;

    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

int str_contains(const char* str, const char* substring) {
    return strstr(str, substring) != NULL;
}

char* str_copy(const char* src, char* dest, size_t dest_size) {
    if (!src || !dest || dest_size == 0) return NULL;

    size_t src_len = strlen(src);
    size_t copy_len = src_len < dest_size - 1 ? src_len : dest_size - 1;

    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';

    return dest;
}

char* str_concat(char* dest, const char* src, size_t dest_size) {
    if (!dest || !src || dest_size == 0) return NULL;

    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    size_t total_len = dest_len + src_len;

    if (total_len >= dest_size) {
        // Truncate if necessary
        size_t copy_len = dest_size - dest_len - 1;
        if (copy_len > 0) {
            memcpy(dest + dest_len, src, copy_len);
            dest[dest_len + copy_len] = '\0';
        }
    } else {
        memcpy(dest + dest_len, src, src_len + 1);
    }

    return dest;
}

// Mathematical utilities
double calculate_expression(const char* expression) {
    // Very basic expression evaluator
    // This is a simplified implementation - a real one would use proper parsing

    if (!expression) return NAN;

    char expr[256];
    str_copy(expression, expr, sizeof(expr));
    str_trim(expr);

    // Handle simple operations
    double result = 0.0;

    // Check for basic arithmetic
    if (strstr(expr, "+")) {
        char* parts[2];
        char* token = strtok(expr, "+");
        int i = 0;
        while (token && i < 2) {
            parts[i++] = token;
            token = strtok(NULL, "+");
        }
        if (i == 2) {
            result = atof(parts[0]) + atof(parts[1]);
            return result;
        }
    }

    if (strstr(expr, "-")) {
        char* parts[2];
        char* token = strtok(expr, "-");
        int i = 0;
        while (token && i < 2) {
            parts[i++] = token;
            token = strtok(NULL, "-");
        }
        if (i == 2) {
            result = atof(parts[0]) - atof(parts[1]);
            return result;
        }
    }

    if (strstr(expr, "*")) {
        char* parts[2];
        char* token = strtok(expr, "*");
        int i = 0;
        while (token && i < 2) {
            parts[i++] = token;
            token = strtok(NULL, "*");
        }
        if (i == 2) {
            result = atof(parts[0]) * atof(parts[1]);
            return result;
        }
    }

    if (strstr(expr, "/")) {
        char* parts[2];
        char* token = strtok(expr, "/");
        int i = 0;
        while (token && i < 2) {
            parts[i++] = token;
            token = strtok(NULL, "/");
        }
        if (i == 2) {
            double divisor = atof(parts[1]);
            if (divisor != 0) {
                result = atof(parts[0]) / divisor;
                return result;
            }
        }
    }

    // Check for functions
    if (str_starts_with(expr, "sin(")) {
        char* arg = expr + 4;
        if (str_ends_with(arg, ")")) {
            arg[strlen(arg) - 1] = '\0';
            return sin(atof(arg) * M_PI / 180.0); // Convert to radians
        }
    }

    if (str_starts_with(expr, "cos(")) {
        char* arg = expr + 4;
        if (str_ends_with(arg, ")")) {
            arg[strlen(arg) - 1] = '\0';
            return cos(atof(arg) * M_PI / 180.0);
        }
    }

    if (str_starts_with(expr, "sqrt(")) {
        char* arg = expr + 5;
        if (str_ends_with(arg, ")")) {
            arg[strlen(arg) - 1] = '\0';
            double val = atof(arg);
            return val >= 0 ? sqrt(val) : NAN;
        }
    }

    // If no operation found, try to parse as number
    result = atof(expr);
    return isnan(result) ? NAN : result;
}

double evaluate_function(const char* func_name, double arg) {
    if (strcmp(func_name, "sin") == 0) return sin(arg);
    if (strcmp(func_name, "cos") == 0) return cos(arg);
    if (strcmp(func_name, "tan") == 0) return tan(arg);
    if (strcmp(func_name, "sqrt") == 0) return sqrt(arg);
    if (strcmp(func_name, "log") == 0) return log(arg);
    if (strcmp(func_name, "exp") == 0) return exp(arg);
    return NAN;
}

// Time and date utilities
char* get_current_time(char* buffer, size_t size) {
    if (!buffer || size == 0) return NULL;

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    strftime(buffer, size, "%H:%M:%S", tm_info);
    return buffer;
}

char* get_current_date(char* buffer, size_t size) {
    if (!buffer || size == 0) return NULL;

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    strftime(buffer, size, "%Y-%m-%d", tm_info);
    return buffer;
}

time_t parse_date(const char* date_str) {
    // Simple date parsing - YYYY-MM-DD format
    struct tm tm_info = {0};

    if (sscanf(date_str, "%d-%d-%d", &tm_info.tm_year, &tm_info.tm_mon, &tm_info.tm_mday) == 3) {
        tm_info.tm_year -= 1900; // tm_year is years since 1900
        tm_info.tm_mon -= 1;     // tm_mon is 0-based
        return mktime(&tm_info);
    }

    return (time_t)-1;
}

int format_time(time_t timestamp, char* buffer, size_t size) {
    if (!buffer || size == 0) return -1;

    struct tm* tm_info = localtime(&timestamp);
    return strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// File utilities
int file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

long get_file_size(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return -1;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size;
}

// Random utilities
int random_int(int min, int max) {
    if (min > max) return min;
    return min + rand() % (max - min + 1);
}

double random_double(double min, double max) {
    if (min > max) return min;
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void shuffle_array(int* array, int size) {
    if (!array || size <= 1) return;

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Memory utilities
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* safe_calloc(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void safe_free(void* ptr) {
    if (ptr) {
        free(ptr);
    }
}

// Validation utilities
int is_valid_email(const char* email) {
    if (!email) return 0;

    const char* at = strchr(email, '@');
    const char* dot = strrchr(email, '.');

    return at && dot && at < dot;
}

int is_valid_phone(const char* phone) {
    if (!phone || strlen(phone) < 10) return 0;

    for (const char* p = phone; *p; ++p) {
        if (!isdigit(*p) && *p != '+' && *p != '-' && *p != ' ') {
            return 0;
        }
    }
    return 1;
}

int is_valid_date(const char* date) {
    // Simple YYYY-MM-DD validation
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) return 0;

    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    // Basic month-day validation
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        days_in_month[1] = 29; // Leap year
    }

    return day <= days_in_month[month - 1];
}

int is_numeric(const char* str) {
    if (!str || !*str) return 0;

    for (const char* p = str; *p; ++p) {
        if (!isdigit(*p) && *p != '.' && *p != '-') {
            return 0;
        }
    }
    return 1;
}

int is_alphabetic(const char* str) {
    if (!str || !*str) return 0;

    for (const char* p = str; *p; ++p) {
        if (!isalpha(*p) && *p != ' ') {
            return 0;
        }
    }
    return 1;
}

// Logging utilities
static LogLevel current_log_level = LOG_INFO;
static char log_filename[256] = "ai_chatbot.log";

void log_message(LogLevel level, const char* message, ...) {
    if (level < current_log_level) return;

    va_list args;
    va_start(args, message);

    // Get current time
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    // Format log level
    const char* level_str;
    switch (level) {
        case LOG_DEBUG: level_str = "DEBUG"; break;
        case LOG_INFO: level_str = "INFO"; break;
        case LOG_WARNING: level_str = "WARNING"; break;
        case LOG_ERROR: level_str = "ERROR"; break;
        default: level_str = "UNKNOWN"; break;
    }

    // Print to console
    printf("[%s] %s: ", time_str, level_str);
    vprintf(message, args);
    printf("\n");

    // Write to file if specified
    if (log_filename[0]) {
        FILE* log_file = fopen(log_filename, "a");
        if (log_file) {
            fprintf(log_file, "[%s] %s: ", time_str, level_str);
            vfprintf(log_file, message, args);
            fprintf(log_file, "\n");
            fclose(log_file);
        }
    }

    va_end(args);
}

void set_log_level(LogLevel level) {
    current_log_level = level;
}

void set_log_file(const char* filename) {
    if (filename) {
        str_copy(filename, log_filename, sizeof(log_filename));
    }
}