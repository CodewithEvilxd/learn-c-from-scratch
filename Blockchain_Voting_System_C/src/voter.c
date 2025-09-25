/*
 * Voter Management Implementation
 * Voter registration and authentication
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/voter.h"
#include "../headers/utils.h"

// Voter lifecycle
Voter* voter_create(const char* name, const char* email, const char* address, const char* phone, time_t dob) {
    Voter* voter = (Voter*)safe_malloc(sizeof(Voter));
    if (!voter) return NULL;

    memset(voter, 0, sizeof(Voter));

    // Generate voter ID
    sprintf(voter->voter_id, "VOTER_%06d", random_int(100000, 999999));

    // Copy data
    str_copy(name, voter->name, sizeof(voter->name));
    str_copy(email, voter->email, sizeof(voter->email));
    str_copy(address, voter->address, sizeof(voter->address));
    if (phone) {
        str_copy(phone, voter->phone, sizeof(voter->phone));
    }

    voter->date_of_birth = dob;
    voter->registration_date = time(NULL);
    voter->status = VOTER_STATUS_REGISTERED;
    voter->has_voted = false;
    voter->vote_count = 0;

    return voter;
}

void voter_destroy(Voter* voter) {
    if (voter) {
        safe_free(voter);
    }
}

// Voter operations
int voter_generate_id(Voter* voter) {
    if (!voter) return VOTER_ERROR_INVALID_DATA;
    sprintf(voter->voter_id, "VOTER_%06d", random_int(100000, 999999));
    return VOTER_SUCCESS;
}

int voter_verify_identity(const Voter* voter) {
    if (!voter) return VOTER_ERROR_INVALID_DATA;

    // Basic verification
    if (strlen(voter->name) == 0 || strlen(voter->email) == 0) {
        return VOTER_ERROR_INVALID_DATA;
    }

    // Check age (must be 18+)
    time_t now = time(NULL);
    double age_seconds = difftime(now, voter->date_of_birth);
    double age_years = age_seconds / (365.25 * 24 * 3600);

    if (age_years < 18.0) {
        return VOTER_ERROR_NOT_ELIGIBLE;
    }

    return VOTER_SUCCESS;
}

int voter_update_status(Voter* voter, VoterStatus status) {
    if (!voter) return VOTER_ERROR_INVALID_DATA;
    voter->status = status;
    return VOTER_SUCCESS;
}

bool voter_is_eligible(const Voter* voter, const char* election_id) {
    if (!voter) return false;

    // Check basic eligibility
    if (voter->status != VOTER_STATUS_VERIFIED) return false;

    // Check if already voted in this election
    if (voter->has_voted && strcmp(voter->last_vote_election, election_id) == 0) {
        return false;
    }

    return true;
}

// Voter database operations
VoterDatabase* voter_database_create(int max_voters) {
    VoterDatabase* db = (VoterDatabase*)safe_malloc(sizeof(VoterDatabase));
    if (!db) return NULL;

    memset(db, 0, sizeof(VoterDatabase));
    db->max_voters = max_voters;
    strcpy(db->filename, "voters.db");

    return db;
}

void voter_database_destroy(VoterDatabase* db) {
    if (!db) return;

    for (int i = 0; i < db->count; i++) {
        if (db->voters[i]) {
            voter_destroy(db->voters[i]);
        }
    }

    safe_free(db);
}

int voter_database_add(VoterDatabase* db, Voter* voter) {
    if (!db || !voter) return VOTER_ERROR_INVALID_DATA;
    if (db->count >= db->max_voters) return VOTER_ERROR_DATABASE_FULL;

    // Check for duplicate email
    for (int i = 0; i < db->count; i++) {
        if (db->voters[i] && strcmp(db->voters[i]->email, voter->email) == 0) {
            return VOTER_ERROR_DUPLICATE_ID;
        }
    }

    db->voters[db->count] = voter;
    db->count++;

    return VOTER_SUCCESS;
}

Voter* voter_database_find_by_id(const VoterDatabase* db, const char* voter_id) {
    if (!db || !voter_id) return NULL;

    for (int i = 0; i < db->count; i++) {
        if (db->voters[i] && strcmp(db->voters[i]->voter_id, voter_id) == 0) {
            return db->voters[i];
        }
    }

    return NULL;
}

Voter* voter_database_find_by_email(const VoterDatabase* db, const char* email) {
    if (!db || !email) return NULL;

    for (int i = 0; i < db->count; i++) {
        if (db->voters[i] && strcmp(db->voters[i]->email, email) == 0) {
            return db->voters[i];
        }
    }

    return NULL;
}

int voter_database_remove(VoterDatabase* db, const char* voter_id) {
    if (!db || !voter_id) return VOTER_ERROR_INVALID_DATA;

    for (int i = 0; i < db->count; i++) {
        if (db->voters[i] && strcmp(db->voters[i]->voter_id, voter_id) == 0) {
            voter_destroy(db->voters[i]);

            // Shift remaining voters
            for (int j = i; j < db->count - 1; j++) {
                db->voters[j] = db->voters[j + 1];
            }

            db->voters[db->count - 1] = NULL;
            db->count--;

            return VOTER_SUCCESS;
        }
    }

    return VOTER_ERROR_NOT_FOUND;
}

// Stub implementations for other functions
int voter_database_save(const VoterDatabase* db, const char* filename) {
    return VOTER_SUCCESS;
}

int voter_database_load(VoterDatabase* db, const char* filename) {
    return VOTER_SUCCESS;
}

int voter_database_import_csv(VoterDatabase* db, const char* filename) {
    return VOTER_SUCCESS;
}

bool voter_validate_email(const char* email) {
    return email && strlen(email) > 5 && strstr(email, "@") != NULL;
}

bool voter_validate_phone(const char* phone) {
    return phone && strlen(phone) >= 10;
}

bool voter_validate_age(const Voter* voter, int minimum_age) {
    if (!voter) return false;

    time_t now = time(NULL);
    double age_seconds = difftime(now, voter->date_of_birth);
    double age_years = age_seconds / (365.25 * 24 * 3600);

    return age_years >= minimum_age;
}

bool voter_validate_address(const char* address) {
    return address && strlen(address) > 10;
}

// Statistics
void voter_database_get_stats(const VoterDatabase* db, VoterStats* stats) {
    if (!stats) return;

    memset(stats, 0, sizeof(VoterStats));
    stats->total_voters = db ? db->count : 0;

    time_t earliest_registration = time(NULL);
    int verified_count = 0;

    for (int i = 0; i < stats->total_voters; i++) {
        Voter* voter = db->voters[i];
        if (voter) {
            if (voter->status == VOTER_STATUS_VERIFIED) {
                verified_count++;
            }

            if (voter->registration_date < earliest_registration) {
                earliest_registration = voter->registration_date;
            }
        }
    }

    stats->verified_voters = verified_count;
    stats->average_registration_age = difftime(time(NULL), earliest_registration) / (365.25 * 24 * 3600);
}

// Error handling
const char* voter_error_message(VoterError error) {
    switch (error) {
        case VOTER_SUCCESS: return "Success";
        case VOTER_ERROR_INVALID_DATA: return "Invalid voter data";
        case VOTER_ERROR_DUPLICATE_ID: return "Duplicate voter ID";
        case VOTER_ERROR_NOT_FOUND: return "Voter not found";
        case VOTER_ERROR_ALREADY_VOTED: return "Voter already voted";
        case VOTER_ERROR_NOT_ELIGIBLE: return "Voter not eligible";
        case VOTER_ERROR_DATABASE_FULL: return "Voter database full";
        default: return "Unknown error";
    }
}