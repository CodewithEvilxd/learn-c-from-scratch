/*
 * Transaction Header - Vote Transaction Data Structure
 * Defines vote transactions and related operations
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

// Transaction field sizes
#define TX_VOTER_ID_SIZE 50
#define TX_ELECTION_ID_SIZE 50
#define TX_CANDIDATE_ID_SIZE 50
#define TX_TIMESTAMP_SIZE 20
#define TX_SIGNATURE_SIZE 129  // ECDSA signature size
#define TX_HASH_SIZE 65

// Transaction types
typedef enum {
    TX_TYPE_VOTE,
    TX_TYPE_REGISTRATION,
    TX_TYPE_ELECTION_START,
    TX_TYPE_ELECTION_END,
    TX_TYPE_SYSTEM
} TransactionType;

// Vote transaction structure
typedef struct {
    char voter_id[TX_VOTER_ID_SIZE];        // Anonymous voter identifier
    char election_id[TX_ELECTION_ID_SIZE];   // Election identifier
    char candidate_id[TX_CANDIDATE_ID_SIZE]; // Selected candidate
    char timestamp[TX_TIMESTAMP_SIZE];       // Vote timestamp (ISO format)
    char signature[TX_SIGNATURE_SIZE];       // Digital signature
    int vote_weight;                         // Vote weight (default: 1)
    TransactionType type;                    // Transaction type
    char transaction_hash[TX_HASH_SIZE];     // Transaction hash
    uint32_t nonce;                          // Random nonce for uniqueness
} Transaction;

// Transaction pool for pending transactions
typedef struct {
    Transaction* transactions[1000];
    int count;
    int max_size;
} TransactionPool;

// Function declarations

// Transaction lifecycle
Transaction* transaction_create(const char* voter_id, const char* election_id,
                               const char* candidate_id, TransactionType type);
void transaction_destroy(Transaction* transaction);

// Transaction operations
int transaction_calculate_hash(Transaction* transaction, char* output_hash);
int transaction_sign(Transaction* transaction, const char* private_key);
int transaction_verify_signature(const Transaction* transaction, const char* public_key);
int transaction_set_timestamp(Transaction* transaction);
int transaction_generate_nonce(Transaction* transaction);

// Transaction validation
bool transaction_is_valid(const Transaction* transaction);
bool transaction_is_unique(const Transaction* transaction, const Transaction* existing_transactions[], int count);
bool transaction_belongs_to_election(const Transaction* transaction, const char* election_id);

// Transaction pool operations
TransactionPool* transaction_pool_create(int max_size);
void transaction_pool_destroy(TransactionPool* pool);
int transaction_pool_add(TransactionPool* pool, Transaction* transaction);
Transaction* transaction_pool_remove(TransactionPool* pool, int index);
int transaction_pool_get_count(const TransactionPool* pool);
Transaction** transaction_pool_get_all(TransactionPool* pool, int* count);

// Batch operations
int transaction_process_batch(Transaction* transactions[], int count);
int transaction_validate_batch(const Transaction* transactions[], int count);

// Serialization
int transaction_to_json(const Transaction* transaction, char* json_buffer, size_t buffer_size);
int transaction_from_json(Transaction* transaction, const char* json_string);

// Utility functions
void transaction_print(const Transaction* transaction);
void transaction_print_short(const Transaction* transaction);
bool transaction_equals(const Transaction* tx1, const Transaction* tx2);

// Statistics
typedef struct {
    int total_votes;
    int unique_voters;
    int election_count;
    time_t earliest_vote;
    time_t latest_vote;
} TransactionStats;

void transaction_get_stats(const Transaction* transactions[], int count, TransactionStats* stats);

// Error handling
typedef enum {
    TX_SUCCESS = 0,
    TX_ERROR_INVALID_DATA = -1,
    TX_ERROR_SIGNATURE_INVALID = -2,
    TX_ERROR_HASH_MISMATCH = -3,
    TX_ERROR_DUPLICATE = -4,
    TX_ERROR_EXPIRED = -5,
    TX_ERROR_INSUFFICIENT_FUNDS = -6,
    TX_ERROR_UNKNOWN = -99
} TransactionError;

const char* transaction_error_message(TransactionError error);

// Advanced features
int transaction_compress(Transaction* transaction);
int transaction_decompress(Transaction* transaction);
int transaction_encrypt(Transaction* transaction, const char* key);
int transaction_decrypt(Transaction* transaction, const char* key);

// Merkle tree integration (for efficient verification)
typedef struct MerkleNode {
    char hash[TX_HASH_SIZE];
    struct MerkleNode* left;
    struct MerkleNode* right;
} MerkleNode;

MerkleNode* transaction_build_merkle_tree(Transaction* transactions[], int count);
void merkle_tree_destroy(MerkleNode* root);
int merkle_tree_get_root_hash(MerkleNode* root, char* hash_output);
bool merkle_tree_verify_transaction(MerkleNode* root, const Transaction* transaction, const char* proof[]);

#endif // TRANSACTION_H