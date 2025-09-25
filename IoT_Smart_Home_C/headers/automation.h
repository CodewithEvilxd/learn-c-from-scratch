/*
 * IoT Smart Home - Automation Engine Header
 * Rule-based automation and scheduling system
 */

#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <time.h>
#include <stdbool.h>
#include "device.h"

// Condition Types
typedef enum {
    CONDITION_DEVICE_STATE,
    CONDITION_TIME_EQUALS,
    CONDITION_TIME_RANGE,
    CONDITION_SENSOR_VALUE,
    CONDITION_ENERGY_USAGE,
    CONDITION_SECURITY_EVENT,
    CONDITION_USER_PRESENCE
} ConditionType;

// Action Types
typedef enum {
    ACTION_DEVICE_COMMAND,
    ACTION_SEND_NOTIFICATION,
    ACTION_LOG_EVENT,
    ACTION_TRIGGER_SCENE,
    ACTION_ADJUST_THERMOSTAT,
    ACTION_SECURITY_ALERT
} ActionType;

// Operator Types
typedef enum {
    OP_EQUALS,
    OP_NOT_EQUALS,
    OP_GREATER_THAN,
    OP_LESS_THAN,
    OP_GREATER_EQUAL,
    OP_LESS_EQUAL,
    OP_CONTAINS,
    OP_NOT_CONTAINS
} OperatorType;

// Condition Structure
typedef struct {
    ConditionType type;
    int device_id;
    char parameter[50];
    OperatorType op_type;  // Renamed from 'operator' to avoid C keyword conflict
    char value[100];
    bool inverted;      // NOT condition
} Condition;

// Action Structure
typedef struct {
    ActionType type;
    int device_id;
    DeviceCommand command;
    char parameters[200];
    char message[200];  // For notifications
} Action;

// Automation Rule Structure
typedef struct {
    int id;
    char name[100];
    char description[200];
    Condition* conditions;
    int condition_count;
    Action* actions;
    int action_count;
    bool enabled;
    bool triggered;
    time_t last_triggered;
    time_t created_date;
    int trigger_count;
    char schedule[100]; // Cron-like schedule
} AutomationRule;

// Scene Structure (Group of actions)
typedef struct {
    int id;
    char name[100];
    char description[200];
    Action* actions;
    int action_count;
    bool is_active;
    time_t created_date;
    int usage_count;
} Scene;

// Automation Manager
typedef struct {
    AutomationRule* rules;
    int rule_count;
    int max_rules;
    Scene* scenes;
    int scene_count;
    int max_scenes;
    int next_rule_id;
    int next_scene_id;
} AutomationManager;

// Schedule Structure
typedef struct {
    int minute;     // 0-59, -1 for any
    int hour;       // 0-23, -1 for any
    int day;        // 1-31, -1 for any
    int month;      // 1-12, -1 for any
    int weekday;    // 0-6 (Sun-Sat), -1 for any
} Schedule;

// Function Prototypes

// Automation Manager
AutomationManager* automation_manager_create(int max_rules, int max_scenes);
void automation_manager_destroy(AutomationManager* manager);

// Rule Management
int automation_add_rule(AutomationManager* manager, const char* name,
                       const char* description, Condition* conditions,
                       int condition_count, Action* actions, int action_count);
int automation_remove_rule(AutomationManager* manager, int rule_id);
AutomationRule* automation_find_rule(AutomationManager* manager, int rule_id);
int automation_enable_rule(AutomationManager* manager, int rule_id, bool enabled);
int automation_update_rule_schedule(AutomationManager* manager, int rule_id,
                                   const char* schedule);

// Scene Management
int automation_add_scene(AutomationManager* manager, const char* name,
                        const char* description, Action* actions, int action_count);
int automation_remove_scene(AutomationManager* manager, int scene_id);
Scene* automation_find_scene(AutomationManager* manager, int scene_id);
int automation_activate_scene(AutomationManager* manager, int scene_id);

// Rule Processing
int automation_evaluate_rules(AutomationManager* manager, DeviceManager* devices);
int automation_check_schedule(const char* schedule, time_t current_time);
bool automation_evaluate_condition(Condition* condition, DeviceManager* devices);
int automation_execute_actions(Action* actions, int action_count, DeviceManager* devices);

// Condition and Action Builders
Condition* automation_create_device_condition(int device_id, const char* parameter,
                                            OperatorType op, const char* value);
Condition* automation_create_time_condition(ConditionType type, const char* time_value);
Condition* automation_create_sensor_condition(int device_id, OperatorType op, float threshold);

Action* automation_create_device_action(int device_id, DeviceCommand cmd, const char* params);
Action* automation_create_notification_action(const char* message);
Action* automation_create_scene_action(int scene_id);

// Utility Functions
int automation_parse_schedule(const char* schedule_str, Schedule* schedule);
bool automation_schedule_matches(const Schedule* schedule, struct tm* time_info);
void automation_free_condition(Condition* condition);
void automation_free_action(Action* action);

// Data Persistence
int automation_save_rules(AutomationManager* manager, const char* filename);
int automation_load_rules(AutomationManager* manager, const char* filename);
int automation_save_scenes(AutomationManager* manager, const char* filename);
int automation_load_scenes(AutomationManager* manager, const char* filename);

// Statistics and Monitoring
int automation_get_active_rules(AutomationManager* manager);
int automation_get_triggered_today(AutomationManager* manager);
int automation_get_rule_stats(AutomationManager* manager, int rule_id,
                             int* trigger_count, time_t* last_triggered);

// Error Handling
typedef enum {
    AUTOMATION_SUCCESS = 0,
    AUTOMATION_ERROR_INVALID_RULE = -1,
    AUTOMATION_ERROR_INVALID_CONDITION = -2,
    AUTOMATION_ERROR_INVALID_ACTION = -3,
    AUTOMATION_ERROR_RULE_NOT_FOUND = -4,
    AUTOMATION_ERROR_SCENE_NOT_FOUND = -5,
    AUTOMATION_ERROR_MEMORY = -6,
    AUTOMATION_ERROR_FILE_IO = -7,
    AUTOMATION_ERROR_INVALID_SCHEDULE = -8
} AutomationError;

const char* automation_error_to_string(AutomationError error);

// Advanced Features
int automation_create_complex_rule(AutomationManager* manager,
                                  const char* name, const char* logic_expression,
                                  Action* actions, int action_count);
bool automation_evaluate_logic_expression(const char* expression,
                                        Condition* conditions, int count);

// Integration with other systems
int automation_trigger_by_event(AutomationManager* manager,
                               const char* event_type, const char* event_data,
                               DeviceManager* devices);
int automation_schedule_maintenance(AutomationManager* manager);

#endif // AUTOMATION_H