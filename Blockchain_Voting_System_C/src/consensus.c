/*
 * Consensus Implementation
 * Proof-of-Work and consensus algorithms
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include "../headers/consensus.h"
#include "../headers/crypto.h"

// Static variables
static ConsensusAlgorithm current_algorithm = CONSENSUS_POW;

// Proof-of-Work functions
MiningResult pow_mine_block(const char* block_data, char* nonce_output, size_t nonce_size, const MiningConfig* config) {
    if (!block_data || !nonce_output || !config) return MINE_FAILED;

    char test_hash[65];
    uint32_t nonce = 0;
    time_t start_time = time(NULL);

    while (1) {
        // Create test data with nonce
        char test_data[1024];
        sprintf(test_data, "%s%u", block_data, nonce);

        // Calculate hash
        uint8_t hash[SHA256_DIGEST_SIZE];
        sha256_hash((const uint8_t*)test_data, strlen(test_data), hash);
        sha256_to_hex(hash, test_hash);

        // Check if meets difficulty
        if (crypto_verify_difficulty(test_hash, config->difficulty)) {
            sprintf(nonce_output, "%u", nonce);
            return MINING_SUCCESS;
        }

        nonce++;

        // Check timeout
        if (config->timeout_seconds > 0) {
            time_t current_time = time(NULL);
            if (difftime(current_time, start_time) >= config->timeout_seconds) {
                return MINE_TIMEOUT;
            }
        }

        // Check nonce limit
        if (nonce >= config->max_nonce) {
            return MINE_FAILED;
        }
    }
}

bool pow_validate_proof(const char* block_hash, int difficulty) {
    return crypto_verify_difficulty(block_hash, difficulty);
}

int pow_adjust_difficulty(int current_difficulty, time_t actual_time, time_t target_time) {
    if (actual_time < target_time / 2) {
        return current_difficulty + 1; // Increase difficulty
    } else if (actual_time > target_time * 2) {
        return current_difficulty > 1 ? current_difficulty - 1 : 1; // Decrease difficulty
    }
    return current_difficulty; // Keep same
}

// Consensus validation
bool consensus_validate_block(const void* block_data, const ConsensusAlgorithm algorithm) {
    // Stub implementation
    return true;
}

bool consensus_validate_chain(const void* chain_data, const ConsensusAlgorithm algorithm) {
    // Stub implementation
    return true;
}

int consensus_get_required_confirmations(const ConsensusAlgorithm algorithm) {
    switch (algorithm) {
        case CONSENSUS_POW: return 6;
        case CONSENSUS_POS: return 30;
        case CONSENSUS_DPOS: return 15;
        case CONSENSUS_PBFT: return 1;
        default: return 6;
    }
}

// Mining utilities
double consensus_calculate_hash_rate(uint64_t hashes, time_t time_seconds) {
    if (time_seconds == 0) return 0.0;
    return (double)hashes / time_seconds;
}

time_t consensus_estimate_mining_time(int difficulty, double hash_rate) {
    if (hash_rate == 0) return 0;

    // Rough estimation: 16^difficulty possibilities
    double total_attempts = 1.0;
    for (int i = 0; i < difficulty; i++) {
        total_attempts *= 16.0;
    }

    return (time_t)(total_attempts / hash_rate);
}

int consensus_get_target_difficulty(time_t block_time, time_t target_time, int current_difficulty) {
    return pow_adjust_difficulty(current_difficulty, block_time, target_time);
}

// Network consensus
bool consensus_reach_network_consensus(const void* local_chain, const void* network_chains[], int network_count) {
    // Stub implementation - always return true for demo
    return true;
}

int consensus_resolve_conflicts(const void* chains[], int chain_count, int* winner_index) {
    // Stub implementation - return first chain
    if (winner_index) *winner_index = 0;
    return 0;
}

// Statistics and monitoring
void consensus_update_stats(ConsensusStats* stats, MiningResult result, time_t mining_time, uint64_t hashes) {
    if (!stats) return;

    stats->total_blocks_mined++;
    stats->total_hashes_computed += hashes;

    if (mining_time > 0) {
        stats->average_block_time = (stats->average_block_time + mining_time) / 2.0;
        stats->network_hash_rate = consensus_calculate_hash_rate(stats->total_hashes_computed, mining_time);
    }

    stats->last_block_time = time(NULL);
}

void consensus_print_stats(const ConsensusStats* stats) {
    if (!stats) return;

    printf("Consensus Statistics:\n");
    printf("  Blocks Mined: %" PRIu64 "\n", stats->total_blocks_mined);
    printf("  Total Hashes: %" PRIu64 "\n", stats->total_hashes_computed);
    printf("  Average Block Time: %.2f seconds\n", stats->average_block_time);
    printf("  Network Hash Rate: %.2f H/s\n", stats->network_hash_rate);
}

void consensus_reset_stats(ConsensusStats* stats) {
    if (stats) {
        memset(stats, 0, sizeof(ConsensusStats));
    }
}

// Configuration
int consensus_set_algorithm(ConsensusAlgorithm algorithm) {
    current_algorithm = algorithm;
    return 0;
}

ConsensusAlgorithm consensus_get_algorithm(void) {
    return current_algorithm;
}

int consensus_configure_mining(const MiningConfig* config) {
    // Stub implementation
    return 0;
}

// Error handling
const char* consensus_error_message(ConsensusError error) {
    switch (error) {
        case CONSENSUS_SUCCESS: return "Success";
        case CONSENSUS_ERROR_INVALID_BLOCK: return "Invalid block";
        case CONSENSUS_ERROR_INVALID_CHAIN: return "Invalid chain";
        case CONSENSUS_ERROR_MINING_FAILED: return "Mining failed";
        case CONSENSUS_ERROR_NETWORK_FAILURE: return "Network failure";
        case CONSENSUS_ERROR_TIMEOUT: return "Timeout";
        default: return "Unknown error";
    }
}