/*
 * Blockchain Voting System - Main Header File
 * Core blockchain data structures and function declarations
 */

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "transaction.h"
#include "consensus.h"
#include "election.h"
#include "block.h"

// Maximum sizes for blockchain
#define MAX_BLOCKS 10000
#define MAX_PENDING_TRANSACTIONS 1000
#define HASH_SIZE 65  // SHA-256 hash size + null terminator
#define DIFFICULTY_DEFAULT 4
#define BLOCK_TIME_SECONDS 600  // 10 minutes

// Blockchain status
typedef enum {
    BLOCKCHAIN_STATUS_ACTIVE,
    BLOCKCHAIN_STATUS_SYNCING,
    BLOCKCHAIN_STATUS_VALIDATING,
    BLOCKCHAIN_STATUS_ERROR
} BlockchainStatus;

// Mining status
typedef enum {
    MINING_IDLE,
    MINING_ACTIVE,
    MINING_SUCCESS,
    MINING_FAILED
} MiningStatus;

// Blockchain statistics
typedef struct {
    int total_blocks;
    int total_transactions;
    double average_block_time;
    double hash_rate;
    time_t uptime;
} BlockchainStats;

// Main blockchain structure
typedef struct {
    Block* blocks[MAX_BLOCKS];           // Array of block pointers
    int block_count;                     // Current number of blocks
    int difficulty;                      // Current mining difficulty
    Transaction* pending_transactions[MAX_PENDING_TRANSACTIONS];
    int pending_count;                   // Number of pending transactions
    char genesis_hash[HASH_SIZE];        // Hash of genesis block
    time_t last_block_time;              // Timestamp of last block
    BlockchainStatus status;             // Current blockchain status
    MiningStatus mining_status;          // Current mining status
    char data_directory[256];            // Directory for data storage
    bool auto_save;                      // Auto-save blockchain to disk
    uint64_t total_transactions;         // Total transactions processed
} Blockchain;

// Network node information (for future P2P implementation)
typedef struct {
    char node_id[50];
    char ip_address[16];
    int port;
    time_t last_seen;
    bool is_active;
} NetworkNode;

// Function declarations

// Blockchain lifecycle
Blockchain* blockchain_create(void);
void blockchain_destroy(Blockchain* chain);

// Block operations
int blockchain_add_block(Blockchain* chain, Block* block);
Block* blockchain_get_latest_block(const Blockchain* chain);
Block* blockchain_get_block_by_index(const Blockchain* chain, int index);
Block* blockchain_get_block_by_hash(const Blockchain* chain, const char* hash);

// Transaction operations
int blockchain_add_transaction(Blockchain* chain, Transaction* transaction);
int blockchain_get_pending_transactions(const Blockchain* chain, Transaction** transactions, int max_count);
int blockchain_clear_pending_transactions(Blockchain* chain);

// Mining operations
int blockchain_mine_pending_transactions(Blockchain* chain);
int blockchain_adjust_difficulty(Blockchain* chain);

// Validation operations
bool blockchain_validate_chain(const Blockchain* chain);
bool blockchain_validate_block(const Blockchain* chain, const Block* block);
bool blockchain_validate_transaction(const Blockchain* chain, const Transaction* transaction);

// Persistence operations
int blockchain_save_to_file(const Blockchain* chain, const char* filename);
int blockchain_load_from_file(Blockchain* chain, const char* filename);
int blockchain_export_to_json(const Blockchain* chain, const char* filename);

// Query operations
uint64_t blockchain_get_total_votes(const Blockchain* chain, const char* election_id);
uint64_t blockchain_get_votes_for_candidate(const Blockchain* chain, const char* election_id, const char* candidate_id);
int blockchain_get_election_results(const Blockchain* chain, const char* election_id, ElectionResult* results, int max_results);

// Statistics and information
void blockchain_get_stats(const Blockchain* chain, BlockchainStats* stats);
void blockchain_print_info(const Blockchain* chain);
void blockchain_print_chain(const Blockchain* chain, int start_index, int count);

// Utility functions
bool blockchain_is_chain_valid(const Blockchain* chain);
int blockchain_get_chain_length(const Blockchain* chain);
time_t blockchain_get_average_block_time(const Blockchain* chain);
double blockchain_get_hash_rate(const Blockchain* chain);

// Network operations (simulated for now)
int blockchain_broadcast_block(const Blockchain* chain, const Block* block);
int blockchain_request_chain_sync(Blockchain* chain, const char* peer_address);
int blockchain_verify_with_network(const Blockchain* chain);

// Security and integrity
int blockchain_detect_double_spending(const Blockchain* chain, const Transaction* transaction);
int blockchain_verify_transaction_integrity(const Blockchain* chain, const Transaction* transaction);
bool blockchain_is_transaction_unique(const Blockchain* chain, const Transaction* transaction);

// Configuration
int blockchain_set_difficulty(Blockchain* chain, int difficulty);
int blockchain_set_auto_save(Blockchain* chain, bool auto_save);
int blockchain_set_data_directory(Blockchain* chain, const char* directory);

// Error handling
typedef enum {
    BLOCKCHAIN_SUCCESS = 0,
    BLOCKCHAIN_ERROR_MEMORY = -1,
    BLOCKCHAIN_ERROR_INVALID_BLOCK = -2,
    BLOCKCHAIN_ERROR_INVALID_TRANSACTION = -3,
    BLOCKCHAIN_ERROR_CHAIN_INVALID = -4,
    BLOCKCHAIN_ERROR_FILE_IO = -5,
    BLOCKCHAIN_ERROR_MINING_FAILED = -6,
    BLOCKCHAIN_ERROR_DOUBLE_SPEND = -7,
    BLOCKCHAIN_ERROR_NETWORK = -8,
    BLOCKCHAIN_ERROR_INVALID_INPUT = -9,
    BLOCKCHAIN_ERROR_UNKNOWN = -99
} BlockchainError;

const char* blockchain_error_message(BlockchainError error);

// Callback functions for events
typedef void (*BlockMinedCallback)(const Block* block);
typedef void (*TransactionAddedCallback)(const Transaction* transaction);
typedef void (*ChainInvalidCallback)(const char* reason);

void blockchain_set_callbacks(Blockchain* chain,
                           BlockMinedCallback block_callback,
                           TransactionAddedCallback transaction_callback,
                           ChainInvalidCallback invalid_callback);

#endif // BLOCKCHAIN_H