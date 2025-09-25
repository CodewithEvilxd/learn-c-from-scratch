/*
 * Election Management Implementation
 * Election creation, candidate management, and result calculation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include "../headers/election.h"
#include "../headers/utils.h"

// Election lifecycle
Election* election_create(const char* name, const char* description, time_t start_date, time_t end_date) {
    Election* election = (Election*)safe_malloc(sizeof(Election));
    if (!election) return NULL;

    memset(election, 0, sizeof(Election));

    // Generate election ID
    sprintf(election->election_id, "ELEC_%06d", random_int(100000, 999999));

    // Copy data
    str_copy(name, election->name, sizeof(election->name));
    str_copy(description, election->description, sizeof(election->description));

    election->start_date = start_date;
    election->end_date = end_date;
    election->status = ELECTION_STATUS_DRAFT;
    election->max_candidates = 100;
    election->anonymous_voting = true;
    election->real_time_results = true;
    election->created_date = time(NULL);

    return election;
}

void election_destroy(Election* election) {
    if (!election) return;

    // Free candidates
    for (int i = 0; i < election->candidate_count; i++) {
        if (election->candidates[i]) {
            safe_free(election->candidates[i]);
        }
    }

    safe_free(election);
}

// Election operations
int election_add_candidate(Election* election, const char* name, const char* party, const char* description) {
    if (!election || !name || !party) return ELECTION_ERROR_INVALID_DATES;
    if (election->candidate_count >= election->max_candidates) return ELECTION_ERROR_TOO_MANY_CANDIDATES;

    Candidate* candidate = (Candidate*)safe_malloc(sizeof(Candidate));
    if (!candidate) return ELECTION_ERROR_INVALID_DATES;

    memset(candidate, 0, sizeof(Candidate));

    // Generate candidate ID
    sprintf(candidate->candidate_id, "CAND_%06d", random_int(100000, 999999));

    // Copy data
    str_copy(name, candidate->name, sizeof(candidate->name));
    str_copy(party, candidate->party, sizeof(candidate->party));
    if (description) {
        str_copy(description, candidate->description, sizeof(candidate->description));
    }

    candidate->registration_date = time(NULL);
    candidate->is_active = true;

    election->candidates[election->candidate_count] = candidate;
    election->candidate_count++;

    return ELECTION_SUCCESS;
}

int election_remove_candidate(Election* election, const char* candidate_id) {
    if (!election || !candidate_id) return ELECTION_ERROR_INVALID_DATES;

    for (int i = 0; i < election->candidate_count; i++) {
        if (election->candidates[i] &&
            strcmp(election->candidates[i]->candidate_id, candidate_id) == 0) {

            safe_free(election->candidates[i]);

            // Shift remaining candidates
            for (int j = i; j < election->candidate_count - 1; j++) {
                election->candidates[j] = election->candidates[j + 1];
            }

            election->candidates[election->candidate_count - 1] = NULL;
            election->candidate_count--;

            return ELECTION_SUCCESS;
        }
    }

    return ELECTION_ERROR_CANDIDATE_NOT_FOUND;
}

int election_start_voting(Election* election) {
    if (!election) return ELECTION_ERROR_INVALID_DATES;

    time_t now = time(NULL);
    if (now < election->start_date) return ELECTION_ERROR_VOTING_NOT_OPEN;

    election->status = ELECTION_STATUS_VOTING;
    return ELECTION_SUCCESS;
}

int election_end_voting(Election* election) {
    if (!election) return ELECTION_ERROR_INVALID_DATES;

    election->status = ELECTION_STATUS_COMPLETED;
    return ELECTION_SUCCESS;
}

int election_cancel(Election* election) {
    if (!election) return ELECTION_ERROR_INVALID_DATES;

    election->status = ELECTION_STATUS_CANCELLED;
    return ELECTION_SUCCESS;
}

// Candidate operations
Candidate* election_find_candidate(const Election* election, const char* candidate_id) {
    if (!election || !candidate_id) return NULL;

    for (int i = 0; i < election->candidate_count; i++) {
        if (election->candidates[i] &&
            strcmp(election->candidates[i]->candidate_id, candidate_id) == 0) {
            return election->candidates[i];
        }
    }

    return NULL;
}

int election_get_candidate_count(const Election* election) {
    return election ? election->candidate_count : 0;
}

Candidate** election_get_all_candidates(Election* election, int* count) {
    if (!election || !count) return NULL;

    *count = election->candidate_count;
    return election->candidates;
}

// Voting operations
int election_cast_vote(Election* election, const char* candidate_id) {
    if (!election) return ELECTION_ERROR_INVALID_DATES;
    if (election->status != ELECTION_STATUS_VOTING) return ELECTION_ERROR_VOTING_CLOSED;

    Candidate* candidate = election_find_candidate(election, candidate_id);
    if (!candidate) return ELECTION_ERROR_CANDIDATE_NOT_FOUND;

    candidate->vote_count++;
    election->total_votes++;

    return ELECTION_SUCCESS;
}

int election_validate_vote(const Election* election, const char* candidate_id) {
    if (!election) return ELECTION_ERROR_INVALID_DATES;
    if (election->status != ELECTION_STATUS_VOTING) return ELECTION_ERROR_VOTING_CLOSED;

    return election_find_candidate(election, candidate_id) ? ELECTION_SUCCESS : ELECTION_ERROR_CANDIDATE_NOT_FOUND;
}

bool election_is_voting_open(const Election* election) {
    if (!election) return false;

    time_t now = time(NULL);
    return election->status == ELECTION_STATUS_VOTING &&
           now >= election->start_date &&
           now <= election->end_date;
}

// Results calculation
int election_calculate_results(const Election* election, ElectionResult* results, int max_results) {
    if (!election || !results || max_results <= 0) return 0;

    int result_count = 0;

    for (int i = 0; i < election->candidate_count && result_count < max_results; i++) {
        Candidate* candidate = election->candidates[i];
        if (candidate && candidate->is_active) {
            strcpy(results[result_count].candidate_id, candidate->candidate_id);
            strcpy(results[result_count].candidate_name, candidate->name);
            strcpy(results[result_count].party, candidate->party);
            results[result_count].vote_count = candidate->vote_count;
            results[result_count].vote_percentage = election->total_votes > 0 ?
                (double)candidate->vote_count / election->total_votes * 100.0 : 0.0;
            results[result_count].rank = result_count + 1;

            result_count++;
        }
    }

    // Sort by vote count (simple bubble sort for demonstration)
    for (int i = 0; i < result_count - 1; i++) {
        for (int j = 0; j < result_count - i - 1; j++) {
            if (results[j].vote_count < results[j + 1].vote_count) {
                ElectionResult temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }

    // Update ranks
    for (int i = 0; i < result_count; i++) {
        results[i].rank = i + 1;
    }

    return result_count;
}

int election_get_winner(const Election* election, ElectionResult* winner) {
    if (!election || !winner) return ELECTION_ERROR_INVALID_DATES;

    ElectionResult results[100];
    int count = election_calculate_results(election, results, 100);

    if (count == 0) return ELECTION_ERROR_INVALID_DATES;

    *winner = results[0]; // First result is the winner (highest votes)
    return ELECTION_SUCCESS;
}

double election_get_turnout_percentage(const Election* election) {
    if (!election || election->eligible_voters == 0) return 0.0;

    return (double)election->total_votes / election->eligible_voters * 100.0;
}

// Election database operations (stub implementations)
ElectionDatabase* election_database_create(void) {
    ElectionDatabase* db = (ElectionDatabase*)safe_malloc(sizeof(ElectionDatabase));
    if (!db) return NULL;

    memset(db, 0, sizeof(ElectionDatabase));
    strcpy(db->filename, "elections.db");

    return db;
}

void election_database_destroy(ElectionDatabase* db) {
    if (!db) return;

    for (int i = 0; i < db->count; i++) {
        if (db->elections[i]) {
            election_destroy(db->elections[i]);
        }
    }

    safe_free(db);
}

int election_database_add(ElectionDatabase* db, Election* election) {
    if (!db || !election) return ELECTION_ERROR_INVALID_DATES;
    if (db->count >= 100) return ELECTION_ERROR_INVALID_DATES;

    db->elections[db->count] = election;
    db->count++;

    return ELECTION_SUCCESS;
}

Election* election_database_find_by_id(const ElectionDatabase* db, const char* election_id) {
    if (!db || !election_id) return NULL;

    for (int i = 0; i < db->count; i++) {
        if (db->elections[i] &&
            strcmp(db->elections[i]->election_id, election_id) == 0) {
            return db->elections[i];
        }
    }

    return NULL;
}

int election_database_remove(ElectionDatabase* db, const char* election_id) {
    if (!db || !election_id) return ELECTION_ERROR_INVALID_DATES;

    for (int i = 0; i < db->count; i++) {
        if (db->elections[i] &&
            strcmp(db->elections[i]->election_id, election_id) == 0) {

            election_destroy(db->elections[i]);

            // Shift remaining elections
            for (int j = i; j < db->count - 1; j++) {
                db->elections[j] = db->elections[j + 1];
            }

            db->elections[db->count - 1] = NULL;
            db->count--;

            return ELECTION_SUCCESS;
        }
    }

    return ELECTION_ERROR_NOT_FOUND;
}

// Persistence (stub implementations)
int election_database_save(const ElectionDatabase* db, const char* filename) {
    // TODO: Implement file saving
    return ELECTION_SUCCESS;
}

int election_database_load(ElectionDatabase* db, const char* filename) {
    // TODO: Implement file loading
    return ELECTION_SUCCESS;
}

// Validation
bool election_validate_dates(time_t start_date, time_t end_date) {
    return start_date < end_date && start_date > time(NULL) - 86400; // Allow 1 day grace period
}

bool election_validate_candidate_count(const Election* election) {
    return election && election->candidate_count >= 2 && election->candidate_count <= election->max_candidates;
}

bool election_is_valid_candidate_id(const Election* election, const char* candidate_id) {
    return election_find_candidate(election, candidate_id) != NULL;
}

// Statistics
void election_database_get_stats(const ElectionDatabase* db, ElectionStats* stats) {
    if (!db || !stats) return;

    memset(stats, 0, sizeof(ElectionStats));
    stats->total_elections = db->count;

    for (int i = 0; i < db->count; i++) {
        Election* election = db->elections[i];
        if (election) {
            if (election->status == ELECTION_STATUS_COMPLETED) {
                stats->completed_elections++;
                stats->total_votes_cast += election->total_votes;
            } else if (election->status == ELECTION_STATUS_VOTING) {
                stats->active_elections++;
            }

            if (election->eligible_voters > 0) {
                double turnout = election_get_turnout_percentage(election);
                stats->average_turnout = (stats->average_turnout + turnout) / 2.0;
            }
        }
    }
}

// Utility functions
void election_print_info(const Election* election) {
    if (!election) return;

    printf("Election: %s (%s)\n", election->name, election->election_id);
    printf("Description: %s\n", election->description);
    printf("Status: %s\n", election_status_to_string(election->status));
    printf("Duration: %s to %s\n", ctime(&election->start_date), ctime(&election->end_date));
    printf("Candidates: %d\n", election->candidate_count);
    printf("Total Votes: %" PRIu64 "\n", election->total_votes);
    printf("Anonymous Voting: %s\n", election->anonymous_voting ? "Yes" : "No");
    printf("Real-time Results: %s\n", election->real_time_results ? "Yes" : "No");
}

void election_print_candidates(const Election* election) {
    if (!election) return;

    printf("Candidates:\n");
    for (int i = 0; i < election->candidate_count; i++) {
        Candidate* candidate = election->candidates[i];
        if (candidate) {
            printf("  %s: %s (%s) - %" PRIu64 " votes\n",
                   candidate->candidate_id, candidate->name,
                   candidate->party, candidate->vote_count);
        }
    }
}

void election_print_results(const Election* election) {
    if (!election) return;

    ElectionResult results[100];
    int count = election_calculate_results(election, results, 100);

    printf("Election Results for: %s\n", election->name);
    printf("Total Votes: %" PRIu64 "\n\n", election->total_votes);

    for (int i = 0; i < count; i++) {
        printf("%d. %s (%s)\n", results[i].rank, results[i].candidate_name, results[i].party);
        printf("   Votes: %" PRIu64 " (%.2f%%)\n", results[i].vote_count, results[i].vote_percentage);
        printf("\n");
    }
}

char* election_status_to_string(ElectionStatus status) {
    switch (status) {
        case ELECTION_STATUS_DRAFT: return "Draft";
        case ELECTION_STATUS_REGISTERING: return "Registering";
        case ELECTION_STATUS_VOTING: return "Voting";
        case ELECTION_STATUS_COUNTING: return "Counting";
        case ELECTION_STATUS_COMPLETED: return "Completed";
        case ELECTION_STATUS_CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}

// Error handling
const char* election_error_message(ElectionError error) {
    switch (error) {
        case ELECTION_SUCCESS: return "Success";
        case ELECTION_ERROR_INVALID_DATES: return "Invalid election dates";
        case ELECTION_ERROR_TOO_MANY_CANDIDATES: return "Too many candidates";
        case ELECTION_ERROR_CANDIDATE_NOT_FOUND: return "Candidate not found";
        case ELECTION_ERROR_VOTING_CLOSED: return "Voting is closed";
        case ELECTION_ERROR_VOTING_NOT_OPEN: return "Voting is not open";
        case ELECTION_ERROR_ALREADY_EXISTS: return "Election already exists";
        case ELECTION_ERROR_NOT_FOUND: return "Election not found";
        default: return "Unknown error";
    }
}