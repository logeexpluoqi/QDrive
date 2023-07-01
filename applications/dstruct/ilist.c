/*
 * @Author: luoqi 
 * @Date: 2023-07-02 02:42:17 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-07-02 02:44:07
 */

#include "ilist.h"

void list_init(ListObj* list)
{
    list->next = list->prev = list;
}

void list_insert_after(ListObj* list, ListObj* node)
{
    list->next->prev = node;
    node->next = list->next;

    list->next = node;
    node->prev = list;
}

void list_insert_before(ListObj* list, ListObj* node)
{
    list->prev->next = node;
    node->prev = list->prev;

    list->prev = node;
    node->next = list;
}

void list_remove(ListObj* node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;

    node->next = node->prev = node;
}

int list_isempty(const ListObj* list)
{
    return list->next == list;
}

uint32_t list_len(const ListObj* list)
{
    uint32_t len = 0;
    const ListObj* p = list;
    while (p->next != list) {
        p = p->next;
        len++;
    }

    return len;
}
