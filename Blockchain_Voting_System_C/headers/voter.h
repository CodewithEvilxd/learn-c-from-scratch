/*
 * Voter Management Header
 * Voter registration and authentication system
 */

#ifndef VOTER_H
#define VOTER_H

#include <time.h>
#include <stdbool.h>

// Voter field sizes
#define VOTER_ID_SIZE 50
#define VOTER_NAME_SIZE 100
#define VOTER_EMAIL_SIZE 100
#define VOTER_ADDRESS_SIZE 200
#define VOTER_PHONE_SIZE 20

// Voter status
typedef enum {
    VOTER_STATUS_REGISTERED,
    VOTER_STATUS_VERIFIED,
    VOTER_STATUS_VOTED,
    VOTER_STATUS_SUSPENDED,
    VOTER_STATUS_INACTIVE
} VoterStatus;

// Voter structure
typedef struct {
    char voter_id[VOTER_ID_SIZE];        // Unique voter identifier
    char name[VOTER_NAME_SIZE];          // Full name
    char email[VOTER_EMAIL_SIZE];        // Email address
    char address[VOTER_ADDRESS_SIZE];    // Physical address
    char phone[VOTER_PHONE_SIZE];        // Phone number
    time_t date_of_birth;                // Date of birth
    time_t registration_date;            // Registration timestamp
    VoterStatus status;                  // Current status
    bool has_voted;                      // Has voted in current election
    char last_vote_election[50];         // Last election voted in
    time_t last_vote_time;               // Last vote timestamp
    int vote_count;                      // Total votes cast
} Voter;

// Voter database
typedef struct {
    Voter* voters[10000];                // Array of voter pointers
    int count;                           // Number of registered voters
    int max_voters;                      // Maximum capacity
    char filename[256];                  // Database file
} VoterDatabase;

// Function declarations

// Voter lifecycle
Voter* voter_create(const char* name, const char* email, const char* address, const char* phone, time_t dob);
void voter_destroy(Voter* voter);

// Voter operations
int voter_generate_id(Voter* voter);
int voter_verify_identity(const Voter* voter);
int voter_update_status(Voter* voter, VoterStatus status);
bool voter_is_eligible(const Voter* voter, const char* election_id);

// Voter database operations
VoterDatabase* voter_database_create(int max_voters);
void voter_database_destroy(VoterDatabase* db);
int voter_database_add(VoterDatabase* db, Voter* voter);
Voter* voter_database_find_by_id(const VoterDatabase* db, const char* voter_id);
Voter* voter_database_find_by_email(const VoterDatabase* db, const char* email);
int voter_database_remove(VoterDatabase* db, const char* voter_id);

// Database persistence
int voter_database_save(const VoterDatabase* db, const char* filename);
int voter_database_load(VoterDatabase* db, const char* filename);
int voter_database_import_csv(VoterDatabase* db, const char* filename);

// Validation
bool voter_validate_email(const char* email);
bool voter_validate_phone(const char* phone);
bool voter_validate_age(const Voter* voter, int minimum_age);
bool voter_validate_address(const char* address);

// Statistics
typedef struct {
    int total_voters;
    int verified_voters;
    int voted_voters;
    int suspended_voters;
    time_t average_registration_age;
} VoterStats;

void voter_database_get_stats(const VoterDatabase* db, VoterStats* stats);

// Search and filtering
int voter_database_search(const VoterDatabase* db, const char* query, Voter* results[], int max_results);
int voter_database_filter_by_status(const VoterDatabase* db, VoterStatus status, Voter* results[], int max_results);
int voter_database_filter_by_age_range(const VoterDatabase* db, int min_age, int max_age, Voter* results[], int max_results);

// Bulk operations
int voter_database_bulk_register(VoterDatabase* db, Voter* voters[], int count);
int voter_database_bulk_verify(VoterDatabase* db, const char* voter_ids[], int count);
int voter_database_bulk_suspend(VoterDatabase* db, const char* voter_ids[], int count);

// Error handling
typedef enum {
    VOTER_SUCCESS = 0,
    VOTER_ERROR_INVALID_DATA = -1,
    VOTER_ERROR_DUPLICATE_ID = -2,
    VOTER_ERROR_NOT_FOUND = -3,
    VOTER_ERROR_ALREADY_VOTED = -4,
    VOTER_ERROR_NOT_ELIGIBLE = -5,
    VOTER_ERROR_DATABASE_FULL = -6,
    VOTER_ERROR_UNKNOWN = -99
} VoterError;

const char* voter_error_message(VoterError error);

#endif // VOTER_H