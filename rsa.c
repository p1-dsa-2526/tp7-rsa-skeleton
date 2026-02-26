//
// Created by flasque on 02/02/2026.
//

#include <stdio.h>
#include "rsa.h"
#include "arithmetic.h"



t_RSA_keys generate_rsa_keys(uint64_t lower, uint64_t upper)
{
    // TODO : generate all values for the RSA keys (p, q, n, phi_n, e, d) and return them in a structure
}

uint64_t rsa_encrypt(uint64_t message, t_RSA_keys keys)
{
    return modexp(message, keys.e, keys.n); // TODO : encrypt the message using the RSA public key (n, e) and return the ciphertext
}

uint64_t rsa_decrypt(uint64_t ciphertext, t_RSA_keys keys)
{
    // TODO : decrypt the message using the RSA private key (n, d) and return the deciphered value
}

void publish_keys(t_RSA_keys keys)
{
    // TODO : print the public key (n, e) to the console in a readable format
}

