//
// Created by Flasque
//

#include <stdint.h>

uint64_t gcd(uint64_t a, uint64_t b)
{
    // TODO : implement the Euclidean algorithm for GCD
}

uint64_t modinv(uint64_t a, uint64_t m)
{
    // TODO : find b, the modular inverse of a modulo m
    //        such that (a * b) % m == 1
}

uint64_t modexp(uint64_t m, uint64_t expo, uint64_t n)
{
    uint64_t result = 1;
    while (expo > 0)
    {
        if (expo % 2 == 1)
        {
            result = (result * m) % n;
        }
        expo = expo >> 1;
        m = (m * m) % n;
    }
    return result;
}

int isprime(uint64_t n)
{
    // TODO : implement a primality test (e.g., trial division)
}

uint64_t generate_large_prime(uint64_t lower, uint64_t upper)
{
    // TODO : generate numbers in the range [lower, upper] until a prime is found
    //       Use the isprime function to check for primality and rand() to generate random numbers
}