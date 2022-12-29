#include <stdlib.h>
#include <stdio.h>
#include "logger.h"


typedef struct Node {
    char symbol;
    struct Node* next;
} node;


typedef struct String {
    node* head;
} String;


String* initString() {
    String* sPtr = calloc(1, sizeof(String));
    sPtr->head = NULL;
    return sPtr;
}


void append(String* s, char val) {
    node* newNodePtr = (node*)calloc(1, sizeof(node));
    if (newNodePtr == NULL)
        logErrorAndExit("Can't allocate memory", 1);

    newNodePtr->symbol = val;
    newNodePtr->next = NULL;

    if (s->head == NULL) {
        s->head = newNodePtr;
        return;
    }

    node* curNode = s->head;
    while (curNode->next != NULL)
        curNode = curNode->next;
    curNode->next = newNodePtr;
}


void print(String* s) {
    if (s->head == NULL) return;

    printf("\x1b[32m\"\x1b[0m");
    node* curNode = s->head;
    while (curNode != NULL) {
        printf("\x1b[32m%c\x1b[0m", curNode->symbol);
        curNode = curNode->next;
    }
    printf("\x1b[32m\"\x1b[0m\n");
}


void freeString(String** s) {
    if (*s == NULL) return;

    node* curNode = (*s)->head;
    node* prevNode = NULL;
    free(*s);
    while (curNode != NULL) {
        prevNode = curNode;
        curNode = curNode->next;
        free(prevNode);
    }

    *s = NULL;
}


int scanString(String* s) {
    char c = getchar();
    while (c != EOF && c != '\n') {
        append(s, c);
        c = getchar();
    }
    if (c == EOF) return EOF;
    return 1;
}
