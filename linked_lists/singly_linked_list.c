/******************************************************************************/
/*!
 * @file  singly_linked_list.c
 * @brief Copying an on paper solution - Didn't try to add std libs on paper.
 * 
 * @author Cathal Harte <cathal.harte@protonmail.com>
 *
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include <stdio.h>
#include <stdlib.h> // for calloc and free
#include <stdint.h> // necessary for uint32_t

/*******************************************************************************
* Definitions and types
*******************************************************************************/

typedef struct linked_elem
{
    uint32_t data;
    struct linked_elem *next; // was missing "struct"
} linked_elem_t;

/*******************************************************************************
* Internal function prototypes
*******************************************************************************/

linked_elem_t* delete_elem_from_list(linked_elem_t *elem, linked_elem_t *start_elem);

void delete_all_elems_from_list(linked_elem_t *start_elem);

void add_elem_to_list_after(uint32_t elem_data, linked_elem_t* location_to_add);

linked_elem_t* find_last_elem_in_list(linked_elem_t *start_elem);

/*******************************************************************************
* Data
*******************************************************************************/


/*******************************************************************************
* Functions
*******************************************************************************/

int main(void)
{
    linked_elem_t root_elem;
    root_elem.data = 11;
    root_elem.next = NULL;

    add_elem_to_list_after(13, &root_elem);
    add_elem_to_list_after(15, root_elem.next);
    linked_elem_t* last_elem = find_last_elem_in_list(&root_elem);

    for (int i = 0; i < 7; i++)
    {
        add_elem_to_list_after((i+8), last_elem);
        last_elem = last_elem->next;
    }

    delete_all_elems_from_list(&root_elem);
}

linked_elem_t* delete_elem_from_list(linked_elem_t *elem, linked_elem_t *start_elem)
{
    linked_elem_t *iterator = start_elem;

    if(elem == start_elem)
    {
        iterator = start_elem->next;
        free(elem);
        return iterator;
    }

    while(iterator->next != NULL)
    {
        if(iterator->next == elem)
        {
            iterator->next = elem->next;
            free(elem);
            return start_elem;
        }
        iterator = iterator->next;
    }
    return NULL;

}

void delete_all_elems_from_list(linked_elem_t *start_elem)
{
    while(start_elem != NULL)
    {
        start_elem = delete_elem_from_list(start_elem, start_elem);
    }
}

// This function cannot add an elem to the start, so that's a limitation
// It can, however, add to the end
void add_elem_to_list_after(uint32_t elem_data, linked_elem_t* location_to_add)
{
    linked_elem_t* new_elem = calloc(1, sizeof *new_elem);
    new_elem->data = elem_data;
    new_elem->next = location_to_add->next;
    location_to_add->next = new_elem;
}

linked_elem_t* find_last_elem_in_list(linked_elem_t *start_elem)
{
    while(start_elem->next != NULL)
    {
        start_elem = start_elem->next;
    }
    return start_elem;
}