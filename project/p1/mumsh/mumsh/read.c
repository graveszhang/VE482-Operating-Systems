//
// Created by Graves Zhang on 9/14/20.
//

#include "read.h"
#include "execute.h"
#include "parse.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int IsEmpty(Stack* stack){
    return stack->size == 0;
}

void Push(Stack* stack, char ch){
    stack->container[stack->size] = ch;
    stack->size += 1;
}

char Top(Stack* stack){
    return stack->container[stack->size-1];
}

char Pop(Stack* stack){
    stack->size -= 1;
    return stack->container[stack->size];
}

Bool Redirection_Complete(char *line, int pos) {
    if (line[0] == '\0')
        return False;
    int i = pos - 1;

    while(i > 0 && line[i] == ' '){
        i--;
    }
    if (line[i] == '|' || line[i] == '<' || line[i] == '>') {
        return False;
    }
    return True;
}

Bool Quotation_Complete(char* line) {
    Stack quote;
    quote.size = 0;
    memset(quote.container, '\0', 16);

    if (line[0] == '\0')
        return True;

    int i = 0;
    while (line[i] != '\0') {
        if (line[i] == '\'' || line[i] == '\"') {
            if (IsEmpty(&quote) || Top(&quote) != line[i])
                Push(&quote, line[i]);
            else if (Top(&quote) == line[i])
                Pop(&quote);

        }
        i++;
    }

    if (IsEmpty(&quote))
        return True;
    else
        return False;
}

int mread(char *line) {
    printf("mumsh $ ");
    fflush(stdout);

    char c;
    int i = 0;
    char buffer[1024];
    memset(buffer, '\0', 1024);

//    while ((c = (char) fgetc(stdin)) != '\n') {
    while (1) {
        c = (char) fgetc(stdin);
        if (i >= 1024) break;

        if (c == '\n') {
            if (i == 0) {
                printf("mumsh $ ");
                continue;
            }
            if (Quotation_Complete(buffer) == True && Redirection_Complete(buffer, i) == True) {
                qparse(buffer, i); // i is current length of input
                break;
            } else if (Redirection_Complete(buffer, i) == False) {
                printf("> ");
                fflush(stdout);
                continue;
            } else {
                buffer[i++] = '\n';
                printf("> ");
                fflush(stdout);
                continue;
            }
        } else if (c == EOF) { // handle ctrl-d
//            printf("DEBUGG:%s\n", buffer[0]);
            if (buffer[0] != '\0') {
                fflush(stdin);
                continue;
            } else {
                printf("exit\n");
                fflush(stdout);
                exit(0);
            }
        } else {
            buffer[i] = c;
        }
        i += 1;
    }
    buffer[i] = '\0';
    strcpy(line, buffer);
    return 0;
}

