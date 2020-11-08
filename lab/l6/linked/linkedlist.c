yo#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void list_init(List **list) {
    *list = malloc(sizeof(List));
    (*list)->first = NULL;
    (*list)->length = 0;
}

void list_free(List *list) {
    Node *temp = list->first;
    for (int i = 0; i < list->length; i++) {
        temp = temp->next;
        free(list->first->str);
        free(list->first->data);
        free(list->first);
        list->first = temp;
    }
    free(list);
}

Node *list_insert(List *list, char *str, void *data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->str = str;
    new_node->data = data;
    list->length++;
    if (list->first) new_node->next = list->first;
    else new_node->next = NULL;
    list->first = new_node;
    return new_node;
}

const Node *list_search(List *list, const Node *first, const void *data, int (*cmp)(const void *, const void *)) {
    if (list->first == NULL) return NULL;
    if (first == NULL) first = list->first;
    else first = first->next;
    while (first) {
        if (cmp(first->data, data)) return first;
        first = first->next;
    }
    return first;
}

void list_sort(List *list, int (*cmp)(const void *, const void *)) {
    if (list->length == 0)return;
    Node *arr = malloc(sizeof(Node) * list->length);
    Node *temp = list->first;
    for (size_t i = 0; i < list->length; i++) {
        memcpy(arr + i, temp, sizeof(Node));
        temp = temp->next;
    }
    qsort(arr, list->length, sizeof(Node), cmp);
    temp = list->first;
    for (size_t i = 0; i < list->length; i++) {
        temp->str = arr[i].str;
        temp->data = arr[i].data;
        temp = temp->next;
    }
    free(arr);
}

void list_print(const List *list, FILE *file, void(*print)(FILE *file, const void *)) {
    Node *temp = list->first;
    for (size_t i = 0; i < list->length; i++) {
        fprintf(file, "%s=", temp->str);
        print(file, temp->data);
        fprintf(file, "\n");
        temp = temp->next;
    }
}
