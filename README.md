## skeleton - sandbox version for tests

### uses UTEST.H from mikael

### added `testing` directory to separate students code from testing code

### added xml_to_md.c in `testing` to produce .md outputs from .xml (utest --output)

### modified CMakeLists.txt file :

>build xml_to_md.exe executable on Cmake configuration
>
>added custom_command for test target to produce .md feedback on test target running
>
>added run_tests.cmake for 'All C tests' to produce .md feedback file on all tests running

### in test_xxx.c : use sprintf to produce meaningful message, use UTEST_TRUE

```C
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
```

