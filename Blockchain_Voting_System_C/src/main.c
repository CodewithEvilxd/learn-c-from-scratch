/*
 * Blockchain Voting System - Main Entry Point
 * A secure, decentralized voting system implemented in pure C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <inttypes.h>
#include "../headers/blockchain.h"
#include "../headers/transaction.h"
#include "../headers/block.h"
#include "../headers/crypto.h"
#include "../headers/voter.h"
#include "../headers/election.h"
#include "../headers/consensus.h"
#include "../headers/network.h"
#include "../headers/utils.h"

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 10

// Global system components
static Blockchain* blockchain = NULL;
static VoterDatabase* voter_db = NULL;
static ElectionDatabase* election_db = NULL;
static P2PNetwork* network = NULL;

// Function prototypes
void print_banner(void);
void print_help(void);
int process_command(int argc, char* argv[]);
int initialize_system(void);
void cleanup_system(void);

// Command handlers
int cmd_create_election(int argc, char* argv[]);
int cmd_add_candidate(int argc, char* argv[]);
int cmd_register_voter(int argc, char* argv[]);
int cmd_cast_vote(int argc, char* argv[]);
int cmd_get_results(int argc, char* argv[]);
int cmd_blockchain_info(int argc, char* argv[]);
int cmd_validate_chain(int argc, char* argv[]);
int cmd_mine_block(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Initialize logging
    set_log_level(LOG_INFO);
    set_log_file("voting_system.log");

    log_message(LOG_INFO, "Starting Blockchain Voting System");

    // Initialize system components
    if (initialize_system() != 0) {
        log_message(LOG_ERROR, "Failed to initialize system");
        return EXIT_FAILURE;
    }

    // Print banner
    print_banner();

    // Process command line arguments or enter interactive mode
    if (argc > 1) {
        // Command line mode
        if (process_command(argc - 1, &argv[1]) != 0) {
            log_message(LOG_ERROR, "Command execution failed");
            cleanup_system();
            return EXIT_FAILURE;
        }
    } else {
        // Interactive mode
        printf("Type 'help' for available commands or 'quit' to exit.\n\n");

        char input[MAX_COMMAND_LENGTH];
        while (1) {
            printf("voting> ");
            fflush(stdout);

            if (!fgets(input, sizeof(input), stdin)) {
                break;
            }

            // Remove newline
            input[strcspn(input, "\n")] = 0;

            // Skip empty input
            if (strlen(input) == 0) continue;

            // Parse command
            char* args[MAX_ARGS];
            int arg_count = 0;

            char* token = strtok(input, " ");
            while (token && arg_count < MAX_ARGS) {
                args[arg_count++] = token;
                token = strtok(NULL, " ");
            }

            if (arg_count == 0) continue;

            // Check for exit commands
            if (strcmp(args[0], "quit") == 0 || strcmp(args[0], "exit") == 0) {
                printf("Goodbye!\n");
                break;
            }

            // Check for help
            if (strcmp(args[0], "help") == 0) {
                print_help();
                continue;
            }

            // Process command
            if (process_command(arg_count, args) != 0) {
                printf("Command failed. Type 'help' for available commands.\n");
            }
        }
    }

    // Cleanup
    cleanup_system();
    log_message(LOG_INFO, "Blockchain Voting System shutdown complete");

    return EXIT_SUCCESS;
}

void print_banner(void) {
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    🔗 BLOCKCHAIN VOTING SYSTEM in C                        ║\n");
    printf("║                                                                              ║\n");
    printf("║  A secure, decentralized voting platform ensuring transparency and security  ║\n");
    printf("║                                                                              ║\n");
    printf("║  Features:                                                                   ║\n");
    printf("║  • SHA-256 Cryptographic Security                                           ║\n");
    printf("║  • Proof-of-Work Consensus                                                  ║\n");
    printf("║  • Immutable Blockchain Ledger                                              ║\n");
    printf("║  • Anonymous Voting System                                                  ║\n");
    printf("║  • Real-time Election Results                                               ║\n");
    printf("║  • Decentralized P2P Network                                               ║\n");
    printf("║                                                                              ║\n");
    printf("║  Type 'help' for commands or 'quit' to exit                                 ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n\n");
}

void print_help(void) {
    printf("\n📚 BLOCKCHAIN VOTING SYSTEM HELP\n");
    printf("================================\n\n");

    printf("🗳️  ELECTION MANAGEMENT:\n");
    printf("  create-election <name> <start-date> <end-date>    Create new election\n");
    printf("  add-candidate <election-id> <name> <party>        Add candidate to election\n");
    printf("  list-elections                                     List all elections\n");
    printf("  election-info <election-id>                       Show election details\n\n");

    printf("👥 VOTER MANAGEMENT:\n");
    printf("  register-voter <name> <email> <address>           Register new voter\n");
    printf("  list-voters                                        List all registered voters\n");
    printf("  voter-info <voter-id>                             Show voter information\n\n");

    printf("🗳️  VOTING OPERATIONS:\n");
    printf("  cast-vote <voter-id> <election-id> <candidate-id> Cast a vote\n");
    printf("  get-results <election-id>                         Get election results\n");
    printf("  verify-vote <transaction-hash>                    Verify a vote\n\n");

    printf("⛓️  BLOCKCHAIN OPERATIONS:\n");
    printf("  blockchain-info                                   Show blockchain information\n");
    printf("  validate-chain                                    Validate entire blockchain\n");
    printf("  mine-block                                        Mine pending transactions\n");
    printf("  list-blocks                                       List all blocks\n");
    printf("  block-info <block-index>                          Show block details\n\n");

    printf("🔧 SYSTEM COMMANDS:\n");
    printf("  status                                            Show system status\n");
    printf("  save-data                                         Save all data to disk\n");
    printf("  load-data                                         Load data from disk\n");
    printf("  clear-data                                        Clear all data\n");
    printf("  help                                              Show this help message\n");
    printf("  quit/exit                                         Exit the system\n\n");

    printf("📝 NOTES:\n");
    printf("  • Dates should be in YYYY-MM-DD format\n");
    printf("  • All IDs are auto-generated\n");
    printf("  • Votes are anonymous and immutable\n");
    printf("  • Blockchain ensures election integrity\n\n");
}

int process_command(int argc, char* argv[]) {
    if (argc == 0) return -1;

    const char* command = argv[0];

    // Election commands
    if (strcmp(command, "create-election") == 0) {
        return cmd_create_election(argc, argv);
    }
    else if (strcmp(command, "add-candidate") == 0) {
        return cmd_add_candidate(argc, argv);
    }
    else if (strcmp(command, "list-elections") == 0) {
        // TODO: Implement
        printf("List elections not implemented yet\n");
        return 0;
    }
    else if (strcmp(command, "election-info") == 0) {
        // TODO: Implement
        printf("Election info not implemented yet\n");
        return 0;
    }

    // Voter commands
    else if (strcmp(command, "register-voter") == 0) {
        return cmd_register_voter(argc, argv);
    }
    else if (strcmp(command, "list-voters") == 0) {
        // TODO: Implement
        printf("List voters not implemented yet\n");
        return 0;
    }
    else if (strcmp(command, "voter-info") == 0) {
        // TODO: Implement
        printf("Voter info not implemented yet\n");
        return 0;
    }

    // Voting commands
    else if (strcmp(command, "cast-vote") == 0) {
        return cmd_cast_vote(argc, argv);
    }
    else if (strcmp(command, "get-results") == 0) {
        return cmd_get_results(argc, argv);
    }
    else if (strcmp(command, "verify-vote") == 0) {
        // TODO: Implement
        printf("Verify vote not implemented yet\n");
        return 0;
    }

    // Blockchain commands
    else if (strcmp(command, "blockchain-info") == 0) {
        return cmd_blockchain_info(argc, argv);
    }
    else if (strcmp(command, "validate-chain") == 0) {
        return cmd_validate_chain(argc, argv);
    }
    else if (strcmp(command, "mine-block") == 0) {
        return cmd_mine_block(argc, argv);
    }
    else if (strcmp(command, "list-blocks") == 0) {
        // TODO: Implement
        printf("List blocks not implemented yet\n");
        return 0;
    }
    else if (strcmp(command, "block-info") == 0) {
        // TODO: Implement
        printf("Block info not implemented yet\n");
        return 0;
    }

    // System commands
    else if (strcmp(command, "status") == 0) {
        printf("System Status: Active\n");
        printf("Blockchain: %d blocks\n", blockchain ? blockchain->block_count : 0);
        printf("Voters: %d registered\n", voter_db ? voter_db->count : 0);
        printf("Elections: %d active\n", election_db ? election_db->count : 0);
        return 0;
    }
    else if (strcmp(command, "save-data") == 0) {
        // TODO: Implement
        printf("Data saving not implemented yet\n");
        return 0;
    }
    else if (strcmp(command, "load-data") == 0) {
        // TODO: Implement
        printf("Data loading not implemented yet\n");
        return 0;
    }
    else if (strcmp(command, "clear-data") == 0) {
        // TODO: Implement
        printf("Data clearing not implemented yet\n");
        return 0;
    }

    printf("Unknown command: %s\n", command);
    printf("Type 'help' for available commands.\n");
    return -1;
}

int initialize_system(void) {
    log_message(LOG_INFO, "Initializing system components");

    // Create blockchain
    blockchain = blockchain_create();
    if (!blockchain) {
        log_message(LOG_ERROR, "Failed to create blockchain");
        return -1;
    }

    // Create voter database
    voter_db = voter_database_create(1000);
    if (!voter_db) {
        log_message(LOG_ERROR, "Failed to create voter database");
        return -1;
    }

    // Create election database
    election_db = election_database_create();
    if (!election_db) {
        log_message(LOG_ERROR, "Failed to create election database");
        return -1;
    }

    // Create P2P network (simulated)
    network = network_create(DEFAULT_PORT);
    if (!network) {
        log_message(LOG_ERROR, "Failed to create network");
        return -1;
    }

    log_message(LOG_INFO, "System initialization complete");
    return 0;
}

void cleanup_system(void) {
    log_message(LOG_INFO, "Cleaning up system components");

    if (network) {
        network_destroy(network);
        network = NULL;
    }

    if (election_db) {
        election_database_destroy(election_db);
        election_db = NULL;
    }

    if (voter_db) {
        voter_database_destroy(voter_db);
        voter_db = NULL;
    }

    if (blockchain) {
        blockchain_destroy(blockchain);
        blockchain = NULL;
    }

    log_message(LOG_INFO, "System cleanup complete");
}

// Command implementations
int cmd_create_election(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: create-election <name> <start-date> <end-date>\n");
        return -1;
    }

    const char* name = argv[1];
    const char* start_date_str = argv[2];
    const char* end_date_str = argv[3];

    // Parse dates
    time_t start_date = parse_date(start_date_str);
    time_t end_date = parse_date(end_date_str);

    if (start_date == (time_t)-1 || end_date == (time_t)-1) {
        printf("Invalid date format. Use YYYY-MM-DD\n");
        return -1;
    }

    // Create election
    Election* election = election_create(name, "", start_date, end_date);
    if (!election) {
        printf("Failed to create election\n");
        return -1;
    }

    // Add to database
    if (election_database_add(election_db, election) != 0) {
        printf("Failed to add election to database\n");
        election_destroy(election);
        return -1;
    }

    printf("Election created successfully!\n");
    printf("Election ID: %s\n", election->election_id);
    printf("Name: %s\n", election->name);
    printf("Duration: %s to %s\n", start_date_str, end_date_str);

    return 0;
}

int cmd_add_candidate(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: add-candidate <election-id> <name> <party>\n");
        return -1;
    }

    const char* election_id = argv[1];
    const char* candidate_name = argv[2];
    const char* party = argv[3];

    // Find election
    Election* election = election_database_find_by_id(election_db, election_id);
    if (!election) {
        printf("Election not found: %s\n", election_id);
        return -1;
    }

    // Add candidate
    if (election_add_candidate(election, candidate_name, party, "") != 0) {
        printf("Failed to add candidate\n");
        return -1;
    }

    printf("Candidate added successfully!\n");
    printf("Election: %s\n", election->name);
    printf("Candidate: %s (%s)\n", candidate_name, party);

    return 0;
}

int cmd_register_voter(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: register-voter <name> <email> <address>\n");
        return -1;
    }

    const char* name = argv[1];
    const char* email = argv[2];
    const char* address = argv[3];

    // Create voter
    Voter* voter = voter_create(name, email, address, "", time(NULL) - 365*24*3600*25); // 25 years ago
    if (!voter) {
        printf("Failed to create voter\n");
        return -1;
    }

    // Add to database
    if (voter_database_add(voter_db, voter) != 0) {
        printf("Failed to register voter\n");
        voter_destroy(voter);
        return -1;
    }

    printf("Voter registered successfully!\n");
    printf("Voter ID: %s\n", voter->voter_id);
    printf("Name: %s\n", voter->name);
    printf("Email: %s\n", voter->email);

    return 0;
}

int cmd_cast_vote(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: cast-vote <voter-id> <election-id> <candidate-id>\n");
        return -1;
    }

    const char* voter_id = argv[1];
    const char* election_id = argv[2];
    const char* candidate_id = argv[3];

    // Find voter
    Voter* voter = voter_database_find_by_id(voter_db, voter_id);
    if (!voter) {
        printf("Voter not found: %s\n", voter_id);
        return -1;
    }

    // Check if voter already voted
    if (voter->has_voted) {
        printf("Voter has already voted in this election\n");
        return -1;
    }

    // Find election
    Election* election = election_database_find_by_id(election_db, election_id);
    if (!election) {
        printf("Election not found: %s\n", election_id);
        return -1;
    }

    // Check if voting is open
    time_t now = time(NULL);
    if (now < election->start_date || now > election->end_date) {
        printf("Voting is not currently open for this election\n");
        return -1;
    }

    // Create transaction
    Transaction* transaction = transaction_create(voter_id, election_id, candidate_id, TX_TYPE_VOTE);
    if (!transaction) {
        printf("Failed to create vote transaction\n");
        return -1;
    }

    // Add to blockchain
    if (blockchain_add_transaction(blockchain, transaction) != 0) {
        printf("Failed to add vote to blockchain\n");
        transaction_destroy(transaction);
        return -1;
    }

    // Mark voter as voted
    voter->has_voted = true;
    strcpy(voter->last_vote_election, election_id);
    voter->last_vote_time = time(NULL);
    voter->vote_count++;

    printf("Vote cast successfully!\n");
    printf("Transaction will be included in the next mined block.\n");

    return 0;
}

int cmd_get_results(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: get-results <election-id>\n");
        return -1;
    }

    const char* election_id = argv[1];

    // Find election
    Election* election = election_database_find_by_id(election_db, election_id);
    if (!election) {
        printf("Election not found: %s\n", election_id);
        return -1;
    }

    // Get results from blockchain
    ElectionResult results[100];
    int result_count = blockchain_get_election_results(blockchain, election_id, results, 100);

    if (result_count == 0) {
        printf("No votes found for this election yet.\n");
        return 0;
    }

    printf("Election Results: %s\n", election->name);
    printf("Total Votes: %" PRIu64 "\n", election->total_votes);
    printf("\n");

    for (int i = 0; i < result_count; i++) {
        printf("%d. %s (%s)\n", i + 1, results[i].candidate_name,
               results[i].candidate_id);
        printf("   Votes: %" PRIu64 " (%.2f%%)\n",
               results[i].vote_count, results[i].vote_percentage);
        printf("\n");
    }

    return 0;
}

int cmd_blockchain_info(int argc, char* argv[]) {
    if (!blockchain) {
        printf("Blockchain not initialized\n");
        return -1;
    }

    printf("Blockchain Information:\n");
    printf("Total Blocks: %d\n", blockchain->block_count);
    printf("Current Difficulty: %d\n", blockchain->difficulty);
    printf("Pending Transactions: %d\n", blockchain->pending_count);
    printf("Status: %s\n", blockchain->status == BLOCKCHAIN_STATUS_ACTIVE ? "Active" : "Inactive");

    if (blockchain->block_count > 0) {
        Block* latest = blockchain_get_latest_block(blockchain);
        printf("Latest Block: #%d\n", latest->index);
        printf("Latest Block Hash: %.16s...\n", latest->hash);
        printf("Latest Block Time: %s", ctime(&latest->mining_time));
    }

    return 0;
}

int cmd_validate_chain(int argc, char* argv[]) {
    if (!blockchain) {
        printf("Blockchain not initialized\n");
        return -1;
    }

    printf("Validating blockchain...\n");

    bool is_valid = blockchain_validate_chain(blockchain);

    if (is_valid) {
        printf("✅ Blockchain is valid!\n");
        return 0;
    } else {
        printf("❌ Blockchain validation failed!\n");
        return -1;
    }
}

int cmd_mine_block(int argc, char* argv[]) {
    if (!blockchain) {
        printf("Blockchain not initialized\n");
        return -1;
    }

    if (blockchain->pending_count == 0) {
        printf("No pending transactions to mine\n");
        return 0;
    }

    printf("Mining block with %d transactions...\n", blockchain->pending_count);

    time_t start_time = time(NULL);
    int result = blockchain_mine_pending_transactions(blockchain);
    time_t end_time = time(NULL);

    if (result == 0) {
        printf("✅ Block mined successfully!\n");
        printf("Mining time: %ld seconds\n", end_time - start_time);
        printf("New block count: %d\n", blockchain->block_count);
        return 0;
    } else {
        printf("❌ Block mining failed\n");
        return -1;
    }
}