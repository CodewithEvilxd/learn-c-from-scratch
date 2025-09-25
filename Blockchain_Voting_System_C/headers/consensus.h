/*
 * Consensus Header - Proof-of-Work and Consensus Algorithms
 * Consensus mechanism for blockchain validation
 */

#ifndef CONSENSUS_H
#define CONSENSUS_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "blockchain.h"

// Consensus algorithms
typedef enum {
    CONSENSUS_POW,        // Proof-of-Work
    CONSENSUS_POS,        // Proof-of-Stake (future)
    CONSENSUS_DPOS,       // Delegated Proof-of-Stake (future)
    CONSENSUS_PBFT        // Practical Byzantine Fault Tolerance (future)
} ConsensusAlgorithm;

// Mining status (defined in blockchain.h)

// Mining result
typedef enum {
    MINE_SUCCESS,
    MINE_FAILED,
    MINE_TIMEOUT,
    MINE_INTERRUPTED
} MiningResult;

// Mining configuration
typedef struct {
    int difficulty;
    int max_nonce;
    time_t timeout_seconds;
    bool allow_interrupt;
} MiningConfig;

// Consensus statistics
typedef struct {
    uint64_t total_blocks_mined;
    uint64_t total_hashes_computed;
    double average_block_time;
    double network_hash_rate;
    time_t last_block_time;
} ConsensusStats;

// Function declarations

// Proof-of-Work functions
MiningResult pow_mine_block(const char* block_data, char* nonce_output, size_t nonce_size, const MiningConfig* config);
bool pow_validate_proof(const char* block_hash, int difficulty);
int pow_adjust_difficulty(int current_difficulty, time_t actual_time, time_t target_time);

// Consensus validation
bool consensus_validate_block(const void* block_data, const ConsensusAlgorithm algorithm);
bool consensus_validate_chain(const void* chain_data, const ConsensusAlgorithm algorithm);
int consensus_get_required_confirmations(const ConsensusAlgorithm algorithm);

// Mining utilities
double consensus_calculate_hash_rate(uint64_t hashes, time_t time_seconds);
time_t consensus_estimate_mining_time(int difficulty, double hash_rate);
int consensus_get_target_difficulty(time_t block_time, time_t target_time, int current_difficulty);

// Network consensus
bool consensus_reach_network_consensus(const void* local_chain, const void* network_chains[], int network_count);
int consensus_resolve_conflicts(const void* chains[], int chain_count, int* winner_index);

// Statistics and monitoring
void consensus_update_stats(ConsensusStats* stats, MiningResult result, time_t mining_time, uint64_t hashes);
void consensus_print_stats(const ConsensusStats* stats);
void consensus_reset_stats(ConsensusStats* stats);

// Configuration
int consensus_set_algorithm(ConsensusAlgorithm algorithm);
ConsensusAlgorithm consensus_get_algorithm(void);
int consensus_configure_mining(const MiningConfig* config);

// Error handling
typedef enum {
    CONSENSUS_SUCCESS = 0,
    CONSENSUS_ERROR_INVALID_BLOCK = -1,
    CONSENSUS_ERROR_INVALID_CHAIN = -2,
    CONSENSUS_ERROR_MINING_FAILED = -3,
    CONSENSUS_ERROR_NETWORK_FAILURE = -4,
    CONSENSUS_ERROR_TIMEOUT = -5,
    CONSENSUS_ERROR_UNKNOWN = -99
} ConsensusError;

const char* consensus_error_message(ConsensusError error);

#endif // CONSENSUS_H