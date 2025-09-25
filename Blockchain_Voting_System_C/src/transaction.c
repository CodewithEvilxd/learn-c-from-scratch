/*
 * Transaction Implementation
 * Vote transaction handling and validation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include "../headers/transaction.h"
#include "../headers/crypto.h"
#include "../headers/utils.h"

// Transaction lifecycle
Transaction* transaction_create(const char* voter_id, const char* election_id,
                               const char* candidate_id, TransactionType type) {
    Transaction* transaction = (Transaction*)safe_malloc(sizeof(Transaction));
    if (!transaction) return NULL;

    memset(transaction, 0, sizeof(Transaction));

    // Copy data
    str_copy(voter_id, transaction->voter_id, sizeof(transaction->voter_id));
    str_copy(election_id, transaction->election_id, sizeof(transaction->election_id));
    str_copy(candidate_id, transaction->candidate_id, sizeof(transaction->candidate_id));

    transaction->type = type;
    transaction->vote_weight = 1; // Default weight
    transaction->nonce = random_int(0, UINT32_MAX);

    // Set timestamp
    transaction_set_timestamp(transaction);

    // Calculate hash
    transaction_calculate_hash(transaction, transaction->transaction_hash);

    return transaction;
}

void transaction_destroy(Transaction* transaction) {
    if (transaction) {
        safe_free(transaction);
    }
}

// Transaction operations
int transaction_calculate_hash(Transaction* transaction, char* output_hash) {
    if (!transaction || !output_hash) return TX_ERROR_INVALID_DATA;

    char data[1024] = {0};
    char temp[50];

    // Combine transaction data
    strcat(data, transaction->voter_id);
    strcat(data, transaction->election_id);
    strcat(data, transaction->candidate_id);
    strcat(data, transaction->timestamp);

    sprintf(temp, "%d", transaction->vote_weight);
    strcat(data, temp);

    sprintf(temp, "%u", transaction->nonce);
    strcat(data, temp);

    // Calculate SHA-256 hash
    uint8_t hash[SHA256_DIGEST_SIZE];
    sha256_hash((const uint8_t*)data, strlen(data), hash);
    sha256_to_hex(hash, output_hash);

    return TX_SUCCESS;
}

int transaction_set_timestamp(Transaction* transaction) {
    if (!transaction) return TX_ERROR_INVALID_DATA;

    time_t now = time(NULL);
    strftime(transaction->timestamp, sizeof(transaction->timestamp),
             "%Y-%m-%d %H:%M:%S", localtime(&now));

    return TX_SUCCESS;
}

int transaction_generate_nonce(Transaction* transaction) {
    if (!transaction) return TX_ERROR_INVALID_DATA;

    transaction->nonce = random_int(0, UINT32_MAX);
    return TX_SUCCESS;
}

// Validation
bool transaction_is_valid(const Transaction* transaction) {
    if (!transaction) return false;

    // Check required fields
    if (strlen(transaction->voter_id) == 0 ||
        strlen(transaction->election_id) == 0 ||
        strlen(transaction->candidate_id) == 0) {
        return false;
    }

    // Check timestamp (not in future)
    time_t now = time(NULL);
    struct tm tm_time;
    if (strptime(transaction->timestamp, "%Y-%m-%d %H:%M:%S", &tm_time) == NULL) {
        return false;
    }

    time_t tx_time = mktime(&tm_time);
    if (tx_time > now + 300) { // Allow 5 minutes clock skew
        return false;
    }

    // Check vote weight
    if (transaction->vote_weight < 1) {
        return false;
    }

    return true;
}

bool transaction_is_unique(const Transaction* transaction, const Transaction* existing_transactions[], int count) {
    if (!transaction) return false;

    for (int i = 0; i < count; i++) {
        if (existing_transactions[i] &&
            strcmp(transaction->transaction_hash, existing_transactions[i]->transaction_hash) == 0) {
            return false;
        }
    }

    return true;
}

// Utility functions
void transaction_print(const Transaction* transaction) {
    if (!transaction) return;

    printf("Transaction:\n");
    printf("  Voter ID: %s\n", transaction->voter_id);
    printf("  Election ID: %s\n", transaction->election_id);
    printf("  Candidate ID: %s\n", transaction->candidate_id);
    printf("  Timestamp: %s\n", transaction->timestamp);
    printf("  Vote Weight: %d\n", transaction->vote_weight);
    printf("  Type: %d\n", transaction->type);
    printf("  Hash: %.16s...\n", transaction->transaction_hash);
    printf("  Nonce: %u\n", transaction->nonce);
    printf("\n");
}

void transaction_print_short(const Transaction* transaction) {
    if (!transaction) return;

    printf("TX: %s → %s (%.8s...)\n",
           transaction->voter_id,
           transaction->candidate_id,
           transaction->transaction_hash);
}

// Transaction pool operations
TransactionPool* transaction_pool_create(int max_size) {
    TransactionPool* pool = (TransactionPool*)safe_malloc(sizeof(TransactionPool));
    if (!pool) return NULL;

    pool->count = 0;
    pool->max_size = max_size;
    memset(pool->transactions, 0, sizeof(pool->transactions));

    return pool;
}

void transaction_pool_destroy(TransactionPool* pool) {
    if (!pool) return;

    for (int i = 0; i < pool->count; i++) {
        if (pool->transactions[i]) {
            transaction_destroy(pool->transactions[i]);
        }
    }

    safe_free(pool);
}

int transaction_pool_add(TransactionPool* pool, Transaction* transaction) {
    if (!pool || !transaction) return TX_ERROR_INVALID_DATA;
    if (pool->count >= pool->max_size) return TX_ERROR_INVALID_DATA;

    pool->transactions[pool->count] = transaction;
    pool->count++;

    return TX_SUCCESS;
}

Transaction* transaction_pool_remove(TransactionPool* pool, int index) {
    if (!pool || index < 0 || index >= pool->count) return NULL;

    Transaction* transaction = pool->transactions[index];

    // Shift remaining transactions
    for (int i = index; i < pool->count - 1; i++) {
        pool->transactions[i] = pool->transactions[i + 1];
    }

    pool->transactions[pool->count - 1] = NULL;
    pool->count--;

    return transaction;
}

int transaction_pool_get_count(const TransactionPool* pool) {
    return pool ? pool->count : 0;
}

Transaction** transaction_pool_get_all(TransactionPool* pool, int* count) {
    if (!pool || !count) return NULL;

    *count = pool->count;
    return pool->transactions;
}

// Stub implementations for advanced features
int transaction_sign(Transaction* transaction, const char* private_key) {
    // TODO: Implement ECDSA signing
    return TX_SUCCESS;
}

int transaction_verify_signature(const Transaction* transaction, const char* public_key) {
    // TODO: Implement ECDSA verification
    return TX_SUCCESS;
}

int transaction_process_batch(Transaction* transactions[], int count) {
    // Stub implementation
    return TX_SUCCESS;
}

int transaction_validate_batch(const Transaction* transactions[], int count) {
    for (int i = 0; i < count; i++) {
        if (!transaction_is_valid(transactions[i])) {
            return TX_ERROR_INVALID_DATA;
        }
    }
    return TX_SUCCESS;
}

int transaction_to_json(const Transaction* transaction, char* json_buffer, size_t buffer_size) {
    // Stub implementation
    return TX_SUCCESS;
}

int transaction_from_json(Transaction* transaction, const char* json_string) {
    // Stub implementation
    return TX_SUCCESS;
}

// Statistics
void transaction_get_stats(const Transaction* transactions[], int count, TransactionStats* stats) {
    if (!stats) return;

    memset(stats, 0, sizeof(TransactionStats));

    if (count == 0) return;

    stats->total_votes = 0;
    stats->unique_voters = 0;
    stats->earliest_vote = time(NULL);
    stats->latest_vote = 0;

    // Simple statistics calculation
    for (int i = 0; i < count; i++) {
        if (transactions[i]) {
            stats->total_votes += transactions[i]->vote_weight;

            // Parse timestamp
            struct tm tm_time;
            if (strptime(transactions[i]->timestamp, "%Y-%m-%d %H:%M:%S", &tm_time) != NULL) {
                time_t tx_time = mktime(&tm_time);
                if (tx_time < stats->earliest_vote) stats->earliest_vote = tx_time;
                if (tx_time > stats->latest_vote) stats->latest_vote = tx_time;
            }
        }
    }

    // Estimate unique voters (simplified)
    stats->unique_voters = count > 0 ? count / 2 + 1 : 0; // Rough estimate
}

// Error handling
const char* transaction_error_message(TransactionError error) {
    switch (error) {
        case TX_SUCCESS: return "Success";
        case TX_ERROR_INVALID_DATA: return "Invalid transaction data";
        case TX_ERROR_SIGNATURE_INVALID: return "Invalid signature";
        case TX_ERROR_HASH_MISMATCH: return "Hash mismatch";
        case TX_ERROR_DUPLICATE: return "Duplicate transaction";
        case TX_ERROR_EXPIRED: return "Transaction expired";
        case TX_ERROR_INSUFFICIENT_FUNDS: return "Insufficient funds";
        default: return "Unknown error";
    }
}