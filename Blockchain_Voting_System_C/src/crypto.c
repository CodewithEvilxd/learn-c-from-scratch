/*
 * Cryptography Implementation
 * SHA-256 hashing and basic cryptographic functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/crypto.h"

// SHA-256 constants
static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Initial hash values
static const uint32_t H0[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// Helper functions
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SHR(x, n) ((x) >> (n))

#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define BSIG0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define BSIG1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SSIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define SSIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

// SHA-256 implementation
void sha256_init(SHA256_CTX* ctx) {
    memcpy(ctx->state, H0, sizeof(H0));
    ctx->bit_count = 0;
    memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void sha256_update(SHA256_CTX* ctx, const uint8_t* data, size_t len) {
    size_t i = 0;

    while (i < len) {
        size_t buffer_space = 64 - (ctx->bit_count / 8 % 64);
        size_t chunk_size = (len - i < buffer_space) ? len - i : buffer_space;

        memcpy(ctx->buffer + (ctx->bit_count / 8 % 64), data + i, chunk_size);
        ctx->bit_count += chunk_size * 8;
        i += chunk_size;

        if (ctx->bit_count / 8 % 64 == 0) {
            sha256_transform(ctx->state, ctx->buffer);
        }
    }
}

void sha256_final(SHA256_CTX* ctx, uint8_t hash[SHA256_DIGEST_SIZE]) {
    // Pad the message
    uint64_t bit_length = ctx->bit_count;
    size_t buffer_pos = ctx->bit_count / 8 % 64;

    // Append '1' bit
    ctx->buffer[buffer_pos] = 0x80;
    buffer_pos++;

    // If not enough space for length, pad with zeros and transform
    if (buffer_pos > 56) {
        memset(ctx->buffer + buffer_pos, 0, 64 - buffer_pos);
        sha256_transform(ctx->state, ctx->buffer);
        memset(ctx->buffer, 0, 56);
    } else {
        memset(ctx->buffer + buffer_pos, 0, 56 - buffer_pos);
    }

    // Append length in big-endian
    for (int i = 0; i < 8; i++) {
        ctx->buffer[56 + i] = (bit_length >> (56 - i * 8)) & 0xFF;
    }

    sha256_transform(ctx->state, ctx->buffer);

    // Convert to big-endian and copy to hash
    for (int i = 0; i < 8; i++) {
        hash[i * 4] = (ctx->state[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (ctx->state[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (ctx->state[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = ctx->state[i] & 0xFF;
    }
}

void sha256_transform(uint32_t state[8], const uint8_t block[64]) {
    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, h;

    // Prepare message schedule
    for (int i = 0; i < 16; i++) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
               (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }

    for (int i = 16; i < 64; i++) {
        w[i] = SSIG1(w[i - 2]) + w[i - 7] + SSIG0(w[i - 15]) + w[i - 16];
    }

    // Initialize working variables
    a = state[0]; b = state[1]; c = state[2]; d = state[3];
    e = state[4]; f = state[5]; g = state[6]; h = state[7];

    // Main loop
    for (int i = 0; i < 64; i++) {
        uint32_t t1 = h + BSIG1(e) + CH(e, f, g) + K[i] + w[i];
        uint32_t t2 = BSIG0(a) + MAJ(a, b, c);

        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    // Add to state
    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}

void sha256_hash(const uint8_t* data, size_t len, uint8_t hash[SHA256_DIGEST_SIZE]) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, data, len);
    sha256_final(&ctx, hash);
}

void sha256_to_hex(const uint8_t hash[SHA256_DIGEST_SIZE], char hex[SHA256_HEX_SIZE]) {
    for (int i = 0; i < SHA256_DIGEST_SIZE; i++) {
        sprintf(hex + i * 2, "%02x", hash[i]);
    }
    hex[64] = '\0';
}

// Simplified ECDSA (for demonstration - not cryptographically secure)
int ecdsa_generate_keypair(uint8_t private_key[ECDSA_PRIVATE_KEY_SIZE],
                          uint8_t public_key[ECDSA_PUBLIC_KEY_SIZE]) {
    // Generate random private key
    crypto_random_bytes(private_key, ECDSA_PRIVATE_KEY_SIZE);

    // Simple public key derivation (not real ECDSA)
    memcpy(public_key, private_key, ECDSA_PRIVATE_KEY_SIZE);
    // Add some transformation to simulate public key
    for (int i = 0; i < ECDSA_PRIVATE_KEY_SIZE; i++) {
        public_key[i] = ~private_key[i]; // Simple transformation
    }

    return CRYPTO_SUCCESS;
}

int ecdsa_sign(const uint8_t* data, size_t data_len,
               const uint8_t private_key[ECDSA_PRIVATE_KEY_SIZE],
               uint8_t signature[ECDSA_SIGNATURE_SIZE]) {
    // Simplified signature (not real ECDSA)
    uint8_t hash[SHA256_DIGEST_SIZE];
    sha256_hash(data, data_len, hash);

    // Combine hash with private key for signature
    for (int i = 0; i < ECDSA_SIGNATURE_SIZE; i++) {
        signature[i] = hash[i % SHA256_DIGEST_SIZE] ^ private_key[i % ECDSA_PRIVATE_KEY_SIZE];
    }

    return CRYPTO_SUCCESS;
}

int ecdsa_verify(const uint8_t* data, size_t data_len,
                 const uint8_t public_key[ECDSA_PUBLIC_KEY_SIZE],
                 const uint8_t signature[ECDSA_SIGNATURE_SIZE]) {
    // Simplified verification (not real ECDSA)
    uint8_t expected_signature[ECDSA_SIGNATURE_SIZE];
    uint8_t hash[SHA256_DIGEST_SIZE];
    sha256_hash(data, data_len, hash);

    // Recreate expected signature
    for (int i = 0; i < ECDSA_SIGNATURE_SIZE; i++) {
        expected_signature[i] = hash[i % SHA256_DIGEST_SIZE] ^ (~public_key[i % ECDSA_PUBLIC_KEY_SIZE]);
    }

    // Compare signatures
    if (memcmp(signature, expected_signature, ECDSA_SIGNATURE_SIZE) == 0) {
        return CRYPTO_SUCCESS;
    }

    return CRYPTO_ERROR_SIGNATURE_INVALID;
}

// Utility functions
void crypto_random_bytes(uint8_t* buffer, size_t len) {
    for (size_t i = 0; i < len; i++) {
        buffer[i] = (uint8_t)(rand() % 256);
    }
}

bool crypto_verify_difficulty(const char* hash, int difficulty) {
    for (int i = 0; i < difficulty; i++) {
        if (hash[i] != '0') {
            return false;
        }
    }
    return true;
}

// Stub implementations for other functions
int crypto_base64_encode(const uint8_t* data, size_t len, char* output, size_t output_size) {
    // TODO: Implement base64 encoding
    return CRYPTO_SUCCESS;
}

int crypto_base64_decode(const char* input, uint8_t* output, size_t output_size) {
    // TODO: Implement base64 decoding
    return CRYPTO_SUCCESS;
}

KeyPair* crypto_generate_keypair(void) {
    KeyPair* keypair = (KeyPair*)malloc(sizeof(KeyPair));
    if (!keypair) return NULL;

    ecdsa_generate_keypair(keypair->private_key, keypair->public_key);
    sprintf(keypair->address, "ADDR_%02x%02x%02x...", keypair->public_key[0], keypair->public_key[1], keypair->public_key[2]);

    return keypair;
}

void crypto_destroy_keypair(KeyPair* keypair) {
    if (keypair) {
        free(keypair);
    }
}

const char* crypto_get_address(const KeyPair* keypair) {
    return keypair ? keypair->address : NULL;
}

int crypto_generate_address(const uint8_t public_key[ECDSA_PUBLIC_KEY_SIZE], char* address, size_t address_size) {
    uint8_t hash[SHA256_DIGEST_SIZE];
    sha256_hash(public_key, ECDSA_PUBLIC_KEY_SIZE, hash);

    // Create address from hash
    snprintf(address, address_size, "BCV_%02x%02x%02x%02x%02x%02x%02x%02x",
             hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7]);

    return CRYPTO_SUCCESS;
}

bool crypto_validate_address(const char* address) {
    return address && strlen(address) > 4 && strncmp(address, "BCV_", 4) == 0;
}

// Error handling
const char* crypto_error_message(CryptoError error) {
    switch (error) {
        case CRYPTO_SUCCESS: return "Success";
        case CRYPTO_ERROR_INVALID_KEY: return "Invalid key";
        case CRYPTO_ERROR_INVALID_SIGNATURE: return "Invalid signature";
        case CRYPTO_ERROR_INVALID_HASH: return "Invalid hash";
        case CRYPTO_ERROR_MEMORY: return "Memory allocation failed";
        default: return "Unknown error";
    }
}