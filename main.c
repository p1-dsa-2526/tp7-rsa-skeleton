#include <stdio.h>
#include <stdint.h>
#include "string.h"
#include "encoding.h"
#include "rsa.h"
#include "arithmetic.h"

int main()
{
    char message[] = "Hello, RSA! This is a test message to encode and decode using our custom encoding scheme$";
    uint64_t encoded_message[100]; // large enough to hold the encoded message
    char decoded_message[100]; // large enough to hold the decoded message

    printf("Plain message: %s\n", message);
    encode_message(message, encoded_message);
    printf("Encoded message:\n");
    display_encoded_message(encoded_message);
    printf("\n");




    return 0;
}
