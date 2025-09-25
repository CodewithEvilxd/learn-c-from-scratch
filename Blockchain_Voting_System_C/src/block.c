/*
 * Block Implementation
 * Block data structure and mining operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include "../headers/block.h"
#include "../headers/transaction.h"
#include "../headers/crypto.h"
#include "../headers/utils.h"

// Block lifecycle
Block* block_create(uint32_t index, const char* previous_hash, uint32_t difficulty) {
    Block* block = (Block*)safe_malloc(sizeof(Block));
    if (!block) return NULL;

    memset(block, 0, sizeof(Block));
    block->index = index;
    block->difficulty = difficulty;
    block->is_genesis = (index == 0);

    // Set timestamp
    time_t now = time(NULL);
    strftime(block->timestamp, sizeof(block->timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    // Copy previous hash
    if (previous_hash) {
        str_copy(previous_hash, block->previous_hash, sizeof(block->previous_hash));
    }

    // Initialize transaction array
    memset(block->transactions, 0, sizeof(block->transactions));

    return block;
}

void block_destroy(Block* block) {
    if (!block) return;

    // Free transactions
    for (int i = 0; i < block->transaction_count; i++) {
        if (block->transactions[i]) {
            transaction_destroy(block->transactions[i]);
        }
    }

    safe_free(block);
}

// Block operations
int block_add_transaction(Block* block, Transaction* transaction) {
    if (!block || !transaction) return BLOCK_ERROR_INVALID_DATA;
    if (block->transaction_count >= MAX_TRANSACTIONS_PER_BLOCK) return BLOCK_ERROR_INVALID_DATA;

    block->transactions[block->transaction_count] = transaction;
    block->transaction_count++;
    block->total_votes += transaction->vote_weight;

    return BLOCK_SUCCESS;
}

int block_calculate_hash(Block* block, char* output_hash) {
    if (!block || !output_hash) return BLOCK_ERROR_INVALID_DATA;

    // Create a string representation of the block
    char block_data[4096] = {0};
    char temp[256];

    sprintf(temp, "%u", block->index);
    strcat(block_data, temp);

    strcat(block_data, block->timestamp);
    strcat(block_data, block->previous_hash);

    sprintf(temp, "%u", block->nonce);
    strcat(block_data, temp);

    sprintf(temp, "%u", block->difficulty);
    strcat(block_data, temp);

    // Add transaction data
    for (int i = 0; i < block->transaction_count; i++) {
        if (block->transactions[i]) {
            strcat(block_data, block->transactions[i]->transaction_hash);
        }
    }

    // Calculate SHA-256 hash
    uint8_t hash[SHA256_DIGEST_SIZE];
    sha256_hash((const uint8_t*)block_data, strlen(block_data), hash);
    sha256_to_hex(hash, output_hash);

    return BLOCK_SUCCESS;
}

int block_calculate_merkle_root(Block* block, char* merkle_root) {
    if (!block || !merkle_root) return BLOCK_ERROR_INVALID_DATA;

    // Simplified Merkle root calculation
    // In a real implementation, this would build a proper Merkle tree
    char combined_hashes[4096] = {0};

    for (int i = 0; i < block->transaction_count; i++) {
        if (block->transactions[i]) {
            strcat(combined_hashes, block->transactions[i]->transaction_hash);
        }
    }

    uint8_t hash[SHA256_DIGEST_SIZE];
    sha256_hash((const uint8_t*)combined_hashes, strlen(combined_hashes), hash);
    sha256_to_hex(hash, merkle_root);

    return BLOCK_SUCCESS;
}

int block_mine(Block* block, MiningStats* stats) {
    if (!block || !stats) return BLOCK_ERROR_INVALID_DATA;

    time_t start_time = time(NULL);
    uint32_t start_nonce = block->nonce;

    // Calculate initial hash
    block_calculate_hash(block, block->hash);

    // Mine until we find a valid nonce
    while (!block_meets_difficulty(block->hash, block->difficulty)) {
        block->nonce++;

        // Recalculate hash with new nonce
        if (block_calculate_hash(block, block->hash) != BLOCK_SUCCESS) {
            return BLOCK_ERROR_INVALID_DATA;
        }

        // Safety check to prevent infinite loop
        if (block->nonce - start_nonce > 10000000) { // 10 million attempts
            return BLOCK_ERROR_MINING_FAILED;
        }
    }

    time_t end_time = time(NULL);
    block->mining_time = end_time;

    // Fill mining statistics
    stats->start_time = start_time;
    stats->end_time = end_time;
    stats->hashes_computed = block->nonce - start_nonce;
    stats->nonce_found = block->nonce;
    stats->mining_time_seconds = difftime(end_time, start_time);

    if (stats->mining_time_seconds > 0) {
        stats->hash_rate = stats->hashes_computed / stats->mining_time_seconds;
    }

    return BLOCK_SUCCESS;
}

bool block_meets_difficulty(const char* hash, uint32_t difficulty) {
    if (!hash || difficulty == 0) return true;

    // Check if hash starts with the required number of zeros
    for (uint32_t i = 0; i < difficulty; i++) {
        if (hash[i] != '0') {
            return false;
        }
    }

    return true;
}

// Genesis block
Block* block_create_genesis(void) {
    Block* genesis = block_create(0, "0", 1); // Difficulty 1 for genesis
    if (!genesis) return NULL;

    genesis->is_genesis = true;
    strcpy(genesis->miner_address, "GENESIS_MINER");

    // Calculate genesis hash
    block_calculate_hash(genesis, genesis->hash);

    return genesis;
}

bool block_is_genesis(const Block* block) {
    return block && block->is_genesis;
}

// Validation
bool block_validate_hash(const Block* block) {
    if (!block) return false;

    char calculated_hash[HASH_SIZE];
    if (block_calculate_hash((Block*)block, calculated_hash) != BLOCK_SUCCESS) {
        return false;
    }

    return strcmp(block->hash, calculated_hash) == 0;
}

bool block_validate_transactions(const Block* block) {
    if (!block) return false;

    for (int i = 0; i < block->transaction_count; i++) {
        if (block->transactions[i] && !transaction_is_valid(block->transactions[i])) {
            return false;
        }
    }

    return true;
}

bool block_validate_merkle_root(const Block* block) {
    if (!block) return false;

    char calculated_root[HASH_SIZE];
    if (block_calculate_merkle_root((Block*)block, calculated_root) != BLOCK_SUCCESS) {
        return false;
    }

    return strcmp(block->merkle_root, calculated_root) == 0;
}

// Utility functions
void block_print(const Block* block) {
    if (!block) return;

    printf("Block #%u\n", block->index);
    printf("  Timestamp: %s\n", block->timestamp);
    printf("  Previous Hash: %.16s...\n", block->previous_hash);
    printf("  Hash: %.16s...\n", block->hash);
    printf("  Nonce: %u\n", block->nonce);
    printf("  Difficulty: %u\n", block->difficulty);
    printf("  Transactions: %d\n", block->transaction_count);
    printf("  Total Votes: %" PRIu64 "\n", block->total_votes);
    printf("  Merkle Root: %.16s...\n", block->merkle_root);
    printf("  Miner: %s\n", block->miner_address);
    if (block->is_genesis) {
        printf("  [GENESIS BLOCK]\n");
    }
    printf("\n");
}

void block_print_header(const Block* block) {
    if (!block) return;

    printf("Block #%u: %.16s... (Nonce: %u, Tx: %d)\n",
           block->index, block->hash, block->nonce, block->transaction_count);
}

// Statistics
void block_get_stats(const Block* block, BlockStats* stats) {
    if (!block || !stats) return;

    stats->transaction_count = block->transaction_count;
    stats->total_votes = block->total_votes;
    stats->block_time = block->mining_time;
    stats->mining_time_seconds = 0; // Would need previous block to calculate

    if (block->transaction_count > 0) {
        stats->average_transaction_size = 100; // Placeholder
    } else {
        stats->average_transaction_size = 0;
    }
}

// Error handling
const char* block_error_message(BlockError error) {
    switch (error) {
        case BLOCK_SUCCESS: return "Success";
        case BLOCK_ERROR_INVALID_INDEX: return "Invalid block index";
        case BLOCK_ERROR_INVALID_HASH: return "Invalid block hash";
        case BLOCK_ERROR_INVALID_TRANSACTIONS: return "Invalid transactions";
        case BLOCK_ERROR_INVALID_TIMESTAMP: return "Invalid timestamp";
        case BLOCK_ERROR_INVALID_DIFFICULTY: return "Invalid difficulty";
        case BLOCK_ERROR_MINING_FAILED: return "Mining failed";
        case BLOCK_ERROR_MEMORY: return "Memory allocation failed";
        case BLOCK_ERROR_SERIALIZATION: return "Serialization error";
        default: return "Unknown error";
    }
}