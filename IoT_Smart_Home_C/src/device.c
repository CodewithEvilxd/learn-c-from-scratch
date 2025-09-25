/*
 * IoT Smart Home - Device Management Implementation
 * Device lifecycle, control, and monitoring functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/device.h"
#include "../headers/utils.h"

// Device Manager Implementation

DeviceManager* device_manager_create(int max_devices) {
    DeviceManager* manager = (DeviceManager*)safe_malloc(sizeof(DeviceManager));
    if (!manager) return NULL;

    manager->devices = (Device*)safe_calloc(max_devices, sizeof(Device));
    if (!manager->devices) {
        safe_free(manager);
        return NULL;
    }

    manager->device_count = 0;
    manager->max_devices = max_devices;
    manager->next_id = 1;

    log_info("Device manager created with capacity for %d devices", max_devices);
    return manager;
}

void device_manager_destroy(DeviceManager* manager) {
    if (!manager) return;

    // Free device-specific data
    for (int i = 0; i < manager->device_count; i++) {
        if (manager->devices[i].device_data) {
            safe_free(manager->devices[i].device_data);
        }
    }

    safe_free(manager->devices);
    safe_free(manager);
    log_info("Device manager destroyed");
}

int device_add(DeviceManager* manager, const char* name, const char* location, DeviceType type) {
    if (!manager || !name || !location || manager->device_count >= manager->max_devices) {
        return DEVICE_ERROR_INVALID_PARAMS;
    }

    // Check for duplicate names
    for (int i = 0; i < manager->device_count; i++) {
        if (strcmp(manager->devices[i].name, name) == 0) {
            return DEVICE_ERROR_INVALID_PARAMS;
        }
    }

    Device* device = &manager->devices[manager->device_count];
    device->id = manager->next_id++;
    strncpy(device->name, name, sizeof(device->name) - 1);
    strncpy(device->location, location, sizeof(device->location) - 1);
    device->type = type;
    device->state = DEVICE_OFFLINE;
    device->last_seen = 0;
    device->installed_date = time(NULL);
    device->device_data = NULL;
    device->is_active = false;

    // Initialize device-specific data
    switch (type) {
        case DEVICE_LIGHT:
            device->device_data = safe_malloc(sizeof(LightData));
            if (device->device_data) {
                LightData* light = (LightData*)device->device_data;
                light->brightness = 0;
                light->red = 255;
                light->green = 255;
                light->blue = 255;
                light->motion_activated = false;
                light->last_motion = 0;
            }
            break;

        case DEVICE_THERMOSTAT:
            device->device_data = safe_malloc(sizeof(ThermostatData));
            if (device->device_data) {
                ThermostatData* thermo = (ThermostatData*)device->device_data;
                thermo->current_temp = 22.0;
                thermo->target_temp = 22.0;
                thermo->humidity = 50.0;
                thermo->heating = false;
                thermo->cooling = false;
                strcpy(thermo->mode, "auto");
            }
            break;

        case DEVICE_CAMERA:
            device->device_data = safe_malloc(sizeof(CameraData));
            if (device->device_data) {
                CameraData* camera = (CameraData*)device->device_data;
                camera->recording = false;
                camera->motion_detection = true;
                camera->resolution_width = 1920;
                camera->resolution_height = 1080;
                camera->last_capture = 0;
                strcpy(camera->last_image_path, "");
            }
            break;

        case DEVICE_DOOR_LOCK:
            device->device_data = safe_malloc(sizeof(DoorLockData));
            if (device->device_data) {
                DoorLockData* lock = (DoorLockData*)device->device_data;
                lock->locked = true;
                lock->auto_lock = true;
                lock->last_unlock = 0;
                strcpy(lock->last_access_user, "");
                lock->failed_attempts = 0;
            }
            break;

        case DEVICE_MOTION_SENSOR:
        case DEVICE_TEMPERATURE_SENSOR:
        case DEVICE_HUMIDITY_SENSOR:
            device->device_data = safe_malloc(sizeof(SensorData));
            if (device->device_data) {
                SensorData* sensor = (SensorData*)device->device_data;
                sensor->current_value = 0.0;
                sensor->min_threshold = 0.0;
                sensor->max_threshold = 100.0;
                sensor->alert_active = false;
                sensor->last_alert = 0;
                switch (type) {
                    case DEVICE_TEMPERATURE_SENSOR:
                        strcpy(sensor->unit, "C");
                        sensor->current_value = 22.0;
                        break;
                    case DEVICE_HUMIDITY_SENSOR:
                        strcpy(sensor->unit, "%");
                        sensor->current_value = 50.0;
                        break;
                    case DEVICE_MOTION_SENSOR:
                        strcpy(sensor->unit, "motion");
                        sensor->current_value = 0.0;
                        break;
                    default:
                        strcpy(sensor->unit, "");
                }
            }
            break;

        case DEVICE_ENERGY_METER:
            device->device_data = safe_malloc(sizeof(EnergyMeterData));
            if (device->device_data) {
                EnergyMeterData* meter = (EnergyMeterData*)device->device_data;
                meter->current_power = 0.0;
                meter->daily_consumption = 0.0;
                meter->monthly_consumption = 0.0;
                meter->voltage = 220.0;
                meter->current = 0.0;
                meter->last_reading = time(NULL);
            }
            break;

        default:
            // No specific data needed
            break;
    }

    manager->device_count++;
    log_info("Device added: %s (%s) - ID: %d", name, location, device->id);
    return device->id;
}

int device_remove(DeviceManager* manager, int device_id) {
    if (!manager) return DEVICE_ERROR_INVALID_PARAMS;

    for (int i = 0; i < manager->device_count; i++) {
        if (manager->devices[i].id == device_id) {
            // Free device-specific data
            if (manager->devices[i].device_data) {
                safe_free(manager->devices[i].device_data);
            }

            // Shift remaining devices
            for (int j = i; j < manager->device_count - 1; j++) {
                manager->devices[j] = manager->devices[j + 1];
            }

            manager->device_count--;
            log_info("Device removed: ID %d", device_id);
            return DEVICE_SUCCESS;
        }
    }

    return DEVICE_ERROR_INVALID_ID;
}

Device* device_find_by_id(DeviceManager* manager, int device_id) {
    if (!manager) return NULL;

    for (int i = 0; i < manager->device_count; i++) {
        if (manager->devices[i].id == device_id) {
            return &manager->devices[i];
        }
    }

    return NULL;
}

Device* device_find_by_name(DeviceManager* manager, const char* name) {
    if (!manager || !name) return NULL;

    for (int i = 0; i < manager->device_count; i++) {
        if (strcmp(manager->devices[i].name, name) == 0) {
            return &manager->devices[i];
        }
    }

    return NULL;
}

// Device Operations

int device_execute_command(Device* device, DeviceCommand cmd, void* params) {
    if (!device) return DEVICE_ERROR_INVALID_PARAMS;

    device->last_seen = time(NULL);
    device->state = DEVICE_ACTIVE;

    switch (device->type) {
        case DEVICE_LIGHT:
            return device_execute_light_command(device, cmd, params);
        case DEVICE_THERMOSTAT:
            return device_execute_thermostat_command(device, cmd, params);
        case DEVICE_CAMERA:
            return device_execute_camera_command(device, cmd, params);
        case DEVICE_DOOR_LOCK:
            return device_execute_lock_command(device, cmd, params);
        case DEVICE_SMART_PLUG:
            return device_execute_plug_command(device, cmd, params);
        default:
            return device_execute_generic_command(device, cmd, params);
    }
}

int device_execute_light_command(Device* device, DeviceCommand cmd, void* params) {
    LightData* light = (LightData*)device->device_data;
    if (!light) return DEVICE_ERROR_INVALID_PARAMS;

    switch (cmd) {
        case CMD_TURN_ON:
            // Simulate turning on light
            log_info("Light %s turned on", device->name);
            return DEVICE_SUCCESS;

        case CMD_TURN_OFF:
            // Simulate turning off light
            log_info("Light %s turned off", device->name);
            return DEVICE_SUCCESS;

        case CMD_SET_BRIGHTNESS:
            if (params) {
                int brightness = atoi((char*)params);
                if (brightness >= 0 && brightness <= 100) {
                    light->brightness = brightness;
                    log_info("Light %s brightness set to %d%%", device->name, brightness);
                    return DEVICE_SUCCESS;
                }
            }
            return DEVICE_ERROR_INVALID_PARAMS;

        case CMD_SET_COLOR:
            if (params) {
                // Parse RGB values: "255,255,255"
                int r, g, b;
                if (sscanf((char*)params, "%d,%d,%d", &r, &g, &b) == 3) {
                    light->red = clamp_int(r, 0, 255);
                    light->green = clamp_int(g, 0, 255);
                    light->blue = clamp_int(b, 0, 255);
                    log_info("Light %s color set to RGB(%d,%d,%d)", device->name, r, g, b);
                    return DEVICE_SUCCESS;
                }
            }
            return DEVICE_ERROR_INVALID_PARAMS;

        default:
            return DEVICE_ERROR_INVALID_COMMAND;
    }
}

int device_execute_thermostat_command(Device* device, DeviceCommand cmd, void* params) {
    ThermostatData* thermo = (ThermostatData*)device->device_data;
    if (!thermo) return DEVICE_ERROR_INVALID_PARAMS;

    switch (cmd) {
        case CMD_SET_TEMPERATURE:
            if (params) {
                float temp = atof((char*)params);
                if (temp >= 10.0 && temp <= 35.0) {
                    thermo->target_temp = temp;
                    log_info("Thermostat %s target temperature set to %.1f°C", device->name, temp);
                    return DEVICE_SUCCESS;
                }
            }
            return DEVICE_ERROR_INVALID_PARAMS;

        case CMD_SET_BRIGHTNESS: // Reusing for mode setting
            if (params) {
                const char* mode = (char*)params;
                if (strcmp(mode, "heat") == 0 || strcmp(mode, "cool") == 0 ||
                    strcmp(mode, "auto") == 0 || strcmp(mode, "off") == 0) {
                    strcpy(thermo->mode, mode);
                    log_info("Thermostat %s mode set to %s", device->name, mode);
                    return DEVICE_SUCCESS;
                }
            }
            return DEVICE_ERROR_INVALID_PARAMS;

        default:
            return DEVICE_ERROR_INVALID_COMMAND;
    }
}

int device_execute_camera_command(Device* device, DeviceCommand cmd, void* params) {
    CameraData* camera = (CameraData*)device->device_data;
    if (!camera) return DEVICE_ERROR_INVALID_PARAMS;

    switch (cmd) {
        case CMD_CAPTURE_IMAGE:
            camera->last_capture = time(NULL);
            sprintf(camera->last_image_path, "capture_%s_%ld.jpg", device->name, camera->last_capture);
            log_info("Camera %s captured image: %s", device->name, camera->last_image_path);
            return DEVICE_SUCCESS;

        case CMD_TURN_ON: // Start recording
            camera->recording = true;
            log_info("Camera %s started recording", device->name);
            return DEVICE_SUCCESS;

        case CMD_TURN_OFF: // Stop recording
            camera->recording = false;
            log_info("Camera %s stopped recording", device->name);
            return DEVICE_SUCCESS;

        default:
            return DEVICE_ERROR_INVALID_COMMAND;
    }
}

int device_execute_lock_command(Device* device, DeviceCommand cmd, void* params) {
    DoorLockData* lock = (DoorLockData*)device->device_data;
    if (!lock) return DEVICE_ERROR_INVALID_PARAMS;

    switch (cmd) {
        case CMD_LOCK:
            lock->locked = true;
            log_info("Door lock %s locked", device->name);
            return DEVICE_SUCCESS;

        case CMD_UNLOCK:
            lock->locked = false;
            lock->last_unlock = time(NULL);
            if (params) {
                strncpy(lock->last_access_user, (char*)params, sizeof(lock->last_access_user) - 1);
            }
            log_info("Door lock %s unlocked by %s", device->name,
                    lock->last_access_user[0] ? lock->last_access_user : "unknown");
            return DEVICE_SUCCESS;

        default:
            return DEVICE_ERROR_INVALID_COMMAND;
    }
}

int device_execute_plug_command(Device* device, DeviceCommand cmd, void* params) {
    switch (cmd) {
        case CMD_TURN_ON:
            log_info("Smart plug %s turned on", device->name);
            return DEVICE_SUCCESS;

        case CMD_TURN_OFF:
            log_info("Smart plug %s turned off", device->name);
            return DEVICE_SUCCESS;

        default:
            return DEVICE_ERROR_INVALID_COMMAND;
    }
}

int device_execute_generic_command(Device* device, DeviceCommand cmd, void* params) {
    switch (cmd) {
        case CMD_GET_STATUS:
            // Generic status check
            return DEVICE_SUCCESS;

        case CMD_RESET:
            // Reset device to default state
            device->state = DEVICE_OFFLINE;
            log_info("Device %s reset to default state", device->name);
            return DEVICE_SUCCESS;

        default:
            return DEVICE_ERROR_INVALID_COMMAND;
    }
}

int device_get_status(Device* device, char* status_buffer, size_t buffer_size) {
    if (!device || !status_buffer) return DEVICE_ERROR_INVALID_PARAMS;

    char temp[512];
    temp[0] = '\0';

    switch (device->type) {
        case DEVICE_LIGHT: {
            LightData* light = (LightData*)device->device_data;
            if (light) {
                sprintf(temp, "Light: brightness=%d%%, color=RGB(%d,%d,%d), motion=%s",
                       light->brightness, light->red, light->green, light->blue,
                       light->motion_activated ? "detected" : "none");
            }
            break;
        }

        case DEVICE_THERMOSTAT: {
            ThermostatData* thermo = (ThermostatData*)device->device_data;
            if (thermo) {
                sprintf(temp, "Thermostat: current=%.1f°C, target=%.1f°C, humidity=%.1f%%, mode=%s",
                       thermo->current_temp, thermo->target_temp, thermo->humidity, thermo->mode);
            }
            break;
        }

        case DEVICE_CAMERA: {
            CameraData* camera = (CameraData*)device->device_data;
            if (camera) {
                sprintf(temp, "Camera: recording=%s, motion_detection=%s, resolution=%dx%d",
                       camera->recording ? "yes" : "no",
                       camera->motion_detection ? "enabled" : "disabled",
                       camera->resolution_width, camera->resolution_height);
            }
            break;
        }

        case DEVICE_DOOR_LOCK: {
            DoorLockData* lock = (DoorLockData*)device->device_data;
            if (lock) {
                sprintf(temp, "Door Lock: locked=%s, auto_lock=%s, failed_attempts=%d",
                       lock->locked ? "yes" : "no",
                       lock->auto_lock ? "enabled" : "disabled",
                       lock->failed_attempts);
            }
            break;
        }

        default:
            sprintf(temp, "Device: type=%s, state=%s",
                   device_type_to_string(device->type),
                   device_state_to_string(device->state));
    }

    strncpy(status_buffer, temp, buffer_size - 1);
    status_buffer[buffer_size - 1] = '\0';

    return DEVICE_SUCCESS;
}

int device_update_data(Device* device) {
    if (!device) return DEVICE_ERROR_INVALID_PARAMS;

    device->last_seen = time(NULL);

    // Simulate sensor readings for demonstration
    switch (device->type) {
        case DEVICE_TEMPERATURE_SENSOR: {
            SensorData* sensor = (SensorData*)device->device_data;
            if (sensor) {
                // Simulate temperature variation
                sensor->current_value = 22.0 + (rand() % 100 - 50) / 10.0;
                sensor->current_value = clamp_float(sensor->current_value, -10.0, 50.0);
            }
            break;
        }

        case DEVICE_HUMIDITY_SENSOR: {
            SensorData* sensor = (SensorData*)device->device_data;
            if (sensor) {
                // Simulate humidity variation
                sensor->current_value = 50.0 + (rand() % 100 - 50) / 5.0;
                sensor->current_value = clamp_float(sensor->current_value, 0.0, 100.0);
            }
            break;
        }

        case DEVICE_MOTION_SENSOR: {
            SensorData* sensor = (SensorData*)device->device_data;
            if (sensor) {
                // Simulate random motion detection
                sensor->current_value = (rand() % 100) < 10 ? 1.0 : 0.0; // 10% chance
            }
            break;
        }

        case DEVICE_ENERGY_METER: {
            EnergyMeterData* meter = (EnergyMeterData*)device->device_data;
            if (meter) {
                // Simulate power consumption
                meter->current_power = (rand() % 5000) / 10.0; // 0-500W
                meter->voltage = 220.0 + (rand() % 20 - 10); // 210-230V
                meter->current = meter->current_power / meter->voltage;
                meter->last_reading = time(NULL);
            }
            break;
        }

        default:
            // No dynamic updates needed
            break;
    }

    return DEVICE_SUCCESS;
}

// Utility Functions

const char* device_type_to_string(DeviceType type) {
    switch (type) {
        case DEVICE_LIGHT: return "Light";
        case DEVICE_THERMOSTAT: return "Thermostat";
        case DEVICE_CAMERA: return "Camera";
        case DEVICE_DOOR_LOCK: return "Door Lock";
        case DEVICE_MOTION_SENSOR: return "Motion Sensor";
        case DEVICE_SMOKE_DETECTOR: return "Smoke Detector";
        case DEVICE_SMART_PLUG: return "Smart Plug";
        case DEVICE_TEMPERATURE_SENSOR: return "Temperature Sensor";
        case DEVICE_HUMIDITY_SENSOR: return "Humidity Sensor";
        case DEVICE_ENERGY_METER: return "Energy Meter";
        default: return "Unknown";
    }
}

const char* device_state_to_string(DeviceState state) {
    switch (state) {
        case DEVICE_OFFLINE: return "Offline";
        case DEVICE_ONLINE: return "Online";
        case DEVICE_ACTIVE: return "Active";
        case DEVICE_INACTIVE: return "Inactive";
        case DEVICE_ERROR: return "Error";
        default: return "Unknown";
    }
}

const char* device_command_to_string(DeviceCommand cmd) {
    switch (cmd) {
        case CMD_TURN_ON: return "Turn On";
        case CMD_TURN_OFF: return "Turn Off";
        case CMD_SET_BRIGHTNESS: return "Set Brightness";
        case CMD_SET_TEMPERATURE: return "Set Temperature";
        case CMD_SET_COLOR: return "Set Color";
        case CMD_LOCK: return "Lock";
        case CMD_UNLOCK: return "Unlock";
        case CMD_CAPTURE_IMAGE: return "Capture Image";
        case CMD_GET_STATUS: return "Get Status";
        case CMD_RESET: return "Reset";
        default: return "Unknown";
    }
}

DeviceType string_to_device_type(const char* str) {
    if (strcmp(str, "light") == 0) return DEVICE_LIGHT;
    if (strcmp(str, "thermostat") == 0) return DEVICE_THERMOSTAT;
    if (strcmp(str, "camera") == 0) return DEVICE_CAMERA;
    if (strcmp(str, "door_lock") == 0) return DEVICE_DOOR_LOCK;
    if (strcmp(str, "motion_sensor") == 0) return DEVICE_MOTION_SENSOR;
    if (strcmp(str, "smoke_detector") == 0) return DEVICE_SMOKE_DETECTOR;
    if (strcmp(str, "smart_plug") == 0) return DEVICE_SMART_PLUG;
    if (strcmp(str, "temperature_sensor") == 0) return DEVICE_TEMPERATURE_SENSOR;
    if (strcmp(str, "humidity_sensor") == 0) return DEVICE_HUMIDITY_SENSOR;
    if (strcmp(str, "energy_meter") == 0) return DEVICE_ENERGY_METER;
    return -1;
}

DeviceCommand string_to_device_command(const char* str) {
    if (strcmp(str, "on") == 0) return CMD_TURN_ON;
    if (strcmp(str, "off") == 0) return CMD_TURN_OFF;
    if (strcmp(str, "brightness") == 0) return CMD_SET_BRIGHTNESS;
    if (strcmp(str, "temperature") == 0) return CMD_SET_TEMPERATURE;
    if (strcmp(str, "color") == 0) return CMD_SET_COLOR;
    if (strcmp(str, "lock") == 0) return CMD_LOCK;
    if (strcmp(str, "unlock") == 0) return CMD_UNLOCK;
    if (strcmp(str, "capture") == 0) return CMD_CAPTURE_IMAGE;
    if (strcmp(str, "status") == 0) return CMD_GET_STATUS;
    if (strcmp(str, "reset") == 0) return CMD_RESET;
    return -1;
}

// Monitoring Functions

int device_get_online_count(DeviceManager* manager) {
    if (!manager) return 0;

    int count = 0;
    time_t now = time(NULL);

    for (int i = 0; i < manager->device_count; i++) {
        // Consider device online if seen within last 5 minutes
        if (now - manager->devices[i].last_seen < 300) {
            count++;
        }
    }

    return count;
}

int device_get_by_type_count(DeviceManager* manager, DeviceType type) {
    if (!manager) return 0;

    int count = 0;
    for (int i = 0; i < manager->device_count; i++) {
        if (manager->devices[i].type == type) {
            count++;
        }
    }

    return count;
}

int device_get_recently_active(DeviceManager* manager, Device** devices, int max_count, time_t since) {
    if (!manager || !devices) return 0;

    int count = 0;
    for (int i = 0; i < manager->device_count && count < max_count; i++) {
        if (manager->devices[i].last_seen >= since) {
            devices[count++] = &manager->devices[i];
        }
    }

    return count;
}

// Data Persistence

int device_save_to_file(DeviceManager* manager, const char* filename) {
    if (!manager || !filename) return DEVICE_ERROR_INVALID_PARAMS;

    FILE* file = fopen(filename, "w");
    if (!file) return DEVICE_ERROR_FILE_IO;

    fprintf(file, "# IoT Smart Home Device Configuration\n");
    fprintf(file, "# Generated: %s\n", get_current_time_string());
    fprintf(file, "\n");

    for (int i = 0; i < manager->device_count; i++) {
        Device* device = &manager->devices[i];
        fprintf(file, "[device_%d]\n", device->id);
        fprintf(file, "name=%s\n", device->name);
        fprintf(file, "location=%s\n", device->location);
        fprintf(file, "type=%s\n", device_type_to_string(device->type));
        fprintf(file, "state=%s\n", device_state_to_string(device->state));
        fprintf(file, "installed_date=%ld\n", device->installed_date);
        fprintf(file, "is_active=%s\n", device->is_active ? "true" : "false");
        fprintf(file, "\n");
    }

    fclose(file);
    log_info("Device configuration saved to %s", filename);
    return DEVICE_SUCCESS;
}

int device_load_from_file(DeviceManager* manager, const char* filename) {
    if (!manager || !filename) return DEVICE_ERROR_INVALID_PARAMS;

    if (!file_exists(filename)) {
        log_warn("Device configuration file %s not found", filename);
        return DEVICE_SUCCESS; // Not an error if file doesn't exist
    }

    FILE* file = fopen(filename, "r");
    if (!file) return DEVICE_ERROR_FILE_IO;

    char line[256];
    char current_section[50] = "";
    Device temp_device = {0};

    while (fgets(line, sizeof(line), file)) {
        // Remove newline and comments
        line[strcspn(line, "\n")] = 0;
        if (line[0] == '#' || line[0] == '\0') continue;

        // Check for section header
        if (line[0] == '[' && line[strlen(line) - 1] == ']') {
            if (strlen(current_section) > 0) {
                // Save previous device
                device_add(manager, temp_device.name, temp_device.location, temp_device.type);
            }

            // Start new section
            strncpy(current_section, line + 1, sizeof(current_section) - 1);
            current_section[strlen(current_section) - 1] = '\0'; // Remove closing bracket
            memset(&temp_device, 0, sizeof(Device));
        } else if (strlen(current_section) > 0) {
            // Parse key-value pairs
            char* key = strtok(line, "=");
            char* value = strtok(NULL, "=");

            if (key && value) {
                if (strcmp(key, "name") == 0) {
                    strncpy(temp_device.name, value, sizeof(temp_device.name) - 1);
                } else if (strcmp(key, "location") == 0) {
                    strncpy(temp_device.location, value, sizeof(temp_device.location) - 1);
                } else if (strcmp(key, "type") == 0) {
                    temp_device.type = string_to_device_type(value);
                }
            }
        }
    }

    // Save last device
    if (strlen(temp_device.name) > 0) {
        device_add(manager, temp_device.name, temp_device.location, temp_device.type);
    }

    fclose(file);
    log_info("Device configuration loaded from %s", filename);
    return DEVICE_SUCCESS;
}

// Error Handling

const char* device_error_to_string(DeviceError error) {
    switch (error) {
        case DEVICE_SUCCESS: return "Success";
        case DEVICE_ERROR_INVALID_ID: return "Invalid device ID";
        case DEVICE_ERROR_INVALID_TYPE: return "Invalid device type";
        case DEVICE_ERROR_INVALID_COMMAND: return "Invalid command";
        case DEVICE_ERROR_OFFLINE: return "Device is offline";
        case DEVICE_ERROR_MEMORY: return "Memory allocation failed";
        case DEVICE_ERROR_FILE_IO: return "File I/O error";
        case DEVICE_ERROR_INVALID_PARAMS: return "Invalid parameters";
        default: return "Unknown error";
    }
}