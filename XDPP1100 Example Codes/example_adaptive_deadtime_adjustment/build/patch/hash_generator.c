/* ============================================================================
 ** Copyright (C) 2014 Infineon Technologies AG
 ** All rights reserved.
 ** ============================================================================
 **
 ** ============================================================================
 ** This document contains proprietary information of Infineon Technologies AG.
 ** Passing on and copying of this document, and communication of its contents
 ** is not permitted without Infineon's prior written authorisation.
 ** ============================================================================
 */
/**
 * @file    hash_generator.c
 * @brief   32 bit hash value generator for passwords
 */
#include "fw_config.h"          /* Essential fw-wide configuration for e.g. buffer size #defines */
#include "environment.h"        /* STATIC, INLINE */
#include <string.h>             /*  memcpy */
#include "crc32.h"              /* hw_crc32 */
#include "log_app.h"            /* Error Handling */
#include "hash_generator.h"

STATIC uint32_t hash_bit_permute_step(uint32_t value, uint32_t mask, uint8_t shift)
{
    uint32_t t = ((value >> shift) ^ value) & mask;
    value = (value ^ t) ^ (t << shift);
    return value;
}

/**
 * This function calculates a 4 byte hash value for the input value
 * @param ptr   Pointer to the input value
 * @param size  Size of the input value in byte
 * @return 32 bit hash value or 0xFFFFFFFF if the input exceeded the maximum size of 8 byte.
 *
 */
uint32_t hash_code_create(const uint8_t* ptr, uint8_t size)
{

    if (size > 8)
    {
        LOG_ERROR_TYPE(UNKNOWN_SOURCE, WARNING, ILLEGAL_PARAMETER);
        return 0xFFFFFFFFUL;
    }
    /* At first an 8-bit constant is appended to the incoming password at the MSB side to prevent
     * rotational repetition of the same CRC value in the following step.
     */

    uint8_t extended_value[9u];
    memcpy(&extended_value[0], ptr, size);
    extended_value[size] = 0x6E;

    /* The resulting value is scrambled on a byte by byte basis with the CRC32 algorithm. */
    uint32_t hash = hw_crc32(&extended_value[0], size, 0);

    /* Afterwards the result of the scrambling will be mysteriously shuffled with a delta swap
     * algorithm. */
    hash = hash_bit_permute_step(hash, 0x14054510, 1);
    hash = hash_bit_permute_step(hash, 0x00D00074, 8);
    hash = hash_bit_permute_step(hash, 0x20133010, 2);
    hash = hash_bit_permute_step(hash, 0x0309030C, 4);
    hash = hash_bit_permute_step(hash, 0x0000A153, 16);
    hash = hash_bit_permute_step(hash, 0x32020011, 2);
    hash = hash_bit_permute_step(hash, 0x006E00EC, 8);
    hash = hash_bit_permute_step(hash, 0x01041504, 1);

    /* At last the result of the shuffling is xor-ed with a constant. */
    return (hash ^ 0x9162ED8B);
}



