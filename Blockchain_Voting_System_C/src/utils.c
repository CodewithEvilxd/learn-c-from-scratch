/*
 * Utilities Implementation
 * Common utility functions for the blockchain voting system
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include "../headers/utils.h"
#include "../headers/crypto.h"

// Simple strptime implementation for Windows compatibility
char* strptime(const char* s, const char* format, struct tm* tm) {
    // Stub implementation - always return NULL for now
    // In a real implementation, this would parse the string according to format
    return NULL;
}

// String utilities
int str_trim(char* str) {
    if (!str) return -1;

    // Trim leading whitespace
    char* start = str;
    while (*start && isspace(*start)) start++;

    // Trim trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) end--;

    // Shift string
    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';

    return 0;
}

int str_to_lower(char* str) {
    if (!str) return -1;

    for (char* p = str; *p; p++) {
        *p = tolower(*p);
    }

    return 0;
}

int str_to_upper(char* str) {
    if (!str) return -1;

    for (char* p = str; *p; p++) {
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

    if (total_len >= dest_size) return NULL;

    memcpy(dest + dest_len, src, src_len + 1);
    return dest;
}

// Mathematical utilities
double calculate_expression(const char* expression) {
    // Stub implementation - would need a proper expression parser
    return 0.0;
}

double evaluate_function(const char* func_name, double arg) {
    // Stub implementation
    return 0.0;
}

// Time and date utilities
char* get_current_time(char* buffer, size_t size) {
    if (!buffer || size == 0) return NULL;

    time_t now = time(NULL);
    strftime(buffer, size, "%H:%M:%S", localtime(&now));
    return buffer;
}

char* get_current_date(char* buffer, size_t size) {
    if (!buffer || size == 0) return NULL;

    time_t now = time(NULL);
    strftime(buffer, size, "%Y-%m-%d", localtime(&now));
    return buffer;
}

time_t parse_date(const char* date_str) {
    if (!date_str) return (time_t)-1;

    struct tm tm_time = {0};
    if (strptime(date_str, "%Y-%m-%d", &tm_time) == NULL) {
        return (time_t)-1;
    }

    return mktime(&tm_time);
}

int format_time(time_t timestamp, char* buffer, size_t size) {
    if (!buffer || size == 0) return -1;

    struct tm* tm_time = localtime(&timestamp);
    if (!tm_time) return -1;

    return strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_time);
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
    if (min >= max) return min;
    return min + rand() % (max - min + 1);
}

double random_double(double min, double max) {
    if (min >= max) return min;
    return min + (double)rand() / RAND_MAX * (max - min);
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

    return at && dot && at < dot && at != email && dot != email + strlen(email) - 1;
}

int is_valid_phone(const char* phone) {
    if (!phone) return 0;

    size_t len = strlen(phone);
    if (len < 10 || len > 15) return 0;

    for (size_t i = 0; i < len; i++) {
        if (!isdigit(phone[i]) && phone[i] != '+' && phone[i] != '-' && phone[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

int is_valid_date(const char* date) {
    return parse_date(date) != (time_t)-1;
}

int is_numeric(const char* str) {
    if (!str || !*str) return 0;

    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '.' && *p != '-') return 0;
    }

    return 1;
}

int is_alphabetic(const char* str) {
    if (!str || !*str) return 0;

    for (const char* p = str; *p; p++) {
        if (!isalpha(*p) && *p != ' ') return 0;
    }

    return 1;
}

// Logging utilities
static LogLevel current_log_level = LOG_INFO;
static char log_filename[256] = "blockchain_voting.log";

void log_message(LogLevel level, const char* message, ...) {
    if (level < current_log_level) return;

    const char* level_names[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    char timestamp[20];
    get_current_time(timestamp, sizeof(timestamp));

    FILE* file = fopen(log_filename, "a");
    if (!file) return;

    fprintf(file, "[%s] %s: ", timestamp, level_names[level]);

    va_list args;
    va_start(args, message);
    vfprintf(file, message, args);
    va_end(args);

    fprintf(file, "\n");
    fclose(file);

    // Also print to console for important messages
    if (level >= LOG_WARNING) {
        printf("[%s] %s: ", timestamp, level_names[level]);
        va_start(args, message);
        vprintf(message, args);
        va_end(args);
        printf("\n");
    }
}

void set_log_level(LogLevel level) {
    current_log_level = level;
}

void set_log_file(const char* filename) {
    if (filename) {
        str_copy(filename, log_filename, sizeof(log_filename));
    }
}

// System information
int get_system_info(SystemInfo* info) {
    if (!info) return -1;

    strcpy(info->os_name, "Windows");
    strcpy(info->architecture, "x64");
    info->total_memory = 8LL * 1024 * 1024 * 1024; // 8GB
    info->available_memory = 6LL * 1024 * 1024 * 1024; // 6GB
    info->cpu_cores = 4;
    strcpy(info->hostname, "localhost");

    return 0;
}

void print_system_info(const SystemInfo* info) {
    if (!info) return;

    printf("System Information:\n");
    printf("  OS: %s\n", info->os_name);
    printf("  Architecture: %s\n", info->architecture);
    printf("  Total Memory: %.2f GB\n", (double)info->total_memory / (1024*1024*1024));
    printf("  Available Memory: %.2f GB\n", (double)info->available_memory / (1024*1024*1024));
    printf("  CPU Cores: %d\n", info->cpu_cores);
    printf("  Hostname: %s\n", info->hostname);
}

// Performance monitoring
void performance_start_monitoring(PerformanceStats* stats) {
    if (!stats) return;

    memset(stats, 0, sizeof(PerformanceStats));
    stats->start_time = time(NULL);
}

void performance_update_stats(PerformanceStats* stats) {
    if (!stats) return;

    stats->operations_count++;
    // Stub implementations for other metrics
}

// Security utilities
int generate_secure_random(uint8_t* buffer, size_t len) {
    for (size_t i = 0; i < len; i++) {
        buffer[i] = (uint8_t)(rand() % 256);
    }
    return 0;
}

int hash_password(const char* password, char* hash_output, size_t output_size) {
    // Stub implementation - use proper password hashing in production
    uint8_t hash[SHA256_DIGEST_SIZE];
    sha256_hash((const uint8_t*)password, strlen(password), hash);
    sha256_to_hex(hash, hash_output);
    return 0;
}

int verify_password(const char* password, const char* hash) {
    // Stub implementation
    char computed_hash[65];
    hash_password(password, computed_hash, sizeof(computed_hash));
    return strcmp(computed_hash, hash) == 0;
}

// Data conversion utilities
int hex_to_bytes(const char* hex, uint8_t* bytes, size_t byte_size) {
    if (!hex || !bytes || strlen(hex) != byte_size * 2) return -1;

    for (size_t i = 0; i < byte_size; i++) {
        char byte_str[3] = {hex[i * 2], hex[i * 2 + 1], '\0'};
        bytes[i] = (uint8_t)strtol(byte_str, NULL, 16);
    }

    return 0;
}

int bytes_to_hex(const uint8_t* bytes, size_t byte_size, char* hex, size_t hex_size) {
    if (!bytes || !hex || hex_size < byte_size * 2 + 1) return -1;

    for (size_t i = 0; i < byte_size; i++) {
        sprintf(hex + i * 2, "%02x", bytes[i]);
    }

    hex[byte_size * 2] = '\0';
    return 0;
}

// Stub implementations
int base64_encode(const uint8_t* data, size_t data_len, char* output, size_t output_size) {
    return 0;
}

int base64_decode(const char* input, uint8_t* output, size_t output_size) {
    return 0;
}

// Network utilities
int resolve_hostname(const char* hostname, char* ip_address, size_t ip_size) {
    // Stub implementation
    str_copy("127.0.0.1", ip_address, ip_size);
    return 0;
}

bool is_valid_ip_address(const char* ip) {
    // Simple validation
    int dots = 0;
    for (const char* p = ip; *p; p++) {
        if (*p == '.') dots++;
        else if (!isdigit(*p)) return false;
    }
    return dots == 3;
}

bool is_valid_port(int port) {
    return port > 0 && port <= 65535;
}

// Threading utilities (stubs)
int thread_create(Thread* thread, void (*callback)(void*), void* arg) {
    return 0;
}

int thread_join(Thread* thread) {
    return 0;
}

int thread_detach(Thread* thread) {
    return 0;
}

// Synchronization primitives (stubs)
int mutex_create(Mutex* mutex) {
    return 0;
}

int mutex_destroy(Mutex* mutex) {
    return 0;
}

int mutex_lock(Mutex* mutex) {
    return 0;
}

int mutex_unlock(Mutex* mutex) {
    return 0;
}