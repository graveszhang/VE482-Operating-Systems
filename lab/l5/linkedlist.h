//
// Created by grave on 2020/10/26.
//

#ifndef L5_LINKEDLIST_H
#define L5_LINKEDLIST_H

#include <stdio.h>

typedef struct node {
    char *str;
    void *data;
    struct node *next;
} Node;

typedef struct list {
    struct node *first;
    size_t length;
} List;

Node *list_insert(List *list, char *str, void *data);
void list_init(List **list);
void list_sort(List *list, int (*cmp)(const void *, const void *));
void list_print(const List *list, FILE *file, void(*print)(FILE* file, const void *));
void list_free(List *list);

#endif //L5_LINKEDLIST_H