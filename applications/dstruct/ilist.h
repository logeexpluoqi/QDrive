/*
 * @Author: luoqi 
 * @Date: 2023-07-02 02:42:25 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-07-02 02:43:53
 */

#ifndef _ILIST_H
#define _ILIST_H

#include <stdint.h>

#define offset_of(type, member)             ((unsigned long) &((type*)0)->member)
#define container_of(ptr, type, member)     ((type *)((char *)(ptr) - offset_of(type, member)))

typedef struct list_structure
{
    struct list_structure* next;
    struct list_structure* prev;
} ListObj;

#define LIST_HEAD_INIT(name)    {&(name), &(name)}
#define LIST_HEAD(name)         ListObj name = LIST_HEAD_INIT(name)

void list_init(ListObj* list);
void list_insert_after(ListObj* list, ListObj* node);
void list_insert_before(ListObj* list, ListObj* node);
void list_remove(ListObj* node);
int list_isempty(const ListObj* list);
uint32_t list_len(const ListObj* list);

#define list_entry(node, type, member) \
    container_of(node, type, member)

#define list_for_each(pos, list) \
    for (pos = (list)->next; pos != (list); pos = pos->next)

#define list_for_each_safe(pos, n, list) \
	for (pos = (list)->next, n = pos->next; pos != (list); \
		pos = n, n = pos->next)


#endif
