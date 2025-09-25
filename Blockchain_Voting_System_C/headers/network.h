/*
 * Network Header - P2P Networking (Simulated)
 * Peer-to-peer communication for blockchain synchronization
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <time.h>
#include <stdbool.h>

// Network configuration
#define MAX_PEERS 100
#define MAX_MESSAGE_SIZE 4096
#define DEFAULT_PORT 8333
#define CONNECTION_TIMEOUT 30

// Peer status
typedef enum {
    PEER_DISCONNECTED,
    PEER_CONNECTING,
    PEER_CONNECTED,
    PEER_ACTIVE,
    PEER_BANNED
} PeerStatus;

// Message types
typedef enum {
    MSG_BLOCK,
    MSG_TRANSACTION,
    MSG_PEER_LIST,
    MSG_BLOCK_REQUEST,
    MSG_BLOCK_RESPONSE,
    MSG_PING,
    MSG_PONG,
    MSG_VERSION,
    MSG_VERACK
} MessageType;

// Network peer
typedef struct {
    char ip_address[16];     // IPv4 address
    int port;               // Port number
    char node_id[65];       // Node identifier (hash)
    PeerStatus status;      // Connection status
    time_t last_seen;       // Last activity timestamp
    time_t connected_time;  // Connection establishment time
    int protocol_version;   // Protocol version
    bool is_outbound;       // Inbound or outbound connection
} NetworkPeer;

// Network message
typedef struct {
    MessageType type;       // Message type
    char* payload;          // Message data
    size_t payload_size;    // Payload size
    char sender_id[65];     // Sender node ID
    time_t timestamp;       // Message timestamp
} NetworkMessage;

// P2P Network
typedef struct {
    NetworkPeer peers[MAX_PEERS];    // Connected peers
    int peer_count;                  // Number of connected peers
    int max_peers;                   // Maximum peers allowed
    char local_node_id[65];          // Local node identifier
    int listening_port;              // Port we're listening on
    bool is_running;                 // Network is active
    time_t start_time;               // Network start time
} P2PNetwork;

// Function declarations

// Network lifecycle
P2PNetwork* network_create(int port);
void network_destroy(P2PNetwork* network);

// Peer management
int network_add_peer(P2PNetwork* network, const char* ip_address, int port);
int network_remove_peer(P2PNetwork* network, const char* node_id);
NetworkPeer* network_find_peer(const P2PNetwork* network, const char* node_id);
int network_get_active_peers(const P2PNetwork* network, NetworkPeer* peers[], int max_peers);

// Message handling
int network_broadcast_message(P2PNetwork* network, const NetworkMessage* message);
int network_send_message(P2PNetwork* network, const char* target_node_id, const NetworkMessage* message);
NetworkMessage* network_receive_message(P2PNetwork* network);

// Blockchain synchronization
int network_request_blockchain(P2PNetwork* network, const char* peer_id);
int network_broadcast_block(P2PNetwork* network, const void* block_data);
int network_broadcast_transaction(P2PNetwork* network, const void* transaction_data);

// Network utilities
bool network_is_peer_connected(const P2PNetwork* network, const char* node_id);
int network_get_network_stats(const P2PNetwork* network, int* active_peers, int* total_messages);
void network_print_peer_list(const P2PNetwork* network);

// Message creation
NetworkMessage* network_create_message(MessageType type, const void* data, size_t data_size);
void network_destroy_message(NetworkMessage* message);

// Error handling
typedef enum {
    NETWORK_SUCCESS = 0,
    NETWORK_ERROR_CONNECTION_FAILED = -1,
    NETWORK_ERROR_PEER_NOT_FOUND = -2,
    NETWORK_ERROR_MESSAGE_TOO_LARGE = -3,
    NETWORK_ERROR_TIMEOUT = -4,
    NETWORK_ERROR_INVALID_MESSAGE = -5,
    NETWORK_ERROR_MAX_PEERS_REACHED = -6,
    NETWORK_ERROR_UNKNOWN = -99
} NetworkError;

const char* network_error_message(NetworkError error);

// Advanced features (simulated)
int network_discover_peers(P2PNetwork* network);
int network_ping_peer(P2PNetwork* network, const char* peer_id);
int network_request_peer_list(P2PNetwork* network, const char* peer_id);

#endif // NETWORK_H