/*
 * Blockchain Core Implementation
 * Main blockchain data structure and operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include "../headers/blockchain.h"
#include "../headers/block.h"
#include "../headers/transaction.h"
#include "../headers/crypto.h"
#include "../headers/consensus.h"
#include "../headers/utils.h"
#include "../headers/election.h"

// Static blockchain instance for callbacks
static Blockchain* current_blockchain = NULL;

// Callback functions
static BlockMinedCallback block_mined_callback = NULL;
static TransactionAddedCallback transaction_added_callback = NULL;
static ChainInvalidCallback chain_invalid_callback = NULL;

// Blockchain lifecycle
Blockchain* blockchain_create(void) {
    Blockchain* chain = (Blockchain*)safe_malloc(sizeof(Blockchain));
    if (!chain) return NULL;

    memset(chain, 0, sizeof(Blockchain));
    chain->difficulty = DIFFICULTY_DEFAULT;
    chain->status = BLOCKCHAIN_STATUS_ACTIVE;
    chain->mining_status = MINING_IDLE;
    chain->auto_save = true;
    strcpy(chain->data_directory, "data");

    // Create genesis block
    Block* genesis = block_create_genesis();
    if (!genesis) {
        safe_free(chain);
        return NULL;
    }

    chain->blocks[0] = genesis;
    chain->block_count = 1;
    strcpy(chain->genesis_hash, genesis->hash);
    chain->last_block_time = time(NULL);

    current_blockchain = chain;
    log_message(LOG_INFO, "Blockchain created with genesis block");

    return chain;
}

void blockchain_destroy(Blockchain* chain) {
    if (!chain) return;

    // Free all blocks
    for (int i = 0; i < chain->block_count; i++) {
        if (chain->blocks[i]) {
            block_destroy(chain->blocks[i]);
        }
    }

    // Free pending transactions
    for (int i = 0; i < chain->pending_count; i++) {
        if (chain->pending_transactions[i]) {
            transaction_destroy(chain->pending_transactions[i]);
        }
    }

    safe_free(chain);
    current_blockchain = NULL;
    log_message(LOG_INFO, "Blockchain destroyed");
}

// Block operations
int blockchain_add_block(Blockchain* chain, Block* block) {
    if (!chain || !block) return BLOCKCHAIN_ERROR_INVALID_BLOCK;

    // Validate block
    if (!blockchain_validate_block(chain, block)) {
        log_message(LOG_ERROR, "Block validation failed");
        return BLOCKCHAIN_ERROR_INVALID_BLOCK;
    }

    // Add block to chain
    if (chain->block_count >= MAX_BLOCKS) {
        log_message(LOG_ERROR, "Blockchain full");
        return BLOCKCHAIN_ERROR_INVALID_BLOCK;
    }

    chain->blocks[chain->block_count] = block;
    chain->block_count++;
    chain->last_block_time = time(NULL);
    chain->total_transactions += block->transaction_count;

    // Trigger callback
    if (block_mined_callback) {
        block_mined_callback(block);
    }

    log_message(LOG_INFO, "Block #%d added to blockchain", block->index);
    return BLOCKCHAIN_SUCCESS;
}

Block* blockchain_get_latest_block(const Blockchain* chain) {
    if (!chain || chain->block_count == 0) return NULL;
    return chain->blocks[chain->block_count - 1];
}

Block* blockchain_get_block_by_index(const Blockchain* chain, int index) {
    if (!chain || index < 0 || index >= chain->block_count) return NULL;
    return chain->blocks[index];
}

Block* blockchain_get_block_by_hash(const Blockchain* chain, const char* hash) {
    if (!chain || !hash) return NULL;

    for (int i = 0; i < chain->block_count; i++) {
        if (strcmp(chain->blocks[i]->hash, hash) == 0) {
            return chain->blocks[i];
        }
    }

    return NULL;
}

// Transaction operations
int blockchain_add_transaction(Blockchain* chain, Transaction* transaction) {
    if (!chain || !transaction) return BLOCKCHAIN_ERROR_INVALID_TRANSACTION;

    // Validate transaction
    if (!transaction_is_valid(transaction)) {
        log_message(LOG_ERROR, "Transaction validation failed");
        return BLOCKCHAIN_ERROR_INVALID_TRANSACTION;
    }

    // Check for double spending
    if (blockchain_detect_double_spending(chain, transaction)) {
        log_message(LOG_ERROR, "Double spending detected");
        return BLOCKCHAIN_ERROR_DOUBLE_SPEND;
    }

    // Add to pending transactions
    if (chain->pending_count >= MAX_PENDING_TRANSACTIONS) {
        log_message(LOG_WARNING, "Pending transaction pool full");
        return BLOCKCHAIN_ERROR_INVALID_TRANSACTION;
    }

    chain->pending_transactions[chain->pending_count] = transaction;
    chain->pending_count++;

    // Trigger callback
    if (transaction_added_callback) {
        transaction_added_callback(transaction);
    }

    log_message(LOG_INFO, "Transaction added to pending pool");
    return BLOCKCHAIN_SUCCESS;
}

int blockchain_get_pending_transactions(const Blockchain* chain, Transaction** transactions, int max_count) {
    if (!chain || !transactions) return 0;

    int count = chain->pending_count < max_count ? chain->pending_count : max_count;
    for (int i = 0; i < count; i++) {
        transactions[i] = chain->pending_transactions[i];
    }

    return count;
}

int blockchain_clear_pending_transactions(Blockchain* chain) {
    if (!chain) return BLOCKCHAIN_ERROR_INVALID_INPUT;

    for (int i = 0; i < chain->pending_count; i++) {
        transaction_destroy(chain->pending_transactions[i]);
        chain->pending_transactions[i] = NULL;
    }

    chain->pending_count = 0;
    return BLOCKCHAIN_SUCCESS;
}

// Mining operations
int blockchain_mine_pending_transactions(Blockchain* chain) {
    if (!chain || chain->pending_count == 0) return BLOCKCHAIN_ERROR_INVALID_INPUT;

    chain->mining_status = MINING_ACTIVE;
    chain->status = BLOCKCHAIN_STATUS_SYNCING;

    // Create new block
    Block* latest_block = blockchain_get_latest_block(chain);
    Block* new_block = block_create(latest_block->index + 1, latest_block->hash, chain->difficulty);

    if (!new_block) {
        chain->mining_status = MINING_FAILED;
        chain->status = BLOCKCHAIN_STATUS_ACTIVE;
        return BLOCKCHAIN_ERROR_MEMORY;
    }

    // Add transactions to block
    for (int i = 0; i < chain->pending_count; i++) {
        if (block_add_transaction(new_block, chain->pending_transactions[i]) != 0) {
            block_destroy(new_block);
            chain->mining_status = MINING_FAILED;
            chain->status = BLOCKCHAIN_STATUS_ACTIVE;
            return BLOCKCHAIN_ERROR_INVALID_TRANSACTION;
        }
    }

    // Mine the block
    time_t mining_start = time(NULL);
    MiningStats mining_stats = {0};

    if (block_mine(new_block, &mining_stats) != 0) {
        block_destroy(new_block);
        chain->mining_status = MINING_FAILED;
        chain->status = BLOCKCHAIN_STATUS_ACTIVE;
        return BLOCKCHAIN_ERROR_MINING_FAILED;
    }

    time_t mining_end = time(NULL);

    // Add block to chain
    if (blockchain_add_block(chain, new_block) != BLOCKCHAIN_SUCCESS) {
        block_destroy(new_block);
        chain->mining_status = MINING_FAILED;
        chain->status = BLOCKCHAIN_STATUS_ACTIVE;
        return BLOCKCHAIN_ERROR_INVALID_BLOCK;
    }

    // Clear pending transactions
    blockchain_clear_pending_transactions(chain);

    // Update mining status
    chain->mining_status = MINING_SUCCESS;
    chain->status = BLOCKCHAIN_STATUS_ACTIVE;

    log_message(LOG_INFO, "Block mined successfully in %ld seconds", mining_end - mining_start);
    return BLOCKCHAIN_SUCCESS;
}

int blockchain_adjust_difficulty(Blockchain* chain) {
    if (!chain || chain->block_count < 2) return BLOCKCHAIN_ERROR_INVALID_INPUT;

    // Simple difficulty adjustment based on block time
    time_t avg_block_time = blockchain_get_average_block_time(chain);
    time_t target_time = BLOCK_TIME_SECONDS;

    if (avg_block_time < target_time) {
        // Blocks are coming too fast, increase difficulty
        chain->difficulty++;
    } else if (avg_block_time > target_time * 2 && chain->difficulty > 1) {
        // Blocks are coming too slow, decrease difficulty
        chain->difficulty--;
    }

    return BLOCKCHAIN_SUCCESS;
}

// Validation operations
bool blockchain_validate_chain(const Blockchain* chain) {
    if (!chain || chain->block_count == 0) return false;

    for (int i = 1; i < chain->block_count; i++) {
        if (!blockchain_validate_block(chain, chain->blocks[i])) {
            if (chain_invalid_callback) {
                char reason[256];
                sprintf(reason, "Block %d validation failed", i);
                chain_invalid_callback(reason);
            }
            return false;
        }
    }

    return true;
}

bool blockchain_validate_block(const Blockchain* chain, const Block* block) {
    if (!chain || !block) return false;

    // Validate block index
    if (block->index != chain->block_count) return false;

    // Validate previous hash
    Block* prev_block = blockchain_get_block_by_index(chain, block->index - 1);
    if (!prev_block || strcmp(block->previous_hash, prev_block->hash) != 0) {
        return false;
    }

    // Validate block hash
    return block_validate_hash(block);
}

// Query operations
uint64_t blockchain_get_total_votes(const Blockchain* chain, const char* election_id) {
    if (!chain || !election_id) return 0;

    uint64_t total = 0;
    for (int i = 0; i < chain->block_count; i++) {
        Block* block = chain->blocks[i];
        for (int j = 0; j < block->transaction_count; j++) {
            Transaction* tx = block->transactions[j];
            if (strcmp(tx->election_id, election_id) == 0) {
                total += tx->vote_weight;
            }
        }
    }

    return total;
}

uint64_t blockchain_get_votes_for_candidate(const Blockchain* chain, const char* election_id, const char* candidate_id) {
    if (!chain || !election_id || !candidate_id) return 0;

    uint64_t total = 0;
    for (int i = 0; i < chain->block_count; i++) {
        Block* block = chain->blocks[i];
        for (int j = 0; j < block->transaction_count; j++) {
            Transaction* tx = block->transactions[j];
            if (strcmp(tx->election_id, election_id) == 0 &&
                strcmp(tx->candidate_id, candidate_id) == 0) {
                total += tx->vote_weight;
            }
        }
    }

    return total;
}

int blockchain_get_election_results(const Blockchain* chain, const char* election_id, ElectionResult* results, int max_results) {
    if (!chain || !election_id || !results || max_results <= 0) return 0;

    // This is a simplified implementation
    // In a real system, you'd track candidates separately
    ElectionResult result = {0};
    strcpy(result.candidate_id, "CAND001");
    strcpy(result.candidate_name, "Sample Candidate");
    result.vote_count = blockchain_get_total_votes(chain, election_id);
    result.vote_percentage = 100.0f;
    result.rank = 1;

    if (max_results > 0) {
        results[0] = result;
        return 1;
    }

    return 0;
}

// Statistics and information
void blockchain_get_stats(const Blockchain* chain, BlockchainStats* stats) {
    if (!chain || !stats) return;

    stats->total_blocks = chain->block_count;
    stats->total_transactions = chain->total_transactions;
    stats->average_block_time = blockchain_get_average_block_time(chain);
    stats->uptime = time(NULL) - chain->last_block_time;
}

void blockchain_print_info(const Blockchain* chain) {
    if (!chain) return;

    printf("Blockchain Information:\n");
    printf("  Blocks: %d\n", chain->block_count);
    printf("  Difficulty: %d\n", chain->difficulty);
    printf("  Pending Transactions: %d\n", chain->pending_count);
    printf("  Status: %s\n", chain->status == BLOCKCHAIN_STATUS_ACTIVE ? "Active" : "Inactive");
    printf("  Total Transactions: %" PRIu64 "\n", chain->total_transactions);
}

// Utility functions
bool blockchain_is_chain_valid(const Blockchain* chain) {
    return blockchain_validate_chain(chain);
}

int blockchain_get_chain_length(const Blockchain* chain) {
    return chain ? chain->block_count : 0;
}

time_t blockchain_get_average_block_time(const Blockchain* chain) {
    if (!chain || chain->block_count < 2) return BLOCK_TIME_SECONDS;

    time_t total_time = 0;
    int intervals = 0;

    for (int i = 1; i < chain->block_count; i++) {
        time_t time_diff = chain->blocks[i]->mining_time - chain->blocks[i-1]->mining_time;
        total_time += time_diff;
        intervals++;
    }

    return intervals > 0 ? total_time / intervals : BLOCK_TIME_SECONDS;
}

double blockchain_get_hash_rate(const Blockchain* chain) {
    // Simplified hash rate calculation
    return 1000.0; // 1000 hashes per second (placeholder)
}

// Persistence operations (stub implementations)
int blockchain_save_to_file(const Blockchain* chain, const char* filename) {
    // TODO: Implement file saving
    return BLOCKCHAIN_SUCCESS;
}

int blockchain_load_from_file(Blockchain* chain, const char* filename) {
    // TODO: Implement file loading
    return BLOCKCHAIN_SUCCESS;
}

int blockchain_export_to_json(const Blockchain* chain, const char* filename) {
    // TODO: Implement JSON export
    return BLOCKCHAIN_SUCCESS;
}

// Security functions
int blockchain_detect_double_spending(const Blockchain* chain, const Transaction* transaction) {
    // Simplified double-spending detection
    // In a real system, this would check the entire transaction history
    return 0; // No double spending detected
}

int blockchain_verify_transaction_integrity(const Blockchain* chain, const Transaction* transaction) {
    return transaction_is_valid(transaction) ? 0 : -1;
}

bool blockchain_is_transaction_unique(const Blockchain* chain, const Transaction* transaction) {
    // Check if transaction hash is unique in the chain
    for (int i = 0; i < chain->block_count; i++) {
        Block* block = chain->blocks[i];
        for (int j = 0; j < block->transaction_count; j++) {
            if (strcmp(block->transactions[j]->transaction_hash, transaction->transaction_hash) == 0) {
                return false;
            }
        }
    }
    return true;
}

// Configuration
int blockchain_set_difficulty(Blockchain* chain, int difficulty) {
    if (!chain || difficulty < 1) return BLOCKCHAIN_ERROR_INVALID_INPUT;
    chain->difficulty = difficulty;
    return BLOCKCHAIN_SUCCESS;
}

int blockchain_set_auto_save(Blockchain* chain, bool auto_save) {
    if (!chain) return BLOCKCHAIN_ERROR_INVALID_INPUT;
    chain->auto_save = auto_save;
    return BLOCKCHAIN_SUCCESS;
}

int blockchain_set_data_directory(Blockchain* chain, const char* directory) {
    if (!chain || !directory) return BLOCKCHAIN_ERROR_INVALID_INPUT;
    str_copy(directory, chain->data_directory, sizeof(chain->data_directory));
    return BLOCKCHAIN_SUCCESS;
}

// Error handling
const char* blockchain_error_message(BlockchainError error) {
    switch (error) {
        case BLOCKCHAIN_SUCCESS: return "Success";
        case BLOCKCHAIN_ERROR_MEMORY: return "Memory allocation failed";
        case BLOCKCHAIN_ERROR_INVALID_BLOCK: return "Invalid block";
        case BLOCKCHAIN_ERROR_INVALID_TRANSACTION: return "Invalid transaction";
        case BLOCKCHAIN_ERROR_CHAIN_INVALID: return "Blockchain validation failed";
        case BLOCKCHAIN_ERROR_FILE_IO: return "File I/O error";
        case BLOCKCHAIN_ERROR_MINING_FAILED: return "Block mining failed";
        case BLOCKCHAIN_ERROR_DOUBLE_SPEND: return "Double spending detected";
        case BLOCKCHAIN_ERROR_NETWORK: return "Network error";
        default: return "Unknown error";
    }
}

// Callback functions
void blockchain_set_callbacks(Blockchain* chain,
                           BlockMinedCallback block_callback,
                           TransactionAddedCallback transaction_callback,
                           ChainInvalidCallback invalid_callback) {
    block_mined_callback = block_callback;
    transaction_added_callback = transaction_callback;
    chain_invalid_callback = invalid_callback;
}