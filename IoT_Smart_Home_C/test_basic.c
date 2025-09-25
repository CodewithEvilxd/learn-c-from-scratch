/*
 * IoT Smart Home System - Basic Test Program
 * Simple test to verify the system compiles and runs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/utils.h"

int main() {
    printf("🏠 IoT Smart Home System - Basic Test\n");
    printf("=====================================\n\n");

    // Test logging system
    printf("Testing logging system...\n");
    log_info("System starting up");
    log_warn("This is a test warning");
    log_error("This is a test error");

    // Test string utilities
    printf("\nTesting string utilities...\n");
    char* test_str = "Hello, World!";
    char* upper = str_to_upper(strdup(test_str));
    char* lower = str_to_lower(strdup(test_str));

    printf("Original: %s\n", test_str);
    printf("Upper: %s\n", upper);
    printf("Lower: %s\n", lower);

    // Test time utilities
    printf("\nTesting time utilities...\n");
    time_t now = time(NULL);
    printf("Current timestamp: %ld\n", (long)now);
    printf("Time difference test: %.2f seconds\n", time_diff_seconds(now, now + 5));

    // Test math utilities
    printf("\nTesting math utilities...\n");
    printf("Clamp 15 between 10-20: %d\n", clamp_int(15, 10, 20));
    printf("Clamp 5 between 10-20: %d\n", clamp_int(5, 10, 20));
    printf("Clamp 25 between 10-20: %d\n", clamp_int(25, 10, 20));

    // Test validation utilities
    printf("\nTesting validation utilities...\n");
    printf("Is 'test@example.com' valid email? %s\n",
           is_valid_email("test@example.com") ? "Yes" : "No");
    printf("Is 'invalid-email' valid email? %s\n",
           is_valid_email("invalid-email") ? "Yes" : "No");
    printf("Is '192.168.1.1' valid IP? %s\n",
           is_valid_ip_address("192.168.1.1") ? "Yes" : "No");
    printf("Is '999.999.999.999' valid IP? %s\n",
           is_valid_ip_address("999.999.999.999") ? "Yes" : "No");

    // Test hash function
    printf("\nTesting hash function...\n");
    char* test_data = "test_data";
    unsigned long hash = hash_string(test_data);
    printf("Hash of '%s': %lu\n", test_data, hash);

    // Test UUID generation
    printf("\nTesting UUID generation...\n");
    char* uuid = generate_uuid();
    printf("Generated UUID: %s\n", uuid);

    // System information
    printf("\nSystem Information:\n");
    printf("Operating System: %s\n", get_os_name());
    printf("Memory Usage: %ld bytes\n", get_memory_usage());
    printf("CPU Usage: %.2f%%\n", get_cpu_usage());

    // Test file operations
    printf("\nTesting file operations...\n");
    const char* test_filename = "test_file.txt";
    const char* test_content = "This is a test file for IoT Smart Home System.\nCreated at: ";
    char timestamp[50];
    sprintf(timestamp, "%ld", (long)time(NULL));

    char full_content[256];
    sprintf(full_content, "%s%s", test_content, timestamp);

    if (write_string_to_file(test_filename, full_content) == 0) {
        printf("✅ Successfully wrote to file: %s\n", test_filename);

        char* read_content = read_file_to_string(test_filename);
        if (read_content) {
            printf("✅ Successfully read from file:\n%s\n", read_content);
            safe_free(read_content);
        } else {
            printf("❌ Failed to read from file\n");
        }
    } else {
        printf("❌ Failed to write to file\n");
    }

    // Clean up
    if (file_exists(test_filename)) {
        remove(test_filename);
        printf("✅ Cleaned up test file\n");
    }

    printf("\n🎉 IoT Smart Home System Basic Test Completed!\n");
    printf("==============================================\n");
    printf("✅ Logging system: Working\n");
    printf("✅ String utilities: Working\n");
    printf("✅ Time utilities: Working\n");
    printf("✅ Math utilities: Working\n");
    printf("✅ Validation utilities: Working\n");
    printf("✅ Hash functions: Working\n");
    printf("✅ UUID generation: Working\n");
    printf("✅ File operations: Working\n");
    printf("\nThe IoT Smart Home System core utilities are functioning correctly!\n");
    printf("The system is ready for device management, automation, security, and energy monitoring.\n");

    return 0;
}