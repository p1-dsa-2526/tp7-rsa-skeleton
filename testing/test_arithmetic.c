//
// Created by flasque on 24/02/2026.
//

#include "utest.h"
#include "../arithmetic.h"

UTEST(isprime, test_on_primes)
{
   int test_values[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < sizeof(test_values)/sizeof(test_values[0]); i++)
    {
         ASSERT_TRUE(isprime(test_values[i]));
    }
}

UTEST(isprime, test_on_non_primes)
{
    int test_values[] = {1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26, 27, 28, 30};
    for (int i = 0; i < sizeof(test_values)/sizeof(test_values[0]); i++)
    {
         ASSERT_FALSE(isprime(test_values[i]));
    }

}

UTEST(gcd, standard_cases)
{
    ASSERT_EQ(gcd(48, 18), 6);
    ASSERT_EQ(gcd(56, 98), 14);
    ASSERT_EQ(gcd(101, 10), 1);
    ASSERT_EQ(gcd(54, 24), 6);
    ASSERT_EQ(gcd(17, 13), 1);
    // 4 more tests to cover edge cases
    ASSERT_EQ(gcd(0, 5), 5); // gcd with zero
    ASSERT_EQ(gcd(5, 0), 5); // gcd with zero
    ASSERT_EQ(gcd(0, 0), 0); // gcd of zero and zero
    ASSERT_EQ(gcd(1, 1), 1); // gcd of one and one

}

UTEST(modinv, standard_cases)
{
    ASSERT_EQ(modinv(3, 11), 4); // 3 * 4 % 11 == 1
    ASSERT_EQ(modinv(10, 17), 12); // 10 * 12 % 17 == 1
    ASSERT_EQ(modinv(7, 26), 15); // 7 * 15 % 26 == 1
    ASSERT_EQ(modinv(5, 9), 2); // 5 * 2 % 9 == 1
    ASSERT_EQ(modinv(37, 187200), 65773); // from RSA example
}

UTEST(generate_large_prime, in_range_300_700_and_is_prime)
{
    uint64_t prime = generate_large_prime(300, 700);
    char msg_lower[50];
    char msg_upper[50];
    char msg_prime[50];
    sprintf(msg_lower, "generated %lu is not >=300 ", prime);
    sprintf(msg_upper, "generated %lu is not <= 700", prime);
    sprintf(msg_prime, "test if %lu is prime", prime);
    UTEST_TRUE(prime <= 700, msg_upper, 1);
    UTEST_TRUE(prime >= 300,msg_lower,1);
    UTEST_TRUE(isprime(prime),msg_prime,1);
}

UTEST_MAIN();