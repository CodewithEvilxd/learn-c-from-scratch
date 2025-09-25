/*
 * IoT Smart Home - Data Storage Header
 * Configuration and data persistence management
 */

#ifndef STORAGE_H
#define STORAGE_H

#include <time.h>
#include <stdbool.h>

// Storage Formats
typedef enum {
    FORMAT_JSON,
    FORMAT_XML,
    FORMAT_BINARY,
    FORMAT_CSV,
    FORMAT_INI
} StorageFormat;

// Storage Types
typedef enum {
    STORAGE_CONFIG,
    STORAGE_DEVICE_DATA,
    STORAGE_AUTOMATION_RULES,
    STORAGE_SECURITY_EVENTS,
    STORAGE_ENERGY_READINGS,
    STORAGE_SYSTEM_LOGS
} StorageType;

// Configuration Entry
typedef struct {
    char key[100];
    char value[500];
    char section[50];
    time_t last_modified;
    bool is_encrypted;
} ConfigEntry;

// Storage Manager
typedef struct {
    ConfigEntry* config_entries;
    int config_count;
    int max_config_entries;
    char config_file[256];
    StorageFormat format;
    bool auto_save;
    time_t last_save;
    char backup_directory[256];
} StorageManager;

// Function Prototypes

// Storage Manager
StorageManager* storage_manager_create(const char* config_file, StorageFormat format);
void storage_manager_destroy(StorageManager* manager);

// Configuration Management
int storage_set_config(StorageManager* manager, const char* section,
                      const char* key, const char* value);
const char* storage_get_config(StorageManager* manager, const char* section,
                              const char* key);
int storage_remove_config(StorageManager* manager, const char* section,
                         const char* key);
int storage_list_config_section(StorageManager* manager, const char* section,
                               char** keys, int* count);

// File Operations
int storage_save_config(StorageManager* manager);
int storage_load_config(StorageManager* manager);
int storage_backup_config(StorageManager* manager);
int storage_restore_config(StorageManager* manager, const char* backup_file);

// Data Export/Import
int storage_export_data(StorageManager* manager, StorageType type,
                       const char* filename, StorageFormat format);
int storage_import_data(StorageManager* manager, StorageType type,
                       const char* filename);

// Utility Functions
int storage_validate_config_file(const char* filename);
int storage_create_default_config(const char* filename);
int storage_migrate_config_format(const char* old_file, const char* new_file,
                                 StorageFormat old_format, StorageFormat new_format);

// Error Handling
typedef enum {
    STORAGE_SUCCESS = 0,
    STORAGE_ERROR_FILE_NOT_FOUND = -1,
    STORAGE_ERROR_INVALID_FORMAT = -2,
    STORAGE_ERROR_PERMISSION_DENIED = -3,
    STORAGE_ERROR_CORRUPTED_DATA = -4,
    STORAGE_ERROR_MEMORY = -5,
    STORAGE_ERROR_INVALID_KEY = -6
} StorageError;

const char* storage_error_to_string(StorageError error);

#endif // STORAGE_H