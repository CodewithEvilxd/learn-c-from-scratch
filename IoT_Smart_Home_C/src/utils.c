/*
 * IoT Smart Home - Utility Functions Implementation
 * Common utilities, logging, and helper functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include "../headers/utils.h"

// Global variables for logging
static LogLevel current_log_level = LOG_INFO;
static char log_filename[256] = "smarthome.log";
static FILE* log_file = NULL;

// String Utilities

char* str_trim(char* str) {
    if (!str) return NULL;

    // Trim leading whitespace
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return str;

    // Trim trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';
    return str;
}

char* str_to_lower(char* str) {
    if (!str) return NULL;

    for (char* p = str; *p; p++) {
        *p = tolower((unsigned char)*p);
    }
    return str;
}

char* str_to_upper(char* str) {
    if (!str) return NULL;

    for (char* p = str; *p; p++) {
        *p = toupper((unsigned char)*p);
    }
    return str;
}

char** str_split(const char* str, const char* delimiter, int* count) {
    if (!str || !delimiter || !count) return NULL;

    // Count occurrences of delimiter
    int delim_count = 0;
    const char* temp = str;
    while ((temp = strstr(temp, delimiter))) {
        delim_count++;
        temp += strlen(delimiter);
    }

    *count = delim_count + 1;
    char** result = (char**)safe_malloc(*count * sizeof(char*));
    if (!result) return NULL;

    int index = 0;
    char* token;
    char* str_copy = safe_malloc(strlen(str) + 1);
    if (!str_copy) {
        safe_free(result);
        return NULL;
    }
    strcpy(str_copy, str);

    token = strtok(str_copy, delimiter);
    while (token && index < *count) {
        result[index] = safe_malloc(strlen(token) + 1);
        if (!result[index]) {
            // Cleanup on error
            for (int i = 0; i < index; i++) {
                safe_free(result[i]);
            }
            safe_free(result);
            safe_free(str_copy);
            return NULL;
        }
        strcpy(result[index], token);
        index++;
        token = strtok(NULL, delimiter);
    }

    safe_free(str_copy);
    return result;
}

char* str_join(char** strings, int count, const char* separator) {
    if (!strings || count <= 0 || !separator) return NULL;

    // Calculate total length
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i]) {
            total_len += strlen(strings[i]);
        }
        if (i < count - 1) {
            total_len += strlen(separator);
        }
    }

    char* result = (char*)safe_malloc(total_len + 1);
    if (!result) return NULL;

    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        if (strings[i]) {
            strcat(result, strings[i]);
        }
        if (i < count - 1) {
            strcat(result, separator);
        }
    }

    return result;
}

bool str_starts_with(const char* str, const char* prefix) {
    if (!str || !prefix) return false;
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool str_ends_with(const char* str, const char* suffix) {
    if (!str || !suffix) return false;

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len) return false;
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

char* str_replace(const char* str, const char* old_sub, const char* new_sub) {
    if (!str || !old_sub || !new_sub) return NULL;

    size_t old_len = strlen(old_sub);
    size_t new_len = strlen(new_sub);
    size_t str_len = strlen(str);

    // Count occurrences
    int count = 0;
    const char* temp = str;
    while ((temp = strstr(temp, old_sub))) {
        count++;
        temp += old_len;
    }

    // Calculate new string length
    size_t result_len = str_len + count * (new_len - old_len) + 1;
    char* result = (char*)safe_malloc(result_len);
    if (!result) return NULL;

    // Perform replacement
    char* dest = result;
    const char* src = str;
    while (*src) {
        if (strstr(src, old_sub) == src) {
            strcpy(dest, new_sub);
            dest += new_len;
            src += old_len;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';

    return result;
}

// Time Utilities

char* time_to_string(time_t timestamp) {
    static char buffer[20];
    struct tm* time_info = localtime(&timestamp);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
    return buffer;
}

time_t string_to_time(const char* time_str) {
    // Stub implementation - return current time to avoid strptime issues
    return time(NULL);
}

char* get_current_time_string(void) {
    return time_to_string(time(NULL));
}

time_t get_current_time(void) {
    return time(NULL);
}

double time_diff_seconds(time_t start, time_t end) {
    return difftime(end, start);
}

bool is_time_between(time_t time, time_t start, time_t end) {
    return time >= start && time <= end;
}

// File Utilities

bool file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

long get_file_size(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return -1;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

time_t get_file_modified_time(const char* filename) {
    // Simplified - would need platform-specific implementation
    return get_current_time();
}

int create_directory(const char* path) {
    // Simplified - would need platform-specific implementation
#ifdef _WIN32
    return mkdir(path);
#else
    return mkdir(path, 0755);
#endif
}

char* read_file_to_string(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)safe_malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(content, 1, size, file);
    content[read_size] = '\0';

    fclose(file);
    return content;
}

int write_string_to_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (!file) return -1;

    size_t written = fwrite(content, 1, strlen(content), file);
    fclose(file);

    return written == strlen(content) ? 0 : -1;
}

// Math Utilities

int clamp_int(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float clamp_float(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

double round_to_decimals(double value, int decimals) {
    double factor = pow(10.0, decimals);
    return round(value * factor) / factor;
}

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

float random_float(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

// Logging System

void set_log_level(LogLevel level) {
    current_log_level = level;
}

void set_log_file(const char* filename) {
    if (log_file) {
        fclose(log_file);
    }

    if (filename) {
        strncpy(log_filename, filename, sizeof(log_filename) - 1);
        log_file = fopen(log_filename, "a");
    } else {
        log_file = NULL;
    }
}

void log_message(LogLevel level, const char* format, ...) {
    if (level < current_log_level) return;

    const char* level_str;
    switch (level) {
        case LOG_DEBUG: level_str = "DEBUG"; break;
        case LOG_INFO: level_str = "INFO"; break;
        case LOG_WARN: level_str = "WARN"; break;
        case LOG_ERROR: level_str = "ERROR"; break;
        case LOG_FATAL: level_str = "FATAL"; break;
        default: level_str = "UNKNOWN";
    }

    // Format timestamp
    char timestamp[20];
    time_t now = time(NULL);
    struct tm* time_info = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);

    // Format message
    va_list args;
    va_start(args, format);
    char message[1024];
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);

    // Console output
    printf("[%s] [%s] %s\n", timestamp, level_str, message);

    // File output
    if (log_file) {
        fprintf(log_file, "[%s] [%s] %s\n", timestamp, level_str, message);
        fflush(log_file);
    }
}

void log_debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_DEBUG, format, args);
    va_end(args);
}

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_INFO, format, args);
    va_end(args);
}

void log_warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_WARN, format, args);
    va_end(args);
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_ERROR, format, args);
    va_end(args);
}

void log_fatal(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_FATAL, format, args);
    va_end(args);
}

// Memory Utilities

void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        log_fatal("Memory allocation failed for size %zu", size);
        exit(1);
    }
    return ptr;
}

void* safe_calloc(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    if (!ptr) {
        log_fatal("Memory allocation failed for %zu elements of size %zu", num, size);
        exit(1);
    }
    return ptr;
}

void* safe_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr && size > 0) {
        log_fatal("Memory reallocation failed for size %zu", size);
        exit(1);
    }
    return new_ptr;
}

void safe_free(void* ptr) {
    if (ptr) {
        free(ptr);
    }
}

// Validation Utilities

bool is_valid_ip_address(const char* ip) {
    // Simple IPv4 validation
    int parts[4];
    if (sscanf(ip, "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]) != 4) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        if (parts[i] < 0 || parts[i] > 255) {
            return false;
        }
    }

    return true;
}

bool is_valid_port(int port) {
    return port > 0 && port <= 65535;
}

bool is_valid_email(const char* email) {
    // Simple email validation
    const char* at_pos = strchr(email, '@');
    const char* dot_pos = strrchr(email, '.');

    return at_pos && dot_pos && at_pos < dot_pos;
}

bool is_numeric(const char* str) {
    if (!str || !*str) return false;

    for (const char* p = str; *p; p++) {
        if (!isdigit((unsigned char)*p) && *p != '.' && *p != '-') {
            return false;
        }
    }
    return true;
}

bool is_alphabetic(const char* str) {
    if (!str || !*str) return false;

    for (const char* p = str; *p; p++) {
        if (!isalpha((unsigned char)*p) && !isspace((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

bool is_alphanumeric(const char* str) {
    if (!str || !*str) return false;

    for (const char* p = str; *p; p++) {
        if (!isalnum((unsigned char)*p) && !isspace((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

// Hash and Encryption Utilities

unsigned long hash_string(const char* str) {
    // Simple djb2 hash
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

char* generate_uuid(void) {
    // Simple UUID-like string generation
    static char uuid[37];
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            uuid[i] = '-';
        } else {
            int r = rand() % 16;
            uuid[i] = (r < 10) ? ('0' + r) : ('a' + r - 10);
        }
    }
    uuid[36] = '\0';
    return uuid;
}

// System Utilities

char* get_os_name(void) {
#ifdef _WIN32
    return "Windows";
#elif __APPLE__
    return "macOS";
#elif __linux__
    return "Linux";
#else
    return "Unknown";
#endif
}

long get_memory_usage(void) {
    // Simplified - would need platform-specific implementation
    return 0;
}

double get_cpu_usage(void) {
    // Simplified - would need platform-specific implementation
    return 0.0;
}

char* get_executable_path(void) {
    // Simplified - would need platform-specific implementation
    return "./smarthome";
}

bool is_admin_user(void) {
#ifdef _WIN32
    // Windows admin check would go here
    return false;
#else
    return geteuid() == 0;
#endif
}

// Configuration Utilities

int parse_config_line(const char* line, char* key, char* value) {
    const char* equals_pos = strchr(line, '=');
    if (!equals_pos) return -1;

    size_t key_len = equals_pos - line;
    if (key_len >= 100) return -1;

    strncpy(key, line, key_len);
    key[key_len] = '\0';
    str_trim(key);

    strcpy(value, equals_pos + 1);
    str_trim(value);

    return 0;
}

int load_config_file(const char* filename, void (*callback)(const char* key, const char* value)) {
    FILE* file = fopen(filename, "r");
    if (!file) return -1;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == ';' || strlen(str_trim(line)) == 0) {
            continue;
        }

        char key[100], value[500];
        if (parse_config_line(line, key, value) == 0) {
            callback(key, value);
        }
    }

    fclose(file);
    return 0;
}

// Error Handling

static ErrorInfo last_error = {0};

void set_last_error(int code, const char* message, const char* function,
                   const char* file, int line) {
    last_error.code = code;
    strncpy(last_error.message, message, sizeof(last_error.message) - 1);
    last_error.timestamp = time(NULL);
    strncpy(last_error.function, function, sizeof(last_error.function) - 1);
    strncpy(last_error.file, file, sizeof(last_error.file) - 1);
    last_error.line = line;
}

ErrorInfo* get_last_error(void) {
    return &last_error;
}

void clear_error(void) {
    memset(&last_error, 0, sizeof(last_error));
}

// Performance Monitoring

void start_performance_monitor(PerformanceMetrics* metrics) {
    metrics->start_time = time(NULL);
    metrics->memory_before = get_memory_usage();
}

void end_performance_monitor(PerformanceMetrics* metrics) {
    metrics->end_time = time(NULL);
    metrics->duration_ms = time_diff_seconds(metrics->start_time, metrics->end_time) * 1000;
    metrics->memory_after = get_memory_usage();
    metrics->memory_peak = 0; // Would need more complex tracking
}

// Threading Utilities

ThreadHandle create_thread(ThreadFunction func, void* arg) {
#ifdef _WIN32
    return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, arg, 0, NULL);
#else
    ThreadHandle thread;
    pthread_create(&thread, NULL, func, arg);
    return thread;
#endif
}

void wait_thread(ThreadHandle thread) {
#ifdef _WIN32
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
#else
    pthread_join(thread, NULL);
#endif
}

void destroy_thread(ThreadHandle thread) {
#ifdef _WIN32
    CloseHandle(thread);
#else
    // pthread_join should have been called already
#endif
}

// Network Utilities

char* get_local_ip_address(void) {
    // Simplified - would need platform-specific implementation
    return "127.0.0.1";
}

bool is_port_open(const char* host, int port) {
    // Simplified - would need socket implementation
    return false;
}

char* url_encode(const char* str) {
    // Simplified URL encoding
    static char encoded[1024];
    char* dest = encoded;

    for (const char* src = str; *src && dest - encoded < sizeof(encoded) - 3; src++) {
        if (isalnum((unsigned char)*src) || *src == '-' || *src == '_' || *src == '.') {
            *dest++ = *src;
        } else {
            sprintf(dest, "%%%02X", (unsigned char)*src);
            dest += 3;
        }
    }
    *dest = '\0';
    return encoded;
}

char* url_decode(const char* str) {
    // Simplified URL decoding
    static char decoded[1024];
    char* dest = decoded;

    for (const char* src = str; *src && dest - decoded < sizeof(decoded) - 1; src++) {
        if (*src == '%' && isxdigit((unsigned char)*(src + 1)) && isxdigit((unsigned char)*(src + 2))) {
            char hex[3] = {*(src + 1), *(src + 2), '\0'};
            *dest++ = (char)strtol(hex, NULL, 16);
            src += 2;
        } else {
            *dest++ = *src;
        }
    }
    *dest = '\0';
    return decoded;
}

// JSON Utilities (Simple Implementation)

JSONObject* json_parse(const char* json_str) {
    // Simplified JSON parser - would need full implementation
    JSONObject* obj = (JSONObject*)safe_malloc(sizeof(JSONObject));
    obj->pairs = NULL;
    obj->count = 0;
    return obj;
}

char* json_stringify(JSONObject* obj) {
    // Simplified JSON stringifier
    return safe_malloc(1); // Empty string
}

void json_free(JSONObject* obj) {
    if (obj) {
        safe_free(obj);
    }
}

const char* json_get_string(JSONObject* obj, const char* key) {
    return ""; // Simplified
}

int json_get_int(JSONObject* obj, const char* key) {
    return 0; // Simplified
}

double json_get_double(JSONObject* obj, const char* key) {
    return 0.0; // Simplified
}

bool json_get_bool(JSONObject* obj, const char* key) {
    return false; // Simplified
}