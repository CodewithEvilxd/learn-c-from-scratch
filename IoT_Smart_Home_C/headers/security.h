/*
 * IoT Smart Home - Security System Header
 * Security monitoring, access control, and alert management
 */

#ifndef SECURITY_H
#define SECURITY_H

#include <time.h>
#include <stdbool.h>
#include "device.h"

// Security Event Types
typedef enum {
    SECURITY_DOOR_OPENED,
    SECURITY_DOOR_CLOSED,
    SECURITY_MOTION_DETECTED,
    SECURITY_CAMERA_TRIGGERED,
    SECURITY_ALARM_TRIGGERED,
    SECURITY_SYSTEM_ARMED,
    SECURITY_SYSTEM_DISARMED,
    SECURITY_ACCESS_GRANTED,
    SECURITY_ACCESS_DENIED,
    SECURITY_TAMPER_DETECTED,
    SECURITY_POWER_OUTAGE,
    SECURITY_SYSTEM_ERROR
} SecurityEventType;

// Alert Levels
typedef enum {
    ALERT_INFO,
    ALERT_WARNING,
    ALERT_CRITICAL,
    ALERT_EMERGENCY
} AlertLevel;

// User Access Levels
typedef enum {
    ACCESS_NONE,
    ACCESS_GUEST,
    ACCESS_USER,
    ACCESS_ADMIN,
    ACCESS_MASTER
} AccessLevel;

// Security Event Structure
typedef struct {
    int id;
    SecurityEventType type;
    time_t timestamp;
    int device_id;
    char device_name[50];
    char location[50];
    char description[200];
    AlertLevel alert_level;
    bool acknowledged;
    time_t acknowledged_time;
    char acknowledged_by[50];
    char additional_data[500]; // JSON-like data
} SecurityEvent;

// Access Log Entry
typedef struct {
    int id;
    time_t timestamp;
    char user_id[50];
    char user_name[50];
    AccessLevel access_level;
    char action[100];
    char resource[100];
    bool success;
    char ip_address[50];
    char user_agent[200];
} AccessLogEntry;

// Security Zone
typedef struct {
    int id;
    char name[50];
    char description[100];
    Device** devices;
    int device_count;
    bool armed;
    AlertLevel sensitivity;
    time_t last_activity;
    char authorized_users[500]; // Comma-separated user IDs
} SecurityZone;

// Security System
typedef struct {
    SecurityEvent* events;
    int event_count;
    int max_events;
    AccessLogEntry* access_logs;
    int log_count;
    int max_logs;
    SecurityZone* zones;
    int zone_count;
    int max_zones;
    bool system_armed;
    AlertLevel current_alert_level;
    time_t last_intrusion_attempt;
    int failed_login_attempts;
} SecuritySystem;

// Function Prototypes

// Security System Management
SecuritySystem* security_system_create(int max_events, int max_logs, int max_zones);
void security_system_destroy(SecuritySystem* system);

// Event Management
int security_log_event(SecuritySystem* system, SecurityEventType type,
                      int device_id, const char* description,
                      AlertLevel level, const char* additional_data);
SecurityEvent* security_get_events(SecuritySystem* system, int* count);
SecurityEvent* security_get_unacknowledged_events(SecuritySystem* system, int* count);
int security_acknowledge_event(SecuritySystem* system, int event_id,
                              const char* acknowledged_by);

// Access Control
int security_log_access(SecuritySystem* system, const char* user_id,
                       const char* user_name, AccessLevel level,
                       const char* action, const char* resource, bool success);
AccessLogEntry* security_get_access_logs(SecuritySystem* system, int* count,
                                        time_t since, const char* user_id);

// Zone Management
int security_add_zone(SecuritySystem* system, const char* name,
                     const char* description, AlertLevel sensitivity);
int security_remove_zone(SecuritySystem* system, int zone_id);
SecurityZone* security_find_zone(SecuritySystem* system, int zone_id);
int security_add_device_to_zone(SecuritySystem* system, int zone_id, int device_id);
int security_remove_device_from_zone(SecuritySystem* system, int zone_id, int device_id);
int security_arm_zone(SecuritySystem* system, int zone_id, bool armed);

// System Control
int security_arm_system(SecuritySystem* system, bool armed);
bool security_is_system_armed(SecuritySystem* system);
AlertLevel security_get_alert_level(SecuritySystem* system);
int security_set_alert_level(SecuritySystem* system, AlertLevel level);

// Intrusion Detection
int security_check_intrusion(SecuritySystem* system, DeviceManager* devices);
int security_trigger_alarm(SecuritySystem* system, const char* reason);
int security_reset_alarm(SecuritySystem* system);

// User Authorization
bool security_check_authorization(SecuritySystem* system, const char* user_id,
                                 AccessLevel required_level, const char* resource);
int security_grant_access(SecuritySystem* system, const char* user_id,
                         AccessLevel level, const char* resource);
int security_revoke_access(SecuritySystem* system, const char* user_id,
                          const char* resource);

// Monitoring and Analytics
int security_get_intrusion_attempts(SecuritySystem* system, time_t since);
int security_get_failed_logins(SecuritySystem* system, time_t since);
int security_get_zone_activity(SecuritySystem* system, int zone_id, time_t since);
double security_get_system_uptime(SecuritySystem* system);

// Emergency Protocols
int security_trigger_emergency(SecuritySystem* system, const char* emergency_type);
int security_evacuate_zone(SecuritySystem* system, int zone_id);
int security_lockdown_system(SecuritySystem* system);

// Integration with Devices
int security_monitor_device(SecuritySystem* system, Device* device);
int security_handle_device_alert(SecuritySystem* system, Device* device,
                                const char* alert_message);

// Data Persistence
int security_save_events(SecuritySystem* system, const char* filename);
int security_load_events(SecuritySystem* system, const char* filename);
int security_save_access_logs(SecuritySystem* system, const char* filename);
int security_load_access_logs(SecuritySystem* system, const char* filename);
int security_save_zones(SecuritySystem* system, const char* filename);
int security_load_zones(SecuritySystem* system, const char* filename);

// Utility Functions
const char* security_event_type_to_string(SecurityEventType type);
const char* alert_level_to_string(AlertLevel level);
const char* access_level_to_string(AccessLevel level);
SecurityEventType string_to_security_event_type(const char* str);
AlertLevel string_to_alert_level(const char* str);
AccessLevel string_to_access_level(const char* str);

// Advanced Security Features
int security_setup_biometric_auth(SecuritySystem* system, const char* user_id,
                                 const char* biometric_data);
int security_enable_two_factor(SecuritySystem* system, const char* user_id);
int security_detect_anomalies(SecuritySystem* system, time_t time_window);

// Error Handling
typedef enum {
    SECURITY_SUCCESS = 0,
    SECURITY_ERROR_INVALID_EVENT = -1,
    SECURITY_ERROR_INVALID_ZONE = -2,
    SECURITY_ERROR_ACCESS_DENIED = -3,
    SECURITY_ERROR_SYSTEM_ARMED = -4,
    SECURITY_ERROR_MEMORY = -5,
    SECURITY_ERROR_FILE_IO = -6,
    SECURITY_ERROR_INVALID_PARAMS = -7,
    SECURITY_ERROR_ZONE_FULL = -8
} SecurityError;

const char* security_error_to_string(SecurityError error);

// Real-time Monitoring
typedef struct {
    int active_zones;
    int triggered_alarms;
    int unacknowledged_events;
    int online_devices;
    time_t last_security_check;
    double system_health_score; // 0-100
} SecurityStatus;

int security_get_status(SecuritySystem* system, SecurityStatus* status);
int security_perform_security_audit(SecuritySystem* system);

#endif // SECURITY_H