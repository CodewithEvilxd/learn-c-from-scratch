/*
 * Cryptography Header - SHA-256 and Digital Signatures
 * Cryptographic functions for blockchain security
 */

#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>
#include <stdbool.h>

// Hash sizes
#define SHA256_DIGEST_SIZE 32
#define SHA256_BLOCK_SIZE 64
#define SHA256_HEX_SIZE 65  // 64 hex chars + null terminator

// Key sizes for ECDSA (simplified)
#define ECDSA_PRIVATE_KEY_SIZE 32
#define ECDSA_PUBLIC_KEY_SIZE 64
#define ECDSA_SIGNATURE_SIZE 64

// SHA-256 context structure
typedef struct {
    uint32_t state[8];
    uint64_t bit_count;
    uint8_t buffer[SHA256_BLOCK_SIZE];
} SHA256_CTX;

// Function declarations

// SHA-256 hash functions
void sha256_init(SHA256_CTX* ctx);
void sha256_update(SHA256_CTX* ctx, const uint8_t* data, size_t len);
void sha256_final(SHA256_CTX* ctx, uint8_t hash[SHA256_DIGEST_SIZE]);
void sha256_hash(const uint8_t* data, size_t len, uint8_t hash[SHA256_DIGEST_SIZE]);
void sha256_to_hex(const uint8_t hash[SHA256_DIGEST_SIZE], char hex[SHA256_HEX_SIZE]);

// Simplified ECDSA functions (for demonstration)
int ecdsa_generate_keypair(uint8_t private_key[ECDSA_PRIVATE_KEY_SIZE],
                          uint8_t public_key[ECDSA_PUBLIC_KEY_SIZE]);
int ecdsa_sign(const uint8_t* data, size_t data_len,
               const uint8_t private_key[ECDSA_PRIVATE_KEY_SIZE],
               uint8_t signature[ECDSA_SIGNATURE_SIZE]);
int ecdsa_verify(const uint8_t* data, size_t data_len,
                 const uint8_t public_key[ECDSA_PUBLIC_KEY_SIZE],
                 const uint8_t signature[ECDSA_SIGNATURE_SIZE]);

// Utility functions
void crypto_random_bytes(uint8_t* buffer, size_t len);
bool crypto_verify_difficulty(const char* hash, int difficulty);
int crypto_base64_encode(const uint8_t* data, size_t len, char* output, size_t output_size);
int crypto_base64_decode(const char* input, uint8_t* output, size_t output_size);

// Key management
typedef struct {
    uint8_t private_key[ECDSA_PRIVATE_KEY_SIZE];
    uint8_t public_key[ECDSA_PUBLIC_KEY_SIZE];
    char address[50];  // Derived address
} KeyPair;

KeyPair* crypto_generate_keypair(void);
void crypto_destroy_keypair(KeyPair* keypair);
const char* crypto_get_address(const KeyPair* keypair);

// Address generation
int crypto_generate_address(const uint8_t public_key[ECDSA_PUBLIC_KEY_SIZE], char* address, size_t address_size);
bool crypto_validate_address(const char* address);

// Password-based key derivation (PBKDF2 simplified)
int crypto_pbkdf2(const char* password, const uint8_t* salt, size_t salt_len,
                  uint8_t* key, size_t key_len, int iterations);

// Error handling
typedef enum {
    CRYPTO_SUCCESS = 0,
    CRYPTO_ERROR_INVALID_KEY = -1,
    CRYPTO_ERROR_INVALID_SIGNATURE = -2,
    CRYPTO_ERROR_SIGNATURE_INVALID = -3,
    CRYPTO_ERROR_INVALID_HASH = -4,
    CRYPTO_ERROR_MEMORY = -5,
    CRYPTO_ERROR_UNKNOWN = -99
} CryptoError;

const char* crypto_error_message(CryptoError error);

#endif // CRYPTO_H