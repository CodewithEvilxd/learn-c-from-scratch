/*
 * IoT Smart Home - Device Management Header
 * Device types, states, and management functions
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <time.h>
#include <stdbool.h>

// Device Types
typedef enum {
    DEVICE_LIGHT,
    DEVICE_THERMOSTAT,
    DEVICE_CAMERA,
    DEVICE_DOOR_LOCK,
    DEVICE_MOTION_SENSOR,
    DEVICE_SMOKE_DETECTOR,
    DEVICE_SMART_PLUG,
    DEVICE_TEMPERATURE_SENSOR,
    DEVICE_HUMIDITY_SENSOR,
    DEVICE_ENERGY_METER
} DeviceType;

// Device States
typedef enum {
    DEVICE_OFFLINE,
    DEVICE_ONLINE,
    DEVICE_ACTIVE,
    DEVICE_INACTIVE,
    DEVICE_ERROR
} DeviceState;

// Device Commands
typedef enum {
    CMD_TURN_ON,
    CMD_TURN_OFF,
    CMD_SET_BRIGHTNESS,
    CMD_SET_TEMPERATURE,
    CMD_SET_COLOR,
    CMD_LOCK,
    CMD_UNLOCK,
    CMD_CAPTURE_IMAGE,
    CMD_GET_STATUS,
    CMD_RESET
} DeviceCommand;

// Device Structure
typedef struct {
    int id;
    char name[50];
    char location[50];
    DeviceType type;
    DeviceState state;
    time_t last_seen;
    time_t installed_date;
    void* device_data;  // Type-specific data
    bool is_active;
} Device;

// Light Device Data
typedef struct {
    int brightness;     // 0-100
    int red, green, blue; // RGB values
    bool motion_activated;
    time_t last_motion;
} LightData;

// Thermostat Device Data
typedef struct {
    float current_temp;
    float target_temp;
    float humidity;
    bool heating;
    bool cooling;
    char mode[20];      // "heat", "cool", "auto", "off"
} ThermostatData;

// Camera Device Data
typedef struct {
    bool recording;
    bool motion_detection;
    int resolution_width;
    int resolution_height;
    time_t last_capture;
    char last_image_path[256];
} CameraData;

// Door Lock Device Data
typedef struct {
    bool locked;
    bool auto_lock;
    time_t last_unlock;
    char last_access_user[50];
    int failed_attempts;
} DoorLockData;

// Sensor Device Data
typedef struct {
    float current_value;
    float min_threshold;
    float max_threshold;
    bool alert_active;
    time_t last_alert;
    char unit[10];      // "C", "%", "lux", etc.
} SensorData;

// Energy Meter Device Data
typedef struct {
    float current_power;    // Watts
    float daily_consumption; // kWh
    float monthly_consumption; // kWh
    float voltage;          // Volts
    float current;          // Amperes
    time_t last_reading;
} EnergyMeterData;

// Device Manager
typedef struct {
    Device* devices;
    int device_count;
    int max_devices;
    int next_id;
} DeviceManager;

// Function Prototypes

// Device Management
DeviceManager* device_manager_create(int max_devices);
void device_manager_destroy(DeviceManager* manager);
int device_add(DeviceManager* manager, const char* name, const char* location, DeviceType type);
int device_remove(DeviceManager* manager, int device_id);
Device* device_find_by_id(DeviceManager* manager, int device_id);
Device* device_find_by_name(DeviceManager* manager, const char* name);

// Device Operations
int device_execute_command(Device* device, DeviceCommand cmd, void* params);
int device_get_status(Device* device, char* status_buffer, size_t buffer_size);
int device_update_data(Device* device);

// Device Type Specific Functions
int light_set_brightness(Device* device, int brightness);
int light_set_color(Device* device, int red, int green, int blue);
int thermostat_set_temperature(Device* device, float temperature);
int thermostat_set_mode(Device* device, const char* mode);
int camera_start_recording(Device* device);
int camera_capture_image(Device* device);
int door_lock_toggle(Device* device, bool lock);
int sensor_get_reading(Device* device, float* value);

// Utility Functions
const char* device_type_to_string(DeviceType type);
const char* device_state_to_string(DeviceState state);
const char* device_command_to_string(DeviceCommand cmd);
DeviceType string_to_device_type(const char* str);
DeviceCommand string_to_device_command(const char* str);

// Data Persistence
int device_save_to_file(DeviceManager* manager, const char* filename);
int device_load_from_file(DeviceManager* manager, const char* filename);

// Monitoring and Statistics
int device_get_online_count(DeviceManager* manager);
int device_get_by_type_count(DeviceManager* manager, DeviceType type);
int device_get_recently_active(DeviceManager* manager, Device** devices, int max_count, time_t since);

// Error Handling
typedef enum {
    DEVICE_SUCCESS = 0,
    DEVICE_ERROR_INVALID_ID = -1,
    DEVICE_ERROR_INVALID_TYPE = -2,
    DEVICE_ERROR_INVALID_COMMAND = -3,
    DEVICE_ERROR_OFFLINE = -4,
    DEVICE_ERROR_MEMORY = -5,
    DEVICE_ERROR_FILE_IO = -6,
    DEVICE_ERROR_INVALID_PARAMS = -7
} DeviceError;

const char* device_error_to_string(DeviceError error);

#endif // DEVICE_H