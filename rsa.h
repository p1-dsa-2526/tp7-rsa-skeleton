//
// Created by flasque on 02/02/2026.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H


#include <stdint.h>

/**
 * @struct keysRsa
 * @brief Structure to hold RSA public and private keys.
 */
typedef struct s_RSA_keys
{
    uint64_t p; // prime 1
    uint64_t q; // prime 2
    uint64_t n; // modulus n = p * q
    uint64_t e; // public exponent
    uint64_t d; // private exponent
} t_RSA_keys;

/**
 * @brief Generate RSA keys (public and private) within a specified range.
 * @param lower The lower bound for prime number generation.
 * @param upper The upper bound for prime number generation.
 * @return A structure containing the generated RSA keys.
 */
t_RSA_keys generate_rsa_keys(uint64_t lower, uint64_t upper);

/**
 * @brief Encrypt a message using the RSA public key.
 * @param message The plaintext message to encrypt.
 * @param expo The public exponent (e) from the RSA keys.
 * @param n The modulus (n) from the RSA keys.
 * @return The encrypted ciphertext.
 */
uint64_t rsa_encrypt(uint64_t message, uint64_t expo, uint64_t n);

/**
 * @brief Decrypt a ciphertext using the RSA private key.
 * @param ciphertext The encrypted message to decrypt.
 * @param keys The RSA keys containing the private key (n, d).
 * @return The decrypted plaintext message.
 */
uint64_t rsa_decrypt(uint64_t ciphertext, t_RSA_keys keys);

/**
 * @brief Publish the RSA public key (n, e) for others to use.
 * @param keys The RSA keys containing the public key (n, e).
 */
void publish_keys(t_RSA_keys keys);
#endif //RSA_RSA_H