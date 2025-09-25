/*
 * IoT Smart Home - Network Communication Header
 * IoT device discovery, communication, and protocols
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <time.h>
#include <stdbool.h>
#include "device.h"

// Network Protocols
typedef enum {
    PROTOCOL_MQTT,
    PROTOCOL_COAP,
    PROTOCOL_HTTP,
    PROTOCOL_WEBSOCKET,
    PROTOCOL_BLE,
    PROTOCOL_ZIGBEE,
    PROTOCOL_ZWAVE
} NetworkProtocol;

// Message Types
typedef enum {
    MSG_DEVICE_DISCOVERY,
    MSG_DEVICE_STATUS,
    MSG_DEVICE_COMMAND,
    MSG_SENSOR_DATA,
    MSG_SYSTEM_ALERT,
    MSG_CONFIG_UPDATE,
    MSG_FIRMWARE_UPDATE,
    MSG_HEARTBEAT
} MessageType;

// Network Device Structure
typedef struct {
    char device_id[50];
    char ip_address[50];
    int port;
    NetworkProtocol protocol;
    time_t last_seen;
    time_t connected_time;
    bool authenticated;
    char auth_token[100];
    int message_count;
    DeviceState state;
} NetworkDevice;

// Network Message Structure
typedef struct {
    int id;
    MessageType type;
    char source_id[50];
    char destination_id[50];
    time_t timestamp;
    char payload[1024];
    int payload_size;
    bool encrypted;
    char checksum[33];  // SHA-256 checksum
} NetworkMessage;

// Network Manager
typedef struct {
    NetworkDevice* devices;
    int device_count;
    int max_devices;
    NetworkMessage* message_queue;
    int queue_size;
    int max_queue_size;
    int next_message_id;
    char gateway_ip[50];
    int gateway_port;
    NetworkProtocol default_protocol;
    bool encryption_enabled;
    char network_key[100];
} NetworkManager;

// Function Prototypes

// Network Manager
NetworkManager* network_manager_create(int max_devices, int max_queue);
void network_manager_destroy(NetworkManager* manager);

// Device Discovery and Registration
int network_discover_devices(NetworkManager* manager);
int network_register_device(NetworkManager* manager, const char* device_id,
                           const char* ip_address, int port, NetworkProtocol protocol);
int network_unregister_device(NetworkManager* manager, const char* device_id);
NetworkDevice* network_find_device(NetworkManager* manager, const char* device_id);

// Message Handling
int network_send_message(NetworkManager* manager, const char* destination_id,
                        MessageType type, const char* payload, int payload_size);
int network_broadcast_message(NetworkManager* manager, MessageType type,
                             const char* payload, int payload_size);
NetworkMessage* network_receive_message(NetworkManager* manager);
int network_process_message_queue(NetworkManager* manager);

// Protocol Handlers
int network_init_protocol(NetworkManager* manager, NetworkProtocol protocol);
int network_send_mqtt(NetworkManager* manager, const char* topic, const char* message);
int network_send_coap(NetworkManager* manager, const char* uri, const char* method,
                     const char* payload);
int network_send_http(NetworkManager* manager, const char* url, const char* method,
                     const char* data);

// Authentication and Security
int network_authenticate_device(NetworkManager* manager, const char* device_id,
                               const char* credentials);
int network_generate_auth_token(NetworkManager* manager, const char* device_id,
                               char* token, size_t token_size);
bool network_verify_auth_token(NetworkManager* manager, const char* token);

// Heartbeat and Monitoring
int network_send_heartbeat(NetworkManager* manager);
int network_check_device_status(NetworkManager* manager, const char* device_id);
int network_get_network_stats(NetworkManager* manager, int* active_devices,
                             int* messages_sent, int* messages_received);

// Configuration Management
int network_update_device_config(NetworkManager* manager, const char* device_id,
                                const char* config_key, const char* config_value);
int network_get_device_config(NetworkManager* manager, const char* device_id,
                             const char* config_key, char* value, size_t value_size);

// Firmware Updates
int network_initiate_firmware_update(NetworkManager* manager, const char* device_id,
                                    const char* firmware_url);
int network_check_update_status(NetworkManager* manager, const char* device_id);

// Error Handling and Recovery
int network_handle_connection_error(NetworkManager* manager, const char* device_id);
int network_retry_failed_messages(NetworkManager* manager);
int network_cleanup_stale_connections(NetworkManager* manager);

// Utility Functions
const char* network_protocol_to_string(NetworkProtocol protocol);
const char* message_type_to_string(MessageType type);
NetworkProtocol string_to_network_protocol(const char* str);
MessageType string_to_message_type(const char* str);

// Data Persistence
int network_save_device_list(NetworkManager* manager, const char* filename);
int network_load_device_list(NetworkManager* manager, const char* filename);
int network_save_message_queue(NetworkManager* manager, const char* filename);
int network_load_message_queue(NetworkManager* manager, const char* filename);

// Integration with Device Manager
int network_sync_with_device_manager(NetworkManager* manager, DeviceManager* device_manager);
int network_update_device_status(NetworkManager* manager, Device* device);

// Advanced Features
int network_setup_mesh_network(NetworkManager* manager);
int network_enable_auto_discovery(NetworkManager* manager, bool enabled);
int network_configure_quality_of_service(NetworkManager* manager, int qos_level);

// Error Handling
typedef enum {
    NETWORK_SUCCESS = 0,
    NETWORK_ERROR_INVALID_DEVICE = -1,
    NETWORK_ERROR_CONNECTION_FAILED = -2,
    NETWORK_ERROR_AUTHENTICATION_FAILED = -3,
    NETWORK_ERROR_MESSAGE_TOO_LARGE = -4,
    NETWORK_ERROR_PROTOCOL_NOT_SUPPORTED = -5,
    NETWORK_ERROR_MEMORY = -6,
    NETWORK_ERROR_TIMEOUT = -7
} NetworkError;

const char* network_error_to_string(NetworkError error);

// Performance Monitoring
typedef struct {
    int active_connections;
    int messages_per_second;
    float average_latency;
    int failed_connections;
    time_t last_network_scan;
    bool gateway_connected;
} NetworkStatus;

int network_get_status(NetworkManager* manager, NetworkStatus* status);

#endif // NETWORK_H