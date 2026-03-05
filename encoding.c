//
// Created by flasque on 20/02/2026.
//

#include <string.h>
#include <stdio.h>
#include "encoding.h"

// provided as is - DO NOT MODIFY

void encode_message(char *message, uint64_t* encoded_message)
{
    int i = 0;
    int j = 0;
    // add a padding space character at the end of the message if its length is odd, to ensure we always have pairs of characters

    int len = strlen(message);
    if (len % 2 != 0) {
        message[len] = ' ';
        message[len+1] = '\0';
        len++;
    }
    int blocks = (len+1)/2; // blocks of two characters, if odd, last block will be one character
    while (j<blocks)
    {
        char c1 = message[i++];
        char c2 = (i<len) ? message[i++] : 0; // if odd, second character is 0
        int result = (c1-' '+1) * 256 + (c2-' '+1); // map ' ' to 0, '~' to 94
        encoded_message[j++] = result;
    }
    encoded_message[j] = MESSAGE_END; // O terminate the encoded message (cannot be obtained from encoding)
}

void decode_message(uint64_t* encoded_message, char *decoded_message)
{
    int i = 0;
    int j = 0;
    while (encoded_message[i] != MESSAGE_END) // until null terminator
    {
        unsigned int chunk = encoded_message[i++];
        char c1 = (chunk / 256) + ' ' - 1; // reverse mapping
        char c2 = (chunk % 256) + ' ' - 1; // reverse mapping
        decoded_message[j++] = c1;

            decoded_message[j++] = c2;

    }
    decoded_message[j] = '\0'; // null terminate the decoded message
}

void display_encoded_message(uint64_t* encoded_message) {
    int i = 0;
    while (encoded_message[i] != MESSAGE_END) {
        printf("%u ", encoded_message[i]);
        i++;
    }
    printf("\n");
}

void input_encoded_message(uint64_t* encoded_message) {
    int i = 0;
    uint64_t value;
    printf("Enter the encoded message as a sequence of unsigned integers, ending with 0:\n");
    while ((scanf("%llu", &value) == 1) && (value != MESSAGE_END)) {
        encoded_message[i++] = value;
    }
    encoded_message[i] = MESSAGE_END; // null terminate the encoded message
    printf("Encoded message input complete : the message is :");
    display_encoded_message(encoded_message);
}