/*
 * IoT Smart Home - Utility Functions Header
 * Common utilities, logging, and helper functions
 */

#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>
#include <stdarg.h>

// Log Levels
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

// String Utilities
char* str_trim(char* str);
char* str_to_lower(char* str);
char* str_to_upper(char* str);
char** str_split(const char* str, const char* delimiter, int* count);
char* str_join(char** strings, int count, const char* separator);
bool str_starts_with(const char* str, const char* prefix);
bool str_ends_with(const char* str, const char* suffix);
char* str_replace(const char* str, const char* old_sub, const char* new_sub);

// Time Utilities
char* time_to_string(time_t timestamp);
time_t string_to_time(const char* time_str);
char* get_current_time_string(void);
time_t get_current_time(void);
double time_diff_seconds(time_t start, time_t end);
bool is_time_between(time_t time, time_t start, time_t end);

// File Utilities
bool file_exists(const char* filename);
long get_file_size(const char* filename);
time_t get_file_modified_time(const char* filename);
int create_directory(const char* path);
char* read_file_to_string(const char* filename);
int write_string_to_file(const char* filename, const char* content);

// Math Utilities
int clamp_int(int value, int min, int max);
float clamp_float(float value, float min, float max);
double round_to_decimals(double value, int decimals);
int random_int(int min, int max);
float random_float(float min, float max);

// Array Utilities
void* array_find(void* array, size_t element_size, int count,
                bool (*predicate)(void* element, void* context), void* context);
int array_filter(void* source, size_t element_size, int source_count,
                void* dest, bool (*predicate)(void* element, void* context), void* context);
void array_sort(void* array, size_t element_size, int count,
               int (*compare)(const void* a, const void* b));

// Logging System
void set_log_level(LogLevel level);
void set_log_file(const char* filename);
void log_message(LogLevel level, const char* format, ...);
void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_warn(const char* format, ...);
void log_error(const char* format, ...);
void log_fatal(const char* format, ...);

// Memory Utilities
void* safe_malloc(size_t size);
void* safe_calloc(size_t num, size_t size);
void* safe_realloc(void* ptr, size_t size);
void safe_free(void* ptr);

// Validation Utilities
bool is_valid_ip_address(const char* ip);
bool is_valid_port(int port);
bool is_valid_email(const char* email);
bool is_numeric(const char* str);
bool is_alphabetic(const char* str);
bool is_alphanumeric(const char* str);

// Hash and Encryption Utilities
unsigned long hash_string(const char* str);
char* generate_uuid(void);
char* base64_encode(const unsigned char* data, size_t len);
unsigned char* base64_decode(const char* str, size_t* out_len);

// System Utilities
char* get_os_name(void);
long get_memory_usage(void);
double get_cpu_usage(void);
char* get_executable_path(void);
bool is_admin_user(void);

// Configuration Utilities
int parse_config_line(const char* line, char* key, char* value);
int load_config_file(const char* filename, void (*callback)(const char* key, const char* value));

// Error Handling
typedef struct {
    int code;
    char message[256];
    time_t timestamp;
    char function[100];
    char file[100];
    int line;
} ErrorInfo;

void set_last_error(int code, const char* message, const char* function,
                   const char* file, int line);
ErrorInfo* get_last_error(void);
void clear_error(void);

// Macros for error handling
#define SET_ERROR(code, message) set_last_error(code, message, __func__, __FILE__, __LINE__)
#define CHECK_NULL(ptr, message) \
    if (!(ptr)) { \
        SET_ERROR(-1, message); \
        return NULL; \
    }
#define CHECK_NEGATIVE(value, message) \
    if ((value) < 0) { \
        SET_ERROR(value, message); \
        return value; \
    }

// Performance Monitoring
typedef struct {
    time_t start_time;
    time_t end_time;
    double duration_ms;
    long memory_before;
    long memory_after;
    long memory_peak;
} PerformanceMetrics;

void start_performance_monitor(PerformanceMetrics* metrics);
void end_performance_monitor(PerformanceMetrics* metrics);
void log_performance_metrics(const char* operation, PerformanceMetrics* metrics);

// Threading Utilities (if needed)
#ifdef _WIN32
#include <windows.h>
typedef HANDLE ThreadHandle;
#else
#include <pthread.h>
typedef pthread_t ThreadHandle;
#endif

typedef void* (*ThreadFunction)(void* arg);

ThreadHandle create_thread(ThreadFunction func, void* arg);
void wait_thread(ThreadHandle thread);
void destroy_thread(ThreadHandle thread);

// Network Utilities
char* get_local_ip_address(void);
bool is_port_open(const char* host, int port);
char* url_encode(const char* str);
char* url_decode(const char* str);

// JSON Utilities (simple implementation)
typedef struct {
    char* key;
    char* value;
    bool is_string;
} JSONPair;

typedef struct {
    JSONPair* pairs;
    int count;
} JSONObject;

JSONObject* json_parse(const char* json_str);
char* json_stringify(JSONObject* obj);
void json_free(JSONObject* obj);
const char* json_get_string(JSONObject* obj, const char* key);
int json_get_int(JSONObject* obj, const char* key);
double json_get_double(JSONObject* obj, const char* key);
bool json_get_bool(JSONObject* obj, const char* key);

#endif // UTILS_H