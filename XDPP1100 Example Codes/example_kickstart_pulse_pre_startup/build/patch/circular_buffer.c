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
 * @file    circular_buffer.h
 * @brief   Implementation of a circular buffer.
 */

/* Always compare to the associated interface */
#include "circular_buffer.h"

/* Standard library */
#include <stdint.h>     // uint*_t
#include <string.h>     // memset
#include <stddef.h>     // NULL pointer
#include "fw_bool.h"    // boolean type

/*lint -esym(714, circ_buffer_*) -esym(759, circ_buffer_*) -esym(765, circ_buffer_*)
 * These library functions should not be local/static and we ignore that it is currently not called.
 * The linker will remove it. */

/* ============================================================================
 * Functions
 * ========================================================================= */

void circ_buffer_init(Circ_Buffer_t* circ_buffer, uint32_t size, Circ_Buffer_Element_t memory[])
{
    /* Set all data to zero */
    memset(circ_buffer, 0, sizeof(Circ_Buffer_t));

    circ_buffer->size = size;

    /* Memory is allocated from the outside */
    circ_buffer->elements = memory;
}

void circ_buffer_push(Circ_Buffer_t* circ_buffer, Circ_Buffer_Element_t element)
{
    circ_buffer->elements[circ_buffer->i_write] = element;

    /* Overwrite if the buffer is full. In this case also push the read
     * index forward. */
    if (circ_buffer->count == circ_buffer->size)
    {
        circ_buffer->i_read++;
        if (circ_buffer->i_read == circ_buffer->size) circ_buffer->i_read = 0;
    }

    circ_buffer->i_write++;
    if (circ_buffer->i_write == circ_buffer->size) circ_buffer->i_write = 0;
    circ_buffer->count++;
}

Circ_Buffer_Element_t circ_buffer_pop(Circ_Buffer_t* circ_buffer)
{
    Circ_Buffer_Element_t element = NULL;
    if (circ_buffer->count > 0)
    {
        element = circ_buffer->elements[circ_buffer->i_read];
        circ_buffer->i_read++;
        if (circ_buffer->i_read == circ_buffer->size) circ_buffer->i_read = 0;
        circ_buffer->count--;
    }
    return element;
}

boolean circ_buffer_is_full(const Circ_Buffer_t* circ_buffer)
{
    return (circ_buffer->count == circ_buffer->size);
}

boolean circ_buffer_is_empty(const Circ_Buffer_t* circ_buffer)
{
    return (circ_buffer->count == 0);
}

void circ_buffer_elements_remove(Circ_Buffer_t* circ_buffer, uint32_t num_elements)
{
    if (num_elements >= circ_buffer->count)
    {
        /* Empty the buffer. */
        circ_buffer->i_read = circ_buffer->i_write;
        circ_buffer->count = 0;
    }
    else
    {
        /* Advance the read index which is still behind the write index. */
        circ_buffer->i_read += num_elements;
        circ_buffer->count -= num_elements;
        if (circ_buffer->i_read >= circ_buffer->size)
            circ_buffer->i_read %= circ_buffer->size; // usual modulo
    }
}
