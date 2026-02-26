//
// Created by flasque on 20/02/2026.
//

#ifndef RSA_ENCODING_H
#define RSA_ENCODING_H

#include <stdint.h>

#define MESSAGE_END 0

/**
 * @brief Encode a plaintext message into an array of uint64_tegers using a custom encoding scheme.
 * @param message The plaintext message to encode (null-terminated string).
 * @param encoded_message An array to hold the encoded message ((null-terminated with MESSAGE_END).
 */
void encode_message(char *message, uint64_t* encoded_message);

/**
 * @brief Decode an array of uint64_tegers back into a plaintext message using the custom encoding scheme.
 * @param encoded_message The encoded message as an array of uint64_tegers (null-terminated with MESSAGE_END).
 * @param decoded_message An array to hold the decoded plaintext message (must be large enough to hold the result).
 */
void decode_message(uint64_t* encoded_message, char *decoded_message);

/**
 * @brief Display the encoded message as a sequence of uint64_tegers.
 * @param encoded_message The encoded message to display (null-terminated with MESSAGE_END).
 */
void display_encoded_message(uint64_t* encoded_message);

/**
 * @brief Input an encoded message from the user and store it in an array of uint64_tegers.
 *        The input should be a sequence of uint64_tegers separated by spaces, ending with MESSAGE_END (0).
 * @param encoded_message An array to hold the input encoded message (must be large enough to hold the result).
 */
void input_encoded_message(uint64_t* encoded_message);

#endif //RSA_ENCODING_H
