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
 * @file    linked_list.c
 * @brief   Implementation of a double linked list.
 */

/* Always compare to the associated interface */
#include "linked_list.h"

/* Standard library */
#include <stddef.h>     // NULL pointer


/* ============================================================================
 * Private data
 * ========================================================================= */


/* ============================================================================
 * Functions
 * ========================================================================= */

/* ----------------------------------------------------------------------------
 * Forward declaration and documentation of private functions
 * ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */

/*lint -esym(714, linked_list_*) -esym(759, linked_list_*) -esym(765, linked_list_*)
* Info: Symbol not called, or could be moved from header to module file.
 * Library function! */

void linked_list_init(Linked_List_t* list)
{
    list->root = NULL;
    list->last = NULL;
    list->iterator = NULL;
}

void linked_list_back_push(Linked_List_t* list, Linked_Node_t* node)
{
    if (list->last == NULL)
    {
        /* Add first node */
        node->next = NULL;
        node->previous = NULL;
        list->root = node;
    }
    else
    {
        /* Double linking */
        list->last->next = node;
        node->next = NULL;
        node->previous = list->last;
    }

    /* Update the last node and size */
    list->last = node;
}

void* linked_list_back_pop(Linked_List_t* list)
{
    void* element = NULL;
    if (list->last != NULL)
    {
        /* Save the element to return */
        element = list->last->element;

        /* Update the last node. The old one is simply forgotten within this list */
        if (list->last->previous == list->root->next) list->root->next = NULL;
        list->last = list->last->previous;

        /* In case the last node was removed, the root must be reset for linked_list_front_get.  */
        if (list->last == NULL) list->root = NULL;
    }
    return element;
}

Linked_Node_t* linked_list_remove(Linked_List_t* list, const void* element)
{
    /* Traverse the list from the root until the element is found. */
    Linked_Node_t* removed_node = list->root;
    while( (removed_node != NULL) && (removed_node->element != element) )
    {
        removed_node = removed_node->next;
    }

    if (removed_node != NULL)
    {
        /* Re-link the previous and next node (also needed the list's root and end). */
        if (removed_node->previous != NULL) removed_node->previous->next = removed_node->next;
        if (removed_node->next != NULL) removed_node->next->previous = removed_node->previous;

        /* Adjust the list's root and end if necessary */
        if (removed_node == list->root) list->root = removed_node->next;
        if (removed_node == list->last) list->last = removed_node->previous;
    }

    return removed_node;
}

void* linked_list_front_get(Linked_List_t* list)
{
    list->iterator = list->root;
    if (list->root != NULL)
        return list->root->element;
    else
        return NULL;
}

void* linked_list_next_get(Linked_List_t* list)
{
    void* element = NULL;
    if (list->iterator != NULL)
    {
        /* Advance and return the element */
        list->iterator = list->iterator->next;
        if (list->iterator != NULL) element = list->iterator->element;
    }
    return element;
}

void* linked_list_back_get(Linked_List_t* list)
{
    list->iterator = list->last;
    if (list->last != NULL)
        return list->last->element;
    else
        return NULL;
}

void* linked_list_previous_get(Linked_List_t* list)
{
    void* element = NULL;
    if (list->iterator != NULL)
    {
        /* Advance and return the element */
        list->iterator = list->iterator->previous;
        if (list->iterator != NULL) element = list->iterator->element;
    }
    return element;
}
