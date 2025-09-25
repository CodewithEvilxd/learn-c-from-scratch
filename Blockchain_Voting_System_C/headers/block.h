/*
 * Block Header - Blockchain Block Data Structure
 * Defines blocks and block-related operations
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "transaction.h"

// Hash size constant
#define HASH_SIZE 65

// Block field sizes
#define BLOCK_TIMESTAMP_SIZE 20
#define BLOCK_HASH_SIZE 65
#define BLOCK_PREV_HASH_SIZE 65
#define BLOCK_MERKLE_ROOT_SIZE 65
#define BLOCK_MINER_ADDRESS_SIZE 50

// Maximum transactions per block
#define MAX_TRANSACTIONS_PER_BLOCK 100

// Block structure
typedef struct {
    uint32_t index;                              // Block index/height
    char timestamp[BLOCK_TIMESTAMP_SIZE];         // Block creation timestamp (ISO format)
    Transaction* transactions[MAX_TRANSACTIONS_PER_BLOCK];  // Array of transactions
    int transaction_count;                        // Number of transactions in block
    char previous_hash[BLOCK_PREV_HASH_SIZE];     // Hash of previous block
    char hash[BLOCK_HASH_SIZE];                   // Current block hash
    char merkle_root[BLOCK_MERKLE_ROOT_SIZE];     // Merkle root of transactions
    uint32_t nonce;                               // Proof-of-work nonce
    uint32_t difficulty;                          // Mining difficulty target
    char miner_address[BLOCK_MINER_ADDRESS_SIZE]; // Address of miner who created block
    uint64_t total_votes;                         // Total votes in this block
    time_t mining_time;                           // Time taken to mine block
    bool is_genesis;                              // Is this the genesis block?
} Block;

// Block header (for lightweight validation)
typedef struct {
    uint32_t index;
    char timestamp[BLOCK_TIMESTAMP_SIZE];
    char previous_hash[BLOCK_PREV_HASH_SIZE];
    char merkle_root[BLOCK_MERKLE_ROOT_SIZE];
    uint32_t nonce;
    uint32_t difficulty;
} BlockHeader;

// Mining statistics
typedef struct {
    time_t start_time;
    time_t end_time;
    uint64_t hashes_computed;
    double hash_rate;  // hashes per second
    uint32_t nonce_found;
    double mining_time_seconds;
} MiningStats;

// Function declarations

// Block lifecycle
Block* block_create(uint32_t index, const char* previous_hash, uint32_t difficulty);
void block_destroy(Block* block);

// Block operations
int block_add_transaction(Block* block, Transaction* transaction);
int block_calculate_hash(Block* block, char* output_hash);
int block_calculate_merkle_root(Block* block, char* merkle_root);
int block_mine(Block* block, MiningStats* stats);
bool block_validate(const Block* block, const Block* previous_block);

// Block utilities
void block_print(const Block* block);
void block_print_header(const Block* block);
char* block_to_string(const Block* block);
Block* block_from_string(const char* block_string);

// Mining operations
bool block_meets_difficulty(const char* hash, uint32_t difficulty);
uint32_t block_find_nonce(const Block* block, uint32_t difficulty, MiningStats* stats);
double block_calculate_hash_rate(const MiningStats* stats);

// Validation
bool block_validate_index(const Block* block, uint32_t expected_index);
bool block_validate_timestamp(const Block* block);
bool block_validate_hash(const Block* block);
bool block_validate_transactions(const Block* block);
bool block_validate_merkle_root(const Block* block);
bool block_validate_difficulty(const Block* block, uint32_t expected_difficulty);

// Serialization
int block_to_json(const Block* block, char* json_buffer, size_t buffer_size);
int block_from_json(Block* block, const char* json_string);
int block_header_to_json(const BlockHeader* header, char* json_buffer, size_t buffer_size);

// Genesis block
Block* block_create_genesis(void);
bool block_is_genesis(const Block* block);

// Block statistics
typedef struct {
    int transaction_count;
    uint64_t total_votes;
    double average_transaction_size;
    time_t block_time;
    double mining_time_seconds;
    double hash_rate_mega;
} BlockStats;

void block_get_stats(const Block* block, BlockStats* stats);

// Memory management
size_t block_get_memory_usage(const Block* block);
int block_optimize_memory(Block* block);

// Error handling
typedef enum {
    BLOCK_SUCCESS = 0,
    BLOCK_ERROR_INVALID_INDEX = -1,
    BLOCK_ERROR_INVALID_HASH = -2,
    BLOCK_ERROR_INVALID_TRANSACTIONS = -3,
    BLOCK_ERROR_INVALID_TIMESTAMP = -4,
    BLOCK_ERROR_INVALID_DIFFICULTY = -5,
    BLOCK_ERROR_MINING_FAILED = -6,
    BLOCK_ERROR_MEMORY = -7,
    BLOCK_ERROR_SERIALIZATION = -8,
    BLOCK_ERROR_INVALID_DATA = -9,
    BLOCK_ERROR_UNKNOWN = -99
} BlockError;

const char* block_error_message(BlockError error);

// Advanced features
int block_compress(Block* block);
int block_decompress(Block* block);
int block_encrypt(Block* block, const char* key);
int block_decrypt(Block* block, const char* key);

// Fork handling
typedef enum {
    FORK_NONE,
    FORK_LENGTH,
    FORK_WEIGHT,
    FORK_ATTACK
} ForkType;

ForkType block_detect_fork(const Block* block1, const Block* block2);
int block_resolve_fork(const Block* chain1[], int len1, const Block* chain2[], int len2);

// Timestamp utilities
time_t block_get_timestamp_seconds(const Block* block);
int block_set_timestamp_now(Block* block);
bool block_is_recent(const Block* block, time_t max_age_seconds);

// Block rewards and incentives
#define BLOCK_REWARD_BASE 50  // Base block reward
#define BLOCK_REWARD_DECAY 210000  // Blocks per reward halving

uint64_t block_calculate_reward(uint32_t block_height);
uint64_t block_get_total_supply(void);

// Network protocol
int block_serialize_for_network(const Block* block, unsigned char* buffer, size_t* buffer_size);
int block_deserialize_from_network(Block* block, const unsigned char* buffer, size_t buffer_size);

// Testing utilities
Block* block_create_test_block(uint32_t index, const char* prev_hash, int tx_count);
bool block_run_tests(void);

#endif // BLOCK_H