//
// Created by Flasque
//

#ifndef RSA_ARITHMETIC_H
#define RSA_ARITHMETIC_H

#include <stdint.h>
/**
 * @brief Compute the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
 * @param a First integer.
 * @param b Second integer.
 * @return The GCD of a and b.
 */

uint64_t gcd(uint64_t a, uint64_t b);

/**
 * @brief Compute the modular inverse of a modulo m
 * @param a The integer to find the inverse of.
 * @param m The modulus.
 * @return The modular inverse of a modulo m, or -1 if it does not exist.
 */

uint64_t modinv(uint64_t a, uint64_t m);

/**
 * @brief Compute (base^exponent) mod modulus using modular exponentiation.
 * @param base The base integer.
 * @param exponent The exponent integer.
 * @param modulus The modulus integer.
 * @return The result of (base^exponent) mod modulus.
 */
uint64_t modexp(uint64_t base, uint64_t exponent, uint64_t modulus);

/**
 * @brief Check if a number is prime using trial division.
 * @param n The integer to check for primality.
 * @return 1 if n is prime, 0 otherwise.
 */

int isprime(uint64_t n);

/**
 * @brief Generate a large prime number within a specified range.
 * @param lower The lower bound of the range.
 * @param upper The upper bound of the range.
 * @return A large prime number within the specified range.
 */

uint64_t generate_large_prime(uint64_t lower, uint64_t upper);


#endif //RSA_ARITHMETIC_H