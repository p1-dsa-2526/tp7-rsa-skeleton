//
// Created by flasque on 24/02/2026.
//

#include "utest.h"
#include "../rsa.h"
#include "../arithmetic.h"

UTEST(generate_rsa_keys, key_generation)
{
    t_RSA_keys keys = generate_rsa_keys(300, 700);
    char msg_p[150], msg_q[150], msg_n[150], msg_e[150], msg_d[150];
    sprintf(msg_p, "`generate_rsa_keys` gives p=%lu - %lu is not considered prime by `isprime`", keys.p, keys.p);
    sprintf(msg_q, "`generate_rsa_keys` gives q=%lu - %lu is not considered prime by `isprime`", keys.q, keys.q);
    sprintf(msg_n, "`generate_rsa_keys` gives n=%lu - expected n=%lu = p=%lu . q=%lu", keys.n, keys.p*keys.q, keys.p, keys.q);
    sprintf(msg_e, "`generate_rsa_keys` gives e=%lu - %lu is not coprime to phi(n)=(p-1).(q-1)=%lu", keys.e, keys.e, (keys.p-1)*(keys.q-1));
    sprintf(msg_d, "`generate_rsa_keys` gives d=%lu - d does not satisfy (e*d)[phi(n)] = 1", keys.d);
    UTEST_TRUE(isprime(keys.p), msg_p, 1);
    UTEST_TRUE(isprime(keys.q), msg_q, 1);
    UTEST_TRUE(keys.n == keys.p * keys.q, msg_n, 1);
    uint64_t phi = (keys.p - 1) * (keys.q - 1);
    UTEST_TRUE(gcd(keys.e, phi) == 1, msg_e, 1);
    UTEST_TRUE((keys.e*keys.d)%phi==1, msg_d, 1);

    // TODO : add assertions to check if the generated keys are valid (e.g., n is product of two primes, e and d are correct)
}

UTEST(rsa_encrypt, encryption)
{
    uint64_t n1,e1,m1;
    n1 = 188113;
    e1 = 37;
    m1 = 12345;
    uint64_t expected = 42517;
    unsigned long result = rsa_encrypt(m1, (t_RSA_keys){.n=n1, .e=e1});
    char msg_encrypt[150];
    sprintf(msg_encrypt, "test for encryption for %lu with (n=%lu, e=%lu). expected %lu _ got %lu", m1, n1, e1, expected,result);
    UTEST_TRUE(result == expected, msg_encrypt, 1);
}

UTEST_MAIN();