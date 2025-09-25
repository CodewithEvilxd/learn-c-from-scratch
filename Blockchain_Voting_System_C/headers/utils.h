/*
 * Utilities Header - Common Utility Functions
 * Helper functions for blockchain voting system
 */

#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

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

// Blockchain-specific utilities (defined in blockchain.h)

// Election result structure (defined in election.h)

// Error handling
typedef enum {
    UTILS_SUCCESS = 0,
    UTILS_ERROR_MEMORY = -1,
    UTILS_ERROR_INVALID_INPUT = -2,
    UTILS_ERROR_FILE_IO = -3,
    UTILS_ERROR_UNKNOWN = -99
} UtilsError;

const char* utils_error_message(UtilsError error);

// Configuration utilities
typedef struct {
    char config_file[256];
    int debug_mode;
    int log_level;
    char data_directory[256];
} Config;

int load_config(Config* config, const char* filename);
int save_config(const Config* config, const char* filename);

// System information
typedef struct {
    char os_name[50];
    char architecture[20];
    uint64_t total_memory;
    uint64_t available_memory;
    int cpu_cores;
    char hostname[100];
} SystemInfo;

int get_system_info(SystemInfo* info);
void print_system_info(const SystemInfo* info);

// Performance monitoring
typedef struct {
    time_t start_time;
    uint64_t operations_count;
    double cpu_usage;
    uint64_t memory_usage;
} PerformanceStats;

void performance_start_monitoring(PerformanceStats* stats);
void performance_update_stats(PerformanceStats* stats);
void performance_print_stats(const PerformanceStats* stats);

// Security utilities
int generate_secure_random(uint8_t* buffer, size_t size);
int hash_password(const char* password, char* hash_output, size_t output_size);
int verify_password(const char* password, const char* hash);

// Data conversion utilities
int hex_to_bytes(const char* hex, uint8_t* bytes, size_t byte_size);
int bytes_to_hex(const uint8_t* bytes, size_t byte_size, char* hex, size_t hex_size);
int base64_encode(const uint8_t* data, size_t data_len, char* output, size_t output_size);
int base64_decode(const char* input, uint8_t* output, size_t output_size);

// Network utilities (basic)
int resolve_hostname(const char* hostname, char* ip_address, size_t ip_size);
bool is_valid_ip_address(const char* ip);
bool is_valid_port(int port);

// Threading utilities (if needed)
typedef struct {
    void* handle;
    bool is_running;
    void (*callback)(void* arg);
    void* callback_arg;
} Thread;

int thread_create(Thread* thread, void (*callback)(void*), void* arg);
int thread_join(Thread* thread);
int thread_detach(Thread* thread);

// Synchronization primitives
typedef struct {
    void* handle;
} Mutex;

int mutex_create(Mutex* mutex);
int mutex_destroy(Mutex* mutex);
int mutex_lock(Mutex* mutex);
int mutex_unlock(Mutex* mutex);

#endif // UTILS_H