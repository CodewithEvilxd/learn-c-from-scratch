/*
 * Election Management Header
 * Election creation, management, and result calculation
 */

#ifndef ELECTION_H
#define ELECTION_H

#include <time.h>
#include <stdbool.h>
#include <stdint.h>

// Election field sizes
#define ELECTION_ID_SIZE 50
#define ELECTION_NAME_SIZE 200
#define ELECTION_DESCRIPTION_SIZE 500
#define CANDIDATE_NAME_SIZE 100
#define CANDIDATE_PARTY_SIZE 100

// Election status
typedef enum {
    ELECTION_STATUS_DRAFT,
    ELECTION_STATUS_REGISTERING,
    ELECTION_STATUS_VOTING,
    ELECTION_STATUS_COUNTING,
    ELECTION_STATUS_COMPLETED,
    ELECTION_STATUS_CANCELLED
} ElectionStatus;

// Candidate structure
typedef struct {
    char candidate_id[50];               // Unique candidate identifier
    char name[CANDIDATE_NAME_SIZE];      // Candidate full name
    char party[CANDIDATE_PARTY_SIZE];    // Political party
    char description[500];               // Candidate description
    time_t registration_date;            // Registration timestamp
    bool is_active;                      // Is candidate still active
    uint64_t vote_count;                 // Total votes received
} Candidate;

// Election structure
typedef struct {
    char election_id[ELECTION_ID_SIZE];  // Unique election identifier
    char name[ELECTION_NAME_SIZE];       // Election name
    char description[ELECTION_DESCRIPTION_SIZE]; // Election description
    time_t start_date;                   // Voting start date
    time_t end_date;                     // Voting end date
    ElectionStatus status;               // Current status
    Candidate* candidates[100];          // Array of candidates
    int candidate_count;                 // Number of candidates
    int max_candidates;                  // Maximum candidates allowed
    uint64_t total_votes;                // Total votes cast
    uint64_t eligible_voters;            // Number of eligible voters
    time_t created_date;                 // Election creation date
    bool anonymous_voting;               // Is voting anonymous
    bool real_time_results;              // Show real-time results
} Election;

// Election results
typedef struct {
    char candidate_id[50];
    char candidate_name[CANDIDATE_NAME_SIZE];
    char party[CANDIDATE_PARTY_SIZE];
    uint64_t vote_count;
    double vote_percentage;
    int rank;
} ElectionResult;

// Election database
typedef struct {
    Election* elections[100];            // Array of elections
    int count;                           // Number of elections
    char filename[256];                  // Database file
} ElectionDatabase;

// Function declarations

// Election lifecycle
Election* election_create(const char* name, const char* description, time_t start_date, time_t end_date);
void election_destroy(Election* election);

// Election operations
int election_add_candidate(Election* election, const char* name, const char* party, const char* description);
int election_remove_candidate(Election* election, const char* candidate_id);
int election_start_voting(Election* election);
int election_end_voting(Election* election);
int election_cancel(Election* election);

// Candidate operations
Candidate* election_find_candidate(const Election* election, const char* candidate_id);
int election_get_candidate_count(const Election* election);
Candidate** election_get_all_candidates(Election* election, int* count);

// Voting operations
int election_cast_vote(Election* election, const char* candidate_id);
int election_validate_vote(const Election* election, const char* candidate_id);
bool election_is_voting_open(const Election* election);

// Results calculation
int election_calculate_results(const Election* election, ElectionResult* results, int max_results);
int election_get_winner(const Election* election, ElectionResult* winner);
double election_get_turnout_percentage(const Election* election);

// Election database operations
ElectionDatabase* election_database_create(void);
void election_database_destroy(ElectionDatabase* db);
int election_database_add(ElectionDatabase* db, Election* election);
Election* election_database_find_by_id(const ElectionDatabase* db, const char* election_id);
int election_database_remove(ElectionDatabase* db, const char* election_id);

// Database persistence
int election_database_save(const ElectionDatabase* db, const char* filename);
int election_database_load(ElectionDatabase* db, const char* filename);

// Validation
bool election_validate_dates(time_t start_date, time_t end_date);
bool election_validate_candidate_count(const Election* election);
bool election_is_valid_candidate_id(const Election* election, const char* candidate_id);

// Statistics
typedef struct {
    int total_elections;
    int active_elections;
    int completed_elections;
    uint64_t total_votes_cast;
    double average_turnout;
} ElectionStats;

void election_database_get_stats(const ElectionDatabase* db, ElectionStats* stats);

// Utility functions
void election_print_info(const Election* election);
void election_print_candidates(const Election* election);
void election_print_results(const Election* election);
char* election_status_to_string(ElectionStatus status);

// Error handling
typedef enum {
    ELECTION_SUCCESS = 0,
    ELECTION_ERROR_INVALID_DATES = -1,
    ELECTION_ERROR_TOO_MANY_CANDIDATES = -2,
    ELECTION_ERROR_CANDIDATE_NOT_FOUND = -3,
    ELECTION_ERROR_VOTING_CLOSED = -4,
    ELECTION_ERROR_VOTING_NOT_OPEN = -5,
    ELECTION_ERROR_ALREADY_EXISTS = -6,
    ELECTION_ERROR_NOT_FOUND = -7,
    ELECTION_ERROR_UNKNOWN = -99
} ElectionError;

const char* election_error_message(ElectionError error);

#endif // ELECTION_H