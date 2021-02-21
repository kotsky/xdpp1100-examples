/* ============================================================================
** Original author
** Stephan Brumme
** Rudolf-Breitscheid-Str. 226
** 14482 Potsdam
** Germany
** create@stephan-brumme.com
** ============================================================================
**
** ============================================================================
** License
** All source code published on http://create.stephan-brumme.com and its
** sub-pages is licensed similar to the zlib license:
**
** This software is provided 'as-is', without any express or implied warranty.
** In no event will the author be held liable for any damages arising from the
** use of this software.
** Permission is granted to anyone to use this software for any purpose,
** including commercial applications, and to alter it and redistribute it
** freely, subject to the following restrictions:
**
** 1. The origin of this software must not be misrepresented; you must not
**    claim that you wrote the original software.
** 2. If you use this software in a product, an acknowledgment in the product
**    documentation would be appreciated but is not required.
** 3. Altered source versions must be plainly marked as such, and must not be
**    misrepresented as being the original software.
** ============================================================================
*/
/**
 * @file    crc32.c
 * @brief   Implementation of the CRC32 algorithm.
 */

/* Always compare to the associated interface */
#include "crc32.h"
#include "shasta_hal_crc32.h" // HW CRC module
#include "shasta_hal_rgu.h"   // Reset for HW CRC module
#include "shasta_hal_cgu.h"   // Clock enable for HW CRC module

/* Standard library */
#include <stdint.h>     // uint*_t


/** Precomputed table made of the 16th entry of the standard 256x32bit
 * look-up table if the default polynomial 0xEDB88320 was used. */
static const uint32_t lut[16] =
{
        0x00000000,0x1DB71064,0x3B6E20C8,0x26D930AC,
        0x76DC4190,0x6B6B51F4,0x4DB26158,0x5005713C,
        0xEDB88320,0xF00F9344,0xD6D6A3E8,0xCB61B38C,
        0x9B64C2B0,0x86D3D2D4,0xA00AE278,0xBDBDF21C
};

uint32_t crc32_halfbyte(const void* data, uint16_t length, uint32_t previous_crc32)
{
    uint32_t crc = ~previous_crc32;

    /* Update the checksum for every byte of data */
    uint8_t* current = (uint8_t*) data;
    while (length--)
    {
        crc = lut[(crc ^  *current      ) & 0x0Fu] ^ (crc >> 4);
        crc = lut[(crc ^ (*current >> 4)) & 0x0Fu] ^ (crc >> 4);
        current++; // next byte
    }

    return ~crc;
}

uint32_t hw_crc32(const void* data, uint16_t length, uint32_t previous_crc32)
{
    // Check if the module is disabled if yes enabled it forever
    if ((CGU_CLK_EN_CTRL__BIF_PER_SVID_CLK_G__GET() == 0UL) ||
            (RGU_RSTMODS__BIFPERSVIDRST__GET() == 1UL))
    {
        // Enable the CRC32 HW via SVID clock because it is used for the crc32 module.
        CGU_CLK_EN_CTRL_SET__BIF_PER_SVID_CLK_G__SET(1UL);

        // Release SVID RESET
        RGU_RSTMODS_CLR__SET(RGU_RSTMODS_CLR__BIFPERSVIDRST__Shift(1UL));
        CRC32_POLY__SET(HWCRC32_POLYNOMIAL);
        CRC32_XORE__SET(0xFFFFFFFFUL);
        CRC32_CNFG__SET(0x3UL);
    }

    // Only set the crc32 configuration if pervious_crc is zero because
    // the module stores the state from the previous calculation inside.
    // There is currently no other way to chain the calculation then using the
    // internally stored values.
    CRC32_INIT__SET(previous_crc32);

    uint32_t crc = 0;

    // the hw is set to 32 bit crc there we need to reduce the length by 4
    length >>= 2;
    /* Update the checksum for every byte of data */
    uint32_t* current = (uint32_t*) data;
    while (length--)
    {
        // Calculate the hw crc
        CRC32_DATA__SET(*current);
        // Retrieve the hw crc value
        crc = CRC32_DATA__GET();
        current++; // next byte
    }

    /* For now we leave the module activated all the time otherwise we would
     * loose the internal state for chaining calculations
     *
    // Disable SVID clock because it is not used anymore for crc calculation.
    CGU_CLK_EN_CTRL_CLR__BIF_PER_SVID_CLK_G__SET(1UL);

    // Activate SVID RESET
    RGU_RSTMODS_SET__SET(RGU_RSTMODS_SET__BIFPERSVIDRST__Shift(1UL));
     */
    return crc;
}
