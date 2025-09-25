/*
 * Network Implementation (Simulated)
 * P2P networking for blockchain synchronization
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/network.h"

// Network lifecycle
P2PNetwork* network_create(int port) {
    P2PNetwork* network = (P2PNetwork*)malloc(sizeof(P2PNetwork));
    if (!network) return NULL;

    memset(network, 0, sizeof(P2PNetwork));
    network->listening_port = port;
    network->max_peers = MAX_PEERS;
    network->is_running = true;
    network->start_time = time(NULL);

    // Generate local node ID
    sprintf(network->local_node_id, "NODE_%06d", rand() % 1000000);

    return network;
}

void network_destroy(P2PNetwork* network) {
    if (network) {
        free(network);
    }
}

// Peer management
int network_add_peer(P2PNetwork* network, const char* ip_address, int port) {
    if (!network || network->peer_count >= network->max_peers) {
        return NETWORK_ERROR_MAX_PEERS_REACHED;
    }

    NetworkPeer* peer = &network->peers[network->peer_count];
    strcpy(peer->ip_address, ip_address);
    peer->port = port;
    sprintf(peer->node_id, "PEER_%06d", rand() % 1000000);
    peer->status = PEER_CONNECTED;
    peer->last_seen = time(NULL);
    peer->connected_time = time(NULL);
    peer->protocol_version = 1;
    peer->is_outbound = true;

    network->peer_count++;
    return NETWORK_SUCCESS;
}

int network_remove_peer(P2PNetwork* network, const char* node_id) {
    if (!network || !node_id) return NETWORK_ERROR_PEER_NOT_FOUND;

    for (int i = 0; i < network->peer_count; i++) {
        if (strcmp(network->peers[i].node_id, node_id) == 0) {
            // Shift remaining peers
            for (int j = i; j < network->peer_count - 1; j++) {
                network->peers[j] = network->peers[j + 1];
            }
            network->peer_count--;
            return NETWORK_SUCCESS;
        }
    }

    return NETWORK_ERROR_PEER_NOT_FOUND;
}

NetworkPeer* network_find_peer(const P2PNetwork* network, const char* node_id) {
    if (!network || !node_id) return NULL;

    for (int i = 0; i < network->peer_count; i++) {
        if (strcmp(network->peers[i].node_id, node_id) == 0) {
            return &network->peers[i];
        }
    }

    return NULL;
}

int network_get_active_peers(const P2PNetwork* network, NetworkPeer* peers[], int max_peers) {
    if (!network || !peers) return 0;

    int count = 0;
    for (int i = 0; i < network->peer_count && count < max_peers; i++) {
        if (network->peers[i].status == PEER_ACTIVE) {
            peers[count] = &network->peers[i];
            count++;
        }
    }

    return count;
}

// Message handling (stub implementations)
int network_broadcast_message(P2PNetwork* network, const NetworkMessage* message) {
    // Simulate broadcasting to all peers
    printf("Broadcasting message to %d peers\n", network->peer_count);
    return NETWORK_SUCCESS;
}

int network_send_message(P2PNetwork* network, const char* target_node_id, const NetworkMessage* message) {
    NetworkPeer* peer = network_find_peer(network, target_node_id);
    if (!peer) return NETWORK_ERROR_PEER_NOT_FOUND;

    printf("Sending message to peer %s\n", target_node_id);
    return NETWORK_SUCCESS;
}

NetworkMessage* network_receive_message(P2PNetwork* network) {
    // Stub - no messages in simulation
    return NULL;
}

// Blockchain synchronization (stub implementations)
int network_request_blockchain(P2PNetwork* network, const char* peer_id) {
    printf("Requesting blockchain from peer %s\n", peer_id);
    return NETWORK_SUCCESS;
}

int network_broadcast_block(P2PNetwork* network, const void* block_data) {
    printf("Broadcasting block to %d peers\n", network->peer_count);
    return NETWORK_SUCCESS;
}

int network_broadcast_transaction(P2PNetwork* network, const void* transaction_data) {
    printf("Broadcasting transaction to %d peers\n", network->peer_count);
    return NETWORK_SUCCESS;
}

// Network utilities
bool network_is_peer_connected(const P2PNetwork* network, const char* node_id) {
    NetworkPeer* peer = network_find_peer(network, node_id);
    return peer && peer->status == PEER_CONNECTED;
}

int network_get_network_stats(const P2PNetwork* network, int* active_peers, int* total_messages) {
    if (active_peers) *active_peers = network->peer_count;
    if (total_messages) *total_messages = 0; // Stub
    return NETWORK_SUCCESS;
}

void network_print_peer_list(const P2PNetwork* network) {
    printf("Connected Peers (%d):\n", network->peer_count);
    for (int i = 0; i < network->peer_count; i++) {
        NetworkPeer* peer = &network->peers[i];
        printf("  %s: %s:%d (%s)\n",
               peer->node_id, peer->ip_address, peer->port,
               peer->status == PEER_ACTIVE ? "Active" : "Connected");
    }
}

// Message creation
NetworkMessage* network_create_message(MessageType type, const void* data, size_t data_size) {
    NetworkMessage* message = (NetworkMessage*)malloc(sizeof(NetworkMessage));
    if (!message) return NULL;

    message->type = type;
    message->payload = malloc(data_size);
    if (message->payload) {
        memcpy(message->payload, data, data_size);
        message->payload_size = data_size;
    }
    strcpy(message->sender_id, "LOCAL_NODE");
    message->timestamp = time(NULL);

    return message;
}

void network_destroy_message(NetworkMessage* message) {
    if (message) {
        if (message->payload) {
            free(message->payload);
        }
        free(message);
    }
}

// Error handling
const char* network_error_message(NetworkError error) {
    switch (error) {
        case NETWORK_SUCCESS: return "Success";
        case NETWORK_ERROR_CONNECTION_FAILED: return "Connection failed";
        case NETWORK_ERROR_PEER_NOT_FOUND: return "Peer not found";
        case NETWORK_ERROR_MESSAGE_TOO_LARGE: return "Message too large";
        case NETWORK_ERROR_TIMEOUT: return "Timeout";
        case NETWORK_ERROR_INVALID_MESSAGE: return "Invalid message";
        case NETWORK_ERROR_MAX_PEERS_REACHED: return "Max peers reached";
        default: return "Unknown error";
    }
}

// Stub implementations for advanced features
int network_discover_peers(P2PNetwork* network) {
    // Simulate discovering peers
    printf("Discovering peers...\n");
    return NETWORK_SUCCESS;
}

int network_ping_peer(P2PNetwork* network, const char* peer_id) {
    NetworkPeer* peer = network_find_peer(network, peer_id);
    if (peer) {
        peer->last_seen = time(NULL);
        return NETWORK_SUCCESS;
    }
    return NETWORK_ERROR_PEER_NOT_FOUND;
}

int network_request_peer_list(P2PNetwork* network, const char* peer_id) {
    printf("Requesting peer list from %s\n", peer_id);
    return NETWORK_SUCCESS;
}