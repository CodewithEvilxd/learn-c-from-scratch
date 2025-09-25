/*
 * IoT Smart Home System - Main Application
 * Command-line interface for smart home management
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "../headers/device.h"
#include "../headers/automation.h"
#include "../headers/security.h"
#include "../headers/energy.h"
#include "../headers/network.h"
#include "../headers/storage.h"
#include "../headers/utils.h"

// System Components
DeviceManager* device_manager = NULL;
AutomationManager* automation_manager = NULL;
SecuritySystem* security_system = NULL;
EnergyManager* energy_manager = NULL;
NetworkManager* network_manager = NULL;
StorageManager* storage_manager = NULL;

// System State
bool system_running = true;
char current_user[50] = "admin";

// Function Prototypes
void initialize_system(void);
void cleanup_system(void);
void signal_handler(int signal);
void print_welcome_banner(void);
void print_help(void);
int process_command(char* command);
void print_system_status(void);

// Command Handlers
int cmd_add_device(char* args);
int cmd_remove_device(char* args);
int cmd_list_devices(char* args);
int cmd_control_device(char* args);
int cmd_create_rule(char* args);
int cmd_create_scene(char* args);
int cmd_show_status(char* args);
int cmd_security_status(char* args);
int cmd_energy_report(char* args);
int cmd_save_config(char* args);
int cmd_load_config(char* args);

int main(int argc, char* argv[]) {
    char command[1024];

    // Initialize signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Initialize system
    initialize_system();

    // Print welcome banner
    print_welcome_banner();

    // Main command loop
    while (system_running) {
        printf("\n🏠 SmartHome> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        // Skip empty commands
        if (strlen(command) == 0) {
            continue;
        }

        // Process command
        if (process_command(command) != 0) {
            printf("❌ Command failed. Type 'help' for available commands.\n");
        }
    }

    // Cleanup system
    cleanup_system();

    printf("\n👋 Smart Home System shut down successfully.\n");
    return 0;
}

void initialize_system(void) {
    log_info("Initializing IoT Smart Home System...");

    // Create system components
    device_manager = device_manager_create(100);
    automation_manager = automation_manager_create(50, 20);
    security_system = security_system_create(1000, 5000, 10);
    energy_manager = energy_manager_create(10000, 50);
    network_manager = network_manager_create(50, 1000);
    storage_manager = storage_manager_create("smarthome.conf", FORMAT_INI);

    if (!device_manager || !automation_manager || !security_system ||
        !energy_manager || !network_manager || !storage_manager) {
        log_fatal("Failed to initialize system components");
        exit(1);
    }

    // Load configuration
    if (storage_load_config(storage_manager) != 0) {
        log_warn("Could not load configuration, using defaults");
    }

    // Initialize default devices for demonstration
    device_add(device_manager, "living_room_light", "Living Room", DEVICE_LIGHT);
    device_add(device_manager, "kitchen_thermostat", "Kitchen", DEVICE_THERMOSTAT);
    device_add(device_manager, "front_door_camera", "Front Door", DEVICE_CAMERA);
    device_add(device_manager, "main_door_lock", "Front Door", DEVICE_DOOR_LOCK);

    log_info("System initialization complete");
}

void cleanup_system(void) {
    log_info("Shutting down IoT Smart Home System...");

    // Save configuration
    storage_save_config(storage_manager);

    // Destroy system components
    if (device_manager) device_manager_destroy(device_manager);
    if (automation_manager) automation_manager_destroy(automation_manager);
    if (security_system) security_system_destroy(security_system);
    if (energy_manager) energy_manager_destroy(energy_manager);
    if (network_manager) network_manager_destroy(network_manager);
    if (storage_manager) storage_manager_destroy(storage_manager);

    log_info("System cleanup complete");
}

void signal_handler(int signal) {
    log_info("Received signal %d, shutting down gracefully...", signal);
    system_running = false;
}

void print_welcome_banner(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     🏠 IOT SMART HOME SYSTEM                               ║\n");
    printf("║                                                                              ║\n");
    printf("║  A comprehensive Internet of Things platform for smart home management      ║\n");
    printf("║                                                                              ║\n");
    printf("║  Features:                                                                   ║\n");
    printf("║  • Device Management (Lights, Thermostats, Cameras, Locks)                 ║\n");
    printf("║  • Automation Engine (Rules, Scenes, Scheduling)                           ║\n");
    printf("║  • Security System (Monitoring, Alerts, Access Control)                    ║\n");
    printf("║  • Energy Monitoring (Usage Tracking, Cost Analysis)                       ║\n");
    printf("║  • Network Communication (Device Discovery, Messaging)                     ║\n");
    printf("║                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Type 'help' for available commands or 'quit' to exit.\n");
}

void print_help(void) {
    printf("\n📋 Available Commands:\n");
    printf("═══════════════════════════════════════════════\n");
    printf("🏠 Device Management:\n");
    printf("  add-device <type> <name> <location>    Add a new device\n");
    printf("  remove-device <id>                     Remove a device\n");
    printf("  list-devices                           List all devices\n");
    printf("  control-device <id> <command> [params] Control a device\n");
    printf("\n");
    printf("🤖 Automation:\n");
    printf("  create-rule <name> <condition> <action> Create automation rule\n");
    printf("  create-scene <name> <actions>          Create scene\n");
    printf("  list-rules                             List automation rules\n");
    printf("  list-scenes                            List scenes\n");
    printf("\n");
    printf("🔒 Security:\n");
    printf("  security-status                        Show security status\n");
    printf("  arm-system                             Arm security system\n");
    printf("  disarm-system                          Disarm security system\n");
    printf("  acknowledge-alert <id>                 Acknowledge security alert\n");
    printf("\n");
    printf("⚡ Energy:\n");
    printf("  energy-report                          Show energy usage report\n");
    printf("  add-energy-reading <device_id> <value> Add energy reading\n");
    printf("  set-energy-cost <cost_per_kwh>         Set electricity cost\n");
    printf("\n");
    printf("💾 Configuration:\n");
    printf("  save-config                            Save system configuration\n");
    printf("  load-config                            Load system configuration\n");
    printf("  show-status                            Show system status\n");
    printf("\n");
    printf("❓ Other:\n");
    printf("  help                                   Show this help message\n");
    printf("  quit                                   Exit the system\n");
    printf("\n");
    printf("📝 Examples:\n");
    printf("  add-device light bedroom_light Bedroom\n");
    printf("  control-device 1 on\n");
    printf("  create-rule \"Evening Lights\" \"time>18:00\" \"turn_on(living_room_light)\"\n");
}

int process_command(char* command) {
    char* token = strtok(command, " ");
    if (!token) return -1;

    // Device commands
    if (strcmp(token, "add-device") == 0) {
        return cmd_add_device(strtok(NULL, ""));
    }
    else if (strcmp(token, "remove-device") == 0) {
        return cmd_remove_device(strtok(NULL, ""));
    }
    else if (strcmp(token, "list-devices") == 0) {
        return cmd_list_devices(strtok(NULL, ""));
    }
    else if (strcmp(token, "control-device") == 0) {
        return cmd_control_device(strtok(NULL, ""));
    }

    // Automation commands
    else if (strcmp(token, "create-rule") == 0) {
        return cmd_create_rule(strtok(NULL, ""));
    }
    else if (strcmp(token, "create-scene") == 0) {
        return cmd_create_scene(strtok(NULL, ""));
    }

    // Security commands
    else if (strcmp(token, "security-status") == 0) {
        return cmd_security_status(strtok(NULL, ""));
    }

    // Energy commands
    else if (strcmp(token, "energy-report") == 0) {
        return cmd_energy_report(strtok(NULL, ""));
    }

    // Configuration commands
    else if (strcmp(token, "save-config") == 0) {
        return cmd_save_config(strtok(NULL, ""));
    }
    else if (strcmp(token, "load-config") == 0) {
        return cmd_load_config(strtok(NULL, ""));
    }
    else if (strcmp(token, "show-status") == 0) {
        return cmd_show_status(strtok(NULL, ""));
    }

    // Other commands
    else if (strcmp(token, "help") == 0) {
        print_help();
        return 0;
    }
    else if (strcmp(token, "quit") == 0) {
        system_running = false;
        return 0;
    }

    printf("❌ Unknown command: %s\n", token);
    printf("Type 'help' for available commands.\n");
    return -1;
}

void print_system_status(void) {
    printf("\n🏠 Smart Home System Status\n");
    printf("═══════════════════════════════════════════════\n");

    // Device status
    int online_devices = device_get_online_count(device_manager);
    printf("📱 Devices: %d online\n", online_devices);

    // Automation status
    int active_rules = automation_get_active_rules(automation_manager);
    printf("🤖 Automation Rules: %d active\n", active_rules);

    // Security status
    SecurityStatus sec_status;
    security_get_status(security_system, &sec_status);
    printf("🔒 Security: %s (%d alerts)\n",
           sec_status.system_health_score > 80 ? "Good" : "Needs Attention",
           sec_status.triggered_alarms);

    // Energy status
    EnergyStats energy_stats;
    energy_get_global_stats(energy_manager, &energy_stats);
    printf("⚡ Energy: %.1f kWh today (₹%.2f)\n",
           energy_stats.daily_usage,
           energy_calculate_cost(energy_manager, energy_stats.daily_usage));

    // Network status
    NetworkStatus net_status;
    network_get_status(network_manager, &net_status);
    printf("🌐 Network: %d active connections\n", net_status.active_connections);

    printf("👤 Current User: %s\n", current_user);
    printf("⏰ System Uptime: %s\n", get_current_time_string());
}

// Command Implementations

int cmd_add_device(char* args) {
    if (!args) {
        printf("❌ Usage: add-device <type> <name> <location>\n");
        return -1;
    }

    char* type_str = strtok(args, " ");
    char* name = strtok(NULL, " ");
    char* location = strtok(NULL, "");

    if (!type_str || !name || !location) {
        printf("❌ Usage: add-device <type> <name> <location>\n");
        return -1;
    }

    DeviceType type = string_to_device_type(type_str);
    if (type == -1) {
        printf("❌ Invalid device type. Valid types: light, thermostat, camera, door_lock, motion_sensor, smoke_detector, smart_plug, temperature_sensor, humidity_sensor, energy_meter\n");
        return -1;
    }

    int device_id = device_add(device_manager, name, location, type);
    if (device_id > 0) {
        printf("✅ Device added successfully (ID: %d)\n", device_id);
        return 0;
    } else {
        printf("❌ Failed to add device\n");
        return -1;
    }
}

int cmd_remove_device(char* args) {
    if (!args) {
        printf("❌ Usage: remove-device <id>\n");
        return -1;
    }

    int device_id = atoi(args);
    if (device_id <= 0) {
        printf("❌ Invalid device ID\n");
        return -1;
    }

    if (device_remove(device_manager, device_id) == 0) {
        printf("✅ Device removed successfully\n");
        return 0;
    } else {
        printf("❌ Failed to remove device\n");
        return -1;
    }
}

int cmd_list_devices(char* args) {
    printf("\n📱 Connected Devices:\n");
    printf("═══════════════════════════════════════════════\n");

    for (int i = 0; i < device_manager->device_count; i++) {
        Device* device = &device_manager->devices[i];
        printf("ID: %d | %s | %s | %s | %s\n",
               device->id,
               device_type_to_string(device->type),
               device->name,
               device->location,
               device_state_to_string(device->state));
    }

    printf("\nTotal: %d devices\n", device_manager->device_count);
    return 0;
}

int cmd_control_device(char* args) {
    if (!args) {
        printf("❌ Usage: control-device <id> <command> [parameters]\n");
        return -1;
    }

    char* id_str = strtok(args, " ");
    char* cmd_str = strtok(NULL, " ");
    char* params = strtok(NULL, "");

    if (!id_str || !cmd_str) {
        printf("❌ Usage: control-device <id> <command> [parameters]\n");
        return -1;
    }

    int device_id = atoi(id_str);
    DeviceCommand cmd = string_to_device_command(cmd_str);

    if (device_id <= 0 || cmd == -1) {
        printf("❌ Invalid device ID or command\n");
        return -1;
    }

    Device* device = device_find_by_id(device_manager, device_id);
    if (!device) {
        printf("❌ Device not found\n");
        return -1;
    }

    if (device_execute_command(device, cmd, params) == 0) {
        printf("✅ Command executed successfully\n");
        return 0;
    } else {
        printf("❌ Failed to execute command\n");
        return -1;
    }
}

int cmd_create_rule(char* args) {
    printf("🤖 Automation rule creation - Feature coming soon!\n");
    return 0;
}

int cmd_create_scene(char* args) {
    printf("🎭 Scene creation - Feature coming soon!\n");
    return 0;
}

int cmd_show_status(char* args) {
    print_system_status();
    return 0;
}

int cmd_security_status(char* args) {
    printf("🔒 Security System Status - Feature coming soon!\n");
    return 0;
}

int cmd_energy_report(char* args) {
    printf("⚡ Energy Report - Feature coming soon!\n");
    return 0;
}

int cmd_save_config(char* args) {
    if (storage_save_config(storage_manager) == 0) {
        printf("✅ Configuration saved successfully\n");
        return 0;
    } else {
        printf("❌ Failed to save configuration\n");
        return -1;
    }
}

int cmd_load_config(char* args) {
    if (storage_load_config(storage_manager) == 0) {
        printf("✅ Configuration loaded successfully\n");
        return 0;
    } else {
        printf("❌ Failed to load configuration\n");
        return -1;
    }
}