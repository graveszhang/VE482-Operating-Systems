//
// Created by Graves Zhang on 9/14/20.
//

#ifndef P1_READ_H
#define P1_READ_H

#include "execute.h"

int mread(char *line, char *goodline);

Bool Redirection_Complete(char *line, int pos);

Bool Quotation_Complete(char* line);

typedef struct _stack {
    char container[16]; // for quote pairs
    int size;
}Stack;

int IsEmpty(Stack* stack);

void Push(Stack* stack, char ch); // add ch in stack

char Top(Stack* stack);

char Pop(Stack* stack);

#endif //P1_READ_H
